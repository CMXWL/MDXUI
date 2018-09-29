

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
#include "DxWindowImpl.h"
#include "DxRendImpl.h"
#include "DxEffects.h"

namespace DxUI{
	typedef const DxDimI& CDxDimI;
	class CDxUIEvent;
	class CDxLayout;
	class CDxCaption;
	class CDxStackedWidget;

	//+------------------------------------
	//
	// �ؼ����ڵĻ���
	// ÿһ�����ڶ���һ����֤���ظ���id��Ϊ��ݱ�ʶ
	// ����4�����ⰴť��ID
	// 0 �������
	// 1 ���ڻ�ԭ���
	// 2 ������С��
	// 3 ���ڹرմ���
	//
	//+------------------------------------
	class DXUI_API CDxWidget : public  CDxRendImpl, public INotifyUI
	{
		DECLARE_CLASS(CDxWidget)

		friend class CDxStackedWidget;
		friend class CDxTableWidget;
	public:
		CDxWidget();
		~CDxWidget();


		//
		// ��ȡ����������
		//
		virtual DXWindowType	GetWindowSelfDesc() const;

		//
		// ���ݴ���������Ҵ���
		//
		CDxWidget*		GetWindowFromPoint(int x, int y, HWND hwnd);
		CDxWidget*		GetWindowFromIdentify(int identify);
		const CDxEffects* GetEffects() const;
		CDxEffects*		GetEffects();
		CDxEffects*		GetSurfaceEffects();
		void			SetSurfaceEnable(bool isEnable);
		void			SetEffects(const CDxEffects* effects);


		//+-------------------
		//
		// ��ʱ����Ӧ����
		//
		//+--------------------
		void			OnTimer(){}




		//+---------------------------
		//
		// ����Hwnd
		//
		//+---------------------------
		virtual void	CreateHwnd();
		virtual void	CreateHwnd(HWND parent);

		virtual void	SetParent(CDxWidget* parent);
		virtual CDxWidget* GetParent();
		virtual CDxWidget* GetVisibleParent();


	

		//+-----------------
		//
		// ���ô���λ��
		//
		//+------------------
		virtual void	SetGeometyDim(CDxDimI x, CDxDimI y, CDxDimI w, CDxDimI h);
		virtual void	GetGeometyDim(DxDimI& x, DxDimI& y, DxDimI& w, DxDimI& h);
		virtual void	SetGeomety(const DxRectI& rc);
		virtual void	SetPosition(int x, int y);
		virtual void	SetSize(int w, int h);
		virtual void	UpdateArea();


		//+--------------------------------------
		//
		// �޸���������ƫ����Ϣ
		//
		//+--------------------------------------
		void			SetXOffset(int offset);
		void			SetYOffset(int offset);
		void			SetWOffset(int offset);
		void			SetHOffset(int offset);

		void			AddXOffset(int offset);
		void			AddYOffset(int offset);
		void			AddWOffset(int offset);
		void			AddHOffset(int offset);


		//
		// ������������
		//
		virtual void	SetLimitSize(int minx, int maxx, int miny, int maxy);
		virtual void	GetLimitSize(int& minx, int& maxx, int& miny, int& maxy);

		//
		// ͼ����ı���������㷽ʽ�ǻ��� mRendArea �����
		//
		virtual void	SetImageArea(CDxDimI x, CDxDimI y, CDxDimI w, CDxDimI h);
		virtual void	SetTextArea(CDxDimI x, CDxDimI y, CDxDimI w, CDxDimI h);
		virtual void	GetTextArea(DxDimI& x, DxDimI& y, DxDimI& w, DxDimI& h);
		virtual void	GetIamgeArea(DxDimI& x, DxDimI& y, DxDimI& w, DxDimI& h);


		virtual void	SetIamgeIsExpend(bool isExpend);
		virtual void	SetTextAreaIsLimit(bool isLimit);
	
	
		//
		// ����id���Ҵ��� ���� ���� ������Ҵ���
		// �ݹ���� �Ӵ���
		//
		virtual CDxWidget*	FindWindowFromId(int id);
		virtual CDxWidget*	HitTest(int x, int y);  // ������ԣ�ͨ��һ������ҵ���Ӧ�Ŀؼ�

		//
		// ��ѯһ�����Ƿ����ڴ�����
		//
		virtual bool		PointInArea(int x, int y); // ���һ�����Ƿ����ڿؼ�֮��


