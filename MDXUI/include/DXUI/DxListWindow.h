#pragma once
#include "DxLabel.h"
#include "DxScrollBar.h"
#include "DxDataMode.h"
#include "DxWindow.h"


namespace DxUI{

	class CDxListItem;

	//+------------------------------------
	//
	// 列表框
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
		TL::Vector<MString> GetAllItem() const;
		TL::Vector<int>     GetSelectedIndex() const;
		TL::Vector<MString> GetSelected() const;
		TL::Vector<MString> GetAllItem();
		TL::Vector<MString> GetSelected();

		MString				GetItemText(int index) const;
		void				SetSelected(int index);
		void				SetSelected(const TL::Vector<int>& indexs);
		void				SelectedAll();
		void				DeSelectedAll();

		void				Clear();

		void				OnResizeEvent();
		virtual void		OnItemsChanged();


		bool				OnNotify(DXNotifyUI* NotifyEvent);
		void				ReceiveEvent(CDxUIEvent* e);


		void				OnRendWindow(IPainterInterface* painter);


		//
		// 当选择改变时触发该函数，该函数可通过TL::MTLDataBind::Connect 进行和外部通信
		// void testFun(int index1, int index2);
		// DxUI::CDxListWindow list;
		// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxListWindow, SelectedChanged, &list),TL::MSLOT(testFun));
		// ItemChecked 对于可选中的item来说可以有该信号
		// 
	msignals:
		void				SelectedChanged(int curIndex, int preIndex,CDxWidget* sender); 
		void				SelectedIterms(TL::Vector<int> selecteditems, CDxWidget* sender);
		void				ItemChecked(bool isChecked,int curIndex, CDxWidget* sender);
		void				ItemClicked(int index, MString Text, CDxWidget* sender);
		void				ItemClickedPoint(int index, MString Text,POINT pt, CDxWidget* sender);
		void				DoubleClicked(int index, MString Text, CDxWidget* sender);


	public:
		int					GetMaxHeight() const; // 获取所需要的高度——不使用滚动条
		int					GetMaxWidth() const;  // 获取所需要的宽度——不使用滚动条


	protected:
		void				OnDealItemForDistance(int disx,int disy);
		void				UpdateScrollBarPos();
		void				OnItemChecked(bool isChecked, CDxWidget* sender);


	private:
		CDxHorizonScrollBar			mHorizonScrollBar;
		CDxVerticalScrollBar		mVerticalScrollBar;

		TL::Vector<CDxListDataMode*> mListDatas;
		TL::Vector<CDxListItem*>	mItems;
		std::map<CDxListItem*, unsigned> mWindowMapToData; // 视图到数据的映射

		CDxListDataMode*			pDataFactory{ nullptr };
		CDxListItem*				pItemFactory{ nullptr };
		CDxListItem*				pCurrentItem{ nullptr };
		int							mItemMaxWidth{ 0 };
		int							mItemMaxHeight{ 0 };
		int							mXCurrentOffset{ 0 };		// 当前偏移距离
		int							mYCurrentOffset{ 0 };		// 当前偏移距离
		int							mXMaxOffset{ 0 };			// 最大偏移距离
		int							mYMaxOffset{ 0 };			// 最大偏移距离

		int							mCurrentSelectedIndex{ -1 }; // 当前选中的索引
		TL::Vector<int>				mSelectedIndexs;             // 当前所有选中的索引
		bool						bIsMultSelectedEnabel{ false };
	};



	//+---------------------------------
	//
	// 带个表头
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
		TL::Vector<MString> GetAllItem() const;
		TL::Vector<MString> GetSelected() const;
		TL::Vector<int>     GetSelectedIndex() const;

		MString				GetItemText(int index) const;
		void				SetSelected(int index);

		void				SetSelected(const TL::Vector<int>& indexs);
		void				SelectedAll();
		void				DeSelectedAll();

		void				Clear();

		void				SetText(const MString& Text);

		//
		// 选择发生改变时下面信号会被触发
		// ItemChecked 如果item可选时选中状态发生改变时发送该信号
		// ItemClicked item被点击时发送该信号
		// ItemClickedPoint 右键点击时发送该信号
		// DoubleClicked 双击时发送该信号
		//
	msignals:
		void				SelectedChanged(int curIndex, int preIndex, CDxWidget* sender);
		void				SelectedIterms(TL::Vector<int> selecteditems, CDxWidget* sender);
		void				ItemChecked(bool isChecked, int curIndex, CDxWidget* sender);
		void				ItemClicked(int index, MString Text, CDxWidget* sender);
		void				ItemClickedPoint(int index, MString Text, POINT pt, CDxWidget* sender);
		void				DoubleClicked(int index, MString Text, CDxWidget* sender);

	public:
		int					GetMaxHeight() const; // 获取所需要的高度——不使用滚动条
		int					GetMaxWidth() const;  // 获取所需要的宽度——不使用滚动条

		void				OnItemsChanged();
		void				OnRendWindow(IPainterInterface* painter);

	private:
		CDxListWindow*		p_ListWindow{ nullptr };
		CDxLabel*			p_HeaderLabel{ nullptr };
	};
}


