//=============================================================================
// �����蔻��܂Ƃ�
// ����F���o�n
//=============================================================================
#pragma once

#include "Main.h"

void Collision();	// �����蔻��܂Ƃ�

/*
*  2D����
*/
// 22/07/15 size�̒�`��1�ӂ̒����ɏC��
///* ������size�͒��S����ӂ܂ł̋����Ƃ���(���v���O�����ɍ��킹�邽��)
//*  ----   ----����size
//*  | * |
//*  ----
//*/
// �o�E���f�B���O�|�C���g�{�b�N�X(BPB)
/*@brief: 2DPoint & 2DBox
* [in]	: pPoint1	�_
* [in]	: pCenter2	���S
* [in]	: pSize2	�ӂ̒���
*/
bool CollisionBPB(
	XMFLOAT2* pPoint1,
	XMFLOAT2* pCenter2, XMFLOAT2* pSize2);

// �o�E���f�B���O�|�C���g�T�[�N��(BPC)
/*@brief: 2DPoint & 2DBox
* [in]	: pPoint1	�_
* [in]	: pCenter2	���S
* [in]	: pRadius2	���a
*/
bool CollisionBPC(
	XMFLOAT2* pPoint1,
	XMFLOAT2* pCenter2, float pRadius2);

// �o�E���f�B���O�{�b�N�X(BB2D)
/*@brief: 2DBox & 2DBox
* [in]	: pCenter1	���S
* [in]	: pSize1	�ӂ̒���
* [in]	: pCenter2	���S
* [in]	: pSize2	�ӂ̒���
*/
bool CollisionBB2D(
	XMFLOAT2* pCenter1, XMFLOAT2* pSize1,
	XMFLOAT2* pCenter2, XMFLOAT2* pSize2);

// �o�E���f�B���O�T�[�N��(BC)
/*@brief: 2DCircle & 2DCircle
* [in]	: pCenter1	���S
* [in]	: pRadius1	���a
* [in]	: pCenter2	���S
* [in]	: pRadius2	���a
*/
bool CollisionBC(
	XMFLOAT2* pCenter1, float fRadius1,
	XMFLOAT2* pCenter2, float fRadius2 );

// �o�E���f�B���O�{�b�N�X�T�[�N��(BBC)
/*@brief: 2Dbox & 2DCircle
* [in]	: pCenter1	���S
* [in]	: pSize1	�ӂ̒���
* [in]	: pCenter2	���S
* [in]	: pRadius2	���a
*/
bool CollisionBBC(
	XMFLOAT2* pCenter1, XMFLOAT2* pSize1,
	XMFLOAT2* pCenter2, float fRadius2);


/*
*  3D����
*/
// �o�E���e�B���O�{�b�N�X(BB3D)
/*@brief: 2DCube & 2DCube
* [in]	: pCenter1	���S
* [in]	: pSize1	�ӂ̒���
* [in]	: pCenter2	���S
* [in]	: pSize2	�ӂ̒���
*/
bool CollisionBB3D(
	XMFLOAT3* pCenter1, XMFLOAT3* pSize1,
	XMFLOAT3* pCenter2, XMFLOAT3* pSize2);

// �o�E���e�B���O�X�t�B�A(BS)
/*@brief: 3DSphere & 3DSphere
* [in]	: pCenter1	���S
* [in]	: pRadius1	���a
* [in]	: pCenter2	���S
* [in]	: pRadius2	���a
*/
bool CollisionBS(
	XMFLOAT3* pCenter1, float fRadius1,
	XMFLOAT3* pCenter2, float fRadius2);

// �o�E���f�B���O�{�b�N�X�X�t�B�A(BBS)
/*@brief: 3DCube & 3DSphere
* [in]	: pCenter1	���S
* [in]	: pSize1	�ӂ̒���
* [in]	: pCenter2	���S
* [in]	: pRadius2	���a
*/
bool CollisionBBS(
	XMFLOAT3* pCenter1, XMFLOAT3* pSize1,
	XMFLOAT3* pCenter2, float fRadius2);

// �o�E���f�B���O�V�����_�[(BCy)
/*@brief: 3DCylinder & 3DCylinder
* [in]	: pCenter1	���S
* [in]	: height1	�~���̍���
* [in]	: pRadius1	���a
* [in]	: pCenter2	���S
* [in]	: height2	�~���̍���
* [in]	: pRadius2	���a
*/
bool CollisionBCy(
	XMFLOAT3* pCenter1, float height1, float fRadius1,
	XMFLOAT3* pCenter2, float height2, float fRadius2);