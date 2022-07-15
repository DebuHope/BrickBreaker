//=============================================================================
// �v���C���[����
// ����F���o�n
//=============================================================================
#define _USE_MATH_DEFINES
#include <math.h>
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Player.h"
#include "Shadow.h"
#include "main.h"
#include "Camera.h"
#include "input.h"
#include "UI.h"
#include "Transition.h"
#include "Life.h"
#include "Sound.h"
#include "Score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_RUN		"data/model/player/padlle_01.fbx"

#define MAX_PLAYER_MODEL	(1)

#define ROT_Y			(180.0f)
#define VALUE_MOVE		(3.0f)
#define VALUE_ROTATE	(5.0f)
#define GRAVITY			(-0.50f)

#define LIMIT_LEFT	-98
#define LIMIT_RIGHT	98

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct _tPlayer
{
	XMFLOAT4X4	mtxWorld;

	XMFLOAT3 pos;	// ���W
	XMFLOAT3 rot;	// ��]
	float	angle;	// ��]�ړ��p
	XMFLOAT3 scl;	// �g�嗦
	XMFLOAT3 vel;	// ���x
	XMFLOAT2 velXZ;	// �O�ړ��p���x

	int		nPhase;	// �s���p�^�[���̒i�K
	int		nState;	// �s��(0�ȉ�:���g�p 1�ȏ�:�ʏ�)
	int		nShadowIdx;	// �e�̔ԍ�
}tPlayer;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAssimpModel	g_model[MAX_PLAYER_MODEL];	// ���f���f�[�^
static tPlayer		g_player[MAX_PLAYER];	// �v���C���[��
static int AnimCount;
static int DashCount;
static int SlideCount;
static int JumpCount;
static int JoyZCount;
static int InvincibleCount;
static int StartInvincibleCount;
static bool DownFlag;
static bool JoyTriggerFalg;

HRESULT LoadPlayer(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// ���f���f�[�^�̓ǂݍ���
	hr = g_model[0].Load(pDevice, pDeviceContext,
		MODEL_RUN);

	return hr;
}

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_player[i].pos = XMFLOAT3(0.0f, -75.0f, 0.0f);
		g_player[i].rot = XMFLOAT3(0.0f, ROT_Y, 0.0f);
		g_player[i].scl = XMFLOAT3(15.0f, 1.0f, 1.0f);
		g_player[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_player[i].velXZ = XMFLOAT2(0.0f, 0.0f);
		g_player[i].nPhase = 0;
		g_player[i].nState = 1;	// �v���C���[�����͐���
		g_player[i].angle = 0.0f;


		if(GetSceneNo() == SCENE_ENDING)	g_player[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	AnimCount = 0;
	DashCount = 120;
	SlideCount = 40;
	JumpCount = 40;
	JoyZCount = 0;
	InvincibleCount = 0;
	StartInvincibleCount = 0;
	DownFlag = false;
	JoyTriggerFalg = false;

	// ���[���h�}�g���b�N�X�̏�����
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		XMStoreFloat4x4(&g_player[i].mtxWorld, mtxWorld);
	}

	//// �e�̍쐬
	//for (int i = 0; i < MAX_PLAYER; i++) {
	//	g_player[i].nShadowIdx = CreateShadow(g_player[i].pos, 20.0f);
	//}
}


//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	// �e�̉��
	for (int i = 0; i < MAX_PLAYER; i++) {
		ReleaseShadow(g_player[i].nShadowIdx);
	}
	// ���f���̉��
	//for (int i = 0; i < MAX_PLAYER_MODEL; i++) {
	//	g_model[i].Release();
	//}
	StopSound(SOUND_LABEL_SE_RUN);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (g_player[i].nState == 0)	continue;
	
		// ���E�ړ�
		if (GetKeyPress(VK_A))
		{
			g_player[i].vel.x = -VALUE_MOVE;
		}
		else if (GetKeyPress(VK_D))
		{
			g_player[i].vel.x = VALUE_MOVE;
		}

