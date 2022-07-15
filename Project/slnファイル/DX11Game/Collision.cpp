//=============================================================================
// �����蔻�菈��
// ����F���o�n
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
// �����蔻��܂Ƃ�
void Collision()
{
	int nCnt1, nCnt2;	// ���[�v�p�ϐ�

	// �p�h���ƃ{�[��
	for (nCnt1 = 0; nCnt1 < MAX_TEXT; nCnt1++) {
		if (!IsText(nCnt1))	continue;

		for (nCnt2 = 0; nCnt2 < MAX_PLAYER; nCnt2++) {
			if (!IsPlayer(nCnt2))	continue;

			if (CollisionBBS(
				(&GetTextCenter(nCnt1)),
				&GetTextSize(nCnt1),
				&GetPlayerCenter(nCnt2),
				GetPlayerSize(nCnt2).y))
			{	// �����������̏���
				KillText(nCnt1);
			}
		}
	}
}
#pragma endregion

#pragma region 2DCollisions
// �_�Ƌ�`
bool CollisionBPB(XMFLOAT2 * pPoint1, XMFLOAT2 * pCenter2, XMFLOAT2 * pSize2)
{
	float fx = pPoint1->x - pCenter2->x;
	float fy = pPoint1->y - pCenter2->y;
	// x
	if ( pPoint1->x <= pCenter2->x + pSize2->x / 2 &&
		 pPoint1->x >= pCenter2->x - pSize2->x / 2)
		// y
		if( pPoint1->y <= pCenter2->y + pSize2->y / 2 &&
			pPoint1->y >= pCenter2->y - pSize2->y / 2) {
		return true;
	}
	// ������Ȃ�����
	return false;
}

// �_�Ɖ~
bool CollisionBPC(XMFLOAT2 * pPoint1, XMFLOAT2 * pCenter2, float pRadius2)
{
	float fx = pPoint1->x - pCenter2->x;
	float fy = pPoint1->y - pCenter2->y;
	float fr = pRadius2 * pRadius2;
	if ( ((fx*fx)+(fy*fy)) <= (fr*fr) ) {
		return true;
	}
	// ������Ȃ�����
	return false;
}

// ��`�Ƌ�`
bool CollisionBB2D( XMFLOAT2 * pCenter1, XMFLOAT2 * pSize1, XMFLOAT2 * pCenter2, XMFLOAT2 * pSize2 )
{
	if( pCenter1->x + pSize1->x / 2 >= 
		pCenter2->x - pSize2->x / 2 && 
		pCenter1->x - pSize1->x / 2 <=
		pCenter2->x + pSize2->x / 2 )
	{	// X�������������Ă���
		if( pCenter1->y + pSize1->y / 2 >=
			pCenter2->y - pSize2->y / 2 &&
			pCenter1->y - pSize1->y / 2 <=
			pCenter2->y + pSize2->y / 2 )
		{	// Y�������������Ă���
			return true;
		}
	}
	// ������Ȃ�����
	return false;
}

// �~�Ɖ~
bool CollisionBC( XMFLOAT2 * pCenter1, float fRadius1, XMFLOAT2 * pCenter2, float fRadius2 )
{
	float fx = pCenter1->x - pCenter2->x;
	float fy = pCenter1->y - pCenter2->y;
	float len = fx * fx + fy * fy;
	float fr = fRadius1 + fRadius2;
	if( len <= fr * fr )
	{
		return true;	// ��������
	}

	return false;		// �������ĂȂ�
}

// ��`�Ɖ~
// https://ftvoid.com/blog/post/300 ���ϑO
// https://inwans.com/collision-circle-rectangle/ ���ό�(�Q�l���͍��㌴�_�Ȃ̂Œ���)
/*
*  l,t  ____
*      |    |
*      |____|
*            r,b
*/
bool CollisionBBC(XMFLOAT2 * pCenter1, XMFLOAT2 * pSize1, XMFLOAT2 * pCenter2, float fRadius2)
{
	// ��`���`
	float left, top, right, bottom;
	left   = pCenter1->x - pSize1->x / 2;
	top    = pCenter1->y + pSize1->y / 2;
	right  = pCenter1->x + pSize1->x / 2;
	bottom = pCenter1->y - pSize1->y / 2;
#pragma region after
	/* ���ό� */
	// ���菇��ς��A������false�����悤�ɂ���
	//��`�ɉ~�̔��a���𑫂����͈�
	if (left - fRadius2 > pCenter2->x ||
		right + fRadius2 < pCenter2->x ||
		top + fRadius2 < pCenter2->y ||
		bottom - fRadius2 > pCenter2->y) {
		return false;
	}
	//����̓����蔻��
	if (left > pCenter2->x &&
		top < pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
		(top - pCenter2->y) * (top - pCenter2->y) < fRadius2 * fRadius2)) {
		return false;
	}
	//�E��̓����蔻��
	if (right < pCenter2->x &&
		top < pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
		(top - pCenter2->y) * (top - pCenter2->y) < fRadius2 * fRadius2)) {
		return false;
	}
	//�����̓����蔻��
	if (left > pCenter2->x &&
		bottom > pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
		(bottom - pCenter2->y) * (bottom - pCenter2->y) < fRadius2 * fRadius2)) {
		return false;
	}
	//�E���̓����蔻��
	if (right < pCenter2->x &&
		bottom > pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
		(bottom - pCenter2->y) * (bottom - pCenter2->y) < fRadius2 * fRadius2)) {
		return false;
	}

	return true; // ���ׂĂ̏������O�ꂽ���������Ă���
