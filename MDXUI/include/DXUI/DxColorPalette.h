#pragma once
#include "DxWindow.h"

namespace DxUI{
	//+---------------------------
	//
	//
	// class CDxColorPalette
	// ��ɫ��
	//
	//+---------------------------
	class DXUI_API CDxColorPalette :
		public CDxWindow
	{
		DECLARE_CLASS(CDxColorPalette)
	public:
		CDxColorPalette();
		~CDxColorPalette();
		DxColor		GetResult() const;

		//
		// connect�ú�������ʵʱ��ȡ��ɫ
		//
		void		ColorChanged(DxColor col, CDxWidget* sender);

	protected:
		bool	OnNotify(DXNotifyUI* NotifyEvent);
		void	UpdateChildWindowPos();
		void	UpdateColor();
		void	UpdateBarColor();
		void	OnRendWindow(IPainterInterface* painter);
	private:
		ID2D1Bitmap*		pBitmap{ nullptr };
		ID2D1Bitmap*		pBarBitmap{ nullptr };
		ID2D1RenderTarget*  pRendTargetCach{ nullptr };
		DxRectI				mColorRect;
		DxRectI				mSaturationRect;
		DxRectI				mSliderRect;
		DxRectI				mShowColorRect;
		DxPointI			mColorPos;
		DxPointI			mSlidePos;
		bool				bIsMoveSlider{ false };
		int					mCurH{ 200 };
		int					mCurS{ 200 };
		int					mCurB{ 100 };
		DxColor				mColor;
	};
}


