//======================================================================================
// スコア処理
// 制作：向出創
//======================================================================================

// ヘッダファイルのインクルード
#include"score.h"
#include"texture.h"
#include"polygon.h"
#include"number.h"
#include "Life.h"

// 構造体宣言
typedef struct _tScore
{
	int score2[12][5];	// [ステージ数][各項目]
	bool SPStateS;		// 隠しストリート
	bool SPStateF;		// 隠しストリート
	bool SPStateN;		// 隠しストリート
}tScore;

// グローバル変数宣言

static int g_score1[12][5];
tScore	g_score;
static int  X1;
static int	g_width1;
static int	g_width2;
static int	g_width3;
static int	BeforeScore1;
static int	BeforeScore2;
static int	BeforeScore3;
static int	BeforeScore4;
static int	BeforeScore5;

static float	PosY1;
static float	PosY2;

static int	comboCount;

//======================================================================================
// 初期化
//======================================================================================
void InitScore(void)
{
	// 初期化
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 5; j++) {

			g_score1[i][j] = 0;
		}
	}

	// 保持用スコア初期化
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 5; j++) {

			g_score.score2[i][j] = 0;
		}
	}

	// タイム
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		g_score1[0][0] = 7200;
		break;
	case SCENE_STAGE1_2:
		g_score1[1][0] = 7200;
		break;
	case SCENE_STAGE1_3:
		g_score1[2][0] = 7200;
		break;
	case SCENE_STAGE1_4:
		g_score1[3][0] = 1800;
		break;
	case SCENE_STAGE2_1:
		g_score1[4][0] = 7200;
		break;
	case SCENE_STAGE2_2:
		g_score1[5][0] = 7200;
		break;
	case SCENE_STAGE2_3:
		g_score1[6][0] = 7200;
		break;
	case SCENE_STAGE2_4:
		g_score1[7][0] = 7200;
		break;
	case SCENE_STAGE3_1:
		g_score1[8][0] = 7200;
		break;
	case SCENE_STAGE3_2:
		g_score1[9][0] = 7200;
		break;
	case SCENE_STAGE3_3:
		g_score1[10][0] = 7200;
		break;
	case SCENE_STAGE3_4:
		g_score1[11][0] = 7200;
		break;
	}

	X1 = 0;	// タイマ桁数
	g_width1 = 3;
	g_width2 = 1;
	g_width3 = 1;

	PosY1 = SCREEN_HEIGHT / 2 - 90;
	PosY2 = -SCREEN_HEIGHT / 2 + 120;

	comboCount = 0;

	g_score.SPStateS = false;
	g_score.SPStateF = false;
	g_score.SPStateN = false;
	
	// ファイルから読み込み
	FILE* fp;
	if ((fp = fopen("D_StageData.dat", "r")) != NULL)
	{
		// オープン成功
		fread(&g_score, sizeof(tScore), 1, fp);

		fclose(fp);
	}
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
	// タイマ
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		g_score1[0][0]--;
		if (g_score1[0][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[0][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE1_2:
		g_score1[1][0]--;
		if (g_score1[1][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[1][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE1_3:
		g_score1[2][0]--;
		if (g_score1[2][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[2][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE1_4:
		g_score1[3][0]--;
		if (g_score1[3][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[3][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE2_1:
		g_score1[4][0]--;
		if (g_score1[4][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[4][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE2_2:
		g_score1[5][0]--;
		if (g_score1[5][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[5][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE2_3:
		g_score1[6][0]--;
		if (g_score1[6][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[6][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE2_4:
		g_score1[7][0]--;
		if (g_score1[7][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[7][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE3_1:
		g_score1[8][0]--;
		if (g_score1[8][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[8][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE3_2:
		g_score1[9][0]--;
		if (g_score1[9][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[9][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE3_3:
		g_score1[10][0]--;
		if (g_score1[10][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[10][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	case SCENE_STAGE3_4:
		g_score1[11][0]--;
		if (g_score1[11][0] <= 6000) {
			g_width1 = 2;
			X1 = 10;
		}
		if (g_score1[11][0] <= 600) {
			g_width1 = 1;
			X1 = 0;
		}
		break;
	}

	// アイテム
	for (int i = 0; i < 12; i++) {
		if (g_score1[i][1] >= 10) {
			g_width2 = 2;
		}
		if (g_score1[i][1] >= 100) {
			g_width2 = 3;
		}
	}

	// コンボ
	for (int i = 0; i < 12; i++) {
		if (g_score1[i][2] >= 10) {
			g_width3 = 2;
		}
		if (g_score1[i][2] >= 100) {
			g_width3 = 3;
		}
	}

	if (PosY1 > SCREEN_HEIGHT / 2 - 90) {
		PosY1 -= 2.0f;
	}
	if (PosY2 > -SCREEN_HEIGHT / 2 + 120) {
		PosY2 -= 4.0f;
	}

	// 隠し
	if (g_score.score2[0][1] >= 90 && g_score.score2[1][1] >= 90 && g_score.score2[2][1] >= 90)		g_score.SPStateS = true;
	if (g_score.score2[4][1] >= 90 && g_score.score2[5][1] >= 90 && g_score.score2[6][1] >= 90)		g_score.SPStateF = true;
	if (g_score.score2[8][1] >= 90 && g_score.score2[9][1] >= 90 && g_score.score2[10][1] >= 90)	g_score.SPStateN = true;

}

//======================================================================================
// 描画
//======================================================================================
void DrawScore()
{
	// タイマ
	XMFLOAT2 pos1 = XMFLOAT2((float)(0 - 30 + X1), (float)(SCREEN_HEIGHT / 2 - 45));
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		DrawNumber(&pos1, g_score1[0][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE1_2:
		DrawNumber(&pos1, g_score1[1][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE1_3:
		DrawNumber(&pos1, g_score1[2][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE1_4:
		DrawNumber(&pos1, g_score1[3][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE2_1:
		DrawNumber(&pos1, g_score1[4][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE2_2:
		DrawNumber(&pos1, g_score1[5][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE2_3:
		DrawNumber(&pos1, g_score1[6][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE2_4:
		DrawNumber(&pos1, g_score1[7][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE3_1:
		DrawNumber(&pos1, g_score1[8][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE3_2:
		DrawNumber(&pos1, g_score1[9][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE3_3:
		DrawNumber(&pos1, g_score1[10][0] / 60, g_width1, 22, 32);
		break;
	case SCENE_STAGE3_4:
		DrawNumber(&pos1, g_score1[11][0] / 60, g_width1, 22, 32);
		break;
	}

	// アイテム
	XMFLOAT2 pos2 = XMFLOAT2((float)(-SCREEN_WIDTH / 2 + 120 - g_width2 * 10), PosY1);
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		DrawNumber(&pos2, g_score1[0][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE1_2:
		DrawNumber(&pos2, g_score1[1][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE1_3:
		DrawNumber(&pos2, g_score1[2][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE1_4:
		DrawNumber(&pos2, g_score1[3][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE2_1:
		DrawNumber(&pos2, g_score1[4][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE2_2:
		DrawNumber(&pos2, g_score1[5][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE2_3:
		DrawNumber(&pos2, g_score1[6][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE2_4:
		DrawNumber(&pos2, g_score1[7][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE3_1:
		DrawNumber(&pos2, g_score1[8][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE3_2:
		DrawNumber(&pos2, g_score1[9][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE3_3:
		DrawNumber(&pos2, g_score1[10][1], g_width2, 15, 21);
		break;
	case SCENE_STAGE3_4:
		DrawNumber(&pos2, g_score1[11][1], g_width2, 15, 21);
		break;
	}
	XMFLOAT2 pos3 = XMFLOAT2((float)(-SCREEN_WIDTH / 2 + 170), (float)(SCREEN_HEIGHT / 2 - 90));
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	DrawNumber(&pos3, 100, 3, 15, 21);

	// コンボ
	XMFLOAT2 pos4 = XMFLOAT2((float)(-SCREEN_WIDTH / 2 + 120 - g_width3 * 10), PosY2);
	if (GetScore(2) == 0 && GetScore(2) < 20) {
		SetPolygonColor(1.0f, 1.0f, 1.0f);
	}
	else if (GetScore(2) >= 20 && GetScore(2) < 50) {
		SetPolygonColor(0.0f, 0.6f, 1.0f);
	}
	else if (GetScore(2) >= 50 && GetScore(2) < 80) {
		SetPolygonColor(0.0f, 1.0f, 0.0f);
	}
	else if (GetScore(2) >= 80 && GetScore(2) < 100) {
		SetPolygonColor(1.0f, 1.0f, 0.0f);
	}
	else if (GetScore(2) >= 100) {
		SetPolygonColor(1.0f, 0.0f, 0.0f);
	}
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		DrawNumber(&pos4, g_score1[0][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE1_2:
		DrawNumber(&pos4, g_score1[1][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE1_3:
		DrawNumber(&pos4, g_score1[2][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE1_4:
		DrawNumber(&pos4, g_score1[3][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE2_1:
		DrawNumber(&pos4, g_score1[4][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE2_2:
		DrawNumber(&pos4, g_score1[5][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE2_3:
		DrawNumber(&pos4, g_score1[6][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE2_4:
		DrawNumber(&pos4, g_score1[7][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE3_1:
		DrawNumber(&pos4, g_score1[8][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE3_2:
		DrawNumber(&pos4, g_score1[9][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE3_3:
		DrawNumber(&pos4, g_score1[10][2], g_width3, 40, 57);
		break;
	case SCENE_STAGE3_4:
		DrawNumber(&pos4, g_score1[11][2], g_width3, 40, 57);
		break;
	}
}

//======================================================================================
// スコアの加算
//======================================================================================

void AddCountItem(int num)
{
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		g_score1[0][1] += num;
		break;
	case SCENE_STAGE1_2:
		g_score1[1][1] += num;
		break;
	case SCENE_STAGE1_3:
		g_score1[2][1] += num;
		break;
	case SCENE_STAGE1_4:
		g_score1[3][1] += num;
		break;
	case SCENE_STAGE2_1:
		g_score1[4][1] += num;
		break;
	case SCENE_STAGE2_2:
		g_score1[5][1] += num;
		break;
	case SCENE_STAGE2_3:
		g_score1[6][1] += num;
		break;
	case SCENE_STAGE2_4:
		g_score1[7][1] += num;
		break;
	case SCENE_STAGE3_1:
		g_score1[8][1] += num;
		break;
	case SCENE_STAGE3_2:
		g_score1[9][1] += num;
		break;
	case SCENE_STAGE3_3:
		g_score1[10][1] += num;
		break;
	case SCENE_STAGE3_4:
		g_score1[11][1] += num;
		break;
	}
	for (int i = 0; i < 12; i++) {
		if (g_score1[i][1] < 0)
		{
			g_score1[i][1] = 0;
		}
	}
	PosY1 = SCREEN_HEIGHT / 2 - 90;
	PosY1 += 20.0f;
}

void AddCountCombo(int num)
{
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		g_score1[0][2] += num;
		break;
	case SCENE_STAGE1_2:
		g_score1[1][2] += num;
		break;
	case SCENE_STAGE1_3:
		g_score1[2][2] += num;
		break;
	case SCENE_STAGE1_4:
		g_score1[3][2] += num;
		break;
	case SCENE_STAGE2_1:
		g_score1[4][2] += num;
		break;
	case SCENE_STAGE2_2:
		g_score1[5][2] += num;
		break;
	case SCENE_STAGE2_3:
		g_score1[6][2] += num;
		break;
	case SCENE_STAGE2_4:
		g_score1[7][2] += num;
		break;
	case SCENE_STAGE3_1:
		g_score1[8][2] += num;
		break;
	case SCENE_STAGE3_2:
		g_score1[9][2] += num;
		break;
	case SCENE_STAGE3_3:
		g_score1[10][2] += num;
		break;
	case SCENE_STAGE3_4:
		g_score1[11][2] += num;
		break;
	}
	for (int i = 0; i < 12; i++) {
		if (g_score1[i][2] < 0)
		{
			g_score1[i][2] = 0;
			g_width3 = 1;
		}
	}
	PosY2 = -SCREEN_HEIGHT / 2 + 120;
	PosY2 += 40.0f;

	comboCount++;
}

void AddCountKill(int num)
{
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		g_score1[0][3] += num;
		break;
	case SCENE_STAGE1_2:
		g_score1[1][3] += num;
		break;
	case SCENE_STAGE1_3:
		g_score1[2][3] += num;
		break;
	case SCENE_STAGE1_4:
		g_score1[3][3] += num;
		break;
	case SCENE_STAGE2_1:
		g_score1[4][3] += num;
		break;
	case SCENE_STAGE2_2:
		g_score1[5][3] += num;
		break;
	case SCENE_STAGE2_3:
		g_score1[6][3] += num;
		break;
	case SCENE_STAGE2_4:
		g_score1[7][3] += num;
		break;
	case SCENE_STAGE3_1:
		g_score1[8][3] += num;
		break;
	case SCENE_STAGE3_2:
		g_score1[9][3] += num;
		break;
	case SCENE_STAGE3_3:
		g_score1[10][3] += num;
		break;
	case SCENE_STAGE3_4:
		g_score1[11][3] += num;
		break;
	}
}

int GetScore(int no)
{
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		return g_score1[0][no];
	case SCENE_STAGE1_2:
		return g_score1[1][no];
	case SCENE_STAGE1_3:
		return g_score1[2][no];
	case SCENE_STAGE1_4:
		return g_score1[3][no];
	case SCENE_STAGE2_1:
		return g_score1[4][no];
	case SCENE_STAGE2_2:
		return g_score1[5][no];
	case SCENE_STAGE2_3:
		return g_score1[6][no];
	case SCENE_STAGE2_4:
		return g_score1[7][no];
	case SCENE_STAGE3_1:
		return g_score1[8][no];
	case SCENE_STAGE3_2:
		return g_score1[9][no];
	case SCENE_STAGE3_3:
		return g_score1[10][no];
	case SCENE_STAGE3_4:
		return g_score1[11][no];
	}
	return -1;
}

int	GetScore2(int no1, int no2)
{
	return g_score.score2[no1][no2];
}

void SetBeforeScore()
{
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:
		BeforeScore1 = g_score1[0][0];
		BeforeScore2 = g_score1[0][1];
		BeforeScore3 = g_score1[0][2];
		break;
	case SCENE_STAGE1_2:
		BeforeScore1 = g_score1[1][0];
		BeforeScore2 = g_score1[1][1];
		BeforeScore3 = g_score1[1][2];
		break;
	case SCENE_STAGE1_3:
		BeforeScore1 = g_score1[2][0];
		BeforeScore2 = g_score1[2][1];
		BeforeScore3 = g_score1[2][2];
		break;
	case SCENE_STAGE1_4:
		BeforeScore1 = g_score1[3][0];
		BeforeScore2 = g_score1[3][1];
		BeforeScore3 = g_score1[3][2];
		break;
	case SCENE_STAGE2_1:
		BeforeScore1 = g_score1[4][0];
		BeforeScore2 = g_score1[4][1];
		BeforeScore3 = g_score1[4][2];
		break;
	case SCENE_STAGE2_2:
		BeforeScore1 = g_score1[5][0];
		BeforeScore2 = g_score1[5][1];
		BeforeScore3 = g_score1[5][2];
		break;
	case SCENE_STAGE2_3:
		BeforeScore1 = g_score1[6][0];
		BeforeScore2 = g_score1[6][1];
		BeforeScore3 = g_score1[6][2];
		break;
	case SCENE_STAGE2_4:
		BeforeScore1 = g_score1[7][0];
		BeforeScore2 = g_score1[7][1];
		BeforeScore3 = g_score1[7][2];
		break;
	case SCENE_STAGE3_1:
		BeforeScore1 = g_score1[8][0];
		BeforeScore2 = g_score1[8][1];
		BeforeScore3 = g_score1[8][2];
		break;
	case SCENE_STAGE3_2:
		BeforeScore1 = g_score1[9][0];
		BeforeScore2 = g_score1[9][1];
		BeforeScore3 = g_score1[9][2];
		break;
	case SCENE_STAGE3_3:
		BeforeScore1 = g_score1[10][0];
		BeforeScore2 = g_score1[10][1];
		BeforeScore3 = g_score1[10][2];
		break;
	case SCENE_STAGE3_4:
		BeforeScore1 = g_score1[11][0];
		BeforeScore2 = g_score1[11][1];
		BeforeScore3 = g_score1[11][2];
		break;
	}
}

int GetComboCount()
{
	return comboCount;
}

void SetComboCount()
{
	comboCount = 0;
}

bool GetSPStateS()
{
	return g_score.SPStateS;
}

bool GetSPStateF()
{
	return g_score.SPStateF;
}

bool GetSPStateN()
{
	return g_score.SPStateN;
}

