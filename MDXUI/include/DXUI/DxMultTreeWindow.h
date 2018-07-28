#pragma once
#include "DxWindow.h"
#include "DxScrollBar.h"

namespace DxUI{

	class CDxTreeItem;
	class CDxTableHeader;
	//+----------------------------
	//
	// class  CDxMultTreeWindow
	// �������ṹ
	//
	//+----------------------------
	class DXUI_API CDxMultTreeWindow :
		public CDxWindow
	{
		DECLARE_CLASS(CDxMultTreeWindow)
	public:
		CDxMultTreeWindow();
		~CDxMultTreeWindow();
		DXWindowType GetWindowSelfDesc() const;

		void					SetHeaderLabelShow(bool isShow);
		void					SetHeaderLabelHeight(int height);
		void					SetHeaderEffects(const DxUI::CDxEffects& effects);
		void					SetHeaderLabels(const TL::Vector<MString>& Header);
		void					SetColumsWidth(const TL::Vector<int>& widths);
		void					SetColumCounts(int counts);

		void					AddItem(CDxTreeItem* item);

		void					Clear();

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
		void					ClickedItem(CDxTreeItem* item); // ����
		void					DBClickedItem(CDxTreeItem* item);// ˫��

	protected:
		void					UpdateChildWindowPos();
		void					UpdateViewWindow();
		void					OnDealItemForDistance(unsigned xdis, unsigned ydis);
		void					UpdateScrollBarPos();


	private:
		int							mHeaderHeight{ 30 };
		int							mColums{ 1 };
		TL::Vector<int>				mColumsWidths;
		TL::Vector<MString>			mHeaders;
		CDxHorizonScrollBar			mHorizonScrollBar;
		CDxVerticalScrollBar		mVerticalScrollBar;
		TL::Vector<CDxTableHeader*>	mHeaderItems;
		TL::Vector<CDxTreeItem*>	mItems;  // ������¼root�ڵ��item
		TL::Vector<CDxTreeItem*>    mAllItems; // ��¼���е�item����root
		CDxTreeItem*				pCurrentItem{ nullptr };
		CDxTableHeader*				pCurrentHeaderItem{ nullptr };
		int							mItemMaxWidth{ 0 };
		int							mItemMaxHeight{ 0 };
		int							mXCurrentOffset{ 0 };
		int							mYCurrentOffset{ 0 };
		int							mXMaxOffset{ 0 };
		int							mYMaxOffset{ 0 };
		bool						bIsShowHeader{ true };
		DxUI::CDxEffects			mHeaderEffects;
	};
}


