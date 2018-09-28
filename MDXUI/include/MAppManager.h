

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
#include <HVector.h>
#include <memory>
#include <unordered_map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include "MProjectType.h"
#include <unordered_map>
#include "MAppDataUnit.h"
#include "MAppWindow.h"
#include <MSingleton.h>
#include "MAppFrameData.h"
#include "MAppFrameUI.h"
#include "ICommunication.h"
#include "MSerialize.h"
#include "IFrameWindowInterface.h"
#include "MTreeModule.h"
#include "MAppEvent.h"
#include "MAppEventHandle.h"
#include <IMSql.h>
#include "MMenuAction.h"
//
// HAppFrameUI �����õ�UI
// HAppFrameData �����õ�Data
// MLogger ��¼���logger
//

class MAppData;
class MAppUI;
class MAppInstance;
class MAppParseFile;
class IDealDataInterface;
class MProjectType;
class MAppDataUnit;
class MAppWindow;
class MAppFrameData;
class MAppFrameUI;
class MLoggerBox;



namespace DxUI{
	class CDxWidget;
	struct IWindow;
}

//
// �����ӿ�
//
class IFactoryInterface;

//
// App ��ʵ������ֻ��һ��
// ��������App�������Լ�UI��Ϣ
//
class DXUI_API MAppManager : public TL::MTLObject
{
public:
    friend class MFrameWindow;
    //
    // ������״̬�ı�ʱִ�еĻص�����
    //
    typedef std::function<void(int)> APPSTATUSCHANGEFUN;

    //
    // �����״̬�Ĺ��̸ı�ʱִ�еĻص�����
    //
    typedef std::function<void(MString)> PROJECTCHANGEFUN;

    //
    // �������͸ı�Ļص�����
    //
    typedef APPSTATUSCHANGEFUN   APPPROJTYPECHANGEFUN;

    //
    // �ڼ����깤�̺���Щʲô�أ�
    //
    typedef std::function<void()>  FINISHEDLOADPROJFUN;



    //
    // ��������StrID���������ݣ�����UI
    //
    typedef TL::MMNoSqlDB<MString,MAppData*,MAppUI*> APPDATATYPE;

    //
    // ����ʵ�����󣬶�ͬһ��ʵ��������һ������,int ����������
    //
    typedef TL::MMNoSqlDB<MAppInstance*,MAppData*,MAppUI*,int> INSTACETYPE;

    //
    // ��������StrID����������
    //
    typedef std::map<MString,MProjectType*> APPPROJTYPE;

    //
    // ģ������ģ��ʵ��ָ��
    //
    typedef std::map<MString,MAppInstance*>  APPMODULES;

    //
    // HAppDataBase��HAppWindow
    //
    typedef std::map<MAppDataUnit*,MAppWindow*> APPDATAUI;


	//
	// ������ص��¼�����
	//
	typedef std::map<MString, MAppEventHandle*> PROJEVENTHANDLE;

    //
    // ������---���ݴ�����
    //
    typedef std::map<MString,IDealDataInterface*> PROJDATADEALER;


    typedef DxUI::IWindow*(*CreateInstanceFun)();


	//
	// �ض���������
	//
	typedef void(*NoArgrFunType)(TL::MTLObject*);


    explicit MAppManager();
    virtual ~MAppManager();

public:

    //
    // ��ǰ����Ӧ�ó����״̬
    //
    enum APPSTATUS{
        TESTING = 0,
        PURSE,
        STOP,
    };

    //
    // ��ǰ���̵�״̬���򿪣��½�����棿
    //
    enum PROJECTSTATUS{
        NEWPROJECT = 0,
        OPENPROJECT,
        SAVEASPROJECT,
        NONESTASTUS
    };

    ///
    /// \brief BindInstance
    /// \param __AppManager
    /// ���ⲿApp������
    /// ��֮��ʹ��Instance��ȡ�ı��ǰ󶨵�
    ///
    static void BindInstance(MAppManager* __AppManager);

    ///
    /// \brief Instance
    /// \return
    /// ����App�����Ψһʵ��
    /// �����ʹ�� BindInstance ��ʵ������ô���صı����ⲿʵ��
    ///
    static MAppManager* Instance();

    ///
    /// \brief DestroyInstance
    /// ����App�����ʵ��
    /// ֻ�����Լ�����������
    /// BindInstance �󶨵Ĳ�����
    ///
    static void DestroyInstance();


    ///
    /// \brief LoadWindowFromDll
    /// \param dllname Dll
    /// \param parent  ������ ����Ϊnullptr
    /// \return
    /// ��dllģ���м��ش���ģ��
    ///
    static DxUI::IWindow* LoadWindowFromDll(const MString& dllname);


