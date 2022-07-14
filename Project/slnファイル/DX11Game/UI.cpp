//======================================================================================
// UI処理
// 制作：向出創
//======================================================================================

// ヘッダファイルのインクルード
#include"UI.h"
#include "Debugproc.h"
#include"Texture.h"
#include"polygon.h"
#include "Input.h"
#include "Transition.h"
#include "Game.h"
#include "Sound.h"
#include "Score.h"
#include "Number.h"
#include "Player.h"

// マクロ定義
#define UI_POS_X	(0)
#define UI_POS_Y	(0)
#define UI_SIZE_X	(SCREEN_WIDTH)
#define UI_SIZE_Y	(SCREEN_HEIGHT)

#define MAX_UI (1)
#define MAX_UI_TEXTURE (MAX_UI_TYPE)

#define T_UI_TITLE_PRINT	_T("data/texture/UI/TitleScreenMoji.png")
#define T_UI_MAINSELECT		_T("data/texture/UI/MainSelect.png")
#define T_UI_STAGESELECT	_T("data/texture/UI/StageSelect.png")
#define T_UI_STAGESTREET	_T("data/texture/UI/StageStreet.png")
#define T_UI_OPTIONSELECT	_T("data/texture/UI/OptionSelect.png")
#define T_UI_MANUAL			_T("data/texture/UI/Manual.png")
#define T_UI_KETTEIMODORU1	_T("data/texture/UI/KetteiModoru.png")
#define T_UI_KETTEIMODORU2	_T("data/texture/UI/KetteiModoru1.png")
#define T_UI_NOWSELECT1		_T("data/texture/UI/NowSelect1.png")
#define T_UI_NOWSELECT2		_T("data/texture/UI/NowSelect2.png")
#define T_UI_LIFE1			_T("data/texture/UI/life1.png")
#define T_UI_LIFE2			_T("data/texture/UI/life01.png")
#define T_UI_UEUI			_T("data/texture/UI/UI.png")
#define T_UI_POSE			_T("data/texture/UI/Pause1.png")
#define T_UI_POSEBACK		_T("data/texture/UI/PauseBack.png")
#define TRANSITION1			_T("data/texture/UI/Tips1.png")
#define TRANSITION2			_T("data/texture/UI/Tips2.png")
#define TRANSITION3			_T("data/texture/UI/Tips3.png")
#define T_UI_STREETFIRE		_T("data/texture/UI/StreetFire.png")
#define T_UI_RESULT			_T("data/texture/UI/Result.png")
#define T_UI_DANGER			_T("data/texture/UI/!.png")
#define T_UI_1_4			_T("data/texture/UI/1_4.png")
#define T_UI_STAGEFOREST	_T("data/texture/UI/StageForest.png")
#define T_UI_2_4			_T("data/texture/UI/2_4.png")
#define T_UI_FORESTFIRE		_T("data/texture/UI/ForestFire.png")
#define T_UI_STAGENIGHT		_T("data/texture/UI/StageNight.png")
#define T_UI_3_4			_T("data/texture/UI/3_4.png")
#define T_UI_NIGHTFIRE		_T("data/texture/UI/NightFire.png")
#define T_UI_MANUAL2		_T("data/texture/UI/Manual2.png")

// 構造体定義
typedef struct _tUI
{
	XMFLOAT3	Position;	// 座標
	XMFLOAT2	Size;		// サイズ
	XMFLOAT2	Scale;		// 拡大縮小
	float		Angle;		// 回転角度
	float		Alpha;

}tUI;

// グローバル変数宣言
static ID3D11ShaderResourceView* g_pTexture[MAX_UI_TEXTURE];
static tUI	g_ui[MAX_UI];

static UIType DrawTexNo;	// 表示テクスチャ
static bool temp;
static int state;

static XMFLOAT2 g_TexCoord;		// テクスチャ座標(ポリゴンの左上)(TextureCoordinate)
static XMFLOAT2 g_TexFrameSize;	// テクスチャを貼り付けるサイズ

