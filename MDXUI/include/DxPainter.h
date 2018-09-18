

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution and is Copyright
// 2017-2018 by Mengjin (sh06155@hotmail.com).
// The latest version may be obtained from [******************]
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "DxConfig.h"
#include "IPainterInterface.h"
#include "DxCharaterFormat.h"
#include <list>

namespace DxUI{

	class CDxEffects;

	//+-----------------------------------
	//
	// class CDxPainter �ò㸺����Ⱦ
	//
	//+-----------------------------------
	class DXUI_API CDxPainter : public IPainterInterface{
	public:
		typedef ID2D1RenderTarget* LPID2D1HwndRenderTarget;
	public:
		CDxPainter(ID2D1RenderTarget* render);
		~CDxPainter();

		void*  GetPainterEnginer();
		ID2D1RenderTarget* getRenderTarget() const;
		ID2D1RenderTarget* operator->() const;
		operator LPID2D1HwndRenderTarget() const;
		operator bool() const;


		//
		// ��ͼ�ӿ�
		//

		void	BeginDraw();
		void	Clear(const DxColor& col);
		void	EndDraw();

		void	DrawRectangle(const RECT& rc, const DxColor& col, double size);
		void	DrawRoundedRectangle(const RECT& rc, const SIZE& radius, const DxColor& col, double size);
		void	DrawEllipse(const RECT& rc, const SIZE& radius, const DxColor& col, double size);

		void	DrawDashRectangle(const RECT& rc, const DxColor& col, double size);
		void	DrawDashRoundedRectangle(const RECT& rc, const SIZE& radius, const DxColor& col, double size);
		void	DrawDashEllipse(const RECT& rc, const SIZE& radius, const DxColor& col, double size);

		void	FillRectangle(const RECT& rc, const DxColor& col);
		void	FillRoundedRectangle(const RECT& rc, const SIZE& radius, const DxColor& col);
		void	FillEllipse(const RECT& rc, const SIZE& radius, const DxColor& col);

		void	FillRectangle(const RECT& rc, CDxEffects* pEffects);
		void	FillRoundedRectangle(const RECT& rc, const SIZE& radius, CDxEffects* pEffects);
		void	FillEllipse(const RECT& rc, const SIZE& radius, CDxEffects* pEffects);

		void	FillBaseShape(const BaseShape& shape, const DxColor& col);
		void	DrawBaseShape(const BaseShape& shape, const DxColor& col, double size);
		void	DrawDashBaseShape(const BaseShape& shape, const DxColor& col, double size);

		//
		// ����λͼ
		//
		void	DrawBitmap(const RECT& rc, CDxEffects* pEffects);
		void	DrawBitmap(const RECT& rc, const MString& bitmap, int w = -1, int h = -1);


		//
		// �����ı�
		//
		void	DrawText(const MString& Text,const RECT& rc, CDxEffects* pEffects);
		void	DrawText(const MString& Text, const RECT& rc, const DxColor& col, const DXFontInfo& font, DXAlignment alignt);
		void	DrawTextWithClip(const MString& Text, const RECT& rc, CDxEffects* pEffects, const RECT& cliprc = { 0, 0, 0, 0 });


		//
		// ����ӿڣ���Ҫ���ڻ�ȡ�ı��Ĺ����Ϣ
		//
		bool	QueCaretInformation(const MString& Text, const RECT& rc, CDxEffects* pEffects, const POINT& pt, int& index, POINT& outpt, double& outHeight, DxColor& outCol, bool& isTrailingHit, DXDrawTextInfo& metrics);
		bool	QueCaretInformation(const MString& Text, const RECT& rc, CDxEffects* pEffects, int index, bool isTrailingHit, POINT& outpt, double& outHeight, DXDrawTextInfo& metrics);

		//
		// ����ӿڣ����ڼ�������ַ�����Ҫ�ĳ���
		//
		int		GetLineTextLayoutLength(const MString& Text,  CDxEffects* pEffects);


		//
		// ���ڶԻ�������Ĳü�
		// ��BeginClipRect �� EndClipRect ֮����л��� ���ֻ����ʾ rc ָ���Ĳ���
		//
		void	BeginClipRect(const RECT& rc); 
		void	BeginClipRect(const std::vector<DxPointD>& points);
		void	EndClipRect();

