//======================================================================================
// 建物処理
// 制作：向出創
//======================================================================================
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Object.h"
#include "main.h"
#include "Camera.h"
#include "input.h"
#include "Player.h"
#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_BUILDING_01	"data/model/building/stage1/building_07.fbx"
#define MODEL_BUILDING_02	"data/model/building/stage1/building_09.fbx"
#define MODEL_BUILDING_03	"data/model/building/stage1/building_11.fbx"
#define MODEL_BUILDING_04	"data/model/building/stage1/building_12.fbx"
#define MODEL_BUILDING_05	"data/model/building/stage1/building_13.fbx"

#define MODEL_DECORATION_01	"data/model/building/stage2/decoration_01.fbx"
#define MODEL_DECORATION_02	"data/model/building/stage2/decoration_05.fbx"
#define MODEL_DECORATION_03	"data/model/building/stage2/decoration_06.fbx"
#define MODEL_DECORATION_04	"data/model/building/stage2/decoration_12.fbx"
#define MODEL_DECORATION_05	"data/model/building/stage2/decoration_15.fbx"

#define MODEL_BUILDING_06	"data/model/building/stage3/building_01.fbx"
#define MODEL_BUILDING_07	"data/model/building/stage3/building_02.fbx"
#define MODEL_BUILDING_08	"data/model/building/stage3/building_03.fbx"
#define MODEL_BUILDING_09	"data/model/building/stage3/building_04.fbx"
#define MODEL_BUILDING_10	"data/model/building/stage3/building_05.fbx"

#define MODEL_SIGN01		"data/model/building/kanban4.fbx"

#define MAX_OBJECT_MODEL	(16)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct _tObject
{
	XMFLOAT4X4	mtxWorld;

	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT3 scl;
}tObject;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAssimpModel	g_model[MAX_OBJECT_MODEL];
static tObject		g_object[MAX_OBJECT];

static float InitPosY;

static int DrawObjectType1;
static int DrawObjectType2;
static int DrawObjectType3;
static int DrawObjectType4;
static int DrawObjectType5;
static int DrawObjectType6;
static int DrawObjectType7;
static int DrawObjectType8;
static int DrawObjectType9;
static int DrawObjectType10;
static int DrawObjectType11;
static int DrawObjectType12;
static int DrawObjectType13;
static int DrawObjectType14;
static int DrawObjectType15;
static int DrawObjectType16;
static int DrawObjectType17;

HRESULT LoadObject(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// モデルデータの読み込み
	hr = g_model[0].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_01);
	hr = g_model[1].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_02);
	hr = g_model[2].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_03);
	hr = g_model[3].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_04);
	hr = g_model[4].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_05);

	hr = g_model[5].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_06);
	hr = g_model[6].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_07);
	hr = g_model[7].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_08);
	hr = g_model[8].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_09);
	hr = g_model[9].Load(pDevice, pDeviceContext,
		MODEL_BUILDING_10);

	hr = g_model[10].Load(pDevice, pDeviceContext,
		MODEL_DECORATION_01);
	hr = g_model[11].Load(pDevice, pDeviceContext,
		MODEL_DECORATION_02);
	hr = g_model[12].Load(pDevice, pDeviceContext,
		MODEL_DECORATION_03);
	hr = g_model[13].Load(pDevice, pDeviceContext,
		MODEL_DECORATION_04);
	hr = g_model[14].Load(pDevice, pDeviceContext,
		MODEL_DECORATION_05);

	hr = g_model[15].Load(pDevice, pDeviceContext,
		MODEL_SIGN01);

	return hr;

}

