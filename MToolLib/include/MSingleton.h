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
