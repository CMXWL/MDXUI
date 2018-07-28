#pragma once
#include "DxDialog.h"
#include "DxPushButton.h"


namespace DxUI{
	//
	// ����Ի���
	//
	class DXUI_API CDxBoxImpl : public CDxDialog{
	public:
		CDxBoxImpl(){}
		~CDxBoxImpl(){}
		int	 Exec();
	};

	//
	//
	//
	class DXUI_API CDxErrorBox :
		public CDxBoxImpl
	{
	public:
		CDxErrorBox();
		~CDxErrorBox();

		void SetButtonText(const MString& ButtonText);
		void SetButtonIcon(const MString& ButtonIco);
		
	protected:
		void OnButton(bool isClicked, CDxWidget* sender);
	private:
		CDxPushButton  mConfirmButton;
	};


	//
	// ��ʾ�Ի���
	//
	class DXUI_API CDxInfoBox :
		public CDxBoxImpl
	{
	public:
		CDxInfoBox();
		~CDxInfoBox();

		void SetButtonText(const MString& ButtonText);
		void SetButtonIcon(const MString& ButtonIco);
	protected:
		void OnButton(bool isClicked, CDxWidget* sender);
	private:
		CDxPushButton  mConfirmButton;
	};

	//
	// ѡ��Ի���
	//
	class DXUI_API CDxQueBox :
		public CDxBoxImpl
	{
	public:
		enum ButtonID{ IID_Yes = 0, IID_Cancel };
	public:
		CDxQueBox();
		~CDxQueBox();
		void SetButtonText(ButtonID ButtonId, const MString& ButtonText);
		void SetButtonIcon(ButtonID ButtonId, const MString& ButtonIco);
	protected:
		void OnButton(bool isClicked, CDxWidget* sender);
	private:
		CDxPushButton  mConfirmButton;
		CDxPushButton  mCancelButton;
	};

	//
	// ѡ��Ի���
	//
	class DXUI_API CDxQueInfoBox :
		public CDxBoxImpl
	{
	public:
		enum ButtonID{ IID_Yes = 0, IID_No, IID_Cancel };
	public:
		CDxQueInfoBox();
		~CDxQueInfoBox();
		void SetButtonText(ButtonID ButtonId, const MString& ButtonText);
		void SetButtonIcon(ButtonID ButtonId, const MString& ButtonIco);
	protected:
		void OnButton(bool isClicked, CDxWidget* sender);
	private:
		CDxPushButton  mConfirmButton;
		CDxPushButton  mNoButton;
		CDxPushButton  mCancelButton;
	};

	extern "C" DXUI_API int DxErrorBox(const MString& Text, CDxWidget* Parent = nullptr, const MString& YesStr = "ȷ��", const MString& Title = "����");
	extern "C" DXUI_API int DxInfoBox(const MString& Text, CDxWidget* Parent = nullptr, const MString& YesStr = "ȷ��", const MString& Title = "��ʾ");
	extern "C" DXUI_API int DxQueBox(const MString& Text, CDxWidget* Parent = nullptr, const MString& YesStr = "ȷ��", const MString& NoStr = "ȡ��", const MString& Title = "ѯ��");
	extern "C"DXUI_API int DxQueInfoBox(const MString& Text, CDxWidget* Parent = nullptr, const MString& YesStr = "��", const MString& NoStr = "��", const MString& CancelStr = "ȡ��", const MString& Title = "ѡ��");
}
