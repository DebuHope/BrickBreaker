//=============================================================================
// メインメニュー処理
// 制作：向出創
//=============================================================================

#include "Main.h"
#include "Select.h"
#include "Input.h"
#include "Bg.h"
#include "Street.h"
#include "Field.h"
#include "Player.h"
#include "Object.h"
#include "DEnemy.h"
#include "EF_Acceleration.h"
#include "UI.h"
#include "Transition.h"
#include "Shadow.h"
#include "Score.h"


#include "Endroll.h"
#include "Block.h"

//=============================================================================
// 初期化処理
//=============================================================================
void InitSelect()
{
	InitBg();
	//InitUI();
	InitStreet();
	InitField();
	InitObject();
	InitPlayer();
	InitDEnemy();
	InitScore();

	InitText();
	InitBlock();

	SetDrawTexNo(UI_MAINSELECT);

	// ブロックの配置			位置							サイズ		タイプ
	SetBlock(XMFLOAT3(-51.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-51.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-51.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-51.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-51.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-34.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-34.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-34.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-34.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-34.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-17.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-17.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-17.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-17.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(-17.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(0.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(0.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(0.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(0.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(0.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(17.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(17.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(17.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(17.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(17.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(34.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(34.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(34.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(34.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(34.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(51.0f, 70.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(51.0f, 65.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(51.0f, 60.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(51.0f, 55.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);
	SetBlock(XMFLOAT3(51.0f, 50.0f, 0.0f), XMFLOAT3(8.0f, 2.0f, 1.0f), 0);

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
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSelect()
{
	UninitBg();
	//UninitUI();
	UninitStreet();
	UninitField();
	UninitObject();
	UninitPlayer();

	UninitText();
	UninitBlock();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSelect()
{
	UpdateBg();
	//UpdateUI();
	UpdateStreet();
	UpdateField();
	UpdateObject();
	UpdatePlayer();

	UpdateText();
	UpdateBlock();

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
	DrawShadow();
	SetZWrite(true);
	// Zバッファ無効
	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);
	//DrawUI();
	//DrawTransition();
	SetBlendState(BS_NONE);
	// Zバッファ有効
	SetZBuffer(true);
}