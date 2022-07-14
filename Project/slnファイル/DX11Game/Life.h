//======================================================================================
// ライフ処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

// ヘッダファイルのインクルード
#include"main.h"

// プロトタイプ宣言
HRESULT LoadLife();		// 初期化
void	InitLife();		// 初期化
void	UninitLife();	// 終了
void	UpdateLife();	// 更新
void	DrawLife();		// 描画

int		RemainingLife(int num);
int		RecoveryLife(int num);