#include "WiFi.h"
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <FreeRTOS.h>
#include <task.h>
#include <wifi_mgmr_ext.h>
#include <hal_wifi.h>
#include <aos/yloop.h>
#include <event_device.h>
#include <lwip/tcpip.h>

static void arduino_wifi_event_handler(input_event_t *event, void *private_data)
{
    if (event) {
        printf("[WiFi] EVENT RECEIVED code=%d\r\n", event->code);
        WiFi._handle_event(event->code);
    }
}

#ifdef __cplusplus
}
#endif

WiFiClass WiFi;

static wifi_conf_t s_wifi_conf = {
    .country_code = "CN",
};

WiFiClass::WiFiClass() :
    _state(WIFI_NOT_STARTED),
    _req_mode(WIFI_MODE_NONE),
    _status(WL_DISCONNECTED),
    _channel(1)
{
    memset(_ssid, 0, sizeof(_ssid));
    memset(_pass, 0, sizeof(_pass));
}

void WiFiClass::ensure_init()
{
    if (_state != WIFI_NOT_STARTED) return;
    _state = WIFI_STARTING;

    printf("[WiFi] ensure_init ENTER\r\n");

    printf("[WiFi] before tcpip_init\r\n");
    tcpip_init(NULL, NULL);
    printf("[WiFi] after tcpip_init\r\n");

    printf("[WiFi] before wifi_mgmr_cli_init\r\n");
    wifi_mgmr_cli_init();
    printf("[WiFi] after wifi_mgmr_cli_init\r\n");

    printf("[WiFi] before event registration\r\n");
    aos_register_event_filter(EV_WIFI, arduino_wifi_event_handler, NULL);
    printf("[WiFi] after event registration\r\n");

    printf("[WiFi] before firmware task\r\n");
    hal_wifi_start_firmware_task();
    printf("[WiFi] after firmware task\r\n");

    printf("[WiFi] before post event\r\n");
    aos_post_event(EV_WIFI, CODE_WIFI_ON_INIT_DONE, 0);
    printf("[WiFi] after post event\r\n");
}

void WiFiClass::_handle_event(int code)
{
    switch (code) {
        case CODE_WIFI_ON_INIT_DONE:
        {
            printf("[WiFi] CODE_WIFI_ON_INIT_DONE: starting background manager\r\n");
            wifi_mgmr_start_background(&s_wifi_conf);
        }
        break;

        case CODE_WIFI_ON_MGMR_DONE:
        {
            printf("[WiFi] CODE_WIFI_ON_MGMR_DONE: manager ready\r\n");
            _state = WIFI_MANAGER_READY;

            if (_req_mode == WIFI_MODE_AP && strlen(_ssid) > 0) {
                _state = WIFI_AP_STARTING;
                char *pass_arg = (strlen(_pass) >= 8) ? _pass : NULL;
                wifi_interface_t wifi_if = wifi_mgmr_ap_enable();
                printf("[WiFi] starting AP: SSID=%s\r\n", _ssid);
                int ret = wifi_mgmr_ap_start((wifi_interface_t *)wifi_if, _ssid, 0, pass_arg, _channel);
                printf("[WiFi] ap_start ret=%d\r\n", ret);
            } else if (_req_mode == WIFI_MODE_STA && strlen(_ssid) > 0) {
                _state = WIFI_STA_CONNECTING;
                char *pass_arg = (strlen(_pass) > 0) ? _pass : NULL;
                wifi_interface_t wifi_if = wifi_mgmr_sta_enable();
                wifi_mgmr_sta_connect_mid(
                    &wifi_if,
                    _ssid,
                    pass_arg,
                    NULL,
                    NULL,
                    0,
                    0,
                    1,
                    WIFI_CONNECT_PMF_CAPABLE
                );
            }
        }
        break;

        case CODE_WIFI_ON_CONNECTING:
            _state = WIFI_STA_CONNECTING;
            _status = WL_IDLE_STATUS;
            break;

        case CODE_WIFI_ON_CONNECTED:
        case CODE_WIFI_ON_GOT_IP:
            _state = WIFI_CONNECTED;
            _status = WL_CONNECTED;
            break;

        case CODE_WIFI_ON_DISCONNECT:
            _state = WIFI_MANAGER_READY;
            _status = WL_DISCONNECTED;
            break;

        case CODE_WIFI_ON_AP_STARTED:
            printf("[WiFi] CODE_WIFI_ON_AP_STARTED\r\n");
            _state = WIFI_AP_STARTED;
            _status = WL_CONNECTED;
            break;

        case CODE_WIFI_ON_AP_STOPPED:
            _state = WIFI_MANAGER_READY;
            _status = WL_DISCONNECTED;
            break;

        default:
            break;
    }
}

