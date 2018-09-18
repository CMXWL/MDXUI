

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once;

#include "DxConfig.h"
#include <vector>

class MTreeModuleImpl;
class MTreeEvent;
namespace DxUI{
	class CDxWidget;
	class CDxTreeItem;
}



class DXUI_API MTreeModule
{
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
    typedef std::function<void(const char*,__int64,DxUI::DxPointI)> A_RCLICK_RECALL;


public:
	explicit MTreeModule();
	~MTreeModule();

	DxUI::CDxWidget* TreeView();

    void DealFile(const std::string& filename);



    //
    // ����ģ��
    //
    void UpdateTree();



    //
    // ��������ģ��
    //
    void Reset();



    //
    // ����item����ʾ����
    // ��һ������Ϊitem��stringid���ڶ�������Ϊ��ʾ������
    //
    bool ModifyName(const std::string& strid,const std::string& ShowName);

    void SetSelectStatus(const std::string& strid,bool isselected);



    //
    // ������ʾ������item��str id
    //
    std::string GetItemStrId(const std::string& showName);
    std::string GetItemText(const std::string& strid);



    //
    // ����header��Ϣ
    //
    void SetHeaderLabel(const MString& header);
    void SetHeaderHide(bool isHide);

    void SetItemFont(const std::string& strid,const DxUI::DXFontInfo& font);



    //
    // ������¼��ص�����
    //
    void BindClickFun(CLICK_RECALL fun);
    void BindDClickFun(CLICK_RECALL fun);
    void BindRClickFun(RCLICK_RECALL fun);




    //
    // ���Ӳ�������
    // ��Ҫ�Լ����½�������
    // ������ÿһ��������#�ŷ���
    //
    void BindTreeEvent(MTreeEvent* Event);
    void BindAClickFun(A_CLICK_RECALL fun);
    void BindADClickFun(A_CLICK_RECALL fun);
    void BindARClickFun(A_RCLICK_RECALL fun);

    //-------------------------------------------
    // �������item��Ϣ
    //-------------------------------------------
    void push_back(const std::string& info);
    void push_back(std::vector<std::string>& info);
    void insert(const std::string& before,const std::string& item);
    bool remove_item(const std::string& item);
    void clear();
    void push_CheckItem(const std::string& item);
    void push_CheckItem(std::vector<std::string>& info);
    void insert_CheckItem(const std::string& before,const std::string& item);
    void remove_CheckItem(const std::string& item);


    void remove_root(const std::string& rootId);

    //-------------------------------------------
    // ����item��ѡ��״̬
    //-------------------------------------------
    void SetCheckStatus(bool ischeck);

    //------------------------------------------
    // ��ȡ��ѡ�е�item��Ϣ
    //------------------------------------------
    std::vector<std::string> GetSelectItems();

    //
    // ��ѯQStandarItem
    //
	void QueryStandardItem(const std::string& itemstrid, DxUI::CDxTreeItem*& outItem);




private:
    MTreeModuleImpl* pTreeImpl;
};

