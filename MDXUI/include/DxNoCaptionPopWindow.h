

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "DxPopWindow.h"

namespace DxUI{
	//
	// ����Ч��͸��
	// RgbI(1, 5, 11) ������ɫ��Ϊ����ɫ ������͸��
	//
	class DXUI_API CDxNoCaptionPopWindow :
		public CDxPopWindow
	{
		DECLARE_CLASS(CDxNoCaptionPopWindow)
	public:
		CDxNoCaptionPopWindow();
		~CDxNoCaptionPopWindow();
		void	CreateHwnd(HWND parent);
		LRESULT	OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		void	OnRender2D();
		void	OnRendWindow(IPainterInterface* painter);
	};
}


