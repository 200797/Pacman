#include "Player.h"
#include "LifeGauge.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr), maxHp_(180), nowHp_(180)
{
}

//初期化
void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_ = XMFLOAT3(2.0f, 0.0f, 2.0f);

	pStage_ = (Stage*)FindObject("Stage");
}

//更新
void Player::Update()
{
	PrevPosition_ = transform_.position_;
	XMFLOAT3 fMove = XMFLOAT3(0.0f, 0.0f, 0.0f);
	if (Input::IsKey(DIK_D)) {
		fMove.x = 0.1f;
	}
	if (Input::IsKey(DIK_A)) {
		fMove.x = -0.1f;
	}
	if (Input::IsKey(DIK_W)) {
		fMove.z = 0.1f;
	}
	if (Input::IsKey(DIK_S)) {
		fMove.z = -0.1f;
	}

	////コントローラー操作
	//fMove.x = Input::GetPadStickL().x;//引数省略は0(1P)
	//fMove.z = Input::GetPadStickL().y;//sティックはx,yで入力を見てる

	//正規化、斜め移動の速度を抑える
	XMVECTOR vMove;
	vMove = XMLoadFloat3(&fMove);
	vMove = XMVector3Normalize(vMove);//コントローラーにするならコメントアウト
	vMove *= 0.1;
	XMStoreFloat3(&fMove, vMove);

	transform_.position_.x += fMove.x;
	transform_.position_.z += fMove.z;


	//向きを変更する処理

	//ベクトルの長さを求める
	XMVECTOR vLength = XMVector3Length(vMove);//ベクトル型で受け取り
	float length = XMVectorGetX(vLength);

	if (length != 0)//vMoveの長さが0じゃないとき(動いているとき)
	{
		XMVECTOR vFront = { 0,0,1,0 };//奥向き
		vMove = XMVector3Normalize(vMove);
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);//内積
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		XMVECTOR vCross = XMVector3Cross(vFront, vMove);//外積
		//外積のYが負の値なら
		if (XMVectorGetY(vCross) < 0) {
			angle *= -1;
		}

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}

	//壁にめり込んだら直前の位置に戻す
	int checkX1, checkX2;
	int checkZ1, checkZ2;
	//右
	{
		checkX1 = (int)(transform_.position_.x + 0.3f);
		checkZ1 = (int)(transform_.position_.z + 0.2f);
		checkX2 = (int)(transform_.position_.x + 0.3f);
		checkZ2 = (int)(transform_.position_.z - 0.2f);

		if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))//引数：playerの位置
		{
			Debug::Log("接触中");
			transform_.position_.x = (float)((int)transform_.position_.x) + (1.0f - 0.3f);
		}
	}
	//左
	{
		checkX1 = (int)(transform_.position_.x - 0.3f);
		checkZ1 = (int)(transform_.position_.z + 0.2f);
		checkX2 = (int)(transform_.position_.x - 0.3f);
		checkZ2 = (int)(transform_.position_.z - 0.2f);

		if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))//引数：playerの位置
		{
			Debug::Log("接触中");
			transform_.position_.x = (float)((int)transform_.position_.x) + 0.3f;
		}
	}
	//奥
	{
		checkX1 = (int)(transform_.position_.x + 0.2f);
		checkZ1 = (int)(transform_.position_.z + 0.3f);
		checkX2 = (int)(transform_.position_.x - 0.2f);
		checkZ2 = (int)(transform_.position_.z + 0.3f);

		if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))//引数：playerの位置
		{
			Debug::Log("接触中");
			transform_.position_.z = (float)((int)transform_.position_.z) + (1.0f - 0.3f);
		}
	}
	//手前
	{
		checkX1 = (int)(transform_.position_.x + 0.2f);
		checkZ1 = (int)(transform_.position_.z - 0.3f);
		checkX2 = (int)(transform_.position_.x - 0.2f);
		checkZ2 = (int)(transform_.position_.z - 0.3f);

		if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))//引数：playerの位置
		{
			Debug::Log("接触中");
			transform_.position_.z = (float)((int)transform_.position_.z) + 0.3f;
		}
	}
	//Mキーを押すとHPを30増やす
	if (Input::IsKeyDown(DIK_M)) {
		nowHp_ += 30;
		if (nowHp_ > maxHp_) {
			nowHp_ = maxHp_;
		}
	}
	//Nキーを押すとHPを30減らす
	if (Input::IsKeyDown(DIK_N)) {
		nowHp_ -= 30;
		if (nowHp_ < 0) {
			nowHp_ = 0;
		}
	}
	LifeGauge* pLife = (LifeGauge*)FindObject("LifeGauge");
	pLife->SetHp(nowHp_, maxHp_);
}

//描画
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}

