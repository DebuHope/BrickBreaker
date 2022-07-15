//=============================================================================
// メイン処理
// 制作：向出創
//=============================================================================
#include <time.h>
#include "AssimpModel.h"
#include "Main.h"
#include "Polygon.h"
#include "Debugproc.h"
#include "Mesh.h"
#include "Input.h"
#include "Collision.h"
#include "Shadow.h"
#include "Title.h"
#include "Select.h"
#include "Game.h"
#include "Load.h"
#include "Number.h"
#include "Transition.h"
#include "Sound.h"
#include "Player.h"
#include "D2DRenderTargetsAndDWrite.h"
#include "D2DText.h"
#include "D2DDrawMng.h"

//-------- ライブラリのリンク
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

//=============================================================================
// マクロ定義
//=============================================================================
#define CLASS_NAME		_T("AppClass")		// ウインドウのクラス名
#define WINDOW_NAME		_T("SPEED STREET")	// ウインドウのキャプション名

//=============================================================================
// プロトタイプ宣言
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//=============================================================================
// グローバル変数宣言
//=============================================================================
HWND						g_hWnd;					// メイン ウィンドウ ハンドル
HINSTANCE					g_hInst;				// インスタンス ハンドル

ID3D11Device*				g_pDevice;				// デバイス
ID3D11DeviceContext*		g_pDeviceContext;		// デバイス コンテキスト
IDXGISwapChain*				g_pSwapChain;			// スワップチェーン
ID3D11RenderTargetView*		g_pRenderTargetView;	// フレームバッファ
ID3D11Texture2D*			g_pDepthStencilTexture;	// Zバッファ用メモリ
ID3D11DepthStencilView*		g_pDepthStencilView;	// Zバッファ
UINT						g_uSyncInterval = 0;	// 垂直同期 (0:無, 1:有)
ID3D11RasterizerState*		g_pRs[MAX_CULLMODE];	// ラスタライザ ステート
ID3D11BlendState*			g_pBlendState[MAX_BLENDSTATE];// ブレンド ステート
ID3D11DepthStencilState*	g_pDSS[2];				// Z/ステンシル ステート

D2DRenderTargetsandDWrite*	g_Targets = nullptr;	// D2DとWrite機能のファクトリとレンダーターゲット集
D2DText*					g_D2DText = nullptr;	// Text機能のインスタンスアドレス
D2DTextMng*					g_D2DTextMng = GetTextMng();// Text機能の描画管理インスタンスアドレス

int							g_nCountFPS;			// FPSカウンタ
ETypeScene					g_currentScene;	// 現在のシーン

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 未使用宣言
	UNREFERENCED_PARAMETER(lpCmdLine);		// 未使用宣言

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINFRM)),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		nullptr,
		CLASS_NAME,
		nullptr
	};
	MSG msg;

	// COM初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		MessageBox(NULL, _T("COMの初期化に失敗しました。"), _T("error"), MB_OK);
		return -1;
	}

	// インスタンス ハンドル保存
	g_hInst = hInstance;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域サイズからウィンドウ サイズ算出
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;	
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// ウィンドウの作成
	g_hWnd = CreateWindowEx(dwExStyle,
		CLASS_NAME,
		WINDOW_NAME,
		dwStyle,
		CW_USEDEFAULT,		// ウィンドウの左座標
		CW_USEDEFAULT,		// ウィンドウの上座標
		rc.right - rc.left,	// ウィンドウ横幅
		rc.bottom - rc.top,	// ウィンドウ縦幅
		nullptr,
		nullptr,
		hInstance,
		nullptr);
	// フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	
	// DirectXの初期化(ウィンドウを作成してから行う)
	if (FAILED(Init(g_hWnd, true))) {
		return -1;
	}

	// メッセージループ
	for (;;) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				// PostQuitMessage()が呼ばれたらループ終了
				break;
			} else {
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) {	// 0.5秒ごとに実行
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) {
				dwExecLastTime = dwCurrentTime;
				// 更新処理
				Update();
			}
			// 描画処理
			Draw();
			dwFrameCount++;
		}
	}

	// タイマ設定を元に戻す
	timeEndPeriod(1);

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, g_hInst);

	// COM終了処理
	CoUninitialize();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:					//----- ウィンドウが生成された
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);
	case WM_DESTROY:				//----- ウィンドウ破棄指示がきた
		PostQuitMessage(0);				// システムにスレッドの終了を要求
		break;
	//case WM_KEYDOWN:				//----- キーボードが押された
	//	switch (wParam) {
	//	case VK_ESCAPE:					// [ESC]キーが押された
	//		PostMessage(hWnd, WM_CLOSE, 0, 0);	// [x]が押されたように振舞う
	//		return 0;
	//	}
	//	break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;			// [Alt]+[Enter]時のBEEPを抑止
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// WM_CREATEメッセージハンドラ
//=============================================================================
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// クライアント領域サイズをSCREEN_WIDTH×SCREEN_HEIGHTに再設定.
	RECT rcClnt;
	GetClientRect(hWnd, &rcClnt);
	rcClnt.right -= rcClnt.left;
	rcClnt.bottom -= rcClnt.top;
	if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT) {
		RECT rcWnd;
		GetWindowRect(hWnd, &rcWnd);
		SIZE sizeWnd;
		sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
		sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;
		SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	// IME無効化
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1を返すとCreateWindow[Ex]が失敗する.
}

