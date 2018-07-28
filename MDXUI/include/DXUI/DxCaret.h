#pragma once
#include "DxWidget.h"

namespace DxUI{
	//+-------------------
	//
	// class CDxCaret
	// �ı��༭��˸�Ĺ��
	//
	//+--------------------
	class DXUI_API CDxCaret :
		public CDxWidget
	{
		DECLARE_CLASS(CDxCaret)
	public:
		CDxCaret();
		~CDxCaret();
		bool				SetWindowStatus(DXWindowStatus status){ return false; }
		void				SetColor(const DxColor& col);
		void				StartBlink();
		void				StopBlink();
		void				OnTimer();
		void				OnRendWindow(IPainterInterface* painter);

	private:
		bool	bIsStart{ false };
	};
}


