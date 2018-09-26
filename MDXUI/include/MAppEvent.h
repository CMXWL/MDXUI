

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution
// Copyright (C) 2017-2018 by Mengjin (sh06155@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include "DxConfig.h"
#include "MTreeEvent.h"


//
// ��Event����ֻ�ᴦ��������Frame�˵����¼���������Ƶ�ʱ��û�п��ǵ�̫�ർ��������չ���ֱ����Щ��Ť
//


class MAppManager;
class MAppCreateWindow;



//
// �¼������࣬������˵��͵����¼�
//
class DXUI_API MAppEvent :public MTreeEvent
{
public:

	///
	/// ���ص������������Ϣ,�����Ҽ������Ļ�������������Ч,�������������ΪĬ�ϲ���
	/// ��һ�����������ݵ��ǵ������ֵ�item��ȫ·��
	/// �ڶ�����������ʾ��������˫�������Ҽ�
	/// 1------>����
	/// 2------>˫��
	/// 3------>�Ҽ�
	/// ��������������е���Ϣ,ֻ��Ҫ��hook�Ĺؼ�����all��ͷ����
	///
	typedef std::function<void(const MString&, int, const DxUI::DxPointI&)> TREEHOOKFUN;
	typedef std::function<void()> EventFunType;

	explicit MAppEvent();
	virtual ~MAppEvent();

	void BindAppManager(MAppManager* Manager);


	
	//
	//  ��ȡ��Ӧ�ĺ���
	//
	EventFunType GetEventFun(const std::string& funName);


	///
	/// \brief InstallCommEventFun
	/// \param CommName
	/// \param fun
	/// �󶨹���������һЩ����
	/// ��HAppManager  InstallCommEvent HAppCommEvent ֮��
	/// ��Ĭ��ע���� �½� �� ���Ϊ���������е�������Ϣ�ĺ���
	///
	void InstallCommEventFun(const MString& CommName, const MAny& fun);

	///
	/// \brief InstallEventFun
	/// \param funName �¼���Ӧ����������
	/// \param fun �¼���Ӧ�����ĺ���ָ����ߺ�������
	/// EventFunType Ϊ void(void)
	/// ֻҪ��������͵ĺ����ȿ������ڸú���
	/// funName Ϊlua�ļ������ƶ����¼�������
	///
	void InstallEventFun(const mj::MString& funName, EventFunType fun);

	///
	/// \brief InstallEventFuns
	/// \param funs ע��һ�麯��
	///
	void InstallEventFuns(const std::map<mj::MString, EventFunType>& funs);





	///
	/// \brief SetTreeHookFun
	/// \param HookInfo ��Ҫ�����ص���Ϣ��ֻҪ�����иùؼ�����Ϣ��item���ᱻ����
	/// \param fun ��Ӧ����
	/// �����Ҫȡ�����أ����ڶ�����������Ϊnullptr ����
	///
	void SetTreeHookFun(const MString& HookInfo, TREEHOOKFUN fun);



	///
	/// \brief ClearHookInfo
	/// ���hook��Ϣ
	/// ʹ�������ص���Ϣͳͳ��Ч
	///
	void ClearHookInfo();


	///
	/// \brief OpenProject
	/// \param ProjName
	/// \return
	/// ��ָ������
	///
	virtual bool OpenProject(const MString& ProjName);

	//
	// ��Ӧ�˵�����¼�
	//

	virtual void onNew();
	virtual void onNewProject();
	virtual void onOpen();
	virtual void onSave();
	virtual void onSaveAs();
	virtual void onSaveAll();
	virtual void onClose();
	virtual void onCloseAll();
	virtual void onExit();

	virtual void onSysOption();
	virtual void onSwitchLG();


	virtual void onAbout();
	virtual void onManual();

	virtual void onRecoverSet();
	virtual void onStart();
	virtual void onPurse();
	virtual void onStop();

	virtual void OnBindProjectType(unsigned index);

	//----------------------------------
	// ��ͨ�ĳ�Ա����
	//----------------------------------
public:
	///
	/// \brief ClickedItemStrID
	/// \return
	/// ��ȡ�������������Ϣ��strid
	/// ������ǰ����������Ч
	///
	mj::MString ClickedItemStrID();



	//
	// ��������Ӧ���������¼�,���Ƽ���д����Ϊ�˴����õ���Hook�����������дû����ý���Hook
	//
private:
	///
	/// \brief Clicked
	/// \param iteminfo  ��������Strid
	/// \param size ����
	/// ������굥�����������¼�
	///
	virtual void Clicked(const char* iteminfo, __int64 size);

	///
	/// \brief DoubleClicked
	/// \param iteminfo
	/// \param size
	/// �������˫�����������¼�
	///
	virtual void DoubleClicked(const char* iteminfo, __int64 size);

	///
	/// \brief RightClicked
	/// \param iteminfo
	/// \param size
	/// \param pos λ�ã����ڵ���pop�˵�
	/// ���������Ҽ��¼�
	///
	virtual void RightClicked(const char* iteminfo, __int64 size, const DxUI::DxPointI& pos);

protected:
	mj::MString				mClickedItem;

	//
	// Hook ����
	//
	std::map<MString, TREEHOOKFUN> mTreeHookFuns;

	//
	// �����ⲿ�¼�����
	//
	std::map<MString, MAny>  mCommEventFun;

	MString                 mRecoderProjectPath;

	MAppCreateWindow*		p_CreateForm{ nullptr };

protected:
	std::map<std::string, EventFunType> mEventFun;
};



#define HADDMETHON(className,MethodName) \
	mEventFun[#MethodName] = std::bind(&className::MethodName, this);

#define HREMOVEMETHON(MethodName) \
	mEventFun[#MethodName] = nullptr;

