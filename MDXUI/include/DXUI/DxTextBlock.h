#pragma once
#include "DxLabel.h"
#include "DxScrollBar.h"
#include "DxCaret.h"

namespace DxUI{

	//+-----------------------
	//
	// class CDxTextBlock
	//
	//+-----------------------
	class DXUI_API CDxTextBlock : public CDxLabel
	{
		DECLARE_CLASS(CDxTextBlock)
	public:
		CDxTextBlock();
		~CDxTextBlock();

		DXWindowType	GetWindowSelfDesc() const;
		SIZE			GetHintSize() const;
		void			SetFocus();
		void			KillFocus();
		void			SetSelectedBkColor(const DxColor& col);
		void			SetSelectedTxtColor(const DxColor& col);
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnTextFormat();
		void			OnTextChangedEvent();
		unsigned		GetMaxCharNum() const;
		void			SetMaxCharNum(unsigned num);
		void			ReceiveEvent(CDxUIEvent* e);
		virtual MString GetSelectedText() const;
		virtual void	ReplaceSelectedText(const MString& Text);
		virtual void	InsertText(int pos, const MString& Text);
		virtual void	OnDealTextForLine(unsigned LineIndex);

	msignals:
		void			TextUpdated(MString Text, CDxWidget* sender); // �ı��и���


	public:
		void			UpdateTextEffects();
		void			OnRendWindow(IPainterInterface* painter);
		
	protected:
		CDxVerticalScrollBar   mVerticalBar;
		CDxCaret			   mCaret;
		int					   mCaretIndex{ 0 };     // �������
		int					   mShowLines{ 0 };      // ��ʾ�˶�����
		int					   mLastLineIndex{ -1 }; // ������ʾ����
		int					   mSelectedStartIndex{ 0 }; // ѡ�еĿ�ʼλ��
		int					   mSelectedStopIndex{ 0 };  // ѡ�еĽ���λ��
		bool				   bIsShowScrollBar{ false };
		bool				   bIsTrailingHit{ false };
		bool				   bIsClicked{ false };
		unsigned			   mMaxCharNum;// ����ַ�
		DxColor				   mSelectedBkColor;
		DxColor				   mSelectedTxtColor;
		bool				   bIsReadOnly{ true };

	protected:
		MString				   mPlaceholderText; // ռλ�ı�
		bool				   bIsHasFocus{ false };
	};
}


