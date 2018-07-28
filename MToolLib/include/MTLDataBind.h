#pragma once
#include <MTLProperty.h>
#include <MTLConnect.h>

namespace TL{
	//
	// �ڲ��� MDataBind::Connect ��ʱ�� Ӧ��ʹ�ø������һ����������
	// Connect ֻ���𵥱߰�
	// MSIGNAL ��ָ������Դ Ŀǰһ��Դֻ�ܶ�Ӧһ��slot,����һ��slot���Զ�Ӧ���Դ
	// MSLOT ��ָ����Ϊ���ն���ĺ���
	// ����  MDataBind::Connect ���ò���Ӧ��Ϊ:
	// MDataBind::Connect(
	//                  MSIGNAL(ClassB,SetValue,pBobj),
	//                  MSLOT(&ClassA::SetValue,pAobj)
	//                  );
	//
	// MSLOT �� MSIGNAL �İ�װ�Ե���Щ��Ť,��ͬһ���Ĳ�����Ϊ��
	//
	// ���������ɺ�����˵,ֻ��Ҫʹ��MSLOTֱ�Ӱ�װ����ָ�뼴��
	// MDataBind::Connect(
	//                  MSIGNAL(ClassB,SetValue,pBobj),
	//                  MSLOT(freeFunPtr)
	//                  );
	// freeFunPtr ��һ������ָ�� ��MSLOT�İ�װ�¾Ϳ�����Ϊ�ۺ���ͨ��
	//
	//

	//
	// ʹ�ú��������������Խ��а�
	//
	class MTLDataBind
	{
	public:
		MTLDataBind(){}
		virtual ~MTLDataBind(){}

		//
		// �ڶ���Connect����
		//
		template<class T, class...Args>
		static std::shared_ptr<MConnect<T>> Connect(
			const MString& funName,
			void(T::*fun1)(Args...),
			T* obj1,
			std::function<void(Args...)> eventfun,
			const MTLProperty::ObjTraceType& tracePtr = MTLProperty::ObjTraceType(),
			bool isAsyc = false
			)
		{
			MAddPropertChangedFun(
				funName,
				fun1,
				obj1,
				eventfun,
				tracePtr,
				isAsyc);
			std::shared_ptr<MConnect<T>> connectObj(new MConnect<T>(
				funName,
				obj1,
				eventfun,
				tracePtr,
				isAsyc));
			return connectObj;
		}

		//
		// �ڶ���Ͽ�����
		//
		template<class T, class...Args>
		static void DisConnect(
			const MString& funName,
			void(T::*fun1)(Args...),
			T* obj1,
			std::function<void(Args...)> eventfun,
			const MTLProperty::ObjTraceType& tracePtr = MTLProperty::ObjTraceType()
			)
		{
			MRemovePropertChangedFun(funName, obj1, tracePtr);
		}

	private:


		//
		// ������Ըı亯��
		//
		template<class T, class ...Args>
		static void MAddPropertChangedFun(const MString& funName,
			void(T::*fun)(Args...),
			T* obj,
			std::function<void(Args...)> eventfun,
			const MTLProperty::ObjTraceType& tracePtr,
			bool isAsyc)
		{
			if (obj == nullptr)
				return;
			(obj->BindGroupFun)(funName, tracePtr,eventfun, isAsyc);
		}

		//
		// �Ͽ�����
		//
		template<class T>
		static void MRemovePropertChangedFun(const MString& funName,
			T* obj,
			const MTLProperty::ObjTraceType& tracePtr)
		{
			if (obj == nullptr)
				return;
			(obj->RemoveGroupFun)(funName, tracePtr);
		}
	};
}