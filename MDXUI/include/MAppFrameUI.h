

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DxConfig.h"
#include "DxWidget.h"
#include "MAppWindow.h"


class DXUI_API MAppFrameUI
{
public:
	MAppFrameUI();
	virtual ~MAppFrameUI();

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
    /// \brief SaveContext
    /// \return
    /// SaveContext ��AppUI ��ʾ�����ݱ��浽 AppData��
    ///
    virtual bool SaveContext();


    ///
    /// \brief SetContext
    /// \return
    /// SetContext  ��AppData �е��������õ� AppUI��
    /// �ú�������������������ɳ�ʼ����������ִ��,���ĳЩ�����Ҫ�����ʱ����ʼ���Ļ��˴�����õĵط�
    /// ��Ϊ�ú��������������н���ִ��һ�Σ�������Ϊ�ĵ���
    ///
    virtual bool SetContext();

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
    /// \brief InitUI
    /// \param parent
    /// \return
    /// ��ʼ��UI����,�ú����ڳ����ʼ����֮�����ȱ�����,�����Υ����ʼ��˳��Ķ���Ҫ��ʼ����ʹ��������ʽ
    /// ����ʹ�� SetContext �����г�ʼ��
    ///
    virtual bool InitUI(DxUI::CDxWidget* parent);

    ///
    /// \brief ToString
    /// \return
    /// ���ýӿ�
    ///
    virtual MString ToString(){return "MAppFrameUI";}

protected:
    TL::Vector<MAppWindow*>  mNeedOpWindows; // ������Ҫ���µĴ���

};
