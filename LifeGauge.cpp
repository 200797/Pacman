#include "LifeGauge.h"
#include "Engine/Image.h"

//�R���X�g���N�^
LifeGauge::LifeGauge(GameObject* parent)
	: GameObject(parent, "LifeGauge"), hPictGauge_(-1), hPictFrame_(-1), maxHp_(180), nowHp_(30)
{
}

//������
void LifeGauge::Initialize()
{
	hPictGauge_ = Image::Load("LifeGauge.png");
	assert(hPictGauge_ >= 0);
	hPictFrame_ = Image::Load("LifeFrame.png");
	assert(hPictFrame_ >= 0);

	//�\���ʒu
	transform_.position_.x = -0.95f;
	transform_.position_.y = 0.85f;

}

//�X�V
void LifeGauge::Update()
{
}

//�`��
void LifeGauge::Draw()
{
	Transform transGauge = transform_;
	transform_.scale_.x = (float)animHp_ / (float)maxHp_;
	Image::SetTransform(hPictGauge_, transGauge);
	Image::Draw(hPictGauge_);

	Image::SetTransform(hPictFrame_, transform_);
	Image::Draw(hPictFrame_);

}

//�J��
void LifeGauge::Release()
{
}

