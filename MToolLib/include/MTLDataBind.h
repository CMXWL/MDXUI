
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