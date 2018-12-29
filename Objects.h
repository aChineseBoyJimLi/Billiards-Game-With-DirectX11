#include "d3dUtility.h"
using namespace d3d;
/* ̨���� */
Vertex vertices[] = {
	//////////////////////////// ̨�������� ///////////////////////////////
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


	//////////////////////////// ĸ��Ķ��� ///////////////////////////////


};

UINT poolTableVerCount = 48; // ̨�����Ķ���

UINT verCount = ARRAYSIZE(vertices);
