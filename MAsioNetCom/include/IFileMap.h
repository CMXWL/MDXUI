#pragma once
#include <comdef.h>

//
// �ļ��ڴ�ӳ��
//
interface __declspec(uuid("11B3F921-7465-447B-9590-5CD56BAAC6C4")) IFileMap : public IUnknown
{
	//
	// ����һ���¶���
	//
	virtual IFileMap* __stdcall CreateNewObj() = 0;

	//
	// ����Ҫ��ӳ����ļ�
	//
	virtual bool __stdcall OpenFile(const char* filename,__int64 filesize = 0ll) = 0;

	//
	// ӳ��һ���ڴ����
	//
	virtual bool __stdcall Map(char*& mem,__int64 __start = 0ll,__int64 size = 0ll) = 0;

	//
	// �ر�ӳ��
	//
	virtual void __stdcall UnMap() = 0;

	//
	// ��ѯ�ļ��Ƿ񱻴�
	//
	virtual bool __stdcall IsOpen() = 0;
};
