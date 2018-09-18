

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "DxFlatButton.h"
namespace DxUI{
	//+--------------------------------------
	//
	// CDxPushButton  ��ͨ��ť ͬʱ�����
	// ���Ȼ�����ı��ĳ��Ƚ��е���
	// ���͵���¼�:
	// Clicked(bool isClicked,CDxWidget* sender)
	// ����ʹ�����·�ʽ�����¼��ص�
	// CDxPushButton button;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxPushButton, Clicked, &button),TL::MSLOT(testFun));
	// testFun:
	// void testFun(bool isClicked,CDxWidget* sender);
	// ��굥��ʱ���� EDxUIClicked �¼�
	//
	// ����ʵ�� GetWidth  UpdateChildWindowPos ���Զ���۽����޸�
	// Ĭ��ʵ�ֵ����ʱ ͼ�� + �ı� ˮƽ��������
	// ʵ�� OnDrawItem �������»��� ���� true ��Ч ������� false �����ڵ�ǰ����������и��ǻ���
	//
	//+--------------------------------------
	class DXUI_API CDxPushButton :
		public CDxFlatButton
	{
		DECLARE_CLASS(CDxPushButton)
	public:
		CDxPushButton();
		~CDxPushButton();
		DXWindowType	GetWindowSelfDesc() const;
		void			SetChecked(bool isChecked);
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);
	};



	//+---------------------------------------
	//
	// CDxStatusButton ״̬��ť
	// ״̬�������仯
	// ��һ��Ϊѡ�� �ڶ��ξ�Ϊ��ѡ�� ......
	//
	//+----------------------------------------
	class DXUI_API CDxStatusButton : public CDxPushButton{
		DECLARE_CLASS(CDxStatusButton)
	public:
		CDxStatusButton();
		~CDxStatusButton();
		DXWindowType	GetWindowSelfDesc() const;
		void			SetChecked(bool isChecked);
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);
	};



	//+------------------------------------
	//
	// class CDxUserButton
	// ���Զ�ͼ����ı����ɶ���
	// ��Ҫ���ı���ͼƬ�����������
	// ���������ܲ����Լ���Ҫ��
	//
	//+------------------------------------
	class DXUI_API CDxUserButton : public CDxPushButton{
		DECLARE_CLASS(CDxUserButton)
	public:
		CDxUserButton();
		~CDxUserButton();

	protected:
		void	UpdateChildWindowPos();
	};

	//+--------------------------------------
	//
	// class CDxHexagonButton 
	// �����ΰ�ť
	// h = w / 2 * std::sqrt(3);
	// �ߺͿ����������ϵʽ��Ϊ��������
	// h === ��
	// w === ��
	// 
	//+--------------------------------------
	class DXUI_API CDxHexagonButton : public CDxPushButton{
		DECLARE_CLASS(CDxHexagonButton)
	public:
		CDxHexagonButton();
		~CDxHexagonButton();
	protected:
		bool OnDrawItem(const RECT& rc, IPainterInterface* painter);
	};
}

