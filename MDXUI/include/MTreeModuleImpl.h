

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

#pragma once
/********************************
 *                              *
 *     �������νṹ����ģ��     *
 *                              *
 * *****************************/
#include "DxTreeWindow.h"
#include "DxTreeItem.h"
#include <memory>
#include <functional>
#include <vector>
#include "MTreeNavigation.h"
#include "MTreeItem.h"
class MTreeEvent;


//
// class MTreeModuleImpl
//
class MTreeModuleImpl {
    typedef std::tuple<std::string,std::string,std::string,void*> Tree_Data;

public:
    ///
    /// �ṩ˫��������
    ///
    typedef std::function<void(const std::string,const std::string)> CLICK_RECALL;
    typedef std::function<void(const std::string,const std::string,DxUI::DxPointI)> RCLICK_RECALL;

    ///
    /// ֻ��һ������
    /// ���Ǹò��������˵��item��������Ϣ����root���Լ���ÿһ���ڵ���#�ŷָ�
    /// ��Ҫ�Լ�����
    /// ��ȷ���ڵ��������ʱ��ʹ������Ļص�
    /// ���ڵ����϶��ʱ��ʹ������Ļص���ʽ
    ///
    typedef std::function<void(const char*,__int64)> A_CLICK_RECALL;
	typedef std::function<void(const char*, __int64, DxUI::DxPointI)> A_RCLICK_RECALL;

public:
	explicit MTreeModuleImpl();
	virtual ~MTreeModuleImpl();
    DxUI::CDxTreeWindow* TreeView();


    void DealFile(const std::string& filename);




    //
    // ����ģ��
    //
    void updateTree();

    //
    // ��������ģ��
    //
    void reset();

    //
    // ����item����ʾ����
    // ��һ������Ϊitem��stringid���ڶ�������Ϊ��ʾ������
    //
    bool modifyName(const std::string& strid,const std::string& ShowName);

    //
    // ������ʾ������item��str id
    //
    std::string getItemStrId(const std::string& showName);
    std::string getItemText(const std::string& strid);


    //
    // ����header��Ϣ
    //
    void setHeaderLabel(const MString& header);
    void setHeaderHide(bool isHide);

    void setFontForItem(const MString& strId,const DxUI::DXFontInfo& font);



    //
    // ������¼��ص�����
    //
    void bindClickFun(CLICK_RECALL fun);
    void bindDClickFun(CLICK_RECALL fun);
    void bindRClickFun(RCLICK_RECALL fun);



    //
    // ���Ӳ�������
    // ��Ҫ�Լ����½�������
    // ������ÿһ��������#�ŷ���
    //
    void bindTreeEvent(MTreeEvent* Event);
    void bindAClickFun(A_CLICK_RECALL fun);
    void bindADClickFun(A_CLICK_RECALL fun);
    void bindARClickFun(A_RCLICK_RECALL fun);



    //
    // �������item��Ϣ
    //
    void push_back(const std::string& info);
    void push_back(std::vector<std::string>& info);
    void insert(const std::string& before,const std::string& item);
    bool remove_item(const std::string& item);
    void clear();
    void push_CheckItem(const std::string& item);
    void push_CheckItem(std::vector<std::string>& info);
    void insert_checkItem(const std::string& before,const std::string& item);
    void remove_CheckItem(const std::string& item);

    void remove_root(const std::string& rootStr);


    //
    // ����item��ѡ��״̬
    //
    void setCheckStatus(bool ischeck);

    //
    // �����ѡ��״̬
    //
    void setSelectStatus(const std::string& strid,bool isselected);



    //
    // ��ȡ��ѡ�е�item��Ϣ
    //
    std::vector<std::string> getSelectItems();

    //
    //
    //
    void QueryStandardItem(const std::string& strid,DxUI::CDxTreeItem*& outItem);



protected:

    void buildTree();

    //
    // �ݹ鴦��item��Ϣ
    //
    void processItems(std::vector<std::string> info);

    //
    // �ݹ鴴��item
    //
    void create_items(const std::string& item_str);

    //
    // ��������item
    //
    void create_item(const std::string& item_str);

    //
    // ������������item
    //
    void create_item_help(const std::string& parentstr,const std::string& selfstr);
    void create_item_help(DxUI::CDxTreeItem* Parentitem,const std::string& parentstr,const std::string& selfstr);



    //
    // �ݹ�append item
    //
    void append_items(std::vector<std::string> items_info);
    void append_items(const std::string& item_info);



    //
    // �ݹ��ѯitem��ǰ������
    //
	void checkItemInfo(DxUI::CDxTreeItem* item);




    //
    // ����item��check״̬
    //
    void setCheckStatus(const std::string& item);



    //
    // ��items���սڵ�ĳ�������
    //
	std::vector<std::string> sortItems(std::vector<std::pair<std::string, DxUI::CDxTreeItem*>>& items);


    MTreeNavigator*     p_tree_view{nullptr};


    MString             m_header_label;

    CLICK_RECALL        m_click_fun{nullptr};
    CLICK_RECALL        m_dclick_fun{nullptr};
    RCLICK_RECALL       m_rclick_fun{nullptr};

    A_CLICK_RECALL      m_a_click_fun{nullptr};
    A_CLICK_RECALL      m_a_dclick_fun{nullptr};
    A_RCLICK_RECALL     m_a_rclick_fun{nullptr};
    std::vector<std::pair<A_CLICK_RECALL,bool>> m_a_click_funs;
    std::vector<std::pair<A_CLICK_RECALL,bool>> m_a_dclick_funs;
    std::vector<std::pair<A_RCLICK_RECALL,bool>> m_a_rclick_funs;


    //
    // ����item�Ĺ�ϵ��
    //
    MTreeItem*          m_item_manage; //����item




    //
    // ����item
    //
	std::vector<DxUI::CDxTreeItem*>      m_last_items;  //���յ�item����ʵҲ�������ļ�����item����



    //
    // ����item���Ƶ�ͼ����Ϣ��ӳ��
    //
    std::vector<std::pair<std::string,std::string>> m_items_info;           //item ---> icon;



    //
    // item��string id ��item��ӳ��
    //
	std::vector<std::pair<std::string, DxUI::CDxTreeItem*>> m_items_items;       // item->string ======= item->item
    std::map<std::string,std::string>                  m_item_names;        // str id ����ʾ����ӳ��




    //
    // ��������� m_items_items �ĸ���
    //
	std::vector<std::pair<std::string, DxUI::CDxTreeItem*>> m_items_items_bak;  //����ĸ���



    //
    // �ڵݹ�����н�����ר��һ��item�������
    //
	std::vector<std::pair<std::string, DxUI::CDxTreeItem*>> m_temp_items;        //�ڵݹ��������Ϊ��ʱ��ת��һ������




    //
    // һ����ʱitem
    // ���ڵݹ��������Ϊ��ʱ�滻
    //
	DxUI::CDxTreeItem*                   m_temp_item{ nullptr };              //�ڵݹ��������Ϊ��ʱ��item
    std::vector<std::string>			 m_temp_str_for_item;               //�ڵݹ��������Ϊ��ʱ��ת��һ������



    //
    // ����item�Ƿ��ѡ��
    //
    std::vector<std::pair<std::string,bool>>        m_item_checkable;

    //
    // ��ѡ�е�item��Ϣ
    //
    std::string                          m_selected_item_info;

    MTreeEvent*                          pTreeEvent{nullptr};
};