    ///
    /// \brief Register
    /// \param syskey ϵͳָ����key ������ HKEY_CLASS_ROOT,HKEY_CURRENT_USER,HKEY_LOCAL_MACHINE,HKEY_USERS,HKEY_CURRENT_CONFIG
    /// \param usekey �û��Զ���key
    /// \param subkey ��
    /// \param value  ֵ
    /// \return
    /// дע���
    /// eg:
    /// Register(HKEY_CURRENT_USER,"HelloWord","Value","1000")
    ///
    static bool Register(HKEY syskey,
                         const MString& usekey,
                         const MString& subkey,
                         const MString& value);


    ///
    /// \brief ReadRegister
    /// \param syskey ͬRegister
    /// \param usekey ͬRegister
    /// \param subkey ͬRegister
    /// \return
    /// ��ȡע�����Ϣ
    /// eg:
    /// MString value = ReadRegister(HKEY_CURRENT_USER,"HelloWord","Value");
    ///
    static MString ReadRegister(HKEY syskey,
                                const MString& usekey,
                                const MString& subkey);

    ///
    /// \brief UnRegister
    /// \param syskey ͬRegister
    /// \param useKey ͬRegister
    /// \return
    /// ж��ע���
    /// eg:
    /// UnRegister(HKEY_CURRENT_USER,"HelloWord")
    ///
    static bool UnRegister(HKEY syskey,const MString& useKey);



	///
	///
	///
	static void RunNoArgrFunction(TL::MTLObject* obj, NoArgrFunType fun);

	//
	// ��ʾ��Ϣ�Ի��򣬽���һ��ȷ�ϰ�ť
	//
	static int ErrorBox(const MString& info,DxUI::CDxWidget* Parent = nullptr,const MString& title = "����");

	//
	// ��ʾ��Ϣ�Ի��򣬽���һ��ȷ�ϰ�ť
	//
	static int ShowBox(const MString& info, DxUI::CDxWidget* Parent = nullptr, const MString& title = "��Ϣ");

	//
	// ����Ի�����������ť��YES �� NO ����ֵΪIDYES �� IDNO
	//
	static int InfoBox(const MString& info, DxUI::CDxWidget* Parent = nullptr, const MString& title = "��ʾ");

	//
	// ����Ի�����������ť��YES NO �� CANCEL ����ֵΪIDYES IDNO �� IDCANCEL
	//
	static int QueBox(const MString& info, DxUI::CDxWidget* Parent = nullptr, const MString& title = "ѯ��");


    ///
    /// \brief ToString
    /// \return
    /// ת��Ϊ�ַ���
    /// ��Ϊһ����׼�ӿڶ�����
    ///
    virtual MString ToString(){return "MAppManager";}


    ///
    /// ��ȡAppData Ӧ�ó���������ݵ�Ψһ���
    ///
    template<class T = MAppData>
    T* AppData(const MString& projId = ""){
        if(mOpingProject.empty()){
            mOpingProject = mCurrentProject;
        }
        MString projName = mOpingProject;
        if(!projId.empty()){
            projName = projId;
        }   
		try{
			auto value = mAppDatas.item<0>(projName);
			MAppData* __Data = TL::get<1>(value);
			return dynamic_cast<T*>(__Data);
		}
		catch (...){
			return nullptr;
		}
    }

    ///
    /// ����FrameData ���ݵ�Ψһ���
    ///
    template<class T = MAppFrameData>
    T* AppFramData(){
        try{
            T* __data = dynamic_cast<T*>(pFrameData);
            return __data;
        }
        catch(...){
            return nullptr;
        }
    }

    ///
    /// ��ȡAppUI
    /// ����Ӧ�ó���UI��Ϣ��Ψһ���
    ///
    template<class T = MAppUI>
    T* AppUI(const MString& projId = ""){
        if(mOpingProject.empty()){
            mOpingProject = mCurrentProject;
        }
        MString projName = mOpingProject;
        if(!projId.empty()){
            projName = projId;
        }
		try{
			auto value = mAppDatas.item<0>(projName);
			MAppUI* __Data = TL::get<2>(value);
			return dynamic_cast<T*>(__Data);
		}
		catch (...){
			return nullptr;
		}
    }


    ///
    /// ��ȡAppFrameUI
    /// ����Ӧ�ó���FrameUI��Ϣ��Ψһ���
    ///
    template<class T = MAppFrameUI>
    T* AppFrameUI(){
        try{
            T* __Ui = dynamic_cast<T*>(pFrameUI);
            return __Ui;
        }
        catch(...){
            return nullptr;
        }
    }

