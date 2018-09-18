

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
	class CDxCheckBox;
	class CDxRadioButton;
	//+---------------------------------
	//
	// class CDxGroupBox 
	// ��Ͽ�
	// StatusChanged(bool isEnabel)
	// ��״̬�ı�ʱ�����ú������ú�����ͨ��TL::MTLDataBind::Connect ���к��ⲿͨ��
	// void testFun(bool);
	// DxUI::CDxGroupBox box;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxSpinBox, StatusChanged, &box),TL::MSLOT(testFun));
	//
	//+---------------------------------
	class DXUI_API CDxGroupBox :
		public CDxWindow
	{
		DECLARE_CLASS(CDxGroupBox)
	public:
		CDxGroupBox();
		~CDxGroupBox();


		CDxWidget*			HitTest(int x, int y);
		bool				PointInArea(int x, int y);
		CDxEffects*			GetSpliterEffects();
		void				SetSpliterHeight(int height);
		void				SetHeaderLineRetract(int distance);
		DXWindowType		GetWindowSelfDesc() const;
		DxColor				GetEraseColor() const;
		void				StatusChanged(bool isEnabel);
		void				SetCheckable(bool isable);
		bool				IsCheckable() const;
		void				SetChecked(bool isChecked);
		bool				IsChecked() const;
		void				ReceiveEvent(CDxUIEvent* e);
		void				OnRendWindow(IPainterInterface* painter);

	msignals:
		void				CheckedStatusChanged(bool isChecked, CDxWidget* sender); // �ⲿ�����Ӹ��¼�
		TL::MTLVoidEvent<bool, CDxWidget*> Event_CheckedStatusChanged;

	mevent:
		void				LayoutWindowChanged(bool isAdd, CDxWidget* window);
		void				OnDealRadioButtonEvent(bool isClicked, CDxWidget* sender);

	protected:
		void				CheckedStatus(bool isChecked, CDxWidget* sender);
		void				UpdateChildWindowPos();

	private:
		CDxCheckBox*		pCheckBox{ nullptr };
		bool				bIsCheckable{ false };
		bool				bIsChecked{ true };
		int					mHeaderTextLength{ 0 };
		int					mHeaderTextHeight{ 0 };
		ObjTraceType		mObjectTrace;
		int					m_SpliterLineSize{ 1 };
		int				    m_HeaderDistance{ 20 };
		CDxEffects			m_SpliterEffects;
		TL::Vector<CDxRadioButton*>	mRadioButtons;
	};
}


