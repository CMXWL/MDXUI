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

