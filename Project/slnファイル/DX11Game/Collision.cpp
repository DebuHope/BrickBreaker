//=============================================================================
// 当たり判定処理
// 制作：向出創
//=============================================================================
#include "Debugproc.h"
#include "Collision.h"
#include "Player.h"
#include "DEnemy.h"
//#include "UEnemy.h"
//#include "Car.h"
//#include "Hole.h"
#include "Item.h"
#include "Score.h"
#include "Life.h"
//#include "CheckPoint.h"
//#include "Goal.h"
#include "Sound.h"
#include "Transition.h"
#include "Endroll.h"

#pragma region AllCollisionChecker
// 当たり判定まとめ
void Collision()
{
	int nCnt1, nCnt2;	// ループ用変数

	// プレイヤーと地上敵
	for (nCnt1 = 0; nCnt1 < MAX_DENEMY; nCnt1++) {
		if (!IsDEnemy(nCnt1))	continue;

		for (nCnt2 = 0; nCnt2 < MAX_PLAYER; nCnt2++) {
			if (!IsPlayer(nCnt2))	continue;

			if (CollisionBCy(
				(&GetDEnemyPos(nCnt1)),
				GetDEnemySize(nCnt1).y,
				GetDEnemySize(nCnt1).x,
				&GetPlayerCenter(nCnt2),
				GetPlayerBBox(nCnt2).y,
				GetPlayerBBox(nCnt2).x))
			{	// 当たった時の処理
				//if (GetPlayerPhose(nCnt2) != SDOWN && GetPlayerPhose(nCnt2) != WDOWN &&
				//	GetPlayerPhose(nCnt2) != FALL && GetPlayerPhose(nCnt2) != SLIDE) {
				//	PlayerPhoseChange(nCnt2, WDOWN);
				//	RemainingLife(1);
				//	AddCountCombo(-999);
				//	PlaySound(SOUND_LABEL_SE_HIT);

				//	break;
				//}

				//if (GetDEnemy(nCnt1) == 5 || GetDEnemy(nCnt1) == 7) {
				//	PlayerPhoseChange(nCnt2, WDOWN);
				//	RemainingLife(1);
				//	AddCountCombo(-999);
				//	PlaySound(SOUND_LABEL_SE_HIT);

				//	break;
				//}

				//if (GetPlayerPhose(nCnt2) == SLIDE && GetDEnemy(nCnt1) != 5) {
				//	KillDEnemy(nCnt1);
				//	AddCountCombo(1);
				//	AddCountKill(1);
				//	PlaySound(SOUND_LABEL_SE_HIT);

				//	break;
				//}
			}
		}
	}

	// プレイヤーと空中敵
	//for (nCnt1 = 0; nCnt1 < MAX_UENEMY; nCnt1++) {
	//	if (!IsUEnemy(nCnt1))	continue;

	//	for (nCnt2 = 0; nCnt2 < MAX_PLAYER; nCnt2++) {
	//		if (!IsPlayer(nCnt2))	continue;

	//		if (CollisionBCy(
	//			&GetUEnemyPos(nCnt1),
	//			GetUEnemySize(nCnt1).y,
	//			GetUEnemySize(nCnt1).x,
	//			&GetPlayerCenter(nCnt2),
	//			GetPlayerBBox(nCnt2).y,
	//			GetPlayerBBox(nCnt2).x))
	//		{	// 当たった時の処理
	//			if (GetPlayerPhose(nCnt2) != SDOWN && GetPlayerPhose(nCnt2) != WDOWN && 
	//				GetPlayerPhose(nCnt2) != FALL && GetPlayerPhose(nCnt2) != SLIDE && GetPlayerPhose(nCnt2) != JUMP) {
	//				PlayerPhoseChange(nCnt2, SDOWN);
	//				RemainingLife(1);
	//				AddCountCombo(-999);
	//				PlaySound(SOUND_LABEL_SE_HIT);

	//				break;
	//			}

	//			if (GetUEnemy(nCnt1) == 7) {
	//				PlayerPhoseChange(nCnt2, SDOWN);
	//				RemainingLife(1);
	//				AddCountCombo(-999);
	//				PlaySound(SOUND_LABEL_SE_HIT);
	//				break;
	//			}

	//			if (GetPlayerPhose(nCnt2) == JUMP) {
	//				KillUEnemy(nCnt1);
	//				AddCountCombo(1);
	//				AddCountKill(1);
	//				PlaySound(SOUND_LABEL_SE_HIT);

	//				break;
	//			}
	//		}
	//	}
	//}

	// プレイヤーと車
	//for (nCnt1 = 0; nCnt1 < MAX_CAR; nCnt1++) {
	//	if (!IsCar(nCnt1))	continue;

	//	for (nCnt2 = 0; nCnt2 < MAX_PLAYER; nCnt2++) {
	//		if (!IsPlayer(nCnt2))	continue;

	//		if (CollisionBCy(
	//			&GetCarCenter(nCnt1),
	//			GetCarBBox(nCnt1).y,
	//			GetCarBBox(nCnt1).x,
	//			&GetPlayerCenter(nCnt2),
	//			GetPlayerBBox(nCnt2).y,
	//			GetPlayerBBox(nCnt2).x))
	//		{	// 当たった時の処理
	//			if (GetPlayerPhose(nCnt2) != SDOWN && GetPlayerPhose(nCnt2) != WDOWN &&
	//				GetPlayerPhose(nCnt2) != FALL) {
	//			PlayerPhoseChange(nCnt2, SDOWN);
	//			RemainingLife(1);
	//			AddCountCombo(-999);
	//			PlaySound(SOUND_LABEL_SE_HIT);
	//			break;
	//			}
	//		}
	//	}
	//}

	// プレイヤーと穴
	//for (nCnt1 = 0; nCnt1 < MAX_HOLE; nCnt1++) {
	//	if (!IsHole(nCnt1))	continue;

	//	for (nCnt2 = 0; nCnt2 < MAX_PLAYER; nCnt2++) {
	//		//if (!IsPlayer(nCnt2))	continue;

	//		if (CollisionBB3D(
	//			&GetHolePos(nCnt1),
	//			&GetHoleSize(nCnt1),
	//			&GetPlayerCenter(nCnt2),
	//			&GetPlayerBBox(nCnt2)))
	//		{	// 当たった時の処理
	//			if (GetPlayerPhose(0) != JUMP) {
	//				PlayerPhoseChange(nCnt2, FALL);
	//				PlaySound(SOUND_LABEL_SE_FALL);
	//			}
	//			break;
	//		}
	//	}
	//}

	// プレイヤーとキャンディ
	for (nCnt1 = 0; nCnt1 < MAX_ITEM; nCnt1++) {
		if (!IsItem(nCnt1))	continue;

		for (nCnt2 = 0; nCnt2 < MAX_PLAYER; nCnt2++) {
			//if (!IsPlayer(nCnt2))	continue;

			if (CollisionBCy(
				&GetItemPos(nCnt1),
				GetItemSize(nCnt1).y,
				GetItemSize(nCnt1).x,
				&GetPlayerCenter(nCnt2),
				GetPlayerBBox(nCnt2).y,
				GetPlayerBBox(nCnt2).x))
			{	// 当たった時の処理
				DestroyItem(nCnt1);
				AddCountCombo(1);
				PlaySound(SOUND_LABEL_SE_CANDY);
				break;
			}
		}
	}

	// プレイヤーとチェックポイント
	//for (nCnt1 = 0; nCnt1 < MAX_CHECKPOINT; nCnt1++) {
	//	if (!IsCheckPoint(nCnt1))	continue;

	//	for (nCnt2 = 0; nCnt2 < MAX_PLAYER; nCnt2++) {
	//		//if (!IsPlayer(nCnt2))	continue;

	//		if (CollisionBCy(
	//			&GetCheckPointPos(nCnt1),
	//			GetCheckPointSize(nCnt1).y,
	//			GetCheckPointSize(nCnt1).x,
	//			&GetPlayerCenter(nCnt2),
	//			GetPlayerBBox(nCnt2).y,
	//			GetPlayerBBox(nCnt2).x))
	//		{	// 当たった時の処理
	//			DestroyCheckPoint(nCnt1);
	//			SetCheckFlag(0, true);
	//			SetBeforeScore();
	//			PlaySound(SOUND_LABEL_SE_CHECKPOINT);
	//			break;
	//		}
	//	}
	//}

	// プレイヤーとエンドロール
	//for (nCnt1 = 0; nCnt1 < MAX_TEXT; nCnt1++) {
	//	if (!IsText(nCnt1))	continue;

	//	for (nCnt2 = 0; nCnt2 < MAX_PLAYER; nCnt2++) {
	//		if (!IsPlayer(nCnt2))	continue;

	//		if (CollisionBCy(
	//			&GetTextPos(nCnt1),
	//			GetTextSize(nCnt1).y,
	//			GetTextSize(nCnt1).x * 20.0f,
	//			&GetPlayerCenter(nCnt2),
	//			GetPlayerBBox(nCnt2).y,
	//			GetPlayerBBox(nCnt2).x))
	//		{	// 当たった時の処理
	//			if (GetPlayerPhose(nCnt2) == JUMP) {
	//				KillText(nCnt1);
	//				PlaySound(SOUND_LABEL_SE_HIT);
	//				break;
	//			}
	//		}
	//	}
	//}
}
#pragma endregion

