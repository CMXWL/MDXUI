
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
#include "DxConfig.h"
namespace DxUI{

	class CDxEffects;
	class CDxPainter;
	//+----------------------
	//
	// �ַ�����Ⱦ����
	//
	//+----------------------
	class DXUI_API ITextService
	{
	public:
		ITextService();
		~ITextService();
		virtual void	DealTextFormat(const MString& Text,const RECT& rc,ID2D1HwndRenderTarget* pRendertarget, CDxEffects* Effects,bool isMultLines = true);
	
		const std::vector<DXLineTextInfo>& GetDealResult() const;
		const std::vector<DXDrawTextInfo>& GetDrawTextInfo() const;
	private:
		std::vector<DXLineTextInfo>  mAllLineInfo;
		std::vector<DXDrawTextInfo>  mAllTextInfo;
		IDWriteTextLayout*			pTextLayout{ nullptr };
	};
}


