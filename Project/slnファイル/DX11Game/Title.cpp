//=============================================================================
// �^�C�g������
// ����F���o�n
//=============================================================================

#include "Main.h"
#include "Title.h"
#include "Input.h"
#include "Bg.h"
#include "Player.h"
#include "Transition.h"

#include "Polygon.h"
#include "Texture.h"


//=============================================================================
// ����������
//=============================================================================
void InitTitle()
{
	InitPlayer();
	InitBg();
	InitTransition();

}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle()
{
	UninitPlayer();
	UninitBg();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle()
{
	UpdatePlayer();
	UpdateBg();
	// �L�[	�P�`�Q�T�U�@�@�@�@�@�p�b�h�@�O�`�R�P
	for (int i = 1; i < 256; i++) {		
		if (GetKeyRelease(i)) {
			StartChange(SCENE_SELECT, 0);
		}
	}

	for (int i = 0; i < 31; i++) {
		if (GetJoyCountSimple() == 1 && GetJoyRelease(0, i)) {
			StartChange(SCENE_SELECT, 0);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle()
{
	// Z�o�b�t�@����
	SetZBuffer(false);
	DrawBg();
	// Z�o�b�t�@�L��
	SetZBuffer(true);

	//// �e�`��
	//SetZWrite(false);	// �e�ݒ�ύX�e���Y���
	//DrawShadow();
	//SetZWrite(true);

	// Z�o�b�t�@����
	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);
	DrawTransition();
	SetBlendState(BS_NONE);
	// Z�o�b�t�@�L��
	SetZBuffer(true);
}