

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Dx3DWidget.h"

using DxUI::IPainterInterface;
using DxUI::DxColor;

//+-------------------------------
//
// clas MDirectPlotImpl
// ���ڻ��Ʒ���ͼ
//
//+-------------------------------
class DXUI_API MDirectPlotImpl :
	public DxUI::CDx3DWidget
{
	DECLARE_CLASS(MDirectPlotImpl)
public:
	MDirectPlotImpl();
	~MDirectPlotImpl();

	void SetBackGroundColor(const DxColor& col);

	void SetCameraPosition(double x, double y, double z);

	//
	// ����ͼ������
	//
	void SetXRotation(double value);
	void SetYRotation(double value);
	void SetZRotation(double value);
	void SetWalkValue(double value);
	void SetXTranslate(double value);
	void SetYTranslate(double value);
	void SetZTranslate(double value);
	void SetScaleValue(double xScale, double yScale, double zScale);

	//
	// �޸�����
	//
	void AddXRotation(double value);
	void AddYRotation(double value);
	void AddZRotation(double value);
	void AddWalkValue(double value);
	void AddXTranslate(double value);
	void AddYTranslate(double value);
	void AddZTranslate(double value);
	void AddScaleValue(double xScale, double yScale, double zScale);

	//
	// ��ȡ����
	//
	double XRotation() const;
	double YRotation() const;
	double ZRotation() const;
	double XTranslate() const;
	double YTranslate() const;
	double ZTranslate() const;
	void ScaleValue(double& xScale, double& yScale, double& zScale);
	void RotationCenter(double& x, double& y, double& z);


	//
	// ������ת���ĵ�
	//
	void SetRotationCenter(double x, double y, double z);


	XMMATRIX	GetWorldTransmatMatrix() const;
	XMMATRIX	GetViewProjectMatrax();
	XMMATRIX	GetViewMatrix();
	XMMATRIX	GetProjectMatrix();
	void		UpdateCamera();

protected:
	virtual void OnPaintEventFor2D(IPainterInterface* painter);
	void	OnRender();
	void	OnRender2D();
	bool	OnInitResource3D();
	void	OnReShape(int w, int h);


protected:

	//+----------------------
	//
	// D3D �� D2D ����
	//
	//+----------------------
	ID3D11InputLayout*          pD2dLayout{ nullptr };
	ID3D10Device1*              pD3d101Device{ nullptr };
	IDXGIKeyedMutex*            pKeyedMutex11{ nullptr };
	IDXGIKeyedMutex*            pKeyedMutex10{ nullptr };
	ID2D1RenderTarget*          pD2DRenderTarget{ nullptr };
	ID2D1SolidColorBrush*       pBrush{ nullptr };
	ID3D11Texture2D*            pBackBuffer11{ nullptr };
	ID3D11Texture2D*            pSharedTex11{ nullptr };
	ID3D11Buffer*               pD2dVertBuffer{ nullptr };
	ID3D11Buffer*               pD2dIndexBuffer{ nullptr };
	ID3D11ShaderResourceView*   pD2dTexture{ nullptr };
	ID3D11BlendState*           pTransparency{ nullptr };
	ID2D1Factory*               pD2DFactory{ nullptr };
	ID3D11Buffer*               pD3dVertBuffer{ nullptr }; // ������������Դ
	ID3D11Buffer*               pD3dIndexBuffer{ nullptr }; //������������Դ
	unsigned                    mD3dIndexNum;

	MDx11BufferManage*			pBufferManagerForD2D{ nullptr };
	MDx11LayoutManage*			pLayoutManagerForD2D{ nullptr };

protected:

	DxColor						mGroundColor;
	//
	// ��������
	//
	double						mWalkValue{ 0.0 };

	//
	// ��ת
	//
	double						mXRotationValue{ 0.0 };
	double						mYRotationValue{ 0.0 };
	double						mZRotationValue{ 0.0 };

	//
	// �ƶ�
	//
	double						mXTranslate{ 0.0 };
	double						mYTranslate{ 0.0 };
	double						mZTranslate{ 0.0 };

	//
	// ����
	//
	double						mXScaleValue{ 1.0 };
	double						mYScaleValue{ 1.0 };
	double						mZScaleValue{ 1.0 };

	//
	// ��ת��
	//
	XMFLOAT3					mCenterPoint{ 0, 0, 0 };

};

