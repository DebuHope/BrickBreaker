//======================================================================================
// ライフ処理
// 制作：向出創
//======================================================================================

// ヘッダファイルのインクルード
#include"Life.h"
#include"input.h"
#include"texture.h"
#include"polygon.h"
#include "Transition.h"
#include "Game.h"

// マクロ定義
#define LIFE_SIZE_X (40)	// 幅
#define LIFE_SIZE_Y (38)	// 縦
#define LIFE_POS_X	 (-SCREEN_WIDTH / 2 + 111)	// x座標
#define LIFE_POS_Y	 (SCREEN_HEIGHT / 2 - 48)	// y座標
#define LIFE_FRAME_X (1)	// 画像幅分割数
#define LIFE_FRAME_Y (2)	// 画像縦分割数

#define LIFE_TEXTURENAME	_T("data/texture/UI/Life2.png")

// グローバル変数宣言
static ID3D11ShaderResourceView* g_pTexture;	// テクスチャ

static XMFLOAT3	g_Position;	// 座標
static XMFLOAT2	g_Size;		// サイズ
static XMFLOAT2	g_Scale;	// 拡大縮小
static float	g_Angle;	// 回転角度
static int		g_nMaxLife;

static XMFLOAT2		g_TexCoord;		// テクスチャ座標(ポリゴンの左上)(TextureCoordinate)
static XMFLOAT2		g_TexFrameSize;	// テクスチャを貼り付けるサイズ

HRESULT LoadLife()
{
	HRESULT hr = S_OK;

	// テクスチャ読み込み
	ID3D11Device*	pDevice = GetDevice();
	hr = CreateTextureFromFile(pDevice, LIFE_TEXTURENAME, &g_pTexture);

	g_TexCoord = XMFLOAT2(0.0f, 0.0f);
	g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);

	return hr;
}

//======================================================================================
// 初期化
//======================================================================================
void InitLife(void)
{
	// パラメータの初期化
	g_Position = XMFLOAT3(LIFE_POS_X, LIFE_POS_Y, 0.0f);
	g_Size = XMFLOAT2(LIFE_SIZE_X, LIFE_SIZE_Y);
	g_Angle = 0.0f;
	g_Scale = XMFLOAT2(1.0f, 1.0f);
	g_nMaxLife = 3;
}

//======================================================================================
// 終了
//======================================================================================
void UninitLife(void)
{
	//// テクスチャ後片付け
	//SAFE_RELEASE(g_pTexture);
}

//======================================================================================
// 更新
//======================================================================================
void UpdateLife()
{

}

//======================================================================================
// 描画
//======================================================================================
void DrawLife()
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// 黒		数値描画
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	SetPolygonAngle(180.0f);
	SetPolygonAlpha(1.0f);
	SetPolygonSize(LIFE_SIZE_X, LIFE_SIZE_Y);
	SetPolygonFrameSize(1.0f / LIFE_FRAME_X, 1.0f / -LIFE_FRAME_Y);

	SetPolygonUV(g_TexCoord.x, g_TexCoord.y);
	SetPolygonTexture(g_pTexture);
	// 表示する位置を決める

	float fX = g_Position.x + LIFE_SIZE_X * (5 - 0.5f);
	float fY = g_Position.y - LIFE_SIZE_Y * 0.5f + 2.0f;

	for (int i = 0; i < 3; ++i)
	{
		SetPolygonPos(fX, fY);
		DrawPolygon(pDeviceContext);
		fX += LIFE_SIZE_X + 10;
	}

	// 赤		数値描画
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	SetPolygonAngle(0.0f);
	SetPolygonAlpha(1.0f);
	SetPolygonSize(LIFE_SIZE_X, LIFE_SIZE_Y);
	SetPolygonFrameSize(1.0f / LIFE_FRAME_X, 1.0f / LIFE_FRAME_Y);

	SetPolygonUV(g_TexCoord.x, g_TexCoord.y);
	SetPolygonTexture(g_pTexture);
	// 表示する位置を決める

	fX = g_Position.x + LIFE_SIZE_X * (5 - 0.5f);
	fY = g_Position.y - LIFE_SIZE_Y * 0.5f;

	for (int i = 0; i < g_nMaxLife; ++i)
	{
		SetPolygonPos(fX, fY);
		DrawPolygon(pDeviceContext);
		fX += LIFE_SIZE_X + 10;
	}
}

// ライフ減少
int RemainingLife(int num)
{
	g_nMaxLife -= num;
	if (g_nMaxLife < 0)	g_nMaxLife = 0;

	return g_nMaxLife;
}

// ライフ回復
int RecoveryLife(int num)
{
	g_nMaxLife += num;
	if (g_nMaxLife > 3)	g_nMaxLife = 3;

	return g_nMaxLife;
}
