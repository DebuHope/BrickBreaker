//=============================================================================
// ���C�����j���[����
// ����F���o�n
//=============================================================================

#include "Main.h"
#include "Select.h"
#include "Input.h"
#include "Bg.h"
#include "Street.h"
#include "Field.h"
#include "Player.h"
#include "Object.h"
#include "DEnemy.h"
#include "EF_Acceleration.h"
#include "UI.h"
#include "Transition.h"
#include "Shadow.h"
#include "Score.h"

//=============================================================================
// ����������
//=============================================================================
void InitSelect()
{
	//InitBg();
	//InitUI();
	InitStreet();
	InitField();
	InitObject();
	InitPlayer();
	InitDEnemy();
	InitScore();

	SetDrawTexNo(UI_MAINSELECT);
}

//=============================================================================
// �I������
//=============================================================================
void UninitSelect()
{
	//UninitBg();
	//UninitUI();
	UninitStreet();
	UninitField();
	UninitObject();
	UninitPlayer();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSelect()
{
	//UpdateBg();
	//UpdateUI();
	UpdateStreet();
	UpdateField();
	UpdateObject();
	UpdatePlayer();

	if (GetPlayerPos(0).z > 80000.0f)	StartChange(SCENE_SELECT, 0);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSelect()
{
	// Z�o�b�t�@����
	SetZBuffer(false);
	//DrawBg();
	// Z�o�b�t�@�L��
	SetZBuffer(true);
	//DrawStreet();
	//DrawField();
	//DrawObject();
	DrawPlayer();
	SetZWrite(false);	// �e�ݒ�ύX�e���Y���
	DrawShadow();
	SetZWrite(true);
	// Z�o�b�t�@����
	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);
	//DrawUI();
	//DrawTransition();
	SetBlendState(BS_NONE);
	// Z�o�b�t�@�L��
	SetZBuffer(true);
}