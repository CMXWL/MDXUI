

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////


#pragma once
#include "DxConfig.h"
#include <MAny.h>

class DXUI_API MLoggerStream
{
    typedef std::function<bool(const char*,__int64)> FeedBackFun;
    typedef std::function<bool(const char*,__int64)> ParamFun;
public:
    MLoggerStream();
    virtual ~MLoggerStream();
    virtual MLoggerStream& operator<<(const MString& str);
    virtual MLoggerStream& TransData(const MString& str);
	virtual bool TransData(const char* buffer, __int64 len);
    virtual bool TransParam(const MString& str);
    void SlotForAnyAction(const MString& StrKey,const MAny& action);
private:
    FeedBackFun   mBackFun{nullptr}; // ʹ��operator ����log �Ļ�����ִ�иò��� ��ʶ�ֶ� FeedBack
    FeedBackFun   mDataFun{nullptr}; // ���ڴ�������ʹ�� ��ʶ�ֶ� SendData
    ParamFun      mParamFun{nullptr}; // ��Ҫ���ڴ������ ��ʶ�ֶ�Ϊ SendParam
};


