#pragma once
#include "DxDialog.h"

namespace DxUI{
	//
	// û�б���ĶԻ���
	// ��������͸��
	//
	class DXUI_API CDxNoCaptionDialog :
		public CDxDialog
	{
		DECLARE_CLASS(CDxNoCaptionDialog)
	public:
		CDxNoCaptionDialog();
		~CDxNoCaptionDialog();
		LRESULT	OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		void OnRender2D();
		void	OnRendWindow(IPainterInterface* painter);
		int		Exec();
	};
}


