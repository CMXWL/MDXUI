

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
		TL::MTLVoidEvent<MString, CDxWidget*> Event_TextUpdated;

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


