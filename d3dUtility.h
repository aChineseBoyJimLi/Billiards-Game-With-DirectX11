#pragma once
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#ifndef __d3dUtilityH__
#define __d3dUtilityH__

#include <Windows.h>

// ��ѧ��
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

// DirectX11 ��ؿ�
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dx11effect.h>

#include "DirectXTex.h"

using namespace DirectX;

namespace d3d {
	// ��ʼ��D3D
	bool InitD3D(HINSTANCE hInstance, int width, int height,
		ID3D11RenderTargetView** renderTargetView, // Ŀ����Ⱦ��ͼ�ӿ�
		ID3D11DeviceContext** immediateContext,	   // ִ��������
		IDXGISwapChain** swapChain,				   // �������ӿ�
		ID3D11Device** device,
		ID3D11Texture2D** depthStencilBuffer,
		ID3D11DepthStencilView** depthStencilView);

	// ��Ϣѭ��
	int EnterMsgLoop(bool(*ptr_display)(float timeDelta));

	// �ص�����
	LRESULT CALLBACK WndProc(
		HWND,
		UINT msg,
		WPARAM,
		LPARAM lParam
	);

	// ����ṹ
	struct Vertex
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Norm;
		XMFLOAT2 Tex;
	};
}


#endif // !__d3dUtilityH__