int WiFiClass::begin(const char *ssid, const char *password)
{
    if (!ssid || strlen(ssid) == 0) return WL_CONNECT_FAILED;

    _req_mode = WIFI_MODE_STA;
    strncpy(_ssid, ssid, sizeof(_ssid) - 1);
    if (password) {
        strncpy(_pass, password, sizeof(_pass) - 1);
    } else {
        memset(_pass, 0, sizeof(_pass));
    }

    if (_state == WIFI_NOT_STARTED) {
        ensure_init();
    } else if (_state >= WIFI_MANAGER_READY) {
        _state = WIFI_STA_CONNECTING;
        char *pass_arg = (strlen(_pass) > 0) ? _pass : NULL;
        wifi_interface_t wifi_if = wifi_mgmr_sta_enable();
        wifi_mgmr_sta_connect_mid(
            &wifi_if,
            _ssid,
            pass_arg,
            NULL,
            NULL,
            0,
            0,
            1,
            WIFI_CONNECT_PMF_CAPABLE
        );
    }

    _status = WL_IDLE_STATUS;
    return _status;
}

int WiFiClass::status()
{
    if (_state == WIFI_CONNECTED || _state == WIFI_AP_STARTED) {
        return WL_CONNECTED;
    }
    if (_state == WIFI_STA_CONNECTING || _state == WIFI_AP_STARTING || _state == WIFI_STARTING) {
        return WL_IDLE_STATUS;
    }
    return WL_DISCONNECTED;
}

IPAddress WiFiClass::localIP()
{
    uint32_t ip = 0, gw = 0, mask = 0;
    wifi_mgmr_sta_ip_get(&ip, &gw, &mask);
    return IPAddress(ip);
}

bool WiFiClass::disconnect()
{
    if (_status == WL_CONNECTED) {
        wifi_mgmr_sta_disconnect();
        _state = WIFI_MANAGER_READY;
        _status = WL_DISCONNECTED;
        return true;
    }
    return false;
}

bool WiFiClass::softAP(const char *ssid, const char *password, int channel)
{
    if (!ssid || strlen(ssid) == 0) return false;

    _req_mode = WIFI_MODE_AP;
    _channel = channel;
    strncpy(_ssid, ssid, sizeof(_ssid) - 1);
    if (password) {
        strncpy(_pass, password, sizeof(_pass) - 1);
    } else {
        memset(_pass, 0, sizeof(_pass));
    }

    if (_state == WIFI_NOT_STARTED) {
        ensure_init();
    } else if (_state >= WIFI_MANAGER_READY) {
        _state = WIFI_AP_STARTING;
        char *pass_arg = (strlen(_pass) >= 8) ? _pass : NULL;
        wifi_interface_t wifi_if = wifi_mgmr_ap_enable();
        wifi_mgmr_ap_start((wifi_interface_t *)wifi_if, _ssid, 0, pass_arg, _channel);
    }

    return true;
}

IPAddress WiFiClass::softAPIP()
{
    uint32_t ip = 0, gw = 0, mask = 0;
    wifi_mgmr_ap_ip_get(&ip, &gw, &mask);
    if (ip == 0) {
        return IPAddress(192, 168, 4, 1);
    }
    return IPAddress(ip);
}
