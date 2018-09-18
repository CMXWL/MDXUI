

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include "DxConfig.h"

class MProjectType;
///
/// \brief The IDealDataInterface class
/// �������ݽӿ���
///
class DXUI_API IDealDataInterface : public TL::MTLObject
{
public:
    IDealDataInterface();
    ~IDealDataInterface();

public:
    virtual MString ToString() const;

    ///
    /// \brief Init
    /// \param __Type
    /// ��ʼ��
    ///
	virtual void Init(MProjectType* __Type);

    ///
    /// \brief Destroy
    /// ���������Ϣ
    ///
    virtual void Destroy();

    ///
    /// \brief PushMessage
    /// \param msg
    ///
    virtual void PushMessage(const MString& msg);
};


