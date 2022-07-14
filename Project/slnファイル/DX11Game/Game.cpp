//=============================================================================
// メインゲーム処理
// 制作：向出創
//=============================================================================
#include <time.h>
#include "Main.h"
#include "Game.h"
#include "Input.h"
#include "Bg.h"
#include "Street.h"
#include "Field.h"
#include "Player.h"
#include "Object.h"
#include "DEnemy.h"
#include "EF_Acceleration.h"
#include "Transition.h"
#include "Shadow.h"
#include "Life.h"
#include "UI.h"
#include "Score.h"
#include "Item.h"
#include "Stage.h"
#include "EF_Maneger.h"
#include "Sound.h"
#include "Combo.h"
#include "Gauge.h"
#include "Endroll.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	state;	// tips情報
static bool	stateFlag;

//=============================================================================
// 初期化処理
//=============================================================================
void InitGame()
{
	// 加速エフェクト
	InitAcceleration();
	// Effekseerエフェクト初期化
	InitEFManeger();
	// 背景
	InitBg();
	// ライフ
	InitLife();
	// 道路
	InitStreet();
	// フィールド
	InitField();
	// プレイヤー
	InitPlayer();
	// 地上敵
	InitDEnemy();
	// 空中敵
	// オブジェクト
	InitObject();
	// エンドロール
	InitText();
	// スコア
	InitScore();
	// アイテム
	InitItem();
	// UI
	InitUI();
	// コンボ
	InitCombo();
	AddCountCombo(-999);

	state = 0;
	stateFlag = false;

	SetDrawTexNo(UI_UE_UI);

	SetStage();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame()
{
	// 加速エフェクト
	UninitAcceleration();
	// 背景
	UninitBg();
	// ライフ
	UninitLife();
	// 道路
	UninitStreet();
	// フィールド
	UninitField();
	// プレイヤー
	UninitPlayer();
	// オブジェクト
	UninitObject();
	// エンドロール
	UninitText();
	// スコア
	UninitScore();
	// アイテム
	UninitItem();
	// UI
	UninitUI();
	// コンボ
	UninitCombo();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame()
{
	if (state == 0) {
		// 加速エフェクト
		UpdateAcceleration();
		// Effekseerエフェクト
		UpdateEFManeger();
		// 背景
		UpdateBg();
		// ライフ
		UpdateLife();
		// 道路
		UpdateStreet();
		// フィールド
		UpdateField();
		// プレイヤー
		UpdatePlayer();
		// エネミー
		UpdateDEnemy();
		// オブジェクト
		UpdateObject();
		// エンドロール
		UpdateText();
		// スコア
		UpdateScore();
		// アイテム
		UpdateItem();
		// コンボ
		UpdateCombo();
	}
	// UI
	UpdateUI();


	// ポーズ切り替え
	if (GetKeyTrigger(VK_ESCAPE) || GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON8)){
		if (state == 0) state = 1;
		StopSound(SOUND_LABEL_SE_RUN);
	}

	// tips表示
	if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 800.0f && GetPlayerPos(0).z <= 850.0f && stateFlag == false) {
		if (state == 0) state = 2;
		stateFlag = true;
		StopSound(SOUND_LABEL_SE_RUN);
	}
	else if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 9000.0f && GetPlayerPos(0).z <= 9550.0f && stateFlag == false) {
		if (state == 0) state = 3;
		stateFlag = true;
		StopSound(SOUND_LABEL_SE_RUN);
	}
	else if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 18000.0f && GetPlayerPos(0).z <= 18050.0f && stateFlag == false) {
		if (state == 0) state = 4;
		stateFlag = true;
		StopSound(SOUND_LABEL_SE_RUN);
	}

	// tipsフラグ回収
	if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 860.0f && GetPlayerPos(0).z <= 900.0f) {
		stateFlag = false;
	}
	else if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 9560.0f && GetPlayerPos(0).z <= 9600.0f) {
		stateFlag = false;
	}
	else if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 18600.0f && GetPlayerPos(0).z <= 18700.0f) {
		stateFlag = false;
	}


	if (GetSceneNo() == SCENE_ENDING && GetPlayerPos(0).z >= 19000.0f) {
		StartChange(SCENE_SELECT, 2);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame()
{
	// Zバッファ無効
	SetZBuffer(false);
	// 背景
	DrawBg();
	// Zバッファ有効
	SetZBuffer(true);
	// フィールド
	DrawField();
	// 道路
	DrawStreet();
	// プレイヤー
	DrawPlayer();
	// エネミー
	DrawDEnemy();
	// オブジェクト
	DrawObject();
	// エンドロール
	DrawTex();
	// アイテム
	DrawItem();
	// Effekseerエフェクト
	DrawEFManeger();

	SetZWrite(false);	// 影設定変更影を綺麗に
	DrawShadow();
	SetZWrite(true);
	// Zバッファ有効
	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);
	if (GetSceneNo() != SCENE_ENDING) {
		// 加速エフェクト
		DrawAcceleration();
		if (state == 1 || state != 2) {	// ポーズ時
			DrawCombo();
			DrawLife();
		}
		if (GetPlayerDashCount() <= 1.0f)	DrawGaugeX(XMFLOAT2(-75.0f, -200.0f), XMFLOAT2(150.0f, 15.0f), GetPlayerDashCount(), 0);
		if (GetPlayerJumpCount() <= 1.0f)	DrawGaugeY1(XMFLOAT2(-150.0f, -130.0f), XMFLOAT2(15.0f, 150.0f), GetPlayerJumpCount(), 1);
		if (GetPlayerSlide() <= 1.0f)	DrawGaugeY2(XMFLOAT2(150.0f, -130.0f), XMFLOAT2(15.0f, 150.0f), GetPlayerSlide(), 2);
	}
	DrawUI();
	if (GetSceneNo() != SCENE_ENDING) {
		if (state == 2) {	// tips時
			DrawCombo();
			DrawLife();
		}
		DrawScore();
	}
	DrawTransition();
	SetBlendState(BS_NONE);
	// Zバッファ有効
	SetZBuffer(true);
}

int GetState()
{
	return state;
}

void SetState(int no)
{
	state = no;
}