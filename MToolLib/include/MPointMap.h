#pragma once

#include <vector>
#include <MMatrixSheet.h>
#include <MTypeWrap.h>
#include <HMath.h>
#include <HContainer.h>
#include <MToolLib>
#include <MTypeTool.h>

namespace mj{
	//
	// Ԥ����һ������Ϣ
	//
#ifndef MPoint2DType
	struct MPoint2DType{
		double mX;
		double mY;
		unsigned mId;

		friend std::ostream& operator<<(std::ostream& os, const MPoint2DType& p){
			os << p.mId << "\t" << p.mX << "," << p.mY << std::endl;
			return os;
		}
	};
#endif

	//
	// Ԥ����һ�����б�
	//
#ifndef MPoint2DList
	typedef std::vector<MPoint2DType> MPoint2DList;
#endif

	//
	// ʵ��ӳ��
	//
	template<class PointType = MPoint2DType>
	class MPointMap{
	public:
		//
		// ��Ԫ����
		//
		typedef PointType unit_point_type;

		//
		// ̽ͷ������λ�õ�ӳ��
		//
		typedef std::pair<unsigned, unsigned> prober_to_index_type;

		//
		// ·�����ͣ���ʼ�У���ʼ̽ͷ----��Ӧ����
		//
	//	typedef std::vector<std::pair<unsigned, std::vector<prober_to_index_type>>> path_type;

		//
		// ��ǰɨ��Ŀ�ʼ����,��һ��̽ͷ��λ��,��ǰλ��ɨ���ϵ�е�
		//
		typedef mj::HContainer<unsigned, PointType, std::vector<prober_to_index_type>> path_type;
		

		//
		// ��̽ͷӳ����
		//
		typedef MMatrixSheet<PointType, std::vector<unsigned>> result_type;

		//
		// ��̽ͷӳ����
		//
		typedef MMatrixSheet<std::pair<unsigned, PointType>, std::vector<unsigned>> mult_probe_result_type;

		//
		// ���캯��
		//
		MPointMap(const std::vector<PointType>& points = std::vector<PointType>());
		MPointMap(const MPointMap& other);
		MPointMap(MPointMap&& other);

		MPointMap& operator=(const MPointMap& other);
		MPointMap& operator=(MPointMap&& other);

		//
		// ����ӳ����Ϣ
		//
		void setMapInformation(double distance, double angle);

		//
		// ����ԭʼ����
		//
		void setOrgPoints(const std::vector<PointType>& points);

		//
		// ���ļ��м���
		//
		void loadOrgPointFromFile(const mj::MString& filename);

		//
		// ӳ����
		//
		result_type map();

		//
		// ������̽ͷ
		// ̽ͷ��Ŵ�������
		// ɨ��·�����������ƶ�
		//
		mult_probe_result_type map(double step, unsigned num);

		//
		// ��Ե�ӳ��·��,���ڽ�����̽ͷɨ��ʱ��·���滮
		//
		mult_probe_result_type p2p_map(double step, unsigned num);

		//
		// �ڶ�̽ͷɨ���������Ҫ��·�����й滮
		//
		const path_type&  scan_path() const;

		///
		/// \brief get_subnum
		/// \return
		/// ��ȡ̽ͷ֮��Ĳ�������
		///
		int get_subnum() const;


        int get_pointsnum() const{
               return mOrgPoints.size();
        }


		//
		// ��ѯλ��
		//
		bool query_point(unsigned id, PointType& outpint);

		//
		// ��ӡ������Ϣ
		//
		void print(const char* msg, std::ostream& os = std::cout);


		//
		// ��ȡ���м��صĵ�
		//
		MTypeWrap<std::vector<PointType>> get_points() const{
			return mOrgPoints;
		}
	private:
		MTypeWrap<std::vector<PointType>>  mOrgPoints;
		double				   mDistance{ 0 };
		double				   mAngle{ 0 };
		path_type              mMultPath;
		int                    mSubNum{ 1 };

	private:
		bool point_in_rect(const PointType& center, double radius, const PointType& p);
	};










	//
	// ------------------------------------------------------------------
	// 
	template<class PointType>
	MPointMap<PointType>::MPointMap(const std::vector<PointType>& points){
		mOrgPoints = points;
	}

