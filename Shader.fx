cbuffer MatrixBuffer
{
	matrix World;         //世界坐标变换矩阵
	matrix View;          //观察坐标变换矩阵
	matrix Projection;    //投影坐标变换矩阵
	float4 EyePosition;	  //视点位置
}

cbuffer MaterialBuffer
{
	float4 MatAmbient;   
	float4 MatDiffuse;   
	float4 MatSpecular;  
	float  MatPower;     
}



cbuffer LightBuffer
{      
	float4 LightPosition; 
	float4 LightDirection;
	float4 LightAmbient;  
	float4 LightDiffuse;  
	float4 LightSpecular; 
	float  LightAtt0;
	float  LightAtt1;
	float  LightAtt2;
	float  LightAlpha;
	float  LightBeta;
	float  LightFallOff;
}

Texture2D Texture;       //纹理变量

SamplerState Sampler     //定义采样器
{
	Filter = MIN_MAG_MIP_LINEAR;   //采用线性过滤
	AddressU = WRAP;              //寻址模式为WRAP
	AddressV = WRAP;              //寻址模式为WRAP
};

struct VS_INPUT
{
	float4 Pos : POSITION;   //位置
	float3 Norm : NORMAL;
	float2 Tex : TEXCOORD0;  //纹理
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;    //位置
	float2 Tex : TEXCOORD0;      //纹理
	float3 Norm : TEXCOORD1;
	float4 ViewDirection : TEXCOORD2;
	float4 LightVector : TEXCOORD3;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;              //声明一个VS_OUTPUT对象

	output.Pos = mul(input.Pos, World);         //在input坐标上进行世界变换
	output.Pos = mul(output.Pos, View);         //进行观察变换
	output.Pos = mul(output.Pos, Projection);   //进行投影变换

	output.Norm = mul(input.Norm, (float3x3)World);  //获得output的方向量
	output.Norm = normalize(output.Norm);              //对法向量进行归一化

	float4 worldPosition = mul(input.Pos, World);          //获取顶点的世界坐标
	output.ViewDirection = EyePosition - worldPosition;    //获取视点方向
	output.ViewDirection = normalize(output.ViewDirection);//将视点方向归一化

	output.LightVector = LightPosition - worldPosition;    //获取光照方向
	output.LightVector = normalize(output.LightVector);    //将光照方向归一化
	output.LightVector.w = length(LightPosition - worldPosition);  //获取光照距离

	output.Tex = input.Tex;       //纹理设置

	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	return Texture.Sample(Sampler, input.Tex);
}



 //聚光灯像素着色器
float4 PSSpotLight(VS_OUTPUT input) : SV_Target
{
	float4 finalColor;        //声明颜色向量，这个颜色是最终的颜色
	float4 ambientColor, diffuseColor, specularColor;  //声明环境光，漫反射，镜面光颜色

	//光照向量等于顶点的光照向量
	float3 lightVector = input.LightVector.xyz;
	lightVector = normalize(lightVector); //归一化
	float d = input.LightVector.w;        //光照距离
	float3 lightDirection = LightDirection.xyz;  //光照方向
	lightDirection = normalize(lightDirection);  //归一化

	//判断光照区域
	float cosTheta = dot(-lightVector, lightDirection);
	//如果照射点位于圆锥体照射区域之外，则不产生光照
	if (cosTheta < cos(LightBeta / 2))
		return float4(0.0f, 0.0f, 0.0f, 1.0f);
	//用材质环境光反射率和环境光强度相乘得到环境光颜色
	ambientColor = MatAmbient * LightAmbient;
	//将顶点法向量和光照方向进行点乘得到漫反射光因子
	float diffuseFactor = dot(lightVector, input.Norm);
	if (diffuseFactor > 0.0f)    //漫反射光因子>0表示不是背光面
	{
		//用材质的漫反射光的反射率和漫反射光的光照强度以及反漫射光因子相乘得到漫反射光颜色
		diffuseColor = MatDiffuse * LightDiffuse * diffuseFactor;
		//根据光照方向和顶点法向量计算反射方向
		float3 reflection = reflect(-lightVector, input.Norm);
		//根据反射方向，视点方向以及材质的镜面光反射系数来计算镜面反射因子
		float specularFactor = pow(max(dot(reflection, input.ViewDirection.xyz), 0.0f), MatPower);
		//材质的镜面反射率，镜面光强度以及镜面反射因子相乘得到镜面光颜色
		specularColor = MatSpecular * LightSpecular * specularFactor;
	}

	//距离衰减因子
	float att = LightAtt0 + LightAtt1 * d + LightAtt2 * d * d;
	if (cosTheta > cos(LightAlpha / 2)) //当照射点位于内锥体内
	{
		finalColor = saturate(ambientColor + diffuseColor + specularColor) / att;
	}
	else if (cosTheta >= cos(LightBeta / 2) && cosTheta <= cos(LightAlpha / 2))//当照射点位于内锥体和外锥体之间
	{
		//外锥体衰减因子
		float spotFactor = pow((cosTheta - cos(LightBeta / 2)) / (cos(LightAlpha / 2) - cos(LightBeta / 2)), 1);
		finalColor = spotFactor * saturate(ambientColor + diffuseColor + specularColor) / att;
	}
	float4 texColor = Texture.Sample(Sampler, input.Tex);  //获取纹理颜色
	finalColor = finalColor * texColor;                    //纹理颜色与光照颜色相乘得到最后颜色
	finalColor.a = texColor.a * MatDiffuse.a;              //获取alpha值即透明度
	return finalColor;
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

technique11 T_SpotLight
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PSSpotLight()));
	}
}

//technique11 Light
//{
//	pass P0 {
//		SetVertexShader(CompileShader(vs_5_0, VS()));
//		/*SetPixelShader(CompileShader(ps_5_0, PSDirectionalLight()));*/
//		SetPixelShader(CompileShader(ps_5_0, PSSpotLight()));
//	}
//	pass P1 {
//		
//	}
//}