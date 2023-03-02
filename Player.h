#pragma once
#include "Engine/GameObject.h"
#include "stage.h"

class Player : public GameObject
{
private:
	int hModel_;
	XMFLOAT3 PrevPosition_;//プレイヤーの直前の位置
	Stage* pStage_;

	int maxHp_, nowHp_;
	float dashSpeed_ = 1.5;
	float slowSpeed_ = 0.5;
	bool isJumping_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};