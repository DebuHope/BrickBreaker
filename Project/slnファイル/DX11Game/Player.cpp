//=============================================================================
// プレイヤー処理
// 制作：向出創
//=============================================================================
#define _USE_MATH_DEFINES
#include <math.h>
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Player.h"
#include "Shadow.h"
#include "main.h"
#include "Camera.h"
#include "input.h"
#include "UI.h"
#include "Transition.h"
#include "Life.h"
#include "Sound.h"
#include "Score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_RUN		"data/model/player/paddle.fbx"

#define MAX_PLAYER_MODEL	(1)

#define ROT_Y			(180.0f)
#define VALUE_MOVE		(4.0f)
#define VALUE_ROTATE	(5.0f)
#define GRAVITY			(-0.50f)

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
static int AnimCount;
static int DashCount;
static int SlideCount;
static int JumpCount;
static int JoyZCount;
static int InvincibleCount;
static int StartInvincibleCount;
static bool DownFlag;
static bool JoyTriggerFalg;

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
		//g_player[i].pos = XMFLOAT3(0.0f, 34.0f, 0.0f);
		g_player[i].rot = XMFLOAT3(0.0f, ROT_Y, 0.0f);
		g_player[i].scl = XMFLOAT3(3.0f, 3.0f, 3.0f);
		g_player[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_player[i].velXZ = XMFLOAT2(0.0f, 0.0f);
		g_player[i].nPhase = 0;
		g_player[i].nState = 1;	// プレイヤー初期は生存
		g_player[i].angle = 0.0f;


		if(GetSceneNo() == SCENE_ENDING)	g_player[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	AnimCount = 0;
	DashCount = 120;
	SlideCount = 40;
	JumpCount = 40;
	JoyZCount = 0;
	InvincibleCount = 0;
	StartInvincibleCount = 0;
	DownFlag = false;
	JoyTriggerFalg = false;

	// ワールドマトリックスの初期化
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		XMStoreFloat4x4(&g_player[i].mtxWorld, mtxWorld);
	}

	//// 影の作成
	//for (int i = 0; i < MAX_PLAYER; i++) {
	//	g_player[i].nShadowIdx = CreateShadow(g_player[i].pos, 20.0f);
	//}
}


