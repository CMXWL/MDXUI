#pragma once
#include <comdef.h>

//
// ��ʱ��
//
interface __declspec(uuid("97694F70-72BF-467E-9778-57E010586DE0")) ITimer : public IUnknown
{
	//
	// ����һ���¶���
	//
	virtual ITimer* __stdcall CreateNewObj() = 0;

	//
	// ��ȡ��Reset��ʼ��ʱ��
	//
	virtual float TotalTime()const = 0;

	//
	// ��ȡ���ε���Tick֮���ʱ��
	//
	virtual float DeltaTime()const = 0;

	//
	// ���ü�ʱ��
	//
	virtual void Reset() = 0;

	//
	// ��ʼ��ʱ
	//
	virtual void Start() = 0;

	//
	// ��ͣ��ʱ
	//
	virtual void Stop() = 0;

	//
	// ͨ����ѯcpu�ĵδ���Ȼ����������ε��øú�����ʱ��������Ϊ��λ��ͨ��DeltaTime���Ի�ȡ
	//
	virtual void Tick() = 0;
};