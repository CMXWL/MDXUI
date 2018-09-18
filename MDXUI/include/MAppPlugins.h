

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include <map>
#include "DxConfig.h"
#include <MSingleton.h>


///
/// ǰ������
///
class IPluginInterface;

///
/// \brief The HAppPlugins class
/// ����������App����Ϊ���еĴ���
///
class DXUI_API MAppPlugins : public MSingleton<MAppPlugins>
{
public:
	MAppPlugins();
	~MAppPlugins();

    ///
    /// \brief OnPutData
    /// \param any_data
    /// \param dllName
    /// ��plugin��д������
    /// dllName ���Ϊ�� ��ô������plugin��д������
    ///
    bool OnPutData(const mj::MAny& any_data,const MString& dllName = "");

    ///
    /// \brief OnGetData
    /// \param dllName
    /// \return
    /// ��ȡָ��plugin�е�����
    ///
    mj::MAny OnGetData(const MString& dllName) const;



    ///
    /// \brief AddPlugin
    /// \param dllName
    ///
    IPluginInterface* AddPlugin(const MString& dllName);

    ///
    /// \brief RemovePlugin
    /// \param dllName
    ///
    void RemovePlugin(const MString& dllName);

    ///
    /// \brief GetPluginList
    /// \return
    ///
    std::vector<MString> GetPluginList() const;

    ///
    /// \brief GetPlugin
    /// \param dllName
    /// \return
    ///
    IPluginInterface* GetPlugin(const MString& dllName);


	///
	/// \brief
	/// \param KeyName
	/// \return
	/// ͨ���ؼ��ֲ�ѯIPluginInterface
	/// KeyName ����Ҫȫ·��
	/// ֻ��Ҫ���ּ���
	/// ����Ҫȫ·��
	/// Ҳ����Ҫ��׺��
	///
	IPluginInterface* QueryPlugin(const MString& KeyName);

    ///
    /// \brief LoadPluginFromDll
    /// \param dllName
    /// \return
    ///
    IPluginInterface* LoadPluginFromDll(const MString& dllName);


	///
	/// ֱ��ע���������ڲ�����
	///
	void RegisterPlugin(const MString& KeyName, IPluginInterface* Plugin);
private:
    std::map<MString,IPluginInterface*>   mPlugins;
};

