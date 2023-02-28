#include "TestScene.h"
#include "Engine/Camera.h"
#include "Player.h"
#include "LifeGauge.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(5, 50, -5));
	Camera::SetTarget(XMFLOAT3(5, 20, 3));

	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<LifeGauge>(this);
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}