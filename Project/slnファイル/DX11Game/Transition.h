//======================================================================================
// シーン遷移処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

//ヘッダファイルのインクルード
#include"main.h"

//プロトタイプ宣言
HRESULT LoadTransition();	//初期化
void	InitTransition();	//初期化
void	UninitTransition();	//終了
void	UpdateTransition();	//更新
void	DrawTransition();	//描画

void	StartChange(ETypeScene nextscene, int no);		// シーン切り替え