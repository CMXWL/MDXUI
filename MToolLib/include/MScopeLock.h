#pragma once
#include <functional>
#include <MFunctionTraits.h>

///
/// ��Ҫ������ָ��Lock��UnLock�Ķ���
///
template<class T>
class MScopeLock{
public:
    MScopeLock(T& obj):lockObj(obj){
        obj.Lock();
    }

    MScopeLock(T* obj):lockObj(*obj){
        obj->Lock();
    }

    ~MScopeLock(){
        lockObj.UnLock();
    }

private:
    T& lockObj;
};

///
/// \brief The MScopeBool class
/// ͨ������ĳЩʱ����Ҫ�ڷ���ʱ�޸Ŀ��Ʊ���ֵ��ʱ�������
///
class MScopeBool{
public:
    MScopeBool(bool& val):bVal(val){}
    ~MScopeBool(){bVal = !bVal;}
private:
    bool& bVal;
};

///
/// ֵ�����⸲��
/// ��Ҫ�����ڲ���Ҫ��ʱ��ָ�ֵ
/// ����б�Ҫ���ڴ濪��
///
template<class T>
class MScopeValue{
public:
    MScopeValue(T& val,const T& covervalue):mVal(val),mCoverVal(covervalue){

    }
    ~MScopeValue(){mVal = mCoverVal;}
private:
    T& mVal;
    T  mCoverVal;
};

///
/// ���������⸲��
/// ��װһ������,�ڶ�������ʱִ�иú���
///
template<class R,class...Args>
class MExitFunction{
public:

    typedef std::tuple<Args...> ArgsType;
    typedef std::function<R(Args...)> FunType;

    MExitFunction(FunType fun,const Args&... args):mFun(fun),mArgs(std::make_tuple(args...)){
    }
    ~MExitFunction(){
        if(mFun){
            mj::ManualFun(mFun,mArgs);
        }
    }

    void Run(){
        if(mFun){
            mj::ManualFun(mFun,mArgs);
            mFun = nullptr;
        }
    }
private:
    FunType mFun{nullptr};
    ArgsType mArgs;
};

template<class R>
class MExitFunction<R>{
public:
    typedef std::function<R()> FunType;

    MExitFunction(FunType fun):mFun(fun){
    }
    ~MExitFunction(){
        if(mFun){
            mFun();
        }
    }

    void Run(){
        if(mFun){
            mFun();
            mFun = nullptr;
        }
    }

private:
    FunType mFun{nullptr};
};
