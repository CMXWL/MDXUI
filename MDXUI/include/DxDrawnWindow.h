

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

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
		virtual bool	OnMouseEvent(const CDxMouseEvent& e); // ��Ӧ����¼�
	};
}