    ///
    /// ��ȡ������Ϣ�������,ͬ���Ƿ��ʹ�����Ϣ��Ψһ���
    ///
    template<class T = MProjectType>
    T* ProjceType(const MString& projId = ""){
        if(mOpingProject.empty()){
            mOpingProject = mCurrentProject;
        }
        MString projName = mOpingProject;
        if(!projId.empty()){
            projName = projId;
        }
        if(mProjTypes.count(projName)){
            try{
				MProjectType* __Type = mProjTypes.at(projName);
                return dynamic_cast<T*>(__Type);
            }
            catch(...){
                return nullptr;
            }
        }
        else{
            return nullptr;
        }
    }


	///
	/// ��ȡ�źŴ�����
	/// ProjId ��Ҫ���ʵĹ���id
	///
	template<class T>
	T* AppSignalHandle(const MString& ProjId = ""){
		if (mOpingProject.empty()){
			mOpingProject = mCurrentProject;
		}
		MString projName = mOpingProject;
		if (!ProjId.empty()){
			projName = ProjId;
		}
		if (mProjEventHandle.count(projName)){
			auto ptr = mProjEventHandle.at(projName);
			try{
				T* __Ptr = dynamic_cast<T*>(ptr);
				return __Ptr;
			}
			catch (...){
				return nullptr;
			}
		}
		return nullptr;
	}


    ///
    /// ��ȡ�������ݴ�����
    /// ProjId ��Ҫ���ʵĹ���id Ĭ��Ϊ��ǰ���ڲ����Ĺ���
    ///
    template<class T>
    T* AppDataDealer(const MString& ProjId = ""){
        if(mOpingProject.empty()){
            mOpingProject = mCurrentProject;
        }
        MString projName = mOpingProject;
        if(!ProjId.empty()){
            projName = ProjId;
        }
        if(mProjDataDealer.count(projName)){
            auto ptr = mProjDataDealer.at(projName);
            try{
                T* __Ptr = dynamic_cast<T*>(ptr);
                return __Ptr;
            }
            catch(...){
                return nullptr;
            }
        }
        return nullptr;
    }

    ///
    /// ͨ��һ��ģ������ȡһ��ģ��ʵ��
    /// ��ģ�����ڴ�������֮ʱ�ɴ�������ģ�鷵��
    /// ��ȡ��ģ��ʵ��֮�����Դ�����ʵ���Ĺ���
    /// moduleName ������dll����Ҳ������ָ����ģ����
    ///
    MAppInstance* ModuleInstance(const MString& moduleName);

    ///
    /// \brief RegisterInstance
    /// \param moduleName
    /// \param instance
    /// ע��Instance
    /// ���ģ�鱾������ڴ��д�����ôֱ��ע�ἴ��
    ///
	void RegisterInstance(const MString& moduleName, MAppInstance* instance);

    ///
    /// \brief RemoveInstance
    /// \param moduleName
    /// �Ƴ�Instance
    ///
    void RemoveInstance(const MString& moduleName);

    ///
    /// ͨ��һ��Nag��StriID ��ȡ����root��
    /// GetNagRootTextFromStrId ��ȡ������ʾ��
    /// GetNagRootStrIdFromStrId ��ȡ����StrID
    ///
    MString GetNagRootTextFromStrId(const MString& strId);
    MString GetNagRootStrIdFromStrId(const MString& strId);

    ///
    /// ���ù�����Ϣ
    /// ��������ӽ������й���
    /// ��������ݣ�UI��������Ϣͨ���ýӿڹ�������
    ///
    void PushProject(const MString& projid,
                     MAppData* __data, MAppUI*
					 __ui, MProjectType* __Type);


	///
	/// \brief
	/// ����湤�̵�ʱ��ʹ��ͬһ��UI
	/// �ؼ�key�ᱻ�޸�
	/// ��Ҫִ�иú���������ظ���
	///
	void UpdateProjectInfo(MAppUI* __ui, MProjectType* __Type);

    ///
    /// \brief ProjectList
    /// \return
    /// ��ȡ�����б�
    ///
    TL::Vector<MString> ProjectList() const;


    //
    // CloseCurrent  �رյ�ǰ����
    // CloseAll �ر����й���
    // CloseProject �ر�ָ������
    //

    ///
    /// \brief CloseCurrent
    /// �رյ�ǰ����
    ///
    void CloseCurrent();

    ///
    /// \brief CloseAll
    /// �ر����й���
    ///
    void CloseAll();

