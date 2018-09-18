

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once
#include "MString.h"
#include <vector>

using mj::MString;
class MXMLParse;


namespace DxUI{

	//
	// ��д xml �ļ�
	//
	class MSTRING_API MXml
	{
	public:
		MXml();
		~MXml();

		//
		// ���ļ����ж�д
		//
		void    ReadFile(const MString& filename);
		void    WriteFile(const MString& filename);


		//
		// ������д���ļ�
		//
		bool  __stdcall PutValue(const MString& key, const char* value);
		bool  __stdcall PutValue(const MString& key, const std::vector<char*>& values);

		bool  __stdcall PutValue(const MString& key, const std::string& value);
		bool  __stdcall PutValue(const MString& key, const std::vector<std::string>& values);

		bool  __stdcall PutValue(const MString& key, const std::wstring& value);
		bool  __stdcall PutValue(const MString& key, const std::vector<std::wstring>& values);

		bool  __stdcall PutValue(const MString& key, const MString& value);
		bool  __stdcall PutValue(const MString& key, const std::vector<MString>& values);

		bool  __stdcall PutValue(const MString& key, float value);
		bool  __stdcall PutValue(const MString& key, const std::vector<float>& values);

		bool  __stdcall PutValue(const MString& key, double value);
		bool  __stdcall PutValue(const MString& key, const std::vector<double>& values);

		bool  __stdcall PutValue(const MString& key, __int64 value);
		bool  __stdcall PutValue(const MString& key, const std::vector<__int64>& values);

		bool  __stdcall PutValue(const MString& key, __int32 value);
		bool  __stdcall PutValue(const MString& key, const std::vector<__int32>& values);

		bool  __stdcall PutValue(const MString& key, __int16 value);
		bool  __stdcall PutValue(const MString& key, const std::vector<__int16>& values);

		bool  __stdcall PutValue(const MString& key, bool value);
		bool  __stdcall PutValue(const MString& key, const std::vector<bool>& values);

		bool  __stdcall PutValue(const MString& key, unsigned __int64 value);
		bool  __stdcall PutValue(const MString& key, const std::vector<unsigned __int64>& values);

		bool  __stdcall PutValue(const MString& key, unsigned __int32 value);
		bool  __stdcall PutValue(const MString& key, const std::vector<unsigned __int32>& values);

		bool  __stdcall PutValue(const MString& key, unsigned __int16 value);
		bool  __stdcall PutValue(const MString& key, const std::vector<unsigned __int16>& values);



		//
		// ��ȡ����
		//
		std::string __stdcall GetValue(const MString& key, const char* defaultvalue);
		std::vector<std::string> __stdcall GetValues(const MString& key, const char* defaultvalue);

		std::string __stdcall GetValue(const MString& key, const std::string& defaultvalue);
		std::vector<std::string> __stdcall GetValues(const MString& key, const std::string& defaultvalue);

		std::wstring __stdcall GetValue(const MString& key, const std::wstring& defaultvalue);
		std::vector<std::wstring> __stdcall GetValues(const MString& key, const std::wstring& defaultvalue);

		MString __stdcall GetValue(const MString& key, const MString& defaultvalue);
		std::vector<MString> __stdcall GetValues(const MString& key, const MString& defaultvalue);

		float __stdcall GetValue(const MString& key, float defaultvalue);
		std::vector<float> __stdcall GetValues(const MString& key, float defaultvalue);

		double __stdcall GetValue(const MString& key, double defaultvalue);
		std::vector<double> __stdcall GetValues(const MString& key, double defaultvalue);

		__int16 __stdcall GetValue(const MString& key, __int16 defaultvalue);
		std::vector<__int16> __stdcall GetValues(const MString& key, __int16 defaultvalue);

		__int32 __stdcall GetValue(const MString& key, __int32 defaultvalue);
		std::vector<__int32> __stdcall GetValues(const MString& key, __int32 defaultvalue);

		__int64 __stdcall GetValue(const MString& key, __int64 defaultvalue);
		std::vector<__int64> __stdcall GetValues(const MString& key, __int64 defaultvalue);

		bool __stdcall GetValue(const MString& key, bool defaultvalue);
		std::vector<bool> __stdcall GetValues(const MString& key, bool defaultvalue);

		unsigned __int16 __stdcall GetValue(const MString& key, unsigned __int16 defaultvalue);
		std::vector<unsigned __int16> __stdcall GetValues(const MString& key, unsigned __int16 defaultvalue);

		unsigned __int32 __stdcall GetValue(const MString& key, unsigned __int32 defaultvalue);
		std::vector<unsigned __int32> __stdcall GetValues(const MString& key, unsigned __int32 defaultvalue);

		unsigned __int64 __stdcall GetValue(const MString& key, unsigned __int64 defaultvalue);
		std::vector<unsigned __int64> __stdcall GetValues(const MString& key, unsigned __int64 defaultvalue);


		//
		// �ر��ļ�
		// ����д�ļ���˵���رվ��Ǳ���
		//
		void	CloseFile();

		//
		// ǿ�Ʊ�������Ƕ��ļ������޸ĺ�Ҳ���Խ��б���
		//
		void    SaveFile();
	private:
		MXMLParse* pXml{ nullptr };
	};

}

