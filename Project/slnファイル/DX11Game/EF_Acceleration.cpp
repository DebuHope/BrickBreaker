//======================================================================================
// 加速エフェクト
// 制作：向出創
//======================================================================================

// ヘッダファイルのインクルード
#include"EF_Acceleration.h"
#include"texture.h"
#include"polygon.h"
#include "Player.h"

// マクロ定義
#define ACCELERATION_POS_X	 (0)
#define ACCELERATION_POS_Y	 (0)
#define ACCELERATION_SIZE_X (2000)
#define ACCELERATION_SIZE_Y (750)
#define ACCELERATION_FRAME_X (5)	// 画像横分割数
#define ACCELERATION_FRAME_Y (1)	// 画像縦分割数

#define ACCELERATION_TEXTURENAME	_T("data/texture/kasoku3.png")

#define FLUCTUATION_ALPHA	(0.15f)	// Alpha変動値

// グローバル変数宣言
static ID3D11ShaderResourceView* g_pTexture;	// テクスチャ

static XMFLOAT3 g_Position;		// 座標
static XMFLOAT2 g_Size;			// サイズ
static float	g_Angle;		// 回転角度
static float	g_Alpha;		// 透明度
static XMFLOAT2 g_TexCoord;		// テクスチャ座標(ポリゴンの左上)(TextureCoordinate)
static XMFLOAT2 g_TexFrameSize;	// テクスチャを貼り付けるサイズ
static int		g_AnimNo;
static int		g_AnimCnt;

static ANIM_PAT g_animPat[1][6] = {	// 爆発アニメーション情報[表示パターン番号][表示フレーム数]
	{{0,2},{1,2},{2,2},{3,2},{4,2},{-1,-1}},
};

HRESULT LoadAcceleration()
{
	HRESULT hr = S_OK;
	ID3D11Device*	pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, ACCELERATION_TEXTURENAME, &g_pTexture);
	if (FAILED(hr)) return hr;

	return hr;
}

//======================================================================================
// 初期化
//======================================================================================
void InitAcceleration(void)
{
	// パラメータの初期化
	g_Position = XMFLOAT3(ACCELERATION_POS_X, ACCELERATION_POS_Y, 0.0f);
	g_Size = XMFLOAT2(ACCELERATION_SIZE_X, ACCELERATION_SIZE_Y);
	g_Angle = 0.0f;
	g_Alpha = 0.0f;
	g_TexCoord = XMFLOAT2(0.0f, 0.0f);
	g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
	g_AnimNo = 0;
	g_AnimCnt = g_animPat[0][g_AnimNo].nCount; // 最初のアニメ表示時間
}

//======================================================================================
// 終了
//======================================================================================
void UninitAcceleration(void)
{
	// テクスチャ後片付け
	//SAFE_RELEASE(g_pTexture);
}

//======================================================================================
// 更新
//======================================================================================
void UpdateAcceleration()
{
	// アニメーション情報の更新
	g_AnimCnt--;	// 残りカウント数を減らす
	if (g_AnimCnt <= 0)
	{
		g_AnimNo++;	// 次の絵に進める

		if (g_animPat[0][g_AnimNo].nPatNo < 0)
		{
			// 番兵を参照したら
			g_AnimNo = 0;	// 戻す
		}
		// カウンタを次の絵の表示フレーム数に設定
		g_AnimCnt = g_animPat[0][g_AnimNo].nCount;
	}
}

//======================================================================================
// 描画
//======================================================================================
void DrawAcceleration()
{
	// ポリゴンの情報設定
	SetPolygonPos(ACCELERATION_POS_X, ACCELERATION_POS_Y);	// 座標
	SetPolygonSize(ACCELERATION_SIZE_X, ACCELERATION_SIZE_Y);	// サイズ
	SetPolygonAngle(g_Angle);	// 角度	

	SetPolygonFrameSize(1.0f / ACCELERATION_FRAME_X, 1.0f / ACCELERATION_FRAME_Y);	// テクスチャの横幅、縦幅
	int u = g_animPat[0][g_AnimNo].nPatNo % ACCELERATION_FRAME_X;	// 向いている方向
	int v = g_animPat[0][g_AnimNo].nPatNo / ACCELERATION_FRAME_X;
	SetPolygonUV(u / (float)ACCELERATION_FRAME_X, v / (float)ACCELERATION_FRAME_Y);	// 0番(左上頂点)のテクスチャ座標指定
	SetPolygonAlpha(g_Alpha);
	SetPolygonColor(1.0f, 1.0f, 1.0f);

	SetPolygonTexture(g_pTexture);	// テクスチャ指定

	// ポリゴンの描画処理
	ID3D11DeviceContext*	pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
}