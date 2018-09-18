

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
	class MSerialize;
}

//
// class MAppDataUnit
// ���ݵ�Ԫ
//
class DXUI_API MAppDataUnit
{
public:
	MAppDataUnit();
	~MAppDataUnit();

	///
	/// \brief ValidateData
	/// \return
	/// У�����ݵ���Ч��
	///
	virtual bool ValidateData(){ return true; }

	///
	/// \brief InitData
	/// ��ʼ������
	///
	virtual void InitData(){}

	///
	/// \brief InitConnect
	/// ��ʼ���ź�����
	///
	virtual void InitConnect(){}


	///
	/// \brief ToString
	/// \return
	/// ���ýӿ�
	/// �������͵�һЩ�����Ϣ
	/// ����˵�����Ͳ���ʧ�ܵ�ʱ����Ҫ֪������һ�����ͳ���
	///
	virtual MString ToString(){ return "HAppDataBase"; }



	///
	/// \brief SerialToFile
	/// \param Serial
	/// ������д�� MSerialize
	///
	virtual void SerialToFile(DxUI::MSerialize* Serial){}

	///
	/// \brief SerialFromFile
	/// \param Serial
	/// �� MSerialize �ж�ȡ����
	///
	virtual void SerialFromFile(DxUI::MSerialize* Serial){}

};