		//
		// �Ӵ��ڻ�ص��ú������¼����ݵ�������
		//
		virtual void	ReceiveEvent(CDxUIEvent* e);
		virtual void	SetFocus();
		virtual void	KillFocus();
		virtual void	StartTimer(int mselapsed); // ������ʱ��
		virtual void	StopTimer();  // �رն�ʱ��

		//
		// ���¼����ݳ�ȥ
		// �ò�������·�ɵ������ڵ� ReceiveEvent ��
		//
		void			SendEvent(CDxUIEvent* e);

		//
		// ���ڳߴ��Ƿ���游���ڵĳߴ�
		//
		void			SetWidthFlowParent(bool isFlow);
		void			SetHeightFlowParent(bool isFlow);


		bool			IsWidthFlowParent() const;
		bool			IsHeightFlowParent() const;

		//
		// ʹ���������ϵ
		// �������ϵʹ�õ��� һ���������� + ƫ�ƴ�С
		//
		void			SetCoordMethod(bool isRelativeCoord);

		//
		// �������
		//
		void			SetAspect(double aspect);

		//
		// Pad ����Ӱ�쵽 �ı����� ����ͼƬ����
		//
		void			SetPadding(RECT pad);
		RECT			GetPadding() const;
		bool			IsRelativeCoord() const;
		double			GetAspect() const;

		//
		// ��ȡ��ǰ����������HWND
		//
		virtual HWND	GetRootHwnd() const;

		//
		// ��ȡ��ǰ��������ڸ����ڵ�ƫ�ƴ�С �����Ǵ��� HWND �Ĵ���
		//
		virtual POINT	GetRootOffset() const;


		//+------------------------------------
		//
		// �̶���С�Ŀؼ�
		//
		//+------------------------------------
		virtual void	SetFixWidth(int w);
		virtual void	SetFixHeight(int h);
		virtual void	SetFixSize(int w, int h);
		virtual int		GetFixWidth() const;
		virtual int		GetFixHeight() const;
		virtual SIZE	GetHintSize() const;




		//+--------------------------------------
		//
		// �߿����
		//
		//+--------------------------------------
		virtual void	SetSizeBox(const RECT& rect);
		virtual void	SetCaptionBox(const RECT& rect);
		virtual void	SetMaxSize(const SIZE& size);
		virtual void	SetMinSize(const SIZE& size);
		virtual void	SetMaxHeight(int height);
		virtual void	SetMaxWidth(int width);
		virtual void	SetMinHeight(int height);
		virtual void	SetMinWidth(int width);
		virtual void	SetRoundRadius(const SIZE& size);
		virtual void	SetBorderSize(double size);
		virtual void	SetBorderColor(const DxColor& col);
		virtual void	SetNeedBoder(bool isNeed);
		virtual void	SetNeedBorder(bool isNeed); // �޸��������ķ�����

		virtual RECT    GetSizeBox() const;
		virtual RECT	GetCaptionRect() const;
		virtual SIZE    GetMaxSize() const;
		virtual SIZE	GetMinSize() const;
		virtual SIZE	GetRoundRectSize() const;
		virtual int		GetBorderSize() const;
		virtual DxColor GetBorderColor() const;
		virtual bool	IsNeedBorder() const;

		virtual int		GetWidth() const;
		virtual int		GetHeight() const;
		virtual int		GetX() const;
		virtual int		GetY() const;



		//+----------------------------------
		//
		// �ߴ�
		//
		//+----------------------------------
		virtual void	ReSize(unsigned w, unsigned h);
		virtual DxRectI	GetClientRect() const;
		virtual DxRectI	GetFrameRect() const;
		virtual DxRectI	GetGlobalRect() const;


		//
		// ��ȡһ����Ч���� ����Ҫ�ػ�ô��ڵ�ʱ����Ҫ��������Ϊ�ػ�����
		//
		virtual void	SetInvalidateRect(const DxRectI& rc);
		virtual DxRectI	GetInvalidateRect() const;
		virtual void	SetEraseColor(const DxColor& col);
		virtual DxColor GetEraseColor() const;
		virtual void	SetClipRect(const DxRectI& rect);
		virtual DxRectI& GetClipRect();
		virtual const DxRectI& GetClipRect() const;
		virtual void	SetSelected(bool isSelected);
		virtual bool	IsSelected();
		virtual void	SetReadOnly(bool isReadOnly);



