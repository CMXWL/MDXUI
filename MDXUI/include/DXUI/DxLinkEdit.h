#pragma once
#include "DxEdit.h"
namespace DxUI{
	//+--------------------------
	// 
	// class CDxLinkEdit
	// �������ı�
	// �����֮ʱ��ִ�лص�����
	// Ҳ����ʹ��connect���лص�����
	// 
	//+---------------------------
	class DXUI_API CDxLinkEdit :
		public CDxEdit
	{
		DECLARE_CLASS(CDxLinkEdit)
		typedef std::function<void(const MString&)> RecallFunType;

	public:
		CDxLinkEdit();
		~CDxLinkEdit();

		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);

		void			SetHoverColor(const DxColor& col);
		void			BindRecallFun(RecallFunType fun);
		void			Clicked(MString Text, CDxWidget* sender);
	private:
		RecallFunType	mFun{ nullptr };
		DxColor			mHoverColor;
	};
}


