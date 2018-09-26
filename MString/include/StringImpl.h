#pragma once
#include "StringRef.h"
#include <iostream>
//
// �ڴ����ǰ������
//
template<class T>
class CMemeryPool;


//
// ����ʵ����
//
namespace mj{
	//
	// ������
	//
    class  MStringImpl : public StringRefrenceObj{
		friend class MString;
		friend class StringRef<MStringImpl>;


		CMemeryPool<char>*  mData;

		//
		// ������ͨ�ַ��� ��0��β
		//
		MStringImpl(const char* str = "");
		MStringImpl(const wchar_t* wchar);

		//
		// ʹ��һ��buffer����,���ڴ洢�ֽ���
		//
		MStringImpl(char* buf, uint64 length);


		void init(const char* str);

		uint64 size();
		uint64 size() const;

		uint64 length();
		uint64 length() const;

		bool empty();
		void trim();
		void trim_left();
		void trim_right();

		bool operator==(const MStringImpl& other);
		bool operator!=(const MStringImpl& other);
		bool operator<(const MStringImpl& other);
		bool operator>(const MStringImpl& other);

		~MStringImpl();

		void clear();

		//
		// ׷����Ϣ
		//
		void append(const char* str);
		void append(const wchar_t* str);
        void append(char* buf,uint64 size);
		char*& c_str();
        const wchar_t *c2w();

		void swap(MStringImpl& other);

		void erase(int beg, int end);
		char* copy(int beg, int end);

		//
		// �����ַ���
		//
		uint64 find(const char* str);

		//
		// ��ָ��λ�ÿ�ʼ����
		//
		uint64 find(const char* str, uint64 start_pos);
		uint64 find_last(const char* str);
		uint64 find_first(const char* str);
		uint64 find_nth(const char* str, uint64 index);
		uint64 find_count(const char* str);

		//
		// �滻��һ�γ��ֵ�
		//
		void replace_first(const char* replaced, const char* value);
		void replace_all(const char* replaced, const char* value);
		void replace_nth(const char* replaced, const char* value, uint64 index);
		void replace_last(const char* replaced, const char* value);

		//
		// �Ƚϲ���
		//
		bool end_with(const char* str);
		bool iend_with(const char* str);
		bool start_with(const char* str);
		bool istart_with(const char* str);

		//
		// ��Сдת������
		//
		void To_upper();
		void To_lower();

		//
		// ת��Ϊutf8�����ַ���
		//
        const char *to_utf8();

		//
		// ����ת��
		//
        static const char* utf8_2_gbk(const char* uft8str);
	};
}

