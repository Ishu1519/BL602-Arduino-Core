#include "WString.h"

String::String(const char *cstr)
{
    if (cstr) {
        len = strlen(cstr);
        capacity = len + 1;
        buffer = (char *)malloc(capacity);
        if (buffer) {
            strcpy(buffer, cstr);
        } else {
            len = 0;
            capacity = 0;
        }
    } else {
        buffer = NULL;
        len = 0;
        capacity = 0;
    }
}

String::String(const String &str)
{
    len = str.len;
    capacity = len + 1;
    buffer = (char *)malloc(capacity);
    if (buffer && str.buffer) {
        strcpy(buffer, str.buffer);
    } else {
        len = 0;
        capacity = 0;
    }
}

String::~String()
{
    if (buffer) {
        free(buffer);
        buffer = NULL;
    }
}

String &String::operator=(const char *cstr)
{
    if (buffer) free(buffer);
    if (cstr) {
        len = strlen(cstr);
        capacity = len + 1;
        buffer = (char *)malloc(capacity);
        if (buffer) strcpy(buffer, cstr);
    } else {
        buffer = NULL;
        len = 0;
        capacity = 0;
    }
    return *this;
}

String &String::operator=(const String &rhs)
{
    if (this != &rhs) {
        *this = rhs.c_str();
    }
    return *this;
}
