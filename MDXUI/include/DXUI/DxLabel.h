#pragma once
#include "DxWindow.h"


namespace DxUI{
	//+------------------------------
	//
	// CDxLabel
	//
	//+------------------------------
	class DXUI_API CDxLabel : public CDxWidget
	{
		DECLARE_CLASS(CDxLabel)
	public:
		CDxLabel();
		~CDxLabel();
		void					CreateHwnd(){}
		void					CreateHwnd(HWND parent){}
		bool					SetWindowStatus(DXWindowStatus status){ return false; }
		DXWindowType			GetWindowSelfDesc() const;
		SIZE					GetHintSize() const;
		void					OnResizeEvent();
		void					OnTextChangedEvent();
		virtual	void			OnTextFormat();


		void					ClearTextEffects();
		CDxEffects*				GetTextEffects();
		void					SetTextAlignment(DXTextAlignment Alignment); // �����ı����뷽ʽ
		void					SetTextFont(int iStart, int nLen, const MString& FontName, int fSize, bool isBold = false, bool isItalic = false); // �趨ָ���ַ�������
		void					SetTextFont(const MString& FontName, int fSize, bool isBold = false, bool isItalic = false); // ��������ָ�������彫ʹ�ø�����
		void					SetTextColor(int iStart, int nLen, const DxColor& col); // �趨ָ���ַ�����ɫ
		void					SetTextSize(int iStart, int nLen, int fSize);           // �趨ָ���ַ��Ĵ�С
		void					SetTextSelectedColor(int iStart, int nLen, const DxColor& bKcol, const DxColor& TxtCol);// �趨ѡ��ʱ�ı���ɫ
		void					SetTextHighLightColor(int iStart, int nLen, const DxColor& col);				// �趨ѡ���ı��ĸ�����ɫ
		void					OnRendWindow(IPainterInterface* painter);

	protected:
		CDxEffects				mTextEffective;
		MString					mRenderText;
		unsigned				mStartLine{ 0 };
		unsigned				mTatalLines;
		unsigned				mStartIndex{ 0 };  // ��Ⱦ�ı��Ŀ�ʼ����
		unsigned				mStopIndex{ -1 };   // ��Ⱦ�ı��Ľ�������
		TL::Vector<DXLineTextInfo> mTextLinesInfo;
	};
}


