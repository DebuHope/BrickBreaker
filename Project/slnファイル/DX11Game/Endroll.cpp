//======================================================================================
// �G���h���[������
// ����F���o�n
//======================================================================================
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Endroll.h"
#include "main.h"
#include "Player.h"
#include "Shadow.h"
#include "Input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CREDIT01	"data/model/text/ball_01.fbx"

#define MAX_TEXT_MODEL		(1)

#define TEXT_SPEED		(1.0f)

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
	int nShadowIdx;
	bool	KillFlag;	// �L���t���O
	int		nState;	// �s��(0�ȉ�:���g�p 1�ȏ�:�ʏ�)
}tText;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAssimpModel	g_model[MAX_TEXT_MODEL];	// ���f���f�[�^
static tText			g_text[MAX_TEXT];

float speed = 2.0f;
float angleX = 0.0f;
float angleY = 0.0f;

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
		g_text[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_text[i].rot = XMFLOAT3(0.0f, 180.0f, 0.0f);
		g_text[i].scl = XMFLOAT3(5.0f, 5.0f, 5.0f);
		g_text[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_text[i].nState = 1;
		g_text[i].KillFlag = false;
	}

	// ���[���h�}�g���b�N�X�̏�����
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_TEXT; i++)
	{
		XMStoreFloat4x4(&g_text[i].mtxWorld, mtxWorld);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitText(void)
{
	// �e�̉��
	for (int i = 0; i < MAX_TEXT; i++) {
		ReleaseShadow(g_text[i].nShadowIdx);
	}
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
		if (g_text[i].nState == 0)	continue;

		if (GetKeyPress(VK_Z))
		{
			angleX -= 10.0f;
		}
		else if (GetKeyPress(VK_X))
		{
			angleX += 10.0f;
		}

		if (GetKeyPress(VK_C))
		{
			angleY -= 10.0f;
		}
		else if (GetKeyPress(VK_V))
		{
			angleY += 10.0f;
		}

		//				  ���_    ���x       �p�x
		g_text[i].vel.x = 0.0f + speed * cosf(angleX * (M_PI / 180.0f));
		g_text[i].vel.y = 0.0f + speed * sinf(angleY * (M_PI / 180.0f));

		// �L���t���O���������ꍇ
		if (g_text[i].KillFlag == true) {
			angleY += 180;
			g_text[i].KillFlag = false;
		}

		// �ʒu�̍X�V
		g_text[i].pos.x += g_text[i].vel.x;
		g_text[i].pos.y += g_text[i].vel.y;
		g_text[i].pos.z += g_text[i].vel.z;

		// ��ʊO����
		if (g_text[i].pos.x > 98.0f || g_text[i].pos.x < -98.0f)
		{	// ���E
			angleX += 180.0f;
			angleX = (int)angleX % 360;
		}
		else if (g_text[i].pos.y > 98.0f || g_text[i].pos.y < -98.0f)
		{	// �㉺
			angleY += 180.0f;
			angleY = (int)angleY % 360;
		}

		// �e������
		if (g_text[i].pos.y <= 0.0f) {
			ReleaseShadow(g_text[i].nShadowIdx);
			g_text[i].nShadowIdx = -1;
		}

		// ���[���h�}�g���b�N�X�̏�����
		XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(
			g_text[i].scl.x,
			g_text[i].scl.y,
			g_text[i].scl.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_text[i].rot.x),
			XMConvertToRadians(g_text[i].rot.y),
			XMConvertToRadians(g_text[i].rot.z)
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(
			g_text[i].pos.x,
			g_text[i].pos.y,
			g_text[i].pos.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�ݒ�
		XMStoreFloat4x4(&g_text[i].mtxWorld, mtxWorld);

		// �e�̈ړ�
		MoveShadow(g_text[i].nShadowIdx, g_text[i].pos);

#ifdef _DEBUG

		PrintDebugProc("BallAngle X : %0.1f Y : %0.1f\n\n\n", angleX, angleY);
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
		if (g_text[i].pos.z > GetPlayerPos(0).z - 5000.0f) {
			ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

			// ���f���\��
			if (g_text[i].nState == 0)	continue;
			g_model[g_text[i].nType].Draw(pDeviceContext, g_text[i].mtxWorld);
		}
	}
}

// �ݒu
int SetText(XMFLOAT3 pos, XMFLOAT3 scl, XMFLOAT3 dir, int type)
{
	_tText* pText = g_text;
	for (int i = 0; i < MAX_TEXT; ++i, ++pText)
	{	// �o�����Ă���ꍇ�X���[
		if (pText->nState != 0) continue;

		pText->pos = pos;
		pText->scl = scl;
		pText->scl.z = scl.z = 8.0f;
		pText->vel.x = dir.x * TEXT_SPEED;
		pText->vel.y = dir.y * TEXT_SPEED;
		pText->vel.z = dir.z * TEXT_SPEED;
		pText->nState = 1;	// �o��
		pText->nType = type;

		// �e�̍쐬
		pText->nShadowIdx = CreateShadow(pText->pos, 20.0f);

		return i;	// �ԍ���Ԃ�
	}
	return -1;	// ������Ȃ�����
}

XMFLOAT4X4 GetTextWorld(int no)
{
	return g_text[no].mtxWorld;
}

// ���S���W����
XMFLOAT3 GetTextCenter(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMFLOAT3 pos = g_model[g_text[no].nType].GetCenter();
	pos.x += g_text[no].pos.x;
	pos.y += g_text[no].pos.y;
	pos.z += g_text[no].pos.z;
	return pos;
}

// ���f���T�C�Y����
XMFLOAT3 GetTextBBox(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// ���f������T�C�Y����������
	return g_model[g_text[no].nType].GetBBox();
}

// ���W����
XMFLOAT3 GetTextPos(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_text[no].pos;
}

// �T�C�Y����
XMFLOAT3 GetTextSize(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return XMFLOAT3(g_text[no].scl.x, g_text[no].scl.y, g_text[no].scl.z);
}

// �������Ă��邩
bool IsText(int no)
{
	if (no < 0 || no >= MAX_TEXT || g_text[no].KillFlag == true) {
		return false;
	}
	return true;
}

// �\�����Ȃ�
void DestroyText(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return;
	}
	g_text[no].nState = 0;
	ReleaseShadow(g_text[no].nShadowIdx);
	g_text[no].pos = XMFLOAT3(0.0f, -1000.0f, 0.0f);
}

void KillText(int no)
{
	if (no < 0 || no >= MAX_TEXT) {
		return;
	}

	g_text[no].KillFlag = true;
}
