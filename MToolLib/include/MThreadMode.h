#pragma once

#include <mutex>

//
// ���߳�ģʽ
//
struct MSingleThreadMode{
	inline void Lock(){}
	inline void UnLock(){}
};

//
// ���߳�ģʽ
//
struct MMultThreadMode{
	inline void Lock(){
		mMutex.lock();
	}

	inline void UnLock(){
		mMutex.unlock();
	}
	std::mutex mMutex;
};