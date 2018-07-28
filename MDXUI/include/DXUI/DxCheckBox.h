#pragma once
#include "DxFlatButton.h"

namespace DxUI{
	//+--------------------------------------
	//
	// CDxCheckBox  ѡ��ť 
	// ���Ȼ�����ı��ĳ��Ƚ��е���
	// ���͵���¼�:
	// Clicked(bool isClicked��CDxWidget* sender)
	// ����ʹ�����·�ʽ�����¼��ص�
	// CDxCheckBox button;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxCheckBox, Clicked, &button),TL::MSLOT(testFun));
	// testFun:
	// void testFun(bool isClicked,CDxWidget* sender);
	// ��굥��ʱ���� EDxUIClicked �¼�
	//
	// ����ʵ�� GetWidth  UpdateChildWindowPos ���Զ���۽����޸�
	// Ĭ��ʵ�ֵ����ʱ ͼ�� + �ı� ˮƽ��������
	// ʵ�� OnDrawItem �������»��� ���� true ��Ч ������� false �����ڵ�ǰ����������и��ǻ���
	//
	//+--------------------------------------
	class DXUI_API CDxCheckBox :
		public CDxFlatButton
	{
		friend class CDxGroupBox;
		DECLARE_CLASS(CDxCheckBox)
	public:
		CDxCheckBox();
		~CDxCheckBox();
		DXWindowType	GetWindowSelfDesc() const;
		DxColor			GetEraseColor() const;
		virtual void	SetChecked(bool isChecked);
		virtual void	SetCheckable(bool isable);
		virtual bool	IsCheckable() const;
		virtual bool	IsChecked() const;
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);

	protected:
		void			UpdateChildWindowPos();
		bool			bIsCheckabel{ true };
	};
}


