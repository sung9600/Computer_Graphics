//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject : register(b0)
{
	float4x4 gWorldViewProj;
	float4x4 axisRotationMatrix;
	float gTime;
}; 

struct VertexIn
{
	float4 Color : COLOR;
	float3 PosL  : POSITION;
	//Q1
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to homogeneous clip space.

	//Q6
	//vin.PosL.xy += 0.5f *sin(3.0f * gTime);
	//float a = vin.PosL.x * cos(gTime) + vin.PosL.z * sin(gTime);
	//float b = vin.PosL.x * (-1) * sin(gTime) + vin.PosL.z * cos(gTime);
	//vin.PosL.x = a;
	//vin.PosL.z = b;
	vin.PosL = mul(float4(vin.PosL, 1.0f), axisRotationMatrix);
	//vin.PosL.z *= 0.6f + 0.4f * sin(2.0f * gTime);
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	// Just pass vertex color into the pixel shader.
    vout.Color = vin.Color;
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	//clip(pin.Color.r - 0.2f);
    return pin.Color;
}


