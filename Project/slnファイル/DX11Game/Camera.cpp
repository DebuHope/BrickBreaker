//=============================================================================
// カメラ処理
// 制作：向出創
//=============================================================================
#include "Camera.h"
#include "Input.h"
#include "Debugproc.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM		(0.0f)										// カメラの初期位置(X座標)
#define	POS_Y_CAM		(100.0f)									// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-200.0f)									// カメラの初期位置(Z座標)
#define	VIEW_ANGLE		(50.0f)										// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)										// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(3000.0f)									// ビュー平面のFarZ値

#define CAMERA_MOVE_SPEED	(2.0f)	// 移動の速さ
#define CAMERA_ROTATE_SPEED	(1.5)	// カメラ回転量

// グローバル変数
static CCamera  g_camera;	// カメラの実体

// コンストラクタ
CCamera::CCamera()
{
	Init();
}

// 初期化
void CCamera::Init()
{
	m_vPos = XMFLOAT3(0.0f, 0.0f, -200.0f);	// 視点
	m_vTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);	// 注視点
	m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);		// 上方ベクトル

	m_fAspectRatio = VIEW_ASPECT;			// 縦横比
	m_fFovY = VIEW_ANGLE;					// 視野角(Degree)
	m_fNearZ = VIEW_NEAR_Z;					// 前方クリップ距離
	m_fFarZ = VIEW_FAR_Z;					// 後方クリップ距離

	m_vAngle = XMFLOAT3(0-.0f, 0.0f, 0.0f);	// 角度

	float fVecX, fVecZ;
	fVecX = m_vPos.x - m_vTarget.x;
	fVecZ = m_vPos.z - m_vTarget.z;
	m_fLengthInterval = sqrtf(fVecX * fVecX + fVecZ * fVecZ);
	
	CalcWorldMatrix();
}

