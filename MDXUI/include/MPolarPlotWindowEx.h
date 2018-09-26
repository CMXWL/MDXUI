

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
#include "MPolarPlotWindow.h"


//+----------------------------
//
// MPolarPlotWindowEx
// ������
// x ������ʾ�Ƕ� deg
// y ��ʾ����
//
//+----------------------------
class DXUI_API MPolarPlotWindowEx :
	public MPolarPlotWindow
{
	DECLARE_CLASS(MPolarPlotWindowEx)
public:
	MPolarPlotWindowEx();
	~MPolarPlotWindowEx();
protected:
	void		UpdateChildWindowPos();
	void		OnDealPoint(int x, int y);
	void		OnDealMarker(int x, int y);
	bool		OnNotify(DxUI::DXNotifyUI* NotifyEvent);
	void		OnRendWindow(IPainterInterface* painter);
};

