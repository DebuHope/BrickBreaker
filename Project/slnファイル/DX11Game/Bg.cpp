//======================================================================================
// 背景
// 制作：向出創
//======================================================================================

// ヘッダファイルのインクルード
#include"bg.h"
#include"Texture.h"
#include"polygon.h"
#include "Player.h"
#include "UI.h"

// マクロ定義
#define BG_POS_X	(0)
#define BG_POS_Y	(0)
#define BG_SIZE_X	(SCREEN_WIDTH)	// ウィンドウの幅と同じサイズ
#define BG_SIZE_Y	(SCREEN_HEIGHT)	// ウィンドウの高さと同じサイズ

#define MAX_TEXTURE (7)

#define BG_STAGE1		_T("data/texture/sky.png")
#define BG_STAGE2		_T("data/texture/yuyake.png")
#define BG_STAGE3		_T("data/texture/night.png")
#define BG_HOLE			_T("data/texture/hole2.png")
#define BG_IKEHOLE		_T("data/texture/ikeHole.png")
#define BG_HOLE3		_T("data/texture/hole5.png")
#define BG_TITLE		_T("data/texture/UI/TitleScreen.png")

// グローバル変数宣言
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE];	// テクスチャ	

static XMFLOAT3 g_Position;		// 座標
static XMFLOAT2 g_Size;			// サイズ
static float	g_Angle;		// 回転角度
static float	g_Alpha;		// 透明度

static int DrawBGNo;

static XMFLOAT2 g_TexCoord;		// テクスチャ座標(ポリゴンの左上)(TextureCoordinate)
static XMFLOAT2 g_TexFrameSize;	// テクスチャを貼り付けるサイズ

static bool temp;

HRESULT LoadBg()
{
	HRESULT hr = S_OK;
	ID3D11Device*	pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, BG_STAGE1, &g_pTexture[0]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, BG_STAGE2, &g_pTexture[1]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, BG_STAGE3, &g_pTexture[2]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, BG_HOLE, &g_pTexture[3]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, BG_TITLE, &g_pTexture[4]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, BG_IKEHOLE, &g_pTexture[5]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, BG_HOLE3, &g_pTexture[6]);
	if (FAILED(hr)) return hr;

	return hr;
}

//======================================================================================
// 初期化
//======================================================================================
void InitBg()
{
	// パラメータの初期化
	g_Position		= XMFLOAT3(BG_POS_X, BG_POS_Y, 0.0f);
	g_Size			= XMFLOAT2(BG_SIZE_X, BG_SIZE_Y);
	g_Angle			= 0.0f;
	g_TexCoord		= XMFLOAT2(0.0f, 0.0f);
	g_TexFrameSize	= XMFLOAT2(1.0f, 1.0f);
	temp = false;

	DrawBGNo = 0;
}

//======================================================================================
// 終了
//======================================================================================
void UninitBg()
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
void UpdateBg()
{
	if (temp == false) {
		g_Alpha -= 0.05f;
		if (g_Alpha < 0.0f)	temp = true;
	}
	else if (temp == true) {
		g_Alpha += 0.1f;
		if (g_Alpha > 2.0f)	temp = false;
	}

	if (GetUIState() == 0) DrawBGNo = 0;
	else if (GetUIState() == 1) DrawBGNo = 1;
	else if (GetUIState() == 2) DrawBGNo = 2;
}

//======================================================================================
// 描画
//======================================================================================
void DrawBg()
{
	SetPolygonAngle(0.0f);				// 回転角度
	SetPolygonAlpha(1.0f);
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	// ポリゴンの情報設定
	SetPolygonPos(BG_POS_X, BG_POS_Y);		// 座標
	SetPolygonSize(BG_SIZE_X, BG_SIZE_Y);	// 大きさ
	SetPolygonAngle(g_Angle);				// 回転角度
	// degree(デグリー)値(0~360°)
	// ←→radian(ラジアン)値(0~2π)

	SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
	SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅
	if (GetSceneNo() == SCENE_TITLE) {
		SetPolygonTexture(g_pTexture[4]);
	}
	else if (GetSceneNo() == SCENE_ENDING) {
		SetPolygonTexture(g_pTexture[0]);	// テクスチャ指定
	}
	else {
		SetPolygonTexture(g_pTexture[DrawBGNo]);
	}

	// ポリゴンの描画処理
	ID3D11DeviceContext*	pDeviceContext = GetDeviceContext();
	DrawPolygon(pDeviceContext);
}