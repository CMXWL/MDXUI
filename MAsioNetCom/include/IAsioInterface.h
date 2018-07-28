#pragma once


#include <comdef.h>

//
// �����������ҪRelease�����Դ˴��ṩ����ָ���ѡ��
//
#include <memory>


//
// ���ID
//



#ifdef X64
#ifdef _DEBUG
// {4C99DE88-4492-4330-BB6A-DE19253EABDB}
__declspec(selectany) GUID ASIOCLSID =
{ 0x4c99de88, 0x4492, 0x4330, { 0xbb, 0x6a, 0xde, 0x19, 0x25, 0x3e, 0xab, 0xdb } };

#else

// {368EA519-CF02-4221-BA2F-AA90332F9BEF}
__declspec(selectany) GUID ASIOCLSID =
{ 0x368ea519, 0xcf02, 0x4221, { 0xba, 0x2f, 0xaa, 0x90, 0x33, 0x2f, 0x9b, 0xef } };

#endif
#else
#ifdef _DEBUG
// {FE623F09-3358-4284-BBD0-FDABACC6F506}
__declspec(selectany) GUID ASIOCLSID =
{ 0xfe623f09, 0x3358, 0x4284, { 0xbb, 0xd0, 0xfd, 0xab, 0xac, 0xc6, 0xf5, 0x6 } };

#else
__declspec(selectany) GUID ASIOCLSID =
{ 0xa469a2b, 0xca40, 0x4e93, { 0xa1, 0x5, 0x77, 0x61, 0x3d, 0x21, 0xb2, 0x2 } };
#endif
#endif

//
// �����⼸��ͷ�ļ�����
//

#include "IClientNet.h"
#include "ISerialPort.h"
#include "IServiceNet.h"
#include "IMLogger.h"

//
// ����һ�����ڲ�ʵ�ֲ�һ��
//
#include "ICoroutClientNet.h"
#include "ICoroutSerialPort.h"
#include "ICoroutServiceNet.h"

//
// ����UDP
//
#include "IUDPService.h"
#include "IUDPClient.h"

//
// ��ʱ��
//
#include "ITimer.h"

//
// �ļ��ڴ�ӳ��
//
#include "IFileMap.h"

class MINitCom{
public:
	MINitCom(){
		CoInitialize(nullptr);
	}
	~MINitCom(){
		CoUninitialize();
	}
};

//
// ����һ��������ʼ��com���
//
#ifndef INITCOM
#define INITCOM MINitCom __GlobInitCom__;
#endif


//
// Ԥ����һ��ɾ��com����ĺ���
//
template<class T>
inline void ReleaseCom(T* comptr){
    std::cout<<"Release COM Ptr"<<std::endl;
    if(comptr){
        comptr->Release();
    }
}

//
// �˴����������ü���,Ϊʲô�أ�
//
template<class T>
std::shared_ptr<T> SharedComPtr(T* __comptr){
    return std::shared_ptr<T>(__comptr,ReleaseCom<T>);
}

//
// ��Ϊ�õ����ٵĺ����󶨣�ֱ�������������ռ�ȽϷ���
//
using namespace std::placeholders;

//
// Ĭ���ṩ�Ĵ������������Ĺ�������
//
inline IServiceNet* CreateServiceNet(){
	IServiceNet* Serv = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IServiceNet),
		(void**)&Serv
		);
	return Serv;
}

//
// ����ʹ��Э��ʵ�ֵ����������
//
inline ICoroutServiceNet* CreateCoroutServiceNet(){
	ICoroutServiceNet* Serv = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(ICoroutServiceNet),
		(void**)&Serv
		);
	return Serv;
}

//
// Ĭ���ṩ�Ĵ����ͻ�������Ĺ�������
//

inline IClientNet*  CreateClientNet(){
	IClientNet* Client = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IClientNet),
		(void**)&Client
		);
	return Client;
}

//
// ����ʹ��Э��ʵ�ֵ�����ͻ���
//
inline ICoroutClientNet*  CreateCoroutClientNet(){
	ICoroutClientNet* Client = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(ICoroutClientNet),
		(void**)&Client
		);
	return Client;
}

//
// Ĭ���ṩ�Ĵ������ڵĹ�������
//
inline ISerialPort* CreateSerialPort(){
	ISerialPort* Serial = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(ISerialPort),
		(void**)&Serial
		);
	return Serial;
}

//
// ����Э��ʵ�ֵĴ���
//
inline ICoroutSerialPort* CreateCoroutSerialPort(){
	ICoroutSerialPort* Serial = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(ICoroutSerialPort),
		(void**)&Serial
		);
	return Serial;
}

//
// ����UDPService
//
inline IUDPService* CreateUDPService(){
	IUDPService* Serv = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IUDPService),
		(void**)&Serv
		);
	return Serv;
}

//
// ����UPPClient
//
inline IUDPClient* CreateUDPClient(){
	IUDPClient* Serv = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IUDPClient),
		(void**)&Serv
		);
	return Serv;
}

//
// Ĭ���ṩ�Ĵ�����־��¼�Ĺ�������
//
inline IMLogger* CreateLogger(){
	IMLogger* Logger = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IMLogger),
		(void**)&Logger
		);
	return Logger;
}

//
// ��ʱ���Ĺ�������
//
inline ITimer* CreateTimer(){
	ITimer* timeptr = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(ITimer),
		(void**)&timeptr
		);
	return timeptr;
}

//
// �ļ��ڴ�ӳ��Ĺ�������
//
inline IFileMap* CreateFileMap(){
	IFileMap* fileMap = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IFileMap),
		(void**)&fileMap
		);
	return fileMap;
}
