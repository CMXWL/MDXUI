#pragma once

#if defined(_MSC_VER) && (_MSC_VER > 1300)
#include <functional>
#endif

static long sComponents = 0; // ��������õĴ���
static long sLockCounts = 0;

#ifdef _DEBUG
const char g_szFriendlyName[] = "MengJin COM Debug, AsioNetCom";
const char g_szVerIndProgID[] = "MengJin Debug.AsioNetCom";
const char g_szProgID[] = "MengJin AsioNetCom Debug.AsioNetCom.1";
#else
const char g_szFriendlyName[] = "MengJin COM Release, AsioNetCom";
const char g_szVerIndProgID[] = "MengJin Release.AsioNetCom";
const char g_szProgID[] = "MengJin  AsioNetCom Release.AsioNetCom.1";
#endif

#ifdef MAXBUFFERSIZE
#undef MAXBUFFERSIZE
#define MAXBUFFERSIZE 8192000   //Ĭ��bufferΪ8M
#else
#define MAXBUFFERSIZE 8192000   //Ĭ��bufferΪ8M
#endif

#if defined(_MSC_VER) && (_MSC_VER > 1300)
typedef std::function<void(const char*, __int64, const char*)>  SERVICEMSFFUN;  // ����˴���������Ϣ�ĺ�������
typedef std::function<void(const char*, const char*)>			NETINFOFUN;		  // ��ʾ����״̬��Ϣ
typedef std::function<void(const char*, __int64)>				CLIENTMSGFUN;	// �ͻ��˺ʹ��ڴ�����Ϣ�ĺ�������
#else
typedef void(*SERVICEMSFFUN)(const char*, __int64, const char*);  // ����˴���������Ϣ�ĺ�������
typedef void(*NETINFOFUN)(const char*, const char*);		  // ��ʾ����״̬��Ϣ
typedef void(*CLIENTMSGFUN)(const char*, __int64);	// �ͻ��˺ʹ��ڴ�����Ϣ�ĺ�������
#endif
