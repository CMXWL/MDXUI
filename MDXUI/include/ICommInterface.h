

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include <comdef.h>
#include <MAny.h>

//
// �����ӿ�
// �������ֻ��һ������Ľӿ�,Ŀ����Ϊ�����дģ��
// �˴���Ĭ����Ϊ�������亯����һ��
//
interface __declspec(uuid("6046C6DB-FD61-4F06-BF7B-D7E94BCFE79E")) ICommInterface
{
    virtual bool __stdcall OnNewOperator() = 0;
    virtual bool __stdcall OnOpenOperator() = 0;
    virtual bool __stdcall OnSaveOperator() = 0;
    virtual bool __stdcall OnSaveAsOperator() = 0;
    virtual bool __stdcall OnCloseOperator() = 0;
    virtual bool __stdcall OnHelpOperator() = 0;

    //
    // ��ȡģ���������Ϣ
    //
    virtual const char* __stdcall DocumentInfo() = 0;
    //
    // ��ģ���л�ȡ����Լ����ⲿ���ݺ�ģ����а�
    // �������ݰ���Ҫ������Ķ���֧��,����MProperty����MPropertyGroup������Ϳ���
    //
    virtual mj::MAny __stdcall OnResult(){return mj::MAny();}
    virtual void __stdcall OnBindData(const mj::MAny& __data){}
};


