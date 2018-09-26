

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


