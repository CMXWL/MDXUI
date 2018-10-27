///////////////////////////////////////////////////////////////////////////////
//
// MToolLib ---- Mengjin Tool Library
// Copyright (C) 2014-2018 by Mengjin (sh06155@hotmail.com)
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

//-------------------------------------------
// ���̸߳�������
// ��Ҫ��Ժ�̨��������ʹ��
// �����������ߺ�������ģ����
//-------------------------------------------
#pragma once
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

class HThreadHelp
{
public:
	typedef std::function<void()> __Fun_Type; // �ص���������,�ж������Ҫ���в���
	HThreadHelp();
	~HThreadHelp();

	//------------------------------------------------
	// ������Ҫʹ����Ϊ�����ߵ��߳���
	//------------------------------------------------
	void Set_Customer_Thread_Num(size_t num);

	//------------------------------------------------
	// ������Ҫʹ����Ϊ�����ߵ��߳���
	//------------------------------------------------
	void Set_Producer_Thread_Num(size_t num);

	//-------------------------------------------------
	// �����������̺߳���
	//-------------------------------------------------
	void Set_Customer_Fun(__Fun_Type fun);

	//-------------------------------------------------
	// �����������̺߳���
	//-------------------------------------------------
	void Set_Producer_Fun(__Fun_Type fun);

	//-------------------------------------------------
	// �Ƿ���Ϊ�����̲߳���
	//-------------------------------------------------
	void Set_Control_Mode(bool isauto);

	//-------------------------------------------------
	// ��ʼ����,�����������õ��߳�
	//-------------------------------------------------
	void start();
	
	//-------------------------------------------------
	// ���������߳��Ƿ�ȴ�
	//-------------------------------------------------
	void Produce_Wait(bool iswait);

	//-------------------------------------------------
	// �����������߳��Ƿ�ȴ�
	//-------------------------------------------------
	void Customer_Wait(bool iswait);
protected:
	void Thread_For_Producer();
	void Thread_For_Customer();
private:
	std::thread m_customer_thread[32];  // ���8���߳�
	std::thread m_producer_thread[32];  // ���8���߳�

	std::mutex  m_customer_mutex;
	std::mutex	m_producer_mutex;

	std::condition_variable m_customer_condition;
	std::condition_variable m_producer_condition;

	std::recursive_mutex	m_mutex1;
	std::recursive_mutex	m_mutex2;

	bool					b_is_exit{ false };
	bool					b_is_start{ false };
	bool					b_is_wait_for_producer{ false };
	bool					b_is_wait_for_customer{ false };
	bool					b_is_auto_control_thread{ true };

	size_t					m_customer_thread_num{ 0 };
	size_t					m_producer_thread_num{ 0 };
	unsigned long long		m_producer_num{ 0 };//��������
	unsigned long long		m_customer_num{ 0 };//���Ѵ���

	__Fun_Type				m_producer_fun{ nullptr };
	__Fun_Type				m_customer_fun{ nullptr };
};

