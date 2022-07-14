//======================================================================================
// 加速エフェクト理処まとめ
// 制作：向出創
//======================================================================================
#pragma once

// ヘッダファイルのインクルード
#include"main.h"

// プロトタイプ宣言
HRESULT LoadAcceleration();		// 初期化
void	InitAcceleration();		// 初期化
void	UninitAcceleration();		// 終了
void	UpdateAcceleration();		// 更新
void	DrawAcceleration();		// 描画