HRESULT LoadUI()
{
	HRESULT hr = S_OK;
	ID3D11Device*	pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, T_UI_TITLE_PRINT, &g_pTexture[UI_TITLE_PRINT]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_MAINSELECT, &g_pTexture[UI_MAINSELECT]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_STAGESELECT, &g_pTexture[UI_STAGESELECT]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_STAGESTREET, &g_pTexture[UI_STAGESTREET]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_OPTIONSELECT, &g_pTexture[UI_OPTIONSELECT]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_MANUAL, &g_pTexture[UI_MANUAL]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_KETTEIMODORU1, &g_pTexture[UI_KETTEIMODORU1]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_KETTEIMODORU2, &g_pTexture[UI_KETTEIMODORU2]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_NOWSELECT1, &g_pTexture[UI_NOWSELECT1]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_NOWSELECT2, &g_pTexture[UI_NOWSELECT2]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_LIFE1, &g_pTexture[UI_LIFE1]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_LIFE2, &g_pTexture[UI_LIFE2]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_UEUI, &g_pTexture[UI_UE_UI]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_POSE, &g_pTexture[UI_PAUSE]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_POSEBACK, &g_pTexture[UI_PAUSEBACK]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, TRANSITION1, &g_pTexture[UI_TIPAS1]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, TRANSITION2, &g_pTexture[UI_TIPAS2]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, TRANSITION3, &g_pTexture[UI_TIPAS3]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_STREETFIRE, &g_pTexture[UI_STREETFIRE]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_RESULT, &g_pTexture[UI_RESULT]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_DANGER, &g_pTexture[UI_DANGER]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_1_4, &g_pTexture[UI_1_4]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_STAGEFOREST, &g_pTexture[UI_STAGEFOREST]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_2_4, &g_pTexture[UI_2_4]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_FORESTFIRE, &g_pTexture[UI_FORESTFIRE]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_STAGENIGHT, &g_pTexture[UI_STAGENIGHT]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_3_4, &g_pTexture[UI_3_4]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_NIGHTFIRE, &g_pTexture[UI_NIGHTFIRE]);
	if (FAILED(hr)) return hr;
	hr = CreateTextureFromFile(pDevice, T_UI_MANUAL2, &g_pTexture[UI_MANUAL2]);
	if (FAILED(hr)) return hr;

	state = 0;

	return hr;
}

//======================================================================================
// 初期化
//======================================================================================
void InitUI()
{
	// パラメータの初期化
	for (int i = 0; i < MAX_UI; i++) {
		g_ui[i].Position = XMFLOAT3(UI_POS_X, UI_POS_Y, 0.0f);
		g_ui[i].Size = XMFLOAT2(UI_SIZE_X, UI_SIZE_Y);
		g_ui[i].Scale = XMFLOAT2(1.0f, 1.0f);
		g_ui[i].Angle = 0.0f;
		g_ui[i].Alpha = 1.0f;
	}
	DrawTexNo = UI_TITLE_PRINT;
	temp = false;
	g_TexCoord = XMFLOAT2(0.0f, 0.0f);
	g_TexFrameSize = XMFLOAT2(1.0f, 1.0f);
}

//======================================================================================
// 終了
//======================================================================================
void UninitUI()
{
	// テクスチャ後片付け
	//for (int i = 0; i < MAX_UI_TEXTURE; i++)
	//{
	//	SAFE_RELEASE(g_pTexture[i]);
	//}
}

