//=============================================================================
// 数値表示処理
// 制作：向出創
//=============================================================================
#include "number.h"
#include "polygon.h"
#include "Texture.h"
#include "Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_TEXTURENAME	L"data/texture/number3.png"	// テクスチャファイル名

#define NUMBER_FRAME_X		(10)	// 横フレーム数
#define NUMBER_FRAME_Y		(1)		// 縦フレーム数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ

//=============================================================================
// 数値表示の初期化処理
//=============================================================================
HRESULT InitNumber()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(), NUMBER_TEXTURENAME, &g_pTexture);
	return hr;
}

//=============================================================================
// 数値表示の終了処理
//=============================================================================
void UninitNumber()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// 数値表示処理
//=============================================================================
void DrawNumber(XMFLOAT2* pPos, unsigned uNumber,
	int nWidth, float fSizeX, float fSizeY)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// 数値描画
	SetPolygonSize(fSizeX, fSizeY);
	SetPolygonTexture(g_pTexture);
	SetPolygonAlpha(1.0f);
	if (GetState() != 0 && GetState() != 2) {
		SetPolygonColor(0.3f, 0.3f, 0.3f);
	}
	SetPolygonFrameSize(1.0f / NUMBER_FRAME_X, 1.0f / NUMBER_FRAME_Y);

	// 表示する位置を決める
	float fX = pPos->x + fSizeX * (nWidth - 0.5f);
	float fY = pPos->y - fSizeY * 0.5f;

	for (int i = 0; i < nWidth; ++i)
	{
		unsigned n = uNumber % 10;
		int u = n % NUMBER_FRAME_X;
		int v = n / NUMBER_FRAME_X;
		SetPolygonUV(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y);
		SetPolygonPos(fX, fY);
		DrawPolygon(pDeviceContext);
		uNumber /= 10;
		fX -= fSizeX;

		// 下1桁を取り出すアルゴリズム
		// 1234 % 10 = 4 → 1234 / 10 = 123
		// 123 % 10 = 3  → 123  / 10 = 12
		// ・以下略
		// ・
	}
	SetPolygonUV(0.0f, 0.0f);
}