//=============================================================================
// バックバッファ生成
//=============================================================================
HRESULT CreateBackBuffer(void)
{
	// レンダーターゲットビュー生成
	ID3D11Texture2D* pBackBuffer = nullptr;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	g_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
	SAFE_RELEASE(pBackBuffer);

	// Zバッファ用テクスチャ生成
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = SCREEN_WIDTH;
	td.Height = SCREEN_HEIGHT;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	HRESULT hr = g_pDevice->CreateTexture2D(&td, nullptr, &g_pDepthStencilTexture);
	if (FAILED(hr)) {
		return hr;
	}

	// Zバッファターゲットビュー生成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	hr = g_pDevice->CreateDepthStencilView(g_pDepthStencilTexture, &dsvd, &g_pDepthStencilView);
	if (FAILED(hr)) {
		return hr;
	}

	// 各ターゲットビューをレンダーターゲットに設定
	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (float)SCREEN_WIDTH;
	vp.Height = (float)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pDeviceContext->RSSetViewports(1, &vp);

	return S_OK;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;

	// デバイス、スワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = SCREEN_WIDTH;
	scd.BufferDesc.Height = SCREEN_HEIGHT;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = bWindow;

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	
	//★---変更--- DirectX11上でDirect2Dを使用するために必要
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	//★

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &scd,
		&g_pSwapChain, &g_pDevice, nullptr, &g_pDeviceContext);
	if (FAILED(hr)) {
		return hr;
	}

	// バックバッファ生成
	hr = CreateBackBuffer();
	if (FAILED(hr)) {
		return hr;
	}

	// ラスタライズ設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;	// カリング無し(両面描画)
	g_pDevice->CreateRasterizerState(&rd, &g_pRs[0]);
	rd.CullMode = D3D11_CULL_FRONT;	// 前面カリング(裏面描画)
	g_pDevice->CreateRasterizerState(&rd, &g_pRs[1]);
	rd.CullMode = D3D11_CULL_BACK;	// 背面カリング(表面描画)
	g_pDevice->CreateRasterizerState(&rd, &g_pRs[2]);
	g_pDeviceContext->RSSetState(g_pRs[2]);

	// ブレンド ステート生成
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[0]);
	// ブレンド ステート生成 (アルファ ブレンド用)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[1]);
	// ブレンド ステート生成 (加算合成用)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[2]);
	// ブレンド ステート生成 (減算合成用)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[3]);
	SetBlendState(BS_ALPHABLEND);

	// 深度ステンシルステート生成
	CD3D11_DEFAULT def;
	CD3D11_DEPTH_STENCIL_DESC dsd(def);
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	g_pDevice->CreateDepthStencilState(&dsd, &g_pDSS[0]);
	CD3D11_DEPTH_STENCIL_DESC dsd2(def);
	dsd2.DepthEnable = FALSE;
	g_pDevice->CreateDepthStencilState(&dsd2, &g_pDSS[1]);

	// 乱数初期化
	srand((unsigned int)time(NULL));

	// D2D&Write初期化
	g_Targets = new D2DRenderTargetsandDWrite();
	g_Targets->Init(g_pSwapChain, g_hWnd);
	g_D2DText = new D2DText(g_Targets->GetDWriteFactory(),g_Targets->GetDxgiRenderTarget());

	// シーンの初期化
	g_currentScene = SCENE_TITLE;	// ゲーム起動時のシーンをセット

	// ポリゴン表示初期化
	hr = InitPolygon(g_pDevice);
	if (FAILED(hr))	return hr;

	// デバッグ文字列表示初期化
	hr = InitDebugProc();
	if (FAILED(hr))	return hr;

	// 入力処理初期化
	hr = InitInput();
	if (FAILED(hr))	return hr;

	// Assimpシェーダ初期化
	if (!CAssimpModel::InitShader(g_pDevice))	
		return E_FAIL;

	// メッシュ処理初期化
	hr = InitMesh();
	if (FAILED(hr))	return hr;

	// 影処理初期化
	InitShadow();

	// 数字初期化
	hr = InitNumber();
	if (FAILED(hr))	return hr;

	// トランジション
	InitTransition();

	// サウンド
	hr = InitSound(hWnd);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("サウンド初期化エラー"), _T("初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// モデル/テクスチャのロード
	hr = LoadModelTex();
	if (FAILED(hr))	return hr;

	// シーン毎に分岐して初期化
	switch (g_currentScene)
	{
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_SELECT:
		InitSelect();
		break;
	//case SCENE_STAGE_SELECT:
	//	InitStageSelect();
	//	break;
	case SCENE_STAGE1_1:
	case SCENE_STAGE1_2:
	case SCENE_STAGE1_3:
	case SCENE_STAGE1_4:
	case SCENE_STAGE2_1:
	case SCENE_STAGE2_2:
	case SCENE_STAGE2_3:
	case SCENE_STAGE2_4:
	case SCENE_STAGE3_1:
	case SCENE_STAGE3_2:
	case SCENE_STAGE3_3:
	case SCENE_STAGE3_4:
	case SCENE_ENDING:
		InitGame();
		break;
	default:
		break;
	}

	PlaySound(SOUND_LABEL_BGM01);
	StartSceneChange(SCENE_SELECT);	// ゲーム起動時：タイトル画面

	return hr;
}

