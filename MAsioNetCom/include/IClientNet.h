#pragma once
#include <comdef.h>
#include "IComBase.h"
interface __declspec(uuid("6046C6DB-FD61-4F06-BF7B-D7E94BCFE79E")) IClientNet : public IUnknown
{
	//
	// ����һ���¶���
	//
	virtual IClientNet* __stdcall CreateNewObj() = 0;

	//
	// ���ý�����ʹ�õ�buffer��С
	//
	virtual void __stdcall ResizeBuffer(__int64 size) = 0;

	//
	// ����ip�˿��Լ��˳��߳�
	//
	virtual void __stdcall SetNetIP(const char* ip) = 0;
	virtual void __stdcall SetNetPort(unsigned port) = 0;
	virtual void __stdcall Exit() = 0;

	//
	// ����Ϣ�ص�����
	//
	virtual void __stdcall BindMsgFun(CLIENTMSGFUN  fun) = 0;
	virtual void __stdcall BindNetInfoFun(CLIENTMSGFUN fun) = 0;

	//
	// ������Ϣ�ڴ���com����������,���԰�ȫ���ͷ�ģʽӦ����com��������ͷ�
	//
	virtual void __stdcall FreeMemery(char* & ptr) = 0;

	//
	// �첽����
	//
	virtual void __stdcall PostConnect() = 0;
	virtual void __stdcall PostReceive() = 0;
	virtual void __stdcall PostSend(const char* send, __int64 size) = 0;

	//
	// ͬ������
	//
	virtual void __stdcall Connect() = 0;
	virtual __int64 __stdcall Send(const char* send, __int64 size, __int64 timeout = 5000) = 0;
	virtual __int64 __stdcall Recv(char*& str, __int64 timeout = 5000) = 0;

	//
	// �����ڹ�������Э��Ĳ���
	//
	virtual __int64 __stdcall Write(const char* cmd, __int64 size,__int64 timeout = 5000) = 0;
	virtual __int64 __stdcall Read(char*& result, __int64 timeout = 5000) = 0;

	//
	// �����߳�
	//
	virtual void __stdcall Run() = 0;

	//
	// ��ѯsocket��״̬������Ƿ�ʱ
	//
	virtual bool __stdcall Timeout() = 0;

	//
	// ����״̬
	//
	virtual bool __stdcall IsConnected() = 0;
	virtual void __stdcall Close() = 0;

	virtual void __stdcall ShowConsole(bool isshow) = 0;
	virtual void __stdcall SetLoggerFile(const char* filename) = 0;
};

