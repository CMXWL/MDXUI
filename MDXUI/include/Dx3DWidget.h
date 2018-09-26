

///////////////////////////////////////////////////////////////////////////////
//
// This source file is part of the MDXUI source distribution
// Copyright (C) 2017-2018 by Mengjin (sh06155@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "DxWidget.h"
#include <MTLPairEx.h>
#include "MDx11BufferManage.h"
#include "MDx11LayoutManage.h"
#include "MDx11Camera.h"

namespace DxUI{
	//+-------------------------------
	//
	// �ṩһ������ά�������Ⱦ�����
	//
	//+--------------------------------
	class DXUI_API CDx3DWidget :
		public CDxWidget
	{
		DECLARE_CLASS(CDx3DWidget)
	public:
		typedef MPairEx<DxVectorF, DxVectorF, XMFLOAT2>		MDx11PointValue;
		typedef TL::Vector<MDx11PointValue>					MDx11MeshPointType;

		static MDx11PointValue MakeValue(float x, float y, float z, float r, float g, float b, float u, float v);
		static MDx11PointValue MakeValue(const DxVectorF& p, const DxVectorF& col);
		static XMMATRIX GetRotationAnyPointMatrix(XMFLOAT3 vCenter, float x_angle, float y_angle, float z_angle);

	public:
		CDx3DWidget();
		~CDx3DWidget();


		void			CreateHwnd();
		void			CreateHwnd(HWND hwnd);

		bool			OnInitResource3D();
		void			UnInitResource();
		void			SetViewPort(const DxRectI& viewArea);

		void			SetGeomety(const DxRectI& rc);
		void			SetFocus();
		void			KillFocus();
		void			OnTimer();
		LRESULT			OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		void			OnReShape(int w, int h);
		void			OnRender();
		void			OnRendWindow(IPainterInterface* painter);
		void			SaveToFile(const MString& fileName);
		void			SetParent(CDxWidget* parent);
		HWND			GetRootHwnd() const;


		void			SetStackedWindowIsVisible(bool isVisible);
		IDXGISwapChain*			GetSwapChain();
		ID3D11Device*			GetD3DDevice();
		ID3D11DeviceContext*	GetD3DContext();
		ID3D11RenderTargetView*	GetTargetView();
		ID3D11DepthStencilView*	GetDepathStencilView();
		MDx11BufferManage*		GetBufferManager();
		MDx11LayoutManage*		GetLayoutManager();
		MDx11Camera*			GetCamera();


		
	protected:
		XMFLOAT4X4		mWorldMat;

		//+----------------------
		//
		// 3D ��Ⱦ���
		//
		//+----------------------
		ID3D11Device*				p_d3dDevice{ nullptr };
		ID3D11DeviceContext*		p_d3dContext{ nullptr };
		IDXGISwapChain*				p_swapChain{ nullptr };
		unsigned int				m_4xMsaaQuality{ 0 };
		ID3D11RenderTargetView*		p_backBufferTarget{ nullptr }; //��ȾĿ����ͼ
		ID3D11Texture2D*			p_depthTexture{ nullptr };
		ID3D11DepthStencilView*		p_depthStencilView{ nullptr };
		D3D11_VIEWPORT				m_viewport;
		MDx11Camera					mCamera;
		MDx11BufferManage*			pBufferManager{ nullptr };
		MDx11LayoutManage*			pLayoutManager{ nullptr };
	};
}


