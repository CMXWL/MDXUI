

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "DxWindowImpl.h"
#include "DxConfig.h"
#include "MDx11BufferManage.h"
#include "MDx11LayoutManage.h"
#include "MDx11Camera.h"
#include "DxPainter.h"
#include <gdiplus.h>

namespace DxUI{
	

	class CDxWidget;

	//+-----------------------------
	//
	// class CDxMouseEvent
	//
	//+-----------------------------
	class DXUI_API CDxMouseEvent{
	public:
		CDxMouseEvent(DXMouseButton button, DXMouseAction action, POINT pt, POINT lastpt, bool isMove);

		POINT CurrentPos() const;
		POINT LastPos() const;
		DXMouseButton Button() const;
		DXMouseAction Action() const;
		bool		  IsMove() const;
	private:
		POINT mPoint;
		POINT mLastPoint;
		DXMouseButton   mButton;
		DXMouseAction	mAction;
		bool			bIsMove;
	};

	//+-----------------------------
	//
	// class CDxKeyBoardEvent
	//
	//+-----------------------------
	class DXUI_API CDxKeyBoardEvent{
	public:
		CDxKeyBoardEvent(WPARAM key,bool isPress);
		WPARAM Key() const;
		bool IsPress() const;
	private:
		WPARAM mKey;
		bool   bIsPress;
	};


	//+------------------------
	//
	//
	// class CDxRendImpl
	//
	//+-------------------------
	class DXUI_API CDxRendImpl : public CDxWindowImpl
	{
		DECLARE_CLASS(CDxRendImpl)
	public:
		CDxRendImpl();
		~CDxRendImpl();
		
		//+------------------------------------------
		//
		// ��Բ�ͬ�Ĵ�������ѡ��ʹ�ò�ͬ�ĳ�ʼ������
		// OnInitResource2D ��ʼ��2D����
		// OnInitResource3D ��ʼ��3D���Ƶ���Դ
		// OnRender2D ����2D����
		// OnRender3D ����3D����
		//
		//+---------------------------------------------
		virtual bool OnInitResource2D();
		virtual bool OnInitResource3D();
		virtual void UnInitResource();
		virtual bool OnLoadContent();
		virtual void OnReShape(int w, int h);
		
		void		 OnRepaintEvent(); // ǿ�Ƶײ㴰���ػ�
		virtual void OnPainterEvent(); // �ú����������߳�����ִ��,�첽���ͻ�����ϢȻ����� OnRender
		virtual void OnRender();       // �ú�������ִ�� �߳������Ƿ����ֱ�ӵ���δ֪
		virtual void OnRender2D();
		virtual void OnRender3D();
		virtual void SaveToFile(const MString& fileName);
		virtual void RendToBitmap(ID2D1RenderTarget* RendTargert,  int width, int height, ID2D1Bitmap*& outBitmap);
	
		virtual void OnRendWindow(IPainterInterface* painter);
	
		virtual void OnTimer();
		virtual bool OnMouseEvent(const CDxMouseEvent& e);
		virtual bool OnKeyBoardEvent(const CDxKeyBoardEvent& e);
		bool		 OnMessageHandle(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);

		virtual void			SetWindowShape(DXShape shape);
		virtual void			SetViewPort(const DxRectI& viewArea);
		virtual DXShape			GetWindowShape() const;
		virtual bool			SetWindowStatus(DXWindowStatus status);
		virtual DXWindowStatus	GetWindowStatus() const;
		virtual IPainterInterface* GetPainter();
		virtual IPainterInterface* GetPainter() const;

		//
		// �Ҽ������ʱ���ִ�иú���
		// x y �������������λ��
		//
		virtual void ContextMenuEvent(int x, int y){}

		HDC						GetDC();
		virtual ID2D1HwndRenderTarget*	GetRenderTarget();
		

		//
		// ����״̬�ı�ʱ���͸��¼�
		//
		void					OnWindowStatusChanged(DXWindowStatus status,CDxWidget* sender);

	protected:
		void					ClearWndRelatedResource();
		//
		// ����ִ�к���
		//
		virtual void			OnIdle();


	protected:

		//+---------------------
		//
		// 2D ��Ⱦ���
		//
		//+----------------------
		ID2D1HwndRenderTarget*			pRendTarget{ nullptr };
		ID2D1GdiInteropRenderTarget*	pGdiRendTarget{ nullptr };
		HDC								mHDC{ nullptr };
		IPainterInterface*				pPainter{ nullptr };


		//+------------------------
		//
		// ��ȾΪλͼ
		//
		//+------------------------
		ID2D1RenderTarget*			pBitmapRendTarget{ nullptr };



		//+-----------------------
		//
		// ��¼��ǰ���ڲ����Ķ���
		//
		//+-------------------------
		CDxWidget*					pFocusWindow{ nullptr };
		CDxWidget*					pHoverWindow{ nullptr };
		CDxWidget*					pClickedWindow{ nullptr };
		bool						bIsTraceMouse{ true };
		POINT						mLastMousePos;
		bool						bRightButtonDown{ false };
		bool						bLeftButtonDown{ false };
		bool						bIsRending{ false };

		//+------------------------------------
		//
		//  ��ʾ��Ϣ
		//
		//+------------------------------------
		CDxWidget*					pToolTipWindow{ nullptr };
		int							mTooltipHoverTime{ 400 };


		DXWindowStatus				mWindowStatus{ Dx_Normal };
		DXShape						mWindowShape{ Dx_Rectangle };
	};

}

