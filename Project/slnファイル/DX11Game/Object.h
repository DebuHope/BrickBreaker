//======================================================================================
// 建物処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

#include "Main.h"

#define MAX_OBJECT		(40)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT		LoadObject(void);
void		InitObject(void);
void		UninitObject(void);
void		UpdateObject(void);
void		DrawObject(void);

// 設置(pos = 出現位置, rot = 向き)
void		SetSign(XMFLOAT3 pos, XMFLOAT3 rot);

XMFLOAT3	GetObjectPos(int no); 
XMFLOAT3	GetObjectRot(int no);
