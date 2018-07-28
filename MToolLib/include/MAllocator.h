#pragma once
#include "MEmptyType.h"
//
// Allocator ӵ�� Instance ������ȡ����
// Allocator �����ڴ�
// Deallocator �ͷ��ڴ�
//

template<class Allocator = MEmptyType>
class MAllocator{
public:
	static void* operator new(std::size_t size);
	static void operator delete(void* p, std::size_t size);
};


//
// ������ת��
//
template<class Allocator>
struct __Allocator_Dispatch__{
	static void* malloc(std::size_t size){
		return Allocator::Instance()->Allocator(size);
	}

	static void  free(void* p, std::size_t size){
		Allocator::Instance()->Deallocator(p, size);
	}
};

template<>
struct __Allocator_Dispatch__<MEmptyType>{
	static void* malloc(std::size_t size){
		return ::operator new(size);
	}

	static void  free(void* p, std::size_t size){
		::operator delete(p);
	}
};

//
// ������ʵ��
//
template<class Allocator>
void* MAllocator<Allocator>::operator new(std::size_t size){
	return __Allocator_Dispatch__<Allocator>::malloc(size);
}

template<class Allocator>
void MAllocator<Allocator>::operator delete(void* p, std::size_t size){
	__Allocator_Dispatch__<Allocator>::free(p, size);
}
