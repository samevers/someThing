/*******************************************************

* �ļ����� gary_string.h
* ��  �ܣ� ���string�ķ�װ
* ��  ���� version 1.0 2010-3-31
* ��  �ģ�

********************************************************/

#ifndef __GARY_STRING_H_
#define __GARY_STRING_H_

#include <string>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
//using namespace std;

namespace spaceGary
{

//split
inline
bool StringSplit(std::string strItem, std::vector<std::string> &vectRes, const char* splitWord) {
    vectRes.clear();

	std::string::size_type posOnePart, posFindBegin = 0;
	unsigned int nSplitWordLen = strlen(splitWord);
	posOnePart = strItem.find(splitWord);
	
	while (std::string::npos != posOnePart) {
		
		//���ܽ�splitword�� ���뵽�����
		if (posOnePart != posFindBegin) {
			vectRes.push_back(strItem.substr(posFindBegin, posOnePart-posFindBegin));
		}
		posFindBegin = posOnePart + nSplitWordLen;
		posOnePart = strItem.find(splitWord, posFindBegin);
	}

	//��ֹ�������splitword�����
	if (posFindBegin < strItem.length()) {
		vectRes.push_back(strItem.substr(posFindBegin));
	}
    
	return true;
};

//seg split
inline
bool SegSplit(std::string strItem, std::vector<std::string> &vectRes, const char* splitWord) {
   
	vectRes.clear();

	std::string::size_type posOnePart, posFindBegin = 0;
	unsigned int nSplitWordLen = strlen(splitWord);
	posOnePart = strItem.find(splitWord);
	bool is_pre_seg = false;

	while (std::string::npos != posOnePart) {
		
		//����ָ�����ԭ��һ�£� ����ϵ���ֵ����
		if  (posOnePart == posFindBegin) {
			if (is_pre_seg) {
				vectRes.push_back(splitWord);
			}
			is_pre_seg = true;
		}
		else {
			vectRes.push_back(strItem.substr(posFindBegin, posOnePart-posFindBegin));
			is_pre_seg = false;
		}

		posFindBegin = posOnePart + nSplitWordLen;
		posOnePart = strItem.find(splitWord, posFindBegin);
	}

	//��ֹ�������splitword�����
	if (posFindBegin < strItem.length()) {
		vectRes.push_back(strItem.substr(posFindBegin));
	}
    
	return true;
};

//trim
inline
bool StringTrim(std::string &strItem) {

 
	const char *pItem = strItem.c_str();
	unsigned int nItemLen = strItem.length();
    if (0 ==  nItemLen) {
		return true;
	}
	int left = 0;
	while (pItem[left] == ' ' || pItem[left] == '\t' || pItem[left] == '\r' || pItem[left] == '\n') {
		left++;
	}

	int right = nItemLen-1;
	while (right >=0 && (pItem[right] == ' ' || pItem[right] == '\t' || pItem[right] == '\r' || pItem[right] == '\n')) {
		right--;
	}

	if (left > right) {
		strItem = "";
	}
	else {
		strItem = strItem.substr(left, right-left+1);
	}

	return true;
}

inline
int GetWordNum(const char *src) {

	int num = 0;

	const char *p = src;
	while (*p) {
		if (*p == ' ') {
			p++;
		}
		while (*p) {
			if (*p < 0) {
				if (*(p + 1) == '\0') {
					return num + 1;
				}
				p += 2;
			}
			else if (*p == ' ') {
				p++;
				num++;
				break;
			}
			else {
				p++;
			}
		}
	}

	return num + 1;
}

inline 
const char* GetTheWord(char *src) {
	
	char *p = src;
	if (*p == ' ') {
		p++;
	}
	while (*p && *p != ' ') {
		if (*p < 0) {
			p += 2;
		}
		else {
			p++;
		}
	}

	*p = 0;

	return src;

}

inline
const char *GetEngWord(const char *query, int &len_eng, int &num_eng_word) {

	int cur_num_eng_word = 0;
	int cur_len_eng = 0;
	len_eng = 0;

	const char *p = query;
	while (*p) {
		if (*p == ' ') {
			
			len_eng = cur_len_eng;
			cur_len_eng++;
			p++;
			cur_num_eng_word++;
			if (cur_num_eng_word >= num_eng_word) {
				break;
			}
			
		}
		else if (*p >= 'a' && *p <= 'z') {
			cur_len_eng++;
			p++;
		}
		else {
			break;
		}
	}

	num_eng_word = cur_num_eng_word;
	if (0 == len_eng) {
		return NULL;
	}

	return query;
	
}
inline
int deleteSpace(std::string& line)
{
	if(line.length() < 1)
		return 0;

	int loc;
	while((loc = line.find(" ")) != -1)
	{
		line.replace(loc,1,"");
	}
	return 0;
}
inline
int deleteStr(std::string& line, const char* str)
{
	if(line.length() < 1)
		return 0;

	int loc;
	while((loc = line.find(str)) != -1)
	{
		line.replace(loc,strlen(str),"");
	}
	return 0;
}
//
inline
std::string toString(int32_t& num)
{
		std::stringstream os;
		os << num;
		std::string out;
		os >> out;

		return out;
}
inline
std::string double2String(double& num)
{
	std::stringstream os;
		os << num;
		std::string out;
		os >> out;

		return out;
}

//
inline
double toDouble(std::string& str)
{
	std::stringstream os;
		os << str;
		double out;
		os >> out;

		return out;
}
//
inline
int toInt(std::string& str)
{
	std::stringstream os;
		os << str;
		int out;
		os >> out;

		return out;
}
inline
int all_substr(std::vector<std::string> segment, std::vector<std::string>& all_sub)
{
	std::string sub;
	if(segment.size() < 1)
		return 0;
	int size = segment.size();
	int K;
	for(int i = 0; i < size; i++)
	{
		sub = "";
		K = (size <= (i + 5) ? size:(i + 5));
		for(int j = i; j < K; j++)
		{
			sub += segment[j];
			all_sub.push_back(sub);
		}
	}
	return 0;
}

inline
int all_substr(std::vector<std::string> segment, std::map<std::string, int32_t>& all_sub)
{
	std::string sub;
	if(segment.size() < 1)
		return 0;
	int size = segment.size();
	int K;
	for(int i = 0; i < size; i++)
	{
		sub = "";
		if(segment[i].length() == 0)
			continue;
		K = (size <= (i + 5) ? size:(i + 5));
		for(int j = i; j < K; j++)
		{
			if(segment[j] == "")
				continue;
			else
				sub += segment[j];
			if(sub.length() > 10)
				break;
			all_sub[sub] += 1;
		}
	}
	return 0;
}

inline
int all_suffix(std::vector<std::string> segment, std::vector<std::string>& all_suffix)
{
	all_suffix.clear();
	std::string sub;
	if(segment.size() < 1)
		return 0;
	int size = segment.size();
	int begin;
	if(size > 10)
	{
		begin = size - 10;
	}else
	{
		begin = 0;
	}
	for(int i = begin; i < size; i++)
	{
		sub = segment[i];
		for(int j = i + 1; j < size; j++)
		{
			sub += segment[j];
		}
		all_suffix.push_back(sub);
	}
	return 0;
}



};


#endif


