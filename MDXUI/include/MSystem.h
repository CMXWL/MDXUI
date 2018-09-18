

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Windows.h>
#include <MTLObject.h>
#include <map>

#ifdef __MAPI_DEBUG__
#define DXUI_SYS_API 
#else
#if defined(DIRECTUI_EXPORTS)
#define DXUI_SYS_API __declspec(dllexport)
#else
#define DXUI_SYS_API __declspec(dllimport)
#endif
#endif 


using mj::MString;
class IFactoryInterface;
namespace DxUI{
	class CDxWidget;
	struct IWindow;
}

class DXUI_SYS_API MSystem : public TL::MTLObject
{
    DECLARE_CLASS(MSystem)

    typedef DxUI::IWindow*(*CreateInstanceFun)();
    typedef IFactoryInterface*(*CreateFactoryFun)();

public:
    MSystem();
    ~MSystem();

    //
    // ���ⲿApp������
    //
    static void BindInstance(MSystem* __MSystem);

    //
    // ����App�����Ψһʵ��
    //
    static MSystem* Instance();

    //
    // ����App�����ʵ��
    //
    static void DestroyInstance();


    //
    // ��dllģ���м��ش���ģ��
    //
	static DxUI::IWindow* LoadWindowFromDll(const MString& dllname);


    static IFactoryInterface* CreateFactory(const MString& dllname);

    //
    // дע���
    //
    static bool Register(HKEY syskey,
                         const MString& usekey,
                         const MString& subkey,
                         const MString& value);

    static MString ReadRegister(HKEY syskey,
                                const MString& usekey,
                                const MString& subkey);

    //
    // ж��ע���
    //
    static bool UnRegister(HKEY syskey,const MString& useKey);

private:
    static MSystem*                                     pSystemSelf;
    static bool                                         bInstanceIsThis;
    static std::map<MString,CreateInstanceFun>			mModuleFuns;
    static std::map<MString,CreateFactoryFun>			mFactoryFuns;
};

