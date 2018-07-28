//----------------------------------------------
// �����ֶ���
// ������ɫ��
// ������ɫ��
//---------------------------------------------
#pragma once
#include "DxConfig.h"

class DXUI_API MDx11LayoutManage
{
public:
	MDx11LayoutManage(ID3D11Device*	d3dDevice);
	virtual ~MDx11LayoutManage();
	MDx11LayoutManage(const MDx11LayoutManage&) = delete;
	MDx11LayoutManage& operator=(const MDx11LayoutManage&) = delete;

	//------------------------------------------------
	// ��device
	// ��Ϊ����buffer��Ҫ�õ�device
	//------------------------------------------------
	void  dx_BindDevice(ID3D11Device*	d3dDevice);

	void dx_Clear();

	//---------------------------------------------------
	// ����fx�ļ�
	// ����hlsl�ļ�
	//---------------------------------------------------
	ID3DX11Effect* dx_FxComplieFile(const std::string& filename, const char* vs_fun = "fx_5_0", \
		unsigned flag1 = D3D10_SHADER_ENABLE_STRICTNESS,ID3DX11ThreadPump* pthread = nullptr);
	bool dx_HlslComplerFilePS(const std::string& filename,const char* fun_name,const char* vs_fun,\
		unsigned flag1 = D3D10_SHADER_ENABLE_STRICTNESS, ID3DX11ThreadPump* pthread = nullptr);
	bool dx_HlslComplerFileVS(const std::string& filename, const char* fun_name, const char* vs_fun, \
		unsigned flag1 = D3D10_SHADER_ENABLE_STRICTNESS, ID3DX11ThreadPump* pthread = nullptr);


	//---------------------------------------------------
	// ͨ���ַ�����ȡEffect��һЩ��ز���
	//---------------------------------------------------
	ID3DX11EffectMatrixVariable* dx_GetWVPMatrix(const std::string& effect_flag_name);
	ID3DX11EffectMatrixVariable* dx_GetMatrixFromEF(const std::string& name);
	ID3DX11EffectVectorVariable* dx_GetVectorFromEF(const std::string& name);
	ID3DX11EffectConstantBuffer* dx_GetConstBufferFromEF(const std::string& name);
	ID3DX11EffectShaderResourceVariable* dx_GetShaderResourceFromEF(const std::string& name);
	ID3DX11EffectDepthStencilViewVariable* dx_GetDepthStenciViewFromEF(const std::string& name);
	ID3DX11EffectDepthStencilVariable*	dx_GetDepthStenciFromEF(const std::string& name);
	ID3DX11EffectScalarVariable*	dx_GetScaleFromEF(const std::string& name);
	ID3DX11EffectSamplerVariable*	dx_GetSamplerFromEF(const std::string& name);
	ID3DX11EffectShaderVariable*	dx_GetShaderFromEF(const std::string& name);
	ID3DX11EffectStringVariable*	dx_GetStringFromEF(const std::string& name);


	ID3DX11EffectTechnique* dx_GetTechFromEF(const std::string& name);
	ID3DX11EffectTechnique* dx_GetTechFromEF(unsigned index);

	D3DX11_TECHNIQUE_DESC  dx_GetTichDescFromEF(const std::string& name);
	D3DX11_TECHNIQUE_DESC  dx_GetTichDescFromEF(unsigned index);

	unsigned			    dx_GetPassNum(const std::string& name);
	unsigned			    dx_GetPassNum(unsigned index);
	ID3DX11EffectPass*		dx_GetPassFromEF(const std::string& name, unsigned index);
	ID3DX11EffectPass*		dx_GetPassFromEF(unsigned index1, unsigned index2);
	ID3DX11EffectPass*		dx_GetPassFromEF(const std::string& name, const std::string& name2);
	ID3DX11EffectPass*		dx_GetPassFromEF(unsigned index1, const std::string& name);
	//---------------------------------------------------
	// ����wvp����
	//---------------------------------------------------
	void dx_SetMatrix(XMMATRIX* m);


	//----------------------------------------------------
	// ��������
	//----------------------------------------------------
	ID3D11InputLayout* dx_CreatInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, unsigned count);
	ID3D11InputLayout* dx_CreatInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, \
		unsigned count,const std::string& tech_name,int tech_num = 0);

	//---------------------------------------------------
	// ��ȡID3D11PixelShader ID3D11VertexShader
	//---------------------------------------------------
	ID3D11PixelShader* dx_GetPixShader();
	ID3D11VertexShader* dx_GetVertexShade();

	//---------------------------------------------------
	// ʹ��Effect���
	//---------------------------------------------------
	

private:
	ID3D11Device*	     p_d3dDevice;
	ID3D11InputLayout*   p_input_layout;
	ID3D11PixelShader*	 p_pixe1_shader;
	ID3D11VertexShader*	 p_vertex_shader;

	ID3D10Blob*			 p_Tech_Blod;
	ID3D10Blob*			 p_vertex_blod;
	//----------------------------------------------
	// D3D11 Effect ���
	//----------------------------------------------
	ID3DX11Effect*				 p_effect;
	ID3DX11EffectMatrixVariable* p_fxWorldViewProj;

	//-----------------------------------------------
	// ������Դ
	//------------------------------------------------
	std::vector<D3DX11_TECHNIQUE_DESC*> m_tich_desc_manage;
};

