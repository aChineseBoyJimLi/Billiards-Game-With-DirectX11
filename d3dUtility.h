#pragma once
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#ifndef __d3dUtilityH__
#define __d3dUtilityH__

#include <Windows.h>

// 数学库
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

// DirectX11 相关库
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dx11effect.h>

#include "DirectXTex.h"

using namespace DirectX;

namespace d3d {
	// 初始化D3D
	bool InitD3D(HINSTANCE hInstance, int width, int height,
		ID3D11RenderTargetView** renderTargetView, // 目标渲染视图接口
		ID3D11DeviceContext** immediateContext,	   // 执行上下文
		IDXGISwapChain** swapChain,				   // 交换连接口
		ID3D11Device** device,
		ID3D11Texture2D** depthStencilBuffer,
		ID3D11DepthStencilView** depthStencilView);

	// 消息循环
	int EnterMsgLoop(bool(*ptr_display)(float timeDelta));

	// 回调函数
	LRESULT CALLBACK WndProc(
		HWND,
		UINT msg,
		WPARAM,
		LPARAM lParam
	);

	// 顶点结构
	struct Vertex
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Norm;
		XMFLOAT2 Tex;
	};
}


#endif // !__d3dUtilityH__

