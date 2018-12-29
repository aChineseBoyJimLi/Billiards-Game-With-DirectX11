#include "d3dUtility.h"
#include "Objects.h"
#include "Light.h"

//声明全局的指针
ID3D11Device* device = NULL;//D3D11设备接口
IDXGISwapChain* swapChain = NULL;//交换链接口
ID3D11DeviceContext* immediateContext = NULL;
ID3D11RenderTargetView* renderTargetView = NULL;//渲染目标视图  
ID3D11DepthStencilView* depthStencilView;  //深度模板视图
ID3D11Texture2D* depthStencilBuffer;       //深度缓存

//Effect相关全局指针
ID3DX11Effect* effect;
ID3DX11EffectTechnique* technique;
ID3D11InputLayout* vertexLayout;

//int verticeLength;

//声明材质和光照的全局对象
Material floorMaterial;
Light spotLight;	// 聚光灯

//声明三个坐标系矩阵
XMMATRIX world;         //用于世界变换的矩阵
XMMATRIX view;          //用于观察变换的矩阵
XMMATRIX projection;    //用于投影变换的矩阵

// 贴图
ID3D11ShaderResourceView* textureFloor;

void SetLightEffect();

using namespace d3d;


//**************以下为框架函数******************
bool Setup()
{
	HRESULT hr = S_OK;
	ID3DBlob* pTechBlob = NULL;
	hr = D3DCompileFromFile(L"Shader.fx", NULL, NULL, NULL, "fx_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &pTechBlob, NULL);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"fx文件载入失败", L"Error", MB_OK); //如果读取失败，弹出错误信息
		return hr;
	}


	hr = D3DX11CreateEffectFromMemory(pTechBlob->GetBufferPointer(),
		pTechBlob->GetBufferSize(), 0, device, &effect);

	if (FAILED(hr))
	{
		::MessageBox(NULL, L"创建Effect失败", L"Error", MB_OK);  //创建失败，弹出错误信息
		return hr;
	}

	// 读取贴图
	wchar_t const* filename1 = L"ToolTableTexture.bmp";
	wchar_t ext1[_MAX_EXT] = {};
	_wsplitpath_s(filename1, nullptr, 0, nullptr, 0, nullptr, 0, ext1, _MAX_EXT);
	ScratchImage image1;
	LoadFromWICFile(filename1, DDS_FLAGS_NONE, nullptr, image1);
	hr = CreateShaderResourceView(device, image1.GetImages(), image1.GetImageCount(), image1.GetMetadata(), &textureFloor);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"读取贴图失败", L"Error", MB_OK);  //创建失败，弹出错误信息
		return hr;
	}
	effect->GetVariableByName("Texture")->AsShaderResource()->SetResource(textureFloor);
	technique = effect->GetTechniqueByName("TexTech");

	D3DX11_PASS_DESC passDesc;
	technique->GetPassByIndex(0)->GetDesc(&passDesc);

	// 输入布局
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = ARRAYSIZE(layout);
	hr = device->CreateInputLayout(layout, numElements, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &vertexLayout);
	immediateContext->IASetInputLayout(vertexLayout);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"创建Input Layout失败", L"Error", MB_OK);
		return hr;
	}

	// 顶点缓存
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * verCount; // 这里的 verCount 来自 Objects.h
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;  
	bd.CPUAccessFlags = 0;

	//声明一个D3D11_SUBRESOURCE_DATA数据用于初始化子资源
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices; // 这里 vertices 来自 Objects.h 

	//声明一个ID3D11Buffer对象作为顶点缓存
	ID3D11Buffer* vertexBuffer;
	//调用CreateBuffer创建顶点缓存
	hr = S_OK;
	hr = device->CreateBuffer(&bd, &InitData, &vertexBuffer);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"创建VertexBuffer失败", L"Error", MB_OK);
		return hr;
	}

	UINT stride = sizeof(Vertex);                 //获取Vertex的大小作为跨度
	UINT offset = 0;                              //设置偏移量为0
	//设置顶点缓存，参数的解释见实验4
	immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//指定图元类型，D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST表示图元为三角形
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	

	return true;
}

