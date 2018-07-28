#pragma once
#include "DxConfig.h"

namespace DxUI{
	class CDxEffects;


	struct IPainterInterface{

		//+----------------------
		//
		// Ԥ���弸������
		// ����
		// Բ�Ǿ���
		// ��Բ��
		//
		//+-----------------------
		struct BaseShape
		{
			virtual DXShape ShapeType() const = 0;
			virtual double left() const = 0;
			virtual double top() const = 0;
			virtual double right() const = 0;
			virtual double bottom() const = 0;
			virtual double radiusx() const = 0;
			virtual double radiusy() const = 0;
		};

		struct Rectangle : BaseShape {
			Rectangle(double __x, double __y, double __w, double __h) :x(__x), y(__y), w(__w), h(__h){}
			double x, y, w, h;
			DXShape ShapeType() const{ return Dx_Rectangle; }
			double left() const{ return x; }
			double top() const{ return y; }
			double right() const{ return x + w; }
			double bottom() const{ return y + h; }
			double radiusx() const{ return 0; }
			double radiusy() const{ return 0; }
		};

		struct RoundedRectangle : Rectangle{
			RoundedRectangle(double __x, double __y, double __w, double __h, double __xr, double __yr) :Rectangle(__x, __y, __w, __h), xr(__xr), yr(__yr){}
			double xr, yr;
			DXShape ShapeType() const{ return Dx_RoundedRectangle; }
			double radiusx() const{ return xr; }
			double radiusy() const{ return yr; }
		};

		struct Ellipse : RoundedRectangle{
			Ellipse(double __x, double __y, double __w, double __h, double __xr, double __yr) :RoundedRectangle(__x, __y, __w, __h, __xr, __yr){}
			DXShape ShapeType() const{ return Dx_Ellipse; }
		};

		//+-----------------------------
		//
		// ��άƽ��任����
		//
		//+-----------------------------
		struct TransformMatrix{
			FLOAT _11;
			FLOAT _12;
			FLOAT _21;
			FLOAT _22;
			FLOAT _31;
			FLOAT _32;

			TransformMatrix(){
				_11 = 1.f;
				_12 = 0.f;
				_21 = 0.f;
				_22 = 1.f;
				_31 = 0.f;
				_32 = 0.f;
			}


			TransformMatrix(FLOAT f11, FLOAT f12, FLOAT f21, FLOAT f22, FLOAT f31, FLOAT f32){
				_11 = f11;
				_12 = f12;
				_21 = f21;
				_22 = f22;
				_31 = f31;
				_32 = f32;
			}

			TransformMatrix(const D2D1_MATRIX_3X2_F& mat){
				_11 = mat._11;
				_12 = mat._12;
				_21 = mat._21;
				_22 = mat._22;
				_31 = mat._31;
				_32 = mat._32;
			}

			operator D2D1_MATRIX_3X2_F() const{
				D2D1_MATRIX_3X2_F mat;
				mat._11 = _11;
				mat._12 = _12;
				mat._21 = _21;
				mat._22 = _22;
				mat._31 = _31;
				mat._32 = _32;
				return mat;
			}

		};

		//+-------------------------------------------
		//
		// Ϊ���Ʒ��㣬����Ľӿڶ���ʵ��
		// ��Ȼ���ʵ��û���ô��Ŀ��Լ򵥵�ʵ�ּ���
		//
		//+-------------------------------------------
		virtual ~IPainterInterface(){};

		virtual void*  GetPainterEnginer() = 0;

		virtual void	BeginDraw() = 0;  // ��ʼ����
		virtual void	Clear(const DxColor& col) = 0; // ʹ���ض�ɫ�ʲ�������
		virtual void	EndDraw() = 0;  // ��������

		virtual void	DrawRectangle(const RECT& rc, const DxColor& col,double size) = 0;
		virtual void	DrawRoundedRectangle(const RECT& rc, const SIZE& radius, const DxColor& col, double size) = 0;
		virtual void	DrawEllipse(const RECT& rc, const SIZE& radius, const DxColor& col, double size) = 0;