//======================================================================================
// 更新
//======================================================================================
void UpdateUI()
{
	for (int i = 0; i < MAX_UI; i++) {

		if (GetSceneNo() == SCENE_TITLE) {

			// タイトル文字
			if (DrawTexNo == UI_TITLE_PRINT) {
				if (temp == false) {
					g_ui[i].Alpha -= 0.05f;
					if (g_ui[i].Alpha < 0.0f)	temp = true;
				}
				else if (temp == true) {
					g_ui[i].Alpha += 0.1f;
					if (g_ui[i].Alpha > 2.0f)	temp = false;
				}
			}
		}
		else if (GetSceneNo() == SCENE_SELECT) {
			// メインセレクト
			if (DrawTexNo == UI_MAINSELECT) {
				if (GetKeyTrigger(VK_W) && g_ui[i].Position.y > 0.0f ||
					GetKeyTrigger(VK_UP) && g_ui[i].Position.y > 0.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 0) && g_ui[i].Position.y > 0.0f) {
					g_ui[i].Position.x += 30.0f;
					g_ui[i].Position.y -= 135.0f;
				}
				else if (GetKeyTrigger(VK_S) && g_ui[i].Position.y < 270.0f ||
					GetKeyTrigger(VK_DOWN) && g_ui[i].Position.y < 270.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 18000) && g_ui[i].Position.y < 270.0f) {
					g_ui[i].Position.x -= 30.0f;
					g_ui[i].Position.y += 135.0f;
				}

				// ステージセレクトへ切り替え
				if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 0.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 0.0f) {
					DrawTexNo = UI_STAGESELECT;
					if (state == 0) {
						g_ui[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
					}
					else if (state == 1) {
						g_ui[i].Position = XMFLOAT3(-30.0f, 135.0f, 0.0f);
					}
					else if (state == 2) {
						g_ui[i].Position = XMFLOAT3(-60.0f, 270.0f, 0.0f);
					}
				}
				// オプションセレクトへ切り替え
				else if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 135.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 135.0f) {
					DrawTexNo = UI_OPTIONSELECT;
					g_ui[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				}
				// ゲーム終了
				else if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 270.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 270.0f) {
					ReleaseGame();
				}
				// タイトルへ戻る
				else if (GetKeyTrigger(VK_BACK) ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON1)) {
					StartChange(SCENE_TITLE, 0);
				}
			}
			// ステージセレクト
			else if (DrawTexNo == UI_STAGESELECT) {
				if (GetKeyTrigger(VK_W) && g_ui[i].Position.y > 0.0f ||
					GetKeyTrigger(VK_UP) && g_ui[i].Position.y > 0.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 0) && g_ui[i].Position.y > 0.0f) {
					g_ui[i].Position.x += 30.0f;
					g_ui[i].Position.y -= 135.0f;
					state--;
				}
				else if (GetKeyTrigger(VK_S) && g_ui[i].Position.y < 270.0f ||
					GetKeyTrigger(VK_DOWN) && g_ui[i].Position.y < 270.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 18000) && g_ui[i].Position.y < 270.0f) {
					g_ui[i].Position.x -= 30.0f;
					g_ui[i].Position.y += 135.0f;
					state++;
				}

				// ステージストリートへ切り替え
				if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 0.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 0.0f) {
					DrawTexNo = UI_STAGESTREET;
					// 選んでいたステージによってポジション変える
					g_ui[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				}
				// ステージフォレストへ切り替え（未実装）
				else if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 135.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 135.0f) {
					DrawTexNo = UI_STAGEFOREST;
					// 選んでいたステージによってポジション変える
					g_ui[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				}
				// ステージナイトストリートへ切り替え（未実装）
				else if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 270.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 270.0f) {
					DrawTexNo = UI_STAGENIGHT;
					// 選んでいたステージによってポジション変える
					g_ui[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				}
				// メインセレクトへ戻る
				else if (GetKeyTrigger(VK_BACK) ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON1)) {
					DrawTexNo = UI_MAINSELECT;
					g_ui[i].Position.x = 0.0f;
					g_ui[i].Position.y = 0.0f;
				}
			}
			// ステージストリートセレクト
			else if (DrawTexNo == UI_STAGESTREET) {
				if (GetKeyTrigger(VK_W) && g_ui[i].Position.y > 0.0f ||
					GetKeyTrigger(VK_UP) && g_ui[i].Position.y > 0.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 0) && g_ui[i].Position.y > 0.0f) {
					g_ui[i].Position.x += 30.0f;
					g_ui[i].Position.y -= 135.0f;
				}
				else if (GetKeyTrigger(VK_S) && g_ui[i].Position.y < 405.0f ||
					GetKeyTrigger(VK_DOWN) && g_ui[i].Position.y < 405.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 18000) && g_ui[i].Position.y < 405.0f) {
					g_ui[i].Position.x -= 30.0f;
					g_ui[i].Position.y += 135.0f;
					// 1-4の解放条件
					if (g_ui[i].Position.y == 405.0f && !GetSPStateS()) {
						g_ui[i].Position.x = -60.0f;
						g_ui[i].Position.y = 270.0f;
					}
				}
			}
			// ステージフォレストセレクト
			else if (DrawTexNo == UI_STAGEFOREST) {
				if (GetKeyTrigger(VK_W) && g_ui[i].Position.y > 0.0f ||
					GetKeyTrigger(VK_UP) && g_ui[i].Position.y > 0.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 0) && g_ui[i].Position.y > 0.0f) {
					g_ui[i].Position.x += 30.0f;
					g_ui[i].Position.y -= 135.0f;
				}
				else if (GetKeyTrigger(VK_S) && g_ui[i].Position.y < 405.0f ||
					GetKeyTrigger(VK_DOWN) && g_ui[i].Position.y < 405.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 18000) && g_ui[i].Position.y < 405.0f) {
					g_ui[i].Position.x -= 30.0f;
					g_ui[i].Position.y += 135.0f;
					// 2-4の解放条件
					if (g_ui[i].Position.y == 405.0f && !GetSPStateF()) {
						g_ui[i].Position.x = -60.0f;
						g_ui[i].Position.y = 270.0f;
					}
				}
			}
			// ステージナイト
			else if (DrawTexNo == UI_STAGENIGHT) {
				if (GetKeyTrigger(VK_W) && g_ui[i].Position.y > 0.0f ||
					GetKeyTrigger(VK_UP) && g_ui[i].Position.y > 0.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 0) && g_ui[i].Position.y > 0.0f) {
					g_ui[i].Position.x += 30.0f;
					g_ui[i].Position.y -= 135.0f;
				}
				else if (GetKeyTrigger(VK_S) && g_ui[i].Position.y < 405.0f ||
					GetKeyTrigger(VK_DOWN) && g_ui[i].Position.y < 405.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 18000) && g_ui[i].Position.y < 405.0f) {
					g_ui[i].Position.x -= 30.0f;
					g_ui[i].Position.y += 135.0f;
					// 3-4の解放条件
					if (g_ui[i].Position.y == 405.0f && !GetSPStateN()) {
						g_ui[i].Position.x = -60.0f;
						g_ui[i].Position.y = 270.0f;
					}
				}
			}
			// オプションセレクト
			else if (DrawTexNo == UI_OPTIONSELECT) {
				if (GetKeyTrigger(VK_W) && g_ui[i].Position.y > 0.0f ||
					GetKeyTrigger(VK_UP) && g_ui[i].Position.y > 0.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 0) && g_ui[i].Position.y > 0.0f) {
					g_ui[i].Position.x += 30.0f;
					g_ui[i].Position.y -= 135.0f;
				}
				else if (GetKeyTrigger(VK_S) && g_ui[i].Position.y < 135.0f ||
					GetKeyTrigger(VK_DOWN) && g_ui[i].Position.y < 135.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 18000) && g_ui[i].Position.y < 135.0f) {
					g_ui[i].Position.x -= 30.0f;
					g_ui[i].Position.y += 135.0f;
				}

				// 操作方法へ切り替え
				if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 0.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 0.0f) {
					DrawTexNo = UI_MANUAL;
					g_ui[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				}
				// クレジットへ切り替え（未実装）
				else if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 135.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 135.0f) {
					StartChange(SCENE_ENDING, 0);
					state = 0;
				}
				// メインセレクトへ戻る
				else if (GetKeyTrigger(VK_BACK) ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON1)) {
					DrawTexNo = UI_MAINSELECT;
					g_ui[i].Position.x = -30.0f;
					g_ui[i].Position.y = 135.0f;
				}
			}
			// 操作方法画面時
			else if (DrawTexNo == UI_MANUAL) {
				// オプションセレクトセレクトへ戻る
				if (GetKeyTrigger(VK_BACK) ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON3)) {
					DrawTexNo = UI_OPTIONSELECT;
					g_ui[i].Position.x = 0.0f;
					g_ui[i].Position.y = 0.0f;
				}
			}
		}
		else if (GetSceneNo() != SCENE_TITLE && GetSceneNo() != SCENE_SELECT) {
			// ポーズ画面時
			if (GetState() == 1) {

				if (GetKeyTrigger(VK_W) && g_ui[i].Position.y > 0.0f ||
					GetKeyTrigger(VK_UP) && g_ui[i].Position.y > 0.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 0) && g_ui[i].Position.y > 0.0f) {
					g_ui[i].Position.x += 30.0f;
					g_ui[i].Position.y -= 135.0f;
				}
				else if (GetKeyTrigger(VK_S) && g_ui[i].Position.y < 270.0f ||
					GetKeyTrigger(VK_DOWN) && g_ui[i].Position.y < 270.0f ||
					GetJoyCountSimple() == 1 && (GetJoyPOVTrigger(0) == 18000) && g_ui[i].Position.y < 270.0f) {
					g_ui[i].Position.x -= 30.0f;
					g_ui[i].Position.y += 135.0f;
				}

				// 続ける
				if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 0.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 0.0f) {
					SetState(0);
					PlaySound(SOUND_LABEL_SE_RUN);
				}
				// リトライ
				else if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 135.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 135.0f) {
					StartChange(GetSceneNo(), 0);
				}
				// あきらめる
				else if (GetKeyTrigger(VK_RETURN) && g_ui[i].Position.y == 270.0f ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2) && g_ui[i].Position.y == 270.0f) {
					StartChange(SCENE_SELECT, 1);
				}
			}
			// tips表示
			else if (GetState() == 2 || GetState() == 3 || GetState() == 4) {
				if (GetKeyTrigger(VK_RETURN) ||
					GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON2)) {
					SetState(0);
					PlaySound(SOUND_LABEL_SE_RUN);
				}
			}
		}
	}
}

