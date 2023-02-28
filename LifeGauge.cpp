#include "LifeGauge.h"
#include "Engine/Image.h"

//コンストラクタ
LifeGauge::LifeGauge(GameObject* parent)
	: GameObject(parent, "LifeGauge"), hPictGauge_(-1), hPictFrame_(-1), maxHp_(180), nowHp_(30)
{
}

//初期化
void LifeGauge::Initialize()
{
	hPictGauge_ = Image::Load("LifeGauge.png");
	assert(hPictGauge_ >= 0);
	hPictFrame_ = Image::Load("LifeFrame.png");
	assert(hPictFrame_ >= 0);

	//表示位置
	transform_.position_.x = -0.95f;
	transform_.position_.y = 0.85f;

}

//更新
void LifeGauge::Update()
{
}

//描画
void LifeGauge::Draw()
{
	Transform transGauge = transform_;
	transform_.scale_.x = (float)animHp_ / (float)maxHp_;
	Image::SetTransform(hPictGauge_, transGauge);
	Image::Draw(hPictGauge_);

	Image::SetTransform(hPictFrame_, transform_);
	Image::Draw(hPictFrame_);

}

//開放
void LifeGauge::Release()
{
}

