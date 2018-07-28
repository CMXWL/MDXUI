#pragma once
#include "DxWindow.h"

namespace DxUI{
	//
	// class CDxSpliterWindow
	// �ָ��
	//
	class DXUI_API CDxSpliterWindow :
		public CDxWindow
	{
		DECLARE_CLASS(CDxSpliterWindow)
	public:
		CDxSpliterWindow();
		CDxSpliterWindow(DXDirection Direct); // ˮƽ���ߴ�ֱ
		~CDxSpliterWindow();


		void	SetFirstWindowSize(int Size); // ����һ�����ڳ�ʼ�߶Ȼ��߳�ʼ���
		void	SetFirstWindowRatio(double ratio); // �����������ڵĳ�ʼ�߶Ȼ��߳�ʼ��ȵı���
		void	AddChild(CDxWidget* Window);
		void	UpdateChildWindowPos();
		bool	OnNotify(DXNotifyUI* NotifyEvent);
		void	OnRendWindow(IPainterInterface* painter);
	private:
		int			mFirstPartSize{ -1 };
		double		mFirstRatio{ 1.0 };
		DXDirection mExtentDirect;
		CDxWidget*  pWindow1{ nullptr };
		CDxWidget*  pWindow2{ nullptr };
		bool		bIsMove{ false };
		POINT		mOldPoint;
	};
}


