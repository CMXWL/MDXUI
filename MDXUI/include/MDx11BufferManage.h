

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



//------------------------------------------------
//  �������ڹ���dx11�õ��ĸ���buffer
//  ������Ҫ����:
//  ����buffer 
//  ����buffer
//  ������Դbuffer
//  ������Դbuffer
//  ����buffer,
//-----------------------------------------------

#pragma once

#include "DxConfig.h"

class DXUI_API MDx11BufferManage
{
public:
	MDx11BufferManage(ID3D11Device*	d3dDevice);
	virtual ~MDx11BufferManage();

	MDx11BufferManage(const MDx11BufferManage&) = delete;
	MDx11BufferManage& operator=(const MDx11BufferManage&) = delete;

	//
	// ��device
	// ��Ϊ����buffer��Ҫ�õ�device
	//
	void  dx_BindDevice(ID3D11Device*	d3dDevice);

	void dx_Clear();

	void dx_ReleaseBuffer(ID3D11Buffer*& buffer);

    //
    // ������̬buffer
    //
    template<class T>
    ID3D11Buffer* dx_CreateDynamicBuffer(unsigned count,unsigned bindflag = D3D11_BIND_VERTEX_BUFFER){
        ID3D11Buffer* pDynamicBuffer;
        D3D11_BUFFER_DESC pointBufDesc;

        pointBufDesc.ByteWidth = sizeof(T)* count;
        pointBufDesc.Usage = D3D11_USAGE_DYNAMIC;
        pointBufDesc.BindFlags = bindflag;
        pointBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        pointBufDesc.MiscFlags = 0;
        HRESULT hr = p_d3dDevice->CreateBuffer(&pointBufDesc, nullptr, &pDynamicBuffer);
        if (FAILED(hr)){
            throw std::runtime_error("Create Dynamic Buffer fail.......");
        }
        return pDynamicBuffer;
    }

	template<class T>
	ID3D11Buffer* dx_CreateDynamicBuffer(unsigned count, ID3D11Buffer*& outBuffer,unsigned bindflag = D3D11_BIND_VERTEX_BUFFER){
		safe_release(outBuffer);
		D3D11_BUFFER_DESC pointBufDesc;
		pointBufDesc.ByteWidth = sizeof(T)* count;
		pointBufDesc.Usage = D3D11_USAGE_DYNAMIC;
		pointBufDesc.BindFlags = bindflag;
		pointBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		pointBufDesc.MiscFlags = 0;
		HRESULT hr = p_d3dDevice->CreateBuffer(&pointBufDesc, nullptr, &outBuffer);
		if (FAILED(hr)){
			throw std::runtime_error("Create Dynamic Buffer fail.......");
		}
		return outBuffer;
	}

