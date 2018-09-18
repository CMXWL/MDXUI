

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
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

