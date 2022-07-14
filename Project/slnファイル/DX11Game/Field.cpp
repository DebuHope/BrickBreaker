//======================================================================================
// 地面処理
// 制作：向出創
//======================================================================================
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Field.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_FIELD1	L"data/texture/asphalt01.png"	// テクスチャ
#define TEXTURE_FIELD2	L"data/texture/grass02.png"	// テクスチャ
#define TEXTURE_FIELD3	L"data/texture/asphalt02.png"	// テクスチャ

#define MAX_FIELD_TEXTURE	(3)

#define M_DIFFUSE		XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define M_SPECULAR		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)
#define M_AMBIENT		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_EMISSIVE		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)

#define SIZE_X			(2000.0f)		// 地面のサイズ
#define SIZE_Y			(0.0f)
#define SIZE_Z			(1000.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct _tField {
	XMFLOAT3 pos;	// 位置
	XMFLOAT3 rot;	// 回転
	XMFLOAT3 scl;	// 拡大

	int nState;		// 状態(0以下:未使用 1以上:通常)
}tField;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexField(ID3D11Device* pDevice, int i);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static MESH			g_mesh[MAX_FIELD_TEXTURE];		// メッシュ情報（オブジェクトの表面）
static MATERIAL		g_material;	// マテリアル情報

static tField g_field[MAX_FIELD];	// フィールド数
static int DrawStreetNo;

HRESULT LoadField(void)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = S_OK;

	// マテリアルの初期設定
	g_material.Diffuse = M_DIFFUSE;
	g_material.Ambient = M_AMBIENT;
	g_material.Specular = M_SPECULAR;
	g_material.Power = 1.0f;
	g_material.Emissive = M_EMISSIVE;

	for (int i = 0; i < MAX_FIELD_TEXTURE; i++) {
		g_mesh[i].pMaterial = &g_material;
	}

	// テクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, TEXTURE_FIELD1, &g_mesh[0].pTexture);
	if (FAILED(hr))	return hr;
	hr = CreateTextureFromFile(pDevice, TEXTURE_FIELD2, &g_mesh[1].pTexture);
	if (FAILED(hr))	return hr;
	hr = CreateTextureFromFile(pDevice, TEXTURE_FIELD3, &g_mesh[2].pTexture);
	if (FAILED(hr))	return hr;

	// ワールドマトリクス初期化
	for (int i = 0; i < MAX_FIELD_TEXTURE; i++) {
		XMStoreFloat4x4(&g_mesh[i].mtxTexture, XMMatrixIdentity());
		XMStoreFloat4x4(&g_mesh[i].mtxWorld, XMMatrixIdentity());
	}

	// 頂点情報の作成
	for (int i = 0; i < MAX_FIELD_TEXTURE; i++) {
		hr = MakeVertexField(pDevice, i);
	}

	return hr;
}

//=============================================================================
// 初期化処理
//=============================================================================
void InitField(void)
{
	// 変数の初期化
	for (int i = 0; i < MAX_FIELD; i++) {
		g_field[i].nState = 1;
		g_field[i].pos = XMFLOAT3(0.0f, -0.1f, 0.0f);
		g_field[i].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_field[i].scl = XMFLOAT3(1.0f, 1.0f, 1.0f);
	}
	DrawStreetNo = 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	// メッシュ解放
	//ReleaseMesh(&g_mesh);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateField(void)
{
	for (int i = 0; i < MAX_FIELD; i++) {
		if (g_field[i].nState == 0) {
			continue;
		}
		// 移動など更新処理をこの下に記述
		// ====================================================================
		for (int i = 0; i < MAX_FIELD; i++) {	// 10 = 485
			g_field[i].pos.z = 2000.0f * i;
		}

		if (GetUIState() == 0) DrawStreetNo = 0;
		else if (GetUIState() == 1) DrawStreetNo = 1;
		else if (GetUIState() == 2) DrawStreetNo = 2;
		// ====================================================================
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// 半透明を合成する
	SetBlendState(BS_ALPHABLEND);

	for (int i = 0; i < MAX_FIELD; i++) {
		if (g_field[i].nState == 0) {
			continue;
		}

		for (int j = 0; j < MAX_FIELD_TEXTURE; j++) {
			g_mesh[j].scl = g_field[i].scl;
			g_mesh[j].pos = g_field[i].pos;
			g_mesh[j].rot = g_field[i].rot;

			// メッシュ更新
			UpdateMesh(&g_mesh[j]);
		}
		// メッシュの描画
		DrawMesh(pDeviceContext, &g_mesh[DrawStreetNo]);
	}
	// 半透明元を戻す
	SetBlendState(BS_NONE);
}

HRESULT MakeVertexField(ID3D11Device* pDevice, int i)
{
	VERTEX_3D vertexWk[NUM_VERTEX]; //作業用頂点情報
	int		  indexWk[NUM_VERTEX];	//作業用インデックス

	// 頂点座標の設定
	g_mesh[i].nNumVertex = NUM_VERTEX;
	vertexWk[0].vtx	= XMFLOAT3(-SIZE_X, 0.0f,  SIZE_Z);
	vertexWk[1].vtx	= XMFLOAT3( SIZE_X, 0.0f,  SIZE_Z);
	vertexWk[2].vtx	= XMFLOAT3(-SIZE_X, 0.0f, -SIZE_Z);
	vertexWk[3].vtx	= XMFLOAT3( SIZE_X, 0.0f, -SIZE_Z);
	
	// ディフューズの設定								alpha値
	vertexWk[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// 法線ベクトルの設定
	vertexWk[0].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[1].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[2].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[3].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// テクスチャ座標の設定
	vertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	vertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
	vertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
	vertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);

	// インデックス配列の設定
	g_mesh[i].nNumIndex = NUM_VERTEX;
	indexWk[0] = 0;
	indexWk[1] = 1;
	indexWk[2] = 2;
	indexWk[3] = 3;

	return MakeMeshVertex(pDevice, &g_mesh[i], vertexWk, indexWk);
}

// 座標所得
XMFLOAT3 GetFieldPos(int no)
{
	if (no < 0 || no >= MAX_FIELD) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_field[no].pos;
}

// サイズ所得
XMFLOAT3 GetFieldSize(int no)
{
	if (no < 0 || no >= MAX_FIELD) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return XMFLOAT3(SIZE_X, SIZE_Y, SIZE_Z);
}

// 地面があるか
bool IsField(int no)
{
	if (no < 0 || no >= MAX_FIELD) {
		return false;
	}
	return true;
}