    ///
    /// \brief CloseProject
    /// \param projid
    /// �ر�ָ������
    ///
    void CloseProject(const MString& projid);

    //
    // ��Ե�ǰ���̽��в���
    //

    ///
    /// \brief SaveCurrent
    /// \return
    /// ���浱ǰ����
    ///
    bool SaveCurrent();

    ///
    /// \brief SetCurrent
    /// \return
    /// ���õ�ǰ����
    ///
    bool SetCurrent();

    ///
    /// \brief ValidateCurrentData
    /// \return
    /// У�鵱ǰ����
    ///
    bool ValidateCurrentData();

    ///
    /// \brief UpdateCurrentWindow
    /// \return
    /// ���µ�ǰ���̵Ĵ���
    ///
    bool UpdateCurrentWindow();

    //
    // �������еĹ���
    // SaveAll ��UI���ݱ��浽Data��
    // SetAll  ��Data���õ�UI��
    // SaveProject ��Data���ݱ��浽�ļ���
    // ReadProject ���ļ��ж�ȡ���ݵ�Data��
    //

    ///
    /// \brief SaveAll
    /// \return
    /// �������й���
    /// �ù�����ͨ�� SaveContext ��UI�������Ϣ���浽Data��
    ///
    bool SaveAll();

    ///
    /// \brief SetAll
    /// \return
    /// �������й���
    /// �ù�����ͨ�� SetContext ������Data�ϵ��������õ�UI��
    ///
    bool SetAll();

    ///
    /// \brief ValidateAll
    /// \return
    /// ͨ�� ValidateData У��UI��������Ϣ
    ///
    bool ValidateAll();

    ///
    /// \brief UpdateAllWindow
    /// \return
    /// ͨ�� UpdateWindow ��UI���и���
    ///
    bool UpdateAllWindow();

    ///
    /// \brief SaveProject
    /// \param project
    /// \return
    /// ��ָ�����̵�UI��Ϣ���浽Data������Data�б��浽Ӳ��
    ///
    bool SaveProject(const MString& project = "");

    ///
    /// \brief ReadProject
    /// \param project
    /// \return
    /// ��Ӳ���ж�ȡָ�����̵����ݵ�Data�У������õ�UI
    ///
    bool ReadProject(const MString& project = "");

    //
    // ����ȫ������
    //

    ///
    /// \brief SaveFrameData
    /// \return
    /// ��FrameUI��Ϣͨ�� SaveContext ���浽 FrameData �ٵ�Ӳ��
    ///
    bool SaveFrameData();

    ///
    /// \brief SetFrameData
    /// \return
    /// ��ȡ FrameData Ȼ��ͨ�� SetContext ���õ�FrameUI
    ///
    ///
    bool SetFrameData();

    ///
    /// \brief UpdateFrameUI
    /// \return
    /// ����FrameUI
    ///
    bool UpdateFrameUI();

    ///
    /// \brief ValidateFrameData
    /// \return
    /// У��FrameUI�������Ƿ���Ч
    ///
    bool ValidateFrameData();

    //
    // ���µ�����
    //

    ///
    /// \brief UpdateNagTree
    /// \param isAll
    /// ���µ�����
    ///
    void UpdateNagTree(bool isAll = true);

    ///
    /// \brief PushNagTree
    /// \param itemID
    /// ��ӵ����˵�
    /// itemID �� # �ŷֲ� ͼ�����[]��
    /// eg :
    /// StrId = Project[:res/icon.png]#Item1[:res/xxxx]#Item2[xxxx]
    /// �������
    /// Project
    ///     Item1
    ///         Item2
    ///
    void PushNagTree(const MString& itemID);

    ///
    /// \brief EraseNagTree
    /// \param itemID
    /// ɾ��������Ϣ
    ///
    void EraseNagTree(const MString& itemID);

    ///
    /// \brief SetCurrentNagItem
    /// \param itemId
    /// ��ָ����item��ѡ��״̬
    ///
    void SetCurrentNagItem(const MString& itemId);

    ///
    /// \brief ModifyNagShowName
    /// \param itemId
    /// \param Name
    /// �޸�ָ����Item����ʾ��
    ///
    void ModifyNagShowName(const MString& itemId,const MString& Name);

    //
    // �޸ĵ�ǰ�����Ĺ���
    // ���ú���������Ĳ������ǶԵ�ǰ���̽��в���
    //

    ///
    /// \brief SetCurrentProject
    /// \param currentProjId
    /// ����ָ������Ϊ��ǰ����
    ///
    void SetCurrentProject(const MString& currentProjId);

