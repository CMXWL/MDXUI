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

	class MSTRING_API MStringImpl : public StringRefrenceObj{
		friend class MString;
		friend class StringRef<MStringImpl>;


		CMemeryPool<wchar_t>*  mData;

		//
		// ������ͨ�ַ��� ��0��β
		//
		MStringImpl(const char* str = "");
		MStringImpl(const wchar_t* wchar);

		//
		// ʹ��һ��buffer����,���ڴ洢�ֽ���
		//
		MStringImpl(const wchar_t* buf, uint64 length);


		void init(const wchar_t* str);

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
		void append(const wchar_t* buf, uint64 size);
		wchar_t*& c_str();
        std::string w2c();

		void swap(MStringImpl& other);

		void erase(int beg, int end);
		const wchar_t* copy(int beg, int end);

		//
		// �����ַ���
		//
		uint64 find(const wchar_t* str);

		//
		// ��ָ��λ�ÿ�ʼ����
		//
		uint64 find(const wchar_t* str, uint64 start_pos);
		uint64 find_last(const wchar_t* str);
		uint64 find_first(const wchar_t* str);
		uint64 find_nth(const wchar_t* str, uint64 index);
		uint64 find_count(const wchar_t* str);

		void   insert(uint64 pos, const wchar_t* value);

		//
		// �滻��һ�γ��ֵ�
		//
		void replace_first(const wchar_t* replaced, const wchar_t* value);
		void replace_all(const wchar_t* replaced, const wchar_t* value);
		void replace_nth(const wchar_t* replaced, const wchar_t* value, uint64 index);
		void replace_last(const wchar_t* replaced, const wchar_t* value);

		//
		// �Ƚϲ���
		//
		bool end_with(const wchar_t* str);
		bool iend_with(const wchar_t* str);
		bool start_with(const wchar_t* str);
		bool istart_with(const wchar_t* str);

		//
		// ��Сдת������
		//
		void To_upper();
		void To_lower();

		//
		// ת��Ϊutf8�����ַ���
		//
		std::string to_utf8();

		//
		// ����ת��
		//
		static std::wstring utf8_2_gbk(const char* uft8str);
	};
}

