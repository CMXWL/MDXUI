#pragma once
#include "DxCheckBox.h"
namespace DxUI{
	//+------------------------------------------------------------
	//
	// �˵���
	// �����Ҫ���»���item����ۣ�����̳к���дOnDrawItem����
	// ��Ϊ�����дOnRendWindow���л��漰��һЩ�ü�ϸ��
	// OnDrawItem ��д�ú������ÿ��ǲü�ϸ��
	//
	//+-------------------------------------------------------------
	class DXUI_API CDxAction :
		public CDxCheckBox
	{
		friend class CDxMenu;
		DECLARE_CLASS(CDxAction)
	public:
		CDxAction();
		~CDxAction();
		DXWindowType	GetWindowSelfDesc() const;
		DxColor			GetEraseColor() const;
		DxRectI			GetInvalidateRect() const;
		void			SetCheckable(bool isable);
		void			SetIcon(const MString& Text);
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			OnRendWindow(IPainterInterface* painter);
		int				GetWidth() const;
		int				GetHeight() const;
	protected:
		void			SetMenu(CDxMenu* menu);
		int				GetIconAreaWidth() const;
		void			SetIconAreaWidth(int w);
		
	protected:
		void			UpdateChildWindowPos();
		CDxMenu*		pRelativeMenu{ nullptr }; // �����˵�
		bool			bIsNeedIconAreaW{ false };
	};


	//+--------------------------
	//
	// ֻ����һ������
	//
	//+---------------------------
	class DXUI_API CDxSpliter : public CDxAction{
		friend class CDxMenu;
		DECLARE_CLASS(CDxSpliter)
	public:
		CDxSpliter();
		~CDxSpliter();
		int				GetHeight() const;
		void			OnRendWindow(IPainterInterface* painter);
	protected:
		void			UpdateChildWindowPos();
	};
}


