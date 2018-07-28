#pragma once
#include "DxWindow.h"
#include "DxScrollBar.h"

namespace DxUI{
	class CDxListItem;
	//+------------------------------------
	//
	// 列表框
	// 不同于 CDxListWindow
	// 不使用数据模型
	//
	//+-------------------------------------
	class DXUI_API CDxListWidget :
		public CDxWindow
	{
		DECLARE_CLASS(CDxListWidget)
	public:
		CDxListWidget();
		~CDxListWidget();


		void				SetMultSelectedEnable(bool isMultSelected);
		void				AddItem(CDxListItem* item);
		bool				Empty() const;
		int					Size() const;
		void				RemoveItem(int index);

		CDxListItem*		FirstItem() const;
		CDxListItem*		LastItem() const;
		CDxListItem*		GetCurrentItem() const;
		CDxListItem*		GetItemByIndex(int index) const;
		CDxListItem*		GetItemByText(const MString& Text) const;
		int					GetIndexByItem(CDxListItem* item) const;

		TL::Vector<CDxListItem*> GetAllItem() const;
		TL::Vector<CDxListItem*> GetSelected() const;

		MString				GetItemText(int index) const;
		void				SetSelected(int index);

		void				Clear();

		void				OnResizeEvent();
		void				OnForceUpdate();
		virtual void		OnItemsChanged();


		bool				OnNotify(DXNotifyUI* NotifyEvent);
		void				ReceiveEvent(CDxUIEvent* e);


		void				OnRendWindow(IPainterInterface* painter);


		//
		// 当选择改变时触发该函数，该函数可通过TL::MTLDataBind::Connect 进行和外部通信
		// void testFun(int index1, int index2);
		// DxUI::CDxListWindow list;
		// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxListWindow, SelectedChanged, &list),TL::MSLOT(testFun));
		// 
		void				SelectedChanged(int curIndex, int preIndex, CDxWidget* sender);
		void				SelectedIterms(TL::Vector<int> selecteditems, CDxWidget* sender);


		int					GetMaxHeight() const; // 获取所需要的高度——不使用滚动条
		int					GetMaxWidth() const;  // 获取所需要的宽度——不使用滚动条


	protected:
		void				OnDealItemForDistance(int disx, int disy);
		void				UpdateScrollBarPos();

	private:
		CDxVerticalScrollBar		mVerticalScrollBar;
		CDxHorizonScrollBar			mHorizonScrollBar;
		TL::Vector<CDxListItem*>	mItems;
		int							mItemMaxWidth{ 0 };
		int							mItemMaxHeight{ 0 };
		int							mXCurrentOffset{ 0 };		// 当前偏移距离
		int							mYCurrentOffset{ 0 };		// 当前偏移距离
		int							mXMaxOffset{ 0 };			// 最大偏移距离
		int							mYMaxOffset{ 0 };			// 最大偏移距离
		int							mCurrentSelectedIndex{ -1 }; // 当前选中的索引
		TL::Vector<int>				mSelectedIndexs;             // 当前所有选中的索引
		bool						bIsMultSelectedEnabel{ false };
		CDxListItem*				pCurrentItem{ nullptr };	 // 当前选中的item
		
	};
}


