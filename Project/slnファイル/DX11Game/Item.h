//======================================================================================
// アイテム処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

#include "Main.h"

// マクロ定義
#define MAX_ITEM  (300)     //弾の数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT LoadItem(void);
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

// 設置(pos = 出現位置, scl = 大きさ)
int SetItem(XMFLOAT3 pos, int scl);

XMFLOAT3 GetItemPos(int no);
XMFLOAT3 GetItemSize(int no);
bool	 IsItem(int no);
void	 DestroyItem(int no);
