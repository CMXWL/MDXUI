

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once
#include "DxConfig.h"
#include "MAppWindow.h"

class MProjectType;

class DXUI_API MAppUI
{
public:
	MAppUI();
	~MAppUI();

	///
	/// \brief Attach
	/// \param Window
	/// �����ں�ϵͳ��ܹ�������
	///
	void Attach(MAppWindow* Window);

	///
	/// \brief Dettach
	/// \param window
	/// �����ں�ϵͳ��ܶϿ�����
	///
	void Dettach(MAppWindow* window);

	///
	/// \brief ToString
	/// \return
	/// ���ýӿ�
	///
	virtual MString ToString(){ return "HAppUI"; }

	///
	/// \brief ShowWindow
	/// \param window
	/// ShowWindow ��ʾ���� PushWindow ѹ�봰��
	///
	void ShowWindow(MAppWindow* window);

	///
	/// \brief PushWindow
	/// \param window
	/// ��Ӵ���
	///
	void PushWindow(MAppWindow* window);

	///
	/// \brief RemoveWindow
	/// \param window
	/// �Ƴ�����
	///
	void RemoveWindow(MAppWindow* window);

	///
	/// \brief CurrentWindow
	/// \return
	/// ��ȡ��ǰ�Ĵ���
	///
	DxUI::CDxWidget* CurrentWindow() const;


	///
	/// \brief SaveContext
	/// \return
	/// SaveContext ��AppUI ��ʾ�����ݱ��浽 AppData��
	///
	virtual bool SaveContext();

	///
	/// \brief SetContext
	/// \return
	/// SetContext  ��AppData �е��������õ� AppUI��
	///
	virtual bool SetContext();

	///
	/// \brief LockWindow
	/// ��ס������Ϣ
	///
	virtual void LockWindow();

	///
	/// \brief UnLockWindow
	/// ��������
	///
	virtual void UnLockWindow();


	///
	/// \brief OnAnyOporator
	/// \param any
	/// ִ������Ĳ���
	///
	virtual void OnAnyOporator(const mj::MAny& any);


	///
	/// \brief ValidateData
	/// \return
	/// У��������Ϣ
	///
	virtual bool ValidateData();

	///
	/// \brief UpdateWindow
	/// \return
	/// ���´�����Ϣ
	///
	virtual bool UpdateWindow();

	///
	/// \brief Destroy
	/// ����UI
	///
	virtual void Destroy();

	//
	// ��ȡ��ǰ���̵ĵ�������Ϣ
	// GetRootStrID ��ȡ���Root��StrID
	// PushNag ��ӵ�����Ϣ ��ʽ ����
	// root#child#chilchild# ........... ����ͼ��
	// root[ͼ��]#child[ͼ��]#chilchild[ͼ��]# ..��ͼ��
	// EraseNag ɾ���������ϵ���
	// SetProjectName ���ù�����
	// RegisterWindow �ô��ں�item��������
	// UnrigsterWindow �ô��ں�item���ٹ���
	//

	///
	/// \brief GetRootStrID
	/// \return
	/// ��ȡ���Root��StrID ͨ����͹�������صĵ�һ��
	///
	MString GetRootStrID();

	///
	/// \brief ModifyProjectName
	/// \param NewName
	/// �Թ�����ʾ�������޸�
	///
	void ModifyProjectName(const MString& NewName); // �޸Ĺ�����

	///
	/// \brief PushNag
	/// \param Nag
	/// ��ӵ���item
	/// root[ͼ��]#child[ͼ��]#chilchild[ͼ��]# ..��ͼ��
	///
	void PushNag(const MString& Nag);

	///
	/// \brief PushNag
	/// \param Nags
	/// ���һ�鵼��item
	///
	void PushNag(const TL::Vector<MString>& Nags);

	///
	/// \brief EraseNag
	/// \param Nags
	/// ɾ������item
	///
	void EraseNag(const MString& Nags);

	///
	/// \brief SetProjectName
	/// \param ProjectName
	/// ���ù�����
	///
	void SetProjectName(const MString& ProjectName);

	///
	/// \brief RegisterWindow
	/// \param NagStrId
	/// \param window
	/// ע�ᴰ�ڣ��ô��ں�item��������
	/// ��������֮��ͨ�����������������л�����Ӧ�Ĵ���
	///
	void RegisterWindow(const MString& NagStrId, MAppWindow* window);

	///
	/// \brief UnrigsterWindow
	/// \param NagStrId
	/// ��ע�ᴰ��
	///
	void UnrigsterWindow(const MString& NagStrId);


	///
	/// \brief NagTreeInfo
	/// \return
	/// ��ȡ��ǰ���̵ĵ�������Ϣ
	///
	TL::Vector<MString> NagTreeInfo();

	///
	/// \brief InitUI
	/// \param parent ������
	/// \param __Type ������Ϣ
	/// \return
	/// ��ʼ��UI����
	/// �������Ҫ���´���UI������ʹ��UpdateAppUI��UI���и���
	///
	virtual bool InitUI(DxUI::CDxWidget* parent, MProjectType* __Type);
	virtual bool UpdateAppUI(MProjectType* __Type);



	///
	/// \brief InitConnect
	/// ��ʼ���ź�����
	///
	virtual void InitConnect();



	///
	/// \brief InitUIConnect
	/// InitConnect Ĭ��ʵ�ֻ��������������ź�Connect
	/// ����Ҫ��дӦ����д����ĺ���
	///
	virtual void InitUIConnect();

	///
	/// \brief WindowContainer
	/// \return
	/// ��ȡ��������
	///
	DxUI::CDxStackedWidget* WindowContainer();

	///
	/// \brief GetWindowFromStrId
	/// \param strId
	/// \return
	/// ͨ��strid��ȡһ�����ڣ�ǰ����Ҫע����д˴���
	///
	MAppWindow* GetWindowFromStrId(const MString& strId);

	///
	/// \brief GetStrIDFromWindow
	/// \param window
	/// \return
	/// ͨ�����ڻ�ȡ��Ӧ��StrID
	MString     GetStrIDFromWindow(MAppWindow* window);

	///
	/// \brief GetProjectStrID
	/// \return
	/// ��ȡ���̵�strID
	///
	MString GetProjectStrID() const;

	///
	/// \brief ClearNagInfo
	/// ���������Ϣ
	///
	void ClearNagInfo();

	///
	/// \brief Clear
	/// ����󶨵Ĵ���
	///
	void Clear();

protected:
	void  DealNagInfo();
	void  SetProjectStrID(const MString& strID);

protected:
	TL::Vector<MAppWindow*>		mNeedOpWindows; // ������Ҫ���µĴ���
	TL::Vector<MString>			mNagTreeInfo;   // �����ͼ����Ϣ��item
	TL::Vector<MString>			mNagStrIDs;     // ���������ַ�item
	MString						mProjectStrId;  // ���̵�StrID
	MString						mProjectName;
	DxUI::CDxWidget*            pParentWindow{ nullptr };  // ���游���ڵ�ָ�� ������ʾ����ܻ��õ�
	DxUI::CDxStackedWidget*		pWindowContainer{ nullptr }; // UI����Ĵ�������
	std::map<MString, MAppWindow*> mNagWindows; // �������ϵĴ���

};

