#include "d3dUtility.h"

//����ȫ�ֵ�ָ��
ID3D11Device* device = NULL;//D3D11�豸�ӿ�
IDXGISwapChain* swapChain = NULL;//�������ӿ�
ID3D11DeviceContext* immediateContext = NULL;
ID3D11RenderTargetView* renderTargetView = NULL;//��ȾĿ����ͼ  
ID3D11DepthStencilView* depthStencilView;  //���ģ����ͼ
ID3D11Texture2D* depthStencilBuffer;       //��Ȼ���

//Effect���ȫ��ָ��
ID3DX11Effect* effect;
ID3DX11EffectTechnique* technique;
ID3D11InputLayout* vertexLayout;

int verticeLength;


//������������ϵ����
XMMATRIX world;         //��������任�ľ���
XMMATRIX view;          //���ڹ۲�任�ľ���
XMMATRIX projection;    //����ͶӰ�任�ľ���

// ��ͼ
ID3D11ShaderResourceView* textureFloor;

// ����ṹ
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};


//**************����Ϊ��ܺ���******************
bool Setup()
{
	HRESULT hr = S_OK;
	ID3DBlob* pTechBlob = NULL;
	hr = D3DCompileFromFile(L"Shader.fx", NULL, NULL, NULL, "fx_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &pTechBlob, NULL);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"fx�ļ�����ʧ��", L"Error", MB_OK); //�����ȡʧ�ܣ�����������Ϣ
		return hr;
	}


	hr = D3DX11CreateEffectFromMemory(pTechBlob->GetBufferPointer(),
		pTechBlob->GetBufferSize(), 0, device, &effect);

	if (FAILED(hr))
	{
		::MessageBox(NULL, L"����Effectʧ��", L"Error", MB_OK);  //����ʧ�ܣ�����������Ϣ
		return hr;
	}

	// ��ȡ��ͼ
	wchar_t const* filename1 = L"ToolTableTexture.bmp";
	wchar_t ext1[_MAX_EXT] = {};
	_wsplitpath_s(filename1, nullptr, 0, nullptr, 0, nullptr, 0, ext1, _MAX_EXT);
	ScratchImage image1;
	LoadFromWICFile(filename1, DDS_FLAGS_NONE, nullptr, image1);
	hr = CreateShaderResourceView(device, image1.GetImages(), image1.GetImageCount(), image1.GetMetadata(), &textureFloor);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"��ȡ��ͼʧ��", L"Error", MB_OK);  //����ʧ�ܣ�����������Ϣ
		return hr;
	}
	effect->GetVariableByName("Texture")->AsShaderResource()->SetResource(textureFloor);
	technique = effect->GetTechniqueByName("TexTech");

	D3DX11_PASS_DESC passDesc;
	technique->GetPassByIndex(0)->GetDesc(&passDesc);

	// ���벼��
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = ARRAYSIZE(layout);
	hr = device->CreateInputLayout(layout, numElements, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &vertexLayout);
	immediateContext->IASetInputLayout(vertexLayout);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"����Input Layoutʧ��", L"Error", MB_OK);
		return hr;
	}

	// ���㻺��
	Vertex vertices[] = {
		{XMFLOAT3(0.0f,0.0f,-2.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(1.0f,0.0f,-1.0f), XMFLOAT2(0.0f,1.0f)},
		{XMFLOAT3(1.0f,0.0f,-2.0f), XMFLOAT2(0.0f,0.0f)},

		{XMFLOAT3(-1.0f,0.0f,-2.0f), XMFLOAT2(0.0f,0.0f)},
		{XMFLOAT3(-1.0f,0.0f,-1.0f), XMFLOAT2(0.0f,1.0f)},
		{XMFLOAT3(0.0f,0.0f,-2.0f), XMFLOAT2(1.0f,0.0f)},

		{XMFLOAT3(0.0f,0.0f,-1.0f), XMFLOAT2(1.0f,1.0f)},
		{XMFLOAT3(1.0f,0.0f,-1.0f), XMFLOAT2(0.0f,1.0f)},
		{XMFLOAT3(0.0f,0.0f,-2.0f), XMFLOAT2(1.0f,0.0f)},

		{XMFLOAT3(0.0f,0.0f,-1.0f), XMFLOAT2(1.0f,1.0f)},
		{XMFLOAT3(0.0f,0.0f,-2.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(-1.0f,0.0f,-1.0f), XMFLOAT2(0.0f,1.0f)},

		////////////////////////////////////////////////////////////////////
		{XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT2(0.3f,0.7f)},
		{XMFLOAT3(1.0f,0.0f,-1.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(0.0f,0.0f,-1.0f), XMFLOAT2(1.0f,0.7f)},

		{XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT2(0.3f,0.7f)},
		{XMFLOAT3(0.0f,0.0f,-1.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(-1.0f,0.0f,-1.0f), XMFLOAT2(1.0f,0.7f)},

		{XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(1.0f,0.0f,0.0f), XMFLOAT2(0.0f,0.0f)},
		{XMFLOAT3(1.0f,0.0f,-1.0f), XMFLOAT2(0.0f,1.0f)},

		{XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(-1.0f,0.0f,-1.0f), XMFLOAT2(0.0f,1.0f)},
		{XMFLOAT3(-1.0f,0.0f,0.0f), XMFLOAT2(0.0f,0.0f)},

		/////////////////////////////////////////////////////////////////////
		{XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(1.0f,0.0f,1.0f), XMFLOAT2(0.3f,0.7f)},
		{XMFLOAT3(1.0f,0.0f,0.0f), XMFLOAT2(1.0f,0.7f)},

		{XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(-1.0f,0.0f,0.0f), XMFLOAT2(1.0f,0.7f)},
		{XMFLOAT3(-1.0f,0.0f,1.0f), XMFLOAT2(0.3f,0.7f)},

		{XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(0.0f,0.0f,1.0f), XMFLOAT2(1.0f,0.7f)},
		{XMFLOAT3(1.0f,0.0f,1.0f), XMFLOAT2(0.3f,0.7f)},

		{XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(-1.0f,0.0f,1.0f), XMFLOAT2(0.3f,0.7f)},
		{XMFLOAT3(0.0f,0.0f,1.0f), XMFLOAT2(1.0f,0.7f)},
		
		////////////////////////////////////////////////////////////////////

		{XMFLOAT3(0.0f,0.0f,2.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(1.0f,0.0f,2.0f), XMFLOAT2(0.0f,0.0f)},
		{XMFLOAT3(1.0f,0.0f,1.0f), XMFLOAT2(0.0f,1.0f)},
		

		{XMFLOAT3(-1.0f,0.0f,2.0f), XMFLOAT2(0.0f,0.0f)},
		{XMFLOAT3(0.0f,0.0f,2.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(-1.0f,0.0f,1.0f), XMFLOAT2(0.0f,1.0f)},
		

		{XMFLOAT3(0.0f,0.0f,1.0f), XMFLOAT2(1.0f,0.7f)},
		{XMFLOAT3(0.0f,0.0f,2.0f), XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(1.0f,0.0f,1.0f), XMFLOAT2(0.3f,0.7f)},

		{XMFLOAT3(0.0f,0.0f,1.0f), XMFLOAT2(1.0f,0.7f)},
		{XMFLOAT3(-1.0f,0.0f,1.0f), XMFLOAT2(0.3f,0.7f)},
		{XMFLOAT3(0.0f,0.0f,2.0f), XMFLOAT2(1.0f,0.0f)},
		
	};
	UINT verCount = ARRAYSIZE(vertices);
	verticeLength = verCount;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * verCount;      //ע�⣺�������ﶨ����24����������Ҫ����24
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;  //ע�⣺�����ʾ�������Ƕ��㻺��
	bd.CPUAccessFlags = 0;

	//����һ��D3D11_SUBRESOURCE_DATA�������ڳ�ʼ������Դ
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;

	//����һ��ID3D11Buffer������Ϊ���㻺��
	ID3D11Buffer* vertexBuffer;
	//����CreateBuffer�������㻺��
	hr = S_OK;
	hr = device->CreateBuffer(&bd, &InitData, &vertexBuffer);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"����VertexBufferʧ��", L"Error", MB_OK);
		return hr;
	}

	UINT stride = sizeof(Vertex);                 //��ȡVertex�Ĵ�С��Ϊ���
	UINT offset = 0;                              //����ƫ����Ϊ0
	//���ö��㻺�棬�����Ľ��ͼ�ʵ��4
	immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//ָ��ͼԪ���ͣ�D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST��ʾͼԪΪ������
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

void Cleanup()
{
	//�ͷ�ȫ��ָ��
	if (renderTargetView) renderTargetView->Release();
	if (immediateContext) immediateContext->Release();
	if (swapChain) swapChain->Release();
	if (device) device->Release();
	if (vertexLayout) vertexLayout->Release();
	if (effect) effect->Release();
	if (depthStencilView) depthStencilView->Release();
}

bool Display(float timeDelta)
{
	if(device){
		float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
		immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
		immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

		world = XMMatrixIdentity();
		XMVECTOR Eye = XMVectorSet(0.0f,3.0f,-0.5f,0.0f);
		XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		view = XMMatrixLookAtLH(Eye, At, Up);
		projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 800.0f/600.0f, 0.01f, 100.0f);
		effect->GetVariableByName("World")->AsMatrix()->SetMatrix((float*)&world);
		effect->GetVariableByName("View")->AsMatrix()->SetMatrix((float*)&view);
		effect->GetVariableByName("Projection")->AsMatrix()->SetMatrix((float*)&projection);

		D3DX11_TECHNIQUE_DESC techDesc;
		technique->GetDesc(&techDesc);
		technique->GetPassByIndex(0)->Apply(0, immediateContext);
		immediateContext->Draw(verticeLength, 0);

		swapChain->Present(0, 0);
	}
	return true;
}
//**************��ܺ���******************


//
// �ص�����
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			::DestroyWindow(hwnd);
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// ������WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	if (!d3d::InitD3D(hinstance,
		800,
		600,
		&renderTargetView,
		&immediateContext,
		&swapChain,
		&device,
		&depthStencilBuffer,
		&depthStencilView))
	{
		::MessageBox(0, L"InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if (!Setup())
	{
		::MessageBox(0, L"Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop(Display);

	Cleanup();

	return 0;
}

