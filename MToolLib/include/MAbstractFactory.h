#pragma once

#include "MParamWrap.h"

//
// ���󹤳�����
//
namespace mj{

	template<class T>
	struct TypeDispatch{};

	//
	// Ĭ�Ϲ�������
	//
	template<class T>
	struct MDefaultAFHolder{
		virtual T* DoCreate(TypeDispatch<T>){
			return new T();
		}
		virtual void DoDestroy(T*& ptr, TypeDispatch<T>){
			if (ptr){
				delete ptr;
				ptr = nullptr;
			}
		}
		virtual ~MDefaultAFHolder(){}
	};



	template<class T, template<class> class H = MDefaultAFHolder>
	class MAbstractFactory : public mjTL::MTLClass<T, H>{
	public:
		//
		// ����
		//
		template<class R>
		R* Create(){
			H<R>& abf = *this;
			return abf.DoCreate(TypeDispatch<R>());
		}

		//
		// ����
		//
		template<class R>
		void Destroy(R*& ptr){
			H<R>& abf = *this;
			abf.DoDestroy(ptr,TypeDispatch<R>());
		}
	};
}