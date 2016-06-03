/*******************************************************

* �ļ����� gary_common.h
* ��  �ܣ� ��Գ��ú����ķ�װ
* ��  ���� version 1.0 2010-4-18
* ��  �ģ�

********************************************************/

#ifndef __GARY_COMMON_H_
#define __GARY_COMMON_H_
#include "twsetypedef.h"

namespace spaceGary
{

//�Ƿ���GBK����
 /**
        *���Ĳ���:
        *[A1A0 - A1FF]  	ȫ�Ǳ�����   			���˵�
        *[A2A0 - A2FF]     ���ֱ�����   			���˵�
        *[A3A0 - A3FF]   	�����ASCII�ַ���Ӧ     	ת������Ӧ��ASCII�ַ�,Ӣ�ķִʴ���
        *[A4-A5,A0-FF]     ����Ƭ����				���ķִʴ���
        *[A6-A9,A0-FF]   	���ַ���					���˵�
        *[A8-A9,40-9F]   	���ַ���					���˵�
        *[B0-F7,A0-FF]   	GB2312����				���ķִʴ���
        *[81-A0,40-FF]   	��չ���ֵ�һ����			���ķִʴ������˵�
        *[AA-FE,40-AF]  	��չ���ֵڶ�����			���ķִʴ������˵�     
*/
inline 
TBOOL IsStrictGBKChar(const TCHAR* szWord)
{
    const TUCHAR c1 = (const TUCHAR)*szWord;
    const TUCHAR c2 = (const TUCHAR)*(szWord+1);

    if (
                ((c1 >= 0xA1 && c1 <= 0xA9) && (c2 >= 0xA0 && c2 <= 0xFF)) ||
                ((c1 >= 0xA8 && c1 <= 0xA9) && (c2 >= 0x40 && c2 <= 0xFF)) ||
                ((c1 >= 0xB0 && c1 <= 0xF7) && (c2 >= 0xA0 && c2 <= 0xFF)) ||
                ((c1 >= 0x81 && c1 <= 0xA0) && (c2 >= 0x40 && c2 <= 0xFF)) ||
                ((c1 >= 0xAA && c1 <= 0xFE) && (c2 >= 0x40 && c2 <= 0xAF)) 
         )
     {
		 return TRUE;
     }

     return FALSE;
}


//�Ƿ��������GBK
inline
TBOOL IsIncludeChnGBK(const TCHAR* szText, TUINT32 udwTextLen)
{
	const TCHAR* pCur = szText;

	while (pCur < szText+udwTextLen)
	{
		if (*pCur < 0)
		{
			if ((pCur+1) < (szText + udwTextLen))
			{
				if (IsStrictGBKChar(pCur))
				{
					pCur += 2;
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
		}

		pCur++;
	}
	return FALSE;
}

}; //end space

#endif