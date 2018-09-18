

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <MTypeTool.h>

namespace DxUI{
	//+------------------------
	//
	// table ѡ�����ṹ
	// mSelectedCols ѡ�е��к�
	// mData ����
	// int ----> �к�
	// MPairType<int, MString>  �к� + ����
	//
	//+-------------------------
	struct CDxTableSelected{
		TL::Vector<int>		mSelectedCols;  
		TL::Map< int, TL::Vector<std::pair<int, MString>>> mData;
	};
}