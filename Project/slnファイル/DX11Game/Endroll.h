//======================================================================================
// エンドロール処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

#include "Main.h"

#define MAX_TEXT		(1)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT LoadText(void);
void InitText(void);
void UninitText(void);
void UpdateText(void);
void DrawTex(void);

// 設置(pos = 出現位置, scl = 大きさ, type = モデルの種類)
int SetText(XMFLOAT3 pos, XMFLOAT3 scl, XMFLOAT3 dir, int type);

XMFLOAT4X4 GetTextWorld(int no);
XMFLOAT3 GetTextCenter(int no);
XMFLOAT3 GetTextBBox(int no);

XMFLOAT3 GetTextPos(int no);
XMFLOAT3 GetTextSize(int no);
bool IsText(int no);
void DestroyText(int no);

void PadlleBall(int no);
void SetAngleX(float _angleX);
void SetAngleY(float _angleY);
float	GetBallAngleX(int no);
float	GetBallAngleY(int no);

// ボールがブロックと当たった時の挙動決定(簡易判定版)
void CheckBallHitDirection(XMFLOAT3* BCenter, XMFLOAT3* BSize);