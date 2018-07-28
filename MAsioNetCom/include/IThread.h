#pragma once
#include "IAsioInterface.h"

//
// ���ʹ��C++11��ôʹ�ú�������,����ʹ�ú���ָ��
//
#if defined(_MSC_VER) && (_MSC_VER > 1300)
typedef std::function<void()> THREADFUNTYPE;
#else
typedef void(*THREADFUNTYPE)()
#endif

interface __declspec(uuid("B39FC0B4-ED61-4EB5-8670-AB42AB10FA4D")) IThread : public IUnknown
{
	virtual unsigned  __stdcall AddFun(THREADFUNTYPE fun, unsigned num = 1) = 0;
	virtual void  __stdcall Run(unsigned thread = -1) = 0;
	virtual void  __stdcall Detach(unsigned thread = -1) = 0;
	virtual void  __stdcall Join(unsigned thread = -1) = 0;
	virtual void  __stdcall SetConditionVar(void * threadconditionvar, unsigned thread = -1) = 0;
	virtual void  __stdcall SetControlVar(bool* IsExit, unsigned thread = -1) = 0;
	virtual void  __stdcall Sleep(unsigned msec) = 0;
	virtual unsigned __stdcall CurrentThreadID() = 0;
};

//
// Ĭ���ṩ�Ĵ����̹߳���Ĺ�������
//
inline IThread* CreateThreadPtr(){
	IThread* pThread = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IThread),
		(void**)&pThread
		);
	return pThread;
}

//
// ������̬�߳�ָ��
//
inline IThread* CreateStaticThreadPtr(){
	static IThread* pThread = NULL;
	if (pThread)
		return pThread;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IThread),
		(void**)&pThread
		);
	return pThread;
}