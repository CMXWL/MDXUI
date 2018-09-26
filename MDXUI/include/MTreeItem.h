

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution
// Copyright (C) 2017-2018 by Mengjin (sh06155@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////


//---------------------------------------//
// ���ڹ������νṹ��item��Ϣ            //
// ���в���������#���ӵ��ַ���           //
//---------------------------------------//
#pragma once
#include <fstream>
#include <string>
#include <vector>

class  MTreeItem
{
    friend class MTreeModuleImpl;
public:
	MTreeItem();
	~MTreeItem();

	MTreeItem(const MTreeItem& item);
	MTreeItem& operator=(const MTreeItem& item);

    //
    // ���ԭʼ��Ϣ
    //
    void clear();



    //
    // ��Ӻ�ɾ����Ҫ��¼����Ŀ
    // ��Ŀ֮��Ĺ�ϵ�õ����
    //
    bool push_back(const std::string& info);
    void push_back(std::vector<std::string>& info);
    void insert(const std::string& before,const std::string& item);
    bool remove_item(const std::string& item);



    //
    // ������ӵ�itemΪ�ɸ�ѡ��item
    //
    void push_CheckItem(const std::string& item);
    void insert_checkItem(const std::string& before,const std::string& item);
    void push_CheckItem(std::vector<std::string>& info);




    //
    // remove_CheckItem����ɾ��item
    // ֻ���ø�itemʧȥ��ѡ����
    // ��Ҫ������ɾ��itemʹ��remove_item
    //
    bool remove_CheckItem(const std::string& item);



    //
    // �ú��������е�item����Ϊ��check�����ǲ�����check
    //
    void setCheckStatus(bool ischeck);



    //
    // �Ƴ����ڵ��������������
    //
    void remove_root(const std::string& rootStr);


private:
    //
    // ͨ�����������Ӧ��ֵ
    //
    std::vector<std::string> getItems(const std::string& key);




    //
    // �ж�����item�Ƿ�ӵ��ͬһ��parent
    //
    bool isSameParent(const std::string& item1,const std::string& item2);



    //
    // �ж������Ƿ��Ǹ��ӹ�ϵ
    //
    bool isParent(const std::string& parent,const std::string& item);

    bool isDependence(const std::string& majoy,const std::string& sub);




    //
    // ��ȡ���ڵ���Ϣ
    //
    std::string getParent(const std::string& item);




    //
    // ��ȡ�Լ���name
    //
    std::string getSelfName(const std::string& item);



    //
    // ��ȡ������Ϣ
    //
    std::vector<std::string>& getAllItems();
    std::vector<std::pair<std::string,bool>>& getItemsInfo();



    //
    // �׿��Լ��Ľڵ���ʣ�����Ϣ
    // �е���getParent
    //
    std::string removeName(const std::string& item);

    std::string getIconStr(const std::string& item);

private:
    std::vector<std::string> m_need_op_info;  //������Ҫ��������Ϣ
    std::vector<std::pair<std::string,bool>>  m_item_checkable;//������Ҫ���check��item
};

