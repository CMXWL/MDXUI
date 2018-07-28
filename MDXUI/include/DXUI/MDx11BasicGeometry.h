
//------------------------------------
// ���ڹ���һЩ�򵥵ļ���ͼ��
// ����ʹ��
//------------------------------------
#pragma once

#include "DxConfig.h"



class DXUI_API MDx11BasicGeometry
{
public:
	MDx11BasicGeometry();
	~MDx11BasicGeometry();

	enum DATA_TYPE{
		POSITION = 0, //��������
		NORMAL,		  //���㷨��
		TANGENT,	  //��������
		TEX,		  //��������
		INDEX		  //��������
	};

	//------------------------------------------------
	// ����ͼ�εĻ���������Ϣ
	// ����Ҫֱ����ȥ��
	// ���Ը�����Ҫ��ȡ��������
	//-----------------------------------------------
	struct Base_Vertex
	{
		Base_Vertex(){}
		Base_Vertex(const XMFLOAT3 _pos, XMFLOAT3 _normal, XMFLOAT3 _tangent, XMFLOAT2 _tex) :
			pos(_pos), normal(_normal), tangent(_tangent), tex(_tex){}

		XMFLOAT3	pos;
		XMFLOAT3	normal;
		XMFLOAT3	tangent;
		XMFLOAT2	tex;
	};

	//-------------------------------------------------
	// ���漸��ͼ�εĶ��������
	//-------------------------------------------------
	struct MeshData
	{
		std::vector<Base_Vertex>	vertices;
		std::vector<UINT>			indices;
	};


	//--------------------------------------------------------------------
	// ����һ���򵥵�������
	//--------------------------------------------------------------------
	MeshData CreateBox(float width, float height, float depth, MeshData& mesh);

	//---------------------------------------------------------------------
	// ����һ������:width, height. With m * n sub-grids.
	//---------------------------------------------------------------------
	MeshData CreateGrid(float width, float height, UINT m, UINT n, MeshData& mesh);

	//---------------------------------------------------------------------
	// ����һ��Բ����
	//---------------------------------------------------------------------
	MeshData CreateCylinder(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData& mesh);

	//---------------------------------------------------------------------
	// ���Բ������������
	//---------------------------------------------------------------------
	void  AddCylinderTopCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData& mesh);

	//---------------------------------------------------------------------
	// ���Բ������������
	//---------------------------------------------------------------------
	void AddCylinderBottomCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData& mesh);

	//--------------------------------------------------------------------
	// ����һ������
	//--------------------------------------------------------------------
	MeshData CreateSphere(float radius, int slice, int stack, MeshData& mesh);
};

