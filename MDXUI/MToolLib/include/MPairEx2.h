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


#pragma once
#include <iostream>
#include <MMap.h>
//
// ����ֻ�Ƕ�pair������һ����չ,��Ϊ��ʱ���ʹ�õ����������������
//

//
// ��������������
//
template<class T,class V,class K>
class MPairEx
{
public:
    MPairEx():first(T()),second(V()),third(K()){}
    ~MPairEx(){}
    MPairEx(T one,V two,K three):first(one),second(two),third(three)
    {}

    MPairEx(const MPairEx& other):
        first(other.first),
        second(other.second),
        third(other.third)
    {}

    MPairEx& operator=(const MPairEx& other){
        if(&other == this)
            return *this;
        first = other.first;
        second = other.second;
        third = other.third;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os,const MPairEx& p){
        os<<"("<<p.first<<","<<p.second<<","<<p.third<<")";
        return os;
    }

    T first;
    V second;
    K third;
};

//
// �ĸ��������
//
template<class T,class V,class M,class N>
class MFourType : public MPairEx<T,V,M>
{
public:
    MFourType():MPairEx(),fourth(N()){}
    ~MFourType(){}
    MFourType(T one,V two,M three,N four):MPairEx(one,two,three),fourth(four)
    {}

    MFourType(const MFourType& other):MPairEx(other),fourth(four)
    {}

    MFourType& operator=(const MFourType& other){
        if(this == &other)
            return *this;
        MPairEx::operator =(other);
        fourth = other.fourth;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os,const MFourType& p){
        os<<"("<<p.first<<","<<p.second<<","<<p.third<<","<<p.fourth<<")";
        return os;
    }
    N fourth;
};

//
// �Ƚϲ���
//
template<class K,class V>
inline bool operator<(const __MPair<K,V>& left,const __MPair<K,V>& right){
    if(std::less<K>()(left.first,right.first)){
        return true;
    }
    else if(std::less<K>()(right.first,left.first)){
        return false;
    }
    else{
        return std::less<V>()(left.second,right.second);
    }
}

template<class K,class V>
inline bool operator==(const __MPair<K,V>& left,const __MPair<K,V>& right){
    return std::equal_to<K>()(left.first,right.first) &&
            std::equal_to<V>()(left.second,right.second);
}

template<class K,class V>
inline bool operator>(const __MPair<K,V>& left,const __MPair<K,V>& right){
    if(std::greater<K>()(left.first,right.first)){
        return true;
    }
    else if(std::greater<K>()(right.first,left.first)){
        return false;
    }
    else{
        return std::greater<V>()(left.second,right.second);
    }
}

template<class K,class V1,class V2>
inline bool operator<(const MPairEx<K,V1,V2>& left,const MPairEx<K,V1,V2>& right){
    if(std::less<K>()(left.first,right.first)){
        return true;
    }
    else if(std::less<K>()(right.first,left.first)){
        return false;
    }
    else if(std::less<V1>()(left.second,right.second)){
        return true;
    }
    else if(std::less<V1>()(right.second,left.second)){
        return false;
    }
    else if(std::less<V2>()(left.third,right.third)){
        return true;
    }
    else if(std::less<V2>()(right.third,left.third)){
        return false;
    }
    return false;
}

template<class K,class V1,class V2>
inline bool operator==(const MPairEx<K,V1,V2>& left,const MPairEx<K,V1,V2>& right){
    return std::equal_to<K>()(left.first,right.first)&&
            std::equal_to<V1>()(left.second,right.second)&&
            std::equal_to<V2>()(left.third,right.third);
}

template<class K,class V1,class V2>
inline bool operator>(const MPairEx<K,V1,V2>& left,const MPairEx<K,V1,V2>& right){
    if(std::greater<K>()(left.first,right.first)){
        return true;
    }
    else if(std::greater<K>()(right.first,left.first)){
        return false;
    }
    else if(std::greater<V1>()(left.second,right.second)){
        return true;
    }
    else if(std::greater<V1>()(right.second,left.second)){
        return false;
    }
    else if(std::greater<V2>()(left.third,right.third)){
        return true;
    }
    else if(std::greater<V2>()(right.third,left.third)){
        return false;
    }
    return false;
}

