#pragma once
#include "Engine/GameObject.h"


//�e�X�g�V�[�����Ǘ�����N���X
class LifeGauge : public GameObject
{
private:
	int hPictGauge_;//���g
	int hPictFrame_;//�g
	int maxHp_, nowHp_;
	int animHp_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	LifeGauge(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetHp(int nowHp, int maxHp)
	{
		nowHp_ = nowHp;
		maxHp_ = maxHp;
		animHp_ = (animHp_ * 5 + nowHp) / 6;
	}
};