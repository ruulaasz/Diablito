Texture2D txDiffuse : register(t1);
SamplerState samLinear : register(s0);

cbuffer cbView : register(b0)
{
	matrix View;
};

cbuffer cbProj : register(b1)
{
	matrix Projection;
};

cbuffer cbWorld : register(b2)
{
	matrix World;
};

cbuffer cbColor : register(b3)
{
	float4 Color;
};

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Normal : NORMAL0;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
	float3 Normal : TEXCOORD1;
	float2 Depth : TEXCOORD2;
	float4 Color : TEXCOORD3;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );

	float3 viewpos = output.Pos;

    output.Pos = mul( output.Pos, Projection);

	output.Tex = input.Tex;
	output.Normal = input.Normal;

	output.Depth = viewpos.z;

	output.Color = Color;

	return output;
}

float4 PS(PS_INPUT input) : SV_Target0
{
	//float normDepth = input.Depth / 200.0f;
	//return float4(normDepth, normDepth, normDepth, 1.0f);
	//return float4(input.Normal, 1.0f);
	float4 c = txDiffuse.Sample(samLinear, input.Tex);
	return c;//+input.Color;
}