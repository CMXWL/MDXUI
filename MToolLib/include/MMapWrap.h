#pragma once
#include <map>
#include <vector>
#include <iostream>

template<class K, class V, class AllocatorType>
class MTypeWrap<std::map<K, V>, AllocatorType> : public AllocatorType{
public:
	typedef K Key;
	typedef V Value;
	typedef typename MConstParamWrape<K>::type const_k_type;
	typedef typename MConstParamWrape<V>::type const_v_type;

	typedef typename MParamWrape<K>::type k_type;
	typedef typename MParamWrape<V>::type v_type;

	typedef std::map<K, V> Type;
	typedef std::pair<K, V> ValueType;

private:
	//
	// ����item
	//
	class Proxiy{
	public:
		Proxiy(MTypeWrap<Type, AllocatorType>* data, std::size_t index);
		Proxiy(const Proxiy& other);
		operator ValueType()const;
		operator ValueType();
		ValueType toT() const;
		ValueType& ref();
		const ValueType& ref() const;
		const std::pair<const K, V>* operator->();
		const std::pair<const K, V>* operator->() const;
		friend std::ostream& operator<<(std::ostream& os, const Proxiy& proxiy){
			ValueType v = proxiy.toT();
			os << v.first << "," << v.second;;
			return os;
		}

	private:
		Proxiy(const ValueType&) = delete;
		Proxiy& operator=(const Proxiy& val);
		Proxiy& operator=(const ValueType& val);
	private:
		MTypeWrap<Type, AllocatorType>*  mData;
		std::size_t mIndex;
	};

	//
	// ����ֵ
	//
	class ValueProxiy{
	public:
		ValueProxiy(MTypeWrap<Type, AllocatorType>* data, const_k_type key);
		ValueProxiy(const ValueProxiy& other);
		ValueProxiy& operator=(const ValueProxiy& val);
		ValueProxiy& operator=(const_v_type val);
		operator Value()const;
		operator Value();
		const Value* operator&();
		const Value* operator&() const;
		Value toT() const;
		friend std::ostream& operator<<(std::ostream& os, const ValueProxiy& proxiy){
			os << proxiy.toT();
			return os;
		}

		friend std::wostream& operator<<(std::wostream& os, const ValueProxiy& proxiy){
			os << proxiy.toT();
			return os;
		}
	private:
		MTypeWrap<Type, AllocatorType>*  mData;
		const_k_type mKey;
	};

	typedef Proxiy* pointer;
	typedef Proxiy reference;
	typedef Proxiy const_reference;

	class const_iterator{
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef Proxiy value_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::ptrdiff_t distance_type;

		const_iterator(MTypeWrap<Type, AllocatorType>& ptr, size_t num, size_t cnum = 0) :
			mData(ptr),
			mNum(num),
			mCurrentNum(cnum)
		{}

		const_iterator(const const_iterator& other) :
			mData(other.mData),
			mNum(other.mNum),
			mCurrentNum(other.mCurrentNum)
		{}

		const_iterator& operator=(const const_iterator& other){
			mData = other.mData;
			mNum = other.mNum;
			mCurrentNum = other.mCurrentNum;
			return *this;
		}

		const value_type* operator->(){
			if (mCurrentNum < 0 || mCurrentNum >= mNum){
				throw std::out_of_range("index out of range ..... ");
			}
			return &mData.proxy(mCurrentNum);
		}

		const value_type* operator->() const{
			if (mCurrentNum < 0 || mCurrentNum >= mNum){
				throw std::out_of_range("index out of range ..... ");
			}
			return &mData.proxy(mCurrentNum);
		}

		const_reference operator*(){
			if (mCurrentNum < 0 || mCurrentNum >= mNum){
				throw std::out_of_range("index out of range ..... ");
			}
			return mData.proxy(mCurrentNum);
		}

		const_reference operator*() const{
			if (mCurrentNum < 0 || mCurrentNum >= mNum){
				throw std::out_of_range("index out of range ..... ");
			}
			return mData.proxy(mCurrentNum);
		}

		const_iterator operator++(int){
			const_iterator temp(*this);
			++mCurrentNum;
			return temp;
		}

		const_iterator& operator++(){
			++mCurrentNum;
			return *this;
		}