    ///
    /// \brief CurrentProject
    /// \return
    /// ��ȡ��ǰ����
    ///
    const MString&  CurrentProject() const;

    //
    // ParentWindow ��ȡ������
    // AttachWindow ��������Ϊ����APP�ĸ�����
    // DettachWindow ����Ҫ������
    //

    ///
    /// \brief ParentWindow
    /// \return
    /// ��ȡ������
    ///
    DxUI::CDxWidget* ParentWindow();

    ///
    /// \brief AttachWindow
    /// \param __window
    /// ��ָ��������Ϊ�����ڱ�������
    ///
	void AttachWindow(DxUI::CDxWidget* __window);

    ///
    /// \brief DettachWindow
    /// ������Ҫ������
    ///
    void DettachWindow();

    //
    // ��ȡ��ǰ��������Ĵ���
    //

    ///
    /// \brief CurrentWindow
    /// \return
    /// ��ȡ��ǰ�������򴰿�
    ///
	DxUI::CDxWidget* CurrentWindow() const;


	//
	// ��־��¼����
	//
	MLoggerBox* MLoggerWindow();

    //
    // InitWindow ��ʼ���������
    // NagTree ��ȡ���������
    // MsgOuput ��ȡ����������
    // MenuAndTool ��ȡ�˵��������
    // NewForm ��ȡ�½��������
    // PopMenu ��ȡ�Ҽ��˵�
    //
	MTreeModule*  NagTree();


	//
	// ��ȡ�����¼�������
	//
	MAppEvent*  RootEvent();

    /// \brief InitWindow
    /// \param parent ������
    /// \param __data FrameData
    /// \param __ui   FrameUI
    /// ��ʼ����ɺ���ɿ�ܹ��õ����
    ///
	void InitWindow(DxUI::CDxWidget* parent, MAppEvent* Event,MAppFrameData* __data = nullptr, MAppFrameUI* __ui = nullptr); // ��ʼ������

    ///
    /// \brief InstallCommunication
    /// \param __communication
    /// ��װͨ��ģ��
    ///
    void InstallCommunication(ICommunication* __communication);

    ///
    /// \brief InstanllProTypeFactor
    /// \param factor
    ///  ��װ���̹�����
    ///
    void InstallProTypeFactor(MProjectType* factor);



    ///
    /// \brief InstallAnyAction
    /// \param StrKey �ؼ���
    /// \param any    ��������
    /// ��������������ǿ����,��װ���������
    ///
    void InstallAnyAction(const MString& StrKey,const MAny& any);

    ///
    /// \brief RemoveAnyAction
    /// \param any
    /// �� InstallAnyAction ��Ӧ,�����Ƴ�һ������
    ///
    void RemoveAnyAction(const MAny& any);

    ///
    /// \brief GetAnyAction
    /// \return
    /// ��ʵ���л�ȡ�ò����ȿ����������ί��,��Ȼǰ����Ҫ�Ȱ�װ����ί��
    ///
    const TL::Vector<MAny> &GetAnyAction() const;

    ///
    /// \brief GetAnyAction
    /// \param StrKey
    /// \return
    /// ��ȡָ������
    ///
    MAny GetAnyAction(const MString& StrKey) const;




    ///
    /// \brief NewProjType
    /// \return
    /// ͨ�������������̹�����
    ///
    MProjectType* NewProjType() const;


    ///
    /// \brief SetFrameConfigFile
    /// \param configfile
    /// �޸�FrameData�ı����ļ�
    /// ����û��Ҫ��ô��
    ///
    void SetFrameConfigFile(const MString& configfile); // ����Frame��config�ļ�

    ///
    /// \brief FrameConfigFile
    /// \return
    /// ��ȡFrameData������ļ�
    ///
    const MString& FrameConfigFile() const; // Frame��config�ļ�

    ///
    /// \brief GetFrameSerial
    /// \return
    ///
    DxUI::MSerialize*		GetFrameSerial();



	void					SetWorkWindowIndex(int index);
	DxUI::CDxStackedWidget* GetCurrentWorkWindow();
	DxUI::CDxStackedWidget* GetCenterWindow();


    ///
    /// \brief ShowWindow
    /// \param window
    /// ֱ���� Frame ���л����ڵ���ʾ
    ///
	DxUI::CDxWidget*  ShowWindow(DxUI::CDxWidget* window);  // ��ʾ���ڹ���
	int			  ShowWindowByIndex(unsigned index);
	void		  PushWindow(DxUI::CDxWidget* window);
	unsigned	  GetWindowCounts() const;

