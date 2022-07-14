//=============================================================================
// 当たり判定まとめ
// 制作：向出創
//=============================================================================
#pragma once

#include "Main.h"

void Collision();	// 当たり判定まとめ

/*
*  2D判定
*/
// 22/07/15 sizeの定義を1辺の長さに修正
///* 引数のsizeは中心から辺までの距離とする(元プログラムに合わせるため)
//*  ----   ----分がsize
//*  | * |
//*  ----
//*/
// バウンディングポイントボックス(BPB)
/*@brief: 2DPoint & 2DBox
* [in]	: pPoint1	点
* [in]	: pCenter2	中心
* [in]	: pSize2	辺の長さ
*/
bool CollisionBPB(
	XMFLOAT2* pPoint1,
	XMFLOAT2* pCenter2, XMFLOAT2* pSize2);

// バウンディングポイントサークル(BPC)
/*@brief: 2DPoint & 2DBox
* [in]	: pPoint1	点
* [in]	: pCenter2	中心
* [in]	: pRadius2	半径
*/
bool CollisionBPC(
	XMFLOAT2* pPoint1,
	XMFLOAT2* pCenter2, float pRadius2);

// バウンディングボックス(BB2D)
/*@brief: 2DBox & 2DBox
* [in]	: pCenter1	中心
* [in]	: pSize1	辺の長さ
* [in]	: pCenter2	中心
* [in]	: pSize2	辺の長さ
*/
bool CollisionBB2D(
	XMFLOAT2* pCenter1, XMFLOAT2* pSize1,
	XMFLOAT2* pCenter2, XMFLOAT2* pSize2);

// バウンディングサークル(BC)
/*@brief: 2DCircle & 2DCircle
* [in]	: pCenter1	中心
* [in]	: pRadius1	半径
* [in]	: pCenter2	中心
* [in]	: pRadius2	半径
*/
bool CollisionBC(
	XMFLOAT2* pCenter1, float fRadius1,
	XMFLOAT2* pCenter2, float fRadius2 );

// バウンディングボックスサークル(BBC)
/*@brief: 2Dbox & 2DCircle
* [in]	: pCenter1	中心
* [in]	: pSize1	辺の長さ
* [in]	: pCenter2	中心
* [in]	: pRadius2	半径
*/
bool CollisionBBC(
	XMFLOAT2* pCenter1, XMFLOAT2* pSize1,
	XMFLOAT2* pCenter2, float fRadius2);


/*
*  3D判定
*/
// バウンティングボックス(BB3D)
/*@brief: 2DCube & 2DCube
* [in]	: pCenter1	中心
* [in]	: pSize1	辺の長さ
* [in]	: pCenter2	中心
* [in]	: pSize2	辺の長さ
*/
bool CollisionBB3D(
	XMFLOAT3* pCenter1, XMFLOAT3* pSize1,
	XMFLOAT3* pCenter2, XMFLOAT3* pSize2);

// バウンティングスフィア(BS)
/*@brief: 3DSphere & 3DSphere
* [in]	: pCenter1	中心
* [in]	: pRadius1	半径
* [in]	: pCenter2	中心
* [in]	: pRadius2	半径
*/
bool CollisionBS(
	XMFLOAT3* pCenter1, float fRadius1,
	XMFLOAT3* pCenter2, float fRadius2);

// バウンディングボックススフィア(BBS)
/*@brief: 3DCube & 3DSphere
* [in]	: pCenter1	中心
* [in]	: pSize1	辺の長さ
* [in]	: pCenter2	中心
* [in]	: pRadius2	半径
*/
bool CollisionBBS(
	XMFLOAT3* pCenter1, XMFLOAT3* pSize1,
	XMFLOAT3* pCenter2, float fRadius2);

// バウンディングシリンダー(BCy)
/*@brief: 3DCylinder & 3DCylinder
* [in]	: pCenter1	中心
* [in]	: height1	円柱の高さ
* [in]	: pRadius1	半径
* [in]	: pCenter2	中心
* [in]	: height2	円柱の高さ
* [in]	: pRadius2	半径
*/
bool CollisionBCy(
	XMFLOAT3* pCenter1, float height1, float fRadius1,
	XMFLOAT3* pCenter2, float height2, float fRadius2);