		const_iterator operator--(int){
			const_iterator temp(*this);
			--mCurrentNum;
			return temp;
		}

		const_iterator& operator--(){
			--mCurrentNum;
			return *this;
		}

		const_iterator& operator+(size_t index){
			mCurrentNum += index;
			return *this;
		}

		const_iterator& operator-(size_t index){
			mCurrentNum -= index;
			return *this;
		}

		const_iterator& operator+=(size_t index){
			mCurrentNum += index;
			return *this;
		}

		const_iterator& operator-=(size_t index){
			mCurrentNum -= index;
			return *this;
		}

		friend size_t operator-(const_iterator first, const_iterator second){
			return first.mCurrentNum - second.mCurrentNum;
		}

		friend bool operator<(const_iterator first, const_iterator second){
			if (first.mData.empty() && second.mData.empty()){
				return false;
			}
			if (first.mNum != second.mNum || &(first.mData) != &(second.mData)){
				throw std::runtime_error("Error ..... ");
			}
			return first.mCurrentNum < second.mCurrentNum;
		}

		friend bool operator>(const_iterator first, const_iterator second){
			if (first.mData.empty() && second.mData.empty()){
				return false;
			}
			if (first.mNum != second.mNum || &(first.mData) != &(second.mData)){
				throw std::runtime_error("Error ..... ");
			}
			return first.mCurrentNum > second.mCurrentNum;
		}

		friend bool operator==(const_iterator first, const_iterator second){
			if (first.mData.empty() && second.mData.empty()){
				return true;
			}
			if (first.mNum != second.mNum || &(first.mData) != &(second.mData)){
				throw std::runtime_error("Error ..... ");
			}
			return  first.mCurrentNum == second.mCurrentNum;
		}

		friend bool operator!=(const_iterator first, const_iterator second){
			if (first.mData.empty() && second.mData.empty()){
				return false;
			}
			if (first.mNum != second.mNum || &(first.mData) != &(second.mData)){
				throw std::runtime_error("Error ..... ");
			}
			return  first.mCurrentNum != second.mCurrentNum;
		}

		size_t CurrentIndex() const{
			return mCurrentNum;
		}

		const MTypeWrap<Type, AllocatorType>&  CurrentData(){
			return mData;
		}
	protected:
		MTypeWrap<Type, AllocatorType>& mData;
		size_t							mNum;
		size_t							mCurrentNum;
	};

	class iterator : public const_iterator{
	public:
		iterator(MTypeWrap<Type, AllocatorType>& ptr, size_t num, size_t cnum = 0) :
			const_iterator(ptr, num, cnum)
		{}

		iterator(const iterator& other) :
			const_iterator(other)
		{}

		iterator& operator=(const iterator& other){
			const_iterator::operator=(other);
			return *this;
		}

		value_type* operator->(){
			if (mCurrentNum < 0 || mCurrentNum >= mNum){
				throw std::out_of_range("index out of range ..... ");
			}
			return &mData.proxy(mCurrentNum);
		}

		const value_type* operator->() const{
			if (mCurrentNum < 0 || mCurrentNum >= mNum){
				throw std::out_of_range("index out of range ..... ");
			}
			return &mData.proxy(mCurrentNum);
		}

		reference operator*(){
			if (mCurrentNum < 0 || mCurrentNum >= mNum){
				throw std::out_of_range("index out of range ..... ");
			}
			return mData.proxy(mCurrentNum);
		}

		const reference operator*() const{
			if (mCurrentNum < 0 || mCurrentNum >= mNum){
				throw std::out_of_range("index out of range ..... ");
			}
			return mData.proxy(mCurrentNum);
		}

		iterator operator++(int){
			iterator temp(*this);
			++mCurrentNum;
			return temp;
		}

		iterator& operator++(){
			++mCurrentNum;
			return *this;
		}

		iterator operator--(int){
			iterator temp(*this);
			--mCurrentNum;
			return temp;
		}

		iterator& operator--(){
			--mCurrentNum;
			return *this;
		}

		iterator& operator+(size_t index){
			mCurrentNum += index;
			return *this;
		}

		iterator& operator-(size_t index){
			mCurrentNum -= index;
			return *this;
		}

