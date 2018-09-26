

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
