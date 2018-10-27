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


#ifndef MSINGLETON_H
#define MSINGLETON_H

//
// ����ͨ���Ǹ�������ȡ��ʵ������ͬһ��ʵ������
// ��ʹ�����֮����Ҫʹ�� Destroy �����ٶ���
// ����ֱ��ʹ��MSingleton����������,�������Կ���ʹ������Ϊ��������������д�������������
// eg:
// 1:class A;
// A* ptr = MSingleton<A>::Instance();
// 2 : class A : public MSingleton<A>{};
// A* ptr = A::Instance();
//
template<class T>
class MSingleton
{
public:
    MSingleton(){}
    ~MSingleton(){}

    MSingleton(const MSingleton&)=delete;
    MSingleton& operator=(const MSingleton&)=delete;

    //
    // ������ָͨ������
    //
    static T* Instance(){
        try{
            if(__sPtr == nullptr){
                __sPtr = new T;
            }
            return __sPtr;
        }
        catch(...){
            return nullptr;
        }
    }

	//
	// ����������
	//
	template<class...Args>
	static T* InstanceWithArgs(Args...args){
		try{
			if (__sPtr == nullptr){
				__sPtr = new T(args...);
			}
			return __sPtr;
		}
		catch (...){
			return nullptr;
		}
	}

    //
    // ʹ�ù����������д�������
    //
    template<class F>
    static T* Instance(F fun){
        try{
            if(__sPtr == nullptr){
                __sPtr = fun();
                if(__sPtr){
                    __sIsFactory = true;
                }
            }
            return __sPtr;
        }
        catch(...){
            return nullptr;
        }
    }

    static void Destroy(){
        if(__sPtr && !__sIsFactory){
            delete __sPtr;
            __sPtr = nullptr;
        }
    }

    //
    // ʹ�ø������������ͷŶ���
    //
    template<class F>
    static void Destroy(F fun){
        if(__sPtr && __sIsFactory){
            fun(__sPtr);
            __sPtr = nullptr;
        }
    }

    //
    // ��������
    //
    static T& InstanceRef(){
        if(__sPtr == nullptr){
            __sPtr = new T;
        }
        return *__sPtr;
    }

	//
	// ���ʵ���Ƿ��Ѵ���
	//
	static bool IsCreated(){
		if (__sPtr == nullptr){
			return false;
		}
		else{
			return true;
		}
	}

protected:
    static T* __sPtr;
    static bool __sIsFactory;
};

template<class T>
T* MSingleton<T>::__sPtr = nullptr;

template<class T>
bool MSingleton<T>::__sIsFactory = false;

#endif // MSINGLETON_H
