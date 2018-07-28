#pragma once
#include <comdef.h>
#include <vector>
#include <string>
#include "IAsioInterface.h"
//
// ��������Ĵ�С
//
#ifdef IArraySize
#undef IArraySize
#endif
#define IArraySize(N) ARRAYSIZE(N)


//
// ԭ��ʹ�õ�ģ�壬������ֲ����������ʹ�������غ���
//
interface  __declspec(uuid("B7DF1995-4CDE-4D90-89A4-96D3474B9E1C")) IXml : public IUnknown
{
	//
	// ����һ���¶���
	//
	virtual IXml* __stdcall CreateNewObj() = 0;

	virtual bool  __stdcall ReadFile(const char* filename) = 0;
	virtual bool  __stdcall WriteBegin(const char* filename) = 0;

	//
	// д�ļ��޷���������������,һ��Ϊ�ַ�,һ��Ϊ���Σ�һ��Ϊ������
	// ��������ͨ�����غ���������������
	//
	virtual bool  __stdcall PutValue(const char* key, const char* value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<char*>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key, const std::string& value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<std::string>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key, float value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<float>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key, double value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<double>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key, __int64 value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<__int64>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key, __int32 value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<__int32>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key,  __int16 value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<__int16>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key, bool value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<bool>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key, unsigned __int64 value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<unsigned __int64>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key, unsigned __int32 value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<unsigned __int32>& values) = 0;

	virtual bool  __stdcall PutValue(const char* key, unsigned __int16 value) = 0;
	virtual bool  __stdcall PutValue(const char* key, const std::vector<unsigned __int16>& values) = 0;

	//
	// ��ȡ�����޷�Ҳ�Ƕ�ȡ��������
	//
	virtual char* __stdcall GetValue(const char* key, const char* defaultvalue) = 0;
	virtual std::vector<std::string> __stdcall GetValues(const char* key, const char* defaultvalue) = 0;

	virtual std::string __stdcall GetValue(const char* key, std::string defaultvalue) = 0;
	virtual std::vector<std::string> __stdcall GetValues(const char* key, std::string defaultvalue) = 0;

	virtual float __stdcall GetValue(const char* key, float defaultvalue) = 0;
	virtual std::vector<float> __stdcall GetValues(const char* key, float defaultvalue) = 0;

	virtual double __stdcall GetValue(const char* key, double defaultvalue) = 0;
	virtual std::vector<double> __stdcall GetValues(const char* key, double defaultvalue) = 0;

	virtual __int16 __stdcall GetValue(const char* key, __int16 defaultvalue) = 0;
	virtual std::vector<__int16> __stdcall GetValues(const char* key, __int16 defaultvalue) = 0;

	virtual __int32 __stdcall GetValue(const char* key, __int32 defaultvalue) = 0;
	virtual std::vector<__int32> __stdcall GetValues(const char* key, __int32 defaultvalue) = 0;

	virtual __int64 __stdcall GetValue(const char* key, __int64 defaultvalue) = 0;
	virtual std::vector<__int64> __stdcall GetValues(const char* key, __int64 defaultvalue) = 0;

	virtual bool __stdcall GetValue(const char* key, bool defaultvalue) = 0;
	virtual std::vector<bool> __stdcall GetValues(const char* key,  bool defaultvalue) = 0;

	virtual unsigned __int16 __stdcall GetValue(const char* key, unsigned __int16 defaultvalue) = 0;
	virtual std::vector<unsigned __int16> __stdcall GetValues(const char* key, unsigned __int16 defaultvalue) = 0;

	virtual unsigned __int32 __stdcall GetValue(const char* key, unsigned __int32 defaultvalue) = 0;
	virtual std::vector<unsigned __int32> __stdcall GetValues(const char* key, unsigned __int32 defaultvalue) = 0;

	virtual unsigned __int64 __stdcall GetValue(const char* key, unsigned __int64 defaultvalue) = 0;
	virtual std::vector<unsigned __int64> __stdcall GetValues(const char* key, unsigned __int64 defaultvalue) = 0;

	//
	// ���ļ�д���֮����Ҫ��������ĺ���
	//
	virtual void __stdcall	WriteEnd() = 0;

	//
	// ��ȡ�ļ����Լ����ڵ��ļ���,��Ϊ��Щ������ʱ���Ƚ�����
	//
	virtual std::string __stdcall GetFileName() = 0;
	virtual std::string __stdcall GetParentPath() = 0;
};

//
// Ĭ���ṩ�Ĵ���xml�������Ĺ�������
//
inline IXml* CreateXmlPtr(){
	IXml* pXml = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IXml),
		(void**)&pXml
		);
	return pXml;
}