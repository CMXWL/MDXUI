

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

namespace DxUI{
	class MSerialize;
}

//-----------------------------
// ����������
// �Լ��Թ�����Ϣ�Ĵ���
//-----------------------------

class DXUI_API MProjectType
{
public:
	MProjectType();
	virtual ~MProjectType();

	virtual void InitProject();

	//
	// �����Լ�
	//
	virtual MProjectType* CreateThis();
	virtual void Destroy();

	//-----------------------------------------------------
	// SetProjectInfo   ���ù�����Ϣ������·������������ ���磺
	//                  ������Ϊ Test
	//                  ·��Ϊ   E:/Project
	//                  ��ô���õľ��� E:/Project/Test
	// SetProjectType   ��������ʹ���޷�����������ʾ
	//                  �ô��ǿ��Է���ö��
	//                  �ַ���ת��������Ҳ�ܷ���
	// CreateProject    �����úù������ͺ͹�����Ϣ��Ϳ��Դ���������
	//-------------------------------------------------------
	void SetProjectInfo(const MString& projectinfo);
	void SetProjectType(unsigned type);
	void SetProjectType(const MString& strType);
	void SetModuleName(const MString& moduleName);


	//-------------------------------------------------------
	// ���б�Ҫ������д�ú���
	// CreateProject �����½�����
	// OpenProject   ���ڴ򿪹���
	// DealProject   �������Ϊ֮����Ҫ�����һЩ�ļ���Ϣ
	//    ����log�ļ������¶�λ
	//    config�ļ������¶�λ
	//    data�ļ������¶�λ��
	//    NewProjName �ɴ���ɲ�����׺
	//    ����׺�����������ļ�����
	//    ������׺�����������ļ��д���
	//-------------------------------------------------------
	virtual bool CreateProject();
	virtual bool OpenProject(const MString& FileName);
	virtual bool DealProject(const MString& NewProjName);

	virtual bool ClearProject();

	//------------------------------------------------------
	// �����Ƿ��Ѿ�����
	//------------------------------------------------------
	bool HaveBeenCreated();

	//---------------------------------------
	// GetProjectName ���ص�ֻ�ǹ��̵�����
	// GetProjectPath ���ص��ǹ������ڵ�ȫ·��
	// LoggerFile     ���ص�ǰ���̵�Logger�ļ�
	// ConfigFile     ���ص�ǰ���̵�Config�ļ�
	// DataFolderPath ���ش��浱ǰ�������ݵ�·��
	// GetProjectType ��������ʹ���޷����������궨
	// ModuleName     ����ʵ����ģ����
	// DataHeaderFile ��¼���ݵ�ͷ�ļ�
	//---------------------------------------
	const MString& GetProjectName() const;
	const MString& GetProjectPath() const;
	const MString& LoggerFile() const;
	const MString& ConfigFile() const;
	const MString& DataFolderPath() const;
	const MString& ModuleName() const;
	const MString& DataHeaderFile() const;

	//----------------------------------
	// ��ȡ�������л���ָ��
	//----------------------------------
	DxUI::MSerialize* AppSerailPtr() const;

	unsigned GetProjectType();

	//
	// �޸Ĺ�����չ��
	//
	static void RegisterProjectExtension(const MString& extension);
	static MString ProjectExtension();

private:
	bool            bIsCreate{ false };
	MString         mProjectInfo; // ���湤�̵�ȫ������·�������������
	unsigned        mProjectType; // �޹���ʱ��ֵΪ-1
	MString         mProjectName;
	MString         mProjectPath;

	MString         mLoggerFile;  // ��¼logger�ļ�
	MString         mConfigFile;  // ��¼config�ļ�
	MString         mDataFolder;  // ��¼�������ݵ��ļ���·��
	MString         mDataHeaderFile; // ��¼���ݵ�ͷ�ļ�

	MString         mModuleName;  // �������̵�ģ����

	DxUI::MSerialize*    pAppSerial;      // ����������,��Ҫ���ڶ��̺ʹ���

	static MString  mExtensionName;  // ������չ��
};

