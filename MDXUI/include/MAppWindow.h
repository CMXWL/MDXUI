

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include "DxConfig.h"


namespace DxUI{
	class CDxStackedWidget;
	class CDxWidget;
}

//
// ����App �Ĵ��ڶ�Ӧ�ü̳�������
// ��ΪDialog����ͨ���ڵ���ʾ��ʽ�Ͳ�һ��
// ���ͨ��������ṩͳһ�ӿڻ�����ܶ෽��
//
class DXUI_API MAppWindow
{
public:
	MAppWindow();
	virtual ~MAppWindow();


	virtual int OpenWindow();

	///
	/// \brief InitConnect
	/// ��ʼ���ź�����
	///
	virtual void InitConnect(){}


	///
	/// \brief SaveContext
	/// \return
	/// SaveContext ��AppUI ��ʾ�����ݱ��浽 AppData��
	///
	virtual bool SaveContext(){ return true; }

	///
	/// \brief SetContext
	/// \return
	/// SetContext  ��AppData �е��������õ� AppUI��
	///
	virtual bool SetContext(){ return true; }

	///
	/// \brief LockWindow
	/// ��ס���ڽ���
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
	/// ִ��һ���������
	///
	virtual void OnAnyOporator(const mj::MAny& any);

	///
	/// \brief ValidateData
	/// \return
	/// У���������ݵ���Ч��
	///
	virtual bool ValidateData(){ return true; }

	///
	/// \brief UpdateWindow
	/// \return
	/// ���´���
	///
	virtual bool UpdateWindow(){ return true; }


	///
	/// \brief ToString
	/// \return
	/// ���ýӿ�
	///
	virtual MString ToString(){ return "MAppWindow"; }


	///
	/// \brief IsModified
	/// \return
	/// ��鴰�ڵ���Ϣ�Ƿ��и���
	///
	virtual bool IsModified(){ return false; }

	///
	/// \brief IsCanAcceptied
	/// \return
	/// IsCanAcceptied
	///
	virtual bool IsCanAcceptied(){ return true; }



	///
	/// \brief SetWindowContainer
	/// \param Container
	/// �����ô��ڷŽ�����֮ʱ��Ҫ�Ѹ�������¼����
	/// �����Ҫ�����ڷŽ���������
	/// ��ô�ñ�����øú�������������ָ��
	/// ��Ϊ�������Ļ����ԺܺõĿ��ƴ����������е���ʾ
	///
	void SetWindowContainer(DxUI::CDxStackedWidget* Container);

	///
	/// \brief WindowContainer
	/// \return
	/// ��ȡ��������
	///
	DxUI::CDxStackedWidget* WindowContainer() const;


	//
	// protected Ϊ���������ܹ����з���
	//
protected:
	DxUI::CDxStackedWidget* pWindowContainer{ nullptr }; // ��������

};


//
// ��������һ��С����
//
#ifndef CLASS_TOSTRING
#define CLASS_TOSTRING(className) public:\
	virtual MString ToString(){ return #className; }
#endif