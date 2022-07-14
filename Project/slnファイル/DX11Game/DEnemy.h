//======================================================================================
// 地上敵処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

#include "Main.h"

// マクロ定義
#define MAX_DENEMY  (200)     //弾の数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT LoadDEnemy(void);
void InitDEnemy(void);
void UninitDEnemy(void);
void UpdateDEnemy(void);
void DrawDEnemy(void);

// 設置(pos = 出現位置, dir = 進む方向の速度, type = 挙動の種類)
int SetDEnemy(XMFLOAT3 pos, XMFLOAT3 dir, int type);

XMFLOAT3 GetDEnemyPos(int no);
XMFLOAT3 GetDEnemySize(int no);
bool	 IsDEnemy(int no);
void	 DestroyDEnemy(int no);

void	KillDEnemy(int no);

int		GetDEnemy(int no);