		virtual void	DrawDashRectangle(const RECT& rc, const DxColor& col, double size) = 0;
		virtual void	DrawDashRoundedRectangle(const RECT& rc, const SIZE& radius, const DxColor& col, double size) = 0;
		virtual void	DrawDashEllipse(const RECT& rc, const SIZE& radius, const DxColor& col, double size) = 0;

		virtual void	FillRectangle(const RECT& rc, const DxColor& col) = 0;
		virtual void	FillRoundedRectangle(const RECT& rc, const SIZE& radius, const DxColor& col) = 0;
		virtual void	FillEllipse(const RECT& rc, const SIZE& radius, const DxColor& col) = 0;

		virtual void	FillRectangle(const RECT& rc, CDxEffects* pEffects) = 0;
		virtual void	FillRoundedRectangle(const RECT& rc, const SIZE& radius, CDxEffects* pEffects) = 0;
		virtual void	FillEllipse(const RECT& rc, const SIZE& radius, CDxEffects* pEffects) = 0;


		virtual void	FillBaseShape(const BaseShape& shape, const DxColor& col) = 0;
		virtual void	DrawBaseShape(const BaseShape& shape, const DxColor& col, double size) = 0;
		virtual void	DrawDashBaseShape(const BaseShape& shape, const DxColor& col, double size) = 0;

		virtual void	DrawBitmap(const RECT& rc, CDxEffects* pEffects) = 0;
		virtual void	DrawBitmap(const RECT& rc, const MString& bitmap,int w = -1,int h = -1) = 0;


		virtual void	DrawText(const MString& Text, const RECT& rc, CDxEffects* pEffects) = 0;  // ֻ�����ı����������򲻹� Ч�ʸ���
		virtual void	DrawText(const MString& Text, const RECT& rc, const DxColor& col, const DXFontInfo& font,DXAlignment alignt) = 0; // ��ʹ��Ч��ֱ�ӻ���
		virtual void	DrawTextWithClip(const MString& Text, const RECT& rc, CDxEffects* pEffects, const RECT& cliprc = { 0, 0, 0, 0 }) = 0; // �����ı�����������ü�

		virtual void	BeginClipRect(const RECT& rc) = 0;  // �ڻ���֮ǰ����
		virtual void	BeginClipRect(const std::vector<DxPointD>& points) = 0;  // �ڻ���֮ǰ����
		virtual void	EndClipRect() = 0;					// �ڻ������֮�����


		//
		// ���������ӿڵ�ʹ����Ҫ��ȷ֪��void������ʲô
		//
		virtual void	BeginClipRect(const RECT& rc, void*& outptr1, void*& outptr2) = 0;  // �ڻ���֮ǰ����
		virtual void	BeginClipRect(const std::vector<DxPointD>& points, void*& outptr1, void*& outptr2) = 0;  // �ڻ���֮ǰ����
		virtual void	EndClipRect(void* outptr1, void* outptr2) = 0;					// �ڻ������֮����� BeginClipRect ���ص�����ָ�봫�ݸ� EndClipRect

		//
		// ����ӿڣ���Ҫ���ڻ�ȡ�ı��Ĺ����Ϣ
		//
		virtual bool	QueCaretInformation(const MString& Text, const RECT& rc, CDxEffects* pEffects, const POINT& pt, int& index, POINT& outpt, double& outHeight, DxColor& outCol, bool& isTrailingHit,DXDrawTextInfo& metrics) = 0;
		virtual bool	QueCaretInformation(const MString& Text, const RECT& rc, CDxEffects* pEffects, int index, bool isTrailingHit, POINT& outpt, double& outHeight, DXDrawTextInfo& metrics) = 0;


		//
		// ����ӿڣ����ڼ�������ַ�����Ҫ�ĳ���
		//
		virtual int		GetLineTextLayoutLength(const MString& Text, CDxEffects* pEffects) = 0;