	template<class PointType>
	MPointMap<PointType>::MPointMap(const MPointMap& other){
		mOrgPoints = other.mOrgPoints;
		mDistance = other.mDistance;
		mAngle = other.mAngle;
	}

	template<class PointType>
	MPointMap<PointType>::MPointMap(MPointMap&& other){
		mOrgPoints = other.mOrgPoints;
		mDistance = other.mDistance;
		mAngle = other.mAngle;
		other.mOrgPoints.clear();
	}

	template<class PointType>
	MPointMap<PointType>& MPointMap<PointType>::operator=(const MPointMap& other){
		mOrgPoints = other.mOrgPoints;
		mDistance = other.mDistance;
		mAngle = other.mAngle;
		return *this;
	}


	template<class PointType>
	MPointMap<PointType>& MPointMap<PointType>::operator=(MPointMap&& other){
		mOrgPoints = other.mOrgPoints;
		mDistance = other.mDistance;
		mAngle = other.mAngle;
		other.mOrgPoints.clear();
		return *this;
	}

	template<class PointType>
	bool MPointMap<PointType>::point_in_rect(const PointType& center, double radius, const PointType& p){
		double leftx = center.mX - radius;
		double rightx = center.mX + radius;
		double topY = center.mY + radius;
		double bottomY = center.mY - radius;

		if (p.mX >= leftx && p.mX <= rightx && p.mY >= bottomY && p.mY <= topY){
			return true;
		}
		else{
			return false;
		}
	}

	//
	// ����ӳ����Ϣ
	//
	template<class PointType>
	void MPointMap<PointType>::setMapInformation(double distance, double angle){
		mDistance = distance;
		mAngle = angle;
	}

	//
	// ����ԭʼ����
	//
	template<class PointType>
	void MPointMap<PointType>::setOrgPoints(const std::vector<PointType>& points){
		mOrgPoints = points;
	}

	//
	// ���ļ��м���
	//
	template<class PointType>
	void MPointMap<PointType>::loadOrgPointFromFile(const mj::MString& filename){
		std::ifstream inFile(filename.toStdString());
		MString header;
		while (!header.istart_with("Counts:") && !inFile.eof()){
			inFile >> header;
		}
		if (inFile.eof()){
			return;
		}
		int count;
		header.reg_find(mj::REGFORFLOAT, count);

		std::vector<PointType> mIDs;
		mIDs.resize(count);
		while (!header.icontains("ID") && !inFile.eof()){
			inFile >> header;
		}

		if (inFile.eof()){
			return;
		}

		while (!header.icontains("Begin:") && !inFile.eof()){
			inFile >> header;
		}

		if (inFile.eof()){
			return;
		}

		MString mstr;
		for (int i = 0; i < count; ++i){
			if (inFile.eof()){
				break;
			}
			inFile >> mstr;
			if (mstr.empty()){
				std::cout << "data is empty" << std::endl;
				continue;
			}

			std::vector<MString> vstr;
			mstr.split("\t ", vstr);
			if (vstr.size() < 3){
				continue;
			}

			mIDs[i].mId = vstr[0].ToOtherType<int>();
			mIDs[i].mX = vstr[1].ToOtherType<double>();
			mIDs[i].mY = vstr[2].ToOtherType<double>();
		}

		inFile.close();

		mOrgPoints = mIDs;
	}

