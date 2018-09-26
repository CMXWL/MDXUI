

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
#include "DxLabel.h"
#include "DxScrollBar.h"
#include "DxDataMode.h"
#include "DxWindow.h"


namespace DxUI{

	class CDxListItem;

	//+------------------------------------
	//
	// �б��
	//
	//+-------------------------------------
	class DXUI_API CDxListWindow :
		public CDxWindow
	{
		DECLARE_CLASS(CDxListWindow)
	public:
		CDxListWindow();
		~CDxListWindow();

	
		void				SetMultSelectedEnable(bool isMultSelected);
		void				SetItemDataFactory(CDxListDataMode* item);
		void				SetItemFactory(CDxListItem* item);


		void				AddItem(const MString& itemText);
		void				AddItem(const MString& Icon,const MString& itemText);
		void				AddItems(const TL::Vector<MString>& items);
		void				AddItemsWithIco(const TL::Vector<std::pair<MString, MString>>& items);
		void				AddAnyItem(const mj::MAny& any, const MString& itemText);

		bool				Empty() const;
		int					Size() const;
		bool				IsContainText(const MString& Text); 


		void				RemoveItem(int index);


		CDxListDataMode*	FirstItem() const;
		CDxListDataMode*	LastItem() const;
		CDxListDataMode*	GetCurrentItem() const;
		CDxListDataMode*	GetItemByIndex(int index) const;
		CDxListDataMode*	GetItemByText(const MString& Text) const;
		int					GetIndexByItem(CDxListDataMode* item) const;
		int					GetCurrentIndex() const;
		TL::Vector<MString> GetAllItem() const;
		TL::Vector<int>     GetSelectedIndex() const;
		TL::Vector<MString> GetSelected() const;
		TL::Vector<MString> GetAllItem();
		TL::Vector<MString> GetSelected();

		MString				GetItemText(int index) const;
		void				SetSelected(int index);
		void				DeSelected(int index);
		void				SetSelected(const TL::Vector<int>& indexs);
		void				SelectedAll();
		void				DeSelectedAll();


		void				IncreaseIndex(int index);
		void				DecreaseIndex(int index);

		void				Clear();

		void				OnResizeEvent();
		virtual void		OnItemsChanged();


		bool				OnNotify(DXNotifyUI* NotifyEvent);
		void				ReceiveEvent(CDxUIEvent* e);


		void				OnRendWindow(IPainterInterface* painter);


		//
		// ��ѡ��ı�ʱ�����ú������ú�����ͨ��TL::MTLDataBind::Connect ���к��ⲿͨ��
		// void testFun(int index1, int index2);
		// DxUI::CDxListWindow list;
		// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxListWindow, SelectedChanged, &list),TL::MSLOT(testFun));
		// ItemChecked ���ڿ�ѡ�е�item��˵�����и��ź�
		// 
	msignals:
		void				SelectedChanged(int curIndex, int preIndex,CDxWidget* sender); 
		void				SelectedIterms(TL::Vector<int> selecteditems, CDxWidget* sender);
		void				ItemChecked(bool isChecked,int curIndex, CDxWidget* sender);
		void				ItemClicked(int index, MString Text, CDxWidget* sender);
		void				ItemClickedPoint(int index, MString Text,POINT pt, CDxWidget* sender);
		void				DoubleClicked(int index, MString Text, CDxWidget* sender);

		TL::MTLVoidEvent<int, int, CDxWidget*>  Event_SelectedChanged;
		TL::MTLVoidEvent<TL::Vector<int>, CDxWidget*> Event_SelectedIterms;
		TL::MTLVoidEvent<bool, int, CDxWidget*> Event_ItemChecked;
		TL::MTLVoidEvent<int, MString, CDxWidget*> Event_ItemClicked;
		TL::MTLVoidEvent<int, MString, POINT, CDxWidget*> Event_ItemClickedPoint;
		TL::MTLVoidEvent<int, MString, CDxWidget*> Event_DoubleClicked;

	public:
		int					GetMaxHeight() const; // ��ȡ����Ҫ�ĸ߶ȡ�����ʹ�ù�����
		int					GetMaxWidth() const;  // ��ȡ����Ҫ�Ŀ�ȡ�����ʹ�ù�����


	protected:
		void				OnDealItemForDistance(int disx,int disy);
		void				UpdateScrollBarPos();
		void				OnItemChecked(bool isChecked, CDxWidget* sender);


	private:
		CDxHorizonScrollBar			mHorizonScrollBar;
		CDxVerticalScrollBar		mVerticalScrollBar;

		TL::Vector<CDxListDataMode*> mListDatas;
		TL::Vector<CDxListItem*>	mItems;
		std::map<CDxListItem*, unsigned> mWindowMapToData; // ��ͼ�����ݵ�ӳ��

		CDxListDataMode*			pDataFactory{ nullptr };
		CDxListItem*				pItemFactory{ nullptr };
		CDxListItem*				pCurrentItem{ nullptr };
		int							mItemMaxWidth{ 0 };
		int							mItemMaxHeight{ 0 };
		int							mXCurrentOffset{ 0 };		// ��ǰƫ�ƾ���
		int							mYCurrentOffset{ 0 };		// ��ǰƫ�ƾ���
		int							mXMaxOffset{ 0 };			// ���ƫ�ƾ���
		int							mYMaxOffset{ 0 };			// ���ƫ�ƾ���

		int							mCurrentSelectedIndex{ -1 }; // ��ǰѡ�е�����
		TL::Vector<int>				mSelectedIndexs;             // ��ǰ����ѡ�е�����
		bool						bIsMultSelectedEnabel{ false };
	};



