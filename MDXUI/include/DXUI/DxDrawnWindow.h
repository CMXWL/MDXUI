#pragma once
#include "DxWindow.h"

namespace DxUI{
	//+--------------------------------------
	//
	// CDxDrawnWindow  �ֻ洰�ڴ���
	// ʵ�� OnPainterEvent ���л���
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
		virtual void	OnDrawnEvent(const DxRectI& rc, IPainterInterface* painter); // ��Ӧ��ͼ�¼�
		virtual void	OnMouseEvent(const CDxMouseEvent& e); // ��Ӧ����¼�
	};
}


