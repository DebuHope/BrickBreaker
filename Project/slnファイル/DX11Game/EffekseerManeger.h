//======================================================================================
// Effekseerä«óùÉNÉâÉXÇ‹Ç∆Çﬂ
// êßçÏÅFì°â™íqñÁ
//======================================================================================

#pragma once

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>

#include "main.h"
#include "Camera.h"

#ifdef _DEBUG
#pragma comment(lib, "EffekseerD.lib")
#pragma comment(lib, "EffekseerRendererDX11D.lib")
#else
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")
#endif // DEBUG


//
class EffekseerManeger
{
public:
	EffekseerManeger(ID3D11Device*, ID3D11DeviceContext*);

	void update();
	void Draw();

	Effekseer::Handle play(int, XMFLOAT3);
	void setstop(Effekseer::Handle);

	void setposition(Effekseer::Handle, XMFLOAT3);
	void setangle(Effekseer::Handle, XMFLOAT3);
	void setScale(Effekseer::Handle, XMFLOAT3);
	void setScale(Effekseer::Handle, float);

	void setdate(Effekseer::Handle, XMFLOAT3, XMFLOAT3, XMFLOAT3);

	bool getinstance(Effekseer::Handle);


private:
	
	EffekseerRendererDX11::RendererRef rendarer;
	Effekseer::ManagerRef manager;
	Effekseer::EffectRef  effect[8];

};

