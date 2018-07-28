#pragma once
#include "MXml.h"

namespace DxUI{

	class MSTRING_API MSerialize
	{
	public:
		MSerialize();
		~MSerialize();

		//
		// �Զ��ķ�ʽ���ļ�
		//
		void ReadFile(const MString &filename);

		//
		// Ϊд�����ļ�
		//
		void WriteFile(const MString &filename);

		//
		// �ر��ļ���������һ���ļ�ʱ�ǵùرյ�ǰ�ļ�
		// ����д�ļ���������Щ���֮��ǵùر��ļ�
		// ��������ֻ�����ڴ�֮��
		// ��Ȼ�ڳ����˳�֮ʱҹ����øò���
		//
		void CloseFile();

		///
		/// \brief SaveFile
		/// ���ڶ�ȡ���ļ������޸ĵ����
		///
		void SaveFile();

		bool IsReadFile() const;

		virtual MString ToString() { return "MSerialize"; }


		//
		// ������д���ļ�
		// key xml �ļ���key���ڵ�֮����.�ָ�
		// value Ҫд��ֵ
		//
		template<class T>
		bool PutValue(const MString& key, const T& value){
			try{
				mXmlManager->PutValue(key, value);
				return true;
			}
			catch (...){
				return false;
			}
		}


		//
		// ������д���ļ�
		// key xml �ļ���key���ڵ�֮����.�ָ�
		// values ��child����ʽд��ȥ
		// ֻ��xml�ļ��ܹ�ʹ�øò���
		//
		template<class T>
		bool PutValues(const MString& key, const std::vector<T>& values){
			try{
				std::vector<mj::MAny> __Anys;
				for (auto s : values){
					__Anys.push_back(s);
				}
				mXmlManager->PutValue(key, __Anys);
				return true;
			}
			catch (...){
				return false;
			}
		}

		//
		// ���ļ���Ϣ
		// �������д�ļ�һ��
		// ��ôд��ȥ�ľ���ô����������
		//
		template<class T>
		T GetValue(const MString& key, const T& defaultvalue){
			try{
				mj::MAny __Any = mXmlManager->GetValue(key, defaultvalue);
				return mj::any_cast<T>(__Any);
			}
			catch (...){
				return defaultvalue;
			}
		}

		//
		// ��PutValues��Ӧ
		// ��ȡ��������Ҫһ��ĬȻ�ķ���ֵ
		// ��û��ȡ�ø�ֵ��ʱ��ʹ��Ĭ��ֵ����
		// ����Ĭ��ֵ���ܹ��ܺõı�ʶ������
		//
		template<class T>
		std::vector<T> GetValues(const MString& key, const T& defaultvalue){
			std::vector<T> __Result;
			try{
				std::vector<mj::MAny> __Anys = mXmlManager->GetValues(key, defaultvalue);
				for (auto __s : __Anys){
					__Result.push_back(mj::any_cast<T>(__s));
				}
			}
			catch (...){
				__Result.push_back(defaultvalue);
			}
			return __Result;
		}


		MString GetParentPath();
		void CreateFolder(const MString& path);
		bool XmlFileIsExist(const MString& fileName);

	private:
		MXml*    mXmlManager;
		MString  mXmlFile;
		bool    bIsRead;
	};
}

