#include "TestScene.h"
#include "Engine/Camera.h"
#include "Player.h"
#include "LifeGauge.h"

//コンストラクタ
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(5, 50, -5));
	Camera::SetTarget(XMFLOAT3(5, 20, 3));

	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<LifeGauge>(this);
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}