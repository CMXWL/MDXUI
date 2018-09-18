#pragma once
#include "DxWidget.h"

namespace DxUI{

	///+-----------------------------------------
	//
	// ���б������Լ������С��������ť�Ĵ���
	// ��Ϊ������ʹ��
	//
	//+-------------------------------------------
	class DXUI_API CDxMainWindow : public CDxWidget
	{
		DECLARE_CLASS(CDxMainWindow)
	public:
		CDxMainWindow();
		~CDxMainWindow();

		CDxWidget*		hitTest(int x, int y);
		bool			pointInArea(int x, int y);
		void			setTitle(const MString& Title);
		void			setIcon(const MString& Icon);
		
	private:
		CDxWidget*		pIConLabel{ nullptr };
		CDxWidget*		pMinButton{ nullptr };
		CDxWidget*		pMaxButton{ nullptr };
		CDxWidget*		pStoreButton{ nullptr };
		CDxWidget*		pCloseButton{ nullptr };
		CDxWidget*		pTitle{ nullptr };
	};
}


