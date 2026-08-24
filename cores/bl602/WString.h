#ifndef WString_h
#define WString_h

#include <stdlib.h>
#include <string.h>

class String {
private:
    char *buffer;
    unsigned int capacity;
    unsigned int len;

public:
    String(const char *cstr = "");
    String(const String &str);
    ~String();

    unsigned int length() const { return len; }
    const char *c_str() const { return buffer ? buffer : ""; }
    operator const char *() const { return c_str(); }

    String &operator=(const char *cstr);
    String &operator=(const String &rhs);
};

#endif
