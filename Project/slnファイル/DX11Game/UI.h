//======================================================================================
// UI処理まとめ
// 制作：向出創
//======================================================================================
#pragma once

//ヘッダファイルのインクルード
#include"main.h"

enum UIType {
	UI_TITLE_PRINT,
	UI_MAINSELECT,
	UI_STAGESELECT,
	UI_STAGESTREET,
	UI_OPTIONSELECT,
	UI_MANUAL,
	UI_KETTEIMODORU1,
	UI_KETTEIMODORU2,
	UI_NOWSELECT1,
	UI_NOWSELECT2,
	UI_LIFE1,
	UI_LIFE2,
	UI_UE_UI,
	UI_PAUSE,
	UI_PAUSEBACK,
	UI_TIPAS1,
	UI_TIPAS2,
	UI_TIPAS3,
	UI_STREETFIRE,
	UI_RESULT,
	UI_DANGER,
	UI_1_4,
	UI_STAGEFOREST,
	UI_2_4,
	UI_FORESTFIRE,
	UI_STAGENIGHT,
	UI_3_4,
	UI_NIGHTFIRE,
	UI_MANUAL2,

	MAX_UI_TYPE
};

//プロトタイプ宣言
HRESULT LoadUI();	//初期化
void	InitUI();	//初期化
void	UninitUI();	//終了
void	UpdateUI();	//更新
void	DrawUI();	//描画

UIType	GetDrawTexNo();
void	SetDrawTexNo(UIType type);

XMFLOAT3 GetUIPos(int no);
int		GetUIState();