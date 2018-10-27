

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
#include <comdef.h>
#include <MAny.h>

namespace DxUI{
	class CDxWidget;
}

//+------------------------------
//
//  IPluginInterface
//  ����ӿ�
//  CreatePluginInterface ����������Ϊ
//  IPluginInterface*(*CreatePluginFun)()
//
//+------------------------------
struct IPluginInterface{
    virtual ~IPluginInterface(){}


	///
	/// \brief
	/// \param riid,pout
	/// \return
	/// ��ʵ�򵥵�˵��������ת������
	/// riid == __uuidof(IWindow) ��ȡ�Ķ��������� MAppWindow*
	/// riid == __uuidof(IWidget) ��ȡ�Ķ��������� CDxWidget*
	///
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** pout) = 0;


	///
	/// \brief
	/// \param parent
	/// ���ýӿڸ�����ָ���Ĵ�������
	/// ����gui���ڲ����Ч
	///
	virtual void Attach(DxUI::CDxWidget* parent){}

    ///
    /// \brief DestroyInstance
	/// ���ٵ�ǰʵ��
    ///
    virtual void DestroyInstance(){}

    ///
    /// \brief OnPutData
    /// \param any_data
    /// �����ݴ��ݵ�ģ��֮��
    ///
    virtual void OnPutData(const mj::MAny& any_data) = 0;

    ///
    /// \brief OnGetData
    /// \return
    /// ��ģ���л�ȡ����
    ///
    virtual mj::MAny OnGetData() const = 0;

    ///
    /// \brief IsWindowPlugin
    /// \return
    /// ģ���Ƿ����ڴ���ģ��
	/// �����ǰģ���Ǵ���ģ��
	/// ��Ҫͨ�������Attach����parent
    ///
    virtual bool IsWindowPlugin() =0;

    ///
    /// \brief OpenWindow
    /// \return
    /// �򿪴���
    ///
    virtual int OpenWindow() = 0;

    ///
    /// \brief OnDestroy
    /// ����ģ���е�����
    ///
    virtual void OnDestroy() =0;

    ///
    /// \brief OnDescribe
    /// \return
    ///
    virtual const char* OnDescribe() const = 0;

    ///
    /// \brief IsCanAcceptedData
    /// \return
    /// �Ƿ������Ϣ
    ///
    virtual bool IsCanAcceptedData() const = 0;
};