		//
		// ��������
		// DrawLinesЧ�ʸ���
		//
		virtual void	DrawLine(const DxPointD& first, const DxPointD& second, const DxColor& col, double Size) = 0;
		virtual void	DrawLines(const std::vector<DxPointD>& points, const DxColor& col, double Size) = 0;


		virtual void	DrawDashLine(const DxPointD& first, const DxPointD& second, const DxColor& col, double Size) = 0;
		virtual void	DrawDashLines(const std::vector<DxPointD>& points, const DxColor& col, double Size) = 0;

		//
		// ���ƶ���
		// DrawPoints Ч�ʸ���
		//
		virtual void	DrawPoint(const DxPointD& pt, double radius, const DxColor& col, double Size = 1, int roundRadius = 5, DXShape shape = Dx_Ellipse) = 0;
		virtual void	DrawPoints(const std::vector<DxPointD>& points, double radius, const DxColor& col, double Size = 1, int roundRadius = 5, DXShape shape = Dx_Ellipse) = 0;


		//
		// ��䶨��
		// FillPoints Ч�ʸ���
		//
		virtual void	FillPoint(const DxPointD& pt, double radius, const DxColor& col, int roundRadius = 5, DXShape shape = Dx_Ellipse) = 0;
		virtual void	FillPoints(const std::vector<DxPointD>& points, double radius, const DxColor& col, int roundRadius = 5, DXShape shape = Dx_Ellipse) = 0;
		

		//
		// ���ƶ����
		//
		virtual void	DrawGeometry(const std::vector<DxPointD>& points, const DxColor& col, double size) = 0;
		virtual void	FillGeometry(const std::vector<DxPointD>& points, const DxColor& col) = 0;

		//
		// ʹ��Ч�����������߻��Ƽ���ͼ��
		// points ʹ�õ������ rc λ��
		//
		virtual void	DrawGeometry(const RECT& rc, const std::vector<DxPointD>& points, CDxEffects* pEffects, double size) = 0;
		virtual void	FillGeometry(const RECT& rc, const std::vector<DxPointD>& points, CDxEffects* pEffects) = 0;

		//
		// �����ͨͼ�εĻ��ƺ���䣬��� rc ��λ��
		//
		virtual void	DrawGeometry(const RECT& rc, const BaseShape& shape, CDxEffects* pEffects, double size) = 0;
		virtual void	FillGeometry(const RECT& rc, const BaseShape& shape, CDxEffects* pEffects) = 0;

		//
		// ͼ�μ���
		// ������������ε����в���
		//
		virtual void	DrawUnionGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col, double size) = 0;
		virtual void	FillUnionGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col) = 0;
		

		//
		// ������������ε��ཻ����
		//
		virtual void	DrawIntersectGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col, double size) = 0;
		virtual void	FillIntersectGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col) = 0;

		//
		// ������������ε����в��֣����������ֳ���
		//
		virtual void	DrawXorGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col, double size) = 0;
		virtual void	FillXorGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col) = 0;


		//
		// ����ֻ����ͼ��1������ͼ��2�Ĳ���
		//
		virtual void	DrawExcludeGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col, double size) = 0;
		virtual void	FillExcludeGeometry(const std::vector<DxPointD>& points1, const std::vector<DxPointD>& points2, const DxColor& col) = 0;


		//
		// �����ͨͼ�ν�������
		//
		virtual void	DrawUnionGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col, double size) = 0;
		virtual void	FillUnionGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col) = 0;

		virtual void	DrawIntersectGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col, double size) = 0;
		virtual void	FillIntersectGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col) = 0;

		virtual void	DrawXorGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col, double size) = 0;
		virtual void	FillXorGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col) = 0;

		virtual void	DrawExcludeGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col, double size) = 0;
		virtual void	FillExcludeGeometry(const BaseShape& shape1, const BaseShape& shape2, const DxColor& col) = 0;


		//
		// �任
		// 
		virtual void	SetTransform(const TransformMatrix& mat) = 0;

		//
		// ����Ч��ͼ
		//
		virtual void	DrawEffects(const RECT& rc, CDxEffects* pEffects) = 0;
	};


}