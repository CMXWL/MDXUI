#pragma once
#include <iostream>
#include <Windows.h>
#include <objbase.h>
#include <string>
#include <string>
#include <vector>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>
#include <boost/progress.hpp>
#include <boost/filesystem.hpp>
#include <unordered_map>
#include "MCodeCast.h"
#include "HHelp.h"
#include <filesystem>

namespace file{
	typedef boost::filesystem::path _Path;
	using namespace boost::xpressive;
	
	//-------------------------------------------------------
	//�ݹ����һ��Ŀ¼
	//-------------------------------------------------------
        static void recursive_dir(const _Path& dir){
		boost::filesystem::directory_iterator end;
		for (boost::filesystem::directory_iterator pos(dir); pos != end; ++pos){
			if (boost::filesystem::is_directory(*pos)){
				recursive_dir(*pos);
			}
			else{
				std::cout << *pos << std::endl;
			}
		}
	}

	//-----------------------------------------------------
	//��һ��Ŀ¼�������һ���ļ�
	//-----------------------------------------------------
	static boost::optional<_Path> find_file(const _Path& dir, const std::string& filename){
		typedef boost::optional<_Path> result_type;

        if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir)){
			return result_type();
		}

		typedef boost::filesystem::recursive_directory_iterator rd_iterator;

		rd_iterator end;
		for (rd_iterator pos(dir); pos != end; ++pos){
			if (!boost::filesystem::is_directory(*pos) &&
				pos->path().filename() == filename){
				return result_type(pos->path());
			}
		}
		return result_type();
	}


	//----------------------------------------------------------------------------------
	//��һ��Ŀ¼�������һ�����ļ�
	//----------------------------------------------------------------------------------
	static void find_files(const _Path& dir, const std::string& filename, std::vector<_Path>& v){
		static sregex_compiler rc;

		if (!rc[filename].regex_id()){
			std::string str = boost::algorithm::replace_all_copy(
				boost::algorithm::replace_all_copy(filename, ".", "\\."),
				"*", ".*");
			rc[filename] = rc.compile(str);
		}

		typedef std::vector<_Path> result_type;

		if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir)){
			return;
		}

		typedef boost::filesystem::recursive_directory_iterator rd_iterator;
		rd_iterator end;
		for (rd_iterator pos(dir); pos != end; ++pos){
			if (!boost::filesystem::is_directory(*pos) &&
				regex_match(pos->path().filename().string(), rc[filename]))
			{
				v.push_back(pos->path());
			}
		}
	}

	//----------------------------------------------------------------------
	//����һ��Ŀ¼��һ��Ŀ¼
	//----------------------------------------------------------------------
	static size_t copy_files(const std::string& from_dir, const std::string& to_dir,
			const std::string& filename = "*"){

		_Path p_from_dir(from_dir);
		_Path p_to_dir(to_dir);

		if (!boost::filesystem::is_directory(p_from_dir)){
			throw std::runtime_error("args is not a dir");
		}

		std::vector<_Path> v;

		find_files(p_from_dir, filename, v);

		if (v.empty()){
			return 0;
		}
		std::cerr << "now begin copy files..." << std::endl;
		_Path temp;
		boost::progress_display pd(v.size());
		for (auto& p : v){
			temp = p_to_dir/p.string().substr(p_from_dir.string().length());
			if (!boost::filesystem::exists(temp.parent_path())){
				boost::filesystem::create_directories(temp.parent_path());
			}
			boost::filesystem::copy_file(p, temp);
			++pd;
		}
		std::cerr << v.size() << " files copied." << std::endl;
		return v.size();
	}

	//---------------------------------------------------------
	//ɾ��Ŀ¼��ָ���ļ�
	//---------------------------------------------------------
	static size_t remove_files(const _Path& dir, const std::string& filename = "*"){
		if (!boost::filesystem::is_directory(dir)){
			throw std::runtime_error("args is not a dir");
		}

		std::vector<_Path> v;

		find_files(dir, filename, v);

		if (v.empty()){
			return 0;
		}
		std::cerr << "now begin remove files..." << std::endl;
		boost::progress_display pd(v.size());

		for (auto p : v){
			boost::filesystem::remove_all(p);
			++pd;
		}
		std::cerr << v.size() << " files remove." << std::endl;
		return v.size();
	}


        //------------------------------------------------------
        // ��ȡ��ǰϵͳʱ��
        //------------------------------------------------------
       static char* TIME_BUFFER = new char[256];
	   static std::string getCurrentTimeStr(){

            ZeroMemory(TIME_BUFFER, 256);
            SYSTEMTIME sys;

            GetLocalTime(&sys);
            sprintf(TIME_BUFFER, "%4d/%02d/%02d %02d:%02d:%02d",sys.wYear, sys.wMonth, sys.wDay, \
                    sys.wHour, sys.wMinute, sys.wSecond);

			std::string send_str(TIME_BUFFER);
            return send_str;
        }

       //----------------------------------------------------------
       // �ļ��Ƿ����
       // filename ��ָ�����ļ���
       //----------------------------------------------------------
           static bool fileisexist(const std::string& filename){
               if(filename.empty())
                   return false;
               _Path p(filename);
               boost::system::error_code e;
               boost::filesystem::exists(p,e);
               if(e){
                   return false;
               }
               if(!boost::filesystem::is_directory(p) && boost::filesystem::is_regular_file(p)){
                   return true;
               }
               else{
                   return false;
               }

           }

       //----------------------------------------------------------
       // Ŀ¼�Ƿ����
       // folderpath ��ָ�����ļ�
       //----------------------------------------------------------
	   static bool folderisexist(const std::string& folderpath){
           if(folderpath.empty())
               return false;
           _Path p(folderpath);
           boost::system::error_code e;
           boost::filesystem::exists(p,e);
           if(e){
               return false;
           }
           if(boost::filesystem::is_directory(p)){
               return true;
           }
           else{
               return false;
           }
       }

       //---------------------------------------------------------
       // �ݹ鴴��Ŀ¼
       // director ��Ҫ����������Ŀ¼
       //---------------------------------------------------------
           static bool create_director(const std::string& director){
               if (director.empty())
                   return false;
               _Path p(director);
               _Path parent = p.parent_path();
               if (!boost::filesystem::exists(parent))
                   create_director(parent.string());
               if (boost::filesystem::exists(p) && boost::filesystem::is_directory(p)){
                   return true;
               }
               else {
                   if (!boost::filesystem::exists(p)){
                       boost::filesystem::create_directory(p);
                       return true;
                   }
                   else if (!boost::filesystem::is_directory(p)){
                       boost::filesystem::create_directory(p);
                       return true;
                   }
               }
			   return false;
           }

       //-----------------------------------------------------
       // ��ȡһ���ļ��ľ���·��
       //-----------------------------------------------------
	   inline std::string getCompletePath(const std::string& filename){
		   std::string c_path;
           if(filename.empty())
               return c_path;
		   if (!fileisexist(filename) && !folderisexist(filename))
			   return "";
           _Path p(filename);
           c_path = boost::filesystem::complete(p).string();
           return c_path;
       }

       //-----------------------------------------------------
       // ����Guid
       //-----------------------------------------------------
       inline GUID CreateGuid(){
           GUID guid;
           CoCreateGuid(&guid);
           return guid;
       }

       //-----------------------------------------------------
       // ��Guidת��ΪMString
       // guid guid����
       //-----------------------------------------------------
	   inline std::string GuidToStdString(GUID guid){
           char buf[64];
           _snprintf_s(buf, sizeof(buf), "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                       guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1],
                   guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		   return std::string(buf);
       }

	   inline std::string GuidToStdString(){
		   GUID guid = CreateGuid();
		   char buf[64];
		   _snprintf_s(buf, sizeof(buf), "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			   guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1],
			   guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		   return std::string(buf);
	   }

	   inline __int64 GetFileSize(const std::string& filename){
		   if (fileisexist(filename)){
			   return boost::filesystem::file_size(filename);
		   }
		   return 0;
	   }


       //------------------------------------------------
       // ��ȡ����������
       // float
       // filename �ļ���
       // offset ƫ����
       // size ���ݿ��С
       //-----------------------------------------------
	   inline std::vector<float> getDataFromFile(const std::string& filename, \
                                                 long long offset,long long size)
       {
           std::vector<float> result_data;
           if(filename.empty()){
               return result_data;
           }
           char* ch = new char[size];
           memset(ch, 0, size);
           std::ifstream inFile(filename,std::ios::in | std::ios::binary);
           if(inFile.fail()){
               mj::HParseString par;
               par.clear();
               par("unabel open dat file for read\nFile:%1\nLine:%2",__FILE__,__LINE__);
               throw std::runtime_error(par.getresult());
           }
           inFile.seekg(offset,std::ios::beg);
           inFile.read(ch,size);
           inFile.close();
           for (int i=0; i < size; i += 4){
                   float f_test = *(float*)(&ch[i]);
                   result_data.push_back(f_test);
           }
           delete[] ch;
           return result_data;
       }

	   //------------------------------------------------------
	   // �޸��ļ���
	   //------------------------------------------------------
	   inline void rename(const std::string& filename, const std::string& name){
		   if (fileisexist(filename) || folderisexist(filename))
				boost::filesystem::rename(filename, name);
	   }

	   //------------------------------------------------------
	   // ��ȡ��ǰ����·��
	   //------------------------------------------------------
	   inline std::string GetCurrentPath(){
		   return boost::filesystem::current_path().string();
	   }

	   

       //-------------------------------------------------------
       // �滻�ļ���Ϣ
       // filename ��Ҫ�޸ĵ��ļ���
       // start ��Ҫ�滻����ʼλ��
       // place_str �滻������
       // end ָ���滻�Ľ���λ��
       //------------------------------------------------------
	   inline void replace_file(const std::string& filename, const std::string& start, \
		   const std::string& place_str = "", const std::string& end = "#End#"){
           if (filename.empty())
               return;
           std::ifstream inFile(filename);
           if (!inFile){
               inFile.open(filename);
           }
           if (inFile.fail()){
               throw std::runtime_error("Unable open file for read...");
           }

		   std::string str((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
           inFile.close();

           boost::xpressive::sregex sex;
           if (end == "#End#" || end.empty()){
               sex = boost::xpressive::sregex::compile(start + ".*");
           }
           else{
               sex = boost::xpressive::sregex::compile(start + ".*" + end);
           }

		   std::string new_str;
           new_str = boost::xpressive::regex_replace(str, sex, place_str);
           std::ofstream outFile(filename);
           outFile << new_str;
           outFile.close();
       }

       //-------------------------------------------------------------
       // ��ȡһ���ļ�����������
       // filename ����ȡ���ļ���
       //-------------------------------------------------------------
	   inline std::string read_all(const std::string& filename){
           if (filename.empty())
               return "";
           std::ifstream inFile(filename);
           if (!inFile){
               inFile.open(filename);
           }
           if (inFile.fail()){
               throw std::runtime_error("Unable open file for read...");
           }
		   return std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
       }

	   template<class T,class A,template<class T1,class A1>class C>
	   inline C<T, A>& read_all(const std::string& filename, C<T, A>& output){
		   output.clear();
		   if (filename.empty())
			   return output;
		   std::ifstream inFile(filename,std::ios_base::binary);
		   if (!inFile){
			   inFile.open(filename);
		   }
		   if (inFile.fail()){
			   throw std::runtime_error("Unable open file for read...");
		   }
		   size_t size = boost::filesystem::file_size(filename);
		   char* ch = new char[size];
		   inFile.read(ch, size);
		   size_t size1 = sizeof(T);
		   for (int i = 0; i < size; i += size1){
			   T f_test = *(T*)(&ch[i]);
			   output.push_back(f_test);
		   }
		   delete[] ch;
		   return output;
	   }

	   //-----------------------------------------------------------------
	   // ��ȡ��ǰ����dll��·��
	   //----------------------------------------------------------------
	   static std::string GetDllPath()
	   {
		   wchar_t dllPath[MAX_PATH] = { 0 }; //windows limit: longname<260
		   HMODULE hm = NULL;
		   if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
			   GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
			   (LPCWSTR)&GetDllPath,
			   &hm))
		   {
			   int ret = GetLastError();
			   std::cerr << "GetModuleHandle failed:" << ret;
			   return ".";
		   }
		   GetModuleFileName(hm, dllPath, sizeof(dllPath));
		   std::string str = MCodeCast::wtoc(dllPath);
		   std::string parent_path = _Path(getCompletePath(str)).parent_path().string();
		   return parent_path;
	   }

	   inline std::string GetExePath(){
		   char szFileName[MAX_PATH] = "";
		   TCHAR tcFullPath[MAX_PATH] = L"";
		   GetModuleFileName(NULL, tcFullPath, MAX_PATH);
		   _Path strFullPath(tcFullPath);
		   return strFullPath.parent_path().string();
	   }
}

namespace box{

	static int Error_MessageBox(const std::string& message, const std::string& titile = "Error", HWND hwnd = nullptr){
        return ::MessageBoxExA(hwnd,message.c_str(),titile.c_str(),MB_OK,\
                           MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US));
    }

	static int Info_MessageBox(const std::string& message, const std::string& titile = "Info", HWND hwnd = nullptr){
        return ::MessageBoxExA(hwnd,message.c_str(),titile.c_str(),MB_YESNOCANCEL,\
                           MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US));
    }

	static int Que_MessageBox(const std::string& message, const std::string& titile = "Info", HWND hwnd = nullptr){
        return ::MessageBoxExA(hwnd,message.c_str(),titile.c_str(),MB_YESNO,\
                           MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US));
    }
}