	//+---------------------------------
	//
	// ������ͷ
	//
	//+-----------------------------------
	class DXUI_API CDxListWindowEx : public CDxWindow{
		DECLARE_CLASS(CDxListWindowEx)
	public:
		CDxListWindowEx();
		~CDxListWindowEx();
		void				SetMultSelectedEnable(bool isMultSelected);
		void				SetItemDataFactory(CDxListDataMode* item);
		void				SetItemFactory(CDxListItem* item);


		void				AddItem(const MString& itemText);
		void				AddItem(const MString& Icon, const MString& itemText);
		void				AddItems(const TL::Vector<MString>& items);
		void				AddItemsWithIco(const TL::Vector<std::pair<MString, MString>>& items);
		void				AddAnyItem(const mj::MAny& any, const MString& itemText);

		bool				Empty() const;
		int					Size() const;
		bool				IsContainText(const MString& Text);

		void				RemoveItem(int index);


		CDxListDataMode*	FirstItem() const;
		CDxListDataMode*	LastItem() const;
		CDxListDataMode*	GetCurrentItem() const;
		CDxListDataMode*	GetItemByIndex(int index) const;
		CDxListDataMode*	GetItemByText(const MString& Text) const;
		int					GetIndexByItem(CDxListDataMode* item) const;
		int					GetCurrentIndex() const;
		TL::Vector<MString> GetAllItem() const;
		TL::Vector<MString> GetSelected() const;
		TL::Vector<int>     GetSelectedIndex() const;

		MString				GetItemText(int index) const;
		void				SetSelected(int index);
		void				DeSelected(int index);
		void				SetSelected(const TL::Vector<int>& indexs);
		void				SelectedAll();
		void				DeSelectedAll();

		void				IncreaseIndex(int index);
		void				DecreaseIndex(int index);

		void				Clear();

		void				SetText(const MString& Text);

		//
		// ѡ�����ı�ʱ�����źŻᱻ����
		// ItemChecked ���item��ѡʱѡ��״̬�����ı�ʱ���͸��ź�
		// ItemClicked item�����ʱ���͸��ź�
		// ItemClickedPoint �Ҽ����ʱ���͸��ź�
		// DoubleClicked ˫��ʱ���͸��ź�
		//
	msignals:
		void				SelectedChanged(int curIndex, int preIndex, CDxWidget* sender);
		void				SelectedIterms(TL::Vector<int> selecteditems, CDxWidget* sender);
		void				ItemChecked(bool isChecked, int curIndex, CDxWidget* sender);
		void				ItemClicked(int index, MString Text, CDxWidget* sender);
		void				ItemClickedPoint(int index, MString Text, POINT pt, CDxWidget* sender);
		void				DoubleClicked(int index, MString Text, CDxWidget* sender);


		TL::MTLVoidEvent<int, int, CDxWidget*>  Event_SelectedChanged;
		TL::MTLVoidEvent<TL::Vector<int>, CDxWidget*> Event_SelectedIterms;
		TL::MTLVoidEvent<bool, int, CDxWidget*> Event_ItemChecked;
		TL::MTLVoidEvent<int, MString, CDxWidget*> Event_ItemClicked;
		TL::MTLVoidEvent<int, MString, POINT, CDxWidget*> Event_ItemClickedPoint;
		TL::MTLVoidEvent<int, MString, CDxWidget*> Event_DoubleClicked;

	public:
		int					GetMaxHeight() const; // ��ȡ����Ҫ�ĸ߶ȡ�����ʹ�ù�����
		int					GetMaxWidth() const;  // ��ȡ����Ҫ�Ŀ�ȡ�����ʹ�ù�����

		void				OnItemsChanged();
		void				OnRendWindow(IPainterInterface* painter);

	private:
		CDxListWindow*		p_ListWindow{ nullptr };
		CDxLabel*			p_HeaderLabel{ nullptr };
	};
}


