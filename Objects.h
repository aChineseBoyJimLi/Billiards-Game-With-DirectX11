#include "d3dUtility.h"
using namespace d3d;
/* 台球桌 */
Vertex vertices[] = {
	//////////////////////////// 台球桌顶点 ///////////////////////////////
	{XMFLOAT3(0.0f,0.0f,-2.0f),XMFLOAT3(0.0f,1.0f,0.0f), XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(1.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,1.0f)},
	{XMFLOAT3(1.0f,0.0f,-2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,0.0f)},

	{XMFLOAT3(-1.0f,0.0f,-2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,0.0f)},
	{XMFLOAT3(-1.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,1.0f)},
	{XMFLOAT3(0.0f,0.0f,-2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},

	{XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,1.0f)},
	{XMFLOAT3(1.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,1.0f)},
	{XMFLOAT3(0.0f,0.0f,-2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},

	{XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,1.0f)},
	{XMFLOAT3(0.0f,0.0f,-2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(-1.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,1.0f)},

	////////////////////////////////////////////////////////////////////
	{XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.3f,0.7f)},
	{XMFLOAT3(1.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.7f)},

	{XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.3f,0.7f)},
	{XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(-1.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.7f)},

	{XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(1.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,0.0f)},
	{XMFLOAT3(1.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,1.0f)},

	{XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(-1.0f,0.0f,-1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,1.0f)},
	{XMFLOAT3(-1.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,0.0f)},

	/////////////////////////////////////////////////////////////////////
	{XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(1.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.3f,0.7f)},
	{XMFLOAT3(1.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.7f)},

	{XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(-1.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.7f)},
	{XMFLOAT3(-1.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.3f,0.7f)},

	{XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(0.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.7f)},
	{XMFLOAT3(1.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.3f,0.7f)},

	{XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(-1.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.3f,0.7f)},
	{XMFLOAT3(0.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.7f)},

	////////////////////////////////////////////////////////////////////

	{XMFLOAT3(0.0f,0.0f,2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(1.0f,0.0f,2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,0.0f)},
	{XMFLOAT3(1.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,1.0f)},


	{XMFLOAT3(-1.0f,0.0f,2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,0.0f)},
	{XMFLOAT3(0.0f,0.0f,2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(-1.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.0f,1.0f)},


	{XMFLOAT3(0.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.7f)},
	{XMFLOAT3(0.0f,0.0f,2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},
	{XMFLOAT3(1.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.3f,0.7f)},

	{XMFLOAT3(0.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.7f)},
	{XMFLOAT3(-1.0f,0.0f,1.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(0.3f,0.7f)},
	{XMFLOAT3(0.0f,0.0f,2.0f),XMFLOAT3(0.0f,1.0f,0.0f),  XMFLOAT2(1.0f,0.0f)},


	//////////////////////////// 母球的顶点 ///////////////////////////////


};

UINT poolTableVerCount = 48; // 台球桌的顶点

UINT verCount = ARRAYSIZE(vertices);
