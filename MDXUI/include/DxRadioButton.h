

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
#include "DxCheckBox.h"
namespace DxUI{
	//+--------------------------------------
	//
	// CDxRadioButton  ��ѡ��ť 
	// ���Ȼ�����ı��ĳ��Ƚ��е���
	// ���͵���¼�:
	// Clicked(bool isClicked��CDxWidget* sender)
	// ����ʹ�����·�ʽ�����¼��ص�
	// CDxRadioButton button;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxRadioButton, Clicked, &button),TL::MSLOT(testFun));
	// testFun:
	// void testFun(bool isClicked,CDxWidget* sender);
	// ��굥��ʱ���� EDxUIClicked �¼�
	//
	// ����ʵ�� GetWidth  UpdateChildWindowPos ���Զ���۽����޸�
	// Ĭ��ʵ�ֵ����ʱ ͼ�� + �ı� ˮƽ��������
	// ʵ�� OnDrawItem �������»��� ���� true ��Ч ������� false �����ڵ�ǰ����������и��ǻ���
	//
	//+--------------------------------------
	class DXUI_API CDxRadioButton :
		public CDxCheckBox
	{
		DECLARE_CLASS(CDxRadioButton)
	public:
		CDxRadioButton();
		~CDxRadioButton();
		DXWindowType	GetWindowSelfDesc() const;
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);
		void			UpdateChildWindowPos();
	};
}


