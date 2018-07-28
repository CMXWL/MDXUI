#pragma once

//
// ִ�к����İ�װ��
//

#include <MString.h>
#include <MAny.h>
#include <MMap.h>
#include <MFunctionTraits.h>
#include "MSingleton.h"

//
// boost ��Ҫ�������Ͳ�ȫ
//
#include <type_traits>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_reference.hpp>



class MDispatch :public MSingleton<MDispatch>
{
public:
    //
    // ģ��������������Ƶ�
    //
    template<class T>
    struct paramtype : boost::mpl::eval_if <
            boost::mpl::or_ < std::is_scalar<T>,
            std::is_reference < T >> ,
            boost::mpl::identity<T>, boost::add_reference <T >>
    {};

    template<class T>
    struct constparamtype : boost::mpl::eval_if <
            boost::mpl::or_ < std::is_scalar<T>,
            std::is_reference < T >> ,
            boost::mpl::identity<T>, boost::add_reference <T const >>
    {};

public:
    MDispatch(){}
    ~MDispatch(){}

public:
    //
    // ע�ắ��,funName ��ʶ�����ĺ�������fun ��������ʹ��MSLOT�����ɸú�������
    // �����������˷��ز����⣬����Ĳ�����ʹ��const reference���ݣ��������⣩
    //
    void RegisterFunction(const mj::MString& funName,const mj::MAny& fun){
        if(mFunMap.count(funName)){
            mFunMap.at(funName).push_back(fun);
        }
        else{
            mFunMap[funName] = std::list<mj::MAny>({fun});
        }

    }

    //
    // ִ�д��������ݵĺ���
    //
    template<class R,class ...Args>
    bool RunReturnValue(const mj::MString& funName,R& outValue,Args ... args){
        if(mFunMap.count(funName)){
            typedef std::function<R(typename constparamtype<Args>::type...)> FunType;
            auto funs = mFunMap.at(funName);;
            for(auto& f : funs){
                try{
                    auto fun = mj::any_cast<FunType>(f);
                    outValue = fun(args...);
                    return true;
                }
                catch(...){
                    ;
                }
            }
            return false;
        }
        return false;
    }

    //
    // ִ�в����������ݵĺ���,���в������Ͷ���const reference
    //
    template<class ...Args>
    bool Run(const mj::MString& funName,Args ... args){
        if(mFunMap.count(funName)){
            typedef std::function<void(typename constparamtype<Args>::type...)> FunType;
            auto funs = mFunMap.at(funName);;
            for(auto& f : funs){
                try{
                    auto fun = mj::any_cast<FunType>(f);
                    fun(args...);
                    return true;
                }
                catch(...){
                    ;
                }
            }
            return false;
        }
        return false;
    }


    //
    // ִ�в����������ݵĺ��������в������Ͷ������ã���const ,תΪĳЩ���⺯�����趨
    //
    template<class...Args>
    bool RunNoConst(const mj::MString& funName,Args& ... args){
        if(mFunMap.count(funName)){
            typedef std::function<void(typename paramtype<Args>::type...)> FunType;
            auto funs = mFunMap.at(funName);;
            for(auto& f : funs){
                try{
                    auto fun = mj::any_cast<FunType>(f);
                    fun(args...);
                    return true;
                }
                catch(...){
                    ;
                }
            }
            return false;
        }
        return false;
    }

    //
    // ��ѯ�����Ƿ����
    //
    template<class F>
    bool QueryFun(const mj::MString& funName,F& fun){
        if(mFunMap.count(funName)){          
            auto funs = mFunMap.at(funName);;
            for(auto& f : funs){
                try{
                    fun = mj::any_cast<F>(f);
                    return true;
                }
                catch(...){
                    ;
                }
            }
            return false;
        }
        return false;
    }

    bool HasFunByName(const mj::MString&  funName){
        if(mFunMap.count(funName)){
            return true;
        }
        else{
            return false;
        }
    }

    //
    // ����
    //
    void Reset(){
        mFunMap.clear();
    }

private:
   MMap<mj::MString,std::list<mj::MAny>>  mFunMap; // �ַ�����������ӳ��
};

