//=====================================================//
Texture2D MWindowTexture;
matrix   MWorldMatrix;  // ����任����
matrix   MVPMatrix;	// ��ͼͶӰ����
matrix   MWVPMatrix;	// ����任��ͼͶӰ����
float3   EyePosW;
//
// �����ļ�����
//
cbuffer cbFixed
{
	float2 gTexC[4] = 
	{
		float2(0.0f, 1.0f),
		float2(0.0f, 0.0f),
		float2(1.0f, 1.0f),
		float2(1.0f, 0.0f)
	};
};

//
// ���붥������
//
struct VSSceneIn
{
	float3 pos : POSITION;
	float4 colour : COLOR;
    	float2 tex : TEXCOORD;
};

//
// ��������
//
struct VertexOut
{
	float3 CenterW : POSITION;
	float4 Colour  : COLOR;
	float2 SizeW   : SIZE;
};

//
// ���ζ�������
//
struct GeoOut
{
	float4 PosH    : SV_POSITION;
	float4 Colour  : COLOR;
    float2 Tex     : TEXCOORD;
    uint   PrimID  : SV_PrimitiveID;
};

VertexOut VS(VSSceneIn vin)
{
	VertexOut vout 	= (VertexOut)0;
	vout.CenterW 	= mul(float4(vin.pos,1),MWorldMatrix).xyz;
	vout.Colour  	= vin.colour;
	vout.SizeW   	= vin.tex;
	return vout;
}

//
// ������������
//
struct PSSceneIn
{
	float4 pos : SV_Position;
	float4 colour : COLOR;
	float2 tex : TEXCOORD;
};


//
// ���ģ������
//
DepthStencilState DisableDepth
{
	DepthEnable = FALSE;
	DepthWriteMask = ZERO;
};


//
// ���ģ������
//
DepthStencilState LessEqualDSS
{
	DepthEnable = TRUE; 
	DepthFunc = LESS_EQUAL; 
}; 

BlendState AlphaBlend 
{
	AlphaToCoverageEnable = false; 
	BlendEnable[0] = true; 
	SrcBlendAlpha = INV_DEST_ALPHA;	
	DestBlendAlpha = ONE; 
	SrcBlend = SRC_ALPHA; 
	DestBlend = INV_SRC_ALPHA; 
};

//
// �����������
//
SamplerState WindowSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Border;
	AddressV = Border;
};

//
// ��դ��
//
RasterizerState Rasterstate
{
	DepthClipEnable = false;
	FillMode = Solid;
	CullMode = Back;
	FrontCounterClockwise = false;
	ScissorEnable = false;
};

//
// ������ɫ��
//
PSSceneIn VSMain(VSSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0.0;
	output.pos = mul(float4(input.pos,1),MWVPMatrix);
	output.tex = input.tex;
	output.colour = input.colour;
	return output;
}

//
// ������ɫ��
//
float4 PSMain(PSSceneIn input) : SV_Target
{
	return input.colour;
	float4 colour = MWindowTexture.Sample(WindowSampler, input.tex);
	return input.colour*colour;
}


//
// ������ɫ��
//
[maxvertexcount(4)]
void GS(point VertexOut gin[1], uint primID : SV_PrimitiveID, inout TriangleStream<GeoOut> triStream)
{	
	//
	// ���漼��
	//
	float3 up 	= float3(0.0f, 1.0f, 0.0f);
	float3 look 	= EyePosW - gin[0].CenterW;
	look.y 		= 0.0f; 
	look 		= normalize(look);
	float3 right 	= cross(up, look);

	//
	//�����ı��ε��ĸ�����.
	//
	float halfWidth  = 0.5f*gin[0].SizeW.x;
	float halfHeight = 0.5f*gin[0].SizeW.y;


	
	float4 v[4];
	v[0] = float4(gin[0].CenterW + halfWidth*right - halfHeight*up, 1.0f);
	v[1] = float4(gin[0].CenterW + halfWidth*right + halfHeight*up, 1.0f);
	v[2] = float4(gin[0].CenterW - halfWidth*right - halfHeight*up, 1.0f);
	v[3] = float4(gin[0].CenterW - halfWidth*right + halfHeight*up, 1.0f);

	float dx = halfWidth;
	float dy = halfHeight;
	float __x = gin[0].CenterW.x;
	float __y = gin[0].CenterW.y;
	float __z = gin[0].CenterW.z;

	v[0] = float4(__x - dx ,__y + dy,__z,1.0f);
	v[1] = float4(__x + dx ,__y + dy,__z,1.0f);
	v[2] = float4(__x - dx ,__y - dy,__z,1.0f);
	v[3] = float4(__x + dx ,__y - dy,__z,1.0f);

	GeoOut gout = (GeoOut)0;
	[unroll]
	for(int i = 0; i < 4; ++i)
	{
		gout.PosH	  = mul(v[i], MVPMatrix);
		gout.Colour   = gin[0].Colour;
		gout.Tex      = gTexC[i];
		gout.PrimID   = primID;
		triStream.Append(gout);
	}
}

//
// ������ɫ��
//
float4 PS(GeoOut input) : SV_Target
{
	return input.Colour;
}

//
// ͨ��
//
technique11 MDx11WindowTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VSMain())); 
		SetGeometryShader(NULL); 
		SetPixelShader(CompileShader(ps_5_0, PSMain())); 
		SetDepthStencilState(LessEqualDSS, 0); 
		SetRasterizerState(Rasterstate); 
	}
}

technique11 MDx11WindowTechWithGS
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetGeometryShader(CompileShader(gs_5_0, GS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
        SetDepthStencilState(DisableDepth, 0);
		SetBlendState(AlphaBlend, float4(0, 0, 0, 0), 0xFFFFFFFF);
		SetRasterizerState(Rasterstate); 
    }
}


