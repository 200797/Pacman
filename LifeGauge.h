#pragma once
#include "Engine/GameObject.h"


//テストシーンを管理するクラス
class LifeGauge : public GameObject
{
private:
	int hPictGauge_;//中身
	int hPictFrame_;//枠
	int maxHp_, nowHp_;
	int animHp_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	LifeGauge(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetHp(int nowHp, int maxHp)
	{
		nowHp_ = nowHp;
		maxHp_ = maxHp;
		animHp_ = (animHp_ * 5 + nowHp) / 6;
	}
};