//=============================================================================
// 初期化処理
//=============================================================================
void InitObject(void)
{
	// 位置・回転・スケールの初期設定
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (GetUIState() == 0) {
			g_object[i].scl = XMFLOAT3(0.8f, 0.8f, 0.8f);
			InitPosY = g_object[i].pos.y = -10.0f;
		}
		else if (GetUIState() == 1) {
			g_object[i].scl = XMFLOAT3(2.0f, 2.0f, 2.0f);
			InitPosY = g_object[i].pos.y = -21.0f;
		}
		else if (GetUIState() == 2) {
			g_object[i].scl = XMFLOAT3(1.0f, 1.0f, 1.0f);
			InitPosY = g_object[i].pos.y = -11.0f;
		}
	}
	if (GetSceneNo() == SCENE_STAGE1_1 || GetSceneNo() == SCENE_STAGE1_2 || GetSceneNo() == SCENE_STAGE1_3 || GetSceneNo() == SCENE_STAGE1_4) {
		g_object[0].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 200.0f);
		g_object[0].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[1].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 400.0f);
		g_object[1].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[2].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 600.0f);
		g_object[2].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[3].pos = XMFLOAT3(-300.0f, InitPosY, GetPlayerPos(0).z + 800.0f);
		g_object[3].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[4].pos = XMFLOAT3(300.0f, InitPosY, GetPlayerPos(0).z + 1000.0f);
		g_object[4].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[5].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 1200.0f);
		g_object[5].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[6].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 1400.0f);
		g_object[6].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[7].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 1600.0f);
		g_object[7].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[8].pos = XMFLOAT3(320.0f, InitPosY, GetPlayerPos(0).z + 1800.0f);
		g_object[8].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[9].pos = XMFLOAT3(-320.0f, InitPosY, GetPlayerPos(0).z + 2000.0f);
		g_object[9].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[10].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 2200.0f);
		g_object[10].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[11].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 2400.0f);
		g_object[11].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[12].pos = XMFLOAT3(-320.0f, InitPosY, GetPlayerPos(0).z + 2600.0f);
		g_object[12].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[13].pos = XMFLOAT3(300.0f, InitPosY, GetPlayerPos(0).z + 2800.0f);
		g_object[13].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[14].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 3000.0f);
		g_object[14].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[15].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 3200.0f);
		g_object[15].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[16].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 3400.0f);
		g_object[16].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);
	}
	else {
		g_object[0].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 200.0f);
		g_object[0].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[1].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 400.0f);
		g_object[1].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[2].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 600.0f);
		g_object[2].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[3].pos = XMFLOAT3(-300.0f, InitPosY, GetPlayerPos(0).z + 800.0f);
		g_object[3].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[4].pos = XMFLOAT3(300.0f, InitPosY, GetPlayerPos(0).z + 1000.0f);
		g_object[4].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[5].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 1200.0f);
		g_object[5].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[6].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 1400.0f);
		g_object[6].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[7].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 1600.0f);
		g_object[7].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[8].pos = XMFLOAT3(320.0f, InitPosY, GetPlayerPos(0).z + 1800.0f);
		g_object[8].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[9].pos = XMFLOAT3(-320.0f, InitPosY, GetPlayerPos(0).z + 2000.0f);
		g_object[9].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[10].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 2200.0f);
		g_object[10].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[11].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 2400.0f);
		g_object[11].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[12].pos = XMFLOAT3(-320.0f, InitPosY, GetPlayerPos(0).z + 2600.0f);
		g_object[12].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[13].pos = XMFLOAT3(300.0f, InitPosY, GetPlayerPos(0).z + 2800.0f);
		g_object[13].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[14].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 3000.0f);
		g_object[14].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[15].pos = XMFLOAT3(280.0f, InitPosY, GetPlayerPos(0).z + 3200.0f);
		g_object[15].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[16].pos = XMFLOAT3(-280.0f, InitPosY, GetPlayerPos(0).z + 3400.0f);
		g_object[16].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[17].pos = XMFLOAT3(0.0f, -1000.0f, 0.0f);
		g_object[17].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);

		///////////////////////////////////////////////////////stage2
		g_object[18].pos = XMFLOAT3(680.0f, InitPosY, GetPlayerPos(0).z + 300.0f);
		g_object[18].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[19].pos = XMFLOAT3(-680.0f, InitPosY, GetPlayerPos(0).z + 50.0f);
		g_object[19].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[20].pos = XMFLOAT3(680.0f, InitPosY, GetPlayerPos(0).z + 700.0f);
		g_object[20].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[21].pos = XMFLOAT3(-700.0f, InitPosY, GetPlayerPos(0).z + 900.0f);
		g_object[21].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[22].pos = XMFLOAT3(700.0f, InitPosY, GetPlayerPos(0).z + 1100.0f);
		g_object[22].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[23].pos = XMFLOAT3(-680.0f, InitPosY, GetPlayerPos(0).z + 1300.0f);
		g_object[23].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[24].pos = XMFLOAT3(680.0f, InitPosY, GetPlayerPos(0).z + 1500.0f);
		g_object[24].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[25].pos = XMFLOAT3(-680.0f, InitPosY, GetPlayerPos(0).z + 1700.0f);
		g_object[25].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[26].pos = XMFLOAT3(720.0f, InitPosY, GetPlayerPos(0).z + 1900.0f);
		g_object[26].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[27].pos = XMFLOAT3(-720.0f, InitPosY, GetPlayerPos(0).z + 2100.0f);
		g_object[27].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[28].pos = XMFLOAT3(-680.0f, InitPosY, GetPlayerPos(0).z + 2300.0f);
		g_object[28].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[29].pos = XMFLOAT3(680.0f, InitPosY, GetPlayerPos(0).z + 2500.0f);
		g_object[29].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[30].pos = XMFLOAT3(-720.0f, InitPosY, GetPlayerPos(0).z + 2700.0f);
		g_object[30].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[31].pos = XMFLOAT3(700.0f, InitPosY, GetPlayerPos(0).z + 2900.0f);
		g_object[31].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[32].pos = XMFLOAT3(-680.0f, InitPosY, GetPlayerPos(0).z + 3100.0f);
		g_object[32].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);

		g_object[33].pos = XMFLOAT3(680.0f, InitPosY, GetPlayerPos(0).z + 3300.0f);
		g_object[33].rot = XMFLOAT3(0.0f, 90.0f, 0.0f);

		g_object[34].pos = XMFLOAT3(-680.0f, InitPosY, GetPlayerPos(0).z + 3500.0f);
		g_object[34].rot = XMFLOAT3(0.0f, -90.0f, 0.0f);
	}

	// 表示の初期化
	if (GetUIState() == 0) {
		DrawObjectType1 = 0;
		DrawObjectType2 = 1;
		DrawObjectType3 = 2;
		DrawObjectType4 = 3;
		DrawObjectType5 = 4;
		DrawObjectType6 = 2;
		DrawObjectType7 = 1;
		DrawObjectType8 = 0;
		DrawObjectType9 = 3;
		DrawObjectType10 = 4;
		DrawObjectType11 = 1;
		DrawObjectType12 = 2;
		DrawObjectType13 = 3;
		DrawObjectType14 = 4;
		DrawObjectType15 = 2;
		DrawObjectType16 = 1;
		DrawObjectType17 = 3;
	}
	else if (GetUIState() == 1) {
		DrawObjectType1 = 10;
		DrawObjectType2 = 11;
		DrawObjectType3 = 10;
		DrawObjectType4 = 13;
		DrawObjectType5 = 10;
		DrawObjectType6 = 10;
		DrawObjectType7 = 14;
		DrawObjectType8 = 10;
		DrawObjectType9 = 12;
		DrawObjectType10 = 13;
		DrawObjectType11 = 10;
		DrawObjectType12 = 14;
		DrawObjectType13 = 14;
		DrawObjectType14 = 10;
		DrawObjectType15 = 13;
		DrawObjectType16 = 12;
		DrawObjectType17 = 10;
	}
	else if (GetUIState() == 2) {
		DrawObjectType1 = 5;
		DrawObjectType2 = 6;
		DrawObjectType3 = 7;
		DrawObjectType4 = 8;
		DrawObjectType5 = 9;
		DrawObjectType6 = 6;
		DrawObjectType7 = 8;
		DrawObjectType8 = 5;
		DrawObjectType9 = 9;
		DrawObjectType10 = 8;
		DrawObjectType11 = 5;
		DrawObjectType12 = 7;
		DrawObjectType13 = 8;
		DrawObjectType14 = 5;
		DrawObjectType15 = 6;
		DrawObjectType16 = 9;
		DrawObjectType17 = 7;
	}

	if (GetSceneNo() == SCENE_ENDING) {
		DrawObjectType1 = 0;
		DrawObjectType2 = 1;
		DrawObjectType3 = 2;
		DrawObjectType4 = 3;
		DrawObjectType5 = 4;
		DrawObjectType6 = 2;
		DrawObjectType7 = 1;
		DrawObjectType8 = 0;
		DrawObjectType9 = 3;
		DrawObjectType10 = 4;
		DrawObjectType11 = 1;
		DrawObjectType12 = 2;
		DrawObjectType13 = 3;
		DrawObjectType14 = 4;
		DrawObjectType15 = 2;
		DrawObjectType16 = 1;
		DrawObjectType17 = 3;
	}

	// ワールドマトリックスの初期化
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		XMStoreFloat4x4(&g_object[i].mtxWorld, mtxWorld);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitObject(void)
{
	// モデルの解放
	//for (int i = 0; i < MAX_OBJECT_MODEL; i++) {
	//	g_model[i].Release();
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObject(void)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		// モデルの動きを記述するならここ

		// 過ぎた建物を移動させる
		if (GetSceneNo() != SCENE_ENDING) {
			if (i != 17) {
				if (g_object[i].pos.z <= GetPlayerPos(0).z - 150.0f) {
					g_object[i].pos.z = GetPlayerPos(0).z + 3400.0f;
				}
			}
		}
		else {
			if (i != 17) {
				if (g_object[i].pos.z <= GetPlayerPos(0).z - 3000.0f) {
					g_object[i].pos.z = GetPlayerPos(0).z + 500.0f;
				}
			}
		}

		XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(
			g_object[i].scl.x,
			g_object[i].scl.y,
			g_object[i].scl.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_object[i].rot.x),
			XMConvertToRadians(g_object[i].rot.y),
			XMConvertToRadians(g_object[i].rot.z)
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(
			g_object[i].pos.x,
			g_object[i].pos.y,
			g_object[i].pos.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックス設定
		XMStoreFloat4x4(&g_object[i].mtxWorld, mtxWorld);

		// ステージストリートを選んだ場合
		if (GetSceneNo() == SCENE_SELECT && GetDrawTexNo() == UI_STAGESELECT && GetUIPos(0).y == 0.0f ||
			GetSceneNo() == SCENE_STAGE1_1 || GetSceneNo() == SCENE_STAGE1_2 || GetSceneNo() == SCENE_STAGE1_3 || GetSceneNo() == SCENE_STAGE1_4)
		{
			g_object[i].scl = XMFLOAT3(0.8f, 0.8f, 0.8f);

			g_object[i].pos.y = -10.0f;
			DrawObjectType1 = 0;
			DrawObjectType2 = 1;
			DrawObjectType3 = 2;
			DrawObjectType4 = 3;
			DrawObjectType5 = 4;
			DrawObjectType6 = 2;
			DrawObjectType7 = 1;
			DrawObjectType8 = 0;
			DrawObjectType9 = 3;
			DrawObjectType10 = 4;
			DrawObjectType11 = 1;
			DrawObjectType12 = 2;
			DrawObjectType13 = 3;
			DrawObjectType14 = 4;
			DrawObjectType15 = 2;
			DrawObjectType16 = 1;
			DrawObjectType17 = 3;
		}
		// ステージフォレストを選んだ場合
		else if (GetSceneNo() == SCENE_SELECT && GetDrawTexNo() == UI_STAGESELECT && GetUIPos(0).y == 135.0f ||
			GetSceneNo() == SCENE_STAGE2_1 || GetSceneNo() == SCENE_STAGE2_2 || GetSceneNo() == SCENE_STAGE2_3 || GetSceneNo() == SCENE_STAGE2_4)
		{
			g_object[i].scl = XMFLOAT3(2.0f, 2.0f, 2.0f);
			g_object[i].pos.y = -21.0f;
			DrawObjectType1 =  10;
			DrawObjectType2 =  11;
			DrawObjectType3 =  10;
			DrawObjectType4 =  13;
			DrawObjectType5 =  10;
			DrawObjectType6 =  10;
			DrawObjectType7 =  14;
			DrawObjectType8 =  10;
			DrawObjectType9 =  12;
			DrawObjectType10 = 13;
			DrawObjectType11 = 10;
			DrawObjectType12 = 14;
			DrawObjectType13 = 14;
			DrawObjectType14 = 10;
			DrawObjectType15 = 13;
			DrawObjectType16 = 12;
			DrawObjectType17 = 10;
		}
		// ステージナイトストリートを選んだ場合
		else if (GetSceneNo() == SCENE_SELECT && GetDrawTexNo() == UI_STAGESELECT && GetUIPos(0).y == 270.0f ||
			GetSceneNo() == SCENE_STAGE2_1 || GetSceneNo() == SCENE_STAGE2_2 || GetSceneNo() == SCENE_STAGE2_3 || GetSceneNo() == SCENE_STAGE2_4)
		{
			g_object[i].scl = XMFLOAT3(1.0f, 1.0f, 1.0f);
			g_object[i].pos.y = -11.0f;
			DrawObjectType1 = 5;
			DrawObjectType2 = 6;
			DrawObjectType3 = 7;
			DrawObjectType4 = 8;
			DrawObjectType5 = 9;
			DrawObjectType6 = 6;
			DrawObjectType7 = 8;
			DrawObjectType8 = 5;
			DrawObjectType9 = 9;
			DrawObjectType10 = 8;
			DrawObjectType11 = 5;
			DrawObjectType12 = 7;
			DrawObjectType13 = 8;
			DrawObjectType14 = 5;
			DrawObjectType15 = 6;
			DrawObjectType16 = 9;
			DrawObjectType17 = 7;
		}
	}
	//PrintDebugProc("ObjectPos:%0.2f\n", g_object[0].pos.z);
}

