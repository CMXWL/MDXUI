#pragma once
#include "DxWindow.h"

namespace DxUI{
	//+--------------------------------------
	//
	// CDxDrawnWindow  手绘窗口窗口
	// 实现 OnPainterEvent 自行绘制
	//
	//+--------------------------------------
	class DXUI_API CDxDrawnWindow :
		public CDxWindow
	{
		DECLARE_CLASS(CDxDrawnWindow)
	public:
		CDxDrawnWindow();
		~CDxDrawnWindow();
		DXWindowType	GetWindowSelfDesc() const;
		void		    OnRendWindow(IPainterInterface* painter);

	protected:
		virtual void	OnDrawnEvent(const DxRectI& rc, IPainterInterface* painter); // 响应绘图事件
		virtual void	OnMouseEvent(const CDxMouseEvent& e); // 响应鼠标事件
	};
}