#pragma region circular motion
		//float radius = g_player[i].angle * M_PI / 180.0f;

		//float add_x = cosf(radius) * g_player[i].scl.x;
		//float add_y = sinf(radius) * g_player[i].scl.y;

		//if (GetKeyPress(VK_D))
		//{
		//	g_player[i].angle -= 5.0f;
		//	g_player[i].pos.x = g_player[i].pos.x + add_x;
		//	g_player[i].pos.y = g_player[i].pos.y + add_y;
		//}
		//else if (GetKeyPress(VK_A))
		//{
		//	g_player[i].angle += 5.0f;
		//	g_player[i].pos.x = g_player[i].pos.x - add_x;
		//	g_player[i].pos.y = g_player[i].pos.y - add_y;
		//}
#pragma endregion

		// �d�͂����W�ɉ��Z
		//g_player[i].vel.y += GRAVITY;

		// ���x�����W�ɉ��Z
		g_player[i].pos.x += g_player[i].vel.x;
		g_player[i].pos.y += g_player[i].vel.y;

		// ������(�L�[�������Ă��Ȃ���)
		g_player[i].vel.x = 0.0f;
		g_player[i].vel.z = 0.0f;

		// ��ʊO����
		if (g_player[i].pos.x > 98.0f)
		{
			g_player[i].pos.x = 98.0f;
		}
		else if (g_player[i].pos.x < -98.0f)
		{
			g_player[i].pos.x = -98.0f;
		}

		//================================================================
		XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(
			g_player[i].scl.x,
			g_player[i].scl.y,
			g_player[i].scl.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_player[i].rot.x),
			XMConvertToRadians(g_player[i].rot.y),
			XMConvertToRadians(g_player[i].rot.z)
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(
			g_player[i].pos.x,
			g_player[i].pos.y,
			g_player[i].pos.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�ݒ�
		XMStoreFloat4x4(&g_player[i].mtxWorld, mtxWorld);

		// �e�̈ړ�
		MoveShadow(g_player[i].nShadowIdx, g_player[i].pos);
	}

	AnimCount++;
	DashCount++;
	SlideCount++;
	JumpCount++;
	StartInvincibleCount++;

	// �p�b�hZ���t���O
	if (GetJoyCountSimple() == 1 && (GetJoyZ(0) < -20000)) {
		JoyZCount++;
	}
	else if (GetJoyCountSimple() == 1 && (GetJoyZ(0) > 20000)) {
		JoyZCount--;
	}
	else {
		JoyZCount = 0;
	}

	if(DownFlag) InvincibleCount++;
	if (InvincibleCount > 150) DownFlag = false;

#ifdef _DEBUG
	PrintDebugProc("PlayerPos X : %0.1f Y : %0.1f\n\n", GetPlayerPos(0).x, GetPlayerPos(0).y);
#endif // _DEBUG
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	g_model[0].Draw(pDeviceContext, g_player[0].mtxWorld);
}

XMFLOAT4X4 GetPlayerWorld(int no)
{
	return g_player[no].mtxWorld;
}

// ���S���W����
XMFLOAT3 GetPlayerCenter(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMFLOAT3 pos = g_model[0].GetCenter();
	pos.x += g_player[no].pos.x;
	pos.y += g_player[no].pos.y;
	pos.z += g_player[no].pos.z;
	return pos;
}

// ���f���T�C�Y����
XMFLOAT3 GetPlayerBBox(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// ���f������T�C�Y����������
	return g_model[0].GetBBox();
}

// ���W����
XMFLOAT3 GetPlayerPos(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_player[no].pos;
}

// �T�C�Y����
XMFLOAT3 GetPlayerSize(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_player[no].scl;
}

// �������Ă��邩
bool IsPlayer(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return false;
	}
	return true;
}

// �\�����Ȃ�
void DestroyPlayer(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return;
	}
	g_player[no].nState = 0;
	ReleaseShadow(g_player[no].nShadowIdx);
	g_player[no].nShadowIdx = -1;
}

// ���x����
XMFLOAT3 GetPlayerVel(int no)
{
	if (no < 0 || no >= MAX_PLAYER) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_player[no].vel;
}