	//
	// ӳ����
	//
	template<class PointType>
	typename MPointMap<PointType>::result_type MPointMap<PointType>::map(){
		result_type  result;
		mMultPath.clear();

		if (std::abs(mDistance) < 1e-5)
			return result;

		double h = 2 * mDistance*std::tan(mAngle / 180.0 * mj::PI);

		/*
		*  s = h
		*/

		PointType x_max_point = mOrgPoints.max_element([](PointType p1, PointType p2){return p1.mX < p2.mX; });
		PointType x_min_point = mOrgPoints.min_element([](PointType p1, PointType p2){return p1.mX < p2.mX; });

		PointType y_max_point = mOrgPoints.max_element([](PointType p1, PointType p2){return p1.mY < p2.mY; });
		PointType y_min_point = mOrgPoints.min_element([](PointType p1, PointType p2){return p1.mY < p2.mY; });

		double disx = x_max_point.mX - x_min_point.mX;
		double disy = y_max_point.mY - y_min_point.mY;
		


		if (std::abs(mAngle) < 1e-1){
			//
			// ��̽ͷ 0�� ���⴦��
			//
			MTypeWrap<std::vector<PointType>> temppoints = mOrgPoints;
			temppoints.unique([](PointType p1, PointType p2){return p1.mX == p2.mX; }, [](PointType p1, PointType p2){return p1.mX < p2.mX; });
			MTypeWrap<std::vector<double>> spanvecx, spanvecy;

			for (auto& p : temppoints){
				PointType __p1 = p;
				spanvecx.push_back(__p1.mX);
			}
			spanvecx.unique();

			temppoints = mOrgPoints;
			temppoints.unique([](PointType p1, PointType p2){return p1.mY == p2.mY; }, [](PointType p1, PointType p2){return p1.mY < p2.mY; });
			for (auto& p : temppoints){
				PointType __p1 = p;
				spanvecy.push_back(__p1.mY);
			}
			spanvecy.unique();

			int ynum = spanvecy.size();
			int xnum = spanvecx.size();
			result.resize(ynum, xnum);
			unsigned index = 1;

			for (unsigned i = 0; i < ynum; ++i){
				PointType p;
				for (unsigned j = 0; j < xnum; ++j){
					p.mX = spanvecx.at(j);
					p.mY = spanvecy.at(i);
					p.mId = index;
					++index;
					std::vector<unsigned> ids;
					for (auto& p1 : mOrgPoints){
						PointType __p1 = p1;
						if (std::abs(__p1.mX - p.mX) < 1e-2 && std::abs(__p1.mY - p.mY) < 1e-2){
							ids.push_back(__p1.mId);
							p = p1;
							break;
						}
					}
					result(i, j) = p;
					result.set_property(i, j, ids);

				} // for (int j = 0; j < xnum; ++j)
				mMultPath.push_back(i, p, std::vector<prober_to_index_type>({ std::make_pair(0, i) }));

			} // for (int i = 0; i < ynum; ++i)
		}
		else{
			int xnum = disx / h + 1;
			int ynum = disy / h + 1;

			disx = xnum * h;
			disy = ynum * h;

			result.resize(ynum, xnum);
			unsigned index = 1;
			for (unsigned i = 0; i < ynum; ++i){
				PointType p;
				for (unsigned j = 0; j < xnum; ++j){
					p.mX = x_min_point.mX + j*h + 0.5*h;
					p.mY = y_min_point.mY + i*h + 0.5*h;
					p.mId = index;
					result(i, j) = p;
					++index;
					std::vector<unsigned> ids;
					for (auto& p1 : mOrgPoints){
						if (point_in_rect(p, 0.5*h, p1)){
							PointType __p1 = p1;
							ids.push_back(__p1.mId);
						}
					}
					result.set_property(i, j, ids);

				} // for (int j = 0; j < xnum; ++j)
				mMultPath.push_back(i, p, std::vector<prober_to_index_type>({ std::make_pair(0, i) }));
			} // for (int i = 0; i < ynum; ++i)
		}
		return result;
	}

