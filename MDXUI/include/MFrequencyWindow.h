

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once
#include "DxWindow.h"
#include "DxGroupBox.h"
#include "DxRadioButton.h"
#include "DxStackedWidget.h"

using DxUI::CDxWindow;
using DxUI::CDxRadioButton;
using DxUI::CDxStackedWidget;
using DxUI::CDxGroupBox;


//
// ������������״̬�Ķ���
//

class UiBase;
class DXUI_API MFrequencyWindow :
	public CDxWindow
{

	typedef std::function<double(double, const mj::MString&)> TRANSLATEDATAFUNTYPE;
	typedef std::function<void(const std::vector<mj::MString>&)> IMPORTDATAFUNTYPE;
public:
	MFrequencyWindow(const MString& laggroup);
	~MFrequencyWindow();
	std::vector<double> GetData();

	//
	// ��������
	//
	void SetData(unsigned type,const std::vector<double>& data,const MString &unit);

	//
	// ���õ�λ�б�
	//
	void SetUnits(const TL::Vector<MString>& units);

	//
	// ���õ�λת������
	//
	void BindTranlatDataFun(TRANSLATEDATAFUNTYPE fun);

	//
	// ���õ�λת������
	//
	void BindUnitTranslateFun(TRANSLATEDATAFUNTYPE fun);

	//
	// ���õ���������Ĭ�������ļ�ʱʹ�õ��ⲿ������
	//
	void BindImportDataFun(IMPORTDATAFUNTYPE fun);

	//
	// ��ȡ����
	//
	unsigned GetType() const;

	//
	// ��ȡ��λ
	//
	MString GetUnit(); // ��ȡ��λ��Ϣ

	
	//
	// ������������ֻ��Ҫһ�� type -- 1 2 3
	//
	void setOnlyType(unsigned type);
private:
	void init_connect();
	void slot_rad(bool is_checked, CDxWidget* sender);
private:
	void init_style();
	double DefualtUnitTranslateFun(double value, const MString& unit);

	CDxGroupBox*      pTypeGroup;       //���Ϳ��
	CDxGroupBox*      pInfoGroup;       //��Ϣ���
	CDxRadioButton*   pSingleRad;   //��Ƶ��
	CDxRadioButton*   pRangeRad;    //��Χ
	CDxRadioButton*   pListRad;     //�б�
	CDxStackedWidget* pMultWidget;  //info

	UiBase*    pSingleigdet;
	UiBase*    pRangeWidget;
	UiBase*    pListWidget;

private:
	unsigned             mType; //1 2 3

	TRANSLATEDATAFUNTYPE mUnitTranslateFun{ nullptr };

};

