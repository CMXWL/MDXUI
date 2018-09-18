
///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <Windows.h>
#include <MSingleton.h>
#include "MString.h"
#include "DxConfig.h"
#include <condition_variable>
#include <map>
using mj::MString;
class IFactoryInterface;


namespace DxUI{
	class IWindow;
	class DXUI_API CDxApplication 
	{
	public:
		typedef IWindow*(*CreateInstanceFun)();
		typedef IFactoryInterface*(*CreateFactoryFun)();

		//
		// CreateInstance
		// CreateFactory
		// ����������������������ģ���ʹ������Ľӿڼ��ش��ڻ��߹�������
		//
	public:
		CDxApplication(HINSTANCE __hInstance = nullptr);
		~CDxApplication();

		static CDxApplication* InstanceWithArgs(HINSTANCE __hInstance);
		static CDxApplication* Instance();
		static void Destroy();

		static void			 SetFont(const MString& fontName, unsigned fSize, bool isBold = false, bool isItalic = false);
		static HINSTANCE	 GetHInstance();
		static HFONT		 GetFont();
		static DXFontInfo	 GetFontInfo();
		static MString		 GetExePath();
		static MString		 GetCurrentTime();
		static MString		 GetUUIDStr();


		//
		// ��dllģ���м��ش���ģ��
		//
		static IWindow* LoadWindowFromDll(const MString& dllname);
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
		static bool UnRegister(HKEY syskey, const MString& useKey);


		//
		// ��ȡ��ǰ�߳�id
		//
		static unsigned CurrentThreadID();


		//
		// ��ȡ���߳�id
		//
		static unsigned MainThreadID();

		//
		// ��������
		//
		static void SetActiveHWND(HWND  hwnd);
		static HWND GetActiveHWND();



		//
		// ��Ϣѭ��
		//
		void				 Quit();
		int					 Run();


	private:
		bool				bIsDone{ false };
		static HINSTANCE	hInstance;
		static DXFontInfo	sDefaultFontInfo;
		static HFONT		sDefaultFont;

	private:
		static std::map<MString, CreateInstanceFun> mModuleFuns;
		static std::map<MString, CreateFactoryFun>  mFactoryFuns;

	protected:
		static CDxApplication*	 __sPtr;
		static unsigned  mMainThreadID;
		static std::condition_variable	s_AppCondition;
		static HWND     m_ActiveHwnd;
	};
}

