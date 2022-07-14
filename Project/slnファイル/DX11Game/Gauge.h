//======================================================================================
// ゲージ処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

#include "main.h"

// マクロ定義
#define GAUGE_MAX	(100)

// プロトタイプ宣言
HRESULT LoadGauge();	//初期化
void UninitGauge(void);
// 座標は左端を指定
void DrawGaugeX(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no);
void DrawGaugeY1(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no);
void DrawGaugeY2(XMFLOAT2 pos, XMFLOAT2 size, float percent, int no);