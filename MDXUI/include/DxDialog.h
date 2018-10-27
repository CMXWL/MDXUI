

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
#include "DxWidget.h"


namespace DxUI{

	//+------------------------
	//
	// class CDxDialog
	//
	//+------------------------
	class DXUI_API CDxDialog :
		public CDxWidget
	{
		DECLARE_CLASS(CDxDialog)
	public:

		//
		// �Ի����˳���
		//
		enum{
			Rejected = 0,
			Accepted = 1,
		};
	public:
		CDxDialog();
		~CDxDialog();
		DXWindowType		GetWindowSelfDesc() const;
		HWND				GetRootHwnd() const;
		virtual void		SetParent(CDxWidget* parent);
		virtual CDxWidget*  GetParent();
		virtual CDxWidget*  GetDialogParent();
		virtual int			Exec();
		int					AsyncExec(); // �ڷ�GUI�߳�����Ҫ�����Ի�����ô��Ӧ��ʹ�øýӿ�

		//
		// �˳��Ի���
		// Reject ������ == Rejected
		// Accept ������ == Accepted
		// Quit ������ == quitcode
		//
		void				Reject();
		void				Accept();
		void				Quit(int quitcode);

		ID2D1HwndRenderTarget*	GetRenderTarget();
		int						GetRetrunCode() const;

		std::condition_variable* GetConditionVariable();
	protected:
		void				UpdateChildWindowPos();
		void				OnRendWindow(IPainterInterface* painter);

	protected:
		std::condition_variable mCondition;
		int						mReturnCode;
	};



	//
	// �����߳�ִ�жԻ���ʱ����ʹ������ĸ��������������Ի�
	//
	struct DXUI_API CDxDialogHelp{
		static int  AsyncRunDialog(CDxDialog* Dialog);
	};
	
}


