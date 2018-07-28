#pragma once

#include "MTypeWrap.h"
#include "MMemDB.h"

namespace TL{
	template<class T>
	using List = MTypeWrap<std::vector<T>>;

	template<class T>
	using Vector = MTypeWrap<std::vector<T>>;

	template<class K, class V>
	using Map = MTypeWrap<std::map<K, V>>;

	//
	// ���ڳ�ʼ�� Map
	//
	template<class K, class V>
	Map<K, V> map_list(const K& k, const V& v){
		return Map<K, V>()(k, v);
	}

	//
	// ֻ��Ӧ�ڵ��߳�
	//
	template<class T, class...Args>
	using MSNoSqlDB = MNoSqlDB<MSingleThreadMode, T, Args...>;

	//
	// �����ڶ��̲߳���
	//
	template<class T, class...Args>
	using MMNoSqlDB = MNoSqlDB<MMultThreadMode, T, Args...>;

	//
	// һ������MString�ľ���
	//
	typedef mj::MMatrixSheet<MString> smat;
}
