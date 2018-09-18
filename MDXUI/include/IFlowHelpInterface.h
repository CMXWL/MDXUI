
///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once


//+------------------------------------------------------------------------------------------
//
// ���̲��Եĸ����ӿ�
// �ýӿ����MAppDAtaʹ��
// Ϊ�˼򵥵�
// ���Դ�MAppManager::AppData��ȡ�ýӿ�
// ����ʵ��ʹ���������Ҫ��ȡ�ýӿ���ô��Ҫʹ�ö��ؼ̳У�
// class MyData : public MAppData,public IFlowHelpInterface{};
// IFlowHelpInterface* FlowHelpPtr = MAppManager::Instance()->AppData<IFlowHelpInterface>();
//
//+-------------------------------------------------------------------------------------------
struct IFlowHelpInterface
{
public:

	//
	// ����������̽ӿ�
	//
	virtual void doSubrayFlow(){}

	//
	// ����Ȳ��Խӿ�
	//
	virtual void doSNTestFlow(){}

	//
	// �ȶ��Բ��Խӿ�
	//
	virtual void doStabilityFlow(){}

	//
	// ͨ��У׼�ӿ�
	//
	virtual void doChannelCalFlow(){}

	//
	// ̽ͷУ׼�ӿ�
	//
	virtual void doProbeCalFlow(){}


	//
	// �ز�ָ����ray�ӿ�
	//
	virtual void doRetestRayFlow(){}

	//
	// �ϵ�����ӿ�
	//
	virtual void doContinueTestFlow(){}
};