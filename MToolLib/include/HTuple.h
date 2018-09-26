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


//***************************************************
// HTuple.h ��Ҫ����Э����׼���tuple�Ĳ���
//***************************************************

#pragma once
#include <iterator>
#include <iostream>
#include <utility>
#include <tuple>
#include "MString.h"
namespace mj{
	//==================================================
	//����pair�Ĳ���
	//==================================================
	template<typename T, typename U>
        inline std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p){
		os << p.first << "," << p.second << std::endl;
		return os;
	}

	template<typename T,typename U>
	inline std::istream& operator>>(std::istream& is, std::pair<T, U>& p){
		T t;
		U u;
		is >> t >> u;
		p = std::make_pair(t, u);
		return is;
	}

	//------------------------------------------------
	// ��tuple�Ĳ���
	//------------------------------------------------
	template<int N, class Tuple>
	class tuple_helper{
	public:
                tuple_helper(Tuple t, std::ostream& os,const char* spliter = "\t"){
                        tuple_helper<N - 1, Tuple> tp(t, os,spliter);
                        os << std::get<N - 1>(t) << spliter;
		}
	};

	template<class Tuple>
	class tuple_helper<0, Tuple>{
	public:
                tuple_helper(Tuple t, std::ostream& os,const char* spliter = "\t"){}
	};

	//==============================================
	// ����Ԫ��Ĳ���
	//==============================================
	template<class T>
        inline void tuple_print(T t, std::ostream& os,const char* spliter = "\t"){
                tuple_helper<std::tuple_size<T>::value, T> tp(t, os,spliter);
	}

	//==============================================
	// ��Ԫ��Ҳ�ܹ�ͨ�������
	//==============================================
	template<class...Args>
	inline std::ostream& operator<<(std::ostream& os, std::tuple<Args...> t){
		tuple_print(t, os);
		return os;
	}

	//=======================================================
	// ���ַ���ת����ת���ɴ����͵�tuple
	//=======================================================
	template<size_t index,size_t M,class T>
	struct TypeConvert;

	template<size_t index, size_t M, class ... Args>
	struct TypeConvert<index, M, std::tuple<Args...>>{
		typedef typename std::tuple_element<index, std::tuple<Args...>>::type Type;
		template<class T>
		struct Apply{
			Apply(T t) :mT(t){
			}
			inline void apply(std::vector<MString>& v)
			{
				MString str = v.front();
                                str.trim();
				v.erase(v.begin());
				auto tt = std::tuple_cat(mT, std::make_tuple(str.ToOtherType<Type>()));
				TypeConvert<index + 1, M, std::tuple<Args...>>::Apply<decltype(tt)>(tt).apply(v);
			}
			T mT;
		};
		
	};

	template<size_t M,class ... Args>
	struct TypeConvert<M,M,std::tuple<Args...>>{
		typedef  typename std::tuple_element<M-1, std::tuple<Args...>>::type Type;
		template<class T>
		struct Apply{
			Apply(T t) :mT(t){}
			inline void apply(std::vector<MString>& v)
			{
				throw mT;
			}
			T mT;
		};
		
	};
	
	template<class...Args>
        std::tuple<Args...>& Totuple(const std::string& str, std::tuple<Args...>& output,const std::string& spliter = " \t,:"){
		MString Mstr = str;
		std::vector<MString> v;
                Mstr.split(spliter, v);
		if (v.size() < sizeof...(Args)){
			return output;
		}
		try{
			TypeConvert<0, sizeof...(Args), std::tuple<Args...>>::Apply<std::tuple<>>(std::tuple<>()).apply(v);
		}
		catch (std::tuple<Args...> e){
			output = std::forward<std::tuple<Args...>&&>(e);
			return output;
		}
		catch (...){
			return output;
		}
	}

	template<class...Args>
	inline std::istream& operator>>(std::istream& is, std::tuple<Args...>& t){
		std::string str;
		std::getline(is, str);
		if (str.empty())
			return is;
		t = Totuple(str, t);
		return is;
	}

        //
        // ��tutpleת��Ϊָ����ʽ�ַ���
        //
        template<class T>
        inline std::string TupleToStr(const T& t,const std::string& spliter = "\t"){
            std::ostringstream os;
            tuple_helper<std::tuple_size<T>::value, T> tp(t, os,spliter.c_str());
            return os.str();
        }
}
