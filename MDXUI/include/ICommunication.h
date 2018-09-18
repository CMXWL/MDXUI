

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include "DxConfig.h"

class DXUI_API ICommunication : public TL::MTLObject
{
public:
    ICommunication();
    virtual ~ICommunication();
public:
    virtual MString ToString() const;

    ///
    /// \brief Connect
    /// \return
    /// ���Ӳ���
    ///
    virtual bool Connect();

    ///
    /// \brief Close
    /// \return
    /// �Ͽ�����
    ///
    virtual void Close();

    ///
    /// \brief IsConnect
    /// \return
    /// �������״̬
    ///
    virtual bool IsConnect();

    ///
    /// \brief Send
    /// \param msg
    /// \param len
    /// \return
    /// ��������
    /// �ú�����Ҫ���ݾ����ͨ��ģ������,ϵͳ�Լ�����
    ///
    virtual bool Send(const char* msg,__int64 len);


    ///
    /// \brief Read
    /// \param msg
    /// \param len
    /// \return
    /// ��������,�ú�������Ҫ����д,ֻ��Ҫ��ִ�м���
    ///
    void Read(const char* msg,__int64 len);

    ///
    /// \brief setConnectStatus
    /// \param isok
    /// �ֶ�����ͨ��ģ��״̬
    ///
    void setConnectStatus(bool isok);
};