//=============================================================================
// バックバッファ解放
//=============================================================================
void ReleaseBackBuffer()
{
	if (g_pDeviceContext) {
		g_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	}
	SAFE_RELEASE(g_pDepthStencilView);
	SAFE_RELEASE(g_pDepthStencilTexture);
	SAFE_RELEASE(g_pRenderTargetView);
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{ 
	switch (g_currentScene)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_SELECT:
		UninitSelect();
		break;
	//case SCENE_STAGE_SELECT:
	//	UninitStageSelect();
	//	break;
	case SCENE_STAGE1_1:
	case SCENE_STAGE1_2:
	case SCENE_STAGE1_3:
	case SCENE_STAGE1_4:
	case SCENE_STAGE2_1:
	case SCENE_STAGE2_2:
	case SCENE_STAGE2_3:
	case SCENE_STAGE2_4:
	case SCENE_STAGE3_1:
	case SCENE_STAGE3_2:
	case SCENE_STAGE3_3:
	case SCENE_STAGE3_4:
	case SCENE_ENDING:
		UninitGame();
		break;
	default:
		break;
	}

	// 影
	UninitShadow();

	// 数字
	UninitNumber();

	// トランジション
	UninitTransition();

	// メッシュ終了処理
	UninitMesh();

	// Assimp用シェーダ終了処理
	CAssimpModel::UninitShader();

	// 入力処理終了処理
	UninitInput();

	// デバッグ文字列表示終了処理
	UninitDebugProc();

	// ポリゴン表示終了処理
	UninitPolygon();

	// サウンド終了
	UninitSound();

	// 深度ステンシルステート解放
	for (int i = 0; i < _countof(g_pDSS); ++i) {
		SAFE_RELEASE(g_pDSS[i]);
	}

	// ブレンド ステート解放
	for (int i = 0; i < MAX_BLENDSTATE; ++i) {
		SAFE_RELEASE(g_pBlendState[i]);
	}

	// ラスタライザ ステート解放
	for (int i = 0; i < MAX_CULLMODE; ++i) {
		SAFE_RELEASE(g_pRs[i]);
	}

	// D2D&Write解放
	SAFE_DELETE(g_D2DText);
	SAFE_DELETE(g_Targets);

	// バックバッファ解放
	ReleaseBackBuffer();

	// スワップチェーン解放
	SAFE_RELEASE(g_pSwapChain);

	// デバイス コンテキストの開放
	SAFE_RELEASE(g_pDeviceContext);

	// デバイスの開放
	SAFE_RELEASE(g_pDevice);
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// コントローラ接続所得
	time_t t = time(NULL);
	t %= 5;
	if (t == 0) {
		GetJoyCountSimple();
	}

	// 入力処理更新
	UpdateInput();	// 必ずUpdate関数の先頭で実行

#ifdef _DEBUG
	// デバッグ文字列表示更新
	UpdateDebugProc();

	// デバッグ文字列設定
	StartDebugProc();

	//SetHiragana(true);	// ひらがな表示ON

	PrintDebugProc("FPS   :%d\n\n", g_nCountFPS);
	PrintDebugProc("Joy X :%d\n\n", (int)GetJoyX(0));
	PrintDebugProc("Joy Y :%d\n\n", (int)GetJoyY(0));
	PrintDebugProc("Joy Z :%d\n\n", (int)GetJoyZ(0));
	PrintDebugProc("+ key :%d\n\n", (int)GetJoyPOVTrigger(0));
	PrintDebugProc("JoyCnt:%d\n\n", t);
	PrintDebugProc("state:%d\n\n", GetState());
	PrintDebugProc("PlayerPosZ:%0.1f X:%0.1f\n\n", GetPlayerPos(0).y, GetPlayerPos(0).x);
#endif // _DEBUG

	switch (g_currentScene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE_SELECT:
		UpdateSelect();
		break;
	//case SCENE_STAGE_SELECT:
	//	UpdateStageSelect();
	//	break;
	case SCENE_STAGE1_1:
	case SCENE_STAGE1_2:
	case SCENE_STAGE1_3:
	case SCENE_STAGE1_4:
	case SCENE_STAGE2_1:
	case SCENE_STAGE2_2:
	case SCENE_STAGE2_3:
	case SCENE_STAGE2_4:
	case SCENE_STAGE3_1:
	case SCENE_STAGE3_2:
	case SCENE_STAGE3_3:
	case SCENE_STAGE3_4:
	case SCENE_ENDING:
		UpdateGame();
		break;
	default:
		break;
	}
	// ポリゴン表示更新
	UpdatePolygon();

	// カメラ更新
	GetCamera()->Update();

	// ライト更新
	GetLight()->Update();

	// 影更新（別のヘッダに移す）
	UpdateShadow();

	// トランジション
	UpdateTransition();

	// 当たり判定
	Collision();

	if (GetKeyTrigger(VK_F1))StartChange(SCENE_TITLE,0);
	if (GetKeyTrigger(VK_F2))StartChange(SCENE_SELECT,0);
	if (GetKeyTrigger(VK_F3))StartChange(SCENE_STAGE1_1,3);
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア　※重要
	float ClearColor[4] = { 0.117647f, 0.254902f, 0.352941f, 1.0f };
	g_pDeviceContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);
	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Zバッファ有効
	SetZBuffer(true);

	// 奥の2Dに描画するものはここ

	// 3D空間中に描画するものはここ

	// 光源処理無効
	GetLight()->SetDisable();

	// シーン毎に切り替える
	switch (g_currentScene)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE_SELECT:
		DrawSelect();
		break;
	//case SCENE_STAGE_SELECT:
	//	DrawStageSelect();
	//	break;
	case SCENE_STAGE1_1:
	case SCENE_STAGE1_2:
	case SCENE_STAGE1_3:
	case SCENE_STAGE1_4:
	case SCENE_STAGE2_1:
	case SCENE_STAGE2_2:
	case SCENE_STAGE2_3:
	case SCENE_STAGE2_4:
	case SCENE_STAGE3_1:
	case SCENE_STAGE3_2:
	case SCENE_STAGE3_3:
	case SCENE_STAGE3_4:
	case SCENE_ENDING:
		DrawGame();
		break;
	default:
		break;
	}

	// この後にモデルの描画はしないこと

	// Zバッファ無効	// 手前の2Dに描画するものはここ
	SetZBuffer(false);

	// Text描画
	g_D2DTextMng->Render();

	// デバッグ文字列表示
	SetBlendState(BS_ALPHABLEND);
	// トランジション
	SetPolygonColor(0.0f, 2.0f, 0.0f);
	DrawDebugProc();
	SetBlendState(BS_NONE);
	SetZBuffer(true);
	// バックバッファとフロントバッファの入れ替え　この分は一番したに置く
	g_pSwapChain->Present(g_uSyncInterval, 0);
}


