
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
#include "MString.h"
#include <map>
#include <memory>
#include <MTLEvent.h>
struct ITimer;

namespace DxUI{
	//+-----------------------------------------
	//
	// ��ʱ��
	//
	//+-----------------------------------------
	class MSTRING_API CDxTimer
	{
	public:
		CDxTimer();
		~CDxTimer();
		void  SetTimer(int time_ms);
		void  KillTimer();
		
	
		//
		// id , ���, ���Ͷ���
		//
		TL::MTLVoidEvent<int, CDxTimer*> Event_TimeOut;
	private:
		int						 mId{ -1 };

	private:
		CDxTimer(const CDxTimer&) = delete;
		CDxTimer& operator=(const CDxTimer&) = delete;
	};


	//+----------------------------------------------------
	//
	// ����ʱ����
	// ����ֵʱ�䵥λ ms
	//
	//+-----------------------------------------------------
	class MSTRING_API CDxTimerEx : public CDxTimer
	{
	public:
		CDxTimerEx();
		~CDxTimerEx();
		void  Start();      // ��ʼ��ʱ
		void  Reset();
		void  Stop();
		void  Tick();
		double DeltaTime() const; // ��������Tick֮���ʱ��
		double TotalTime() const; // ���س忪ʼ�����һ��Tick֮���ʱ��
		void   Restart();
		double Elapsed() const;

	private:
		std::shared_ptr<ITimer>  mTimer;
	};
}

