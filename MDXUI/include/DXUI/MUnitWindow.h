#pragma once
#include "MDirectPlotImpl.h"
#include "MDx11Point.h"
#include "xnacollision.h"
#include "MDcartplot3d.h"

using DxUI::BasicPC;
namespace DxUI{
	class MFTFont;
}
using DxUI::MFTFont;
//+--------------------------------
//
// class MUnitWindow
// ������
//
//+--------------------------------
class DXUI_API MUnitWindow :
	public MDcartplot3d
{
	DECLARE_CLASS(MUnitWindow)

public:
	struct MVector3D{
		float x;
		float y;
		float z;
	};

	struct TextType{
		ID3D11ShaderResourceView* Tex{ nullptr };
		int width{ 0 };
		int height{ 0 };
	};

	typedef std::function<void(unsigned)>           ClickPointFun;

public:
	MUnitWindow();
	~MUnitWindow();

	//
	// ���Ƶ�ĺ�����
	//
	virtual bool	LondUnitContent(){ return true; }
	void			SetPointBitmap(const MString& bitmap);
	void			SetOrgColor(float r, float g, float b, float a);
	void			SetPointColor(unsigned id, float r, float g, float b);
	void			LoadPointFromFile(const MString& unitfilename);
	void			SetPointRadius(float radius);
	void			SetPoint(std::vector<MDx11::DXUnitPointType> &points);
	void			SetPoint(std::vector<MVector3D> &points, unsigned baseid = 1);
	void			SetPointData(unsigned id, float value);
	void			BindClickPointFun(ClickPointFun fun);
	float			GetValueFromId(unsigned id) const;
	unsigned		GetPointsCount() const;
	void			ClearPoint();
	void			ClearPointColor();
	void			IsNeedShowPointInfo(bool isshow);
	void			IsNeedShowPointId(bool isshow);

protected:
	bool OnInitResource3D();
	bool BuidVertex();
	void readData(const MString& filename);
	void picked(float x, float y);
	void Frustum();
	void updateTetxInfo();
	void OnRender();
	void OnRender3D();
	void UnInitResource();
	void OnUpdateBitmap();
	void ReGenTextureForText(int width, int height);
	void OnPaintEventFor2D(IPainterInterface* painter);
	void OnMouseEvent(const DxUI::CDxMouseEvent& e);
	
private:
	ID3D11Buffer*               pPointVertexBuffer{ nullptr };
	ID3D11InputLayout*          pPointInputLayout{ nullptr };\
	MDx11LayoutManage*          pPointLayoutManager{ nullptr };
	unsigned                    mPointCount;  // ��Ԫ����
	unsigned                    mCurrentBufferSize;
	float                       mZvalue{ 1.f };
	float                       mRadius{ 10.f };
	unsigned                    mPickedIndex{ -1 };  // �������Ƿ���е�Ԫ
	XMFLOAT4X4                  mPointWorldMatrix;         // ����任����
	XMFLOAT4                    mOrgColor;
	XMFLOAT4                    mTextColor;
	XNA::AxisAlignedBox         mPointMeshBox;        // ���ΰ�װ��
	XNA::Frustum                mPointCamFrustum;     // �ü���
	bool                        bIsNeedID{ true };
	bool                        bIsShowMsg{ true };


	ID2D1Bitmap*				pBitmap{ nullptr }; // �ʺ���
	ID3D11ShaderResourceView*   pRoundSRV{ nullptr };// Բ������
	MString					    mRoundSRVBitmap;

	std::map<unsigned, BasicPC> mOrgVertexs;     // ԭʼ��������
	std::map<unsigned, BasicPC> mLVertexs;     // δ�任�Ķ�������
	std::map<unsigned, BasicPC> mVisualPoints; // ����ɼ��ĵ�
	std::map<unsigned, float>   mPointData;    // ������Ե�Ԫ�����ݣ������ֵ��������λ
	std::map<unsigned, XMFLOAT4> mPointColors;
	std::map<mj::MString, TextType> mTextTextureInfo;
	std::map<mj::MString, TextType> mHTextTextureInfo; // �任����ı���Ϣ
	ClickPointFun               mClickFun{ nullptr };

	double                      mXOffset{ 0.0 };
	double                      mYOffset{ 0.0 };
	float                       mPointWidth{ 0.5 };
	float                       mPointHeight{ 0.5 };
	MFTFont*					p_DxFont{ nullptr };
};

