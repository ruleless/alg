#ifndef __ALG_STRING_H__
#define __ALG_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "alg_common.h"

char *alg_replace(char *buf, int buflen, const char *substr, const char *newstr);

#ifdef __cplusplus
}
#endif

#endif /* __ALG_STRING_H__ */