namespace reg{
	static inline std::string GetRegistryInfo(const std::string& __subkey, const wchar_t* ValueName){
    HKEY hKey;
    std::wstring subKey = L"";
	subKey += MCodeCast::stow(__subkey);
    long resulte = RegOpenKey(HKEY_CURRENT_USER, subKey.c_str(), &hKey);
    if (resulte != ERROR_SUCCESS)
    {
        return "";
    }
    else
    {

        DWORD dwType;
        wchar_t* szLogFile = new wchar_t[256];
        memset(szLogFile, 0, 256);
        DWORD dwLogFile;
        DWORD rc = RegQueryValueEx(hKey, ValueName, NULL, &dwType, (LPBYTE)szLogFile, &dwLogFile);
        if (rc == ERROR_SUCCESS   &&   dwType == REG_SZ)
        {
            szLogFile[dwLogFile - 1] = 0;
			std::string __current_path(MCodeCast::wtoc(szLogFile));
            delete[] szLogFile;
            if (file::folderisexist(__current_path)){
                RegCloseKey(hKey);
                return __current_path;
            }
            return "";

        }
        else{
            delete[] szLogFile;
            RegCloseKey(hKey);
            return "";
        }
    }
    return "";
}
}

namespace style{
	static inline std::string read_css_info(const std::string& filename, const std::string& group,
		const std::string& begin = "begin:", const std::string& end = "end"){

		static std::unordered_map<std::string, std::string> mFindStr;
        if(mFindStr.find(group) != mFindStr.end())
            return mFindStr[group];

		std::string  __result;
        if(!file::fileisexist(filename))
            return __result;

        std::ifstream inFile(filename);
        if(inFile.fail())
            return __result;

        while(!inFile.eof()){
			std::string str;
			std::string result_str;
            std::getline(inFile,str);

            if(str[0] == '[' && str[str.length()-1] == ']'){
				std::string __str;
                std::getline(inFile,__str);
                if(__str == begin){
                    while(__str != end){
                        if(inFile.eof()){
                            if(mFindStr.find(group) != mFindStr.end())
                                return mFindStr[group];
                            else
                                return "";
                        }
                        std::getline(inFile,__str);
                        if(__str != end)
                            result_str += __str;
                    }
                    //================================
                    mFindStr[str] = result_str;
                } // end if(__str == begin)
            }// end group
        } // end while(!inFile.eof())
        inFile.close();

        if(mFindStr.find(group) != mFindStr.end())
            return mFindStr[group];
        else
            return "";
    }
}