	//
	// ��������buffer�����ұ������
	//
	template<typename T>
	ID3D11Buffer*  dx_CreateVectexBuffer(T* points, unsigned count, D3D11_USAGE usage = D3D11_USAGE_DEFAULT){
		if (p_d3dDevice){
			D3D11_BUFFER_DESC buffer_desc;
			ZeroMemory(&buffer_desc, sizeof(buffer_desc));
			buffer_desc.Usage = usage;
			buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			buffer_desc.ByteWidth = sizeof(T)* count;

			D3D11_SUBRESOURCE_DATA res_data;
			ZeroMemory(&res_data, sizeof(res_data));
			res_data.pSysMem = points;

			ID3D11Buffer* vertex_buffer{ nullptr };

			HRESULT hr = p_d3dDevice->CreateBuffer(&buffer_desc, &res_data, &vertex_buffer);
			if (FAILED(hr)){
				MString par = MString::Format(L"CreateBuffer Failed\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
				throw std::runtime_error(par);
			}
			return vertex_buffer;
		}
		else{
			return nullptr;
		}
	}

	//
	// ʹ�øú���������buffer������
	//
	template<typename T>
	ID3D11Buffer*  dx_CreateVectexBuffer(T* points, unsigned count, ID3D11Buffer*& outVertex,D3D11_USAGE usage = D3D11_USAGE_DEFAULT){
		if (p_d3dDevice){
			D3D11_BUFFER_DESC buffer_desc;
			ZeroMemory(&buffer_desc, sizeof(buffer_desc));
			buffer_desc.Usage = usage;
			buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			buffer_desc.ByteWidth = sizeof(T)* count;

			D3D11_SUBRESOURCE_DATA res_data;
			ZeroMemory(&res_data, sizeof(res_data));
			res_data.pSysMem = points;
			safe_release(outVertex);
			HRESULT hr = p_d3dDevice->CreateBuffer(&buffer_desc, &res_data, &outVertex);
			if (FAILED(hr)){
				MString par = MString::Format(L"CreateBuffer Failed\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
				throw std::runtime_error(par);
			}
			return outVertex;
		}
		else{
			return nullptr;
		}
	}

	//
	// ���XMFLOAT3�ṩ���ػ��汾
	//
	ID3D11Buffer*  dx_CreateVectexBuffer(XMFLOAT3* points, unsigned count,\
		D3D11_USAGE usage = D3D11_USAGE_DEFAULT);

	

	//
	// ��������buffer
	//
	template<typename T,typename U>
	std::pair<ID3D11Buffer*, ID3D11Buffer*> dx_CreateIndexBuffer(T* points, \
		unsigned points_count, U* indexs, unsigned indexs_count, D3D11_USAGE usage = D3D11_USAGE_DEFAULT){
		if (p_d3dDevice){
			//
			// �ȴ������㻺��
			//
			D3D11_BUFFER_DESC buffer_desc;
			ZeroMemory(&buffer_desc, sizeof(buffer_desc));
			buffer_desc.Usage = usage;
			buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			buffer_desc.ByteWidth = sizeof(T)* points_count;

			D3D11_SUBRESOURCE_DATA res_data;
			ZeroMemory(&res_data, sizeof(res_data));
			res_data.pSysMem = points;

			ID3D11Buffer* vertex_buffer{ nullptr };
			HRESULT hr = p_d3dDevice->CreateBuffer(&buffer_desc, &res_data, &vertex_buffer);
			if (FAILED(hr)){
				MString par = MString::Format(L"CreateBuffer Failed\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
				throw std::runtime_error(par);
			}

			ZeroMemory(&buffer_desc, sizeof(buffer_desc));
			buffer_desc.Usage = usage;
			buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			buffer_desc.ByteWidth = sizeof(U)* indexs_count;
			buffer_desc.CPUAccessFlags = 0;

			ZeroMemory(&res_data, sizeof(res_data));
			res_data.pSysMem = indexs;

			ID3D11Buffer* index_buffer{ nullptr };
			hr = p_d3dDevice->CreateBuffer(&buffer_desc, &res_data, &index_buffer);
			if (FAILED(hr)){
				MString par = MString::Format(L"CreateBuffer Failed\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
				throw std::runtime_error(par);
			}
			return std::make_pair(vertex_buffer, index_buffer);
		}
		else{
			return std::make_pair(nullptr, nullptr);
		}
	}

	//
	// IMMUTABLE
	//
	template<typename T>
	ID3D11Buffer* dx_CreateIndexBuffer(T* __data, size_t size, D3D11_USAGE usage = D3D11_USAGE_DEFAULT){
		if (p_d3dDevice == nullptr)
			return nullptr;

		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.Usage = usage;
		buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buffer_desc.ByteWidth = sizeof(T)* size;
		buffer_desc.CPUAccessFlags = 0;
		buffer_desc.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA res_data;
		res_data.pSysMem = __data;
		ID3D11Buffer* index_buffer{ nullptr };
		HRESULT hr = p_d3dDevice->CreateBuffer(&buffer_desc, &res_data, &index_buffer);
		if (FAILED(hr)){
			MString par = MString::Format(L"CreateBuffer Failed\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
			throw std::runtime_error(par);
		}
		return index_buffer;
	}

	template<typename T>
	ID3D11Buffer* dx_CreateIndexBuffer(T* __data, size_t size, ID3D11Buffer*& outbuffer,D3D11_USAGE usage = D3D11_USAGE_DEFAULT){
		if (p_d3dDevice == nullptr)
			return nullptr;

		safe_release(outbuffer);
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.Usage = usage;
		buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buffer_desc.ByteWidth = sizeof(T)* size;
		buffer_desc.CPUAccessFlags = 0;
		buffer_desc.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA res_data;
		res_data.pSysMem = __data;

		HRESULT hr = p_d3dDevice->CreateBuffer(&buffer_desc, &res_data, &outbuffer);
		if (FAILED(hr)){
			MString par = MString::Format(L"CreateBuffer Failed\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
			safe_release(outbuffer);
			return outbuffer;
		}
		return outbuffer;
	}



	//
	// ����buffer�ĸ��²���
	// ����buffer�����ǿ��Է��ʵ�
	// Ҳ����˵
	// ��buffer�����Ͳ�����default����
	// ������һ��ʹ��ʱ�����а���
	// ��ȡ��Ҫ���µ�bufferָ��֮���ڶ�д�����Ҫ����
	// dx_EndUpdateBuffer()����
	// map_type ��ʾӳ������ͣ�Ĭ�������ʹ���·�����ڴ棬��ԭ���ڴ涪��
	// D3D11_MAP_WRITE_NO_OVERWRITE ��ʾ���Ǹ��µ��ڴ���δ��ʼ���Ĳ��֣������ڸ��µ�ͬʱ������Ⱦ
	// D3D11_MAP_READ ��buffer��GPU ������CPU��system�ڴ���,�����൱����Ч��
	// start_pos ����һ���ڴ�Ķ�λ�㣬��������ֻ��Ҫ��ȡһ�����ڴ���и������ǾͿ���ͨ���ò���ָ��
	// flag ͨ��Ϊ0��������Բο�SDK�ĵ�
	//
	template<typename T>
	T* dx_GetNeedUpdateBuffer(ID3D11DeviceContext* pContex,ID3D11Resource* src_buffer, unsigned start_pos = 0, \
		D3D11_MAP map_type = D3D11_MAP_WRITE_DISCARD, unsigned flag = 0)
	{
		if (!pContex || !src_buffer){
			MString par = MString::Format(L"CreateBuffer Failed\nID3D11DeviceContext is null or src_buffer is null\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
			throw std::runtime_error(par);
		}
		D3D11_MAPPED_SUBRESOURCE __data;
		HRESULT hr = pContex->Map(src_buffer, start_pos, map_type, flag, &__data);
		if (FAILED(hr)){
			MString par = MString::Format(L"Map Failed\nID3D11DeviceContext is null or src_buffer is null\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
			throw std::runtime_error(par);
		}
		T* __result_ptr = reinterpret_cast<T*>(__data.pData);
		return __result_ptr;
	}
	


	//
	// �ú����ڵ��� dx_GetNeedUpdateBuffer ֮����÷�����Ч
	// ������øú�����������
	//
	void dx_EndUpdateBuffer(ID3D11DeviceContext* pContex, ID3D11Resource* src_buffer,unsigned start_pos = 0);


	//
	// ���XMFLOAT3�ṩ���ػ��汾
	//
	std::pair<ID3D11Buffer*, ID3D11Buffer*> dx_CreateIndexBuffer(XMFLOAT3* points, \
		unsigned points_count, unsigned* indexs, unsigned indexs_count,  D3D11_USAGE usage = D3D11_USAGE_DEFAULT);
		 
	//
	// ����buffer
	//
	ID3D11Buffer* dx_CreateConstBuffer(size_t size);

	//
	// Ostream_Buffer
	//
	template<class T>
	ID3D11Buffer* dx_CreateOStremBuffer(T t, size_t size){
		assert(p_d3dDevice);
		ID3D11Buffer* p_os_buffer{ nullptr };
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.ByteWidth = sizeof(T)* size;
		HRESULT hr = p_d3dDevice->CreateBuffer(&buffer_desc, nullptr, &p_os_buffer);
		if (FAILED(hr)){
			MString par = MString::Format(L"CreateBuffer Failed\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
			throw std::runtime_error(par);
		}
		return p_os_buffer;
	}



	//
	// InstanceBuffer
	//
	template<class T>
	ID3D11Buffer* dx_CreateInstanceBuffer(size_t count, D3D11_BUFFER_DESC* buffer_desc = nullptr){
		D3D11_BUFFER_DESC  desc;
		if (buffer_desc){
			desc = *buffer_desc;
		}
		else{
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.ByteWidth = sizeof(T)*count;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;
		}
		ID3D11Buffer* instance_buffer{ nullptr };
		HRESULT hr = p_d3dDevice->CreateBuffer(&desc, nullptr, &instance_buffer);
		if (FAILED(hr)){
			MString par = MString::Format(L"CreateBuffer Failed\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
			throw std::runtime_error(par);
		}
		return instance_buffer;
	}



	template<class T>
	ID3D11Buffer* dx_CreateInstanceBuffer(size_t count, ID3D11Buffer* outbuffer, D3D11_BUFFER_DESC* buffer_desc = nullptr){
		D3D11_BUFFER_DESC  desc;
		if (buffer_desc){
			desc = *buffer_desc;
		}
		else{
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.ByteWidth = sizeof(T)*count;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;
		}
		safe_release(outbuffer);
		HRESULT hr = p_d3dDevice->CreateBuffer(&desc, nullptr, &outbuffer);
		if (FAILED(hr)){
			MString par = MString::Format(L"CreateBuffer Failed\nFILE:%1\nFun:%2\nLine:%3", __FILE__, __FUNCTION__, __LINE__);
			throw std::runtime_error(par);
		}
		return outbuffer;
	}


	//
	// ����������Դ
	// ��������ͬʱ�������������
	//
	std::pair<ID3D11ShaderResourceView*, ID3D11SamplerState*> dx_CreateTexTureResouce(const std::string& filename, \
		D3DX11_IMAGE_LOAD_INFO* pinfo = nullptr, \
		ID3DX11ThreadPump* pthread = nullptr, HRESULT* rel = nullptr);



	//
	// ֻ����һ������
	//
	ID3D11ShaderResourceView* dx_CreateTexTureResouceOnly(const std::string& filename,
		D3DX11_IMAGE_LOAD_INFO* pinfo = nullptr, \
		ID3DX11ThreadPump* pthread = nullptr, HRESULT* rel = nullptr);



	//
	// ������������
	//
	ID3D11ShaderResourceView* dx_CreateTexture2DArraySRV(ID3D11DeviceContext* pContex,\
		std::vector<std::string>& filenames, \
		DXGI_FORMAT format = DXGI_FORMAT_FROM_FILE, \
		unsigned filter = D3DX11_FILTER_NONE,\
		unsigned mipFilter = D3DX11_FILTER_LINEAR, \
		D3DX11_IMAGE_LOAD_INFO* pinfo = nullptr, \
		ID3DX11ThreadPump* pthread = nullptr,\
		HRESULT* rel = nullptr);


	//
	// ����1D�����������Դ
	//
	ID3D11ShaderResourceView* CreateRandomTexture1DSRV(ID3D11Device* device);


	//
	// �������������
	//
	ID3D11SamplerState* dx_CreatTextureSampler(D3D11_SAMPLER_DESC* sample_desc = nullptr);
	
private:
	ID3D11Device*			p_d3dDevice;

	//
	// ������Դ
	// ���Կ���Ϊ��ʹ���߹���
	//
	ID3D11ShaderResourceView* p_texture_resource;//������Դ
	ID3D11SamplerState*		  p_texture_sampler; //���������	
};

