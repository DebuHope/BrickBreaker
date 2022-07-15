#include "Load.h"
#include "Bg.h"
#include "DEnemy.h"
#include "EF_Acceleration.h"
#include "Field.h"
#include "Object.h"
#include "Player.h"
#include "Shadow.h"
#include "Street.h"
#include "UI.h"
#include "Transition.h"
#include "Life.h"
#include "Item.h"
#include "Combo.h"
#include "Gauge.h"
#include "Endroll.h"
#include "Block.h"

HRESULT LoadModelTex()
{
	HRESULT hr = S_OK;
	HWND hWnd = GetMainWnd();

	hr = LoadUI();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("UI初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadPlayer();
	if (FAILED(hr)){
	MessageBox(hWnd, _T("プレイヤー初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
	return hr;
	}

	hr = LoadObject();
	if (FAILED(hr)){
		MessageBox(hWnd, _T("オブジェクト初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadDEnemy();
	if (FAILED(hr)){
		MessageBox(hWnd, _T("地上敵初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadBg();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("背景初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadShadow();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("かげ初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadAcceleration();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("加速エフェクト初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadStreet();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("道初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadField();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("落とし穴初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadTransition();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("トランジション初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadLife();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("ハート初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadItem();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("アイテム初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadCombo();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("コンボ初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadGauge();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("ゲージ初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadText();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("テキスト初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadBlock();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("ブロック初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	InitLife();

	return hr;
}