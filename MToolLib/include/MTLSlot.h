#pragma once
#include <HTuple.h>
#include <functional>

namespace TL{
	//
	// ����ֻ��һЩ��������,����Ҫ����,ֻ��Ҫ֪����ôʹ��MSLOT����
	//
	template<size_t N>
	struct MPropertyFunHelp{
		template<class T, class F, class K, class...Args>
		static inline auto Apply(T t, F fun, K obj, Args...args)->
			decltype(
			MPropertyFunHelp<N - 1>::Apply
			(
			t, fun, obj,
			std::get<N - 1>(t),
			args...)
			)
		{
			return MPropertyFunHelp<N - 1>::Apply
				(
				t, fun, obj,
				std::get<N - 1>(t),
				args...
				);
		}
	};

	template<>
	struct MPropertyFunHelp<0>{
		template<class T, class F, class K, class...Args>
		static inline auto Apply(T t, F fun, K obj, Args...args)->decltype(
			std::bind(fun, obj, args...)
			)
		{
			return std::bind(fun, obj, args...);
		}
	};

	template<int N, int M, class R>
	struct ToFun{
		template<class T, class F, class K, class...Args>
		static std::function<R(Args...)> Apply(T t, F fun, K obj){
			auto __t = std::tuple_cat(t, std::make_tuple(std::_Ph<N + 1>()));
			return ToFun<N + 1, M, R>::Apply<decltype(__t), F, K, Args...>
				(__t, fun, obj);
		}
	};

	template<int N, class R>
	struct ToFun<N, N, R>{
		template<class T, class F, class K, class...Args>
		static std::function<R(Args...)> Apply(T t, F fun, K obj){
			return MPropertyFunHelp<sizeof...(Args)>::Apply(t, fun, obj);
		}
	};

	//
	// ��װ��Ա����
	//
	template<class T, class R, class...Args>
	std::function<R(Args...)> MSLOT(R(T::*fun)(Args...), T* obj){
		auto t = std::make_tuple();
		return ToFun<0, sizeof...(Args), R>::Apply<decltype(t), decltype(fun), T*, Args...>
			(
			t, fun, obj
			);
	}

	//
	// ��װ���ɺ���
	//
	template<class R, class...Args>
	std::function<R(Args...)> MSLOT(R(*fun)(Args...)){
		return std::forward<std::function<R(Args...)>>(fun);
	}


	//
	// ��װ������������ɺ���
	//
	template<class R, class T, class...Args>
	std::function<R(Args...)> MSLOT(R(*fun)(T* obj, Args...), T* obj){
		auto t = std::make_tuple();
		return ToFun<0, sizeof...(Args), R>::Apply<decltype(t), decltype(fun), T*, Args...>
			(
			t, fun, obj
			);
	}

}