//=============================================================================
// メイン ウィンドウ ハンドル取得
//=============================================================================
HWND GetMainWnd()
{
	return g_hWnd;
}

//=============================================================================
// インスタンス ハンドル取得
//=============================================================================
HINSTANCE GetInstance()
{
	return g_hInst;
}

//=============================================================================
// デバイス取得
//=============================================================================
ID3D11Device* GetDevice()
{
	return g_pDevice;
}

//=============================================================================
// デバイス コンテキスト取得
//=============================================================================
ID3D11DeviceContext* GetDeviceContext()
{
	return g_pDeviceContext;
}

//=============================================================================
// 深度バッファ有効無効制御
//=============================================================================
void SetZBuffer(bool bEnable)
{
	g_pDeviceContext->OMSetDepthStencilState((bEnable) ? nullptr : g_pDSS[1], 0);
}

//=============================================================================
// 深度バッファ更新有効無効制御
//=============================================================================
void SetZWrite(bool bEnable)
{
	g_pDeviceContext->OMSetDepthStencilState((bEnable) ? nullptr : g_pDSS[0], 0);
}

//=============================================================================
// ブレンド ステート設定
//=============================================================================
void SetBlendState(int nBlendState)
{
	if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		g_pDeviceContext->OMSetBlendState(g_pBlendState[nBlendState], blendFactor, 0xffffffff);
	}
}

