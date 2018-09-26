

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
#include  "DxEditWidget.h"

namespace DxUI{
	//+-------------------------
	//
	// CDxEdit �ı��༭��
	// ���ı��ı�ʱ���� TextChanged ���� 
	// ���ı��������ʱ���� TextEnterFinished ���� �ټ���س�����ʧȥ����ʱ���д���
	// ͨ��TL::MTLDataBind::Connect ���к��ⲿͨ��
	// void testFun(const MString& str);
	// DxUI::CDxEdit edit;
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxEdit, TextChanged, &edit),TL::MSLOT(testFun));
	// TL::MTLDataBind::Connect(MSIGNAL(DxUI::CDxEdit, TextEnterFinished, &edit),TL::MSLOT(testFun));
	//
	//+--------------------------
	class DXUI_API CDxEdit : public CDxEditWidget
	{
		DECLARE_CLASS(CDxEdit)
	public:
		CDxEdit();
		~CDxEdit();

		bool			SetWindowStatus(DXWindowStatus status);
		DXWindowType	GetWindowSelfDesc() const;
		SIZE			GetHintSize() const;
		void			KillFocus();
		void			SetPasswordMode(bool isPassword);
		bool			IsPasswordMode() const;
		void			SetPasswordChar(TCHAR ch);
		void			SetTextLayoutLength(int length);
		TCHAR			GetPasswordChar() const;
		void			SetNumOnly(bool isOnlyNum);
		bool			IsNumOnly() const;
		void			SetNumRange(double low, double up);
		void			SetNumIsInt(bool isInt);
		void			OnTextFormat();

		//
		// �ı��ı�ʱ�������������ź�
		// TextEnterFinished �����ݽ���ʱ������ʧȥ���� ��ȡ�����س�
		//
	msignals:
		void			TextChanged(MString CurText, MString PreText,  CDxWidget* sender);
		void			TextEnterFinished(MString Text, CDxWidget* sender);

		TL::MTLVoidEvent<MString, MString, CDxWidget*> Event_TextChanged;
		TL::MTLVoidEvent<MString, CDxWidget*> Event_TextEnterFinished;

	public:
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);

	protected:
		bool			ValidInputData();

	protected:
		bool			bIsOnlyNum{ false };
		bool			bIsPasswordMode{ false };
		TCHAR			mPasswordChar;
		int				mLastTextIndex{ 0 };
		TL::Vector<DXDrawTextInfo> mDrawTextInfo;
		int				mTextLayoutLength{ 10000 };
		double			mLimitDown{ -1e+20 };
		double			mLimitUp{ 1e+20 };
		bool			bIsInt{ false };
	};
}


