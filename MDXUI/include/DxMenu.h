

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
#include "DxWindow.h"

namespace DxUI{
	//+--------------------------------------
	//
	// CDxMenu  菜单窗口
	// 一个弹出窗口
	//
	//+--------------------------------------
	class CDxAction;
	class DXUI_API CDxMenu :
		public CDxWindow
	{
		DECLARE_CLASS(CDxMenu)
	public:
		CDxMenu();
		~CDxMenu();
		DXWindowType	GetWindowSelfDesc() const;
		HWND			GetRootHwnd() const;


		virtual CDxAction*		AddAction(const MString& Icon, const MString& Text);
		virtual CDxAction*		AddAction(const MString& Text);
		virtual CDxAction*		AddCheckableAction(const MString& Text);

		virtual void			AddSpliter();

		virtual CDxMenu*	AddMenu(const MString& Icon, const MString& Text);
		virtual CDxMenu*	AddMenu(const MString& Text);


		CDxAction*		GetAction(const MString& Name) const;
		CDxMenu*		GetMenu(const MString& Name) const;

		void			SetGeomety(const DxRectI& rc);
		void			SetSize(int w, int h);
		void			ReSize(unsigned w, unsigned h);
		void			CreateHwnd(HWND parent);
		void			SetFocus();
		void			KillFocus();
		CDxWidget*		HitTest(int x, int y);
		bool			PointInArea(int x, int y);
		void			UpdateArea();
		bool			OnNotify(DxUI::DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);
		ID2D1HwndRenderTarget* GetRenderTarget();
		CDxWidget*		GetParent();
		void			Show();
		int				Exec();
		void			SetVisible(bool isVisible);
		void			Exec(int x, int y);

	msignals:
		void			Clicked(bool isClicked, CDxWidget* sender);
		TL::MTLVoidEvent<bool, CDxWidget*> Event_Clicked;


	protected:
		void			UpdateChildWindowPos();

		TL::Vector<CDxAction*>	mActions;
		TL::Vector<CDxMenu*>	mMenus;	
	};
}


