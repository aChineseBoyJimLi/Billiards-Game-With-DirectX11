cbuffer MatrixBuffer
{
	matrix World;         //��������任����
	matrix View;          //�۲�����任����
	matrix Projection;    //ͶӰ����任����
}

Texture2D Texture;       //�������

SamplerState Sampler     //���������
{
	Filter = MIN_MAG_MIP_LINEAR;   //�������Թ���
	AddressU = WRAP;              //ѰַģʽΪWRAP
	AddressV = WRAP;              //ѰַģʽΪWRAP
};

struct VS_INPUT
{
	float4 Pos : POSITION;   //λ��
	float2 Tex : TEXCOORD0;  //����
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;    //λ��
	float2 Tex : TEXCOORD0;      //����
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;              //����һ��VS_OUTPUT����

	output.Pos = mul(input.Pos, World);         //��input�����Ͻ�������任
	output.Pos = mul(output.Pos, View);         //���й۲�任
	output.Pos = mul(output.Pos, Projection);   //����ͶӰ�任

	output.Tex = input.Tex;       //��������

	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	return Texture.Sample(Sampler, input.Tex);
}

technique11 TexTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}