// 看板セット
void SetSign(XMFLOAT3 pos, XMFLOAT3 rot)
{
	g_object[17].pos = pos;
	g_object[17].rot = rot;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObject(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// モデル表示
	g_model[DrawObjectType1].Draw(pDeviceContext, g_object[0].mtxWorld);
	g_model[DrawObjectType2].Draw(pDeviceContext, g_object[1].mtxWorld);
	g_model[DrawObjectType3].Draw(pDeviceContext, g_object[2].mtxWorld);
	g_model[DrawObjectType4].Draw(pDeviceContext, g_object[3].mtxWorld);
	g_model[DrawObjectType5].Draw(pDeviceContext, g_object[4].mtxWorld);
	g_model[DrawObjectType6].Draw(pDeviceContext, g_object[5].mtxWorld);
	g_model[DrawObjectType7].Draw(pDeviceContext, g_object[6].mtxWorld);
	g_model[DrawObjectType8].Draw(pDeviceContext, g_object[7].mtxWorld);
	g_model[DrawObjectType9].Draw(pDeviceContext, g_object[8].mtxWorld);
	g_model[DrawObjectType10].Draw(pDeviceContext, g_object[9].mtxWorld);
	g_model[DrawObjectType11].Draw(pDeviceContext, g_object[10].mtxWorld);
	g_model[DrawObjectType11].Draw(pDeviceContext, g_object[11].mtxWorld);
	g_model[DrawObjectType12].Draw(pDeviceContext, g_object[12].mtxWorld);
	g_model[DrawObjectType13].Draw(pDeviceContext, g_object[13].mtxWorld);
	g_model[DrawObjectType14].Draw(pDeviceContext, g_object[14].mtxWorld);
	g_model[DrawObjectType15].Draw(pDeviceContext, g_object[15].mtxWorld);
	g_model[DrawObjectType16].Draw(pDeviceContext, g_object[16].mtxWorld);

	g_model[15].Draw(pDeviceContext, g_object[17].mtxWorld);

	if (GetUIState() == 1 ||
		GetSceneNo() == SCENE_STAGE1_1 || GetSceneNo() == SCENE_STAGE1_2 || GetSceneNo() == SCENE_STAGE1_3 || GetSceneNo() == SCENE_STAGE1_4) {

		g_model[DrawObjectType5].Draw(pDeviceContext, g_object[18].mtxWorld);
		g_model[DrawObjectType3].Draw(pDeviceContext, g_object[19].mtxWorld);
		g_model[DrawObjectType7].Draw(pDeviceContext, g_object[20].mtxWorld);
		g_model[DrawObjectType8].Draw(pDeviceContext, g_object[21].mtxWorld);
		g_model[DrawObjectType1].Draw(pDeviceContext, g_object[22].mtxWorld);
		g_model[DrawObjectType3].Draw(pDeviceContext, g_object[23].mtxWorld);
		g_model[DrawObjectType16].Draw(pDeviceContext, g_object[24].mtxWorld);
		g_model[DrawObjectType12].Draw(pDeviceContext, g_object[25].mtxWorld);
		g_model[DrawObjectType10].Draw(pDeviceContext, g_object[26].mtxWorld);
		g_model[DrawObjectType4].Draw(pDeviceContext, g_object[27].mtxWorld);
		g_model[DrawObjectType6].Draw(pDeviceContext, g_object[28].mtxWorld);
		g_model[DrawObjectType8].Draw(pDeviceContext, g_object[29].mtxWorld);
		g_model[DrawObjectType9].Draw(pDeviceContext, g_object[30].mtxWorld);
		g_model[DrawObjectType7].Draw(pDeviceContext, g_object[31].mtxWorld);
		g_model[DrawObjectType2].Draw(pDeviceContext, g_object[32].mtxWorld);
		g_model[DrawObjectType14].Draw(pDeviceContext, g_object[33].mtxWorld);
		g_model[DrawObjectType13].Draw(pDeviceContext, g_object[34].mtxWorld);
	}
}

// 座標所得
XMFLOAT3 GetObjectPos(int no)
{
	if (no < 0 || no >= MAX_OBJECT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_object[no].pos;
}
// 角度所得
XMFLOAT3 GetObjectRot(int no)
{
	if (no < 0 || no >= MAX_OBJECT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_object[no].rot;
}