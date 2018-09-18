

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include "MString.h"
using mj::MString;


extern "C" namespace MFileSystem{
	
	MSTRING_API void MRecursiveDir(const MString& dir); // ������ӡһ��Ŀ¼����������ļ�
	MSTRING_API MString MFindFile(const MString& dir, const MString& filename); // ���ҵ����ļ�
	MSTRING_API void MFindFiles(const MString& dir, const MString& filename, std::vector<MString>& Result); // �����ļ�
	MSTRING_API size_t MCopyFiles(const MString& from_dir, const MString& to_dir, const MString& filename = "*"); // �����ļ�����һ��Ŀ¼

	MSTRING_API size_t MRemoveFiles(const MString& dir, const MString& filename = "*"); // �Ƴ��ļ�
	MSTRING_API size_t MRemoveDir(const MString& dir); // �Ƴ��ļ���
	MSTRING_API bool MFileIsExist(const MString& filename); // �ļ��Ƿ����
	MSTRING_API bool MFolderIsExist(const MString& folderpath); // �ļ����Ƿ����
	MSTRING_API bool MCreateDir(const MString& director);  // ����һ��·��
	MSTRING_API bool MIsCompletePath(const MString& path); // �Ƿ���ȫ·��

	MSTRING_API MString MParentPath(const MString& director);   // �ļ���parent·��
	MSTRING_API MString MFileName(const MString& director);     // �ļ���
	MSTRING_API MString MExtensionName(const MString& director);// �ļ�����չ��
	MSTRING_API MString MLeafName(const MString& director); // ������չ���Ĳ���
	MSTRING_API MString MRootName(const MString& director); // ����
	MSTRING_API MString MRootPath(const MString& director); // ��·��
	MSTRING_API MString MRootDir(const MString& director);  // ��Ŀ¼
	MSTRING_API MString MRemoveFilename(const MString& path);   // �Ƴ�·���е��ļ���
	MSTRING_API MString MReplaceExtension(const MString& path, const MString& newext); // �滻��չ��
		 
	MSTRING_API bool    MIsFolder(const MString& path);
	MSTRING_API bool	 MIsFile(const MString& path);


	MSTRING_API MString MCompletePath(const MString& filename); // ��ȡȫ·��
	MSTRING_API MString MGuidString();					 // ��ȡһ��GUUID�ַ���
	MSTRING_API __int64 MFileSize(const MString& filename);	 // ��ȡ�ļ���С
	MSTRING_API void MRenameFile(const MString& filename, const MString& name); // �������ļ�

	MSTRING_API MString MCurrentPath();	// ��ȡ��ǰ����·��
	MSTRING_API MString MGetDllPath(void *&ptr);		// ��ȡ��ǰִ��exe��·��
	MSTRING_API MString MGetExePath();		// ��ȡ��ǰִ�е�dll·��
	MSTRING_API void MReplaceFileInfo(const MString& filename, const MString& start, \
		const MString& place_str = "", const MString& end = "#End#");  // �滻һ���ļ��е����ݣ���ʼ�����滻��XX,���滻�Ľ�β����"#End#"��ʾ�滻��β

	MSTRING_API MString MCurrentTime();  // ��ȡ��ǰϵͳʱ�� YYYY/MM/DD HH:MM:SS

	MSTRING_API MString  wtoc(const wchar_t* str); //���ֽڵ����ֽڵ�ת��
	MSTRING_API std::wstring stow(const char* src);//���ֽڵ����ֽڵ�ת��
}

