#include "alg_string.h"

char *
alg_replace(char *buf, int buflen, const char *substr, const char *newstr)
{
    char *preptr = buf;
    int substr_len = strlen(substr);
    char *ptr;

    if (substr_len == 0)
    {
        return buf;
    }

    int newstr_len = strlen(newstr);

    while ((ptr = strstr(preptr, substr)))
    {
        int len = strlen(ptr+substr_len) + 1;

        if ((preptr-buf) + newstr_len + len > buflen)
        {
            return ptr;
        }

        memmove(ptr+newstr_len, ptr+substr_len, len);
        memcpy(ptr, newstr, newstr_len);

        preptr = ptr + newstr_len;
    }

    return preptr;
}

BOOL
alg_wildcard_match(const char *str, const char *pattern)
{
    switch (*pattern)
    {
    case '?':
        if (*str)
        {
            return alg_wildcard_match(str+1, pattern+1);
        }
        else
        {
            return FALSE;
        }
    case '*':
        if (*str)
        {
            return alg_wildcard_match(str+1, pattern);
        }
        else
        {
            return TRUE;
        }
    case '\0':
        return '\0' == *str;
    default:
        if (*str == *pattern)
        {
            return alg_wildcard_match(str+1, pattern+1);
        }
        else
        {
            return FALSE;
        }
    }
}
