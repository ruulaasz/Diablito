Texture2D txDiffuse : register(t0);
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
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection);

	output.Tex = input.Tex;

	return output;
}

float4 PS(PS_INPUT input) : SV_Target0
{
	return txDiffuse.Sample(samLinear, input.Tex);
}