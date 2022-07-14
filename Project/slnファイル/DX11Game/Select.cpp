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

//=============================================================================
// 初期化処理
//=============================================================================
void InitSelect()
{
	//InitBg();
	//InitUI();
	InitStreet();
	InitField();
	InitObject();
	InitPlayer();
	InitDEnemy();
	InitScore();

	SetDrawTexNo(UI_MAINSELECT);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSelect()
{
	//UninitBg();
	//UninitUI();
	UninitStreet();
	UninitField();
	UninitObject();
	UninitPlayer();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSelect()
{
	//UpdateBg();
	//UpdateUI();
	UpdateStreet();
	UpdateField();
	UpdateObject();
	UpdatePlayer();

	if (GetPlayerPos(0).z > 80000.0f)	StartChange(SCENE_SELECT, 0);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSelect()
{
	// Zバッファ無効
	SetZBuffer(false);
	//DrawBg();
	// Zバッファ有効
	SetZBuffer(true);
	//DrawStreet();
	//DrawField();
	//DrawObject();
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