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
};

struct PS_OUTPUT
{
	float4 Color1 : SV_Target0;
	float4 Color2 : SV_Target1;
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

	return output;
}

PS_OUTPUT PS(PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;

	output.Color1 = txDiffuse.Sample(samLinear, input.Tex);
	output.Color2 = float4(input.Normal, 1);

	return output;
}