void Cleanup()
{
	//释放全局指针
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
		float ClearColor[4] = { 0.125f, 0.125f, 0.125f, 1.0f };
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
		effect->GetVariableByName("EyePosition")->AsVector()->SetFloatVector((float*)&Eye);

		// 光照特效
		// 聚光灯
		// 材质和光照
		SetLightEffect();

		D3DX11_TECHNIQUE_DESC techDesc;
		technique->GetDesc(&techDesc);


		//设置箱子的纹理
		effect->GetVariableByName("Texture")->AsShaderResource()->SetResource(textureFloor);
		technique->GetPassByIndex(0)->Apply(0, immediateContext);
		technique->GetPassByIndex(0)->Apply(0, immediateContext);
		immediateContext->Draw(poolTableVerCount, 0); // 画台球桌

		swapChain->Present(0, 0);
	}
	return true;
}


//
// 回调函数
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
// 主函数WinMain
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

void SetLightEffect() {
	floorMaterial.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	floorMaterial.diffuse = XMFLOAT4(1.f, 1.f, 1.f, 1.0f);
	floorMaterial.specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 16.0f);
	floorMaterial.power = 5.0f;

	spotLight.position = XMFLOAT4(0.0f, 7.0f, 0.0f, 1.0f); //光源位置
	spotLight.direction = XMFLOAT4(0.0f, -1.0f, 0.0f, 1.0f); //光照方向
	spotLight.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);   //前三位分别表示红绿蓝光的强度
	spotLight.diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);   //同上
	spotLight.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);  //同上
	spotLight.attenuation0 = 0;    //常量衰减因子
	spotLight.attenuation1 = 0.1f; //一次衰减因子
	spotLight.attenuation2 = 0;    //二次衰减因子
	spotLight.alpha = XM_PI / 10;   //内锥角度
	spotLight.beta = XM_PI / 5;    //外锥角度
	spotLight.fallOff = 1.0f;      //衰减系数，一般为1.0

	effect->GetVariableByName("LightAmbient")->AsVector()->SetFloatVector((float*)&(spotLight.ambient));
	effect->GetVariableByName("LightDiffuse")->AsVector()->SetFloatVector((float*)&(spotLight.diffuse));
	effect->GetVariableByName("LightSpecular")->AsVector()->SetFloatVector((float*)&(spotLight.specular));
	effect->GetVariableByName("LightPosition")->AsVector()->SetFloatVector((float*)&(spotLight.position));
	effect->GetVariableByName("LightDirection")->AsVector()->SetFloatVector((float*)&(spotLight.direction));
	effect->GetVariableByName("LightAtt0")->AsScalar()->SetFloat(spotLight.attenuation0);
	effect->GetVariableByName("LightAtt1")->AsScalar()->SetFloat(spotLight.attenuation1);
	effect->GetVariableByName("LightAtt2")->AsScalar()->SetFloat(spotLight.attenuation2);
	effect->GetVariableByName("LightAlpha")->AsScalar()->SetFloat(spotLight.alpha);
	effect->GetVariableByName("LightBeta")->AsScalar()->SetFloat(spotLight.beta);
	effect->GetVariableByName("LightFallOff")->AsScalar()->SetFloat(spotLight.fallOff);

	effect->GetVariableByName("MatAmbient")->AsVector()->SetFloatVector((float*)&(floorMaterial.ambient));
	effect->GetVariableByName("MatDiffuse")->AsVector()->SetFloatVector((float*)&(floorMaterial.diffuse));
	effect->GetVariableByName("MatSpecular")->AsVector()->SetFloatVector((float*)&(floorMaterial.specular));
	effect->GetVariableByName("MatPower")->AsScalar()->SetFloat(floorMaterial.power);

	//将聚光灯光源的Tectnique设置到Effect
	technique = effect->GetTechniqueByName("T_SpotLight");
}
