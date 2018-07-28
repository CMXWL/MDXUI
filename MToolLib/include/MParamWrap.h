#pragma once
#include "MEmptyType.h"

//
// bool �⸲��
//
struct MTrue{
	static const bool value = true;
};

struct MFalse{
	static const bool value = false;
};

//
// �ж����������Ƿ����
//
template<class A,class B>
struct MIs_Same{
	enum{ value = 0 };
};

template<class T>
struct MIs_Same<T,T>{
	enum{ value = 1 };
};

//
// �����⸲��
//
template<int N>
struct MIntType{
	enum{value = N};
};

//
// ���޸�����
//
template<class T>
struct MIdentity{
	typedef T type;
};

//
// ��������Ƿ�Ϊ����
//
#define MIsScalarImpl(classname,type,val) \
template<>\
struct classname<type>{\
	static const bool value = val;\
};\


template<class Type>
struct MIsScalar{
	static const bool value = false;
};

MIsScalarImpl(MIsScalar,__int8,true)
MIsScalarImpl(MIsScalar, __int16, true)
MIsScalarImpl(MIsScalar, __int32, true)
MIsScalarImpl(MIsScalar, __int64, true)
MIsScalarImpl(MIsScalar, unsigned __int8, true)
MIsScalarImpl(MIsScalar, unsigned __int16, true)
MIsScalarImpl(MIsScalar, unsigned __int32, true)
MIsScalarImpl(MIsScalar, unsigned __int64, true)
MIsScalarImpl(MIsScalar, double, true)
MIsScalarImpl(MIsScalar, float, true)


#define IsReferenceImpl(className,type,val) \
template<>\
struct className<type>{\
	static const bool value = val;\
};

//
// �ж�һ�������Ƿ�Ϊ����
//
template<class T>
struct MIsReference{
	static const bool value = false;
};

template<class T>
struct MIsReference<T&>{
	static const bool value = true;
};

template<class T>
struct MIsReference<const T&>{
	static const bool value = true;
};

template<class T>
struct MIsReference<volatile T&>{
	static const bool value = true;
};

IsReferenceImpl(MIsReference, void, false)
IsReferenceImpl(MIsReference, const void, false)
IsReferenceImpl(MIsReference, volatile void, false)


#define AddReferenceImpl(className,typeName,resultType) \
	template<>\
struct className<typeName>{\
	typedef resultType type;\
};

//
// Ϊһ�������������
//
template<class T>
struct MAddReference{
	typedef T& type;
};

template<class T>
struct MAddReference<T&>{
	typedef T& type;
};

template<class T>
struct MAddReference<const T&>{
	typedef const T& type;
};

template<class T>
struct MAddReference<volatile T&>{
	typedef volatile T& type;
};

AddReferenceImpl(MAddReference,void,void)
AddReferenceImpl(MAddReference, const void, const void)
AddReferenceImpl(MAddReference, volatile void, volatile void)


//
// ����ѡ����
//
template<class H,class T>
struct MPairType{
	typedef H HeaderType;
	typedef T NextType;
};

template<bool isTrue, class Type1,class Type2>
struct __Eval_If_Impl{
	typedef typename MPairType<Type1, Type2>::NextType type;
};

template<class Type1, class Type2>
struct __Eval_If_Impl<true, Type1, Type2>{
	typedef typename MPairType<Type1, Type2>::HeaderType type;
};

template<bool isTrue,class Type1,class Type2>
struct MEval_If : public __Eval_If_Impl<isTrue, Type1, Type2>{
};

//
// ����or
//
template<bool Conditon1,bool Condition2>
struct MOr{
	static const bool value = Conditon1 || Condition2;
};

//
// ���ݲ���ʱʹ������޸�ģ������
//
template<class T>
struct MParamWrape : MEval_If <
	MOr<MIsScalar<T>::value, MIsReference<T>::value>::value,
	typename MIdentity<T>::type, typename MAddReference < T >::type>
{};

//
// �Ǳ�����Ա�Լ������ó�Ա�ᱻת���� const ����
//
template<class T>
struct MConstParamWrape : MEval_If <
	MOr<MIsScalar<T>::value, MIsReference<T>::value>::value,
	typename MIdentity<T>::type, typename MAddReference < T const>::type>
{};

//
// �ܾ���char*�Ƚ�����һЩ,������ר�����char*���ػ��汾
//
template<>
struct MParamWrape<char*>{
	typedef char* type;
};

template<>
struct MParamWrape<char*&>{
	typedef char*& type;
};

template<>
struct MParamWrape<const char*>{
	typedef const char* type;
};
/*************************************/
template<>
struct MConstParamWrape<char*>{
	typedef const char* type;
};

template<>
struct MConstParamWrape<char*&>{
	typedef const char*& type;
};

template<>
struct MConstParamWrape<const char*>{
	typedef const char* type;
};

/**************************************/

//
// �ж����������Ƿ�Ϊ�̳�
//

template<class T,class U>
struct MConvertsion{
private:
	typedef typename MConstParamWrape<U>::type type;
	class __TempCalss{
		char temp[2];
	};
	typedef char Small;
	typedef __TempCalss Big;

