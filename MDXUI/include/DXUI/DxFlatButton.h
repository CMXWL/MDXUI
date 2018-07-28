#pragma once
#include "DxEdit.h"
namespace DxUI{

	//+--------------------------------------
	//
	// CDxFlatButton  ��ƽ��ť ͬʱ�����
	// ���Ȼ�����ı��ĳ��Ƚ��е���
	// ���͵���¼�:
	// Clicked(bool isClicked,CDxWidget* sender)
	// ����ʹ�����·�ʽ�����¼��ص�
	// CDxFlatButton button;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxFlatButton, Clicked, &button),TL::MSLOT(testFun));
	// testFun:
	// void testFun(bool isClicked,CDxWidget* sender);
	// ��굥�� ����״̬Ϊtrue ʱ���� EDxUIClicked �¼�
	//
	// ����ʵ�� GetWidth  UpdateChildWindowPos ���Զ���۽����޸�
	// Ĭ��ʵ�ֵ����ʱ ͼ�� + �ı� ˮƽ��������
	// ʵ�� OnDrawItem �������»��� ���� true ��Ч ������� false �����ڵ�ǰ����������и��ǻ���
	//
	//+--------------------------------------
	class DXUI_API CDxFlatButton :
		public CDxEdit
	{
		DECLARE_CLASS(CDxFlatButton)
	public:
		CDxFlatButton();
		~CDxFlatButton();

		DXWindowType	GetWindowSelfDesc() const;
		SIZE			GetHintSize() const;
		int				GetWidth() const;
		int				GetHeight() const;
		int				GetWidthQuickly() const; // ���ٻ�ȡ��� δ��׼
		int				GetHeightQuickly() const; // ���ٻ�ȡ��� δ��׼
		DxRectI			GetInvalidateRect() const;
		bool			SetWindowStatus(DXWindowStatus status);
		void			SetIcon(const MString& icon);

		void			SetGeomety(const DxRectI& rc);

		virtual void	SetChecked(bool isChecked);
		bool			IsChecked() const;

		void			SetClipRect(const DxRectI& rc);
		DxRectI&		GetClipRect();
		const DxRectI&	GetClipRect() const;

		void			OnTextFormat();

		virtual void	Trigger();  // ���� һ������ź�

	msignals:
		virtual void	Clicked(bool isClicked,CDxWidget* sender);  // �ⲿ�ɶԸ��źŽ���connect
		


	public:
		//
		// ����Ҫ����۽������»��ƿ�����д�ú���
		//
		virtual bool	OnDrawItem(const RECT& rc, IPainterInterface* painter);

		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);

	protected:
		void			OnResizeEvent();
		void			UpdateChildWindowPos();

	protected:
		DxRectI			mClipRect;
		bool			bIsClicked{ false };
	};
}


