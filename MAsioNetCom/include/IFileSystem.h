#pragma once
#include <comdef.h>
#include <string>
#include "IAsioInterface.h"
#include <vector>

interface  __declspec(uuid("BBD4F39D-75B9-46D5-B791-F03040F74277"))  IFileSystem : public IUnknown
{
	virtual void __stdcall MRecursiveDir(const std::string& dir) = 0; // ������ӡһ��Ŀ¼����������ļ�
	virtual std::string __stdcall MFindFile(const std::string& dir, const char* filename) = 0; // ���ҵ����ļ�
	virtual void __stdcall MFindFiles(const std::string& dir, const std::string& filename, std::vector<std::string>& Result) = 0; // �����ļ�
	virtual size_t __stdcall MCopyFiles(const std::string& from_dir,
		 const std::string& to_dir, 
		 const std::string& filename = "*") = 0; // �����ļ�����һ��Ŀ¼

	virtual size_t __stdcall MRemoveFiles(const std::string& dir, const std::string& filename = "*") = 0; // �Ƴ��ļ�
	virtual size_t __stdcall MRemoveDir(const std::string& dir) = 0; // �Ƴ��ļ���
	virtual bool __stdcall MRemoveFile(const std::string& file) = 0;
	virtual bool __stdcall MFileIsExist(const std::string& filename) = 0; // �ļ��Ƿ����
	virtual bool __stdcall MFolderIsExist(const std::string& folderpath) = 0; // �ļ����Ƿ����
	virtual bool __stdcall MCreateDir(const std::string& director) = 0;  // ����һ��·��
	virtual bool __stdcall MIsCompletePath(const std::string& path) = 0; // �Ƿ���ȫ·��

	virtual std::string __stdcall MParentPath(const std::string& director) = 0;   // �ļ���parent·��
	virtual std::string __stdcall MFileName(const std::string& director) = 0;     // �ļ���
	virtual std::string __stdcall MExtensionName(const std::string& director) = 0;// �ļ�����չ��
	virtual std::string __stdcall MLeafName(const std::string& director) = 0; // ������չ���Ĳ���
	virtual std::string __stdcall MRootName(const std::string& director) = 0; // ����
	virtual std::string __stdcall MRootPath(const std::string& director) = 0; // ��·��
	virtual std::string __stdcall MRootDir(const std::string& director) = 0;  // ��Ŀ¼
	virtual std::string __stdcall MRemoveFilename(const std::string& path) = 0;   // �Ƴ�·���е��ļ���
	virtual std::string __stdcall MReplaceExtension(const std::string& path, const std::string& newext) = 0; // �滻��չ��

	virtual bool __stdcall MIsFolder(const std::string& path) = 0;
	virtual bool __stdcall MIsFile(const std::string& path) = 0;


	virtual std::string __stdcall MCompletePath(const std::string& filename) = 0; // ��ȡȫ·��
	virtual std::string __stdcall MGuidString() = 0;					 // ��ȡһ��GUUID�ַ���
	virtual __int64 __stdcall MFileSize(const std::string& filename) = 0;	 // ��ȡ�ļ���С
	virtual void __stdcall MRenameFile(const std::string& filename, const std::string& name) = 0; // �������ļ�

	virtual std::string __stdcall MCurrentPath() = 0;	// ��ȡ��ǰ����·��
	virtual std::string __stdcall MGetDllPath(void* ptr) = 0;		// ��ȡ��ǰִ��exe��·��
	virtual std::string __stdcall MGetExePath() = 0;		// ��ȡ��ǰִ�е�dll·��
	virtual void __stdcall MReplaceFileInfo(const std::string& filename, const std::string& start, \
		const std::string& place_str = "", const std::string& end = "#End#") = 0;  // �滻һ���ļ��е����ݣ���ʼ�����滻��XX,���滻�Ľ�β����"#End#"��ʾ�滻��β

	virtual std::string __stdcall MCurrentTime() = 0;  // ��ȡ��ǰϵͳʱ�� YYYY/MM/DD HH:MM:SS

	virtual std::string __stdcall  wtoc(const wchar_t* str) = 0; //���ֽڵ����ֽڵ�ת��
	virtual std::wstring __stdcall stow(const char* src) = 0;//���ֽڵ����ֽڵ�ת��
};

//
// Ĭ���ṩ�Ĵ���IFileSystem�Ĺ�������
// ���ڸýӿ�û���κ�����
// ���Դ˴��ṩ���Ǵ���һ����̬����
//
inline IFileSystem* CreateFileSystem(){
        IFileSystem* pFile = NULL;
	::CoCreateInstance(
		ASIOCLSID,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IFileSystem),
		(void**)&pFile
		);
	return pFile;
}
