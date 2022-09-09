//=============================================================================
// タイトル処理
// 制作：向出創
//=============================================================================

#include "Main.h"
#include "Title.h"
#include "Input.h"
#include "Bg.h"
#include "Player.h"
#include "Transition.h"

#include "Polygon.h"
#include "Texture.h"


//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle()
{
	InitPlayer();
	InitBg();
	InitTransition();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle()
{
	UninitPlayer();
	UninitBg();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle()
{
	UpdatePlayer();
	UpdateBg();
	// キー	１～２５６　　　　　パッド　０～３１
	for (int i = 1; i < 256; i++) {		
		if (GetKeyRelease(i)) {
			StartChange(SCENE_SELECT, 0);
		}
	}

	for (int i = 0; i < 31; i++) {
		if (GetJoyCountSimple() == 1 && GetJoyRelease(0, i)) {
			StartChange(SCENE_SELECT, 0);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle()
{
	// Zバッファ無効
	SetZBuffer(false);
	DrawBg();
	// Zバッファ有効
	SetZBuffer(true);

	//// 影描画
	//SetZWrite(false);	// 影設定変更影を綺麗に
	//DrawShadow();
	//SetZWrite(true);

	// Zバッファ無効
	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);
	DrawTransition();
	SetBlendState(BS_NONE);
	// Zバッファ有効
	SetZBuffer(true);
}