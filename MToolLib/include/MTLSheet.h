#pragma once
#include <MToolLib>
#include <vector>
#include <iostream>
#include <fstream>
#include <MCopyValue.h>
#include <numeric>
#include <omp.h>
//
// ����һ����������,Row ���� ��һ���������� ,�ܹ���ȡÿһ�е�ԭʼ����,����ֻ�ܹ���ȡÿһ�еĿ�������
//

namespace TL{
	//
	// Ĭ���ж��Ƿ�Ϊ��
	//
	template<class T>
	struct MIsEmpty{
		bool operator()(T val){
			return val.empty();
		}
	};


	template<class T>
	class MTLSheet : public TL::MTLObject
	{
	public:
		enum Angle{
			__1Div2Pi = 0,          // 90
			__2Div2Pi,		// 180
			__3Div2Pi,		// 270
			__4Div2Pi,		// 360
			__N1Div2Pi,		// -90
			__N2Div2Pi,		// -180
			__N3Div2Pi,		// -1270
			__N4Div2Pi,		// -360
			__None			// 0
		};
		typedef std::vector<T> colum_data;
		typedef colum_data value_type;
		typedef std::vector<value_type> data_module;
		typedef typename std::vector<value_type>::iterator iterator;
		typedef typename std::vector<value_type>::const_iterator const_iterator;
		MTLSheet(){}
		~MTLSheet(){}

		MTLSheet(const MTLSheet& other) :mData(other.mData)
		{}

		MTLSheet(const mj::MMatrixSheet<T>& __data){
			mData = __data.t().dettach();
		}

		MTLSheet(MTLSheet&& other) :mData(other.mData)
		{
			other.clear();
		}
		MTLSheet& operator=(const MTLSheet& other){
			mData = other.mData;
			return *this;
		}

		MTLSheet& operator=(MTLSheet&& other){
			mData = other.mData;
			other.clear();
			return *this;
		}

		MTLSheet(const std::initializer_list<T>& l, int col){
			value_type val(l.begin(), l.end());
			push_value(val, col);
		}

		template<class U, class A, template<class U1, class A1> class C>
		MTLSheet(const C<U, A>& l, int col){
			value_type val(l.begin(), l.end());
			push_value(val, col);
		}

		template<class U, template<class U1> class C>
		MTLSheet(const C<U>& l, int col){
			value_type val(l.begin(), l.end());
			push_value(val, col);
		}


