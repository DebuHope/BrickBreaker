//======================================================================================
// スコア処理
// 制作：向出創
//======================================================================================

// ヘッダファイルのインクルード
#include"score.h"
#include"texture.h"
#include"polygon.h"
#include"number.h"


//定数宣言
#define SCORE_POS_X (750)
#define SCORE_POS_Y (-200)

#define SCORENUM_POS_X (SCORE_POS_X - 50)
#define SCORENUM_POS_Y (SCORE_POS_Y - 8)

#define TIMER_POS_X (750)
#define TIMER_POS_Y (0)

#define TIMERNUM_POS_X (TIMER_POS_X - 50)
#define TIMERNUM_POS_Y (TIMER_POS_Y - 8)

#define STAGE_POS_X (750)
#define STAGE_POS_Y (200)

#define STAGENUM_POS_X (STAGE_POS_X-5)
#define STAGENUM_POS_Y (STAGE_POS_Y - 8)

#define LIFE_POS_X (-900)
#define LIFE_POS_Y (-200)

// 構造体宣言
struct Score
{
	int timer, score,life,stage;

};

// グローバル変数宣言
Score score;
XMFLOAT2 PosNumbar;
XMFLOAT2 PosPolygon;


//======================================================================================
// 初期化
//======================================================================================
void InitScore(int _stage)
{
	score.stage = _stage;
	score.score = 0;
	score.timer = 0;
	score.life = 2;

	PosNumbar.x = SCORENUM_POS_X;
	PosNumbar.y = SCORENUM_POS_Y;
}

//======================================================================================
// 終了
//======================================================================================
void UninitScore(void)
{

}

//======================================================================================
// 更新
//======================================================================================
void UpdateScore()
{
	//score.life = 2;
	
}

//======================================================================================
// 描画
//======================================================================================
void DrawScore()
{
	//SetPolygonPos(STAGE_POS_X, STAGE_POS_Y);
	//SetPolygonSize(150, 70);
	SetPolygonColor(0, 0, 0);
	//SetPolygonTexture(nullptr);
	//DrawPolygon(GetDeviceContext());

	SetPolygonPos(STAGE_POS_X, STAGE_POS_Y+15);
	//SetPolygonColor(255, 255, 255);
	SetPolygonSize(50, 30);
	SetPolygonTexture(nullptr);
	DrawPolygon(GetDeviceContext());

	PosNumbar.x = STAGENUM_POS_X;
	PosNumbar.y = STAGENUM_POS_Y;
	DrawNumber(&PosNumbar, score.stage, 1, 20, 20);

	//SetPolygonPos(SCORE_POS_X, SCORE_POS_Y);
	//SetPolygonSize(150, 70);
	//SetPolygonColor(0, 0, 0);
	//SetPolygonTexture(nullptr);
	//DrawPolygon(GetDeviceContext());
	
	SetPolygonPos(SCORE_POS_X, SCORE_POS_Y + 15);
	//SetPolygonColor(255, 255, 255);
	SetPolygonSize(50, 30); 
	SetPolygonTexture(nullptr);
	DrawPolygon(GetDeviceContext());

	PosNumbar.x = SCORENUM_POS_X;
	PosNumbar.y = SCORENUM_POS_Y;
	DrawNumber(&PosNumbar, score.score, 5, 20, 20);

	//SetPolygonPos(TIMER_POS_X, TIMER_POS_Y);
	//SetPolygonSize(150, 70);
	//SetPolygonColor(0, 0, 0);
	//SetPolygonTexture(nullptr);
	//DrawPolygon(GetDeviceContext());

	SetPolygonPos(TIMER_POS_X, TIMER_POS_Y + 15);
	//SetPolygonColor(255, 255, 255);
	SetPolygonSize(50, 30);
	SetPolygonTexture(nullptr);
	DrawPolygon(GetDeviceContext());

	PosNumbar.x = TIMERNUM_POS_X;
	PosNumbar.y = TIMERNUM_POS_Y;
	DrawNumber(&PosNumbar, score.score, 5, 20, 20);

	//SetPolygonPos(TIMER_POS_X, TIMER_POS_Y);
	//SetPolygonSize(150, 70);
	//SetPolygonColor(0, 0, 0);
	//SetPolygonTexture(nullptr);
	//DrawPolygon(GetDeviceContext());

	SetPolygonPos(LIFE_POS_X, LIFE_POS_Y + 15);
	//SetPolygonColor(255, 255, 255);
	SetPolygonSize(50, 30);
	SetPolygonTexture(nullptr);
	DrawPolygon(GetDeviceContext());

	for (int i = 0; i < score.life; i++)
	{
		SetPolygonPos(LIFE_POS_X + i * 55, LIFE_POS_Y-30);
		SetPolygonSize(40, 40);
		SetPolygonTexture(nullptr);
		DrawPolygon(GetDeviceContext());
	}

}


// addScore関数
// スコア加算
void addScore(int _score)
{
	score.score += _score;

}