		iterator& operator+=(size_t index){
			mCurrentNum += index;
			return *this;
		}

		iterator& operator-=(size_t index){
			mCurrentNum -= index;
			return *this;
		}

		friend size_t operator-(iterator first, iterator second){
			return first.mCurrentNum - second.mCurrentNum;
		}

		friend bool operator<(iterator first, iterator second){
			if (first.mData.empty() && second.mData.empty()){
				return false;
			}
			if (first.mNum != second.mNum || &(first.mData) != &(second.mData)){
				throw std::runtime_error("Error ..... ");
			}
			return first.mCurrentNum < second.mCurrentNum;
		}

		friend bool operator>(iterator first, iterator second){
			if (first.mData.empty() && second.mData.empty()){
				return false;
			}
			if (first.mNum != second.mNum || &(first.mData) != &(second.mData)){
				throw std::runtime_error("Error ..... ");
			}
			return first.mCurrentNum > second.mCurrentNum;
		}

		friend bool operator==(iterator first, iterator second){
			if (first.mData.empty() && second.mData.empty()){
				return true;
			}
			if (first.mNum != second.mNum || &(first.mData) != &(second.mData)){
				throw std::runtime_error("Error ..... ");
			}
			return  first.mCurrentNum == second.mCurrentNum;
		}

		friend bool operator!=(iterator first, iterator second){
			if (first.mData.empty() && second.mData.empty()){
				return false;
			}
			if (first.mNum != second.mNum || &(first.mData) != &(second.mData)){
				throw std::runtime_error("Error ..... ");
			}
			return  first.mCurrentNum != second.mCurrentNum;
		}

		size_t CurrentIndex() const{
			return mCurrentNum;
		}

		MTypeWrap<Type, AllocatorType>&  CurrentData(){
			return mData;
		}
	};
public:
	MTypeWrap(const Type& val = Type());
	MTypeWrap(Type&& val);
	MTypeWrap& operator =(const Type& val);
	MTypeWrap& operator=(Type&& other);

	//
	// MTypeWrap<std::map<int,int>> m = MTypeWrap<std::map<int,int>>()(1,2)(3,4)(5,6)(7,8)
	//
	MTypeWrap& operator()(const_k_type k, const_v_type val);

	//
	// �����Ĳ�������
	//
	std::vector<K> keys() const;
	std::vector<V> values() const;

	//
	// counts count  contains contains_key ���Ƕ�key�����ж�
	//
	unsigned counts(const_k_type k) const;
	unsigned count(const_k_type k) const;
	bool contains(const_k_type k) const;
	bool contains_key(const_k_type k) const;

	//
	// �ж��Ƿ����ָ��ֵ
	//
	bool contains_value(const_v_type v) const;

	//
	// ȡ������ָ��ֵ������key
	//
	std::vector<K> from_value(const_v_type v) const;

	//
	// ȡ������ָ��ֵ�ĵ�һ��key
	//
	K first_key(const_v_type v) const;

	//
	// ͨ��key��ȡֵ
	//
	const ValueProxiy at(const_k_type k) const;
	ValueProxiy at(const_k_type k);
	const ValueProxiy operator[](const_k_type k) const;
	ValueProxiy operator[](const_k_type k);

        const Value& unsafe_at(const_k_type k) const;
        Value& unsafe_at(const_k_type k);

        const Value& unsafe_ref(const_k_type k) const;
        Value& unsafe_ref(const_k_type k);

	//
	// �ж�map�Ƿ�Ϊ��
	//
	bool empty() const;

	//
	// ��ȡ���ݴ�С
	//
	unsigned size() const;

	//
	// ����key��ֵ
	//
	bool insert(const_k_type k, const_v_type v);

	//
	// �Ƴ�ָ��key
	//
	bool remove(const_k_type k);
	void erase(const_k_type k);

	//
	// ͨ�������������Ƴ�
	//
	void erase(iterator it);
	void erase(iterator begpos, iterator endpos);

	//
	// ����������������
	//
	void clear();

	//
	// ͨ��ָ�������޸�ָ��key��ֵ
	// ���ָ����key�����ڣ���ô�½�һ��
	// ֵ�����ô���
	//
	template<class Fun>
	void transform(const_k_type k, Fun fun);

