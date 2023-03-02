#pragma once
#include "Engine/GameObject.h"
#include "stage.h"

class Player : public GameObject
{
private:
	int hModel_;
	XMFLOAT3 PrevPosition_;//�v���C���[�̒��O�̈ʒu
	Stage* pStage_;

	int maxHp_, nowHp_;
	float dashSpeed_ = 1.5;
	float slowSpeed_ = 0.5;
	bool isJumping_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};