	//
	// ��̽ͷ������Ϣ��ӳ��
	//
	template<class PointType>
	typename MPointMap<PointType>::mult_probe_result_type MPointMap<PointType>::map(double step, unsigned num){
		mult_probe_result_type result;
		mMultPath.clear();
		if (mOrgPoints.empty()){
			return result;
		}

		if (std::abs(mDistance) < 1e-5 && num > 1)
			return result;

		//
		// ���ڶ�̽ͷ����û�����üн���ô̽ͷ֮���໥����
		//
		if (std::abs(mAngle) < 1e-2 && num > 1){
			mAngle = std::atan(step*0.5 / mDistance) * 180 / mj::PI;
		}
		if (num <= 1){
			result_type __tempresult = map();
			result.resize(__tempresult.rows(), __tempresult.cols());
			for (int i = 0; i < __tempresult.rows(); ++i){
				for (int j = 0; j < __tempresult.cols(); ++j){
					result(i, j) = std::make_pair(0, __tempresult(i, j));
					result.set_property(i, j, __tempresult.get_property(i, j));
				}
			}
			return result;
		}


		//
		// ͨ�������нǺ;����������α߳�
		//
		double h = 2 * mDistance*std::tan(mAngle / 180.0 * mj::PI);

		/*
		*  s = h
		*/

		PointType x_max_point = mOrgPoints.max_element([](PointType p1, PointType p2){return p1.mX < p2.mX; });
		PointType x_min_point = mOrgPoints.min_element([](PointType p1, PointType p2){return p1.mX < p2.mX; });

		PointType y_max_point = mOrgPoints.max_element([](PointType p1, PointType p2){return p1.mY < p2.mY; });
		PointType y_min_point = mOrgPoints.min_element([](PointType p1, PointType p2){return p1.mY < p2.mY; });

		double disx = x_max_point.mX - x_min_point.mX;
		double disy = y_max_point.mY - y_min_point.mY;

		int xnum = disx / h + 1;
		int ynum = disy / step + 1;
		int subnum = step / h + 1;

		if (std::abs(h - step) < 1e-5){
			subnum -= 1;
		}
		mSubNum = subnum;

		/*
		* ע�����ͨӳ�������
		*/
		disy = ynum * step;
		ynum *= subnum;
		disx = xnum * h;


		result.resize(ynum, xnum);

		result_type __tempresult;
		__tempresult.resize(ynum, xnum);

		unsigned index = 1;

		MTypeWrap<std::vector<PointType>> temporgpoint = mOrgPoints;

		//
		// ��¼
		//
		int startrow = 0;
		int  probeindex = 0;
		int loopnum = 0;
		int moveindex = 0;
		while (startrow < ynum){

			//
			// ��ʼ��
			//
			
			int rowindex = startrow;
			int recodeindex = 0;
			

			//
			// ѭ�����
			//
			while (true)
			{
				int probe = probeindex;
				if (recodeindex >= subnum)
				{
					startrow += (num - probeindex)*subnum;
					break;
				}

				
				//
				// ��ǰ��
				//
				std::vector<prober_to_index_type> probeindexs;
				int m = rowindex % subnum;

				//
				// �滮ɨ��·��
				//
				for (; probe < num; ++probe)
				{
	
					//
					// ��ǰ��
					//
					int row = rowindex + subnum*(probe - probeindex) + recodeindex;
					

					//
					// ��鵱ǰ�Ƿ����
					//
					if (row >= ynum){
						startrow = row;
						break;
					}

					
					probeindexs.push_back(std::make_pair(probe, row));

					for (int j = 0; j < xnum; ++j){
						PointType p;
						p.mX = x_min_point.mX +  j*h + 0.5*h;
						p.mY = y_min_point.mY + loopnum*num*step + (probe - probeindex)*step + m*h + 0.5*h + recodeindex*h;
						p.mId = index;
						result(row, j) = std::make_pair(probe, p);
						++index;
						std::vector<unsigned> ids;
						for (int k = 0; k < temporgpoint.size();){
							PointType p1 = temporgpoint[k];
							if (point_in_rect(p, 0.5*h, p1)){
								ids.push_back(p1.mId);
								temporgpoint.erase(temporgpoint.begin() + k);
							}
							else{
								++k;
							}
						}
						result.set_property(row, j, ids);
					}	
					
				} // end for

				//
				// ��¼��̽ͷɨ��·��
				//
				{
					PointType p;
					p.mY = y_min_point.mY + loopnum*num*step + m*h + 0.5*h - probeindex*step;
					mMultPath.push_back(moveindex++, p, probeindexs);
				}
				++recodeindex;
			} // end while true
			

			if (startrow >= ynum){
				break;
			}
			else{
				int rnum = ynum - startrow;
				int k = rnum / subnum;
				if (k < num){
					probeindex = num - k;
				}
			}
			++loopnum; 
			

		}// end while(startrow < ynum)
		return result;
	}