#pragma endregion
#pragma region before
	/* ���ϑO */
	//// �̈�A,B,C,D,E,F���v�Z
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
	//// �S�̈�œ������Ă���
	//if (A && B && C && D && E && F) {
	//	return true;
	//}

	//// �������ĂȂ�
	//return false;
#pragma endregion
}
#pragma endregion


#pragma region 3DCollisions
// �����̂ƒ�����
bool CollisionBB3D(XMFLOAT3* pCenter1, XMFLOAT3* pSize1, XMFLOAT3* pCenter2, XMFLOAT3* pSize2)
{
	if (pCenter1->x + pSize1->x / 2 >=
		pCenter2->x - pSize2->x / 2 &&
		pCenter1->x - pSize1->x / 2 <=
		pCenter2->x + pSize2->x / 2)
	{	// X�������������Ă���
		if (pCenter1->y + pSize1->y / 2 >=
			pCenter2->y - pSize2->y / 2 &&
			pCenter1->y - pSize1->y / 2 <=
			pCenter2->y + pSize2->y / 2)
		{	// Y�������������Ă���
			if (pCenter1->z + pSize1->z / 2 >=
				pCenter2->z - pSize2->z / 2 &&
				pCenter1->z - pSize1->z / 2 <=
				pCenter2->z + pSize2->z / 2)
			{	// X���������������Ă���
				return true;
			}
		}
	}
	// ������Ȃ�����
	return false;
}

// ���Ƌ�
bool CollisionBS(XMFLOAT3* pCenter1, float fRadius1, XMFLOAT3* pCenter2, float fRadius2)
{
	float fx = pCenter1->x - pCenter2->x;
	float fy = pCenter1->y - pCenter2->y;
	float fz = pCenter1->z - pCenter2->x;
	float len = fx * fx + fy * fy + fz * fz;
	float fr = fRadius1 + fRadius2;
	if (len <= fr * fr)
	{
		return true;	// ��������
	}

	return false;		// �������ĂȂ�
}

// �{�b�N�X�ƃX�t�B�A
/*     
*     4_______5
*	  /|     /|
*	0/_|____/1|
*	 | /7   | /6
*	3|/_____|/2
*/
bool CollisionBBS(XMFLOAT3 * pCenter1, XMFLOAT3 * pSize1, XMFLOAT3 * pCenter2, float fRadius2)
{
	// ��`���`
	float left, top, right, bottom;
	left   = pCenter1->x - pSize1->x / 2;
	top    = pCenter1->y + pSize1->y / 2;
	right  = pCenter1->x + pSize1->x / 2;
	bottom = pCenter1->y - pSize1->y / 2;
	// z�p�����[�^���`
	float z_p = pCenter1->z + pSize1->z / 2;
	float z_m = pCenter1->z - pSize1->z / 2;

	//��`�ɉ~�̔��a���𑫂����͈�(��������̈�)
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
	// 0�͈̔�
	if (left > pCenter2->x &&
		top < pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
			(top - pCenter2->y) * (top - pCenter2->y) +
			(z_m - pCenter2->z) * (z_m - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 1�͈̔�
	if (right < pCenter2->x &&
		top < pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
			(top - pCenter2->y) * (top - pCenter2->y) +
			(z_m - pCenter2->z) * (z_m - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 2�͈̔�
	if (right < pCenter2->x &&
		bottom > pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
			(bottom - pCenter2->y) * (bottom - pCenter2->y) +
			(z_m - pCenter2->z) * (z_m - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 3�͈̔�
	if (left > pCenter2->x &&
		bottom > pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
			(bottom - pCenter2->y) * (bottom - pCenter2->y) +
			(z_m - pCenter2->z) * (z_m - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	//z-plus
	// 4�͈̔�
	if (left > pCenter2->x &&
		top < pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
			(top - pCenter2->y) * (top - pCenter2->y) +
			(z_p - pCenter2->z) * (z_p - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 5�͈̔�
	if (right < pCenter2->x &&
		top < pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
			(top - pCenter2->y) * (top - pCenter2->y) +
			(z_p - pCenter2->z) * (z_p - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 6�͈̔�
	if (right < pCenter2->x &&
		bottom > pCenter2->y &&
		!((right - pCenter2->x) * (right - pCenter2->x) +
			(bottom - pCenter2->y) * (bottom - pCenter2->y) +
			(z_p - pCenter2->z) * (z_p - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}
	// 7�͈̔�
	if (left > pCenter2->x &&
		bottom > pCenter2->y &&
		!((left - pCenter2->x) * (left - pCenter2->x) +
			(bottom - pCenter2->y) * (bottom - pCenter2->y) +
			(z_p - pCenter2->z) * (z_p - pCenter2->z) < fRadius2 * fRadius2)) {
		return false;
	}

	return true; // ���ׂĂ̏������O�ꂽ���������Ă���
}

// �~���Ɖ~��
bool CollisionBCy(XMFLOAT3* pCenter1, float height1, float fRadius1, XMFLOAT3* pCenter2, float height2, float fRadius2)
{
	if (pCenter1->y + height1 / 2 >=
		pCenter2->y - height2 / 2 &&
		pCenter1->y - height1 / 2 <=
		pCenter2->y + height2 / 2)
	{	// Y���������͈͓�
		float fx = pCenter1->x - pCenter2->x;
		float fz = pCenter1->z - pCenter2->z;
		float len = fx * fx + fz * fz;
		float fr = fRadius1 + fRadius2;
		if (len < fr * fr) {
			return true;	// ��������
		}
	}
	return false;
}
#pragma endregion