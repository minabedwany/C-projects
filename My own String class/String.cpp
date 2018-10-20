// String.cpp
//
// ICS 46 Spring 2018
// Project #0: Getting to Know the ICS 46 VM
//
// Implement all of your String member functions in this file.
//
// Note that the entire standard library -- both the C Standard
// Library and the C++ Standard Library -- is off-limits for this
// task, as the goal is to exercise your low-level implementation
// skills (pointers, memory management, and so on).

#include "String.hpp"
#include "OutOfBoundsException.hpp"

int String::strlen(const char* s)
{
    int len = 0;
    for (int i = 0; s[i] != '\0'; ++i)
        ++len;
    return len;
}

char* String :: strcpy(char* dest, const char* src)
{
    int i;
    for(i = 0; src[i] != '\0'; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char* String :: strdup(const char* src)
{
    return strcpy(new char[strlen(src)+1], src);
}

char* String :: strcat(char* dest, const char* src)
{
    strcpy(dest + strlen(dest), src);
    return dest;
}

int String::strncmp(const char* left, const char* right, int n)
{
    for (int i = 0; i < n; ++i)
        if(left[i] != right[i])
            return left[i] - right[i];
    return 0;
}

char* String::strchr(char* str, int c)
{
    for(int i = 0; str[i] != '\0'; ++i)
    {
        if(str[i] == (char) c)
            return str+i;
    }
    return nullptr;
}

char* String::strstr(char* haystack, const char* needle)
{
    int len = strlen(needle);
    char* s = haystack;
    char* p;
    while(*s != '\0')
    {
        p = strchr(s, needle[0]);
        if(p == nullptr)
            return nullptr;
        if (strncmp(p, needle, len) == 0)
            return p;
        else
            s = p+1;
    }
    return nullptr;
}

//-------------------------------------------------------


String :: String()
    :buf(strdup(""))
{
}

String :: String(const char* s)
    :buf(strdup(s))
{
}

String :: String(const String & s)
    :buf(strdup(s.buf))
{
}

String:: ~String() noexcept
{
    delete[] buf;
}

String& String::operator=(const String& s)
{
    delete[] buf;
    buf = strdup(s.buf);
    return *this;
}

void String::append(const String& s)
{
    char* p = new char[strlen(buf) + strlen(s.buf) + 1];
    strcpy(p, buf);
    strcat(p, s.buf);
    delete[] buf;
    this->buf = p;

}

char String::at(unsigned int index) const
{
    if(index >= strlen(buf))
        throw OutOfBoundsException();
    return buf[index];
}

char& String::at(unsigned int index)
{
    if(index >= strlen(buf))
        throw OutOfBoundsException();
    return buf[index];

}

void String::clear()
{
    delete[] buf;
    buf = strdup("");
}

int String::compareTo(const String& s) const noexcept
{
    for (int i = 0; buf[i] != '\0' || s.buf[i] != '\0'; ++i)
        if(buf[i] != s.buf[i])
            return buf[i] - s.buf[i];
    return 0;
}

String String::concatenate(const String& s) const
{
    char* p = new char[strlen(buf) + strlen(s.buf) + 1];
    strcpy(p, buf);
    strcat(p, s.buf);
    String result(p);
    delete[] p;
    return result;

}

bool String::contains(const String& substring) const noexcept
{
    char* p = strstr(buf, substring.buf);
    if (p != nullptr)
        return true;
    return false;
}

bool String::equals(const String& s) const noexcept
{
    return compareTo(s) == 0;
}

int String::find(const String& substring) const noexcept
{
    char* p = strstr(buf, substring.buf);
    if (p != nullptr)
        return p - buf;
    return -1;
}

bool String::isEmpty() const noexcept
{
    return strlen(buf) == 0;
}

unsigned int String::length() const noexcept
{
    if( buf != nullptr)
        return strlen(buf);
    else
        return 0;
}

String String::substring(unsigned int startIndex, unsigned int endIndex) const
{
    if(startIndex > endIndex)
    {
        String empty;
        return empty;
    }

    if(startIndex > strlen(buf) || endIndex > strlen(buf))
        throw OutOfBoundsException();

    int i;
    char* target = new char[endIndex - startIndex + 1];
    for(i = 0; i < endIndex - startIndex; ++i)
        target[i] = buf[startIndex + i];
    target[i] = '\0';
    String result(target);
    delete[] target;
    return result;
}

const char* String::toChars() const noexcept
{
    return buf;
}

