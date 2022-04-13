
bool wallhack = 1;

HRESULT APIENTRY DrawIndexedPrimitive_hook(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
if (Stride == 40) 
{
AddModels(pDevice, 189);
AddModels(pDevice, 180);
pDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&bias_float);
DrawIndexedPrimitive_orig(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_DEPTHBIAS, 0);
}
return DrawIndexedPrimitive_orig(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}



struct vec2
{
	float x, y;
};

struct vec3
{
	float x, y, z;
};

struct vec4
{
	float x, y, z, w;
};



float ViewportWidth;
float ViewportHeight;

UINT tolerance = 1160;


const char* VariableText(const char* format, ...) {
	va_list argptr;
	va_start(argptr, format);

	char buffer[2048];
	vsprintf_s(buffer, format, argptr); 

	va_end(argptr);

	return buffer;
}


void AddModels(LPDIRECT3DDEVICE9 Device, UINT sr)
{
	vec4 pos{ 0.0f, (float)aimheight, (float)preaim, 0.0f };
	vec4 vOut;
	float matrix[16];

	Device->GetVertexShaderConstantF(sr, matrix, 4);

	vOut.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	vOut.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	vOut.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	vOut.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	float xx, yy;
	xx = ((vOut.x / vOut.w) * (ViewportWidth / 2.0f)) + (ViewportWidth / 2.0f);
	yy = (ViewportHeight / 2.0f) - ((vOut.y / vOut.w) * (ViewportHeight / 2.0f));

	ModelEspInfo_t pModelEspInfo;
	pModelEspInfo = { static_cast<float>(xx), static_cast<float>(yy), static_cast<float>(vOut.w * 0.4f) };
	ModelEspInfo.push_back(pModelEspInfo);
}