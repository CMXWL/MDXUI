#pragma once
#include <MToolLib>
#include <MSerialize.h>

namespace TL{

template<class Key,class Value>
void PutValues(MSerialize& Serial,const char* keys,const TL::Vector<std::pair<Key,Value>>& vals,const char* spliter = "*")
{
    if(vals.empty())
        return;
    std::vector<MString> ver2;
    for(auto& c : vals){
        MString str = c.toT().first;
        str<<spliter<<c.toT().second;
        ver2.push_back(str);
    }
    Serial.PutValues(keys,ver2);
}

template<class Key,class Value>
void GetValues(MSerialize& Serial,const char* keys,TL::Vector<std::pair<Key,Value>>& vals,const char* spliter = "*"){
    std::vector<MString> ver2 = Serial.GetValues(keys,MString());
    if(ver2.empty()){
        return;
    }
    vals.clear();
    for(MString c : ver2){
        std::vector<MString> tempv;
        c.split(spliter,tempv);
        if(tempv.size() != 2)
            continue;
        Key key = tempv[0].ToOtherType<Key>();
        Value val = tempv[1].ToOtherType<Value>();
        vals.push_back(std::make_pair(key,val));
    }
}

template<class Key,class Value>
void PutValues(MSerialize &Serial, const char *keys, const TL::Map<Key, Value> &vals, const char *spliter="*")
{
    if(vals.empty())
        return;
    std::vector<MString> ver2;
    for(auto& c : vals){
        MString str = c->first;
        str<<spliter<<c->second;
        ver2.push_back(str);
    }
    Serial.PutValues(keys,ver2);
}

template<class Key,class Value>
void GetValues(MSerialize& Serial,const char* keys,TL::Map<Key,Value>& vals,const char* spliter = "*")
{
    std::vector<MString> ver2 = Serial.GetValues(keys,MString());
    if(ver2.empty()){
        return;
    }
    vals.clear();
    for(MString c : ver2){
        std::vector<MString> tempv;
        c.split(spliter,tempv);
        if(tempv.size() != 2)
            continue;
        Key key = tempv[0].ToOtherType<Key>();
        Value val = tempv[1].ToOtherType<Value>();
        vals[key] = val;
    }
}


template<class T,class...Args>
void PutValues(MSerialize &Serial, const char *keys, const TL::MSNoSqlDB<T,Args...> &vals, const char *spliter="*"){
    if(vals.empty())
        return;

    TL::smat mstrmat = vals.toMatrix();
    std::vector<MString> vin;
    for(int i=0;i<mstrmat.rows();++i){
        std::vector<MString> tempv = mstrmat.row(i);
        MString str = JoinToMstring(tempv,spliter);
        vin.push_back(str);
    }
    Serial.PutValues(keys,vin);
}

template<class T,class...Args>
void GetValues(MSerialize &Serial, const char *keys, TL::MSNoSqlDB<T,Args...> &vals, const char *spliter="*"){
    std::vector<MString> ver2 = Serial.GetValues(keys,MString());
    if(ver2.empty()){
        return;
    }
    vals.clear();
    for(MString c : ver2){
        TL::MSNoSqlDB<T,Args...>::value_type __val;
        TL::FromStr(c,__val,spliter);
        vals.push_back(__val);
    }
}

template<class T>
void PutValues(MSerialize &Serial, const char *keys, const mj::MMatrixSheet<T> &vals, const char *spliter="*")
{
    if(vals.empty())
        return;
    std::vector<MString> vin;
    for(int i=0;i<vals.rows();++i){
        std::vector<T> tempv = vals.row(i);
        MString str = JoinToMstring(tempv,spliter);
        vin.push_back(str);
    }
    Serial.PutValues(keys,vin);
}

template<class T>
void GetValues(MSerialize &Serial, const char *keys, mj::MMatrixSheet<T> &vals, const char *spliter="*")
{
    std::vector<MString> ver2 = Serial.GetValues(keys,MString());
    if(ver2.empty()){
        return;
    }
    vals.clear();
    int index = 0;
    for(MString c : ver2){
        if(c.empty())
            continue;
        std::vector<T> tempv;
        c.split(spliter,tempv);
        if(tempv.empty())
            continue;
        if(vals.empty()){
            vals.resize(ver2.size(),tempv.size());
        }
        vals.row(index) = tempv;
        ++index;
    }
}

}
