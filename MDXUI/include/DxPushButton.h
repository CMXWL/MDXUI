

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
#include "DxFlatButton.h"
namespace DxUI{
	//+--------------------------------------
	//
	// CDxPushButton  ��ͨ��ť ͬʱ�����
	// ���Ȼ�����ı��ĳ��Ƚ��е���
	// ���͵���¼�:
	// Clicked(bool isClicked,CDxWidget* sender)
	// ����ʹ�����·�ʽ�����¼��ص�
	// CDxPushButton button;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxPushButton, Clicked, &button),TL::MSLOT(testFun));
	// testFun:
	// void testFun(bool isClicked,CDxWidget* sender);
	// ��굥��ʱ���� EDxUIClicked �¼�
	//
	// ����ʵ�� GetWidth  UpdateChildWindowPos ���Զ���۽����޸�
	// Ĭ��ʵ�ֵ����ʱ ͼ�� + �ı� ˮƽ��������
	// ʵ�� OnDrawItem �������»��� ���� true ��Ч ������� false �����ڵ�ǰ����������и��ǻ���
	//
	//+--------------------------------------
	class DXUI_API CDxPushButton :
		public CDxFlatButton
	{
		DECLARE_CLASS(CDxPushButton)
	public:
		CDxPushButton();
		~CDxPushButton();
		DXWindowType	GetWindowSelfDesc() const;
		void			SetChecked(bool isChecked);
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);
	};



	//+---------------------------------------
	//
	// CDxStatusButton ״̬��ť
	// ״̬�������仯
	// ��һ��Ϊѡ�� �ڶ��ξ�Ϊ��ѡ�� ......
	//
	//+----------------------------------------
	class DXUI_API CDxStatusButton : public CDxPushButton{
		DECLARE_CLASS(CDxStatusButton)
	public:
		CDxStatusButton();
		~CDxStatusButton();
		DXWindowType	GetWindowSelfDesc() const;
		void			SetChecked(bool isChecked);
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);
	};



	//+------------------------------------
	//
	// class CDxUserButton
	// ���Զ�ͼ����ı����ɶ���
	// ��Ҫ���ı���ͼƬ�����������
	// ���������ܲ����Լ���Ҫ��
	//
	//+------------------------------------
	class DXUI_API CDxUserButton : public CDxPushButton{
		DECLARE_CLASS(CDxUserButton)
	public:
		CDxUserButton();
		~CDxUserButton();

	protected:
		void	UpdateChildWindowPos();
	};

	//+--------------------------------------
	//
	// class CDxHexagonButton 
	// �����ΰ�ť
	// h = w / 2 * std::sqrt(3);
	// �ߺͿ����������ϵʽ��Ϊ��������
	// h === ��
	// w === ��
	// 
	//+--------------------------------------
	class DXUI_API CDxHexagonButton : public CDxPushButton{
		DECLARE_CLASS(CDxHexagonButton)
	public:
		CDxHexagonButton();
		~CDxHexagonButton();
	protected:
		bool OnDrawItem(const RECT& rc, IPainterInterface* painter);
	};
}

