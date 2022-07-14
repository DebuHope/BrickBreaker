//=============================================================================
// ���C���Q�[������
// ����F���o�n
//=============================================================================
#include <time.h>
#include "Main.h"
#include "Game.h"
#include "Input.h"
#include "Bg.h"
#include "Street.h"
#include "Field.h"
#include "Player.h"
#include "Object.h"
#include "DEnemy.h"
#include "EF_Acceleration.h"
#include "Transition.h"
#include "Shadow.h"
#include "Life.h"
#include "UI.h"
#include "Score.h"
#include "Item.h"
#include "Stage.h"
#include "EF_Maneger.h"
#include "Sound.h"
#include "Combo.h"
#include "Gauge.h"
#include "Endroll.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	state;	// tips���
static bool	stateFlag;

//=============================================================================
// ����������
//=============================================================================
void InitGame()
{
	// �����G�t�F�N�g
	InitAcceleration();
	// Effekseer�G�t�F�N�g������
	InitEFManeger();
	// �w�i
	InitBg();
	// ���C�t
	InitLife();
	// ���H
	InitStreet();
	// �t�B�[���h
	InitField();
	// �v���C���[
	InitPlayer();
	// �n��G
	InitDEnemy();
	// �󒆓G
	// �I�u�W�F�N�g
	InitObject();
	// �G���h���[��
	InitText();
	// �X�R�A
	InitScore();
	// �A�C�e��
	InitItem();
	// UI
	InitUI();
	// �R���{
	InitCombo();
	AddCountCombo(-999);

	state = 0;
	stateFlag = false;

	SetDrawTexNo(UI_UE_UI);

	SetStage();
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame()
{
	// �����G�t�F�N�g
	UninitAcceleration();
	// �w�i
	UninitBg();
	// ���C�t
	UninitLife();
	// ���H
	UninitStreet();
	// �t�B�[���h
	UninitField();
	// �v���C���[
	UninitPlayer();
	// �I�u�W�F�N�g
	UninitObject();
	// �G���h���[��
	UninitText();
	// �X�R�A
	UninitScore();
	// �A�C�e��
	UninitItem();
	// UI
	UninitUI();
	// �R���{
	UninitCombo();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame()
{
	if (state == 0) {
		// �����G�t�F�N�g
		UpdateAcceleration();
		// Effekseer�G�t�F�N�g
		UpdateEFManeger();
		// �w�i
		UpdateBg();
		// ���C�t
		UpdateLife();
		// ���H
		UpdateStreet();
		// �t�B�[���h
		UpdateField();
		// �v���C���[
		UpdatePlayer();
		// �G�l�~�[
		UpdateDEnemy();
		// �I�u�W�F�N�g
		UpdateObject();
		// �G���h���[��
		UpdateText();
		// �X�R�A
		UpdateScore();
		// �A�C�e��
		UpdateItem();
		// �R���{
		UpdateCombo();
	}
	// UI
	UpdateUI();


	// �|�[�Y�؂�ւ�
	if (GetKeyTrigger(VK_ESCAPE) || GetJoyCountSimple() == 1 && GetJoyTrigger(0, JOYBUTTON8)){
		if (state == 0) state = 1;
		StopSound(SOUND_LABEL_SE_RUN);
	}

	// tips�\��
	if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 800.0f && GetPlayerPos(0).z <= 850.0f && stateFlag == false) {
		if (state == 0) state = 2;
		stateFlag = true;
		StopSound(SOUND_LABEL_SE_RUN);
	}
	else if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 9000.0f && GetPlayerPos(0).z <= 9550.0f && stateFlag == false) {
		if (state == 0) state = 3;
		stateFlag = true;
		StopSound(SOUND_LABEL_SE_RUN);
	}
	else if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 18000.0f && GetPlayerPos(0).z <= 18050.0f && stateFlag == false) {
		if (state == 0) state = 4;
		stateFlag = true;
		StopSound(SOUND_LABEL_SE_RUN);
	}

	// tips�t���O���
	if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 860.0f && GetPlayerPos(0).z <= 900.0f) {
		stateFlag = false;
	}
	else if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 9560.0f && GetPlayerPos(0).z <= 9600.0f) {
		stateFlag = false;
	}
	else if (GetSceneNo() == SCENE_STAGE1_1 && GetPlayerPos(0).z >= 18600.0f && GetPlayerPos(0).z <= 18700.0f) {
		stateFlag = false;
	}


	if (GetSceneNo() == SCENE_ENDING && GetPlayerPos(0).z >= 19000.0f) {
		StartChange(SCENE_SELECT, 2);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame()
{
	// Z�o�b�t�@����
	SetZBuffer(false);
	// �w�i
	DrawBg();
	// Z�o�b�t�@�L��
	SetZBuffer(true);
	// �t�B�[���h
	DrawField();
	// ���H
	DrawStreet();
	// �v���C���[
	DrawPlayer();
	// �G�l�~�[
	DrawDEnemy();
	// �I�u�W�F�N�g
	DrawObject();
	// �G���h���[��
	DrawTex();
	// �A�C�e��
	DrawItem();
	// Effekseer�G�t�F�N�g
	DrawEFManeger();

	SetZWrite(false);	// �e�ݒ�ύX�e���Y���
	DrawShadow();
	SetZWrite(true);
	// Z�o�b�t�@�L��
	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);
	if (GetSceneNo() != SCENE_ENDING) {
		// �����G�t�F�N�g
		DrawAcceleration();
		if (state == 1 || state != 2) {	// �|�[�Y��
			DrawCombo();
			DrawLife();
		}
		if (GetPlayerDashCount() <= 1.0f)	DrawGaugeX(XMFLOAT2(-75.0f, -200.0f), XMFLOAT2(150.0f, 15.0f), GetPlayerDashCount(), 0);
		if (GetPlayerJumpCount() <= 1.0f)	DrawGaugeY1(XMFLOAT2(-150.0f, -130.0f), XMFLOAT2(15.0f, 150.0f), GetPlayerJumpCount(), 1);
		if (GetPlayerSlide() <= 1.0f)	DrawGaugeY2(XMFLOAT2(150.0f, -130.0f), XMFLOAT2(15.0f, 150.0f), GetPlayerSlide(), 2);
	}
	DrawUI();
	if (GetSceneNo() != SCENE_ENDING) {
		if (state == 2) {	// tips��
			DrawCombo();
			DrawLife();
		}
		DrawScore();
	}
	DrawTransition();
	SetBlendState(BS_NONE);
	// Z�o�b�t�@�L��
	SetZBuffer(true);
}

int GetState()
{
	return state;
}

void SetState(int no)
{
	state = no;
}