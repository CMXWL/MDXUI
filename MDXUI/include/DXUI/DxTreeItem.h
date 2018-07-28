#pragma once
#include "DxListItem.h"
#include "DxScrollBar.h"

namespace DxUI{
	class CDxTreeWindow;
	class CDxTreeItem;
	class CDxMultTreeWindow;
	class CDxMultTreeItem;

	//+-----------------------------------
	//
	// class CDxTreeItemDecorator
	// չ�����������η�
	//
	//+-----------------------------------
	class DXUI_API CDxTreeItemDecorator : public CDxDecorator{
		DECLARE_CLASS(CDxTreeItemDecorator)
		friend class CDxTreeItem;
		friend class CDxMultTreeItem;

	public:
		CDxTreeItemDecorator();
		~CDxTreeItemDecorator();	
		bool				OnNotify(DXNotifyUI* NotifyEvent);
		DxColor				GetEraseColor() const;
		void				OnRendWindow(IPainterInterface* painter);
	protected:
		virtual void		SetParentWindowStatus(bool isSelected);

	private:
		void				SetSelected(bool selected);
		bool				IsSelected() const;
		bool				bIsSelected{ false };
		CDxTreeItem*		pOwnWindow{ nullptr };
	};


	//+-------------------------------------------------
	//
	// class CDxTreeItem
	// CDxTreeItem ���� �� CDxTreeItem ������������
	// ���е����ö����� CDxTreeWindow ������������
	// UpdateChildWindowPos ���ᱻ�������д
	// UpdateArea ����ʹ��
	//
	//+-------------------------------------------------
	class DXUI_API CDxTreeItem :
		public CDxListItem
	{
		DECLARE_CLASS(CDxTreeItem)
		friend class CDxTreeWindow;
		friend class CDxMultTreeWindow;
		friend class CDxMultTreeItem;

		enum CheckState{Unchecked = 0,PartiallyChecked,Checked};
	public:
		CDxTreeItem();
		~CDxTreeItem();

		CDxTreeItem*				CreateThis();
		bool						DestroyThis();
		
		DXWindowType				GetWindowSelfDesc() const;

		void						AddItem(CDxTreeItem* item);
		virtual CDxTreeItem* 		AddItem(const MString& itemText);
		virtual CDxTreeItem* 		AddItem(const MString& icon, const MString& itemText);

		void						InsertItem(CDxTreeItem* item, CDxTreeItem* positem);
		bool						RemoveItem(CDxTreeItem* item);

		void						Clear();

		CDxTreeItem*				GetItemByText(const MString& Text);

		void						SetGeomety(const DxRectI& rc);
		CDxWidget*					HitTest(int x, int y);
		bool						PointInArea(int x, int y);

		

		DxRectI						GetInvalidateRect() const;

		TL::Vector<CDxTreeItem*>&   GetChildItems();
		const TL::Vector<CDxTreeItem*>&   GetChildItems() const;
		bool						IsExpansion() const;
		void						SetExpansion(bool isExPansion);
		void						NotifyTreeWindowUpdate();

		bool						OnNotify(DXNotifyUI* NotifyEvent);
		void						ReceiveEvent(CDxUIEvent* e);

		CDxTreeItem*				GetParentNode() const;

		void						SetSelected(bool selected);


		void						SetCheckable(bool isCheck);
		bool						IsCheckable() const;
		CheckState					GetCheckState() const;
		void						SetCheckState(CheckState state);


		//
		// ��Զ������ṹʵ��
		//
		virtual void				SetColumsPos(const TL::Vector<int>& pos){}
		virtual void				AddItem(const TL::Vector<MString>& Text){};
		virtual void				AddItem(const MString& icon, const TL::Vector<MString>& Text){};
		virtual void				SetShowText(const TL::Vector<MString>& Texts){};
	protected:
		void						OnViewWindowChanged();
		void					    SetExpansionImpl(bool isExPansion);
		CDxTreeItemDecorator*		GetDecorator();
		void						UpdateChildWindowPos();
		void						UpdateArea(){}
		void						GetItems(std::vector<CDxTreeItem*>& outItems);
		void						OnRendWindow(IPainterInterface* painter);

	protected:
		CDxTreeItemDecorator		mDecorator;
		TL::Vector<CDxTreeItem*>    mItems;
		CDxTreeItem*				pParentNode{ nullptr };
		bool						bIsExpansion{ true };
		bool						bIsCanCheckable{ false };
	};



	//+-------------------------------------------------
	//
	// class CDxMultTreeItem
	// CDxMultTreeItem ���� �� CDxMultTreeItem ������������
	// ���е����ö����� CDxMultTreeWindow ������������
	// UpdateChildWindowPos ���ᱻ�������д
	// UpdateArea ����ʹ��
	//
	//+-------------------------------------------------
	class DXUI_API CDxMultTreeItem : public CDxTreeItem{
		DECLARE_CLASS(CDxMultTreeItem)
		using CDxTreeItem::AddItem;
	public:
		CDxMultTreeItem();
		~CDxMultTreeItem();
		CDxTreeItem*				CreateThis();
		bool						DestroyThis();
		void						SetColumsPos(const TL::Vector<int>& pos);

		CDxTreeItem* 				AddItem(const MString& itemText);
		CDxTreeItem* 				AddItem(const MString& icon, const MString& itemText);
		void						AddItem(const TL::Vector<MString>& Text);
		void						AddItem(const MString& icon, const TL::Vector<MString>& Text);
		void						SetShowText(const TL::Vector<MString>& Texts);

		int							GetWidth() const;
	protected:

		void						OnRendWindow(IPainterInterface* painter);

	protected:
		TL::Vector<int>				mColumPos;
		TL::Vector<MString>			mTextVec;
	};
}


