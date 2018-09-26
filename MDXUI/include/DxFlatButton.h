

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
#include "DxEdit.h"
namespace DxUI{

	//+--------------------------------------
	//
	// CDxFlatButton  ��ƽ��ť ͬʱ�����
	// ���Ȼ�����ı��ĳ��Ƚ��е���
	// ���͵���¼�:
	// Clicked(bool isClicked,CDxWidget* sender)
	// ����ʹ�����·�ʽ�����¼��ص�
	// CDxFlatButton button;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxFlatButton, Clicked, &button),TL::MSLOT(testFun));
	// testFun:
	// void testFun(bool isClicked,CDxWidget* sender);
	// ��굥�� ����״̬Ϊtrue ʱ���� EDxUIClicked �¼�
	//
	// ����ʵ�� GetWidth  UpdateChildWindowPos ���Զ���۽����޸�
	// Ĭ��ʵ�ֵ����ʱ ͼ�� + �ı� ˮƽ��������
	// ʵ�� OnDrawItem �������»��� ���� true ��Ч ������� false �����ڵ�ǰ����������и��ǻ���
	//
	//+--------------------------------------
	class DXUI_API CDxFlatButton :
		public CDxEdit
	{
		DECLARE_CLASS(CDxFlatButton)
	public:
		CDxFlatButton();
		~CDxFlatButton();

		DXWindowType	GetWindowSelfDesc() const;
		SIZE			GetHintSize() const;
		int				GetWidth() const;
		int				GetHeight() const;
		int				GetWidthQuickly() const; // ���ٻ�ȡ��� δ��׼
		int				GetHeightQuickly() const; // ���ٻ�ȡ��� δ��׼
		DxRectI			GetInvalidateRect() const;
		bool			SetWindowStatus(DXWindowStatus status);
		void			SetIcon(const MString& icon);

		void			SetGeomety(const DxRectI& rc);

		virtual void	SetChecked(bool isChecked);
		bool			IsChecked() const;

		void			SetClipRect(const DxRectI& rc);
		DxRectI&		GetClipRect();
		const DxRectI&	GetClipRect() const;

		void			OnTextFormat();

		virtual void	Trigger();  // ���� һ������ź�

	msignals:
		virtual void	Clicked(bool isClicked,CDxWidget* sender);  // �ⲿ�ɶԸ��źŽ���connect
		

		//+---------------
		//
		// ʹ�� Event_Clicked ����ֱ��ʹ�� += �����������¼���
		// Event_Clicked += fun
		// Event_Clicked += fun
		// += ����һ���¼�id
		// �����Ҫ�Ƴ��¼���Ӧ���� -= ����
		// Button ��Ӹ��¼���������
		//
		//+---------------
		TL::MTLVoidEvent<bool, CDxWidget*>   Event_Clicked;

	public:
		//
		// ����Ҫ����۽������»��ƿ�����д�ú���
		//
		virtual bool	OnDrawItem(const RECT& rc, IPainterInterface* painter);

		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);

	protected:
		void			OnResizeEvent();
		void			UpdateChildWindowPos();

	protected:
		DxRectI			mClipRect;
		bool			bIsClicked{ false };
	};


	//+-------------------------------------------------------
	//
	// �߶Ȳ������Ƶ�ƽ�水ť
	// ���ܵ���������ܵ��״̬Ӱ����һ�ε��
	//
	//+-------------------------------------------------------
	class DXUI_API CDxFlatButtonEx : public CDxFlatButton{
		DECLARE_CLASS(CDxFlatButtonEx)
	public:
		CDxFlatButtonEx();
		~CDxFlatButtonEx();
		SIZE			GetHintSize() const;
		bool			SetWindowStatus(DXWindowStatus status);
		void			SetChecked(bool isChecked);
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			UpdateChildWindowPos();
		void			OnRendWindow(IPainterInterface* painter);
	};
}


