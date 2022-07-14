//======================================================================================
// コンボ処理
// 制作：向出創
//======================================================================================

// ヘッダファイルのインクルード
#include"Combo.h"
#include"Texture.h"
#include"polygon.h"
#include "Player.h"
#include "Debugproc.h"
#include "Transition.h"
#include "Game.h"
#include "Score.h"

// マクロ定義
#define COMBO_POS_X	(0)
#define COMBO_POS_Y	(0)
#define COMBO_SIZE_X	(SCREEN_WIDTH)
#define COMBO_SIZE_Y	(SCREEN_HEIGHT)

#define COMBO_TEXTURE		_T("data/texture/UI/Combo.png")

// グローバル変数宣言
static ID3D11ShaderResourceView* g_pTexture;	// テクスチャ	

static XMFLOAT3 g_Position;		// 座標
static XMFLOAT2 g_Size;			// サイズ
static float	g_Angle;		// 回転角度
static XMFLOAT2 g_TexCoord;		// テクスチャ座標(ポリゴンの左上)(TextureCoordinate)
static XMFLOAT2 g_TexFrameSize;	// テクスチャを貼り付けるサイズ

HRESULT LoadCombo()
{
	HRESULT hr = S_OK;
	ID3D11Device*	pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, COMBO_TEXTURE, &g_pTexture);
	if (FAILED(hr)) return hr;

	return hr;
}

//======================================================================================
// 初期化
//======================================================================================
void InitCombo()
{
	// パラメータの初期化
	g_Position		= XMFLOAT3(COMBO_POS_X, COMBO_POS_Y, 0.0f);
	g_Size			= XMFLOAT2(COMBO_SIZE_X, COMBO_SIZE_Y);
	g_Angle			= 0.0f;
	g_TexCoord		= XMFLOAT2(0.0f, 0.0f);
	g_TexFrameSize	= XMFLOAT2(1.0f, 1.0f);
}

//======================================================================================
// 終了
//======================================================================================
void UninitCombo()
{
	//// テクスチャ後片付け
	//for (int i = 0; i < MAX_TEXTURE; i++)
	//{
	//	SAFE_RELEASE(g_pTexture[i]);
	//}
}

//======================================================================================
// 更新
//======================================================================================
void UpdateCombo()
{
	//if (GetComboCount() == 10) {
	//	g_Position.y += 50.0f;
	//	SetComboCount();
	//}

	//if (g_Position.y > COMBO_POS_Y) {
	//	g_Position.y -= 5.0f;
	//}
}

//======================================================================================
// 描画
//======================================================================================
void DrawCombo()
{
	SetPolygonAngle(0.0f);
	SetPolygonAlpha(1.0f);

	if (GetScore(2) == 0 && GetScore(2) < 20) {
		SetPolygonColor(1.0f, 1.0f, 1.0f);
	}
	else if (GetScore(2) >= 20 && GetScore(2) < 50) {
		SetPolygonColor(0.0f, 0.5f, 1.0f);
	}
	else if (GetScore(2) >= 50 && GetScore(2) < 80) {
		SetPolygonColor(0.0f, 1.0f, 0.0f);
	}
	else if (GetScore(2) >= 80 && GetScore(2) < 100) {
		SetPolygonColor(1.0f, 1.0f, 0.0f);
	}
	else if (GetScore(2) >= 100) {
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	// ポリゴンの情報設定
	SetPolygonPos(g_Position.x, g_Position.y);		// 座標
	SetPolygonSize(COMBO_SIZE_X, COMBO_SIZE_Y);	// 大きさ
	SetPolygonAngle(g_Angle);				// 回転角度
	// degree(デグリー)値(0~360°)
	// ←→radian(ラジアン)値(0~2π)

	SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
	SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅
	SetPolygonTexture(g_pTexture);

	// ポリゴンの描画処理
	ID3D11DeviceContext*	pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
}

XMFLOAT3 GetComboPos()
{
	return g_Position;
}
