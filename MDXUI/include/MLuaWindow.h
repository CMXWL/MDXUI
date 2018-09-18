

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef __MAPI_DEBUG__
#define LUA_DXUI_API 
#else
#if defined(DIRECTUI_EXPORTS)
#define LUA_DXUI_API __declspec(dllexport)
#else
#define LUA_DXUI_API __declspec(dllimport)
#endif
#endif 

namespace DxUI{
	class CDxWidget;
	class CDxApplication;
	class MSerialize;
	class CDxEffects;
}



using namespace DxUI;

struct lua_State;

//
// ���ڰ�װCDxWindow
//
struct CDxWidgetWrap{
	CDxWidget* p_window = nullptr;
};


struct CDxApplicationWrap{
	CDxApplication* p_App = nullptr;
};


struct MXmlWrap{
	MSerialize* p_Xml = nullptr;
};


struct CDxEffectsWrap{
	CDxEffects* p_Effects = nullptr;
};

//+------------------------------------
//
// ����lua��C++��������
//
//+------------------------------------
extern "C" LUA_DXUI_API  CDxApplication* __stdcall GetAppliactionFromLua(lua_State* L);
extern "C" LUA_DXUI_API  MSerialize* __stdcall GetXmlFromLua(lua_State* L);
extern "C" LUA_DXUI_API  CDxWidget*	__stdcall GetWidgetFromLua(lua_State* L);
