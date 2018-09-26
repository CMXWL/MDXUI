

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution
// Copyright (C) 2017-2018 by Mengjin (sh06155@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <MString.h>

namespace DxUI{
	class MXml;
	using namespace mj;
	class MSTRING_API MSerialize
	{
	public:
		MSerialize();
		~MSerialize();

		//
		// �Զ��ķ�ʽ���ļ�
		//
		void ReadFile(const MString &filename);

		//
		// Ϊд�����ļ�
		//
		void WriteFile(const MString &filename);

		//
		// �ر��ļ���������һ���ļ�ʱ�ǵùرյ�ǰ�ļ�
		// ����д�ļ���������Щ���֮��ǵùر��ļ�
		// ��������ֻ�����ڴ�֮��
		// ��Ȼ�ڳ����˳�֮ʱҹ����øò���
		//
		void CloseFile();

		///
		/// \brief SaveFile
		/// ���ڶ�ȡ���ļ������޸ĵ����
		///
		void SaveFile();

		bool IsReadFile() const;

		virtual MString ToString() { return "MSerialize"; }


		//
		// ������д���ļ�
		// key xml �ļ���key���ڵ�֮����.�ָ�
		// value Ҫд��ֵ
		//
		template<class T>
		bool __stdcall PutValue(const MString& key, const std::vector<T>& values){
			return PutValues(key, values);
		}

		//
		// д�ļ��޷���������������,һ��Ϊ�ַ�,һ��Ϊ���Σ�һ��Ϊ������
		// ��������ͨ�����غ���������������
		//
		bool  __stdcall PutValue(const MString& key, const char* value);
		bool  __stdcall PutValues(const MString& key, const std::vector<char*>& values);

		bool  __stdcall PutValue(const MString& key, const std::string& value);
		bool  __stdcall PutValues(const MString& key, const std::vector<std::string>& values);

		bool  __stdcall PutValue(const MString& key, const std::wstring& value);
		bool  __stdcall PutValues(const MString& key, const std::vector<std::wstring>& values);

		bool  __stdcall PutValue(const MString& key, const MString& value);
		bool  __stdcall PutValues(const MString& key, const std::vector<MString>& values);

		bool  __stdcall PutValue(const MString& key, float value);
		bool  __stdcall PutValues(const MString& key, const std::vector<float>& values);

		bool  __stdcall PutValue(const MString& key, double value);
		bool  __stdcall PutValues(const MString& key, const std::vector<double>& values);

		bool  __stdcall PutValue(const MString& key, __int64 value);
		bool  __stdcall PutValues(const MString& key, const std::vector<__int64>& values);

		bool  __stdcall PutValue(const MString& key, __int32 value);
		bool  __stdcall PutValues(const MString& key, const std::vector<__int32>& values);

		bool  __stdcall PutValue(const MString& key, __int16 value);
		bool  __stdcall PutValues(const MString& key, const std::vector<__int16>& values);

		bool  __stdcall PutValue(const MString& key, bool value);
		bool  __stdcall PutValues(const MString& key, const std::vector<bool>& values);

		bool  __stdcall PutValue(const MString& key, unsigned __int64 value);
		bool  __stdcall PutValues(const MString& key, const std::vector<unsigned __int64>& values);

		bool  __stdcall PutValue(const MString& key, unsigned __int32 value);
		bool  __stdcall PutValues(const MString& key, const std::vector<unsigned __int32>& values);

		bool  __stdcall PutValue(const MString& key, unsigned __int16 value);
		bool  __stdcall PutValues(const MString& key, const std::vector<unsigned __int16>& values);

		//
		// ��ȡ�����޷�Ҳ�Ƕ�ȡ��������
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
		// ��ȡ��ǰxml�ļ�����·���ĸ�·��
		//
		MString GetParentPath();

		//
		// �����ļ���
		//
		void CreateFolder(const MString& path);


		//
		// xml �ļ��Ƿ����
		//
		bool XmlFileIsExist(const MString& fileName);

	private:
		MXml*    mXmlManager;
		MString  mXmlFile;
		bool    bIsRead;
	};
}