#pragma region 2DCollisions
// 点と矩形
bool CollisionBPB(XMFLOAT2 * pPoint1, XMFLOAT2 * pCenter2, XMFLOAT2 * pSize2)
{
	float fx = pPoint1->x - pCenter2->x;
	float fy = pPoint1->y - pCenter2->y;
	// x
	if ( pPoint1->x <= pCenter2->x + pSize2->x &&
		 pPoint1->x >= pCenter2->x - pSize2->x )
		// y
		if( pPoint1->y <= pCenter2->y + pSize2->y &&
			pPoint1->y >= pCenter2->y - pSize2->y ) {
		return true;
	}
	// 当たらなかった
	return false;
}

// 点と円
bool CollisionBPC(XMFLOAT2 * pPoint1, XMFLOAT2 * pCenter2, float pRadius2)
{
	float fx = pPoint1->x - pCenter2->x;
	float fy = pPoint1->y - pCenter2->y;
	float fr = pRadius2 * pRadius2;
	if ( ((fx*fx)+(fy*fy)) <= (fr*fr) ) {
		return true;
	}
	// 当たらなかった
	return false;
}

// 矩形と矩形
bool CollisionBB2D( XMFLOAT2 * pCenter1, XMFLOAT2 * pSize1, XMFLOAT2 * pCenter2, XMFLOAT2 * pSize2 )
{
	if( pCenter1->x + pSize1->x >= 
		pCenter2->x - pSize2->x && 
		pCenter1->x - pSize1->x <=
		pCenter2->x + pSize2->x )
	{	// X方向が当たっている
		if( pCenter1->y + pSize1->y >=
			pCenter2->y - pSize2->y &&
			pCenter1->y - pSize1->y <=
			pCenter2->y + pSize2->y )
		{	// Y方向も当たっている
			return true;
		}
	}
	// 当たらなかった
	return false;
}