		//+-----------------------------------
		//
		// ����
		//
		//+-----------------------------------
		virtual void		SetLayout(CDxLayout* layout);
		virtual CDxLayout*	GetLayout() const;
		virtual void		SetSpan(int index, int span){}
		virtual void		SetMargin(int left, int top, int right, int bottom){}
		virtual void		SetMargin(int margin){}
		virtual void		SetSeparation(int separation){}
		virtual	void		AddWidget(CDxWidget* widget, int row, int col, int rowspan, int colspan, DXAlignment alignment = Dx_AlignCenter){}
		virtual void		OnLayoutWindowChanged(bool isAdd, CDxWidget* window);
		virtual void		LayoutWindowChanged(bool isAdd, CDxWidget* window);

		


		//+-----------------------
		//
		// �ı�
		//
		//+-----------------------
		MString&		GetText();
		const MString&	GetText() const;
		virtual void	SetText(const MString& content);
		virtual void	AppendText(const MString& content);
		virtual void	SetTextAlignment(DXTextAlignment aligment);
		virtual void	Clear();


		//+------------------------
		//
		// ��ʾ
		//
		//+-----------------------
		void SetToolTip(const MString& Tip);
		const MString& GetToolTip() const;



		//+---------------------
		//
		// ״̬
		//
		//+---------------------
		void			SetDisabel();
		void			SetEnabel();
		bool			IsDisable();
		bool			IsEnabel();
		void			SetEnabled(bool isEnable);
		void			SetDisableColor(const DxColor& col);


		virtual void	SetStackedWindowIsVisible(bool isVisible);


		//+----------------------
		//
		// ��ӱ�����
		//
		//+----------------------
		virtual void	SetCaptionHeight(int h);
		virtual int		GetCaptionHeight() const;
		virtual void	SetCaption(CDxCaption* caption = nullptr);
		CDxCaption*		GetCaption();
		virtual void	SetTitle(const MString& Title);
		const MString&	GetTitle() const;
		virtual void	SetIcon(const MString& Icon);
		const MString&  GetIcon() const;

		MString			GetParentIcon() const;
		MString         GetParentTitle() const;


		//+-----------------------
		//
		// ���ܲ���ϵͳ��֪ͨ
		//
		//+-----------------------
		bool			OnNotify(DXNotifyUI* NotifyEvent);


		//+-----------------------
		//
		// �����Ӵ��ڵ�����
		//
		//+------------------------
		virtual void	UpdateChildWindowPos();


		//
		// ���ߴ緢���仯��ִ�� OnResizeEvent ����
		// ���ı������ı�ʱ��ִ�� OnTextChangedEvent
		// �����巢���ı�ʱ��ִ�� OnFontChangedEvent
		//
		virtual void	OnResizeEvent();
		virtual void	OnForceUpdate();
		virtual void	OnTextChangedEvent(){}
		virtual void	OnFontChangedEvent(){}
		virtual void	OnQueueEvent(unsigned queueId){}
		virtual void	WndDestroyEvent(CDxWidget* sender);




		//+-----------
		//
		// ��ʾ����
		//
		//+-----------
		virtual void		Show();
		virtual void		ShowMaximized();
		virtual void		Show(int x, int y);
		virtual void		Hide();
		virtual int			Exec();

		bool				IsNeedRender();


		//+----------------------
		//
		// �Ӵ���
		//
		//+----------------------
		virtual void	AddChild(CDxWidget* childWindow);
		virtual void	RemoveChild(CDxWidget* childWindow);
		virtual bool	HaveChild() const;


		//
		// ÿ���Զ���Ĵ�����д�ú������д��ڻ���
		//
		virtual void	OnRendWindow(IPainterInterface* painter); 



		//
		// ���ñ���ɫ
		//
		void			SetBackGroundColor(const DxColor& col);
		const DxColor&  GetBackGroundColor() const;
		virtual	void	SetOpacity(double val); // ���ô��ڵĲ�͸����[0,1] 1 ��ʾ��͸�� 0 ��ʾȫ͸��
		double			GetOpacity() const;
		virtual void	SetCoordHwnd(HWND hwnd);
		virtual bool	HasFloatWindow(); // ���Ƹ�������
		void			OnIdle();


