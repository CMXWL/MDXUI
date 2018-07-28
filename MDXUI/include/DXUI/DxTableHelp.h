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