    ///
    /// \brief RemoveWindow
    /// \param window
    /// �����ڴӿ�����Ƴ�
    ///
    void          RemoveWindow(DxUI::CDxWidget* window); // �Ƴ�����
	void		  RemoveWindowByIndex(unsigned index);


    ///
    /// \brief CloseApp
    /// \return
    /// �ر�App
    /// ����ֵ 1 ��ʶ��Ҫ���湤��
    /// 0 ����Ҫ���湤��
    /// -1 ȡ�����ر�
    ///
    int CloseApp();

    ///
    /// \brief AppStatus
    /// \return
    /// ��ȡ��ǰAPP��״̬
    /// ֻ��һ�����̴��ڲ���״̬
    ///
    APPSTATUS AppStatus();

    ///
    /// \brief SetAppStatus
    /// \param status
    /// ���õ�ǰAPP״̬
    /// �ú������з�������
    /// ���Կ��ԶԸ�����ѡ�����
    ///
    void SetAppStatus(APPSTATUS status);

    ///
    /// \brief ProjectStatus
    /// \param projid
    /// \return
    /// ��ȡ��ǰ���̵�״̬
    ///
    PROJECTSTATUS ProjectStatus(const MString &projid = "");

    ///
    /// \brief SetProjectStatus
    /// \param status
    /// \param ProjId
    /// ���õ�ǰ����״̬
    ///
    void SetProjectStatus(PROJECTSTATUS status, const MString& ProjId = "");

    ///
    /// \brief BindAppStatusFun
    /// \param fun
    /// ����APP״̬�ı�ص�����
    ///
    void BindAppStatusFun(APPSTATUSCHANGEFUN fun);

    ///
    /// \brief BindProjectChangeFun
    /// \param fun
    /// ���ù��̸ı�ʱִ�еĲ���
    ///
    void BindProjectChangeFun(PROJECTCHANGEFUN fun);

    ///
    /// \brief BindAppTypeChangeFun
    /// \param fun
    /// �����͸ı�ʱִ�еĲ���
    ///
    void BindAppTypeChangeFun(APPPROJTYPECHANGEFUN fun);

    ///
    /// \brief BindLoadFinishedProjFun
    /// \param fun
    /// ���ü����깤�̺�ִ�еĲ���
    ///
    void BindLoadFinishedProjFun(FINISHEDLOADPROJFUN fun);

    ////
    /// \brief BindSaveFinsihedProjFun
    /// \param fun
    /// ���ñ����깤�̺�ִ�еĲ���
    ///
    void BindSaveFinsihedProjFun(FINISHEDLOADPROJFUN fun);

    ///
    /// \brief BindCloseFinishedProjFun
    /// \param fun
    /// �رչ��̺���ִ�еĲ���
    ///
    void BindCloseFinishedProjFun(FINISHEDLOADPROJFUN fun);

    ///
    /// \brief BindOpenfinishedProjFun
    /// \param fun
    /// �򿪹��̺���ִ�еĲ���
    ///
    void BindOpenfinishedProjFun(FINISHEDLOADPROJFUN fun);

    ///
    /// \brief HaveProject
    /// \param projId
    /// \return
    /// ��ѯ��ǰ�Ƿ��й���
    ///
    bool HaveProject(const MString& projId = "");



    ///
    /// \brief CreateInstance
    /// \param modulename ģ����
    /// \return
    /// ����ģ��ʵ��
    ///
    MAppInstance* CreateInstance(const MString& modulename);

    ///
    /// \brief AppInstance
    /// \param projname
    /// \return
    /// ���ݹ�������ȡ������ǰ���̵�Instance
    ///
    MAppInstance* AppInstance(const MString& projname);

    ///
    /// \brief CreateProject
    /// \param modulename ģ����
    /// \param __Type ������Ϣ������
    /// \return
    /// ��������
    ///
    bool CreateProject(const MString& modulename,MProjectType* __Type);
	bool OpenProject(const MString& modulename, MProjectType* __Type);
	bool GenProjectWindow(const MString& modulename, MProjectType* __Type);

    ///
    /// \brief UpdateOperatorProj
    /// \param ProjID
    /// ���µ�ǰ�����Ĺ���
    ///
    void UpdateOperatorProj(const MString& ProjID);


    ///
    /// \brief getTestingProjectID
    /// \return
    /// ��ȡ���ڲ��ԵĹ���
    ///
    MString GetTestingProjectID() const;

