//======================================================================================
// ゲージ処理
// 制作：向出創
//======================================================================================
#include "gauge.h"
#include "polygon.h"
#include "Texture.h"

// マクロ定義
#define GAUGE_SIZE_X	(200)
#define GAUGE_SIZE_Y	(25)
#define GAUGE_TEXTURENAME1	_T("data/texture/gauge1.png")
#define GAUGE_TEXTURENAME2	_T("data/texture/gauge2.png")
#define GAUGE_TEXTURENAME3	_T("data/texture/gauge21.png")
#define GAUGETEXTNO		(3)

// グローバル変数
static ID3D11ShaderResourceView*	g_pTexture[GAUGETEXTNO];

// 初期化処理
HRESULT LoadGauge()
{
	HRESULT hr = S_OK;
	ID3D11Device*	pDevice = GetDevice();

	// テクスチャ読み込み
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME1, &g_pTexture[0]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME2, &g_pTexture[1]);
	hr = CreateTextureFromFile(GetDevice(), GAUGE_TEXTURENAME3, &g_pTexture[2]);
	return hr;
}

void UninitGauge( void )
{
	//// テクスチャ開放
	//for (int i = 0; i < GAUGETEXTNO; i++)
	//{
	//	SAFE_RELEASE(g_pTexture[i]);
	//}
}

//percent:100%→1.0として受け取る
void DrawGauge(XMFLOAT2 pos, float percent)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	SetPolygonTexture(g_pTexture[0]);
	SetPolygonSize(GAUGE_SIZE_X*percent, GAUGE_SIZE_Y);
	SetPolygonPos(pos.x + GAUGE_SIZE_X * percent / 2, pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(percent, 1.0f);

	DrawPolygon(pDeviceContext);

	SetPolygonFrameSize(1.0f, 1.0f);
}

void DrawGauge2(XMFLOAT2 pos, float percent)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	SetPolygonTexture(g_pTexture[0]);
	SetPolygonSize(415.0f*percent, 72.0f);
	SetPolygonPos(pos.x + 415.0f * percent / 2, pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(percent, 1.0f);

	DrawPolygon(pDeviceContext);

	SetPolygonFrameSize(1.0f, 1.0f);
}

void DrawGaugeX(XMFLOAT2 pos, XMFLOAT2 size, float percent,int no)
{
	static float Pc;
	Pc = abs(percent);
	if (Pc > 1.0f)Pc = 1.0f;
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonTexture(g_pTexture[no]);
	SetPolygonSize(size.x*Pc, size.y);
	SetPolygonPos(pos.x + size.x * percent / 2, pos.y);
	if(percent >= 0)SetPolygonUV(0.0f, 0.0f);
	else SetPolygonUV(1.0f - Pc, 0.0f);
	SetPolygonFrameSize(Pc, 1.0f);
	DrawPolygon(pDeviceContext);
	SetPolygonFrameSize(1.0f, 1.0f);
}

void DrawGaugeY1(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no)
{
	static float Pc;
	Pc = percent;
	if (Pc > 1.0f)Pc = 1.0f;
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonTexture(g_pTexture[no]);
	SetPolygonSize(size.x, size.y*Pc);
	SetPolygonPos(pos.x, pos.y + size.y * Pc / 2);
	SetPolygonUV(0.0f, 1.0f-Pc);
	SetPolygonFrameSize(1.0f, Pc);
	DrawPolygon(pDeviceContext);
	SetPolygonFrameSize(1.0f, 1.0f);
}

void DrawGaugeY2(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no)
{
	static float Pc;
	Pc = percent;
	if (Pc > 1.0f)Pc = 1.0f;
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonTexture(g_pTexture[no]);
	SetPolygonSize(size.x, size.y*Pc);
	SetPolygonPos(pos.x, pos.y + size.y * Pc / 2);
	SetPolygonUV(0.0f, 1.0f - Pc);
	SetPolygonFrameSize(1.0f, Pc);
	DrawPolygon(pDeviceContext);
	SetPolygonFrameSize(1.0f, 1.0f);
}