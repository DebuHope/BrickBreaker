//======================================================================================
// エンドロール処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

#include "Main.h"

#define MAX_BLOCK		(100)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT LoadBlock(void);
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);

// 設置(pos = 出現位置, scl = 大きさ, type = モデルの種類)
int SetBlock(XMFLOAT3 pos, XMFLOAT3 scl, int type);

XMFLOAT4X4 GetBlockWorld(int no);
XMFLOAT3 GetBlockCenter(int no);
XMFLOAT3 GetBlockBBox(int no);

XMFLOAT3 GetBlockPos(int no);
XMFLOAT3 GetBlockSize(int no);
bool IsBlock(int no);
void DestroyBlock(int no);