#pragma once
#include "DxFloatWindow.h"
using DxUI::CDxWindow;
using DxUI::DxColor;
using DxUI::DxPointD;
using DxUI::IPainterInterface;
using DxUI::RgbI;
using DxUI::DXFontInfo;
using DxUI::DXAlignment;
using DxUI::DXNotifyUI;
using DxUI::DXWindowStatus;

//+------------------------------------------
//
// �Ի����ؼ� CDxFloatWindow �Ľ�һ����װ
//
//+-------------------------------------------
class DXUI_API MFlotWindow :
	public DxUI::CDxFloatWindow
{
	DECLARE_CLASS(MFlotWindow)
public:
	MFlotWindow();
	~MFlotWindow();
	void			SetCaptionMinHeight(int height);
	void			SetNeedCloseButton(bool isNeed);
	CDxWidget*		HitTest(int x, int y);
	bool			PointInArea(int x, int y);
	bool			OnNotify(DXNotifyUI* NotifyEvent);
	void			OnRendWindow(IPainterInterface* painter);
protected:
	void			UpdateChildWindowPos();

private:
	int				mCaptionMinHeight{ 20 }; // ���ڱ�������͸߶�
	bool			bIsNeedCloseButton{ true };
	int				mSlideForOpacity{ 4 };
	POINT			mSlidePos;
	bool			bIsNeedSlider{ true };
	bool			bIsMoveSlider{ false };
	DXWindowStatus	mSlideStatus;
};

