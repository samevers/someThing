//ʵ����һ������vector�Ĺ�ϣ
//�ŵ㣺�൱��map ����ÿ���ڵ��е�ָ�룬�����˿ռ��ʹ������ ��hash�� ÿ��Ͱ��vector���ڴ��������� �ṩ�˲�ѯʱ��
//ʹ�÷�Χ�� ����3��ʽ�ĳ��� 1. ��������  2. ����  3. ����������ݽ��в�ѯ�� �������޸�
//author�� garysong  2009-06-22 
//vertion��2.0�� ��Ҫ�ṹ���д��� char *word; 
//change�� 1.2 garysong  2009-09-10 ���Ӹ���word����find�Ĺ��ܣ� ֧��HASH_BASIC ����
//change:  2.0 garysong  2009-10-27 ��ѯ���䳤�� ���ǵ���cache��������Ͳ�ѯ�ٶ�

#ifndef __HASHVECTOR_ENHANCED_H
#define __HASHVECTOR_ENHANCED_H

#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>


//using namespace std;

/*
NODETYPE��Ҫ��
1. ���Ӷ�HASH_BASIC���ͻ��� Ҳ֧��key�ķ��ͻ���
2. Ҫ����붨�� unsigned int word_offset; ��ʾһ���ʵ�ƫ��
*/

