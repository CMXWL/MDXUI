

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