//======================================================================================
// 描画
//======================================================================================
void DrawUI()
{
	for (int i = 0; i < MAX_UI; i++) {

		ID3D11DeviceContext*	pDeviceContext = GetDeviceContext();

		if (GetSceneNo() != SCENE_ENDING) {
			// 短い選択プレート	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL &&
				DrawTexNo != UI_STAGESTREET && DrawTexNo != UI_STAGEFOREST && DrawTexNo != UI_STAGENIGHT) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);
				// ポリゴンの情報設定
				SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_NOWSELECT1]);
				DrawPolygon(pDeviceContext);
			}
			// 長い選択プレート
			else if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGESTREET ||
				GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGEFOREST ||
				GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGENIGHT) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);
				// ポリゴンの情報設定
				SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_NOWSELECT2]);
				DrawPolygon(pDeviceContext);

				SetPolygonTexture(g_pTexture[UI_RESULT]);
				DrawPolygon(pDeviceContext);
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 操作方法	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (GetSceneNo() != SCENE_TITLE && GetSceneNo() != SCENE_SELECT && GetSceneNo() != SCENE_ENDING) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(g_ui[i].Alpha);
				SetPolygonColor(1.0f, 1.0f, 1.0f);
				// ポリゴンの情報設定
				SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_MANUAL2]);
				DrawPolygon(pDeviceContext);
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//  tips表示	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (GetState() == 2) {

				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);
				// ポリゴンの情報設定
				SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_TIPAS1]);
				DrawPolygon(pDeviceContext);
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 現在の表示No	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SetPolygonAngle(g_ui[i].Angle);
			SetPolygonAlpha(g_ui[i].Alpha);
			SetPolygonColor(1.0f, 1.0f, 1.0f);
			// ポリゴンの情報設定
			if (DrawTexNo != UI_UE_UI) {
				SetPolygonPos(g_ui[i].Position.x, g_ui[i].Position.y);		// 座標
			}
			else {
				SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
			}
			SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
			SetPolygonAngle(g_ui[i].Angle);				// 回転角度

			SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
			SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

			// ポリゴンの描画処理
			SetPolygonTexture(g_pTexture[DrawTexNo]);
			DrawPolygon(pDeviceContext);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 隠しステージ	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// ストリート
			if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGESTREET && GetSPStateS()) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);

				// ポリゴンの情報設定
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				SetPolygonPos(g_ui[i].Position.x + 90.0f, g_ui[i].Position.y - 405.0f);	// 座標
				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_1_4]);
				DrawPolygon(pDeviceContext);
			}
			// フォレスト
			if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGEFOREST && GetSPStateF()) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);

				// ポリゴンの情報設定
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				SetPolygonPos(g_ui[i].Position.x + 90.0f, g_ui[i].Position.y - 405.0f);	// 座標
				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_2_4]);
				DrawPolygon(pDeviceContext);
			}
			// ナイトストリート
			if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGENIGHT && GetSPStateN()) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);

				// ポリゴンの情報設定
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				SetPolygonPos(g_ui[i].Position.x + 90.0f, g_ui[i].Position.y - 405.0f);	// 座標
				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_3_4]);
				DrawPolygon(pDeviceContext);
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//  tips表示	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (GetState() == 3) {

				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);
				// ポリゴンの情報設定
				SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_TIPAS2]);
				DrawPolygon(pDeviceContext);
			}
			else if (GetState() == 4) {

				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);
				// ポリゴンの情報設定
				SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_TIPAS3]);
				DrawPolygon(pDeviceContext);
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 決定戻る	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (GetSceneNo() == SCENE_SELECT) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);
				// ポリゴンの情報設定
				SetPolygonPos(UI_POS_X + 200, UI_POS_Y - 100);		// 座標
				SetPolygonSize(UI_SIZE_X - 466, UI_SIZE_Y - 250);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				// ポリゴンの描画処理
				if (DrawTexNo != UI_MANUAL) {
					SetPolygonTexture(g_pTexture[UI_KETTEIMODORU1]);
				}
				else {
					SetPolygonTexture(g_pTexture[UI_KETTEIMODORU2]);
				}
				DrawPolygon(pDeviceContext);
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// ライフ/////////////////////////////////////////////////////////////////////////////////////////////////////////
			// ステージ選択以外
			if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL &&
				DrawTexNo != UI_STAGESTREET && DrawTexNo != UI_STAGEFOREST && DrawTexNo != UI_STAGENIGHT) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);
				// ポリゴンの情報設定
				SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_LIFE1]);
				DrawPolygon(pDeviceContext);
			}
			// ステージ選択
			else if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGESTREET ||
				GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGEFOREST ||
				GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGENIGHT) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);
				// ポリゴンの情報設定
				SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

				// ポリゴンの描画処理
				SetPolygonTexture(g_pTexture[UI_LIFE2]);
				DrawPolygon(pDeviceContext);
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// ファイアー	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// ストリート
			if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGESTREET) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);

				// ポリゴンの情報設定
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅
			}
			// フォレスト
			if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGEFOREST) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);

				// ポリゴンの情報設定
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅
			}
			// ナイト
			if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGENIGHT) {
				SetPolygonAngle(g_ui[i].Angle);
				SetPolygonAlpha(1.0f);
				SetPolygonColor(1.0f, 1.0f, 1.0f);

				// ポリゴンの情報設定
				SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
				SetPolygonAngle(g_ui[i].Angle);				// 回転角度

				SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
				SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				// 3-2 後ろから車
			if (GetSceneNo() == SCENE_STAGE3_2) {
				if (GetPlayerPos(0).z >= 1500.0f && GetPlayerPos(0).z <= 2500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X - 400, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
				if (GetPlayerPos(0).z >= 5500.0f && GetPlayerPos(0).z <= 6500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X + 400, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
				if (GetPlayerPos(0).z >= 9500.0f && GetPlayerPos(0).z <= 10500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X + 400, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
				if (GetPlayerPos(0).z >= 13500.0f && GetPlayerPos(0).z <= 14500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X - 400, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
				if (GetPlayerPos(0).z >= 17500.0f && GetPlayerPos(0).z <= 18500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
				if (GetPlayerPos(0).z >= 21500.0f && GetPlayerPos(0).z <= 22500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
				if (GetPlayerPos(0).z >= 25500.0f && GetPlayerPos(0).z <= 26500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X + 400, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
				if (GetPlayerPos(0).z >= 29500.0f && GetPlayerPos(0).z <= 30500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X - 400, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
				if (GetPlayerPos(0).z >= 33500.0f && GetPlayerPos(0).z <= 34500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
				if (GetPlayerPos(0).z >= 37500.0f && GetPlayerPos(0).z <= 38500.0f) {
					SetPolygonAngle(g_ui[i].Angle);
					SetPolygonAlpha(1.0f);
					SetPolygonColor(1.0f, 1.0f, 1.0f);
					// ポリゴンの情報設定
					SetPolygonPos(UI_POS_X + 400, UI_POS_Y - 200);		// 座標
					SetPolygonSize(300, 300);	// 大きさ
					SetPolygonAngle(g_ui[i].Angle);				// 回転角度

					SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
					SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

					// ポリゴンの描画処理
					SetPolygonTexture(g_pTexture[UI_DANGER]);
					DrawPolygon(pDeviceContext);
				}
			}
		}
		//  ポーズ時	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (GetState() == 1) {

			SetPolygonAngle(g_ui[i].Angle);
			SetPolygonAlpha(1.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);
			// ポリゴンの情報設定
			SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
			SetPolygonSize(UI_SIZE_X, UI_SIZE_Y);	// 大きさ
			SetPolygonAngle(g_ui[i].Angle);				// 回転角度

			SetPolygonUV(g_TexCoord.x, g_TexCoord.y);	// UV座標
			SetPolygonFrameSize(g_TexFrameSize.x, g_TexFrameSize.y);	// 横幅縦幅

			// ポリゴンの描画処理
			SetPolygonTexture(g_pTexture[UI_NOWSELECT1]);
			DrawPolygon(pDeviceContext);
			SetPolygonTexture(g_pTexture[UI_PAUSEBACK]);
			DrawPolygon(pDeviceContext);



			SetPolygonPos(g_ui[i].Position.x, g_ui[i].Position.y);		// 座標
			SetPolygonTexture(g_pTexture[UI_PAUSE]);
			DrawPolygon(pDeviceContext);



			SetPolygonPos(UI_POS_X, UI_POS_Y);		// 座標
			SetPolygonTexture(g_pTexture[UI_LIFE1]);
			DrawPolygon(pDeviceContext);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}

		// リザルト	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 1-1
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGESTREET && g_ui[i].Position.y == 0.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(0, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(0, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(0, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(0, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(0, 3), 3, 30, 45); // 撃破数
		}
		//1-2
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGESTREET && g_ui[i].Position.y == 135.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(1, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(1, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(1, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(1, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(1, 3), 3, 30, 45); // 撃破数
		}
		//1-3
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGESTREET && g_ui[i].Position.y == 270.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(2, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(2, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(2, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(2, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(2, 3), 3, 30, 45); // 撃破数
		}
		//1-4
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGESTREET && g_ui[i].Position.y == 405.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(3, 4) * (int)111.111f, 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 30 - (GetScore2(3, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(3, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(3, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(3, 3), 3, 30, 45); // 撃破数
		}
		// 2-1
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGEFOREST && g_ui[i].Position.y == 0.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(4, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(4, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(4, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(4, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(4, 3), 3, 30, 45); // 撃破数
		}
		//2-2
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGEFOREST && g_ui[i].Position.y == 135.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(5, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(5, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(5, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(5, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(5, 3), 3, 30, 45); // 撃破数
		}
		//2-3
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGEFOREST && g_ui[i].Position.y == 270.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(6, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(6, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(6, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(6, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(6, 3), 3, 30, 45); // 撃破数
		}
		//2-4
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGEFOREST && g_ui[i].Position.y == 405.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(7, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(7, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(7, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(7, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(7, 3), 3, 30, 45); // 撃破数
		}
		// 3-1
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGENIGHT && g_ui[i].Position.y == 0.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(8, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(8, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(8, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(8, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(8, 3), 3, 30, 45); // 撃破数
		}
		// 3-2
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGENIGHT && g_ui[i].Position.y == 135.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(9, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(9, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(9, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(9, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(9, 3), 3, 30, 45); // 撃破数
		}
		// 3-3
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGENIGHT && g_ui[i].Position.y == 270.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(10, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(10, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(10, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(10, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(10, 3), 3, 30, 45); // 撃破数
		}
		// 3-4
		if (GetSceneNo() == SCENE_SELECT && DrawTexNo != UI_MANUAL && DrawTexNo == UI_STAGENIGHT && g_ui[i].Position.y == 405.0f) {
			XMFLOAT2 pos1 = XMFLOAT2(210.0f, 230.0f);
			XMFLOAT2 pos2 = XMFLOAT2(330.0f, 145.0f);
			XMFLOAT2 pos3 = XMFLOAT2(330.0f, 60.0f);
			XMFLOAT2 pos4 = XMFLOAT2(330.0f, -35.0f);
			XMFLOAT2 pos5 = XMFLOAT2(330.0f, -130.0f);
			SetPolygonColor(1.0f, 1.0f, 1.0f);

			DrawNumber(&pos1, GetScore2(11, 4), 7, 30, 45);	// ハイスコア
			DrawNumber(&pos2, 120 - (GetScore2(11, 0) / 60), 3, 30, 45);	// 時間
			DrawNumber(&pos3, GetScore2(11, 1), 3, 30, 45); // コンボ
			DrawNumber(&pos4, GetScore2(11, 2), 3, 30, 45);	// アイテム
			DrawNumber(&pos5, GetScore2(11, 3), 3, 30, 45); // 撃破数
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

UIType GetDrawTexNo()
{
	return DrawTexNo;
}

void SetDrawTexNo(UIType type)
{
	DrawTexNo = type;
}

XMFLOAT3 GetUIPos(int no)
{
	return g_ui[no].Position;
}

int GetUIState()
{
	return state;
}