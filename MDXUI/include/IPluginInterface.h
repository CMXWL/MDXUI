


///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
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


