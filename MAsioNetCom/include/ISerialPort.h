#pragma once
#include <comdef.h>
#include "IComBase.h"

interface __declspec(uuid("114E3952-89A5-455E-8A36-A4215EAF635A")) ISerialPort : public IUnknown
{
	//
	// ����һ���¶���
	//
	virtual ISerialPort* __stdcall CreateNewObj() = 0;
	virtual void __stdcall ResizeBuffer(__int64 size) = 0;

	//
	// ��ί�к���
	//
	virtual void __stdcall BindMsgFun(CLIENTMSGFUN fun) = 0;
	virtual void __stdcall BindNetInfoFun(CLIENTMSGFUN fun) = 0;

	//
	// ������Ϣ�ڴ���com����������,���԰�ȫ���ͷ�ģʽӦ����com��������ͷ�
	//
	virtual void __stdcall FreeMemery(char* & ptr) = 0;

	//
	// �򿪴���
	// SerialName ������
	// baud_rate ������ 9600
	// isAsyni �Ƿ��첽 true �첽 false ͬ��
	// stopbit ֹͣλ 1 || 2
	// parity ��żУ��λ 0 Ϊ Ĭ�� >0 ż <0 ��
	// character_size ����λ Ĭ�� 8
	// flow_control �������� 0 ΪϵͳĬ�� >0 Ӳ�� <0 ���
	//
	virtual bool __stdcall Connect(const char* SerialName, unsigned baud_rate,
		bool isAsyni, int stopbit, int parity = 0, int character_size = 8, int flow_control = 0) = 0;

	//
	// ͬ�����ͺͽ���
	//
	virtual int __stdcall Send(const char* send, __int64 size) = 0;
	virtual int __stdcall Receive(char*& rec) = 0;

	//
	// ͬ������,��Ҫ����ͨ��ָ���ϵĲ���
	//
	virtual int __stdcall Write(const char* sendmsg, size_t size) = 0;
	virtual int __stdcall Read(char*& ch) = 0;

	//
	// ����ʹ���첽����
	//
	virtual void __stdcall PostSend(const char* sendmsg, __int64 size) = 0;
	virtual void __stdcall PostReceive() = 0;

	//
	// ����Ƿ�����
	//
	virtual bool __stdcall IsConnected() = 0;
	virtual void __stdcall Close() = 0;
	virtual bool __stdcall IsOpen() = 0;

	virtual void __stdcall ShowConsole(bool isshow) = 0;
	virtual void __stdcall SetLoggerFile(const char* filename) = 0;
};

