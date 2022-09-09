//======================================================================================
// �G���h���[������
// ����F���o�n
//======================================================================================
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Endroll.h"
#include "main.h"
#include "Player.h"
#include "Input.h"
#include "Collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CREDIT01	"data/model/text/ball_01.fbx"

#define MAX_TEXT_MODEL		(1)

#define TEXT_SPEED		(2.0f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct _tText
{
	XMFLOAT4X4	mtxWorld;

	int	nType;	// ���
	XMFLOAT3 pos;	// ���W
	XMFLOAT3 rot;	// ��]
	XMFLOAT3 scl;	// �g�嗦
	XMFLOAT3 vel;	// ���x
	XMFLOAT3 last;	// ���O�̍��W
	int	invincibleTime;
	int nShadowIdx;
	bool	KillFlag;	// �L���t���O
	int		nState;	// �s��(0�ȉ�:���g�p 1�ȏ�:�ʏ�)
}tText;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAssimpModel	g_model[MAX_TEXT_MODEL];	// ���f���f�[�^
static tText			g_ball[MAX_TEXT];

static float speed = 1.4f;
static float angleX = 270.0f;
static float angleY = 50.0f;
static int a = 0;

HRESULT LoadText(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// ���f���f�[�^�̓ǂݍ���
	hr = g_model[0].Load(pDevice, pDeviceContext, CREDIT01);

	return hr;
}