template<class K,class V1,class V2,class V3>
inline bool operator<(const MFourType<K,V1,V2,V3>& left,const MFourType<K,V1,V2,V3>& right){
    if(std::less<K>()(left.first,right.first)){
        return true;
    }
    else if(std::less<K>()(right.first,left.first)){
        return false;
    }
    else if(std::less<V1>()(left.second,right.second)){
        return true;
    }
    else if(std::less<V1>()(right.second,left.second)){
        return false;
    }
    else if(std::less<V2>()(left.third,right.third)){
        return true;
    }
    else if(std::less<V2>()(right.third,left.third)){
        return false;
    }
    else if(std::less<V3>()(left.fourth,right.fourth)){
        return true;
    }
    else if(std::less<V3>()(right.fourth,left.fourth)){
        return false;
    }
    return false;
}

template<class K,class V1,class V2,class V3>
inline bool operator==(const MFourType<K,V1,V2,V3>& left,const MFourType<K,V1,V2,V3>& right){
    return std::equal_to<K>()(left.first,right.first)&&
            std::equal_to<V1>()(left.second,right.second)&&
            std::equal_to<V2>()(left.third,right.third)&&
            std::equal_to<V3>()(left.fourth,right.fourth);
}


template<class K,class V1,class V2,class V3>
inline bool operator>(const MFourType<K,V1,V2,V3>& left,const MFourType<K,V1,V2,V3>& right){
    if(std::greater<K>()(left.first,right.first)){
        return true;
    }
    else if(std::greater<K>()(right.first,left.first)){
        return false;
    }
    else if(std::greater<V1>()(left.second,right.second)){
        return true;
    }
    else if(std::greater<V1>()(right.second,left.second)){
        return false;
    }
    else if(std::greater<V2>()(left.third,right.third)){
        return true;
    }
    else if(std::greater<V2>()(right.third,left.third)){
        return false;
    }
    else if(std::greater<V3>()(left.fourth,right.fourth)){
        return true;
    }
    else if(std::greater<V3>()(right.fourth,left.fourth)){
        return false;
    }
    return false;
}

//
// ��������
//
namespace mj{
template<class K,class V>
inline __MPair<K,V> makepair(const K& key,const V& value){
    return __MPair<K,V>(key,value);
}

template<class K,class V>
inline __MPair<K,V> operator+(const __MPair<K,V>& left,const __MPair<K,V>& right){
    return __MPair<K,V>(left.first + right.first,left.second + right.second);
}

template<class K,class V>
inline __MPair<K,V> operator-(const __MPair<K,V>& left,const __MPair<K,V>& right){
    return __MPair<K,V>(left.first - right.first,left.second - right.second);
}

template<class K,class V1,class V2>
inline MPairEx<K,V1,V2> makepair(const K& key,const V1& val1,const V2& val2){
    return MPairEx<K,V1,V2>(key,val1,val2);
}

template<class K,class V1,class V2>
inline MPairEx<K,V1,V2> operator+(const MPairEx<K,V1,V2>& left,const MPairEx<K,V1,V2>& right){
    return MPairEx<K,V1,V2>(left.first + right.first,left.second + right.second,left.third + right.third);
}

template<class K,class V1,class V2>
inline MPairEx<K,V1,V2> operator-(const MPairEx<K,V1,V2>& left,const MPairEx<K,V1,V2>& right){
    return MPairEx<K,V1,V2>(left.first - right.first,left.second - right.second,left.third - right.third);
}

template<class T,class V,class M,class N>
inline MFourType<T,V,M,N> makepair(const T& key,const V& val1,const M& val2,const N& val3){
    return MFourType<T,V,M,N>(key,val1,val2,val3);
}

template<class T,class V,class M,class N>
inline MFourType<T,V,M,N> operator+(const MFourType<T,V,M,N>& left,const MFourType<T,V,M,N>& right){
    return MFourType<T,V,M,N>(left.first + right.first,
                              left.second + right.second,
                              left.third + right.third,
                              left.fourth + right.fourth);
}


template<class T,class V,class M,class N>
inline MFourType<T,V,M,N> operator-(const MFourType<T,V,M,N>& left,const MFourType<T,V,M,N>& right){
    return MFourType<T,V,M,N>(left.first - right.first,
                              left.second - right.second,
                              left.third - right.third,
                              left.fourth - right.fourth);
}

}
