//======================================================================================
// エンドロール処理
// 制作：向出創
//======================================================================================
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Endroll.h"
#include "main.h"
#include "Player.h"
#include "Shadow.h"
#include "Input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CREDIT01	"data/model/text/ball_01.fbx"

#define MAX_TEXT_MODEL		(1)

#define TEXT_SPEED		(1.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct _tText
{
	XMFLOAT4X4	mtxWorld;

	int	nType;	// 種類
	XMFLOAT3 pos;	// 座標
	XMFLOAT3 rot;	// 回転
	XMFLOAT3 scl;	// 拡大率
	XMFLOAT3 vel;	// 速度
	int nShadowIdx;
	bool	KillFlag;	// キルフラグ
	int		nState;	// 行動(0以下:未使用 1以上:通常)
}tText;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAssimpModel	g_model[MAX_TEXT_MODEL];	// モデルデータ
static tText			g_text[MAX_TEXT];

float speed = 2.0f;
float angleX = 0.0f;
float angleY = 0.0f;

HRESULT LoadText(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// モデルデータの読み込み
	hr = g_model[0].Load(pDevice, pDeviceContext, CREDIT01);

	return hr;
}

//=============================================================================
// 初期化処理
//=============================================================================
void InitText(void)
{
	// 位置・回転・スケールの初期設定
	for (int i = 0; i < MAX_TEXT; i++)
	{
		g_text[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_text[i].rot = XMFLOAT3(0.0f, 180.0f, 0.0f);
		g_text[i].scl = XMFLOAT3(5.0f, 5.0f, 5.0f);
		g_text[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_text[i].nState = 1;
		g_text[i].KillFlag = false;
	}

	// ワールドマトリックスの初期化
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_TEXT; i++)
	{
		XMStoreFloat4x4(&g_text[i].mtxWorld, mtxWorld);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitText(void)
{
	// 影の解放
	for (int i = 0; i < MAX_TEXT; i++) {
		ReleaseShadow(g_text[i].nShadowIdx);
	}
	// モデルの解放
	//for (int i = 0; i < MAX_TEXT_MODEL; i++) {
	//	g_model[i].Release();
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateText(void)
{
	for (int i = 0; i < MAX_TEXT; i++)
	{
		if (g_text[i].nState == 0)	continue;

		if (GetKeyPress(VK_Z))
		{
			angleX -= 10.0f;
		}
		else if (GetKeyPress(VK_X))
		{
			angleX += 10.0f;
		}

		if (GetKeyPress(VK_C))
		{
			angleY -= 10.0f;
		}
		else if (GetKeyPress(VK_V))
		{
			angleY += 10.0f;
		}

		//				  原点    速度       角度
		g_text[i].vel.x = 0.0f + speed * cosf(angleX * (M_PI / 180.0f));
		g_text[i].vel.y = 0.0f + speed * sinf(angleY * (M_PI / 180.0f));

		// キルフラグが立った場合
		if (g_text[i].KillFlag == true) {
			angleY += 180;
			g_text[i].KillFlag = false;
		}

		// 位置の更新
		g_text[i].pos.x += g_text[i].vel.x;
		g_text[i].pos.y += g_text[i].vel.y;
		g_text[i].pos.z += g_text[i].vel.z;

		// 画面外判定
		if (g_text[i].pos.x > 98.0f || g_text[i].pos.x < -98.0f)
		{	// 左右
			angleX += 180.0f;
			angleX = (int)angleX % 360;
		}
		else if (g_text[i].pos.y > 98.0f || g_text[i].pos.y < -98.0f)
		{	// 上下
			angleY += 180.0f;
			angleY = (int)angleY % 360;
		}

		// 影を消す
		if (g_text[i].pos.y <= 0.0f) {
			ReleaseShadow(g_text[i].nShadowIdx);
			g_text[i].nShadowIdx = -1;
		}

		// ワールドマトリックスの初期化
		XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(
			g_text[i].scl.x,
			g_text[i].scl.y,
			g_text[i].scl.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_text[i].rot.x),
			XMConvertToRadians(g_text[i].rot.y),
			XMConvertToRadians(g_text[i].rot.z)
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(
			g_text[i].pos.x,
			g_text[i].pos.y,
			g_text[i].pos.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックス設定
		XMStoreFloat4x4(&g_text[i].mtxWorld, mtxWorld);

		// 影の移動
		MoveShadow(g_text[i].nShadowIdx, g_text[i].pos);

#ifdef _DEBUG

		PrintDebugProc("BallAngle X : %0.1f Y : %0.1f\n\n\n", angleX, angleY);
#endif // _DEBUG
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTex(void)
{
	for (int i = 0; i < MAX_TEXT; i++)
	{
		if (g_text[i].pos.z > GetPlayerPos(0).z - 5000.0f) {
			ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

			// モデル表示
			if (g_text[i].nState == 0)	continue;
			g_model[g_text[i].nType].Draw(pDeviceContext, g_text[i].mtxWorld);
		}
	}
}

// 設置
int SetText(XMFLOAT3 pos, XMFLOAT3 scl, XMFLOAT3 dir, int type)
{
	_tText* pText = g_text;
	for (int i = 0; i < MAX_TEXT; ++i, ++pText)
	{	// 出現している場合スルー
		if (pText->nState != 0) continue;

		pText->pos = pos;
		pText->scl = scl;
		pText->scl.z = scl.z = 8.0f;
		pText->vel.x = dir.x * TEXT_SPEED;
		pText->vel.y = dir.y * TEXT_SPEED;
		pText->vel.z = dir.z * TEXT_SPEED;
		pText->nState = 1;	// 出現
		pText->nType = type;

		// 影の作成
		pText->nShadowIdx = CreateShadow(pText->pos, 20.0f);

		return i;	// 番号を返す
	}
	return -1;	// 見つからなかった
}

XMFLOAT4X4 GetTextWorld(int no)
{
	return g_text[no].mtxWorld;
}

// 中心座標所得
XMFLOAT3 GetTextCenter(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMFLOAT3 pos = g_model[g_text[no].nType].GetCenter();
	pos.x += g_text[no].pos.x;
	pos.y += g_text[no].pos.y;
	pos.z += g_text[no].pos.z;
	return pos;
}

// モデルサイズ所得
XMFLOAT3 GetTextBBox(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// モデルからサイズ半分を所得
	return g_model[g_text[no].nType].GetBBox();
}

// 座標所得
XMFLOAT3 GetTextPos(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_text[no].pos;
}

// サイズ所得
XMFLOAT3 GetTextSize(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return XMFLOAT3(g_text[no].scl.x, g_text[no].scl.y, g_text[no].scl.z);
}

// 生存しているか
bool IsText(int no)
{
	if (no < 0 || no >= MAX_TEXT || g_text[no].KillFlag == true) {
		return false;
	}
	return true;
}

// 表示しない
void DestroyText(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return;
	}
	g_text[no].nState = 0;
	ReleaseShadow(g_text[no].nShadowIdx);
	g_text[no].pos = XMFLOAT3(0.0f, -1000.0f, 0.0f);
}

void KillText(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return;
	}

	g_text[no].KillFlag = true;
}
