

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "DxWindow.h"
#include <ITimer.h>
#include <memory>
namespace DxUI{
	//
	// �򵥵Ķ���Ч��
	// ��Ҫ��дUpdateTime(doubel time)�ӿ�
	// ����������ݵ���0��ô��ʾû�м�ʱ����
	//
	class DXUI_API CDxAnimationWindow :
		public CDxWindow
	{
		DECLARE_CLASS(CDxAnimationWindow)
	public:
		CDxAnimationWindow();
		~CDxAnimationWindow();

		//
		// ��ʼ ��λms
		//
		bool IsStarted() const;
		void StartAnimation(int timeinter = 300);
		void StopAnimation();
		void OnTimer();
		void OnRendWindow(IPainterInterface*  painter);


		

		//
		// ͨ���ýӿ�ʵ�ֶ���Ч������
		//
		virtual void UpdateTime(IPainterInterface*  painter,double time);

	public:
		static IPainterInterface::TransformMatrix RotateMatrix(double angle,const DxPointI& pos); // ��ת
		static IPainterInterface::TransformMatrix TransformMatrix(int x, int y);// ƽ��
		static IPainterInterface::TransformMatrix ScaleMatrix(double x, double y, const DxPointI& pos);// ����
		static IPainterInterface::TransformMatrix SkewMatrix(double x, double y, const DxPointI& pos);// ����
		static IPainterInterface::TransformMatrix IdentifyMatrix();//��λ����
		static IPainterInterface::TransformMatrix Producat(const IPainterInterface::TransformMatrix& left, const IPainterInterface::TransformMatrix& right); // ������

	private:
		std::shared_ptr<ITimer> mTimer;//��ʱ��
		bool		bIsStart{ false };
	};
}


