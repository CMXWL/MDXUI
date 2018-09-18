
///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once


#include "DxConfig.h"
#include "MAppEvent.h"

//#include <IDealDataInterface.h>
//
// �����ģ���м��س����Ĺ�����Ϣ
// ��ģ�����ܹ���ȡ��Ӧ����
// HAppData  ģ�������
// HAppUI    ģ���UI
// HAppEvent ģ���¼�
//

class MAppData;
class MAppUI;
class MAppManager;
class IDealDataInterface;
class MAppEventHandle;

//
// ���ص������������Ϣ,�����Ҽ������Ļ�������������Ч,�������������ΪĬ�ϲ���
// ��һ�����������ݵ��ǵ������ֵ�item��ȫ·��
// �ڶ�����������ʾ��������˫�������Ҽ�
// 1------>����
// 2------>˫��
// 3------>�Ҽ�
//
//#ifndef TREEHOOKFUN
//typedef std::function<void(const MString&, int, const QPoint&)> TREEHOOKFUN;
//#endif

//
// ���е�ģ��ͨ��һ������������ģ���Instance
// ������Ϊ CreateInstance
// HAppInstance* ����ʵ��ָ��
// ����Ϊvoid
//

class MAppInstance;
typedef MAppInstance*(*MAppInstanceFun)();


class DXUI_API MAppInstance
{
public:
	MAppInstance(){}
	virtual ~MAppInstance(){}

	///
	/// \brief DestroyInstance
	///
	virtual void DestroyInstance(){}

	///
	/// \brief ToString
	/// \return
	/// ���ýӿ�
	///
	virtual MString ToString(){ return "MAppInstance"; }

	///
	/// \brief InitInstance
	/// \param pAppManager
	/// ��ʼ��һ��ģ��
	///
	virtual void InitInstance(MAppManager* pAppManager) = 0;

	///
	/// \brief AppData
	/// \return
	/// AppData��������
	///
	virtual MAppData*  AppData() const = 0;

	///
	/// \brief AppUI
	/// \return
	/// AppUI �Ĺ�������
	///
	virtual MAppUI*    AppUI() const = 0;

	///
	/// \brief AppEvent
	/// \return
	/// ģ���Ӧ���¼�������
	///
	virtual MAppEvent* AppEvent() const = 0;


	//
	/// \brief AppEventHandler
	/// \return
	/// ͨ���¼�����,Ҳ���Ǳ���,Ҳ����
	///
	virtual MAppEventHandle* AppEventHandler(){
		return nullptr;
	}


	///
	/// \brief AppDataDealer
	/// \return
	/// ���ݴ�����,Ҳ���Ǳ���,Ҳ����
	///
	virtual IDealDataInterface* AppDataDealer(){
		return nullptr;
	}


	///
	/// \brief MenuEventFun
	/// \return
	/// Instanceģ���ṩ�˵��¼���Ӧģ��
	/// Frame�õ��ú�����Ὣ�䰲װ��HAppEvent��
	/// ��Action�õ���ȷ����Ӧ
	///
	virtual std::map<MString, MAppEvent::EventFunType> MenuEventFun(){
		return std::map<MString, MAppEvent::EventFunType>();
	}

	///
	/// \brief NagHookFun
	/// \return
	/// ��ȡhook����,ֻ�������Լ�������Ȥ���¼�����
	///
	virtual std::map<MString, MAppEvent::TREEHOOKFUN> NagHookFun(){
		return std::map<MString, MAppEvent::TREEHOOKFUN>();
	}


	///
	/// \brief IsMultProject
	/// \return
	/// �Ƿ������ڶ๤��,Ĭ�Ͻ�Ϊ������ģʽ
	///
	virtual bool IsMultProject(){
		return false;
	}

	///
	/// \brief InstallInstanceAction
	/// װ��instance���еĲ���
	/// װ�غ�ж�ض���ͨ�� HAppManager �� RegisterEventFun �����
	/// �����װ�� FrameUI �� FrameData ʹ�� RegisterFrameData �� RegisterFrameUI �����
	/// ����FrameUI �� FrameData ������ InitInstance ��ע�ἴ��,�������
	///
	virtual void InstallInstanceAction(MAppManager* pAppManager){}

	///
	/// \brief UnInstallInstanceAction
	/// ж��instance���еĲ���
	/// ����ж����˵ HAppManager �� RegisterEventFun �ĵ���������ʹ��nullptr
	/// �����ж�� FrameUI �� FrameData ʹ�� UnRegisterFrameData �� UnRegisterFrameUI �����
	///
	virtual void UnInstallInstanceAction(MAppManager* pAppManager){}

};

