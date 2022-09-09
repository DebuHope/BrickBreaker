#include "Load.h"
#include "Bg.h"
#include "EF_Acceleration.h"
#include "Player.h"
#include "Transition.h"
#include "Life.h"
#include "Combo.h"
#include "Gauge.h"
#include "Endroll.h"
#include "Block.h"

HRESULT LoadModelTex()
{
	HRESULT hr = S_OK;
	HWND hWnd = GetMainWnd();

	hr = LoadPlayer();
	if (FAILED(hr)){
	MessageBox(hWnd, _T("プレイヤー初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
	return hr;
	}

	hr = LoadBg();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("背景初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadAcceleration();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("加速エフェクト初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
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