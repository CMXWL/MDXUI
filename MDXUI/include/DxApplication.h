
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
#include <WinMain.hpp>
#include <Windows.h>
#include <MSingleton.h>
#include "MString.h"
#include "DxConfig.h"
#include <condition_variable>
#include <map>
#include <MTLSlotEx.h>
#include <MMultType.h>
#include <MTLEvent.h>

using mj::MString;
class IFactoryInterface;

namespace TL{
	template<class...Args>
	class MTLAsyncVoidEvent;
}

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
		// ���߳�ʱ�����Ҫ���������ݵ����߳��п���ʹ�øýӿ�
		// ע��������ݹ��̵���Ч��
		//
		static void PostMainThread(ulong message, ulong wParam, ulong lParam);

		//
		// �������߳��������Ҫ�����߳���ִ�к���ʱ����ʹ������Ľӿ�
		//
		static void AsyncRunFunction(std::function<void()> Fun);
		static void AsyncRunFunction(void(*Fun)(TL::MTLObject*),TL::MTLObject* Obj);


		//
		// Args ��ǰ���֧��4��
		//
		template<class T,class...Args>
		static void AsyncRunFunction(void(*fun)(T, Args...), const T& val, const Args&...args){
			std::function<void()> Fun = TL2::MSLOT(fun, val, args...);
			AsyncRunFunction(Fun);
		}

		template<class T, class...Args>
		static void AsyncRunFunction(void(T::*fun)(Args...), T* obj, const Args&...args){
			std::function<void()> Fun = TL2::MSLOT(fun, obj, args...);
			AsyncRunFunction(Fun);
		}

		template<class T>
		static void AsyncRunFunction(void(T::*fun)(), T* obj){
			std::function<void()> Fun = TL::MSLOT(fun, obj);
			AsyncRunFunction(Fun);
		}

		template<class...Args>
		static void AsyncRunFunction(TL::MTLAsyncVoidEvent<Args...>& obj, const Args&...args){
			typedef TL::MTLAsyncVoidEvent<Args...> Type;
			Type* Ptr = &obj;
			AsyncRunFunction(&Type::Run, Ptr, args...);
		}


	
		//
		// �����֪�����ʹ�õ�ʱ�����ò�Ҫʹ��
		//
		static void RunQueryFunction(MSG msg);

		static void SetAppHintSize(const MString& FileName);
		static SIZE GetAppHintSize(const MString& ClassName);



		//
		// ��Ϣѭ��
		//
		void				 Quit();
		int					 Run();


		//
		// ���������ھ��
		//
		void				SaveMainHwnd(HWND hwnd);
		HWND				GetMainHwnd() const;

	msignals:
		//
		// �Զ����¼����ݳ���
		// �����ֱ��� message,wParam,lParam
		//
		static TL::MTLVoidEvent<ulong, ulong, ulong>  Event_Message;


	private:
		bool				bIsDone{ false };
		HWND				mMainHwnd{ nullptr };
		static HINSTANCE	hInstance;
		static DXFontInfo	sDefaultFontInfo;
		static HFONT		sDefaultFont;

	private:
		static std::map<MString, CreateInstanceFun> mModuleFuns;
		static std::map<MString, CreateFactoryFun>  mFactoryFuns;
		static std::map<MString, SIZE>   s_ControlHintSize;
	protected:
		static CDxApplication*	 __sPtr;
		static unsigned  mMainThreadID;
		static std::condition_variable	s_AppCondition;
		static HWND     m_ActiveHwnd;
		
	};

}


namespace TL{
	//
	// ʹ��operator()�����������Ӻ�����Զ�����߳���ִ��
	//
	template<class...Args>
	class MTLAsyncVoidEvent : public MTLVoidEvent<Args...>{
	public:
		MTLAsyncVoidEvent(){}
		virtual ~MTLAsyncVoidEvent(){}

		void operator()(const Args&... arg){
			AsynRun(arg...);
		}

		void Run(Args... arg){
			MTLVoidEvent<Args...>::operator()(arg...);
		}

		void AsynRun(const Args&... arg){
			if (DxUI::CDxApplication::MainThreadID() == DxUI::CDxApplication::CurrentThreadID()){
				Run(arg...);
			}
			else{
				DxUI::CDxApplication::AsyncRunFunction(&MTLAsyncVoidEvent::Run, this, arg...);
			}
		}
	};
}