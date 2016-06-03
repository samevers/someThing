#ifndef STRING_UTIL_H
#define STRING_UTIL_H
#include <string.h>
#include <string>
#include <vector>
#include <iconv.h>
#include "sso_string/sso_string.h"

int _utf16_to_utf8(const my_sso_string &src, my_sso_string &result);
int _utf8_to_utf16(const my_sso_string &src, my_sso_string &result);
int _utf16_to_gbk(const my_sso_string &src, my_sso_string &result);
int _gbk_to_utf16(const my_sso_string &src, my_sso_string &result);
int _gbk_to_utf16le(const my_sso_string &src, my_sso_string &result);
int _utf8_to_gbk(const my_sso_string &src, my_sso_string &result);
int _gbk_to_utf8(const my_sso_string &src, my_sso_string &result);
int gbk2utf8(char * in, int * inlen,char * out, int * outlen);

//string strim
my_sso_string trim_left(my_sso_string &s,const my_sso_string &drop);
my_sso_string trim(my_sso_string &s,const my_sso_string &drop);
my_sso_string trimall(my_sso_string &src);
//my_sso_string trim_line1(my_sso_string &s);
//my_sso_string trim_line2(my_sso_string &s);
//my_sso_string trim_line(my_sso_string &s);

my_sso_string cut_strLen(my_sso_string &src,int len);
my_sso_string  str_find(my_sso_string &src,int ibeg,my_sso_string begtag,my_sso_string endtag,int &ifind);

void toUpper(std::basic_string<char>& s);
void toLower(std::basic_string<char>& s);
my_sso_string ToDBS(my_sso_string str);

char * cltrim ( char * sLine );
char * crtrim ( char * sLine );
char * ctrim ( char * sLine );

int strtoks(const char *src,const char *sep,std::vector<my_sso_string> &ret);
int separateIP(const char *value, char *ip, int *port);

uint64_t hex2uint64(const my_sso_string hexStr);

//hash�㷨����

unsigned int _sgHash(const void *key, int len);
//url process
#endif
