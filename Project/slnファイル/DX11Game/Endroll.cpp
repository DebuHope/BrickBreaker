//======================================================================================
// エンドロール処理
// 制作：向出創
//======================================================================================
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Endroll.h"
#include "main.h"
#include "Player.h"
#include "Input.h"
#include "Collision.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CREDIT01	"data/model/text/ball_01.fbx"

#define MAX_TEXT_MODEL		(1)

#define TEXT_SPEED		(2.0f)

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
	XMFLOAT3 last;	// 直前の座標
	int	invincibleTime;
	int nShadowIdx;
	bool	KillFlag;	// キルフラグ
	int		nState;	// 行動(0以下:未使用 1以上:通常)
}tText;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAssimpModel	g_model[MAX_TEXT_MODEL];	// モデルデータ
static tText			g_ball[MAX_TEXT];

static float speed = 1.4f;
static float angleX = 270.0f;
static float angleY = 50.0f;
static int a = 0;

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
		g_ball[i].pos = XMFLOAT3(0.0f, 30.0f, 0.0f);
		g_ball[i].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_ball[i].scl = XMFLOAT3(3.0f, 3.0f, 3.0f);
		g_ball[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_ball[i].nState = 1;
		g_ball[i].KillFlag = false;
		g_ball[i].invincibleTime = 0;
	}

	// ワールドマトリックスの初期化
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_TEXT; i++)
	{
		XMStoreFloat4x4(&g_ball[i].mtxWorld, mtxWorld);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitText(void)
{
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
		if (g_ball[i].KillFlag) continue;
		if (g_ball[i].nState == 0)	continue;

		g_ball[i].invincibleTime++;

		if (GetKeyPress(VK_X))
		{
			angleX += 10.0f;
		}

		else if (GetKeyPress(VK_V))
		{
			angleY += 10.0f;
		}

		// 直前の位置を保存(ブロックとの判定用) 
		g_ball[i].last.x = g_ball[i].pos.x;
		g_ball[i].last.y = g_ball[i].pos.y;
		g_ball[i].last.z = g_ball[i].pos.z;

		//				  原点    速度       角度
		g_ball[i].vel.x = (float)(0.0f + speed * cosf(angleX * (M_PI / 180.0f)));
		g_ball[i].vel.y = (float)(0.0f + speed * sinf(angleY * (M_PI / 180.0f)));

		// ボールがパドルに当たった時
		if (g_ball[i].pos.y < GetPlayerPos(0).y + 4.5f && g_ball[i].pos.y > GetPlayerPos(0).y - 2.0f &&
			g_ball[i].pos.x <= GetPlayerPos(0).x + 18.0f && g_ball[i].pos.x >= GetPlayerPos(0).x &&
			g_ball[i].invincibleTime > 20)
		{
			g_ball[i].pos.y = -71.0f;
			angleY += 180;
			if (angleX < 270.0f && angleX > 90.0f)
			{
				angleX = 270 + rand() % 180;
			}
			g_ball[i].invincibleTime = 0;
			a = 1;
		}
		else if (g_ball[i].pos.y < GetPlayerPos(0).y + 4.5f && g_ball[i].pos.y > GetPlayerPos(0).y - 2.0f &&
			g_ball[i].pos.x <= GetPlayerPos(0).x && g_ball[i].pos.x >= GetPlayerPos(0).x - 18.0f &&
			g_ball[i].invincibleTime > 20)
		{
			g_ball[i].pos.y = -71.0f;
			angleY += 180;
			if (angleX < 90.0f || angleX > 270.0f)
			{
				angleX = 90 + rand() % 180;
			}
			g_ball[i].invincibleTime = 0;
			a = 2;
		}


		// 位置の更新
		g_ball[i].pos.x += g_ball[i].vel.x;
		g_ball[i].pos.y += g_ball[i].vel.y;
		g_ball[i].pos.z += g_ball[i].vel.z;

		// 画面外判定
		if (g_ball[i].pos.x > 120.5f || g_ball[i].pos.x < -120.5f)
		{	// 左右
			angleX += 180.0f;
		}
		else if (g_ball[i].pos.y > 90.0f)
		{	// 上下
			angleY += 180.0f;
		}
		else if (g_ball[i].pos.y < -98.0f)
			g_ball[i].KillFlag = true;

		// angle 正規化
		if (angleX < 0.0f)
		{
			angleX *= -1.0f;
		}
		if (angleY < 0.0f)
		{
			angleY *= -1.0f;
		}
		angleX = (int)angleX % 360;
		angleY = (int)angleY % 360;

		// 影を消す
		if (g_ball[i].pos.y <= 0.0f) {
			g_ball[i].nShadowIdx = -1;
		}

		// ワールドマトリックスの初期化
		XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(
			g_ball[i].scl.x,
			g_ball[i].scl.y,
			g_ball[i].scl.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_ball[i].rot.x),
			XMConvertToRadians(g_ball[i].rot.y),
			XMConvertToRadians(g_ball[i].rot.z)
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(
			g_ball[i].pos.x,
			g_ball[i].pos.y,
			g_ball[i].pos.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックス設定
		XMStoreFloat4x4(&g_ball[i].mtxWorld, mtxWorld);

#ifdef _DEBUG

		PrintDebugProc("BallAngle X : %0.1f Y : %0.1f\n\n\n", angleX, angleY);
		PrintDebugProc("%d\n\n\n", a);
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
		if (g_ball[i].pos.z > GetPlayerPos(0).z - 5000.0f) {
			ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

			// モデル表示
			if (g_ball[i].nState == 0)	continue;
			g_model[g_ball[i].nType].Draw(pDeviceContext, g_ball[i].mtxWorld);
		}
	}
}

// 設置
int SetText(XMFLOAT3 pos, XMFLOAT3 scl, XMFLOAT3 dir, int type)
{
	_tText* pText = g_ball;
	for (int i = 0; i < MAX_TEXT; ++i, ++pText)
	{	// 出現している場合スルー
		if (pText->nState != 0) continue;

		pText->pos = pos;
		pText->scl = scl;
		pText->nState = 1;	// 出現
		pText->nType = type;

		return i;	// 番号を返す
	}
	return -1;	// 見つからなかった
}

XMFLOAT4X4 GetTextWorld(int no)
{
	return g_ball[no].mtxWorld;
}

// 中心座標所得
XMFLOAT3 GetTextCenter(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMFLOAT3 pos = g_model[g_ball[no].nType].GetCenter();
	pos.x += g_ball[no].pos.x;
	pos.y += g_ball[no].pos.y;
	pos.z += g_ball[no].pos.z;
	return pos;
}

// モデルサイズ所得
XMFLOAT3 GetTextBBox(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// モデルからサイズ半分を所得
	return g_model[g_ball[no].nType].GetBBox();
}

// 座標所得
XMFLOAT3 GetTextPos(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_ball[no].pos;
}

// サイズ所得
XMFLOAT3 GetTextSize(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return XMFLOAT3(g_ball[no].scl.x, g_ball[no].scl.y, g_ball[no].scl.z);
}

// 生存しているか
bool IsText(int no)
{
	if (no >= 0 || no >= MAX_TEXT) {
		return g_ball[no].KillFlag;
	}

}

// 表示しない
void DestroyText(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return;
	}
	g_ball[no].nState = 0;
	g_ball[no].pos = XMFLOAT3(0.0f, -1000.0f, 0.0f);
}

