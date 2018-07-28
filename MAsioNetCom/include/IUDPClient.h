#pragma once
#include <comdef.h>
#include <functional>

interface __declspec(uuid("2D96038E-2523-43BF-BEA2-590FBE69B7DE")) IUDPClient : public IUnknown
{
	typedef std::function<void(const char*, __int64, const char*, unsigned __int16)> UDPSERVICEMSFFUN;
	typedef std::function<void(const char*, __int64, const char*, unsigned __int16)> UDPNETINFOFUN;

	//
	// ����һ���¶���
	//
	virtual IUDPClient* __stdcall CreateNewObj() = 0;

	//
	// ���ý�����ʹ�õ�buffer��С
	//
	virtual void __stdcall ResizeBuffer(__int64 size) = 0;

	//
	// ����Ϣ�ص�����
	//
	virtual void __stdcall BindNetInfoFun(UDPNETINFOFUN fun) = 0;
	virtual void __stdcall BindMsgFun(UDPSERVICEMSFFUN fun) = 0;

	//
	// ����һ�����Ͷ˿�
	//
	virtual void  __stdcall CreateSendPort(const char* strip, unsigned __int16 port, char*& outPort) = 0;

	//
	// �����Ƿ�Ϊ�첽����������첽�����Ļ����н������ݶ��ɻص����������Ϊͬ��,����ͬ���������ݣ�������Ȼ�����첽���ͺͽ�������
	//
	virtual void __stdcall SetOperatorMode(bool isAsyc) = 0;

	//
	// ����������һ��socket����ֻ��runһ��
	//
	virtual void __stdcall Run() = 0;


	//
	// ������Ϣ�ڴ���com����������,���԰�ȫ���ͷ�ģʽӦ����com��������ͷ�
	//
	virtual void __stdcall FreeMemery(char*& ptr) = 0;

	//
	// �첽���ͺͽ���
	//
	virtual void __stdcall PostSendTo(const char* msg, __int64 size, const char* sendport) = 0;
	virtual void __stdcall PostSendTo(const char* msg, __int64 size,
		const char* ip, unsigned __int16 port) = 0;

	//
	// �첽����
	//
	virtual void __stdcall PostReceive() = 0;

	//
	// ���ͺͽ���
	//
	virtual __int64 __stdcall SendTo(const char* send, __int64 size, const char* SendPort) = 0;
	virtual __int64 __stdcall RecvFrom(char*& str, char*& recvPort) = 0;

	//
	// ������Ϣ��ָ��ָ��ip�Ͷ˿���
	//
	virtual __int64 __stdcall SendTo(const char* send, __int64 size, const char* ip, unsigned short port) = 0;

	//
	// ��ѯ���յ����ݵ�ip�Ͷ˿�
	//
	virtual  void __stdcall QuereIpAndPort(const char* portstrid, char*& ip, unsigned __int16& port) = 0;

};

