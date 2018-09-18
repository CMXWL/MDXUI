


///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once
#include <comdef.h>
#include "IObjectBase.h"


//
// ������ӿ�
// ģ����ʵ�ָ��� Ȼ���ͨ��ͨ�� CreateFactory �������䵼��
// CreateInstance ������������
//
class __declspec(uuid("F6B5D822-355D-45B1-A96A-2E162864D832")) IFactoryInterface : public virtual IObjectBase
{
public:
    IFactoryInterface(){}
    virtual ~IFactoryInterface(){}
    virtual HRESULT __stdcall CreateInstance(REFIID riid,void** pout) = 0;
};

//
// CreateInstance ʵ�ֺ�
//

#define MFACTORY_MAP_BEGIN virtual HRESULT __stdcall CreateInstance(REFIID riid,void** pout){\
    *pout = nullptr;

#define MFACTORY_MAP_END  return E_NOINTERFACE;\
    }

#define MFACTORY_INSTANCE(ClassName,iidforinstance) if(riid == iidforinstance){\
    ClassName* instance = new ClassName;\
    instance->QueryInterface(riid,pout);\
    instance->Release();\
    return S_OK;\
}
