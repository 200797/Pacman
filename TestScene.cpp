#include "TestScene.h"
#include "Engine/Camera.h"
#include "Player.h"
#include "LifeGauge.h"

//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//‰Šú‰»
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(5, 20, -5));
	Camera::SetTarget(XMFLOAT3(5, 5, 3));

	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<LifeGauge>(this);
}

//XV
void TestScene::Update()
{
}

//•`‰æ
void TestScene::Draw()
{
}

//ŠJ•ú
void TestScene::Release()
{
}