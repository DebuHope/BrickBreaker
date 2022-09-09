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
	MessageBox(hWnd, _T("�v���C���[�������G���["), _T("�������G���["), MB_OK | MB_ICONSTOP);
	return hr;
	}

	hr = LoadBg();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("�w�i�������G���["), _T("�������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadAcceleration();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("�����G�t�F�N�g�������G���["), _T("�������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadTransition();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("�g�����W�V�����������G���["), _T("�������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadLife();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("�n�[�g�������G���["), _T("�������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadCombo();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("�R���{�������G���["), _T("�������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadGauge();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("�Q�[�W�������G���["), _T("�������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadText();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("�e�L�X�g�������G���["), _T("�������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	hr = LoadBlock();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("�u���b�N�������G���["), _T("�������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	InitLife();

	return hr;
}