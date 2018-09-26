

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
#include "DxScrollBar.h"
#include "DxWindow.h"

namespace DxUI{

	class CDxTreeItem;
	class CDxLabel;
	//+------------------------------------
	//
	// ���ṹ
	// class CDxTreeWindow
	//
	//+-------------------------------------
	class DXUI_API CDxTreeWindow :
		public CDxWindow
	{
		DECLARE_CLASS(CDxTreeWindow)
	public:
		CDxTreeWindow();
		~CDxTreeWindow();

		DXWindowType			GetWindowSelfDesc() const;
		void					AddItem(CDxTreeItem* item);
		CDxTreeItem*			AddItem(const MString& item);
		CDxTreeItem*			AddItem(const MString& icon, const MString& item);
		void					Clear();

		void					RemoveItem(CDxTreeItem* item);
		void					RemoveItemByText(const MString& item);
		void					RemoveItemByIndex(unsigned index);
		CDxTreeItem*			GetItemByIndex(unsigned index);

		unsigned				Size();
		unsigned				Counts();

		void					SetSelectedByIndex(int index);

		void					OnResizeEvent();
		virtual void			OnItemsChanged();
		bool					OnNotify(DXNotifyUI* NotifyEvent);
		void					ReceiveEvent(CDxUIEvent* e);
		void					OnRendWindow(IPainterInterface* painter);

		//
		// �������itemʱ�������¼����ú�����ͨ��TL::MTLDataBind::Connect ���к��ⲿͨ��
		// void testFun(CDxTreeItem item);
		// DxUI::CDxListWindow list;
		// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxListWindow, ClickedItem, &list),TL::MSLOT(testFun));
		// 
	msignals:
		void					ClickedItem(CDxTreeItem* item,CDxWidget* sender); // ����
		void					DBClickedItem(CDxTreeItem* item, CDxWidget* sender);// ˫��
		void					RBClickedItem(CDxTreeItem* item, POINT pt,CDxWidget* sender);// �Ҽ�

		TL::MTLVoidEvent<CDxTreeItem*, CDxWidget*> Event_ClickedItem;
		TL::MTLVoidEvent<CDxTreeItem*, CDxWidget*> Event_DBClickedItem;
		TL::MTLVoidEvent<CDxTreeItem*, POINT, CDxWidget*> Event_RBClickedItem;

	protected:
		void					UpdateChildWindowPos();
		void					UpdateViewWindow();
		void					OnDealItemForDistance(unsigned xdis, unsigned ydis);
		void					UpdateScrollBarPos();

	private:
		CDxHorizonScrollBar			mHorizonScrollBar;
		CDxVerticalScrollBar		mVerticalScrollBar;
		TL::Vector<CDxTreeItem*>	mItems;  // ������¼root�ڵ��item
		TL::Vector<CDxTreeItem*>    mAllItems; // ��¼���е�item����root
		CDxTreeItem*				pCurrentItem{ nullptr };
		int							mItemMaxWidth{ 0 };
		int							mItemMaxHeight{ 0 };
		int							mXCurrentOffset{ 0 };
		int							mYCurrentOffset{ 0 };
		int							mXMaxOffset{ 0 };
		int							mYMaxOffset{ 0 };
		
	};


	//
	// CDxTreeWindowEx
	// ��ͷ��Ϣ��TreeWindow
	//
	class DXUI_API CDxTreeWindowEx : public CDxWindow{
		DECLARE_CLASS(CDxTreeWindowEx)
	public:
		CDxTreeWindowEx();
		~CDxTreeWindowEx();
		DXWindowType			GetWindowSelfDesc() const;

		void					RemoveItem(CDxTreeItem* item);
		void					RemoveItemByText(const MString& item);
		void					RemoveItemByIndex(unsigned index);
		CDxTreeItem*			GetItemByIndex(unsigned index);

		unsigned				Size();
		unsigned				Counts();
		void					SetSelectedByIndex(int index);
		void					SetText(const MString& Text);
		MString&				GetText();
		const MString&			GetText() const;
		void					AddItem(CDxTreeItem* item);
		CDxTreeItem*			AddItem(const MString& item);
		CDxTreeItem*			AddItem(const MString& icon, const MString& item);
		void					Clear();
		void					ClickedItem(CDxTreeItem* item, CDxWidget* sender); // ����
		void					DBClickedItem(CDxTreeItem* item, CDxWidget* sender);// ˫��
		void					RBClickedItem(CDxTreeItem* item, POINT pt, CDxWidget* sender);// �Ҽ����
	private:
		CDxTreeWindow*			p_TreeWindow{ nullptr };
		CDxLabel*				p_HeaderLabel{ nullptr };
	};
}

