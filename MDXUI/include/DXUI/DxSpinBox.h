#pragma once
#include "DxWidget.h"
namespace DxUI{
	class CDxDecorator;
	class CDxEdit;
	//+---------------------------------
	//
	// class CDxSpinBox 
	// ΢����
	// ValueChanged(double val,CDxSpinBox* sender)
	// �����ݸı�ʱ�����ú������ú�����ͨ��TL::MTLDataBind::Connect ���к��ⲿͨ��
	// void testFun(int index1, CDxSpinBox* sender);
	// DxUI::CDxSpinBox box;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxSpinBox, ValueChanged, &box),TL::MSLOT(testFun));
	//
	//+---------------------------------
	class DXUI_API CDxSpinBox :
		public CDxWidget
	{
		DECLARE_CLASS(CDxSpinBox)
	public:
		CDxSpinBox();
		~CDxSpinBox();
		void				CreateHwnd(){}
		void				CreateHwnd(HWND parent){}
		DXWindowType		GetWindowSelfDesc() const;
		SIZE				GetHintSize() const;
		void				SetStep(double step);
		void				SetRange(double minval, double maxval);
		void				SetValue(double val);

		void				SetReadOnly(bool isReadOnly);
		void				SetDecimals(int decimals);
		int					GetDecimals() const;
		double				GetValue() const;
		void				ReceiveEvent(CDxUIEvent* e);

	mevent:
		void				TextChanged(MString CurText, MString PreText, CDxWidget* sender);


	msignals:
		void				ValueChanged(double val, CDxWidget* sender);

	public:
		void				OnRendWindow(IPainterInterface* painter);
		void				UpdateChildWindowPos();


	private:
		CDxDecorator*		pDecValueButton{ nullptr };
		CDxDecorator*		pIncValueButton{ nullptr };
		CDxEdit*			pValueEdit{ nullptr };
		double				mStep{ 1 };
		double				mMinValue;
		double				mMaxValue;
		int					mDecimals;
		bool			    bIsReadOnly{ false };
	};
}