template <typename NODETYPE, unsigned int HASH_BASIC=11111>
class CHashVector_Enhanced {

public:

CHashVector_Enhanced() {
	m_wordsBuf = NULL;
	m_wordsBufSize = 0;
}

~CHashVector_Enhanced() {
	if (NULL != m_wordsBuf) {
		delete[] m_wordsBuf;
		m_wordsBuf = NULL;
	}
}

/*���һ���ʵ�hash*/
unsigned int GetHashValue(const char *str) {
	unsigned index=0;
	while(*str) {
		index^=((index<<5) + (index>>2) + *str++);
	}

	return index%HASH_BASIC;
}

/*�ȽϺ���*/
bool Compare(NODETYPE &t1, NODETYPE &t2) {
	return strcmp(m_wordsBuf+t1.word_offset, m_wordsBuf+t2.word_offset) < 0;
}

/*���Ԫ�أ� ԭword���Ϊ��־����vect�е�ƫ����*/
bool AddItem(NODETYPE & item, const char *word) {
	//����item��wordָ��
	item.word_offset = m_charVect.size();
	const char *p = word;
	while (*p) {
		m_charVect.push_back(*p++);
	}
	m_charVect.push_back('\0');
	unsigned int hashValue = GetHashValue(word);
	data[hashValue].push_back(item);
	return true;
}


/*Ԫ������ ������ʵ���ڲ�ת���Ĺ���*/
/*bool Sort() {
	for (int i = 0; i < HASH_BASIC; i++) {
		vector<NODETYPE> &nodeVect = data[i];
	    sort(nodeVect.begin(), nodeVect.end(), (func)Compare);
	}
	return true;
}*/

bool Wap(NODETYPE &node1, NODETYPE &node2) {
	NODETYPE tmp;
	tmp = node1;
	node1 = node2;
	node2 = tmp;
	
	return true;
}

int Partition(std::vector<NODETYPE> &vect, int left, int right) {
	int key = left;
	const char *pchKeyValue = m_wordsBuf+vect[key].word_offset;
	
	//������������� ֻ������Ԫ�أ� ��һ��Ԫ�ش��ڵڶ���Ԫ��
	if (right == left+1) {
		if(strcmp(pchKeyValue, m_wordsBuf+vect[right].word_offset) > 0) {
			Wap(vect[key], vect[right]);
		}

		return right;
	}
	
	
	left++;
    while (left < right) {
		while (left < right && strcmp(m_wordsBuf+vect[left].word_offset, pchKeyValue) < 0) 
			left++;
		while (left <= right && right > key && strcmp(m_wordsBuf+vect[right].word_offset, pchKeyValue) >= 0) 
			right--;
		if (left < right) {
			Wap(vect[left], vect[right]);
			left++;
			right--;
		}
	}
    
	//������ȵ���������� ��Ҫ����
	if (right == left && strcmp(m_wordsBuf+vect[right].word_offset, pchKeyValue) >= 0) {
		right--;
	}
    
	
	if (right == key) {
		return right;
	}
	
	Wap(vect[key], vect[right]);
	
	return right;
}

void QSort(std::vector<NODETYPE> &vect, int left, int right) {
	if (left < right) {
		int key = Partition(vect, left, right);
		QSort(vect, left, key-1);
		QSort(vect, key+1, right);
	}
}
bool Sort() {
	if (NULL != m_wordsBuf) {
		delete[] m_wordsBuf;
	}
	m_wordsBuf = new char[m_charVect.size()];
	memcpy(m_wordsBuf, &m_charVect[0], m_charVect.size());
	for (unsigned int i = 0; i < HASH_BASIC; i++) {
		
		std::vector<NODETYPE> &nodeVect = data[i];
	    QSort(nodeVect, 0, nodeVect.size()-1);
	}

   // delete[] m_wordsBuf;
	//m_wordsBuf = NULL;
	return true;
}


/*����Ԫ��*/
NODETYPE *Find(const char *word) {
	unsigned int hashValue = GetHashValue(word);
	std::vector<NODETYPE> &vect = data[hashValue];
	int left = 0;
	int right = vect.size()-1;
    int mid = 0;
	int compareRet;


    
	//for (int i = 0; i <= right; i++) {
	//	fprintf(stdout, "%s\n", m_wordsBuf+vect[i].word_offset);
	//}
	
	while (right >= left) {
		mid = (left+right)/2;
		compareRet = strcmp(word, m_wordsBuf+vect[mid].word_offset);
		if (compareRet == 0) {
			return &(vect[mid]);
		}
		else if (compareRet > 0) {
			left = mid+1;
		}
		else {
			right = mid-1;
		}
	}

	return NULL;
}


/*д���ļ�*/
bool WriteFile(FILE *fp) {
	if (!fp) {
		return false;
	}

	//д��wordsBuf
	m_wordsBufSize = m_charVect.size();
	fwrite(&m_wordsBufSize, sizeof(m_wordsBufSize), 1, fp);

	//Ϊ���cache�����е���
	if (NULL != m_wordsBuf) {
		delete[] m_wordsBuf;
	}
	m_wordsBuf = new char[m_wordsBufSize];
	if (NULL == m_wordsBuf) {
		fprintf(stderr, "alloc m_wordsBuf is error!\n");
		return false;
	}
	char *pWord = m_wordsBuf;
	for (unsigned int i = 0; i < HASH_BASIC; i++) {
		std::vector<NODETYPE> &vect = data[i];
		for (typename std::vector<NODETYPE>::iterator itr = vect.begin(); itr != vect.end(); ++itr) {
			unsigned int word_offset = itr->word_offset;
			itr->word_offset = (unsigned int)(pWord-m_wordsBuf);
			while (m_charVect[word_offset]) {
				*pWord++ = m_charVect[word_offset++];
			}
			*pWord++ = '\0';
		}
	}
    //int writeRet = fwrite(&m_charVect[0], sizeof(char), m_wordsBufSize, fp);
	uint64_t writeRet = fwrite(m_wordsBuf, sizeof(char), m_wordsBufSize, fp);
	if (uint64_t(writeRet) != m_wordsBufSize) {
		fprintf(stderr, "error in fwrite! writeRet = %ld, m_wordsBufSize = %ld\n", writeRet, m_wordsBufSize);
		return false;
	}
	fprintf(stdout, "wordsBufSize = %d\n",  m_wordsBufSize);
	
	//д��HashVector��ṹ
	unsigned int hashSize = HASH_BASIC;
	fprintf(stdout, "hash_size = %u\n",  hashSize);
	fwrite(&hashSize, sizeof(unsigned int), 1, fp);
	for (unsigned int i = 0; i < HASH_BASIC; i++) {
		fwrite(&i, sizeof(unsigned int), 1, fp);
		std::vector<NODETYPE> &vect = data[i];
		unsigned int vectSize = vect.size();
		fwrite(&vectSize, sizeof(unsigned int), 1, fp);
		if (vectSize > 0) {
			fwrite(&vect[0], sizeof(NODETYPE), vectSize, fp);
		}
	}

	delete[]  m_wordsBuf;
	m_wordsBuf = NULL;
	return true;
}

/*���ļ��ж���*/
bool ReadInFile(FILE *fp) {
	if (!fp) {
		return false;
	}
	fread(&m_wordsBufSize, sizeof(m_wordsBufSize), 1, fp);
	if (NULL != m_wordsBuf) {
		delete[] m_wordsBuf;
		m_wordsBuf = NULL;
	}
	m_wordsBuf = new char[m_wordsBufSize];
	if (NULL == m_wordsBuf) {
		fprintf(stderr, "alloc m_wordsBuf error!\n");
		return false;
	}
	uint64_t readRet = fread(m_wordsBuf, sizeof(char), m_wordsBufSize, fp);
	if (uint64_t(readRet) != m_wordsBufSize) {
		fprintf(stderr, "error! read m_wordsBuf error! readRet = %ld    m_wordsBufSize = %ld\n", readRet, m_wordsBufSize);
		return false;
	}

    unsigned int hashSize;
	if (fread(&hashSize, sizeof(unsigned int), 1, fp) != 1) {
		fprintf(stderr, "error! error from load hashSize!\n");
		return false;
	}
	
	//�������hash basic��һ�£� ��ʧ��
	if (hashSize != HASH_BASIC) {
		fprintf(stderr, "error! the hash size [%d] != HASH_BASIC [%d]!\n", hashSize, HASH_BASIC);
		return false;
	}

	for (unsigned int i = 0; i < hashSize; i++) {
		unsigned int index;
		fread(&index, sizeof(unsigned int), 1, fp);
		std::vector<NODETYPE> &vect = data[index];
		vect.clear();
		unsigned int vectSize;
		fread(&vectSize, sizeof(unsigned int), 1, fp);
		if (vectSize > 0) {
			vect.resize(vectSize);
			vect.assign(vectSize, NODETYPE());
			fread(&vect[0], sizeof(NODETYPE), vectSize, fp);
		}
	}

	return true;
}

/*���*/
bool Clear() {
	for (unsigned int i = 0; i < HASH_BASIC; i++) {
		data[i].clear();
	}

	m_charVect.clear();
	if (NULL != m_wordsBuf) {
		delete[] m_wordsBuf;
		m_wordsBuf = NULL;
	}

	return true;
}

public:
	std::vector<NODETYPE> data[HASH_BASIC];

private:
	std::vector<char>   m_charVect;
    char *m_wordsBuf;        //���ڴ洢��ѯ�ʵ�buf
	uint64_t m_wordsBufSize; 
};

#endif