//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	// 影の解放
	for (int i = 0; i < MAX_PLAYER; i++) {
		ReleaseShadow(g_player[i].nShadowIdx);
	}
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
	
		//if (GetKeyPress(VK_A))
		//{
		//	if (GetKeyPress(VK_W))		// 左上
		//	{
		//		g_player[i].vel.x = -VALUE_MOVE / 1.414f;
		//		g_player[i].vel.z = VALUE_MOVE / 1.414f;
		//	}
		//	else if (GetKeyPress(VK_S))	// 左下
		//	{
		//		g_player[i].vel.x = -VALUE_MOVE / 1.414f;
		//		g_player[i].vel.z = -VALUE_MOVE / 1.414f;
		//	}
		//	else						// 左
		//	{
		//		g_player[i].vel.x = -VALUE_MOVE;
		//	}
		//}
		//// 右関連
		//else if (GetKeyPress(VK_D))
		//{
		//	if (GetKeyPress(VK_W))		// 右上
		//	{
		//		g_player[i].vel.x = VALUE_MOVE / 1.414f;
		//		g_player[i].vel.z = VALUE_MOVE / 1.414f;
		//	}
		//	else if (GetKeyPress(VK_S))	// 右下
		//	{
		//		g_player[i].vel.x = VALUE_MOVE / 1.414f;
		//		g_player[i].vel.z = -VALUE_MOVE / 1.414f;
		//	}
		//	else						// 右
		//	{
		//		g_player[i].vel.x = VALUE_MOVE;
		//	}
		//}
		//else if (GetKeyPress(VK_W))		// 上
		//{
		//	g_player[i].vel.z = VALUE_MOVE;
		//}
		//else if (GetKeyPress(VK_S))	// 下
		//{
		//	g_player[i].vel.z = -VALUE_MOVE;
		//}
		//// ========================================================

		//// 回転
		//if (GetKeyPress(VK_Q))
		//{
		//	g_player[i].rot.y -= VALUE_ROTATE;
		//}
		//else if (GetKeyPress(VK_E))
		//{
		//	g_player[i].rot.y += VALUE_ROTATE;
		//}

		//// カメラの角度所得
		//CCamera* pCamera = GetCamera();
		//float camerarot = pCamera->GetAngle().y;
		//// 向いている方向に移動
		//if (GetKeyPress(VK_UP))
		//{
		//	g_player[i].vel.x = SinDeg(camerarot) * VALUE_MOVE;
		//	g_player[i].vel.z = CosDeg(camerarot) * VALUE_MOVE;
		//}
		//else if (GetKeyPress(VK_DOWN))
		//{
		//	g_player[i].vel.x = SinDeg(camerarot + 180.0f) * VALUE_MOVE;
		//	g_player[i].vel.z = CosDeg(camerarot + 180.0f) * VALUE_MOVE;
		//}
		//else if (GetKeyPress(VK_LEFT))
		//{
		//	g_player[i].vel.x = SinDeg(camerarot - 90.0f) * VALUE_MOVE;
		//	g_player[i].vel.z = CosDeg(camerarot - 90.0f) * VALUE_MOVE;
		//}
		//else if (GetKeyPress(VK_RIGHT))
		//{
		//	g_player[i].vel.x = SinDeg(camerarot + 90.0f) * VALUE_MOVE;
		//	g_player[i].vel.z = CosDeg(camerarot + 90.0f) * VALUE_MOVE;
		//}

		float radius = g_player[i].angle * M_PI / 180.0f;

		float add_x = cosf(radius) * g_player[i].scl.x;
		float add_y = sinf(radius) * g_player[i].scl.y;

		// 向きを変える
		if (GetKeyPress(VK_D))
		{
			g_player[i].angle -= 5.0f;
			g_player[i].pos.x = g_player[i].pos.x + add_x;
			g_player[i].pos.y = g_player[i].pos.y + add_y;
		}
		else if (GetKeyPress(VK_A))
		{
			g_player[i].angle += 5.0f;
			g_player[i].pos.x = g_player[i].pos.x - add_x;
			g_player[i].pos.y = g_player[i].pos.y - add_y;
		}
		else
		{
			//g_player[i].pos.y += g_player[i].vel.y;
		}

		// 重力を座標に加算
		//g_player[i].vel.y += GRAVITY;

		// 速度を座標に加算
		g_player[i].pos.x += g_player[i].vel.x;
		//g_player[i].pos.y += g_player[i].vel.y;
		g_player[i].pos.z += g_player[i].vel.z;

		// 初期化(キーを押していない間)
		g_player[i].vel.x = 0.0f;
		g_player[i].vel.z = 0.0f;

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

		// 影の移動
		MoveShadow(g_player[i].nShadowIdx, g_player[i].pos);
	}

	AnimCount++;
	DashCount++;
	SlideCount++;
	JumpCount++;
	StartInvincibleCount++;

	// パッドZ軸フラグ
	if (GetJoyCountSimple() == 1 && (GetJoyZ(0) < -20000)) {
		JoyZCount++;
	}
	else if (GetJoyCountSimple() == 1 && (GetJoyZ(0) > 20000)) {
		JoyZCount--;
	}
	else {
		JoyZCount = 0;
	}

	if(DownFlag) InvincibleCount++;
	if (InvincibleCount > 150) DownFlag = false;
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
	XMFLOAT3 size = g_model[0].GetBBox();
	return XMFLOAT3(
		size.x * g_player[no].scl.x,
		size.y * g_player[no].scl.y,
		size.z * g_player[no].scl.z);
}

// 座標所得
XMFLOAT3 GetPlayerPos(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_player[no].pos;
}

// サイズ所得
XMFLOAT3 GetPlayerSize(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_player[no].scl;
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
	ReleaseShadow(g_player[no].nShadowIdx);
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

float GetPlayerDashCount()
{
	return (float)DashCount / 120.0f;
}

float GetPlayerJumpCount()
{
	return (float)JumpCount / 40.0f;
}

float GetPlayerSlide()
{
	return (float)SlideCount / 50.0f;
}