    ///
    /// \brief RegisterEventFun
    /// \param menuName
    /// \param actionName
    /// \param fun
    /// ע����Ӳ˵��¼�
    ///
    void RegisterEventFun(const MString& menuName,const MString& actionName,std::function<bool()> fun);
    void AddMenuToFrame(const MString& menuName,unsigned pos);
    void RemoveMenuFromFrame(const MString& menuName);

    ///
    /// \brief RegisterFrameData
    /// \param FrameData
    /// ע�ṫ������
    ///
    void RegisterFrameData(const TL::Vector<MAppDataUnit *> &FrameData);

    ///
    /// \brief RegisterFrameUI
    /// \param FrameUI
    /// ע�ṫ��UI
    ///
    void RegisterFrameUI(const TL::Vector<MAppWindow *> &FrameUI);

    ///
    /// \brief RegisterFrameData
    /// \param FrameData
    /// ��ע�ṫ������
    ///
	void UnRegisterFrameData(const TL::Vector<MAppDataUnit *> &FrameData);

    ///
    /// \brief RegisterFrameUI
    /// \param FrameUI
    /// ��ע�ṫ��UI
    ///
	void UnRegisterFrameUI(const TL::Vector<MAppWindow *> &FrameUI);


    ///
    /// \brief GetFrameInterface
    /// \return
    /// ��ȡmainwindow�Ĳ����ӿ�
    ///
    IFrameWindowInterface* GetFrameInterface();


	//
	// ��ȡ���ݿ����ָ��
	//
	std::shared_ptr<IMSql> GetSqlPtr();

    ///
    /// \brief HideNagTreeWindow
    /// \param ishide
    /// ���ص���������
    ///
    void HideNagTreeWindow(bool ishide);

    ///
    /// \brief HideOutputWindow
    /// \param ishide
    /// �����������
    ///
    void HideOutputWindow(bool ishide);

    ///
    /// \brief Lock
    /// �Բ��Թ��̽��б���
    ///
    void Lock();

    ///
    /// \brief UnLock
    /// ������������
    ///
    void UnLock();

    ///
    /// \brief isLock
    /// \return
    /// ��鵱ǰ�Ƿ�������
    ///
    bool IsLock();

	void SetCurrentUserName(const MString& UserName);
	MString GetCurrentUserName() const;


	///
	/// \brief UpdateProjectForDataBase
	/// \return
	/// ���ݿ���µ�ʱ�򴥷����¼�
	///
	void UpdateProjectForDataBase();


	//
	// ������д�����ݿ���
	//
	void UpdateProjectToDataBase(const MString& FileName,MProjectType* __Type);


	//
	// �����ݿ��л�ȡ��ǰ����Ĺ����б�
	// ����ʱ��˳������
	// �����ڵĹ��̽��ᱻ�Ƴ�
	//
	TL::Vector<std::pair<MString,MString>> GetProjectListFromDataBase();

	//
	// �����ݿ��л�ȡָ�����͵Ĺ���
	//
	TL::Vector<std::pair<MString, MString>> GetProjectListFromDataBaseByType(int Type);


	//
	// �����ݿ��л�ȡָ���û��Ĺ���
	//
	TL::Vector<std::pair<MString, MString>> GetProjectListFromDataBaseByUser(const MString& userName);

	//
	// �����ݿ��л�ȡָ������ָ���û��Ĺ���
	//
	TL::Vector<std::pair<MString, MString>> GetProjectListFromDataBaseByUser(int Type,const MString& userName);

	MMenuActionManager*  GetMenuManager();

	///
	/// \brief FinishedSerail
	/// \return
	/// �̼߳��������ݺ�ִ�к���
	///
	void FinishedSerail(const MString& ProjectName);
protected:
    bool    SaveUiToData(const MString& proj);
    MString GetProjFromInstance(MAppInstance* __instance);
    void    SaveDataDealer(const MString& Proj,IDealDataInterface* __DealData);
    void    EraseDataDealer(const MString& Proj);

	void    SaveEventHanle(const MString& Proj, MAppEventHandle* __DealData);
	void    EraseEventHanle(const MString& Proj);


protected:
    MString             mCurrentProject;            // ��ǰ���ڲ����Ĺ��� �������һ��StrID
    MString             mOpingProject;               // �����Ĺ��̣���δ���ǵ�ǰ����
    APPDATATYPE         mAppDatas;                  // �������й��̵����� ����UI��Ϣ
    APPPROJTYPE         mProjTypes;                 // ������Ϣ,������ -----> ProjectType
    APPMODULES          mModuleInfo;                // ģ����Ϣ
    APPMODULES          mProjInstanceMap;           // ���湤�̺�instance�Ĺ�ϵ��Ӧ
	PROJEVENTHANDLE		mProjEventHandle;			// ���湤�̺Ͷ�Ӧ���¼�����
    PROJDATADEALER      mProjDataDealer;            // ���湤�̺Ͷ�Ӧ�����ݴ�����
  
