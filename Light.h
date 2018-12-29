#pragma once
#pragma once
#ifndef LIGHT_H_H
#define LIGHT_H_H
#include "d3dUtility.h"
using namespace DirectX;
// 这里是材质对各种光的反射率
struct Material
{
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
	XMFLOAT4 specular;
	float	 power;
};

struct Light
{
	int type;
	XMFLOAT4 direction;
	XMFLOAT4 position;
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
	float attenuation0;
	float attenuation1;
	float attenuation2;

	float alpha;
	float beta;
	float fallOff;
};

#endif // !LIGHT_H_H