	static Small test(type);
	static Big   test(...);
	static T gen();

public:
	enum{ same = MIs_Same<T,U>::value};
	enum{ convert = (sizeof(test(gen())) == sizeof(Small))};
	enum{ convert2 = MConvertsion<U, T>::convert };
};

#define MIsBDClass(U,T) \
	MConvertsion<const T*,const U*>::convert && !MConvertsion<const T*,const void*>::same


//
// ��nulltype ��β����������
//

namespace mjTL{

	template<class...Args>
	struct MTypeList;

	template<>
	struct MTypeList<>{
		typedef MEmptyType type;
		typedef MNullType next;
	};

	template<class T,class... Args>
	struct MTypeList<T,Args...> : public MTypeList<Args...>
	{
		typedef T type;
		typedef MTypeList<Args...> next;
	};



	/********���㳤��*********************/
	template<class T>
	struct length;

	template<>
	struct length<MTypeList<>>{
		enum{value = 0};
	};

	template<class T,class...Args>
	struct length<MTypeList<T, Args...>>{
	private:
		typedef MTypeList<T, Args...> type;
	public:
		enum{ value = 1 + length <type::next>::value};
	};

	/*************************��������**********************/
	template<class T, int index>
	struct index_type;

	template<class T,class...Args>
	struct index_type<MTypeList<T, Args...>, 0>{
		typedef T type;
	};

	template<class T, class...Args, int index>
	struct index_type<MTypeList<T, Args...>, index> : index_type<typename MTypeList<T, Args...>::next, index - 1>{};

	/*************��������,���ص�һ������*********************/
	template<class T,class U>
	struct find_type;

	template<class T,class U>
	struct find_type<MTypeList<T>, U>{
		enum{value = -1};
	};

	template<class T>
	struct find_type<MTypeList<T>, T>{
		enum{value = 0};
	};

	template<class U>
	struct find_type<MTypeList<>, U>{
		enum{value = -1};
	};


	template<class T,class...Args>
	struct find_type<MTypeList<T, Args...>, T>{
		enum{value = 0};
	};

	template<class T, class...Args, class L>
	struct find_type<MTypeList<T, Args...>, L>{
	private:
		typedef typename MTypeList<T, Args...>::next type;
	public:
		enum{ value = find_type<type, L>::value == -1?-1:1 + find_type<type, L>::value };
	};

	/**************************�����ڱ����ں����м�ĺ�������***************************/
	

	template<class T,template<class T1>class U>
	struct MTLClass : public U<T>{
		typedef T type;
		typedef MNullType next;
	};

	template<template<class T>class U>
	struct MTLClass<MNullType, U>;

	template<template<class T>class U>
	struct MTLClass<MEmptyType, U>{
		typedef MEmptyType type;
		typedef MNullType next;
	};

	template<template<class T>class U>
	struct MTLClass<MTypeList<>, U>{
		typedef MEmptyType type;
		typedef MNullType next;
	};

	template<class T,class... Args,template<class> class Holder>
	struct MTLClass<MTypeList<T, Args...>, Holder> :
		public MTLClass<T, Holder>, 
		public MTLClass<MTypeList<Args...>, Holder>
	{
		typedef MTLClass<T, Holder>  type;
		typedef MTLClass<MTypeList<Args...>, Holder> next;
	};

	template<class T, class...Args,template<class> class H>
	struct index_type<MTLClass<MTypeList<T, Args...>,H>, 0>{
		typedef MTLClass<MTypeList<T, Args...>, H> type;
	};

	template<class T, class...Args, template<class> class H, int index>
	struct index_type<MTLClass<MTypeList<T, Args...>,H>, index> : 
		index_type<typename MTLClass<MTypeList<T, Args...>,H>::next, index - 1>
	{};

	//
	// -------------------- ��ȡ�洢���������------------------------------------
	//
	template<class T,class... Args,template<class> class H>
	H<T>& reference_help(const MTLClass<MTypeList<T, Args...>, H>& obj, MIntType<0>){
		typename MTLClass<MTypeList<T, Args...>, H>::type& cur_obj = const_cast<MTLClass<MTypeList<T, Args...>, H>&>(obj);
		return cur_obj;
	}

	template<int N,class T,class... Args,template<class> class H>
	H<typename index_type<MTypeList<T, Args...>, N>::type>& reference_help(
		const MTLClass<MTypeList<T, Args...>, H>& obj, MIntType<N>)
	{
		typename MTLClass<MTypeList<T, Args...>, H>::next& next_obj = const_cast<MTLClass<MTypeList<T, Args...>, H>&>(obj);
		return reference_help(next_obj, MIntType<N - 1>());
	}

	//
	// ��ȡָ������Ĳ���
	//	
	template<int N,class T,class...Args,template<class> class H>
	H<typename index_type<typename MTypeList<T, Args...>, N>::type>& reference_at(const MTLClass<MTypeList<T, Args...>, H>& obj)
	{
		MIntType<N> index;
		return reference_help(obj, index);
	}
	
	//
	// ����const����
	//
	template<int N, class T, class...Args, template<class> class H>
	const H<typename index_type<typename MTypeList<T, Args...>, N>::type>& const_reference_at(const MTLClass<MTypeList<T, Args...>, H>& obj)
	{
		MIntType<N> index;
		return reference_help(obj, index);
	}
}
