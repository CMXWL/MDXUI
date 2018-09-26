
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
#include "MSerialize.h"

class MAppDataUnit;
class MProjectType;

class DXUI_API MAppData
{
public:
	MAppData();
	~MAppData();

	///
	/// \brief Attach
	/// \param __data
	/// �����ݹ�����ϵͳ�����
	///
	void Attach(MAppDataUnit* __data);

	///
	/// \brief Dettach
	/// \param __data
	/// �����ݴ�ϵͳ������Ƴ�
	///
	void Dettach(MAppDataUnit* __data);

	///
	/// \brief ValidateData
	/// \return
	/// У�����ݵ���Ч��
	///
	virtual bool ValidateData();

	///
	/// \brief Destroy
	/// ��������
	///
	virtual void Destroy();

	///
	/// \brief InitData
	/// \param __Type
	/// \return
	/// ��ʼ������,������Ǳ��뽨�鲻Ҫ��д�ú���,������Ҫ���и������ݵĳ�ʼ��������д InitDataAdd
	///
	virtual bool InitData(MProjectType* __Type);

	///
	/// \brief InitDataAdd
	/// \param __Type
	/// \return
	/// ��ʼ������
	/// ���಻����д�����InitData,�б�Ҫ�Ļ�������д InitDataAdd
	///
	virtual bool InitDataAdd(MProjectType* __Type);

	///
	/// \brief InitConnect
	/// ��ʼ���ź�����
	///
	virtual void InitConnect();

	///
	/// \brief SerialToFile
	/// \param Serial
	/// ����ϵͳ��ܹ�ϵ����������д��MSerialize
	/// MSerialize �� MSerialize
	///
	virtual void SerialToFile(DxUI::MSerialize* Serial);

	///
	/// \brief SerialFromFile
	/// \param Serial
	/// �� MSerialize �ж�ȡ����
	///
	virtual void SerialFromFile(DxUI::MSerialize* Serial);

	///
	/// \brief ToString
	/// \return
	/// �����ӿ�
	///
	virtual MString ToString(){ return "MAppData"; }


	///
	/// \brief GetProjectType
	/// \return
	/// ���ع��̵Ĳ�������
	///
	virtual MString GetProjectType();


	///
	/// \brief
	/// \return
	/// ���ع��̵���������Ϣ
	///
	virtual TL::Map<MString, TL::Vector<std::pair<MString,MString>>> GetProjectProperty();


	///
	/// \brief Clear
	/// ����󶨵�����
	///
	void Clear();

protected:
	TL::Vector<MAppDataUnit*>		mNeedOpData;

};

