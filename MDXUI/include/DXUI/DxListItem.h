#pragma once
#include "DxLabel.h"

namespace DxUI{
	//+------------------------------------------------------------
	//
	// �б����
	// Ĭ�ϵ��б��item���������߶�Ϊ26
	// ���������Ҫ�޸�����߶ȿ���ѡ��̳�֮���޸�mFixHeight
	// �����Ҫ���»���item����ۣ�����̳к���дOnDrawItem����
	// ��Ϊ�����дOnRendWindow���л��漰��һЩ�ü�ϸ��
	// OnDrawItem ��д�ú������ÿ��ǲü�ϸ��
	//
	//+-------------------------------------------------------------
	class DXUI_API CDxListItem :
		public CDxLabel
	{
		friend class CDxListWindow;
		friend class CDxComboBox;
		friend class CDxListWidget;

		DECLARE_CLASS(CDxListItem)
	public:
		CDxListItem();

	
		virtual CDxListItem* CreateThis();
		virtual bool		 DestroyThis();
		DXWindowType		 GetWindowSelfDesc() const;  
		SIZE				 GetHintSize() const;


		int				GetWidth() const;
		int				GetWidthQuickly() const; // ���ٻ�ȡ��� δ��׼
		void			SetIcon(const MString& icon);
		bool			SetWindowStatus(DXWindowStatus status);

		void			SetGeomety(const DxRectI& rc);
		void			OnResizeEvent();
		void			OnTextFormat();
		void			SetText(const MString& Text);
		void			SetAny(const mj::MAny& any);

		bool			OnNotify(DXNotifyUI* NotifyEvent);


		bool			IsSelected() const;
		DxRectI			GetInvalidateRect() const;


		void			OnRendWindow(IPainterInterface* painter);


		//
		// ���Item��ʱ����Clickedʱ��
		//
		void			Clicked(bool isClicked, CDxWidget* sender);
		void			DoubleClicked(bool isClicked, CDxWidget* sender);
		void			Checked(bool isChecked, CDxWidget* sender);  //���ڿ�ѡ��Item��˵ѡ��ʱ������ź�
		void			ClickedPoint(bool isClicked, POINT pt, CDxWidget* sender);


		void			Trigger(); // ���������¼� Clicked

		//
		// ����д�����дitem���뷨�Ļ���������д�ú������ɣ���������д����� OnRendWindow
		// rc �ǿɻ�������
		// painter ���ƶ���
		//
		bool			IsVisible() const;
		virtual bool	OnDrawItem(const RECT& rc, IPainterInterface* painter);

	protected:
		void			UpdateChildWindowPos();
		void			SetSelected(bool selected);


		bool			bIsSelected{ false };
		int				mTextLayoutLen{ 0 };
		POINT			mOldPoint;
		mj::MAny		mAny;
	};

}

