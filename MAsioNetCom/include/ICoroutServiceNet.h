#pragma once
#include <comdef.h>
#include "IComBase.h"
interface __declspec(uuid("881ABAC6-4A42-4B4F-A34F-30709C929857")) ICoroutServiceNet : public IUnknown
{
	//
	// ����buffer��С
	//
	virtual void __stdcall ResizeBuffer(__int64 size) = 0;

	//
	// ���ü����˿�
	//
	virtual void __stdcall SetListenPort(unsigned port) = 0;
	virtual void __stdcall StartListen() = 0;

	//
	// ͬ������
	//
	virtual int __stdcall Send(const char* send, __int64 size, const char* strid) = 0;
	virtual int __stdcall Read(char*& rec, const char* strid) = 0;

	//
	// ������Ϣ�ڴ���com����������,���԰�ȫ���ͷ�ģʽӦ����com��������ͷ�
	//
	virtual void __stdcall FreeMemery(char* & ptr) = 0;

	//
	// �첽����
	//
	virtual void __stdcall PostRecive(const char* strid) = 0;
	virtual void __stdcall PostSend(const char* str, __int64 size, const char* strid) = 0;
	virtual void __stdcall PostToAll(const char* send, __int64 size) = 0;

	//
	// �߳���ִ��Э��
	//
	virtual void __stdcall Run() = 0;

	//
	// ���߳���ִ��Э��
	//
	virtual void __stdcall MainThreadRun() = 0;

	virtual void __stdcall BindNetInfoFun(NETINFOFUN fun) = 0;
	virtual void __stdcall BindMsgFun(SERVICEMSFFUN fun) = 0;

	//
	// ͨ���ַ���id��ѯ�ͻ�ip�Ͷ˿�
	//
	virtual void __stdcall QueryIPAndPort(const char* clientstrid, char*& ip, unsigned& port) = 0;

	//
	// �߳�ĳ���ͻ�
	//
	virtual void __stdcall DeleteClient(const char* clientstrid) = 0;

	//
	// ��ѯ�������Ƿ��пͻ�����
	//
	virtual unsigned __stdcall QueryClientNum() = 0;

	//
	// ��ѯĳ���ͻ��Ƿ����
	//
	virtual bool __stdcall ClientIsExist(const char* clientstrid) = 0;
};

