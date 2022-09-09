//=============================================================================
// メインメニュー処理
// 制作：向出創
//=============================================================================

#include "Main.h"
#include "Select.h"
#include "Input.h"
#include "Bg.h"
#include "Player.h"
#include "EF_Acceleration.h"
#include "Transition.h"
#include "Score.h"
#include "Endroll.h"
#include "Block.h"
#include "Polygon.h"

// メインフレームenum
enum GAME_STATE
{
	game_start,
	game_main,
	game_deth,
	game_claer,
	game_max

};

//グローバル変数
static GAME_STATE state;
static int count;
static XMFLOAT2 PolyPos;
static ID3D11DeviceContext* DeviceContext;


//=============================================================================
// 初期化処理
//=============================================================================
void InitSelect()
{
	InitBg();
	InitPlayer();
	InitScore(0);

	InitText();
	InitBlock();


	// ブロックの配置			位置							サイズ		タイプ

	//ステージ２
	SetBlock(XMFLOAT3(82.5f, 44.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(99.0f, 44.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(115.5f, 44.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-82.5f, 44.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-99.0f, 44.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-115.5f, 44.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);

	SetBlock(XMFLOAT3(99.0f, 38.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(82.5f, 38.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(66.0f, 38.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-99.0f, 38.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-82.5f, 38.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-66.0f, 38.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);

	SetBlock(XMFLOAT3(99.0f, 33.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(82.5f, 33.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(66.0f, 33.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(49.5f, 33.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-99.0f, 33.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-82.5f, 33.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-66.0f, 33.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-49.5f, 33.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);

	SetBlock(XMFLOAT3(99.0f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(82.5f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(66.0f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(49.5, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(33.0f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(16.5f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(0.0f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-99.0f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-82.5f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-66.0f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-49.5, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-33.0f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-16.5f, 27.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);

	SetBlock(XMFLOAT3(99.0f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(82.5f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(66.0f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(49.5f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(33.0f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(16.5f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(0.0f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-99.0f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-82.5f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-66.0f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-49.5, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-33.0f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);
	SetBlock(XMFLOAT3(-16.5f, 22.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 0);

	SetBlock(XMFLOAT3(99.0f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);
	SetBlock(XMFLOAT3(82.5f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);
	SetBlock(XMFLOAT3(66.0f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);
	SetBlock(XMFLOAT3(49.5f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);
	SetBlock(XMFLOAT3(33.0f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);
	SetBlock(XMFLOAT3(-99.0f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);
	SetBlock(XMFLOAT3(-82.5f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);
	SetBlock(XMFLOAT3(-66.0f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);
	SetBlock(XMFLOAT3(-49.5f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);
	SetBlock(XMFLOAT3(-33.0f, 16.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);

	//SetBlock(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f),  0);
	//SetBlock(XMFLOAT3(0.0f, 5.5f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f),  0);
	//SetBlock(XMFLOAT3(16.5f, 0.0f, 0.0f), XMFLOAT3(8.0f, 2.5f, 1.0f), 1);

	//SetBlock(XMFLOAT3(-51.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-51.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-34.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-34.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-34.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-34.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-34.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-17.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-17.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-17.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-17.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-17.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(0.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(0.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(0.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(0.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(0.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(17.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(17.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(17.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(17.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(17.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(34.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(34.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(34.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(34.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(34.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(51.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(51.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(51.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(51.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(51.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);

	//SetBlock(XMFLOAT3(0.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(10.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-10.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(20.0f, 75.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-20.0f, 75.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(30.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-30.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(35.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-35.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(40.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-40.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(40.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-40.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(40.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-40.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(35.0f, 45.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-35.0f, 45.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(25.0f, 40.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-25.0f, 40.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(20.0f, 35.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-20.0f, 35.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(15.0f, 30.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-15.0f, 30.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(10.0f, 25.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(-10.0f, 25.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	//SetBlock(XMFLOAT3(0.0f, 20.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);

	state = GAME_STATE::game_start;
	count = 0;
	PolyPos = XMFLOAT2(0, 0);
	DeviceContext = GetDeviceContext();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSelect()
{
	UninitBg();
	UninitPlayer();

	UninitText();
	UninitBlock();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSelect()
{
	switch (state)
	{
	case game_start:

		if (count > 30)
		{
			state = game_main;
			count = 0;

		}
		else count++;

		break;
	case game_main:

		UpdateBg();
		UpdatePlayer();
		UpdateScore();
		UpdateBlock();

		UpdateText();

		//プレイヤーが死んだとき
		if (
			IsText(0))
		{
			if (count > 30)
			{
				state = game_deth;
				count = 0;

			}
			else count++;

		}

		if (!IsBlock())
		{
			if (count > 30)
			{
				state = game_claer;
				count = 0;
		
			}
			else count++;

		}

		break;
	case game_deth:		// ボールが画面下にいったとき

		break;
	case game_claer:	// ブロックを全て壊した時

		break;
	}


	if (GetPlayerPos(0).z > 80000.0f)	StartChange(SCENE_SELECT, 0);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSelect()
{

	// Zバッファ無効
	SetZBuffer(false);
	DrawBg();
	// Zバッファ有効
	SetZBuffer(true);
	//DrawStreet();
	//DrawField();
	//DrawObject();
	DrawBlock();
	DrawTex();
	DrawPlayer();
	SetZWrite(false);	// 影設定変更影を綺麗に
	SetZWrite(true);
	// Zバッファ無効
	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);
	//DrawUI();
	//DrawTransition();
	DrawScore();

	switch (state)
	{
	case game_start:
		SetPolygonSize(300, 50);
		SetPolygonPos(PolyPos.x, PolyPos.y);
		SetPolygonColor(0, 0, 0);
		DrawPolygon(DeviceContext);

		break;
	case game_main:

		break;
	case game_deth:
		SetPolygonSize(300, 50);
		SetPolygonPos(PolyPos.x, PolyPos.y);
		SetPolygonColor(255, 0, 0);
		DrawPolygon(DeviceContext);

		break;
	case game_claer:
		SetPolygonSize(300, 50);
		SetPolygonPos(PolyPos.x, PolyPos.y);
		SetPolygonColor(0, 0, 255);
		DrawPolygon(DeviceContext);

		break;
	}

	SetBlendState(BS_NONE);
	// Zバッファ有効
	SetZBuffer(true);
}