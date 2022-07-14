//======================================================================================
// 影処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

#include "Main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT LoadShadow(void);
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int CreateShadow(XMFLOAT3 pos, float radius);
void MoveShadow(int nShadow, XMFLOAT3 pos);
void ReleaseShadow(int nShadow);