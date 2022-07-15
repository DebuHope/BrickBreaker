//=============================================================================
// メインまとめ
// 制作：向出創
//=============================================================================
#pragma once

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define NOMINMAX
#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Resource.h"
#define _USE_MATH_DEFINES
#include <math.h>

// 本来はヘッダに書かない方が良い
using namespace DirectX;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){(x)->Release();x=nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x){delete(x);x=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if(x){delete[](x);x=nullptr;}}
#endif

#define SCREEN_WIDTH	(1920)				// ウインドウの幅
#define SCREEN_HEIGHT	(1080)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH/2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT/2)	// ウインドウの中心Ｙ座標
#define	NUM_VERTEX		(4)					// 頂点数
#define	NUM_POLYGON		(2)					// ポリゴン数

#define SinDeg(degree)	(sinf(XMConvertToRadians(degree)))
#define CosDeg(degree)	(cosf(XMConvertToRadians(degree)))

//*****************************************************************************
// 列挙型定義
//*****************************************************************************
// 合成の種類
enum EBlendState {
	BS_NONE = 0,							// 半透明合成無し
	BS_ALPHABLEND,							// 半透明合成
	BS_ADDITIVE,							// 加算合成
	BS_SUBTRACTION,							// 減算合成

	MAX_BLENDSTATE
};

// カリング情報
enum ECullMode {
	CULLMODE_NONE = 0,						// カリングしない
	CULLMODE_CW,							// 前面カリング
	CULLMODE_CCW,							// 背面カリング

	MAX_CULLMODE
};

//シーンの種類
enum ETypeScene {
	SCENE_TITLE,
	SCENE_SELECT,
	SCENE_STAGE1_1,
	SCENE_STAGE1_2,
	SCENE_STAGE1_3,
	SCENE_STAGE1_4,
	SCENE_STAGE2_1,
	SCENE_STAGE2_2,
	SCENE_STAGE2_3,
	SCENE_STAGE2_4,
	SCENE_STAGE3_1,
	SCENE_STAGE3_2,
	SCENE_STAGE3_3,
	SCENE_STAGE3_4,
	SCENE_ENDING,

	MAX_SCENE
};

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
typedef struct {
	XMFLOAT3 vtx;		// 頂点座標
	XMFLOAT4 diffuse;	// 拡散反射光
	XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_2D;

// 頂点フォーマット( 頂点座標[3D] / 法線ベクトル / 反射光 / テクスチャ座標 )
typedef struct {
	XMFLOAT3 vtx;		// 頂点座標
	XMFLOAT3 nor;		// 法線ベクトル
	XMFLOAT4 diffuse;	// 拡散反射光
	XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_3D;

// 2Dアニメーション構造体
typedef struct {
	int nPatNo;	// 表示パターン番号
	int nCount;	// 表示フレーム数
}ANIM_PAT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HWND GetMainWnd();
HINSTANCE GetInstance();
ID3D11Device* GetDevice();
ID3D11DeviceContext* GetDeviceContext();
void SetZBuffer(bool bEnable);
void SetZWrite(bool bEnable);
void SetBlendState(int nBlendState);
void SetCullMode(int nCullMode);

void StartSceneChange(ETypeScene NextScene);	// シーン遷移開始
ETypeScene GetSceneNo();		// 現在のシーン番号所得

void ReleaseGame();