    INSTACETYPE         mInstanceMap;               // instance��ʵ��֮���ӳ��
    DxUI::CDxWidget*    pParentWindow{nullptr};     // ������,��DataManagerһ������һ��
    MProjectType*       pProjTypeFactor{nullptr};   // �������͵Ĺ�������



    //
    // ���湫�����ͨ����Ա����ֱ�Ӳ���
    //
private:
    //
    // �����UI�������������ͬʹ�õģ����������ﴴ��
    //
    bool					bIsInishedWindow{false};
	DxUI::CDxStackedWidget* pCenterWindow{ nullptr };
	MLoggerBox*				pLoggerWindow{ nullptr };
	MTreeModule*			pTreeWindow{ nullptr };
	int						mWorkWindowIndex{ -1 };

    //
    // APP��ص�ͨ��UI��Data
    //
    MAppFrameUI*        pFrameUI{nullptr};         // ȫ��UI
	MAppFrameData*      pFrameData{ nullptr };       // ȫ������
	MAppEvent*			pEvent{ nullptr };
    MString             mFrameConfigFile;          // ��ܵ������ļ�


	MString				mCurrentSerialName;
	MMenuActionManager  mMenuManager;

    //
    // ��¼APP��ǰ״̬,�Լ�״̬�ı�ʱִ�еĲ���
    //
    APPSTATUS               mAppStatus{STOP};           // ��ǰ�Ƿ����ڲ�������,�������
    APPSTATUSCHANGEFUN      mAppStatusFun{nullptr};     // ����״̬�ı�ʱִ�еĺ���
    PROJECTCHANGEFUN        mProjectChangeFun{nullptr}; // ���̸ı�ʱִ�еĻص�����
    APPPROJTYPECHANGEFUN    mAppTypeChangeFun{nullptr}; // �������͸ı�ʱִ�еĻص�����
    FINISHEDLOADPROJFUN     mLoadFinsihedProjFun{nullptr}; // �����깤�̺󽫻ᱻִ�еĺ���
    FINISHEDLOADPROJFUN     mSaveFinsihedProjFun{nullptr}; // ���̱�����ɺ��ִ�к���
    FINISHEDLOADPROJFUN     mCloseFinishedProjFun{nullptr}; // �رչ��̺�ִ�еĺ���
    FINISHEDLOADPROJFUN     mOpenFinsihedProjFun{nullptr}; // �򿪹��̺���ִ�еĲ���
    //
    // mLoadFinsihedProjFun �� mOpenFinsihedProjFun ���Ǹ���ͬһ����
    // mLoadFinsihedProjFun �����ڼ���������й������ú󷽲�ִ��
    // mOpenFinsihedProjFun �򿪹���֮����ִ��
    //

    //
    // ��¼���̵�����
    //
    TL::Map<MString,PROJECTSTATUS> mProjectProperty;


    //
    // �����������������¿��ܻ���HAppManager���ᱻ��д,��ô����������ó�
    //
    static MAppManager*				pAppManager;              // ����App�����Ψһʵ��
                                                  // ����ͨ���ⲿ���д�����Ȼ��ͨ��Frame���а�
    static bool						bInstanceIsThis;          // �����ж�AppManager�Ƿ��������
                                                  // ��Ϊ���������Ļ���ô��DestroyInstance��ʱ��Ϳ��Խ���delete

    //
    // ͨ��ģ��
    //
    ICommunication*      pCommunication{nullptr};
    MString              mTestingProject;
    bool                 bIsLock{false};


    //
    // holdסһ��������Ҫ��ʱ�������ȡ���ڸ������һЩ�ⲿ��ɵ�����
    //
    TL::Vector<MAny>          mAnyAction;
    std::map<MString,MAny>     mAnyActionMap;

    //
    // ��dll�м���ģ��
    //
    static std::unordered_map<MString,CreateInstanceFun> mModuleFuns;

    //
    // ���̲߳���,�����ݵĲ��������߳���,��GUI�Ĳ��������߳���
    //
private:
    void DealCommuniction(bool isok);


	MString						m_CurrentUserName;
    MString						mReadingProjectName;
    DxUI::MSerialize*			pSerial{nullptr};
	DxUI::MSerialize			mFrameConfigSerial;
	std::shared_ptr<IMSql>      m_SqlPtr;
};

