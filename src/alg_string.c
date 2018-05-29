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
    BOOL static_matcharr[32*32], *dp;
    int len = strlen(str);
    int patt_len = strlen(pattern);
    int i, j, res;

#define IFMATCH(row, col)  (dp[(row)*patt_len + (col)])

    if (len <= 0 || patt_len <= 0)
    {
        return len <= 0 && patt_len <= 0;
    }

    if (len*patt_len > sizeof(static_matcharr)/sizeof(static_matcharr[0]))
        dp = (BOOL *)malloc(len*patt_len*sizeof(BOOL));
    else
        dp = static_matcharr;

    if (!dp)
        return FALSE;

    for (i = 0; i < len; ++i)
    {
        for (j = 0; j < patt_len; ++j)
        {
            if ('?' == pattern[j] || str[i] == pattern[j])
            {
                if (i > 0 && j > 0)
                {
                    IFMATCH(i, j) = IFMATCH(i-1, j-1);
                }
                else if (j > 0)
                {
                    BOOL has_char = FALSE;
                    int k = 0;
                    for (; k < j; k++)
                    {
                        if (pattern[k] != '*')
                        {
                            has_char = TRUE;
                            break;
                        }
                    }
                    IFMATCH(i, j) = !has_char;
                }
                else
                {
                    IFMATCH(i, j) = (0 == i && 0 == j);
                }
            }
            else if ('*' == pattern[j])
            {
                if (i > 0 && j > 0)
                {
                    IFMATCH(i, j) = IFMATCH(i, j-1) || IFMATCH(i-1, j) || IFMATCH(i-1, j-1);
                }
                else if (j > 0)
                {
                    IFMATCH(i, j) = IFMATCH(i, j-1);
                }
                else
                {
                    IFMATCH(i, j) = TRUE;
                }
            }
            else
            {
                IFMATCH(i, j) = FALSE;
            }
        }
    }

    res = IFMATCH(len-1, patt_len-1);

    if (dp != static_matcharr)
        free(dp);

    return res;
}