		//
		// ��ͨ���ⲿ��������ݽ������ں�������ܽ���
		// Ŀǰֻ֧��Attach ��֧��Detach
		//
		void			AttachHwnd(HWND hwnd);
		


		//+---------------------------------
		//
		// ���ݳ�Ա
		//
		//+---------------------------------
	protected:
		CDxWidget*				pParent{ nullptr };
		CDxLayout*				pLayout{ nullptr };
		CDxCaption*				pCaptionLabel{ nullptr };

		DxDimI					mXDim;
		DxDimI					mYDim;
		DxDimI					mWDim;
		DxDimI					mHDim;



		DxRectI					mRendArea;
		DxRectI					mFrameArea;
		DxRectI					mGlobalArea;   
		DxRectI					mCacheRect;
		DxRectI					mInvalidRect;
		RECT					mPadding;
		DxRectI					mOldClipRect;
		DxRectI					mClipRect;// �ü�����

		double					mAspect{ 1.0 };
		bool					bIsUseRelativCoord{ false };


		int						mFixWidth{ -1 };
		int						mFixHeight{ -1 };
		bool					bWidthFlowParent{ false }; // ��ȸ��游���ڵı仯���仯
		bool					bHeightFlowParent{ false };// �߶ȸ��游���ڵı仯���仯

		//
		// ����ͼƬ������
		//
		DxDimI					mImageAreaX;
		DxDimI					mImageAreaY;
		DxDimI					mImageAreaW;
		DxDimI					mImageAreaH;
		DxRectI					mImageRendArea;
		bool					bIsExpend{ true };// �������չ ʹ�ô���������л���


		//
		// �ı�����
		//
		DxDimI					mTextAreaX;
		DxDimI					mTextAreaY;
		DxDimI					mTextAreaW;
		DxDimI					mTextAreaH;
		DxRectI					mTextRendArea;


		//
		// ״̬
		//
		DxColor					mDisabelColor;
		DxColor					mBackGroundColor;
		DxColor					mClearColor;
		


		//
		// ����
		//
		MString					mText;
		DxColor					mTextColor;
		DXTextAlignment			mTextAlignment{ Dx_AlignNormal };
		MString					mTitle;
		MString					mIcon;
		MString					mToolTip;


		//
		// �Ӵ���
		//
		TL::Vector<CDxWidget*>	mChildList;

		//
		// �߿�
		//
		bool						bIsNeedBorder{ false };
		double						mBorderWidth{ 0 };
		double						mOldBorderWidth{ 0 };
		DxColor						mBorderColor;


		//
		// Ч��
		//
		CDxEffects					mEffects;
		HWND						mCoordHwnd{ nullptr };

		//
		// ����Ч��
		// Ҳ��������ɻ���֮���ڱ�����һ��Ч��
		// ͨ��ֻ������ɫ֮�����
		// ����ͻ�ֱ��Ӱ�쵽ʵ�ʵ�����
		//
		CDxEffects					mSurfaceEffects;
		bool						bIsNeedSurfaceEffects{ false };
	};



	//+--------------------
	//
	// CDxCaption 
	//
	//+--------------------
	class DXUI_API CDxCaption : public CDxWidget{
		DECLARE_CLASS(CDxCaption)
	public:
		CDxCaption();
		void	CreateHwnd();
		void	CreateHwnd(HWND parent);
		void	OnRendWindow(IPainterInterface* painter); 

		CDxEffects*			GetIconEffects();
		CDxEffects*			GetMinButtonEffects();
		CDxEffects*			GetMaxButtonEffects();
		CDxEffects*			GetCloseButtonEffects();
		CDxEffects*			GetRestoreButtonEffects();
	private:
		CDxWidget*			pIconLabel{ nullptr };
		CDxWidget*			pMinButton{ nullptr };
		CDxWidget*			pMaxButton{ nullptr };
		CDxWidget*			pRestoreButton{ nullptr };
		CDxWidget*			pCloseButton{ nullptr };
	};




	//+--------------------------------------------
	//
	// ����ת��
	//
	//+--------------------------------------------
	template<class T>
	T* object_cast(CDxWidget* ptr){
		try{
			T* obj = dynamic_cast<T*>(ptr);
			return obj;
		}
		catch (...){
			return nullptr;
		}
	}
}


