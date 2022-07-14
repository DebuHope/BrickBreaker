//======================================================================================
// 地面処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

#include "Main.h"

#define MAX_FIELD (200)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT LoadField(void);
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

XMFLOAT3 GetFieldPos(int no);
XMFLOAT3 GetFieldSize(int no);
bool IsField(int no);