// 円と円
bool CollisionBC( XMFLOAT2 * pCenter1, float fRadius1, XMFLOAT2 * pCenter2, float fRadius2 )
{
	float fx = pCenter1->x - pCenter2->x;
	float fy = pCenter1->y - pCenter2->y;
	float len = fx * fx + fy * fy;
	float fr = fRadius1 + fRadius2;
	if( len <= fr * fr )
	{
		return true;	// 当たった
	}

	return false;		// 当たってない
}

// 矩形と円
// https://ftvoid.com/blog/post/300 改変前
// https://inwans.com/collision-circle-rectangle/ 改変後(参考元は左上原点なので注意)
/*
*  l,t  ____
*      |    |
*      |____|
*            r,b
*/
bool CollisionBBC(XMFLOAT2 * pCenter1, XMFLOAT2 * pSize1, XMFLOAT2 * pCenter2, float fRadius2)
{
	// 矩形を定義
	float left, top, right, bottom;
	left = pCenter1->x - pSize1->x;
	top = pCenter1->y + pSize1->y;
	right = pCenter1->x + pSize1->x;
	bottom = pCenter1->y - pSize1->y;
#pragma region after
	/* 改変後 */
	// 判定順を変え、早期にfalseを取るようにした
	//矩形に円の半径分を足した範囲
	if (left - fRadius2 > pCenter2->x ||
		right + fRadius2 < pCenter2->x ||
		top + fRadius2 < pCenter2->y ||
		bottom - fRadius2 > pCenter2->y) {
		return false;
	}
	//左上の当たり判定
	if (left > pCenter2->x &&
		top < pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
		(top - pCenter2->y) * (top - pCenter2->y) < fRadius2 * fRadius2)) {
		return false;
	}
	//右上の当たり判定
	if (right < pCenter2->x &&
		top < pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
		(top - pCenter2->y) * (top - pCenter2->y) < fRadius2 * fRadius2)) {
		return false;
	}
	//左下の当たり判定
	if (left > pCenter2->x &&
		bottom > pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
		(bottom - pCenter2->y) * (bottom - pCenter2->y) < fRadius2 * fRadius2)) {
		return false;
	}
	//右下の当たり判定
	if (right < pCenter2->x &&
		bottom > pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
		(bottom - pCenter2->y) * (bottom - pCenter2->y) < fRadius2 * fRadius2)) {
		return false;
	}

	return true; // すべての条件が外れた時当たっている