		//
		// ��ʽת��Ϊ�������͵ľ���
		//
		template<class U, template<class U1> class M>
		operator M<U>(){
			M<U> __Result;
			int row = this->RowCounts();
			int col = this->ColumCounts();
			__Result.resize(row, col);
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					mj::copyvalue(__Result.at(i, j), (*this)(i, j));
				}
			}
			return __Result;
		}


		//
		// �о������
		//
		template<class L, class A,
			template<class U1, class L1, class A1> class M>
		MTLSheet& fromMatrix(const M<T, L, A>& m){
			int row = m.size1();
			int col = m.size2();
			resize(row, col);
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					(*this)(i, j) = m(i, j);
				}
			}
			return *this;
		}

		template<class U, class L, class A,
			template<class U1, class L1, class A1> class M>
		MTLSheet& fromMatrix(const M<U, L, A>& m){
			int row = m.size1();
			int col = m.size2();
			resize(row, col);
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					mj::copyvalue((*this)(i, j), m(i, j));
				}
			}
			return *this;
		}

		//
		// ʹ�ñ�׼��ϵ��������
		//
		template<class A, template<class U1, class A1> class V>
		MTLSheet& fromVector(const V<T, A>& v, int row, int col){
			if (v.size() != row*col)
				return *this;
			resize(row, col);
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					try{
						(*this)(i, j) = v[i*col + j];
					}
					catch (...){
						return *this;
					}
				}
			}
			return *this;
		}

		template<class U, class A, template<class U1, class A1> class V>
		MTLSheet& fromVector(const V<U, A>& v, int row, int col){
			if (v.size() != row*col)
				return *this;
			resize(row, col);
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					try{
						mj::copyvalue((*this)(i, j), v.at(i*col + j));
					}
					catch (...){
						return *this;
					}
				}
			}
			return *this;
		}

		//
		// ��������������������
		//
		MTLSheet& fromArray(const T* array, int row, int col){
			resize(row, col);
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					try{
						(*this)(i, j) = array[i*col + j];
					}
					catch (...){
						return *this;
					}
				}
			}
			return *this;
		}

		template<class U>
		MTLSheet& fromArray(const U* array, int row, int col){
			resize(row, col);
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					try{
						mj::copyvalue((*this)(i, j), array[i*col + j]);
					}
					catch (...){
						return *this;
					}
				}
			}
			return *this;
		}

		//
		// ����ʹ��Qt��ϵ������䣬Ҳ����ʹ��Array���������
		//
		template<class U, template<class U1> class V>
		MTLSheet& fromArray(const V<U>& array, int row, int col){
			std::vector<U> v(array.begin(), array.end());
			return fromVector(v, row, col);
		}

		template<template<class U> class V>
		MTLSheet& fromArray(const V<T>& array, int row, int col){
			std::vector<T> v(array.begin(), array.end());
			return fromVector(v, row, col);
		}

		//
		// ֻ��ʹ��HArray�����
		//
		template<class U>
		MTLSheet& fromArray(const TL::Vector<TL::Vector<U>>& array){
			clear();
			for (auto& v1 : array){
				value_type __v;
				for (auto& v : v1){
					try{
						T __v;
						mj::copyvalue(__v, v);
						__v.push_back(__v);
					}
					catch (...){
						__v.push_back(T());
					}
				}
				push_back(__v);
			}
			return *this;
		}

		MTLSheet& fromArray(const TL::Vector<TL::Vector<T> > &array){
			clear();
			for (auto& v1 : array){
				push_back(v1);
			}
			return *this;
		}

		template<class U, class Prd = std::equal_to<T>>
		MTLSheet subSheet(const U& value, int col, Prd __Prd = Prd()){
			MTLSheet result;
			for (auto& m : mData){
				T val = m.at(col);
				T val2;
				mj::copyvalue(val2, value);
				if (__Prd(val, val2)){
					result.push_value(m);
				}
			}
			return result;
		}

		template<class F>
		MTLSheet subSheet(F fun){
			MTLSheet result;
			for (auto& m : mData){
				value_type v = fun(m);
				result.push_back(v);
			}
			return result;
		}

		//
		// �������
		//
		void clear(){
			mData.clear();
			mHoldCols.clear();
		}

		//
		// ��������Ƿ�Ϊ��
		//
		bool empty(){
			return mData.empty();
		}

		bool empty() const{
			return mData.empty();
		}

		//
		// ��ѯ�����Ƿ���ڿ�����
		//
		template<class PRD = MIsEmpty<T>>
		bool haveEmptyData(PRD prd = PRD()) const{
			if (empty()){
				return true;
			}
			for (auto& v1 : mData){
				for (auto& v2 : v1){
					if (prd(v2)){
						return true;
					}
				}
			}
			return false;
		}

		//
		// �����������
		//
		void fill(const T& value){
			for (auto& c : mData){
				std::fill(c.begin(), c.end(), value);
			}
		}

		template<class U>
		void fill(const U& value){
			T val;
			mj::copyvalue(val, value);
			fill(val);
		}

		//
		// ���������֮ʱ���е��ж��ᱻ��һ��
		//
		void push_back(const value_type& v){
			push_value(const_cast<value_type&>(v));
		}

		template<class A, template<class T1, class A1> class C>
		void push_back(const C<T, A>& value){
			value_type v(value.begin(), value.end());
			push_value(v);
		}

		template<class A, class U, template<class T1, class A1> class C>
		void push_back(const C<U, A>& value){
			value_type v;
			for (auto& __val : value){
				T __val2;
				mj::copyvalue(__val2, __val);
				v.push_back(__val2);
			}
			push_back(v);
		}

		template<template<class T1> class C>
		void push_back(const C<T>& value){
			value_type v(value.begin(), value.end());
			push_back(v);
		}

		template<class U, template<class T1> class C>
		void push_back(const C<U>& value){
			value_type v;
			for (auto& __val : value){
				T __val2;
				mj::copyvalue(__val2, __val);
				v.push_back(__val2);
			}
			push_back(v);
		}

		void push_back(const std::initializer_list<T>& value){
			value_type v(value.begin(), value.end());
			push_value(v);
		}

		template<class U>
		void push_back(const std::initializer_list<U>& value){
			value_type v;
			for (auto& __val : value){
				T __val2;
				mj::copyvalue(__val2, __val);
				v.push_back(__val2);
			}
			push_value(v);
		}

		template<class iter>
		void push_back(iter First, iter Last){
			push_value(value_type(First, Last));
		}

		//
		// ������ƴ�С
		//
		void resize(int row, int col){
			if (mData.empty()){
				for (int i = 0; i < row; ++i){
					value_type v;
					v.resize(col);
					mData.push_back(v);
				}
			}
			else{
				mData.resize(row);
				for (value_type& v : mData){
					v.resize(col);
				}
			}
		}

		//
		// ͨ����˵ֻ�������������������������ݱ����������
		//
		void setRowCounts(int rows){
			mData.resize(rows);
		}

		void setColumCounts(int cols){
			//
			// �����ǰû������
			// ��ôԤ��holdס����
			//
			if (mData.empty()){
				mHoldCols.resize(cols);
				return;
			}

			//
			// ����ֱ���޸��еĴ�С
			//
			for (auto& row : mData){
				row.resize(cols);
			}
		}

		//
		// �����
		//
		void addRow(int row = -1){
			if (mData.empty() || row < 0){
				push_value(value_type());
				return;
			}

			if (row >= mData.size()){
				throw std::out_of_range("Index Out Of Range");
			}
			int col = mData.back().size();
			value_type v;
			v.resize(col);
			mData.insert(mData.begin() + row, v);
		}

		//
		// �����
		//
		void AddColum(int col = -1){
			if (mData.empty()){
				mHoldCols.push_back(T());
				return;
			}
			for (value_type& v : mData){
				if (col < 0){
					v.push_back(T());
				}
				else{
					v.insert(v.begin() + col, T());
				}
			}
		}

		//
		// ������
		//
		int RowCounts(){
			return mData.size();
		}

		int RowCounts() const{
			return mData.size();
		}

		int ColumCounts(){
			if (mData.empty()){
				return 0;
			}
			return mData.back().size();
		}

		int ColumCounts() const{
			return const_cast<MTLSheet*>(this)->ColumCounts();
		}

		unsigned rows() const{
			return RowCounts();
		}

		unsigned cols() const{
			return ColumCounts();
		}

		//
		// ��ֵ����
		//
		T& operator()(int row, int col){
			if (mData.empty()){
				throw std::out_of_range("Index Out of range");
			}
			if (row<0 || row>mData.size()){
				throw std::out_of_range("Row Index Out of range");
			}

			if (col<0 || col>mData.back().size()){
				throw std::out_of_range("col Index Out of range");
			}
			return mData.at(row).at(col);
		}

		//
		// ������
		//
		const T& operator()(int row, int col) const{
			return const_cast<MTLSheet*>(this)->operator ()(row, col);
		}

		//
		// ��һ��Ķ�д����
		//
		void SetData(int row, int col, const T& value){
			this->operator()(row, col) = value;
		}

		T& ReadData(int row, int col){
			return this->operator()(row, col);
		}

		T& at(int row, int col){
			return this->operator()(row, col);
		}

		const T& at(int row, int col) const{
			return this->operator()(row, col);
		}

		//
		// �������ֵ
		//
		T maxvalue(){
			std::vector<T> vals;
			for (auto& v1 : mData){
				auto it = std::minmax_element(v1.begin(), v1.end());
				vals.push_back(*it.first);
				vals.push_back(*it.second);
			}
			if (vals.empty())
				return T();
			return *(std::max_element(vals.begin(), vals.end()));
		}

		//
		// ������Сֵ
		//
		T minvalue(){
			std::vector<T> vals;
			for (auto& v1 : mData){
				auto it = std::minmax_element(v1.begin(), v1.end());
				vals.push_back(*it.first);
				vals.push_back(*it.second);
			}
			if (vals.empty())
				return T();
			return *(std::min_element(vals.begin(), vals.end()));
		}

		//
		// ����ƽ��ֵ
		//
		double Avalvalue(){
			std::vector<T> vals;
			this->toVector(vals);
			if (vals.empty())
				return 0.0;
			double sum = std::accumulate(vals.begin(), vals.end(), 0);
			return sum / vals.size();
		}

		//
		// �����׼��
		//
		double standardiff(){
			std::vector<T> vals;
			this->toVector(vals);
			if (vals.size() <= 1)
				return 0.0;
			double val = Avalvalue();
			double sum = std::accumulate(vals.begin(), vals.end(), 0, [&](double v1, T v){
				return v1 + (v - val)*(v - val);
			});
			double diff = std::sqrt(sum / vals.size());
			return diff;
		}

		//
		// ָ��ƽ��ֵ�����׼��
		//
		double standardiff_if(double val){
			std::vector<T> vals;
			this->toVector(vals);
			if (vals.size() <= 1)
				return 0.0;
			double sum = std::accumulate(vals.begin(), vals.end(), 0, [&](double v1, T v){
				return v1 + (v - val)*(v - val); });
				double diff = std::sqrt(sum / vals.size());
				return diff;
		}

		//
		// ���㷽��
		//
		double squaldiff(){
			std::vector<T> vals;
			this->toVector(vals);
			if (vals.size() <= 1)
				return 0.0;
			double val = Avalvalue();
			double sum = std::accumulate(vals.begin(), vals.end(), 0, [&](double v1, T v){
				return v1 + (v - val)*(v - val);
			});
			return sum / vals.size();
		}

		//
		// ָ��ƽ��ֵ���㷽��
		//
		double squaldiff_if(double val){
			std::vector<T> vals;
			this->toVector(vals);
			if (vals.size() <= 1)
				return 0.0;
			double sum = std::accumulate(vals.begin(), vals.end(), 0, [&](double v1, T v){
				return v1 + (v - val)*(v - val); });
				return sum / vals.size();
		}

		//
		// ��ȡ���ֵ��Сֵ��λ��
		//
		T maxvalue_pos(int& x, int& y){
			std::vector<T> vals;
			this->toVector(vals);
			auto it = std::max_element(vals.begin(), vals.end());
			int num = std::distance(vals.begin(), it);
			y = num / ColumCounts();
			x = num % ColumCounts();
			return *it;
		}

		T minvalue_pos(int& x, int& y){
			std::vector<T> vals;
			this->toVector(vals);
			auto it = std::min_element(vals.begin(), vals.end());
			int num = std::distance(vals.begin(), it);
			y = num / ColumCounts();
			x = num % ColumCounts();
			return *it;
		}

		//
		// �������ֵ��ָ��ֵ֮��
		//
		template<class CMP = std::equal_to<T>>
		T maxvalue(const T& excepty){
			std::vector<T> vals;
			this->toVector(vals);
			vals.erase(std::remove_if(vals.begin(), vals.end(), [&](T v){return CMP()(v, excepty); }),
				vals.end());
			if (vals.empty())
				return T();
			return *(std::max_element(vals.begin(), vals.end()));
		}

		//
		// ������Сֵ��ָ��ֵ֮��
		//
		template<class CMP = std::equal_to<T>>
		T minvalue(const T& excepty){
			std::vector<T> vals;
			this->toVector(vals);
			vals.erase(std::remove_if(vals.begin(), vals.end(), [&](T v){return CMP()(v, excepty); }),
				vals.end());
			if (vals.empty())
				return T();
			return *(std::min_element(vals.begin(), vals.end()));
		}

		//
		// ����ƽ��ֵ��ָ��ֵ֮��
		//
		template<class CMP = std::equal_to<T>>
		double Avalvalue(const T& excepty){
			std::vector<T> vals;
			this->toVector(vals);
			vals.erase(std::remove_if(vals.begin(), vals.end(), [&](T v){return CMP()(v, excepty); }),
				vals.end());
			if (vals.empty())
				return 0.0;
			double sum = std::accumulate(vals.begin(), vals.end(), 0);
			return sum / vals.size();
		}

		//
		// �����׼���ָ��ֵ֮��
		//
		template<class CMP = std::equal_to<T>>
		double standardiff(const T& excepty){
			std::vector<T> vals;
			this->toVector(vals);
			vals.erase(std::remove_if(vals.begin(), vals.end(), [&](T v){return CMP()(v, excepty); }),
				vals.end());
			if (vals.size() <= 1)
				return 0.0;
			double val = std::accumulate(vals.begin(), vals.end(), 0);
			val /= vals.size();
			double sum = std::accumulate(vals.begin(), vals.end(), 0, [&](double v1, T v){
				return v1 + (v - val)*(v - val); });
				double diff = std::sqrt(sum / vals.size());
				return diff;
		}

		//
		// ���ո�����ƽ��ֵ�����׼���ָ��ֵ֮��
		//
		template<class CMP = std::equal_to<T>>
		double standardiff_if(double val, const T& excepty){
			std::vector<T> vals;
			this->toVector(vals);
			vals.erase(std::remove_if(vals.begin(), vals.end(), [&](T v){return CMP()(v, excepty); }),
				vals.end());
			if (vals.size() <= 1)
				return 0.0;
			double sum = std::accumulate(vals.begin(), vals.end(), 0, [&](double v1, T v){
				return v1 + (v - val)*(v - val); });
				return std::sqrt(sum / vals.size());
		}

		//
		// ���㷽���ָ��ֵ֮��
		//
		template<class CMP = std::equal_to<T>>
		double squaldiff(const T& excepty){
			std::vector<T> vals;
			this->toVector(vals);
			vals.erase(std::remove_if(vals.begin(), vals.end(), [&](T v){return CMP()(v, excepty); }),
				vals.end());
			if (vals.size() <= 1)
				return 0.0;
			double val = std::accumulate(vals.begin(), vals.end(), 0);
			val /= vals.size();
			double sum = std::accumulate(vals.begin(), vals.end(), 0, [&](double v1, T v){
				return v1 + (v - val)*(v - val); });
				return sum / vals.size();
		}

		//
		// ����ƽ��ֵ���㷽���ָ��ֵ֮��
		//
		template<class CMP = std::equal_to<T>>
		double squaldiff_if(double val, const T& excepty){
			std::vector<T> vals;
			this->toVector(vals);
			vals.erase(std::remove_if(vals.begin(), vals.end(), [&](T v){return CMP()(v, excepty); }),
				vals.end());
			if (vals.size() <= 1)
				return 0.0;
			double sum = std::accumulate(vals.begin(), vals.end(), 0, [&](double v1, T v){
				return v1 + (v - val)*(v - val); });
				return sum / vals.size();
		}

		//
		// ��������,�����ݵ�����һ������֮��
		//
		template < class CMP = std::equal_to<T>, class LessCMP = std::less<T>,
		class GreatCMP = std::greater < T >>
			MTLSheet& adjust(const T& adjustvalue, const T& __minvalue, const T& __maxvalue, const T& excepty){
				int row = this->RowCounts();
				int col = this->ColumCounts();
				for (int i = 0; i < row; ++i){
					for (int j = 0; j < col; ++j){
						if (CMP()(mData[i][j], excepty))
							continue;
						if (LessCMP()(mData[i][j], __minvalue)){
							mData[i][j] += adjustvalue;
						}
						else if (GreatCMP()(mData[i][j], __maxvalue)){
							mData[i][j] -= adjustvalue;
						}
					}
				}
				return *this;
			}


		//
		// �滻����,�����ݵ�����һ������֮��
		//
		template<class CMP = std::less<T>>
		MTLSheet& adjust(const T& replaced, const T& value, CMP prd = CMP()){
			int row = this->RowCounts();
			int col = this->ColumCounts();
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					if (prd(mData[i][j], value)){
						mData[i][j] = replaced;
					}
				}
			}
			return *this;
		}


		//
		// �����������������ֵ����һ��value
		//
		template<class CMP = std::equal_to<T>>
		MTLSheet& plus(const T& value, const T& excepty){
			int row = this->RowCounts();
			int col = this->ColumCounts();
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					if (CMP()(mData[i][j], excepty))
						continue;
					mData[i][j] += value;
				}
			}
			return *this;
		}

		//
		// �����������������ֵ��ȥһ��value
		//
		template<class CMP = std::equal_to<T>>
		MTLSheet& minus(const T& value, const T& excepty){
			return plus<CMP>(value*-1, excepty);
		}

		//
		// �����������������ֵ����һ��value
		//
		template<class U, class CMP = std::equal_to<T>>
		MTLSheet& mult(U value, const T& excepty){
			int row = this->RowCounts();
			int col = this->ColumCounts();
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					if (CMP()(mData[i][j], excepty))
						continue;
					mData[i][j] *= value;
				}
			}
			return *this;
		}

		//
		// �����������������ֵ����һ��value
		//
		template<class U, class CMP = std::equal_to<T>>
		MTLSheet& mod(U value, const T& excepty){
			return mult(1.0 / value, excepty);
		}

		//
		// ȫ��ִ��+=����
		//
		MTLSheet& operator+=(T value){
			int row = mData.size();
			for (int i = 0; i < row; ++i){
				int colum = mData[i].size();
				for (int j = 0; j < colum; ++j){
					mData[i][j] += value;
				}
			}
			return *this;
		}

		//
		// ȫ��ִ��-=����
		//
		MTLSheet& operator-=(T value){
			*this += -1 * value;
			return *this;
		}

		//
		// ȫ��ִ��*=����
		//
		MTLSheet& operator*=(T value){
			int row = mData.size();
			for (int i = 0; i < row; ++i){
				int colum = mData[i].size();
				for (int j = 0; j < colum; ++j){
					mData[i][j] *= value;
				}
			}
			return *this;
		}

		//
		// ȫ��ִ��/=����
		//
		MTLSheet& operator/=(T value){
			int row = mData.size();
			for (int i = 0; i < row; ++i){
				int colum = mData[i].size();
				for (int j = 0; j < colum; ++j){
					mData[i][j] /= value;
				}
			}
			return *this;
		}

		//
		// ��ȡ�л�ȡ������
		//
		value_type& Row(int row){
			return mData.at(row);
		}

		const value_type& Row(int row) const{
			return mData.at(row);
		}

		value_type Colum(int col){
			value_type coldata;
			for (value_type& s : mData){
				coldata.push_back(s.at(col));
			}
			return coldata;
		}

		value_type Colum(int col) const{
			return const_cast<MTLSheet*>(this)->Colum(col);
		}

		//
		// ת��Ϊ��׼��ϵ��
		//
		template<class A, template<class U1, class A1> class V>
		V<T, A>& toVector(V<T, A>& result){
			int rowcount = this->RowCounts();
			int colcount = this->ColumCounts();
			result.resize(rowcount*colcount);
			int index = 0;
			for (int i = 0; i < rowcount; ++i){
				for (int j = 0; j < colcount; ++j){
					result[index] = mData.at(i).at(j);
					index++;
				}
			}
			return result;
		}

		template<class A, template<class U1, class A1> class V>
		V<T, A>& toVector(V<T, A>& result) const{
			return const_cast<MTLSheet*>(this)->toVector(result);
		}

		template<class U, class A, template<class U1, class A1> class V>
		V<U, A>& toVector(V<U, A>& result){
			int rowcount = this->RowCounts();
			int colcount = this->ColumCounts();
			result.resize(rowcount*colcount);
			int index = 0;
			for (int i = 0; i < rowcount; ++i){
				for (int j = 0; j < colcount; ++j){
					try{
						mj::copyvalue(result[index], mData.at(i).at(j));
					}
					catch (std::runtime_error e){
						result[index] = U();
					}
					index++;
				}
			}
			return result;
		}

		template<class U, class A, template<class U1, class A1> class V>
		V<U, A>& toVector(V<U, A>& result) const{
			return const_cast<MTLSheet*>(this)->toVector(result);
		}

		//
		// ת��ΪQtϵ���Լ�HArray<T>
		//
		template<template<class U1> class V>
		V<T>& toQVector(V<T>& result){
			int rowcount = this->RowCounts();
			int colcount = this->ColumCounts();
			result.resize(rowcount*colcount);
			int index = 0;
			for (int i = 0; i < rowcount; ++i){
				for (int j = 0; j < colcount; ++j){
					result[index] = mData.at(i).at(j);
					index++;
				}
			}
			return result;
		}

		template<template<class U1> class V>
		V<T>& toQVector(V<T>& result) const{
			return const_cast<MTLSheet*>(this)->toQVector(result);
		}

		template<class U, template<class U1> class V>
		V<U>& toQVector(V<U>& result){
			int rowcount = this->RowCounts();
			int colcount = this->ColumCounts();
			result.resize(rowcount*colcount);
			int index = 0;
			for (int i = 0; i < rowcount; ++i){
				for (int j = 0; j < colcount; ++j){
					mj::copyvalue(result[index], mData.at(i).at(j));
					index++;
				}
			}
			return result;
		}

		template<class U, template<class U1> class V>
		V<U>& toQVector(V<U>& result) const{
			return const_cast<MTLSheet*>(this)->toQVector(result);
		}


		//
		// ת��λHArray
		//
		TL::Vector<TL::Vector<T>> toArray(){
			TL::Vector<TL::Vector<T>> __result;
			for (auto& v1 : mData){
				TL::Vector<T> __v;
				for (auto& v : v1){
					__v.push_back(v);
				}
				__result.push_back(__v);
			}
			return __result;
		}

		TL::Vector<TL::Vector<T>> toArray() const{
			return const_cast<MTLSheet*>(this)->toArray();
		}

		template<class U>
		TL::Vector<TL::Vector<U>> toArray(){
			TL::Vector<TL::Vector<U>> __result;
			for (auto& v1 : mData){
				TL::Vector<U> __v;
				for (auto& v : v1){
					try{
						U val1;
						mj::copyvalue(val1, v);
						__v.push_back(val1);
					}
					catch (...){
						;
					}
				}
				__result.push_back(__v);
			}
			return __result;
		}

		template<class U>
		TL::Vector<TL::Vector<U>> toArray() const{
			return const_cast<MTLSheet*>(this)->toArray<U>();
		}

		//
		// ת��Ϊ�������͵ı�
		//
		template<class U>
		MTLSheet<U> ToOtherType(){
			MTLSheet<U> __Result;
			int row = this->RowCounts();
			int col = this->ColumCounts();
			__Result.resize(row, col);
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					U val;
					mj::copyvalue(val, (*this)(i, j));
					__Result(i, j) = val;
				}
			}
			return __Result;
		}

		template<class U>
		MTLSheet<U> ToOtherType() const{
			return const_cast<MTLSheet*>(this)->ToOtherType<U>();
		}

		template<class U, class CMP = std::equal_to<T>>
		MTLSheet<U> ToOtherType(T excepty, U defaultvalue){
			MTLSheet<U> __Result;
			int rowc = this->RowCounts();
			int colc = this->ColumCounts();
			__Result.resize(rowc, colc);
			for (int i = 0; i < rowc; ++i){
				for (int j = 0; j < colc; ++j){
					if (CMP()(mData.at(i).at(j), excepty)){
						__Result(i, j) = defaultvalue;
					}
					else{
						U val;
						mj::copyvalue(val, mData.at(i).at(j));
						__Result(i, j) = val;
					}
				}
			}
			return __Result;
		}

		template<class U, class CMP = std::equal_to<T>>
		MTLSheet<U> ToOtherType(T excepty, U defaultvalue) const{
			return const_cast<MTLSheet*>(this)->ToOtherType<U, CMP>(excepty, defaultvalue);
		}


		//
		// ����ת��Ϊboost���㷨����
		//
		template<class L, class A,
			template<class U1, class L1, class A1> class M>
		M<T, L, A>& toMatrix(M<T, L, A>& result){
			result.clear();
			int rowcount = this->RowCounts();
			int columcount = this->ColumCounts();
			result.resize(rowcount, columcount);
			for (int i = 0; i < rowcount; ++i){
				for (int j = 0; j < columcount; ++j){
					result(i, j) = mData.at(i).at(j);
				}
			}
			return result;
		}

		template<class L, class A,
			template<class U1, class L1, class A1> class M>
		M<T, L, A>& toMatrix(M<T, L, A>& result) const{
			return const_cast<MTLSheet*>(this)->toUblasM(result);
		}


		template<class U, class L, class A,
			template<class U1, class L1, class A1> class M>
		M<U, L, A>& toMatrix(M<U, L, A>& result){
			result.clear();
			int rowcount = this->RowCounts();
			int columcount = this->ColumCounts();
			result.resize(rowcount, columcount);
			for (int i = 0; i < rowcount; ++i){
				for (int j = 0; j < columcount; ++j){
					try{
						mj::copyvalue(result(i, j), mData.at(i).at(j));
					}
					catch (std::runtime_error e){
						result(i, j) = U();
					}
				}
			}
			return result;
		}


		template<class U, class L, class A,
			template<class U1, class L1, class A1> class M>
		M<U, L, A>& toMatrix(M<U, L, A>& result) const{
			return const_cast<MTLSheet*>(this)->toMatrix(result);
		}

		//
		// ����������
		//
		iterator begin(){
			return mData.begin();
		}

		const_iterator begin() const{
			return mData.begin();
		}

		iterator end(){
			return mData.end();
		}

		const_iterator end() const{
			return mData.end();
		}

		iterator last(){
			return mData.end() - 1;
		}

		const_iterator last() const{
			const_iterator __end = end();
			std::advance(__end, -1);
			return __end;
		}

		//
		// ����
		//
		void insertRow(int beforerow){
			int colSize = 0;
			if (mData.empty()){
				colSize = mHoldCols.size();
			}
			else{
				colSize = mData.back().size();
			}
			value_type v;
			v.resize(colSize);
			if (beforerow >= mData.size() || beforerow < 0){
				mData.push_back(v);
			}
			else{
				mData.insert(mData.begin() + colSize, v);
			}
		}

		//
		// ɾ������
		//
		void erase(int row){
			mData.erase(mData.begin() + row);
		}

		void erase(iterator iter){
			mData.erase(iter);
		}

		//
		// ��ȡӵ�и���ֵ�ļ���
		//
		template<class CMP = std::equal_to<T>>
		MTLSheet find(int col, const T& value){
			MTLSheet __Result;
			for (auto& v : mData){
				T& __v = v.at(col);
				if (CMP()(__v, value))
					__Result.push_back(v);
			}
			return __Result;
		}

		//
		// �����Ƿ�ӵ�и���ֵ
		//
		template<class CMP = std::equal_to<T>>
		std::pair<int, int> find_first(const T& value)
		{
			std::pair<int, int> result = std::make_pair(-1, -1);
			int row = 0;
			for (auto& v : mData){
				auto it = std::find_if(v.begin(), v.end(), std::bind2nd(CMP(), value));
				if (it != v.end()){
					int dis = std::distance(v.begin(), it);
					return std::make_pair(row, dis);
				}
				++row;
			}
			return result;
		}

		//
		// ��һ�к����һ��
		//
		value_type& front(){
			return mData.front();
		}

		value_type& front() const{
			return mData.front();
		}

		value_type& back(){
			return mData.back();
		}

		value_type& back() const{
			return mData.back();
		}

		void pop_front(){
			mData.erase(mData.begin());
		}

		void pop_back(){
			mData.pop_back();
		}

		//
		// ����ĳ�н�������
		//
		template<class CMP = std::less<MString>>
		void sort(unsigned col, CMP __cmp = CMP()){
			std::sort(mData.begin(), mData.end(),
				[&](value_type v1, value_type v2){
				MString val1 = v1[col];
				MString val2 = v2[col];
				return __cmp(val1, val2);
			});
		}

		//
		// ת�ã��б���
		//
		MTLSheet transpose_copy(){
			MTLSheet result;
			if (mData.empty()){
				return result;
			}
			//
			//���������������������Ƿ����
			//
			size_t count = mData.begin()->size();
			for (auto& it : mData){
				if (count != it.size()){
					return result;
				}
			}
			for (int i = 0; i < count; ++i){
				result.push_back(Colum(i));
			}
			return result;
		}

		MTLSheet& transpose(){
			MTLSheet result = transpose_copy();
			mData = result.mData;
			return *this;
		}

		//
		// ����ʹ��һ���������Ա���б任
		//
		template<class F>
		MTLSheet& transform(F fun = F()){
			int row = this->RowCounts();
			int col = this->ColumCounts();
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					(*this)(i, j) = fun(this->at(i, j));
				}
			}
			return *this;
		}

		template<class F>
		MTLSheet transform_copy(F fun = F()){
			int row = this->RowCounts();
			int col = this->ColumCounts();
			MTLSheet __Result;
			__Result.resize(row, col);
			for (int i = 0; i < row; ++i){
				for (int j = 0; j < col; ++j){
					__Result(i, j) = fun(this->at(i, j));
				}
			}
			return __Result;
		}

		void print(const char* msg = "", std::ostream& os = std::cout){
			os << msg << std::endl;
			os << *this;
			os << std::endl;
		}


		//
		// �����е��н�����ת
		//
		MTLSheet reverse_copy(){
			MTLSheet result;
			if (mData.empty()){
				return result;
			}
			for (auto& it : mData){
				std::vector<T> v(it);
				std::reverse(v.begin(), v.end());
				result.push_back(v);
			}
			return result;
		}

		MTLSheet& reverse(bool iscol = true){
			if (iscol){
				for (auto& it : mData){
					std::reverse(it.begin(), it.end());
				}
			}
			else{
				std::reverse(mData.begin(), mData.end());
			}
			return *this;
		}

		//
		// ӳ��һ������ֵ����
		//
		MTLSheet map(unsigned startrow, unsigned startcol, unsigned lastrow, unsigned lastcol){
			int row = RowCounts();
			int col = ColumCounts();

			assert(startrow < lastrow);
			assert(startcol < lastcol);

			assert(lastrow <= row);
			assert(lastcol <= col);

			MTLSheet sheet;

			for (int i = startrow; i < lastrow; ++i){
				value_type v = Row(i);
				value_type temp;
				std::copy(v.begin() + startcol, v.begin() + lastcol, std::back_inserter(temp));
				sheet.push_back(temp);
			}
			return sheet;
		}

		MTLSheet map(unsigned startrow, unsigned startcol, unsigned lastrow, unsigned lastcol) const{
			return const_cast<MTLSheet*>(this)->map(startrow, startcol, lastrow, lastcol);
		}

		//
		// ͨ��һ������Ծ�������޸�
		// start_row ��Ҫ�޸ĵĿ�ʼrow
		// start_colum ��Ҫ�޸ĵĿ�ʼcolum
		// m �滻������
		//
		void replacePart(unsigned start_row, unsigned start_colum, MTLSheet& m){
			if (empty()){
				*this = m;
				return;
			}
			if (start_row >= mData.size() || (m.RowCounts() + start_row) >= mData.size() ||
				start_colum >= ColumCounts() || (m.ColumCounts() + start_colum) >= ColumCounts())
			{
				throw std::runtime_error("row or colum index beyong range .... ");
			}

			int row = 0, colum = 0;
			for (int i = start_row; i < (start_row + m.ColumCounts()); ++i){
				colum = 0;
				for (int j = start_colum; j < (start_colum + m.ColumCounts()); ++j){
					mData[i][j] = m(row, colum);
					++colum;
				}
				++row;
			}
		}

		//
		// ������ת
		// ֻ�ܰ���90 180 270 360 ������Ƕ���ת
		//
		MTLSheet rotation_copy(Angle angle = __None){
			MTLSheet __result;
			if (mData.empty()){
				return __result;
			}

			//
			// ���������������������Ƿ����
			//
			size_t colum = ColumCounts();
			size_t row = mData.size();
			std::cout << "colum = " << colum << "\trow = " << row << std::endl;
			for (auto& it : mData){
				if (colum != it.size()){
					throw std::runtime_error("matrix isn't standar matrix and couldn't rotation");
				}
			}

			//
			// ��������ת����
			//
			switch (angle){
			case __1Div2Pi:
				while (colum--){
					auto __data = Colum(colum);
					__result.push_back(__data);
				}
				break;

			case __2Div2Pi:
				while (row--){
					auto __data = Row(row);
					std::reverse(__data.begin(), __data.end());
					__result.push_back(__data);
				}
				break;

			case __3Div2Pi:
				for (int i = 0; i < colum; ++i){
					auto __data = Colum(i);
					std::reverse(__data.begin(), __data.end());
					__result.push_back(__data);
				}
				break;

			case __4Div2Pi:
				return *this;
				break;

			case __N1Div2Pi:
				for (int i = 0; i < colum; ++i){
					auto __data = Colum(i);
					std::reverse(__data.begin(), __data.end());
					__result.push_back(__data);
				}
				break;

			case __N2Div2Pi:
				while (row--){
					auto __data = Row(row);
					std::reverse(__data.begin(), __data.end());
					__result.push_back(__data);
				}
				break;

			case __N3Div2Pi:
				while (colum--){
					auto __data = Colum(colum);
					__result.push_back(__data);
				}
				break;

			case __N4Div2Pi:
				return *this;
				break;

			case __None:
				return *this;
				break;
			}
			return __result;
		}

		MTLSheet& rotation(Angle angle = __None){
			*this = rotation_copy(angle);
			return *this;
		}

		//
		// ��д�ı��ļ�
		//
		void WriteToFile(const MString& fileName){
			if (mData.empty())
				return;
			std::ofstream outFile(fileName.toStdString());
			if (outFile.fail())
				return;
			WriteToStream(outFile);
			outFile.close();
		}

		bool ReadFromFile(const MString& fileName){
			clear();
			std::ifstream inFile(fileName.toStdString());
			if (inFile.fail())
				return false;
			ReadFromStream(inFile);
			inFile.close();
			return true;
		}

		//
		// ��д�������ļ�,����ֵΪд���ļ��Ĵ�С
		//
		__int64 WriteBinaryToFile(const MString& fileName){
			if (mData.empty())
				return 0ll;
			std::ofstream outFile(fileName.toStdString(), std::ios::app | std::ios::binary);
			if (outFile.fail())
				return 0ll;
			int row = mData.size();
			int col = mData.back().size();
			__int64 len = 0ll;
			outFile.write((char*)(&row), sizeof(row));
			outFile.write((char*)(&col), sizeof(col));
			len += sizeof(row);
			len += sizeof(col);
			for (const value_type& s : mData){
				__int64 __len = sizeof(T)*s.size();
				outFile.write((char*)(&s[0]), __len);
				len += __len;
			}
			outFile.close();
			return len;
		}

		__int64 WriteBinaryToFile(const MString& fileName) const{
			return const_cast<MTLSheet*>(this)->WriteBinaryToFile(fileName);
		}

		//
		// ��ȡ�������ļ����������ļ���������ƫ����
		//
		bool ReadBinaryFile(const MString& fileName, __int64 offset = 0ll){
			clear();
			std::ifstream inFile(fileName.toStdString(), std::ios::in | std::ios::binary);
			if (inFile.fail()){
				return false;
			}
			inFile.seekg(offset, std::ios::beg);
			int row = 0, col = 0;
			inFile.read((char*)(&row), sizeof(row));
			inFile.read((char*)(&col), sizeof(row));
			__int64 lenth = row*col*sizeof(T);
			char* ch = new char[lenth];
			memset(ch, 0, lenth);
			inFile.read(ch, lenth);
			inFile.close();
			__int64 collen = col*sizeof(T);
			for (int i = 0; i < row; ++i){
				value_type s((T*)(&ch[i*collen]), (T*)(&ch[i*collen + collen]));
				push_back(s);
			}
			delete[] ch;
			return true;
		}

		//
		// ���ļ�д����������֮���ɷָ�������
		//
		void WriteToStream(std::ostream& os, const MString& spliter = " "){
			if (mData.empty())
				return;
			int row = mData.size();
			int col = mData.back().size();
			os << row << "\t" << col << std::endl;
			for (const value_type& s : mData){
				MString str = JoinToMstring(s, spliter);
				os << str << std::endl;
			}
		}

		//
		// �����ж�ȡ����
		//
		void ReadFromStream(std::istream &is, const MString& spliter){
			clear();
			if (is.eof())
				return;
			int row, col;
			is >> row >> col;
			if (is.eof())
				return;
			while (!is.eof()){
				MString str;
				is >> str;
				value_type vstr;
				str.split(spliter, vstr);
				if (vstr.size() == col){
					push_back(vstr);
					if (this->RowCounts() >= row)
						break;
				}
			}
		}

		//
		// �����ж�ȡ���ݣ���ʱ����֮��ļ���ǿո�
		//
		void ReadFromStream(std::istream& is){
			clear();
			if (is.eof())
				return;
			int row, col;
			is >> row >> col;
			if (is.eof())
				return;
			for (int i = 0; i < row; ++i){
				value_type v;
				for (int j = 0; j < col; ++j){
					if (!is.eof()){
						T t;
						is >> t;
						v.push_back(t);
					}
				}
				push_back(v);
			}
		}

		//
		// ��д����
		//
		friend std::ostream& operator<<(std::ostream& os, const MTLSheet& sheet){
			if (sheet.empty())
				return os;
			int row = sheet.mData.size();
			int col = sheet.mData.back().size();
			os << row << "  " << col << std::endl;
			for (const value_type& s : sheet.mData){
				os << "(";
				MString str = JoinToMstring(s, ",");
				os << str;
				os << ")" << std::endl;
			}
			return os;
		}


		friend std::istream& operator>>(std::istream& is, MTLSheet& sheet){
			sheet.clear();
			int row, col;
			is >> row >> col;

			for (int i = 0; i < row; ++i){
				value_type v;
				for (int j = 0; j < col; ++j){
					T t;
					is >> t;
					v.push_back(t);
				}
				sheet.push_back(v);
			}
			return is;
		}

		//
		// �ж����ű��Ƿ����
		//
		friend bool operator==(const MTLSheet& one,const MTLSheet&two)
		{
			return one.mData == two.mData;
		}

		//
		// �������������ʱ�򷽲�ʹ�øñȽϺ���,���������operator==��Ч�ʸߵö�
		//
		template<class CMP = std::equal_to<MString>>
		bool equal(const MTLSheet& other, CMP __cmp = CMP()){
			if (this->empty() && other.empty())
				return true;

			if (this->RowCounts() != other.RowCounts()){
				return false;
			}
			if (this->ColumCounts() != other.RowCounts()){
				return false;
			}

			for (int i = 0; i < this->RowCounts(); ++i){
				for (int j = 0; j < this->ColumCounts(); ++j){
					MString val1 = this->at(i, j);
					MString val2 = other.at(i, j);
					if (!__cmp(val1, val2)){
						return false;
					}
				}
			}
			return true;
		}

		//
		// ʵ�����ű�����ݽ���
		//
		void swap(MTLSheet& other){
			mData.swap(other);
		}

	private:

		//
		// push���ݵ�ʱ��������Ҫ����������һ��
		//
		void push_value(value_type& v){
			if (!mData.empty()){
				v.resize(mData.back().size());
			}
			else{
				if (!mHoldCols.empty()){
					v.resize(mHoldCols.size());
				}
			}
			mData.push_back(v);
		}

		void push_value(value_type& l, int col){
			mData.clear();
			int i = 0;
			value_type v;
			for (auto& val : l){
				if (i < col){
					v.push_back(val);
					++i;
				}

				if (i == col){
					mData.push_back(v);
					v.clear();
					i = 0;
				}
			}
		}

		data_module     mData;
		value_type      mHoldCols; // ����holder����
	};


	//
	// ����������ݸ�ʽ�ṩ��һЩ��д�ļ����㷨
	//

	template<class T, class L, class A, template<class T1, class L1, class A1> class M>
	inline __int64 WriteMatrixToFileBinary(const M<T, L, A>& m, const MString& FileName){
		std::ofstream outFile(FileName.toStdString(), std::ios::app | std::ios::binary);
		if (outFile.fail())
			return 0ll;
		int row = m.size1();
		int col = m.size2();
		__int64 len = 0ll;
		outFile.write((char*)(&row), sizeof(row));
		outFile.write((char*)(&col), sizeof(col));
		len += sizeof(row);
		len += sizeof(col);
		auto beg1 = m.begin1();
		auto end1 = m.end1();
		for (; beg1 != end1; ++beg1){
			__int64 __len = sizeof(T)*col;
			outFile.write((char*)(&beg1[0]), __len);
			len += __len;
		}
		outFile.close();
		return len;
	}

	template<class T, class L, class A, template<class T1, class L1, class A1> class M>
	inline bool ReadMatrixToFileBinary(M<T, L, A>& m, const MString& FileName, __int64 offset = 0ll){
		m.clear();
		std::ifstream inFile(FileName.toStdString(), std::ios::in | std::ios::binary);
		if (inFile.fail()){
			return false;
		}
		inFile.seekg(offset, std::ios::beg);
		int row = 0, col = 0;
		inFile.read((char*)(&row), sizeof(row));
		inFile.read((char*)(&col), sizeof(row));
		__int64 lenth = row*col*sizeof(T);
		char* ch = new char[lenth];
		memset(ch, 0, lenth);
		inFile.read(ch, lenth);
		inFile.close();
		m.resize(row, col);
		__int64 collen = col*sizeof(T);

		for (int i = 0; i < row; ++i){
			for (int j = 0; j < col; ++j){
				m(i, j) = *(T*)(&ch[i*collen + j*sizeof(T)]);
			}
		}
		return true;
	}


	//
	// ��������ͬ�任
	//
	template<class T, class Prd>
	inline MTLSheet<T> OperatorMSheet(const MTLSheet<T>& m1, const MTLSheet<T>& m2, Prd __prd = Prd()){
		MTLSheet<T> __Result;
		if (m1.RowCounts() != m2.RowCounts())
			return __Result;

		if (m1.ColumCounts() != m2.ColumCounts())
			return __Result;

		int row = m1.RowCounts(), col = m1.ColumCounts();

		__Result.resize(row, col);


#pragma omp parallel for
		for (int i = 0; i < row; ++i){
#pragma omp parallel for num_threads(8)
			for (int j = 0; j < col; ++j){
				__Result(i, j) = __prd(m1(i, j), m2(i, j));
			}
		}
		return __Result;
	}
}
