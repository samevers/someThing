#ifndef __ENCODING_UTILITY_H
#define __ENCODING_UTILITY_H

#include <cstddef>

typedef unsigned short gchar_t;

//���Ŀո�
static const gchar_t CHINESE_SPACE_CHAR = 0xA1A1;
//���õ���һ�����Ŀո�
static const gchar_t CHINESE_SPACE_CHAR2 = 0xA0A3;
//ASCII�Ŀո�ת����Ľ��
static const gchar_t SPACE_CONVERSION_CHAR = 0xA0A1;
//ASCII��tabת����Ľ��
static const gchar_t TAB_CONVERSION_CHAR = 0x0920;

class EncodingConvertor{
private:
    static EncodingConvertor *dinstance;

    static const int MAP_ARR_SIZE = 256;

    unsigned short** pFanToJianMap;

    EncodingConvertor();
    ~EncodingConvertor();

    bool InitFan2JianMap();
    bool DestroyFan2JianMap();

    void EncodeChar(const char *p, char &hc, char &lc);
    void DecodeChar(const char *p, char *q); 

public:
    static EncodingConvertor *Instance(){
        if(dinstance) return dinstance;
        dinstance = new EncodingConvertor();
        return dinstance;
    }

    static void ReleaseInstance(){
        delete dinstance;
        dinstance = NULL;
    }

    //���תȫ��
    // return : ȫ���ַ��ĸ���,����������0�� ʧ�ܷ���-1
    int dbc2sbc(const char *p, char *q, int qlen, bool trans_fan = true, bool trans_alpha = true);

    //ȫ��ת���
    // return : �ַ������ֽ�����ʧ�ܷ���-1
    int sbc2dbc(const char *p, char *q, int qlen, bool trans_fan = true, bool trans_alpha = true);

    //url����
    bool urlEncode(const char *src, char *dst, int dlen);

    //url����
    bool urlDecode(const char *src, char *dst, int dlen);

};

inline
bool isGBKChnChar(gchar_t wc) {
    unsigned char * upc = (unsigned char *)&wc;
    unsigned char b1 = *upc;
    unsigned char b2 = *(upc+1);
    
    //GBK�к��ֱ�������������
    //GBK-2��(GB2312����)��B0A1-F7FE
    //GBK-3����8140-A0FE
    //GBK-4����AA40-FEA0
    if (((b1 >= 0xB0) && (b1 <= 0xF7) && (b2 >= 0xA1) && (b2 <= 0xFE)) || 
        ((b1 >= 0x81) && (b1 <= 0xA0) && (b2 >= 0x40) && (b2 <= 0xFE)) || 
        ((b1 >= 0xAA) && (b1 <= 0xFE) && (b2 >= 0x40) && (b2 <= 0xA0)))
    {
        return true;
    }

    return false;
}

#endif
