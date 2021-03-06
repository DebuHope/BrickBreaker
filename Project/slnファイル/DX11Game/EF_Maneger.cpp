//======================================================================================
// エフェクト管理
// 制作：向出創
//======================================================================================
#include "EF_Maneger.h"
#include "EffekseerManeger.h"
#include "Player.h"
#include "Game.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
EffekseerManeger*	g_effekt;
Effekseer::Handle	g_Handle;

//*****************************************************************************
// 初期化
//*****************************************************************************
void InitEFManeger()
{
	// Effekseerエフェクト
	g_effekt = new EffekseerManeger(GetDevice(), GetDeviceContext());
}

//*****************************************************************************
// 更新（管理部分）
//*****************************************************************************
void UpdateEFManeger()
{

}

//*****************************************************************************
// 描画
//*****************************************************************************
void DrawEFManeger()
{
	g_effekt->Draw();
}