	//
	// ͨ��ָ������ɾ��������������
	// ����Ϊkey �� value
	// ��������Ϊbool
	//
	template<class Fun>
	void erase_if(Fun fun);

	//
	// ��������
	//
	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	void print(const char* msg = "", std::ostream& os = std::cout) const;

	void ostream(std::ostream& os, const char* spliter = " ");
	void istream(std::istream& is);

	void save(const char* filename, const char* spliter = "\t");
	void load(const char* filename);



	void lock();
	void unlock();
	bool islock() const;


	operator Type();

	Type& toType();
	const Type& toType() const;


	MTypeWrap clone();
	MTypeWrap clone() const;

	//
	// ֱ������ԭʼ����
	//
	const Type& reference_obj();
	const Type& reference_obj() const;

	const Type& ref(){ return reference_obj(); }
	const Type& ref() const{ return reference_obj(); }

	//
	// ��ȡ���ݵ�ַ
	//
	void* Address() const;

	//
	// ��ʽת����std::map
	//
	template<class Cmp2, class A, template<class K1, class V1, class C2, class A2>class M>
	operator M<K, V, Cmp2, A>(){
		M<K, V, Cmp2, A> __m;
		for (auto& m : mVal->mVal){
			__m[m.first] = m.second;
		}
		return __m;
	}

	template<class Cmp2, class A, template<class, class, class, class>class M>
	operator M<K, V, Cmp2, A>() const{
		M<K, V, Cmp2, A> __m;
		for (auto& m : mVal->mVal){
			__m[m.first] = m.second;
		}
		return __m;
	}

	//
	// ��ʽת��ΪQMap
	//
	template<template<class, class> class M>
	operator M<K, V>(){
		M<K, V> __m;
		for (auto& m : mVal->mVal){
			__m[m.first] = m.second;
		}
		return __m;
	}


	template<template<class K1, class V1> class M>
	operator M<K, V>() const{
		M<K, V> __m;
		for (auto& m : mVal->mVal){
			__m[m.first] = m.second;
		}
		return __m;
	}

	bool equals(const MTypeWrap& other){
		if (empty() && other.empty()){
			return true;
		}

		if (size() != other.size()){
			return false;
		}

		std::vector<K> lkeys = keys();
		std::vector<V> lvalues = other.values();

		std::vector<K> rkeys = keys();
		std::vector<V> rvalues = other.values();

		for (int i = 0; i < lkeys.size(); ++i){
			if (lkeys[i] != rkeys[i]){
				return false;
			}
		}

		for (int i = 0; i < rvalues.size(); ++i){
			if (lvalues[i] != rvalues[i]){
				return false;
			}
		}
		return true;
	}

	//
	// ʵ�������
	//
	friend std::ostream& operator<<(std::ostream& os, const MTypeWrap& other){
		for (auto& c : mVal->mVal){
			os << c.first << "," << c.second << std::endl;
		}
		return os;
	}

	friend bool operator==(const MTypeWrap& left, const MTypeWrap& right){
		return left.equals(right);
	}

	friend bool operator!=(const MTypeWrap& left, const MTypeWrap& right){
		return !(left == right);
	}

private:
	class MContentType : public MRefImpl<AllocatorType>
	{
	public:
		MContentType(const Type& val = Type());
		MContentType(const MContentType& other);
		MContentType& operator=(const MContentType& other);
		MContentType& operator =(const Type& val);
		void updatevalue(const ValueType& val);
		void updatevalue(const_k_type k,const_v_type v);
		Type   mVal;
	};
	MRefWrap<MContentType> mVal;

	Proxiy proxy(unsigned index);
	const Proxiy proxy(unsigned index) const;
};