//=============================================================================
// カリング設定
//=============================================================================
void SetCullMode(int nCullMode)
{
	if (nCullMode >= 0 && nCullMode < MAX_CULLMODE) {
		g_pDeviceContext->RSSetState(g_pRs[nCullMode]);
	}
}

//=============================================================================
// シーン移行開始
// 引数 : E_TYPE_SCENE　next 移行先のシーン番号
//=============================================================================
void StartSceneChange(ETypeScene NextScene)
{
	// 現在のシーンを終了
	switch (g_currentScene)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_SELECT:
		UninitSelect();
		break;
	//case SCENE_STAGE_SELECT:
	//	UninitStageSelect();
	//	break;
	case SCENE_STAGE1_1:
	case SCENE_STAGE1_2:
	case SCENE_STAGE1_3:
	case SCENE_STAGE1_4:
	case SCENE_STAGE2_1:
	case SCENE_STAGE2_2:
	case SCENE_STAGE2_3:
	case SCENE_STAGE2_4:
	case SCENE_STAGE3_1:
	case SCENE_STAGE3_2:
	case SCENE_STAGE3_3:
	case SCENE_STAGE3_4:
	case SCENE_ENDING:
		UninitGame();
		break;
	default:
		break;
	}

	// 遷移先のシーン番号をセット
	g_currentScene = NextScene;
	switch (g_currentScene)
	{
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_SELECT:
		InitSelect();
		break;
	//case SCENE_STAGE_SELECT:
	//	InitStageSelect();
	//	break;
	case SCENE_STAGE1_1:
	case SCENE_STAGE1_2:
	case SCENE_STAGE1_3:
	case SCENE_STAGE1_4:
	case SCENE_STAGE2_1:
	case SCENE_STAGE2_2:
	case SCENE_STAGE2_3:
	case SCENE_STAGE2_4:
	case SCENE_STAGE3_1:
	case SCENE_STAGE3_2:
	case SCENE_STAGE3_3:
	case SCENE_STAGE3_4:
	case SCENE_ENDING:
		InitGame();
		break;
	default:
		break;
	}
}

//=============================================================================
// シーン番号所得
//=============================================================================
ETypeScene GetSceneNo()
{
	return g_currentScene;
}

void ReleaseGame()
{
	PostMessage(GetMainWnd(), WM_CLOSE, 0, 0);
}

D2DText * GetD2DText()
{
	return g_D2DText;
}


// フルスクリーン
//g_pSwapChain->SetFullscreenState(true, 0);
//g_pSwapChain->SetFullscreenState(false, 0);