//======================================================================================
// スコア処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

// ヘッダファイルのインクルード
#include"main.h"

// マクロ定義
#define MAX_SCORE	(3)	// 最大弾数

// プロトタイプ宣言
void	InitScore();	// 初期化
void	UninitScore();	// 終了
void	UpdateScore();	// 更新
void	DrawScore();	// 描画

void	AddCountItem(int num);		// アイテムカウント
void	AddCountCombo(int num);		// コンボカウント
void	AddCountKill(int num);		// 撃破カウント
int		GetScore(int no);
int		GetScore2(int no1, int no2);
void	SetBeforeScore();
int		GetComboCount();
void	SetComboCount();
bool	GetSPStateS();
bool	GetSPStateF();
bool	GetSPStateN();