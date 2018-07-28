#pragma once
#include <functional>

//
// �ú�������� NotifyPropertyChanged �����ĵ���
// ʹ�øú��Զ����ɺ�����,�Լ�һ����Ա����ָ��
// ���Դ����� NotifyPropertyChanged �ĵ����鷳��
//
#ifndef MPropertyNotifer
#define MPropertyNotifer(className,memFun) #memFun,&className::memFun
#endif


//
//  ģ���ź�,MSLOT��ģ�庯��
//
#ifndef MSIGNAL
#define MSIGNAL(className,memFun,obj) #memFun,&className::memFun,obj
#endif

//
// ���������͵ȵ�ת��Ϊ�ַ���������ʽ
//
#ifndef CONVERTTOSTRING
#define CONVERTTOSTRING(other) #other
#endif


//
// ����Class��Ϣ
// ��class��������ʹ��
//
#ifndef DECLARE_CLASS
#define DECLARE_CLASS(className) \
	private:\
	MString ____##className##Name##____{ #className }; \
	static  TL::MClassDynamic<className::MClassFactory>* pclassName; \
	public:\
	static void* MCreateInstance(){\
\
	return new className; \
	}\
	virtual const MString& MClassName() const{\
		\
		return ____##className##Name##____; \
	}
#endif


//
// ��� DECLARE_CLASS ��ʵ��
//
#ifndef IMPLEMENT_CLASS
#define IMPLEMENT_CLASS(className) \
	TL::MClassDynamic<className::MClassFactory>* className::pclassName = \
	new TL::MClassDynamic<className::MClassFactory>(#className, \
	&className::MCreateInstance);
#endif

#ifndef MCreateInstanceFun
typedef std::function<void*()> MCreateInstanceFun;
#endif