void PadlleBall(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return;
	}

}

void SetAngleX(float _angleX)
{
	angleX += _angleX;
}

void SetAngleY(float _angleY)
{
	angleY += _angleY;
}

float GetBallAngleX(int no)
{
	return angleX;
}

float GetBallAngleY(int no)
{
	return angleY;
}

void CheckBallHitDirection(XMFLOAT3 * BCenter, XMFLOAT3 * BSize)
{
	// どの方向から接触したのかチェック
	for (int i = 0; i < MAX_TEXT; i++) {
		// ブロックの幅の範囲にいた : yのみ反転
		if ((BCenter->x - BSize->x / 2) <= g_ball[i].last.x + 3.0f &&
			(BCenter->x + BSize->x / 2) >= g_ball[i].last.x - 3.0f) {
			SetAngleY(180.0f);
			//g_ball[i].vel.y = -g_ball[i].vel.y;
		}
		// ブロックの高さの範囲にいた : xのみ反転
		if ((BCenter->y - BSize->y / 2) <= g_ball[i].last.y + 3.0f &&
			(BCenter->y + BSize->y / 2) >= g_ball[i].last.y - 3.0f) {
			SetAngleX(180.0f);
			//g_ball[i].vel.x = -g_ball[i].vel.x;
		}
		// ブロックの奥行の範囲にいた
		// 未定義

		// それ以外に当たる(角に当たる) : xy反転
		//SetAngleX(180.0f);
		//SetAngleY(180.0f);
		//g_ball[i].vel.x = -g_ball[i].vel.x;
		//g_ball[i].vel.y = -g_ball[i].vel.y;
	}
}