//=============================================================================
// ����������
//=============================================================================
void InitText(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < MAX_TEXT; i++)
	{
		g_ball[i].pos = XMFLOAT3(0.0f, 30.0f, 0.0f);
		g_ball[i].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_ball[i].scl = XMFLOAT3(3.0f, 3.0f, 3.0f);
		g_ball[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_ball[i].nState = 1;
		g_ball[i].KillFlag = false;
		g_ball[i].invincibleTime = 0;
	}

	// ���[���h�}�g���b�N�X�̏�����
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_TEXT; i++)
	{
		XMStoreFloat4x4(&g_ball[i].mtxWorld, mtxWorld);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitText(void)
{
	// ���f���̉��
	//for (int i = 0; i < MAX_TEXT_MODEL; i++) {
	//	g_model[i].Release();
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateText(void)
{
	for (int i = 0; i < MAX_TEXT; i++)
	{
		if (g_ball[i].KillFlag) continue;
		if (g_ball[i].nState == 0)	continue;

		g_ball[i].invincibleTime++;

		if (GetKeyPress(VK_X))
		{
			angleX += 10.0f;
		}

		else if (GetKeyPress(VK_V))
		{
			angleY += 10.0f;
		}

		// ���O�̈ʒu��ۑ�(�u���b�N�Ƃ̔���p) 
		g_ball[i].last.x = g_ball[i].pos.x;
		g_ball[i].last.y = g_ball[i].pos.y;
		g_ball[i].last.z = g_ball[i].pos.z;

		//				  ���_    ���x       �p�x
		g_ball[i].vel.x = (float)(0.0f + speed * cosf(angleX * (M_PI / 180.0f)));
		g_ball[i].vel.y = (float)(0.0f + speed * sinf(angleY * (M_PI / 180.0f)));

		// �{�[�����p�h���ɓ���������
		if (g_ball[i].pos.y < GetPlayerPos(0).y + 4.5f && g_ball[i].pos.y > GetPlayerPos(0).y - 2.0f &&
			g_ball[i].pos.x <= GetPlayerPos(0).x + 18.0f && g_ball[i].pos.x >= GetPlayerPos(0).x &&
			g_ball[i].invincibleTime > 20)
		{
			g_ball[i].pos.y = -71.0f;
			angleY += 180;
			if (angleX < 270.0f && angleX > 90.0f)
			{
				angleX = 270 + rand() % 180;
			}
			g_ball[i].invincibleTime = 0;
			a = 1;
		}
		else if (g_ball[i].pos.y < GetPlayerPos(0).y + 4.5f && g_ball[i].pos.y > GetPlayerPos(0).y - 2.0f &&
			g_ball[i].pos.x <= GetPlayerPos(0).x && g_ball[i].pos.x >= GetPlayerPos(0).x - 18.0f &&
			g_ball[i].invincibleTime > 20)
		{
			g_ball[i].pos.y = -71.0f;
			angleY += 180;
			if (angleX < 90.0f || angleX > 270.0f)
			{
				angleX = 90 + rand() % 180;
			}
			g_ball[i].invincibleTime = 0;
			a = 2;
		}


		// �ʒu�̍X�V
		g_ball[i].pos.x += g_ball[i].vel.x;
		g_ball[i].pos.y += g_ball[i].vel.y;
		g_ball[i].pos.z += g_ball[i].vel.z;

		// ��ʊO����
		if (g_ball[i].pos.x > 120.5f || g_ball[i].pos.x < -120.5f)
		{	// ���E
			angleX += 180.0f;
		}
		else if (g_ball[i].pos.y > 90.0f)
		{	// �㉺
			angleY += 180.0f;
		}
		else if (g_ball[i].pos.y < -98.0f)
			g_ball[i].KillFlag = true;

		// angle ���K��
		if (angleX < 0.0f)
		{
			angleX *= -1.0f;
		}
		if (angleY < 0.0f)
		{
			angleY *= -1.0f;
		}
		angleX = (int)angleX % 360;
		angleY = (int)angleY % 360;

		// �e������
		if (g_ball[i].pos.y <= 0.0f) {
			g_ball[i].nShadowIdx = -1;
		}

		// ���[���h�}�g���b�N�X�̏�����
		XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(
			g_ball[i].scl.x,
			g_ball[i].scl.y,
			g_ball[i].scl.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_ball[i].rot.x),
			XMConvertToRadians(g_ball[i].rot.y),
			XMConvertToRadians(g_ball[i].rot.z)
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(
			g_ball[i].pos.x,
			g_ball[i].pos.y,
			g_ball[i].pos.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�ݒ�
		XMStoreFloat4x4(&g_ball[i].mtxWorld, mtxWorld);

#ifdef _DEBUG

		PrintDebugProc("BallAngle X : %0.1f Y : %0.1f\n\n\n", angleX, angleY);
		PrintDebugProc("%d\n\n\n", a);
#endif // _DEBUG
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTex(void)
{
	for (int i = 0; i < MAX_TEXT; i++)
	{
		if (g_ball[i].pos.z > GetPlayerPos(0).z - 5000.0f) {
			ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

			// ���f���\��
			if (g_ball[i].nState == 0)	continue;
			g_model[g_ball[i].nType].Draw(pDeviceContext, g_ball[i].mtxWorld);
		}
	}
}

// �ݒu
int SetText(XMFLOAT3 pos, XMFLOAT3 scl, XMFLOAT3 dir, int type)
{
	_tText* pText = g_ball;
	for (int i = 0; i < MAX_TEXT; ++i, ++pText)
	{	// �o�����Ă���ꍇ�X���[
		if (pText->nState != 0) continue;

		pText->pos = pos;
		pText->scl = scl;
		pText->nState = 1;	// �o��
		pText->nType = type;

		return i;	// �ԍ���Ԃ�
	}
	return -1;	// ������Ȃ�����
}

XMFLOAT4X4 GetTextWorld(int no)
{
	return g_ball[no].mtxWorld;
}

// ���S���W����
XMFLOAT3 GetTextCenter(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMFLOAT3 pos = g_model[g_ball[no].nType].GetCenter();
	pos.x += g_ball[no].pos.x;
	pos.y += g_ball[no].pos.y;
	pos.z += g_ball[no].pos.z;
	return pos;
}

// ���f���T�C�Y����
XMFLOAT3 GetTextBBox(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// ���f������T�C�Y����������
	return g_model[g_ball[no].nType].GetBBox();
}

// ���W����
XMFLOAT3 GetTextPos(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_ball[no].pos;
}

// �T�C�Y����
XMFLOAT3 GetTextSize(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return XMFLOAT3(g_ball[no].scl.x, g_ball[no].scl.y, g_ball[no].scl.z);
}

// �������Ă��邩
bool IsText(int no)
{
	if (no >= 0 || no >= MAX_TEXT) {
		return g_ball[no].KillFlag;
	}

}

// �\�����Ȃ�
void DestroyText(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return;
	}
	g_ball[no].nState = 0;
	g_ball[no].pos = XMFLOAT3(0.0f, -1000.0f, 0.0f);
}

void PadlleBall(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return;
	}

}

void SetAngleX(float _angleX)
{
	angleX += _angleX;
}

void SetAngleY(float _angleY)
{
	angleY += _angleY;
}

float GetBallAngleX(int no)
{
	return angleX;
}

float GetBallAngleY(int no)
{
	return angleY;
}

void CheckBallHitDirection(XMFLOAT3 * BCenter, XMFLOAT3 * BSize)
{
	// �ǂ̕�������ڐG�����̂��`�F�b�N
	for (int i = 0; i < MAX_TEXT; i++) {
		// �u���b�N�̕��͈̔͂ɂ��� : y�̂ݔ��]
		if ((BCenter->x - BSize->x / 2) <= g_ball[i].last.x + 3.0f &&
			(BCenter->x + BSize->x / 2) >= g_ball[i].last.x - 3.0f) {
			SetAngleY(180.0f);
			//g_ball[i].vel.y = -g_ball[i].vel.y;
		}
		// �u���b�N�̍����͈̔͂ɂ��� : x�̂ݔ��]
		if ((BCenter->y - BSize->y / 2) <= g_ball[i].last.y + 3.0f &&
			(BCenter->y + BSize->y / 2) >= g_ball[i].last.y - 3.0f) {
			SetAngleX(180.0f);
			//g_ball[i].vel.x = -g_ball[i].vel.x;
		}
		// �u���b�N�̉��s�͈̔͂ɂ���
		// ����`

		// ����ȊO�ɓ�����(�p�ɓ�����) : xy���]
		//SetAngleX(180.0f);
		//SetAngleY(180.0f);
		//g_ball[i].vel.x = -g_ball[i].vel.x;
		//g_ball[i].vel.y = -g_ball[i].vel.y;
	}
}
