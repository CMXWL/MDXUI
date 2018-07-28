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

	protected:
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


