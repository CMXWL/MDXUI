

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include "DxConfig.h"
#include  "MAppDataUnit.h"

//
// class MAppFrameData
//
class DXUI_API MAppFrameData
{
public:
	MAppFrameData();
	virtual ~MAppFrameData();

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
    /// \brief InitData
    /// \param __Type
    /// \return
    /// ��ʼ������,������Ǳ��뽨�鲻Ҫ��д�ú���,������Ҫ���и������ݵĳ�ʼ��������д InitDataAdd
    ///
    virtual bool InitData();

    ///
    /// \brief InitDataAdd
    /// \param __Type
    /// \return
    /// ��ʼ������
    /// ���಻����д�����InitData,�б�Ҫ�Ļ�������д InitDataAdd
    ///
    virtual bool InitDataAdd();

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
    virtual MString ToString() {return "HAppFrameData";}

protected:
	TL::Vector<MAppDataUnit*> mNeedOpData;
};

