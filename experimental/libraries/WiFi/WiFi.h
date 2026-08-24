#ifndef WiFi_h
#define WiFi_h

#include "Arduino.h"
#include "IPAddress.h"

enum wl_status_t {
    WL_NO_SHIELD = 255,
    WL_IDLE_STATUS = 0,
    WL_NO_SSID_AVAIL = 1,
    WL_SCAN_COMPLETED = 2,
    WL_CONNECTED = 3,
    WL_CONNECT_FAILED = 4,
    WL_CONNECTION_LOST = 5,
    WL_DISCONNECTED = 6
};

enum wifi_state_t {
    WIFI_NOT_STARTED = 0,
    WIFI_STARTING,
    WIFI_MANAGER_READY,
    WIFI_AP_STARTING,
    WIFI_AP_STARTED,
    WIFI_STA_CONNECTING,
    WIFI_CONNECTED
};

enum wifi_mode_req_t {
    WIFI_MODE_NONE = 0,
    WIFI_MODE_STA,
    WIFI_MODE_AP
};

class WiFiClass {
private:
    wifi_state_t _state;
    wifi_mode_req_t _req_mode;
    wl_status_t _status;
    int _channel;
    char _ssid[33];
    char _pass[65];

    void ensure_init();

public:
    WiFiClass();

    int begin(const char *ssid, const char *password = NULL);
    int status();
    IPAddress localIP();
    bool disconnect();

    bool softAP(const char *ssid, const char *password = NULL, int channel = 1);
    IPAddress softAPIP();

    void _handle_event(int code);
};

extern WiFiClass WiFi;

#endif