/******************************************������ʵ��ϸ��û��Ȥ���Բ��ù���*************************************************************************/
/*-----------------------------------------------------------------------------------------------*/
/*   ʵ��
*
*
*
*
*
*
*
*
*
*
/*-----------------------------------------------------------------------------------------------
*
*
*
*
*/
/*---------------------------------------------�����ķָ���---------------------------------------*/
//
// �����ʵ��
//
template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::Proxiy(MTypeWrap< std::map<K, V>, AllocatorType>* data, std::size_t index) :
mData(data),
mIndex(index)
{
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::Proxiy(const typename MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy& other) :
mData(other.mData),
mIndex(other.mIndex)
{
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy& MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::operator=(
	const typename MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy& val)
{
	if (mData->mVal->IsShared()){
		mData->mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*(mData->mVal));
	}
	mData->mVal->updatevalue(mIndex, val);
	return *this;
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy& 
MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::operator=(const typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueType& val){
	if (mData->mVal->IsShared()){
		mData->mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*(mData->mVal));
	}
	mData->mVal->updatevalue(mIndex, val);
	return *this;
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::operator typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueType() const{
	auto beg = mData->mVal->mVal.begin();
	std::advance(beg, mIndex);
	return *beg;
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::operator typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueType(){
	auto beg = mData->mVal->mVal.begin();
	std::advance(beg, mIndex);
	return *beg;
}

template<class K, class V, class AllocatorType>
const std::pair<const K,V>* MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::operator->()
{
	auto beg = mData->mVal->mVal.begin();
	std::advance(beg, mIndex);
	return &(*beg);
}

template<class K, class V, class AllocatorType>
const std::pair<const K, V>* MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::operator->() const
{
	auto beg = mData->mVal->mVal.begin();
	std::advance(beg, mIndex);
	return &(*beg);
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueType MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::toT() const{
	auto beg = mData->mVal->mVal.begin();
	std::advance(beg, mIndex);
	return *beg;
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueType& MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::ref(){
	auto beg = mData->mVal->mVal.begin();
	std::advance(beg, mIndex);
	return *beg;
}

template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueType& MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy::ref() const{
	auto beg = mData->mVal->mVal.begin();
	std::advance(beg, mIndex);
	return *beg;
}


///
/// ֵ�Ĵ�����
///
template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy::ValueProxiy(
	MTypeWrap<std::map<K, V>, AllocatorType>* data, 
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type key):
	mData(data),
	mKey(key)
{

}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy::ValueProxiy(
	const ValueProxiy& other):
mData(other.mData),
mKey(other.mKey)
{
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy&  MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy::operator=(const typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy& val)
{
	if (mData->mVal->IsShared()){
		mData->mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*(mData->mVal));
	}
	mData->mVal->updatevalue(mKey, val.toT());
	return *this;
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy&  MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy::operator=(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_v_type val)
{
	if (mData->mVal->IsShared()){
		mData->mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*(mData->mVal));
	}
	mData->mVal->updatevalue(mKey, val);
	return *this;
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy::operator typename MTypeWrap< std::map<K, V>, AllocatorType>::Value()const
{
	return mData->mVal->mVal[mKey];
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy::operator typename MTypeWrap< std::map<K, V>, AllocatorType>::Value()
{
	return mData->mVal->mVal[mKey];
}

template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::Value* MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy::operator&(){
	return &(mData->mVal->mVal[mKey]);
}

template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::Value* MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy::operator&() const
{
	return &(mData->mVal->mVal[mKey]);
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::Value MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy::toT() const
{
	return mData->mVal->mVal[mKey];
}

//-------------------------------------------------------------------
//
//
//--------------------------------------------------------------------
template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::MContentType::MContentType(const typename MTypeWrap< std::map<K, V>, AllocatorType>::Type& val) :
MRefImpl<AllocatorType>(),
mVal(val)
{
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::MContentType::MContentType(const typename MTypeWrap< std::map<K, V>, AllocatorType>::MContentType& other) :
MRefImpl<AllocatorType>(),
mVal(other.mVal)
{
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::MContentType& MTypeWrap< std::map<K, V>, AllocatorType>::MContentType::operator = (
	const typename MTypeWrap< std::map<K, V>, AllocatorType>::MContentType& other)
{
	MRefImpl<Allocator>::operator=(other);
	mVal = other.mVal;
	return *this;
}


template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::MContentType& MTypeWrap< std::map<K, V>, AllocatorType>::MContentType::operator = (
	const typename MTypeWrap< std::map<K, V>, AllocatorType>::Type& val)
{
	MRefImpl<Allocator>::operator=(*this);
	mVal = val;
	return *this;
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::MContentType::updatevalue(const typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueType& val)
{
	mVal[val.first] = val.second;
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::MContentType::updatevalue(
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k, 
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_v_type v)
{
	mVal[k] = v;
}

//--------------------------------------------------------------------------
//
//  ��װ���ʵ��
//
//---------------------------------------------------------------------------

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::MTypeWrap(const typename MTypeWrap< std::map<K, V>, AllocatorType>::Type& val):
mVal(new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(val))
{
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::MTypeWrap(typename MTypeWrap< std::map<K, V>, AllocatorType>::Type&& val):
mVal(new MTypeWrap<std::map<K, V>, AllocatorType>::MContentType(val))
{
	val.clear();
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>& MTypeWrap< std::map<K, V>, AllocatorType>::operator =(const typename MTypeWrap< std::map<K, V>, AllocatorType>::Type& val)
{
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(val);
	}
	else{
		mVal->mVal = val;
	}
	return *this;
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>& MTypeWrap< std::map<K, V>, AllocatorType>::operator=(Type&& other)
{
	if (mVal->IsShared()){
		mVal = new typename MTypeWrap< C<T>, AllocatorType>::MContentType(other);
	}
	else{
		mVal->mVal = other;
	}
	other.clear();
	return *this;
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>& MTypeWrap< std::map<K, V>, AllocatorType>::operator()(
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k, 
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_v_type val)
{
	mVal->mVal[k] = val;
	return *this;
}

//
// �����Ĳ�������
//
template<class K, class V, class AllocatorType>
std::vector<K> MTypeWrap< std::map<K, V>, AllocatorType>::keys() const{
	std::vector<K> res;
	for (auto& m : mVal->mVal){
		res.push_back(m.first);
	}
	return res;
}

template<class K, class V, class AllocatorType>
std::vector<V> MTypeWrap< std::map<K, V>, AllocatorType>::values() const{
	std::vector<V> res;
	for (auto& m : mVal->mVal){
		res.push_back(m.second);
	}
	return res;
}

template<class K, class V, class AllocatorType>
unsigned MTypeWrap< std::map<K, V>, AllocatorType>::counts(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k) const
{
	return mVal->mVal.count(k);
}

template<class K, class V, class AllocatorType>
unsigned MTypeWrap< std::map<K, V>, AllocatorType>::count(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k) const
{
	return mVal->mVal.count(k);
}

template<class K, class V, class AllocatorType>
bool MTypeWrap< std::map<K, V>, AllocatorType>::contains(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k) const{
	return mVal->mVal.count(k) > 0 ? true : false;
}

template<class K, class V, class AllocatorType>
bool MTypeWrap< std::map<K, V>, AllocatorType>::contains_key(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k) const
{
	return mVal->mVal.count(k) > 0 ? true : false;
}

template<class K, class V, class AllocatorType>
bool MTypeWrap< std::map<K, V>, AllocatorType>::contains_value(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_v_type v) const
{
	std::vector<V> res = values();
	if (res.find(v) != res.end()){
		return true;
	}
	return false;
}

template<class K, class V, class AllocatorType>
std::vector<K> MTypeWrap< std::map<K, V>, AllocatorType>::from_value(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_v_type v) const
{
	std::vector<K> res;
	for (auto& m : mVal->mVal){
		if (v == m.second)
			res.push_back(m.first);
	}
	return res;
}

template<class K, class V, class AllocatorType>
K MTypeWrap< std::map<K, V>, AllocatorType>::first_key(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_v_type v) const{
	for (auto& m : mVal->mVal){
		if (v == m.second)
			return m.first;
	}
	return K();
}

template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy MTypeWrap< std::map<K, V>, AllocatorType>::at(
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k) const
{
	return const_cast<MTypeWrap*>(this)->at(k);
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy MTypeWrap< std::map<K, V>, AllocatorType>::at(
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k)
{
	if (mVal->mVal.count(k)){
		return MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy(this, k);
	}
	throw std::out_of_range("MTypeWrap<K,V> Not Contains Current Key");
}

template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy MTypeWrap< std::map<K, V>, AllocatorType>::operator[](
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k) const
{
	return const_cast<MTypeWrap*>(this)->operator[](k);
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy MTypeWrap< std::map<K, V>, AllocatorType>::operator[](
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k)
{
	if (mVal->mVal.count(k)){
		return MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy(this, k);
	}
	else{
		mVal->mVal[k] = V();
		return MTypeWrap< std::map<K, V>, AllocatorType>::ValueProxiy(this, k);
	}
}

template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::Value& MTypeWrap< std::map<K, V>, AllocatorType>::unsafe_at(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k) const{
    return mVal->mVal.at(k);
}


template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::Value& MTypeWrap< std::map<K, V>, AllocatorType>::unsafe_at(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k){
    return mVal->mVal.at(k);
}


template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::Value& MTypeWrap< std::map<K, V>, AllocatorType>::unsafe_ref(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k) const{
    return mVal->mVal.at(k);
}


template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::Value& MTypeWrap< std::map<K, V>, AllocatorType>::unsafe_ref(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k){
    return mVal->mVal.at(k);
}

template<class K, class V, class AllocatorType>
bool MTypeWrap< std::map<K, V>, AllocatorType>::empty() const{
	return mVal->mVal.empty();
}

template<class K, class V, class AllocatorType>
unsigned MTypeWrap< std::map<K, V>, AllocatorType>::size() const{
	return mVal->mVal.size();
}

template<class K, class V, class AllocatorType>
bool MTypeWrap< std::map<K, V>, AllocatorType>::insert(
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k, 
	typename MTypeWrap< std::map<K, V>, AllocatorType>::const_v_type v)
{
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	mVal->mVal.insert(std::make_pair(k, v));
	return true;
}

template<class K, class V, class AllocatorType>
bool MTypeWrap< std::map<K, V>, AllocatorType>::remove(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k)
{
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	if (mVal->mVal.count(k)){
		mVal->mVal.erase(k);
		return true;
	}
	return false;
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::erase(typename MTypeWrap< std::map<K, V>, AllocatorType>::iterator it)
{
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	int num = it.CurrentIndex();
	auto beg = mVal->mVal.begin();
	std::advance(beg, num);
	mVal->mVal.erase(beg);
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::erase(typename MTypeWrap< std::map<K, V>, AllocatorType>::const_k_type k)
{
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	mVal->mVal.erase(k);
}


template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::erase(
	typename MTypeWrap< std::map<K, V>, AllocatorType>::iterator begpos, 
	typename MTypeWrap< std::map<K, V>, AllocatorType>::iterator endpos)
{
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	int num = begpos.CurrentIndex();
	auto beg = mVal->mVal.begin();
	std::advance(beg, num);
	num = endpos.CurrentIndex();
	auto beg2 = mVal->mVal.begin();
	std::advance(beg2, num);
	mVal->mVal.erase(beg, beg2);
}

//
// ͨ��ָ�������޸�ָ��key��ֵ
// ���ָ����key�����ڣ���ô�½�һ��
// ֵ�����ô���
//
template<class K, class V, class AllocatorType>
template<class Fun>
void MTypeWrap< std::map<K, V>, AllocatorType>::transform(const_k_type k, Fun fun)
{
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	V val;
	if (mVal->mVal.count(k)){
		val = mVal->mVal.at(k);
	}
	else{
		val = V();
	}
	fun(val);
	mVal->mVal[k] = val;
}

//
// ͨ��ָ������ɾ��������������
// ����Ϊkey �� value
// ��������Ϊbool
//
template<class K, class V, class AllocatorType>
template<class Fun>
void MTypeWrap< std::map<K, V>, AllocatorType>::erase_if(Fun fun)
{
	if (mVal->mVal.empty())
		return;
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	auto beg = mVal->mVal.begin();
	for (; beg != mVal->mVal.end();){
		K k = (beg)->first;
		V v = (beg)->second;
		if (fun(k, v)){
			mVal->mVal.erase(beg++);
		}
		else{
			++beg;
		}
	}
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::clear()
{
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	mVal->mVal.clear();
}


//
// ��������
//
template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::iterator MTypeWrap< std::map<K, V>, AllocatorType>::begin()
{
	return typename MTypeWrap< std::map<K, V>, AllocatorType>::iterator(*this, mVal->mVal.size());
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::iterator MTypeWrap< std::map<K, V>, AllocatorType>::end()
{
	return typename MTypeWrap< std::map<K, V>, AllocatorType>::iterator(*this, mVal->mVal.size(), mVal->mVal.size());
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::const_iterator MTypeWrap< std::map<K, V>, AllocatorType>::begin() const
{
	return MTypeWrap< std::map<K, V>, AllocatorType>::const_iterator(const_cast<MTypeWrap&>(*this), mVal->mVal.size());
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::const_iterator MTypeWrap< std::map<K, V>, AllocatorType>::end() const
{
	return MTypeWrap< std::map<K, V>, AllocatorType>::const_iterator(const_cast<MTypeWrap&>(*this), mVal->mVal.size(), mVal->mVal.size());
}


template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::print(const char* msg, std::ostream& os) const
{
	os << msg << std::endl;
	for (auto& m : mVal->mVal){
		os << m.first << "," << m.second << std::endl;
	}
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::ostream(std::ostream& os, const char* spliter){
	for (auto& m : mVal->mVal){
		os << m.first << spliter << m.second << spliter;
	}
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::istream(std::istream& is){
	K key;
	V val;
	clear();
	while (is.eof() == false){
		is >> key;
		if (is.eof())
			break;
		is >> val;
		mVal->mVal[key] = val;
	}
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::save(const char* filename, const char* spliter){
	std::ostream outFile(filename);
	for (auto& m : mVal->mVal){
		outFile << m.first << spliter << m.second << spliter;
	}
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::load(const char* filename){
	std::ifstream inFile(filename);
	K key;
	V val;
	clear();
	while (inFile.eof() == false){
		inFile >> key;
		if (inFile.eof())
			break;
		inFile >> val;
		mVal->mVal[key] = val;
	}
	inFile.close();
}


template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::lock(){
	if (mVal->IsShared()){
		mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	mVal->MarkUnshareable();
}

template<class K, class V, class AllocatorType>
void MTypeWrap< std::map<K, V>, AllocatorType>::unlock(){
	mVal->MarkShareable();
}

template<class K, class V, class AllocatorType>
bool MTypeWrap< std::map<K, V>, AllocatorType>::islock() const{
	return mVal->IsShared();
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType>::operator typename MTypeWrap< std::map<K, V>, AllocatorType>::Type()
{
	return mVal->mVal;
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::Type& MTypeWrap< std::map<K, V>, AllocatorType>::toType(){
	if (mVal->IsShared()){
		mVal = new MTypeWrap<std::map<K, V>, AllocatorType>::MContentType(*mVal);
	}
	mVal->MarkUnshareable();
	return mVal->mVal;
}

template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::Type& MTypeWrap< std::map<K, V>, AllocatorType>::toType() const
{
	return mVal->mVal;
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType> MTypeWrap< std::map<K, V>, AllocatorType>::clone(){
	MTypeWrap< std::map<K, V>, AllocatorType> newobj;
	newobj.mVal = new MTypeWrap< std::map<K, V>, AllocatorType>::MContentType(*mVal);
	newobj.mVal->MarkUnshareable();
	return newobj;
}

template<class K, class V, class AllocatorType>
MTypeWrap< std::map<K, V>, AllocatorType> MTypeWrap< std::map<K, V>, AllocatorType>::clone() const{
	return const_cast<MTypeWrap<std::map<K, V>, AllocatorType>*>(this)->clone();
}

//
// ֱ������ԭʼ����
//
template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::Type& MTypeWrap< std::map<K, V>, AllocatorType>::reference_obj(){
	return mVal->mVal;
}

template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::Type& MTypeWrap< std::map<K, V>, AllocatorType>::reference_obj() const{
	return mVal->mVal;
}

//
// ��ȡ���ݵ�ַ
//
template<class K, class V, class AllocatorType>
void* MTypeWrap< std::map<K, V>, AllocatorType>::Address() const{
	return &(mVal->mVal);
}

template<class K, class V, class AllocatorType>
typename MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy MTypeWrap< std::map<K, V>, AllocatorType>::proxy(unsigned index)
{
	return typename MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy(this, index);
}

template<class K, class V, class AllocatorType>
const typename MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy MTypeWrap< std::map<K, V>, AllocatorType>::proxy(unsigned index) const
{
	return typename MTypeWrap< std::map<K, V>, AllocatorType>::Proxiy(const_cast<MTypeWrap*>(this), index);
}