	template<class PointType>
	typename MPointMap<PointType>::mult_probe_result_type MPointMap<PointType>::p2p_map(double step, unsigned num){
		mult_probe_result_type result;
		mMultPath.clear();
		if (mOrgPoints.empty()){
			return result;
		}

		TL::Vector<double> xs, ys;

		for (auto& p : mOrgPoints){
			xs.push_back(p.ref().mX);
			ys.push_back(p.ref().mY);
		}
		
		xs.unique();
		ys.unique();

		double yStep = ys.min_span();

		double res = step / yStep;
		double d1 = 0;
		res = std::modf(res, &d1);
		if (std::abs(res) > 1e-5){
			throw std::runtime_error("Step Invalid");
		}

		/*
		*  s = h
		*/
		double disy = ys.max_element() - ys.min_element();
		double disx = xs.max_element() - xs.min_element();

		int xnum = xs.size();
		int ynum = disy / step;
		int iref = int(disy) % int(step);
		if (iref > 0){
			ynum += 1;
		}
		int subnum = step / yStep;

		if (subnum == 0){
			subnum = 1;
		}

		mSubNum = subnum;

		ynum = ys.size();

		result.resize(ynum, xnum);

		result_type __tempresult;
		__tempresult.resize(ynum, xnum);

		unsigned index = 1;

		MTypeWrap<std::vector<PointType>> temporgpoint = mOrgPoints;

		//
		// ��¼
		//
		int startrow = 0;
		int  probeindex = 0;
		int loopnum = 0;
		int moveindex = 0;
		TL::Vector<int>  NumLoops;

		NumLoops.push_back(num);
		while (startrow < ynum){

			//
			// ��ʼ��
			//

			int rowindex = startrow;
			int recodeindex = 0;


			//
			// ѭ�����
			//
			while (true)
			{
				int probe = probeindex;
				if (recodeindex >= subnum)
				{
					startrow += (num - probeindex)*subnum;
					break;
				}

				std::vector<prober_to_index_type> probeindexs;
				int m = rowindex % subnum;

				int StepNum = (NumLoops.sum_value() - NumLoops.back())*step;
		

				for (; probe < num; ++probe)
				{
					int row = rowindex + subnum*(probe - probeindex) + recodeindex;

					if (row >= ynum){
						startrow = row;
						break;
					}


					probeindexs.push_back(std::make_pair(probe, row));

					for (int j = 0; j < xs.size(); ++j){
						PointType p;
						p.mX = xs.unsafe_at(j);
						p.mY = ys.min_element() + StepNum + (probe - probeindex)*step + m*yStep + recodeindex*yStep;
						p.mId = index;
						result(row, j) = std::make_pair(probe, p);
						++index;
						std::vector<unsigned> ids;
						for (int k = 0; k < temporgpoint.size();){
							PointType p1 = temporgpoint[k];
							if (std::abs(p1.mX - p.mX) < 1e-5 && std::abs(p1.mY - p.mY) < 1e-5){
								ids.push_back(p1.mId);
								temporgpoint.erase(temporgpoint.begin() + k);
								break;
							}
							else{
								++k;
							}
						}
						result.set_property(row, j, ids);
					}

				} // end for

				if (probeindexs.empty()){
					startrow = ynum;
					break;
				}
				//
				// ��¼��̽ͷɨ��·��
				//
				{
					PointType p;
					p.mY = ys.min_element() + StepNum + recodeindex*yStep - probeindex*step;
					p.mX = 0.0;
					p.mId = probeindex;
					mMultPath.push_back(moveindex++, p, probeindexs);
				}
				++recodeindex;
			} // end while true


			if (startrow >= ynum){
				break;
			}
			else{
				int rnum = ynum - startrow;
				int k = rnum / subnum;
				if (k == 0){
					k = 1;
				}
				if (k < num){	
					probeindex = num - k;
				}
			}
			NumLoops.push_back(num - probeindex);
			++loopnum;

		}// end while(startrow < ynum)
		return result;
	}

	template<class PointType>
	const typename MPointMap<PointType>::path_type&  MPointMap<PointType>::scan_path() const{
		return mMultPath;
	}

	template<class PointType>
	int MPointMap<PointType>::get_subnum() const{
		return mSubNum;
	}

	template<class PointType>
	bool MPointMap<PointType>::query_point(unsigned id, PointType& outpint){
		PointType p;
		p.mId = id;
		int index = mOrgPoints.find_index(p, [](PointType p1, PointType p2){return p1.mId == p2.mId; });
		if (index != -1){
			outpint = mOrgPoints[index];
			return true;
		}
		return false;
	}

	template<class PointType>
	void MPointMap<PointType>::print(const char* msg, std::ostream& os){
		mOrgPoints.print(msg, os);
	}
}
