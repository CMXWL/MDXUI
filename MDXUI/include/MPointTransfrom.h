

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "DxConfig.h"


class DXUI_API MPointTransfrom
{
public:
    MPointTransfrom();
    ~MPointTransfrom();
    ///
    /// \brief Rotate
    /// \param x
    /// \param y
    /// \param inoutdata
    /// \param Angle ˳ʱ����ת�Ƕ� deg
    /// \param xAxis 1 0
    /// \param yAxis 1 0
    /// \param zAxis 1 0
    /// \return
    /// ��ָ���������ת
    ///
    bool Rotate(
            std::vector<double>& xs,
            std::vector<double>& ys,
            mj::dmat& inoutdata,
            double Angle,
            int xAxis,
            int yAxis,
            int zAxis
            );

    ///
    /// \brief Rotate
    /// \param x
    /// \param y
    /// \param inoutdata
    /// \param xAngle
    /// \param yAngle
    /// \param zAngle
    /// \param xCenter
    /// \param yCenter
    /// \param zCenter
    /// \return
    /// �����ĵ�(xCenter,yCenter,zCenter) ������ת
    ///
    bool Rotate(std::vector<double>& xs,
            std::vector<double>& ys,
            mj::dmat& inoutdata,
            double xAngle,
            double yAngle,
            double zAngle,
            double xCenter,
            double yCenter,
            double zCenter
            );

    ///
    /// \brief Translate
    /// \param xs
    /// \param ys
    /// \param inoutdata
    /// \param xDistance
    /// \param yDistance
    /// \param zDistance
    /// \param isDisoutrange �Ƿ�Գ�����Χ�Ĳ��ֽ��вü�
    /// \return
    /// ƽ��
    ///
    bool Translate(std::vector<double>& xs,
                   std::vector<double>& ys,
                   mj::dmat& inoutdata,
                   double xDistance,
                   double yDistance,
                   double zDistance,
                   bool isDisoutrange = true);

    ///
    /// \brief Translate
    /// \param xs
    /// \param ys
    /// \param inoutdata
    /// \param xDistance
    /// \param yDistance
    /// \param zDistance
    /// \param minvalue
    /// \param maxvalue
    /// \return
    ///
    bool Translate(std::vector<double>& xs,
                   std::vector<double>& ys,
                   mj::dmat& inoutdata,
                   double xDistance,
                   double yDistance,
                   double zDistance,
                   double minvalue,
                   double maxvalue);

    ///
    /// \brief meshdatatype
    /// bool ��ʶ�Ƿ�������
    /// int ��ǰ���ݵ����
    ///
    typedef mj::MMatrixSheet<bool,int> meshdatatype;

    ///
    /// \brief GenMeshIndex
    /// \param data
    /// \param indexs
    /// \return
    /// ���ݸ���������λ��������Ӧ������
    ///
    bool GenMeshIndex(const meshdatatype& data,std::vector<unsigned>& indexs);
};


