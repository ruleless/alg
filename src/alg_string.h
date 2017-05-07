#ifndef __ALG_STRING_H__
#define __ALG_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "alg_common.h"

/* 字符串替换
 * @param buf    字符串缓冲区
 * @param buflen 字符串缓冲区长度
 * @param substr 需要被替换的子串
 * @param newstr 替换子串的新串
 * @return 返回最后一次进行子串替换后，新串之后的第一个字符的地址；
 *         若没有匹配到任何子串则返回buf
 */
char *alg_replace(char *buf, int buflen, const char *substr, const char *newstr);

/* 简单通配符匹配
 * @param str     待匹配串
 * @param pattern 通配符串(仅支持通配符?*)
 * @return TRUE 匹配 FALSE 不匹配
 */
BOOL alg_wildcard_match(const char *str, const char *pattern);

#ifdef __cplusplus
}
#endif

#endif /* __ALG_STRING_H__ */