#pragma endregion
#pragma region before
	/* 改変前 */
	//// 領域A,B,C,D,E,Fを計算
	//bool A, B, C, D, E, F;
	//// A
	//if (pCenter2->x >= r.left &&
	//	pCenter2->x <= r.right &&
	//	pCenter2->y >= (r.top - fRadius2) &&
	//	pCenter2->y <= (r.bottom + fRadius2)) {
	//	A = true;
	//}
	//// B
	//if (pCenter2->x >= (r.left - fRadius2) &&
	//	pCenter2->x <= (r.right + fRadius2) &&
	//	pCenter2->y >= r.top &&
	//	pCenter2->y <= r.bottom) {
	//	B = true;
	//}
	//// C
	//if ( (r.left - pCenter2->x)*(r.left - pCenter2->x) +
	//	 (r.top - pCenter2->y)*(r.top - pCenter2->y)
	//	 <= fRadius2 * fRadius2 ) {
	//	C = true;
	//}
	//// D
	//if ((r.right - pCenter2->x)*(r.right - pCenter2->x) +
	//	(r.top - pCenter2->y)*(r.top - pCenter2->y)
	//	<= fRadius2 * fRadius2) {
	//	D = true;
	//}
	//// E
	//if ((r.right - pCenter2->x)*(r.right - pCenter2->x) +
	//	(r.bottom - pCenter2->y)*(r.bottom - pCenter2->y)
	//	<= fRadius2 * fRadius2) {
	//	E = true;
	//}
	//// F
	//if ((r.left- pCenter2->x)*(r.left - pCenter2->x) +
	//	(r.bottom - pCenter2->y)*(r.bottom - pCenter2->y)
	//	<= fRadius2 * fRadius2) {
	//	F = true;
	//}
	//// 全領域で当たっている
	//if (A && B && C && D && E && F) {
	//	return true;
	//}

	//// 当たってない
	//return false;
#pragma endregion
}
#pragma endregion


#pragma region 3DCollisions
// 直方体と直方体
bool CollisionBB3D(XMFLOAT3* pCenter1, XMFLOAT3* pSize1, XMFLOAT3* pCenter2, XMFLOAT3* pSize2)
{
	if (pCenter1->x + pSize1->x >=
		pCenter2->x - pSize2->x &&
		pCenter1->x - pSize1->x <=
		pCenter2->x + pSize2->x)
	{	// X方向が当たっている
		if (pCenter1->y + pSize1->y >=
			pCenter2->y - pSize2->y &&
			pCenter1->y - pSize1->y <=
			pCenter2->y + pSize2->y)
		{	// Y方向も当たっている
			if (pCenter1->z + pSize1->z >=
				pCenter2->z - pSize2->z &&
				pCenter1->z - pSize1->z <=
				pCenter2->z + pSize2->z)
			{	// X軸方向も当たっている
				return true;
			}
		}
	}
	// 当たらなかった
	return false;
}

