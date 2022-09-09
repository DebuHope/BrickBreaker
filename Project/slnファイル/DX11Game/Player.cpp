//=============================================================================
// プレイヤー処理
// 制作：向出創
//=============================================================================
#define _USE_MATH_DEFINES
#include <math.h>
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Player.h"
#include "main.h"
#include "Camera.h"
#include "input.h"
#include "Transition.h"
#include "Life.h"
#include "Sound.h"
#include "Score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_RUN		"data/model/player/padlle_01.fbx"

#define MAX_PLAYER_MODEL	(1)

#define ROT_Y			(180.0f)
#define VALUE_MOVE		(3.0f)
#define VALUE_ROTATE	(5.0f)
#define GRAVITY			(-0.50f)

#define LIMIT_LEFT	-98
#define LIMIT_RIGHT	98

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct _tPlayer
{
	XMFLOAT4X4	mtxWorld;

	XMFLOAT3 pos;	// 座標
	XMFLOAT3 rot;	// 回転
	float	angle;	// 回転移動用
	XMFLOAT3 scl;	// 拡大率
	XMFLOAT3 vel;	// 速度
	XMFLOAT2 velXZ;	// 前移動用速度

	int		nPhase;	// 行動パターンの段階
	int		nState;	// 行動(0以下:未使用 1以上:通常)
	int		nShadowIdx;	// 影の番号
}tPlayer;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAssimpModel	g_model[MAX_PLAYER_MODEL];	// モデルデータ
static tPlayer		g_player[MAX_PLAYER];	// プレイヤー数

HRESULT LoadPlayer(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// モデルデータの読み込み
	hr = g_model[0].Load(pDevice, pDeviceContext,
		MODEL_RUN);

	return hr;
}

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	// 位置・回転・スケールの初期設定
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_player[i].pos = XMFLOAT3(0.0f, -75.0f, 0.0f);
		g_player[i].rot = XMFLOAT3(0.0f, ROT_Y, 0.0f);
		g_player[i].scl = XMFLOAT3(15.0f, 1.0f, 1.0f);
		g_player[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_player[i].velXZ = XMFLOAT2(0.0f, 0.0f);
		g_player[i].nPhase = 0;
		g_player[i].nState = 1;	// プレイヤー初期は生存
		g_player[i].angle = 0.0f;
	}

	// ワールドマトリックスの初期化
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		XMStoreFloat4x4(&g_player[i].mtxWorld, mtxWorld);
	}
}


//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	// モデルの解放
	//for (int i = 0; i < MAX_PLAYER_MODEL; i++) {
	//	g_model[i].Release();
	//}
	StopSound(SOUND_LABEL_SE_RUN);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (g_player[i].nState == 0)	continue;
	
		// 左右移動
		if (GetKeyPress(VK_A))
		{
			g_player[i].vel.x = -VALUE_MOVE;
		}
		else if (GetKeyPress(VK_D))
		{
			g_player[i].vel.x = VALUE_MOVE;
		}

#pragma region circular motion
		//float radius = g_player[i].angle * M_PI / 180.0f;

		//float add_x = cosf(radius) * g_player[i].scl.x;
		//float add_y = sinf(radius) * g_player[i].scl.y;

		//if (GetKeyPress(VK_D))
		//{
		//	g_player[i].angle -= 5.0f;
		//	g_player[i].pos.x = g_player[i].pos.x + add_x;
		//	g_player[i].pos.y = g_player[i].pos.y + add_y;
		//}
		//else if (GetKeyPress(VK_A))
		//{
		//	g_player[i].angle += 5.0f;
		//	g_player[i].pos.x = g_player[i].pos.x - add_x;
		//	g_player[i].pos.y = g_player[i].pos.y - add_y;
		//}
#pragma endregion

		// 重力を座標に加算
		//g_player[i].vel.y += GRAVITY;

		// 速度を座標に加算
		g_player[i].pos.x += g_player[i].vel.x;
		g_player[i].pos.y += g_player[i].vel.y;

		// 初期化(キーを押していない間)
		g_player[i].vel.x = 0.0f;
		g_player[i].vel.z = 0.0f;

		// 画面外判定
		if (g_player[i].pos.x > 110.0f)
		{
			g_player[i].pos.x = 110.0f;
		}
		else if (g_player[i].pos.x < -110.0f)
		{
			g_player[i].pos.x = -110.0f;
		}

		//================================================================
		XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(
			g_player[i].scl.x,
			g_player[i].scl.y,
			g_player[i].scl.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_player[i].rot.x),
			XMConvertToRadians(g_player[i].rot.y),
			XMConvertToRadians(g_player[i].rot.z)
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(
			g_player[i].pos.x,
			g_player[i].pos.y,
			g_player[i].pos.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックス設定
		XMStoreFloat4x4(&g_player[i].mtxWorld, mtxWorld);
	}

#ifdef _DEBUG
	PrintDebugProc("PlayerPos X : %0.1f Y : %0.1f\n\n", GetPlayerPos(0).x, GetPlayerPos(0).y);
#endif // _DEBUG
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	g_model[0].Draw(pDeviceContext, g_player[0].mtxWorld);
}

XMFLOAT4X4 GetPlayerWorld(int no)
{
	return g_player[no].mtxWorld;
}

// 中心座標所得
XMFLOAT3 GetPlayerCenter(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMFLOAT3 pos = g_model[0].GetCenter();
	pos.x += g_player[no].pos.x;
	pos.y += g_player[no].pos.y;
	pos.z += g_player[no].pos.z;
	return pos;
}

// モデルサイズ所得
XMFLOAT3 GetPlayerBBox(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// モデルからサイズ半分を所得
	return g_model[0].GetBBox();
}

// 座標所得
XMFLOAT3 GetPlayerPos(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_player[no].pos;
}

//// サイズ所得
//XMFLOAT3 GetPlayerSize(int no)
//{
//	if (no < 0 || no >= MAX_PLAYER) {
//		return XMFLOAT3(0.0f, 0.0f, 0.0f);
//	}
//	return g_player[no].scl;
//}

// サイズ所得
XMFLOAT3 GetPlayerSize(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return XMFLOAT3(g_player[no].scl.x, g_player[no].scl.y, g_player[no].scl.z);
}

// 生存しているか
bool IsPlayer(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return false;
	}
	return true;
}

// 表示しない
void DestroyPlayer(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return;
	}
	g_player[no].nState = 0;
	g_player[no].nShadowIdx = -1;
}

// 速度所得
XMFLOAT3 GetPlayerVel(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_player[no].vel;
}