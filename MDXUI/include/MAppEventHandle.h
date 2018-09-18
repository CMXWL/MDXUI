

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include "DxConfig.h"

//
// Э�������źŵĶ�������Ǽ̳�������,��Ϊ��������ʹ��HAppManagerЭ������
//
class DXUI_API MAppEventHandle : public TL::MTLObject
{
public:
	MAppEventHandle();
	virtual ~MAppEventHandle();
    virtual void Destroy();

    ///
    /// \brief OnStart
    ///
    virtual void OnStart();

    ///
    /// \brief OnPause
    ///
    virtual void OnPause();

    ///
    /// \brief OnStop
    ///
    virtual void OnStop();
};

