#pragma once

#include <vector>

/*
*	�ړI :	�`��Ώۂ̃��X�g��ێ����ADraw�R�[�������̏ꏊ�ł܂Ƃ߂ďo�����߂̃N���X
*	���R :	�@Window.cpp(������not�W��Windows)�ł�Draw���L�q��SceneDraw��RenderTarget�̃N���A�O�ɍs���Ă���
			(����ł̓����_�[�^�[�Q�b�g�ɔ��f����Ȃ�)
*			�A��������Draw�R�[���̎������e��RenderingEngine(������)��***_List�ւ�push_back�ɂȂ��Ă���
*			(�܂�***_List->render()�ȊO�̃O���[�o����Draw�R�[���͑S�����������)
*	���_ :	RenderingEngine��Draw�R�[���͎���push_back���߂̎����ɂȂ��Ă���̂ł���ɍ��킹���L�q���K�v
*			�܂��A�@�\�ǉ�����ۂ�RenderingEngine���ɐ�p��***_List���쐬���Ȃ���΂Ȃ�Ȃ�
*			(�O���[�o���֐��Ƃ��čD���ȃ^�C�~���O�ŌĂׂȂ��̂ŁA�ÓI��lib�Ɏ�������Ȃ���΂����Ȃ�)
			���̃N���X�͏�L�𖞂������߂ɑ��݂���
*/

// �O���錾
class D2DTextParams;
//class D2DFuncComponent;
//
//namespace D2DFunctions
//{
//}

//=============================================================================
//	�e�L�X�g�`��p�Ǘ��N���X
//=============================================================================
class D2DTextMng
{
public:
	D2DTextMng();
	~D2DTextMng();

	void Add(D2DTextParams* text);
	void Remove(D2DTextParams* text);
	void RemoveAll();
	void ChangeDrawOrder(D2DTextParams* text, int drawOrder);
	void Render();

private:
	std::vector<D2DTextParams*> List;
};
//=============================================================================
//	�}�l�[�W���C���X�^���X�̃Q�b�^�[
//=============================================================================
D2DTextMng* GetTextMng();

//class D2DFuncMng
//{
//public:
//	D2DFuncMng();
//	~D2DFuncMng();
//
//	void Add(D2DFuncComponent* comp);
//	void Remove(F_lib_Render::D2DFuncComponent* comp);
//	void RemoveAll();
//	void ChangeDrawOrder(F_lib_Render::D2DFuncComponent* comp, int drawOrder);
//	void Render();
//
//private:
//	std::vector<F_lib_Render::D2DFuncComponent*> List;
//};