		void	BeginClipRect(const RECT& rc, void*& outptr1, void*& outptr2);  // �ڻ���֮ǰ����
		void	BeginClipRect(const std::vector<DxPointD>& points, void*& outptr1, void*& outptr2);  // �ڻ���֮ǰ����
		void	EndClipRect(void* outptr1, void* outptr2);					// �ڻ������֮�����


		//
		// ��������
		//
		void	DrawLine(const DxPointD& first, const DxPointD& second, const DxColor& col, double Size);
		void	DrawLines(const std::vector<DxPointD>& points, const DxColor& col, double Size);

		void	DrawDashLine(const DxPointD& first, const DxPointD& second, const DxColor& col, double Size);
		void	DrawDashLines(const std::vector<DxPointD>& points, const DxColor& col, double Size);


		void	DrawLinesForPoint(const std::vector<DxPointD>& points, const DxColor& col, double Size);
		void	DrawLinesForCross(const std::vector<DxPointD>& points, const DxColor& col, double Size);

		void	DrawLinesForPoint(const std::vector<DxPointD>& points, const DxColor& col, const DxColor& Markcol, double Size);
		void	DrawLinesForCross(const std::vector<DxPointD>& points, const DxColor& col, const DxColor& Markcol, double Size);

		//
		// ���ƶ���
		//
		void	DrawPoint(const DxPointD& pt, double radius, const DxColor& col, double Size = 1, int roundRadius = 5, DXShape shape = Dx_Ellipse);
		void	DrawPoints(const std::vector<DxPointD>& points, double radius, const DxColor& col, double Size = 1, int roundRadius = 5, DXShape shape = Dx_Ellipse);

		void	FillPoint(const DxPointD& pt, double radius, const DxColor& col, int roundRadius = 5, DXShape shape = Dx_Ellipse);
		void	FillPoints(const std::vector<DxPointD>& points, double radius, const DxColor& col, int roundRadius = 5, DXShape shape = Dx_Ellipse);

		//
		// ���Ƽ���ͼ��
		//
		void	DrawGeometry(const std::vector<DxPointD>& points, const DxColor& col, double Size);
		void	FillGeometry(const std::vector<DxPointD>& points, const DxColor& col);


		//
		// ʹ��Ч�����������߻��Ƽ���ͼ��
		// points ʹ�õ������ rc λ��
		//
		void	DrawGeometry(const RECT& rc, const std::vector<DxPointD>& points, CDxEffects* pEffects, double size);
		void	FillGeometry(const RECT& rc, const std::vector<DxPointD>& points, CDxEffects* pEffects);

		//
		// �����ͨͼ�εĻ��ƺ���䣬��� rc ��λ��
		//
		void	DrawGeometry(const RECT& rc, const BaseShape& shape, CDxEffects* pEffects, double size);
		void	FillGeometry(const RECT& rc, const BaseShape& shape, CDxEffects* pEffects);

		//
		// ͼ�μ���
		// ������������ε����в���
		void	DrawUnionGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col, double size);
		void	FillUnionGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col);

		//
		// ������������ε��ཻ����
		//
		void	DrawIntersectGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col, double size);
		void	FillIntersectGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col);

		//
		// ������������ε����в��֣����������ֳ���
		//
		void	DrawXorGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col, double size);
		void	FillXorGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col);


		//
		// ����ֻ����ͼ��1������ͼ��2�Ĳ���
		//
		void	DrawExcludeGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col, double size);
		void	FillExcludeGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col);


		//
		// �����ͨͼ�ν�������
		//
		void	DrawUnionGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col, double size);
		void	FillUnionGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col);

		void	DrawIntersectGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col, double size);
		void	FillIntersectGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col);

		void	DrawXorGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col, double size);
		void	FillXorGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col);

		void	DrawExcludeGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col, double size);
		void	FillExcludeGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col);

		void	SetTransform(const TransformMatrix& mat);

		//
		// ����Ч��ͼ
		//
		void	DrawEffects(const RECT& rc, CDxEffects* pEffects);

	private:
		ID2D1RenderTarget*				pRenderTarget;
		CDxCharaterFormat*				pTextRender{ nullptr };
		ID2D1Layer*						p_ClipLayout{ nullptr };
		ID2D1Geometry*					p_ClipGeometry{ nullptr };
		int								m_PopLayoutCounts{ 0 };
	};
}
