#pragma once
#include "DxListItem.h"

namespace DxUI{

	//+-----------------------
	//
	// һ����ѡ���б���
	//
	//+-----------------------
	class DXUI_API CDxCheckableListItem :
		public CDxListItem
	{
		DECLARE_CLASS(CDxCheckableListItem)
	public:
		CDxCheckableListItem();
		~CDxCheckableListItem();
		CDxListItem*	CreateThis();
		bool			DestroyThis();
		void			SetIcon(const MString& icon);
		void			UpdateChildWindowPos();
		bool			OnNotify(DXNotifyUI* NotifyEvent);
		void			SetAny(const mj::MAny& any);
		bool			OnDrawItem(const RECT& rc, IPainterInterface* painter);
	private:
		bool			bIsChecked{ true };
		CDxEffects		mIconEffects;
	};
}


