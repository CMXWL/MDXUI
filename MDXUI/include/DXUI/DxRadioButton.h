#pragma once
#include "DxCheckBox.h"
namespace DxUI{
	//+--------------------------------------
	//
	// CDxRadioButton  ��ѡ��ť 
	// ���Ȼ�����ı��ĳ��Ƚ��е���
	// ���͵���¼�:
	// Clicked(bool isClicked��CDxWidget* sender)
	// ����ʹ�����·�ʽ�����¼��ص�
	// CDxRadioButton button;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxRadioButton, Clicked, &button),TL::MSLOT(testFun));
	// testFun:
	// void testFun(bool isClicked,CDxWidget* sender);
	// ��굥��ʱ���� EDxUIClicked �¼�
	//
	// ����ʵ�� GetWidth  UpdateChildWindowPos ���Զ���۽����޸�
	// Ĭ��ʵ�ֵ����ʱ ͼ�� + �ı� ˮƽ��������
	// ʵ�� OnDrawItem �������»��� ���� true ��Ч ������� false �����ڵ�ǰ����������и��ǻ���
	//
	//+--------------------------------------
	class DXUI_API CDxRadioButton :
		public CDxCheckBox
	{
		DECLARE_CLASS(CDxRadioButton)
	public:
		CDxRadioButton();
		~CDxRadioButton();
		DXWindowType	GetWindowSelfDesc() const;
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);
		void			UpdateChildWindowPos();
	};
}


