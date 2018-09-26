

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
		// ����д�����дitem���뷨�Ļ���������д�ú������ɣ���������д����� OnRendWindow
		// rc �ǿɻ�������
		// painter ���ƶ���
		//
		bool			IsVisible() const;
		virtual bool	OnDrawItem(const RECT& rc, IPainterInterface* painter);



		void			Trigger(); // �����¼� Clicked
	msignals:
		//
		// ���Item��ʱ����Clickedʱ��
		//
		void			Clicked(bool isClicked, CDxWidget* sender);
		void			DoubleClicked(bool isClicked, CDxWidget* sender);
		void			Checked(bool isChecked, CDxWidget* sender);  //���ڿ�ѡ��Item��˵ѡ��ʱ������ź�
		void			ClickedPoint(bool isClicked, POINT pt, CDxWidget* sender);

		TL::MTLVoidEvent<bool, CDxWidget*> Event_Clicked;
		TL::MTLVoidEvent<bool, CDxWidget*> Event_Checked;
		TL::MTLVoidEvent<bool, CDxWidget*> Event_DoubleClicked;
		TL::MTLVoidEvent<bool, POINT, CDxWidget*> Event_ClickedPoint;

	protected:
		void			UpdateChildWindowPos();
		void			SetSelected(bool selected);


		bool			bIsSelected{ false };
		int				mTextLayoutLen{ 0 };
		POINT			mOldPoint;
		mj::MAny		mAny;
	};

}