// ビュー/プロジェクション マトリックス更新
void CCamera::Update()
{
#ifdef _DEBUG
	// Camera.h　に　CAMERA_DEBUGが定義されているとここが実行される
	// カメラ移動
	float dx = 0.0f, dy = 0.0f, dz = 0.0f;
	if (GetKeyPress(VK_I))
	{
		// 前
		dx += CAMERA_MOVE_SPEED * SinDeg(m_vAngle.y);
		dz += CAMERA_MOVE_SPEED * CosDeg(m_vAngle.y);
	}
	else if (GetKeyPress(VK_K))
	{
		// 後
		dx += CAMERA_MOVE_SPEED * SinDeg(m_vAngle.y + 180);
		dz += CAMERA_MOVE_SPEED * CosDeg(m_vAngle.y + 180);
	}
	else if (GetKeyPress(VK_J))
	{
		// 左
		dx += CAMERA_MOVE_SPEED * SinDeg(m_vAngle.y - 90);
		dz += CAMERA_MOVE_SPEED * CosDeg(m_vAngle.y - 90);
	}
	else if (GetKeyPress(VK_L))
	{
		// 右
		dx += CAMERA_MOVE_SPEED * SinDeg(m_vAngle.y + 90);
		dz += CAMERA_MOVE_SPEED * CosDeg(m_vAngle.y + 90);
	}
	else if (GetKeyPress(VK_Y))
	{
		// 上
		dy += CAMERA_MOVE_SPEED;
	}
	else if (GetKeyPress(VK_N))
	{
		// 下
		dy -= CAMERA_MOVE_SPEED;
	}
	// 座標 += 速度
	m_vPos.x += dx;
	m_vPos.y += dy;
	m_vPos.z += dz;

	// 注視点移動
	if (GetKeyPress(VK_T))
	{
		dy += CAMERA_MOVE_SPEED;
	}
	else if (GetKeyPress(VK_B))
	{
		dy -= CAMERA_MOVE_SPEED;
	}
	m_vTarget.x += dx;
	m_vTarget.y += dy;
	m_vTarget.z += dz;

	// カメラ回転
	if (GetKeyPress(VK_E))
	{
		// 右旋回				
		m_vAngle.y += CAMERA_ROTATE_SPEED;
		if (m_vAngle.y >= 360.0f) {
			m_vAngle.y -= 360.0f;
		}
		m_vPos.x = m_vTarget.x - SinDeg(m_vAngle.y) * m_fLengthInterval;
		m_vPos.z = m_vTarget.z - CosDeg(m_vAngle.y) * m_fLengthInterval;
	}
	else if (GetKeyPress(VK_Q))
	{
		// 右旋回				
		m_vAngle.y -= CAMERA_ROTATE_SPEED;
		if (m_vAngle.y <= -180.0f) {
			m_vAngle.y += 360.0f;
		}
		m_vPos.x = m_vTarget.x - SinDeg(m_vAngle.y) * m_fLengthInterval;
		m_vPos.z = m_vTarget.z - CosDeg(m_vAngle.y) * m_fLengthInterval;
	}

	// 注視点回転
	if (GetKeyPress(VK_OEM_COMMA))
	{
		m_vAngle.y -= CAMERA_ROTATE_SPEED;
		if (m_vAngle.y < -180.0f) {
			m_vAngle.y += 360.0f;
		}
		m_vTarget.x = m_vPos.x + SinDeg(m_vAngle.y) * m_fLengthInterval;
		m_vTarget.z = m_vPos.z + CosDeg(m_vAngle.y) * m_fLengthInterval;
	}
	else if (GetKeyPress(VK_OEM_PERIOD))
	{
		// 右旋回				
		m_vAngle.y += CAMERA_ROTATE_SPEED;
		if (m_vAngle.y >= 180.0f) {
			m_vAngle.y -= 360.0f;
		}
		m_vTarget.x = m_vPos.x + SinDeg(m_vAngle.y) * m_fLengthInterval;
		m_vTarget.z = m_vPos.z + CosDeg(m_vAngle.y) * m_fLengthInterval;
	}

	// リセット
	if (GetKeyTrigger(VK_R))
	{
		m_vPos = XMFLOAT3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
		m_vTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_vAngle = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	// デバック表示
	PrintDebugProc("[ｶﾒﾗ ｲﾁ : (%7.2f,%7.2f,%7.2f)]\n", m_vPos.x, m_vPos.y, m_vPos.z);
	PrintDebugProc("[ﾁｭｳｼﾃﾝ : (%7.2f,%7.2f,%7.2f)]\n", m_vTarget.x, m_vTarget.y, m_vTarget.z);
	PrintDebugProc("[ｶﾒﾗ ﾑｷ : (%7.2f)]\n", m_vAngle.y);
	PrintDebugProc("\n");

	PrintDebugProc("***ｶﾒﾗ ｿｳｻ***\n");
	PrintDebugProc("ﾏｴ   ｲﾄﾞｳ : I\n");
	PrintDebugProc("ｳｼﾛ  ｲﾄﾞｳ : K\n");
	PrintDebugProc("ﾋﾀﾞﾘ ｲﾄﾞｳ : J\n");
	PrintDebugProc("ﾐｷﾞ  ｲﾄﾞｳ : L\n");
	PrintDebugProc("ｳｴ   ｲﾄﾞｳ : Y\n");
	PrintDebugProc("ｼﾀ   ｲﾄﾞｳ : N\n");
	PrintDebugProc("ﾋﾀﾞﾘ ｾﾝｶｲ : U\n");
	PrintDebugProc("ﾐｷﾞ  ｾﾝｶｲ : O\n");
	PrintDebugProc("\n");

	PrintDebugProc("***ﾁｭｳｼﾃﾝ ｿｳｻ***\n");
	PrintDebugProc("ｳｴ   ｲﾄﾞｳ : T\n");
	PrintDebugProc("ｼﾀ   ｲﾄﾞｳ : B\n");
	PrintDebugProc("ﾋﾀﾞﾘ ｾﾝｶｲ : ,\n");
	PrintDebugProc("ﾐｷﾞ  ｾﾝｶｲ : .\n");
	PrintDebugProc("\n");

	PrintDebugProc("ﾘｾｯﾄ      : R\n");
	PrintDebugProc("\n");
#endif // _DEBUG

	// ビュー/プロジェクション マトリックス更新
	UpdateMatrix();
}


// ビュー/プロジェクション マトリックス更新
void CCamera::UpdateMatrix()
{
	XMStoreFloat4x4(&m_mtxView, XMMatrixLookAtLH(
		XMLoadFloat3(&m_vPos), XMLoadFloat3(&m_vTarget), XMLoadFloat3(&m_vUp)));
	XMStoreFloat4x4(&m_mtxProj, XMMatrixPerspectiveFovLH(
		XMConvertToRadians(m_fFovY), m_fAspectRatio, m_fNearZ, m_fFarZ));
}

// ワールド マトリックス設定
void CCamera::SetWorldMatrix(XMFLOAT4X4& mtxWorld)
{
	m_mtxWorld = mtxWorld;
	m_vPos = XMFLOAT3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
	m_vTarget = XMFLOAT3(mtxWorld._41 + mtxWorld._31, mtxWorld._42 + mtxWorld._32, mtxWorld._43 + mtxWorld._33);
	m_vUp = XMFLOAT3(mtxWorld._21, mtxWorld._22, mtxWorld._23);
}

// 視点/注視点/上方ベクトルからワールド マトリックス算出
XMFLOAT4X4& CCamera::CalcWorldMatrix()
{
	XMVECTOR vecZ = XMVectorSet(m_vTarget.x - m_vPos.x, m_vTarget.y - m_vPos.y, m_vTarget.z - m_vPos.z, 0.0f);
	XMFLOAT3 vZ;
	XMStoreFloat3(&vZ, XMVector3Normalize(vecZ));
	XMVECTOR vecY = XMLoadFloat3(&m_vUp);
	XMVECTOR vecX = XMVector3Normalize(XMVector3Cross(vecY, vecZ));
	XMFLOAT3 vX;
	XMStoreFloat3(&vX, vecX);
	vecY = XMVector3Normalize(XMVector3Cross(vecZ, vecX));
	XMFLOAT3 vY;
	XMStoreFloat3(&vY, vecY);

	m_mtxWorld._11 = vX.x;
	m_mtxWorld._12 = vX.y;
	m_mtxWorld._13 = vX.z;
	m_mtxWorld._14 = 0.0f;
	m_mtxWorld._21 = vY.x;
	m_mtxWorld._22 = vY.y;
	m_mtxWorld._23 = vY.z;
	m_mtxWorld._24 = 0.0f;
	m_mtxWorld._31 = vZ.x;
	m_mtxWorld._32 = vZ.y;
	m_mtxWorld._33 = vZ.z;
	m_mtxWorld._34 = 0.0f;
	m_mtxWorld._41 = m_vPos.x;
	m_mtxWorld._42 = m_vPos.y;
	m_mtxWorld._43 = m_vPos.z;
	m_mtxWorld._44 = 1.0f;

	return m_mtxWorld;
}

// カメラ情報
CCamera * GetCamera()
{
	return &g_camera;
}