// 球と球
bool CollisionBS(XMFLOAT3* pCenter1, float fRadius1, XMFLOAT3* pCenter2, float fRadius2)
{
	float fx = pCenter1->x - pCenter2->x;
	float fy = pCenter1->y - pCenter2->y;
	float fz = pCenter1->z - pCenter2->x;
	float len = fx * fx + fy * fy + fz * fz;
	float fr = fRadius1 + fRadius2;
	if (len <= fr * fr)
	{
		return true;	// 当たった
	}

	return false;		// 当たってない
}

// 立方体と球
/*     
*     4_______5
*	  /|     /|
*	0/_|____/1|
*	 | /7   | /6
*	3|/_____|/2
*/
bool CollisionBBS(XMFLOAT3 * pCenter1, XMFLOAT3 * pSize1, XMFLOAT3 * pCenter2, float fRadius2)
{
	// 矩形を定義
	float left, top, right, bottom;
	left = pCenter1->x - pSize1->x;
	top = pCenter1->y + pSize1->y;
	right = pCenter1->x + pSize1->x;
	bottom = pCenter1->y - pSize1->y;
	// zパラメータを定義
	float z_p = pCenter1->z + pSize1->z;
	float z_m = pCenter1->z - pSize1->z;

	//矩形に円の半径分を足した範囲(早期判定領域)
	if (left - fRadius2 > pCenter2->x ||
		right + fRadius2 < pCenter2->x ||
		top + fRadius2 < pCenter2->y ||
		bottom - fRadius2 > pCenter2->y ||
		z_m - fRadius2 > pCenter2->z ||
		z_p + fRadius2 < pCenter2->z
		) {
		return false;
	}
	// z-minus
	// 0の範囲
	if (left > pCenter2->x &&
		top < pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
			(top - pCenter2->y) * (top - pCenter2->y) +
			(z_m - pCenter2->z) * (z_m - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 1の範囲
	if (right < pCenter2->x &&
		top < pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
			(top - pCenter2->y) * (top - pCenter2->y) +
			(z_m - pCenter2->z) * (z_m - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 2の範囲
	if (right < pCenter2->x &&
		bottom > pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
			(bottom - pCenter2->y) * (bottom - pCenter2->y) +
			(z_m - pCenter2->z) * (z_m - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 3の範囲
	if (left > pCenter2->x &&
		bottom > pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
			(bottom - pCenter2->y) * (bottom - pCenter2->y) +
			(z_m - pCenter2->z) * (z_m - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	//z-plus
	// 4の範囲
	if (left > pCenter2->x &&
		top < pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
			(top - pCenter2->y) * (top - pCenter2->y) +
			(z_p - pCenter2->z) * (z_p - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 5の範囲
	if (right < pCenter2->x &&
		top < pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
			(top - pCenter2->y) * (top - pCenter2->y) +
			(z_p - pCenter2->z) * (z_p - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 6の範囲
	if (right < pCenter2->x &&
		bottom > pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
			(bottom - pCenter2->y) * (bottom - pCenter2->y) +
			(z_p - pCenter2->z) * (z_p - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 7の範囲
	if (left > pCenter2->x &&
		bottom > pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
			(bottom - pCenter2->y) * (bottom - pCenter2->y) +
			(z_p - pCenter2->z) * (z_p - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}

	return true; // すべての条件が外れた時当たっている
}

// 円柱と円柱
bool CollisionBCy(XMFLOAT3* pCenter1, float height1, float fRadius1, XMFLOAT3* pCenter2, float height2, float fRadius2)
{
	if (pCenter1->y + height1 >=
		pCenter2->y - height2 &&
		pCenter1->y - height1 <=
		pCenter2->y + height2)
	{	// Y軸方向が範囲内
		float fx = pCenter1->x - pCenter2->x;
		float fz = pCenter1->z - pCenter2->z;
		float len = fx * fx + fz * fz;
		float fr = fRadius1 + fRadius2;
		if (len < fr * fr) {
			return true;	// 当たった
		}
	}
	return false;
}
#pragma endregion