

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution
// Copyright (C) 2017-2018 by Mengjin (sh06155@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "DxWidget.h"

namespace DxUI{

	//+--------------------------------
	//
	// ������
	//
	//+--------------------------------
	class DXUI_API CDxDecorator : public CDxWidget
	{
	public:
		CDxDecorator();
		~CDxDecorator();
		void	CreateHwnd(){}
		void	CreateHwnd(HWND parent){}
		DxColor	GetEraseColor() const;
		void	SetColor(DXWindowStatus status, const DxColor& col);
		void	SetShowRegion(const TL::Vector<DxPointD>& points);
		bool	OnNotify(DXNotifyUI* NotifyEvent);
		void	OnRendWindow(IPainterInterface* painter);
	private:
		TL::Vector<DxPointD> mGeometryPoints;
	};


	//+---------------------------------
	//
	// �������ϵĻ���
	//
	//+---------------------------------
	class DXUI_API CDxChuncker : public CDxWidget
	{
	public:
		CDxChuncker();
		~CDxChuncker();
		void	CreateHwnd(){}
		void	CreateHwnd(HWND parent){}
		DxColor	GetEraseColor() const;
		void	SetColor(DXWindowStatus status, const DxColor& col);
		bool	SetWindowStatus(DXWindowStatus status);
		bool	OnNotify(DXNotifyUI* NotifyEvent);
	private:
		POINT	mOldPoint;
		bool	bIsClicked{ false };
	};

	//+------------------------------------------
	//
	// ����Ļ���
	// ������λ�øı�ʱ�������� ValueChanged
	// CDxScrollBar bar;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxScrollBar, ValueChanged, &bar),TL::MSLOT(testFun));
	// testFun:
	// void testFun(double value,CDxWidget* sender);
	//
	//+--------------------------------------------
	class DXUI_API CDxScrollBar : public CDxWidget
	{
	public:
		CDxScrollBar();
		~CDxScrollBar();

		void			CreateHwnd(){}
		void			CreateHwnd(HWND parent){}
		DxColor			GetEraseColor() const;
		virtual	void	SetStep(double step);
		virtual void	SetRange(double minpos, double maxpos);
		virtual void	SetValue(double pos);
		virtual double	GetValue() const;
		void			GetRange(double& minpos, double& maxpos) const;
		CDxChuncker*	GetChunker();
		CDxChuncker*	GetChuncker() const;
		virtual void	Reset(){}


		void			ValueChanged(double val, CDxScrollBar* sender);
	protected:
		CDxChuncker			mChunker;
		double				mMinPos;
		double				mMaxPos;
		double				mCurrentPos;
		double				mStep;
		double				mChunkerOrgOffset{ 12 };
	};




	//+------------------------------------
	//
	// ˮƽ������
	//
	//+-------------------------------------
	class DXUI_API CDxHorizonScrollBar : public CDxScrollBar
	{
		DECLARE_CLASS(CDxHorizonScrollBar)
	public:
		CDxHorizonScrollBar();
		~CDxHorizonScrollBar();
		CDxDecorator*	GetLeftButton();
		CDxDecorator*	GetRightButton();
		void			SetValue(double pos);  // ���û���λ��
		double			GetValue() const;      // ��ȡ���鵱ǰλ��

		double			GetLength();  //  ��ȡ�����ܹ������ĳ���	
		void			SetSliderLength(double length); // ���û���ĳ���
		double			GetSliderLength();
		void			ReceiveEvent(CDxUIEvent* e);
		void			Reset();
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnResizeEvent();
		void			OnRendWindow(IPainterInterface* painter);
	private:
		CDxDecorator		mLeftButton;
		CDxDecorator		mRightButton;
		bool				bIsClicked{ false };
		int					mWidth{ 0 };
	};




	//+----------------------------------
	//
	// ��ֱ������
	//
	//+----------------------------------
	class DXUI_API CDxVerticalScrollBar : public CDxScrollBar
	{
		DECLARE_CLASS(CDxVerticalScrollBar)
	public:
		CDxVerticalScrollBar();
		~CDxVerticalScrollBar();

		CDxDecorator*	GetUpButton();
		CDxDecorator*	GetDownButton();
		void			SetValue(double pos);  // ���û���λ��
		double			GetValue() const;      // ��ȡ���鵱ǰλ��

		double			GetLength();  //  ��ȡ�����ܹ������ĳ���	
		void			SetSliderLength(double length); // ���û���ĳ���
		double			GetSliderLength();
		void			ReceiveEvent(CDxUIEvent* e);
		void			Reset();
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnResizeEvent();
		void			OnRendWindow(IPainterInterface* painter);
	private:
		CDxDecorator		mUpButton;
		CDxDecorator		mDownButton;
		bool				bIsClicked{ false };
		int					mHeight{ 0 };
	};



	//+--------------------------------
	//
	// ˮƽ����
	//
	//+--------------------------------
	class DXUI_API CDxHorizonSlider : public CDxScrollBar
	{
		DECLARE_CLASS(CDxHorizonSlider)
	public:
		CDxHorizonSlider();
		~CDxHorizonSlider();
		DXWindowType	GetWindowSelfDesc() const;
		SIZE			GetHintSize() const;
		void			SetValue(double pos);  // ���û���λ��
		void			ReceiveEvent(CDxUIEvent* e);
		void			OnRendWindow(IPainterInterface* painter);
	};



	//+-----------------------------
	//
	// ��ֱ����
	//
	//+-----------------------------
	class DXUI_API CDxVerticalSlider : public CDxScrollBar
	{
		DECLARE_CLASS(CDxVerticalSlider)
	public:
		CDxVerticalSlider();
		~CDxVerticalSlider();
		DXWindowType	GetWindowSelfDesc() const;
		SIZE			GetHintSize() const;
		void			SetValue(double pos);  // ���û���λ��
		void			ReceiveEvent(CDxUIEvent* e);
		void			OnRendWindow(IPainterInterface* painter);
	};
}


