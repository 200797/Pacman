#include "Player.h"
#include "LifeGauge.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr), maxHp_(180), nowHp_(180), isJumping_(false)
{
}

//������
void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_ = XMFLOAT3(2.0f, 0.0f, 2.0f);

	pStage_ = (Stage*)FindObject("Stage");
}

//�X�V
void Player::Update()
{
	PrevPosition_ = transform_.position_;
	XMFLOAT3 fMove = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//�L�[�{�[�h����
	//if (Input::IsKey(DIK_D)) {
	//	fMove.x = 0.1f;
	//}
	//if (Input::IsKey(DIK_A)) {
	//	fMove.x = -0.1f;
	//}
	//if (Input::IsKey(DIK_W)) {
	//	fMove.z = 0.1f;
	//}
	//if (Input::IsKey(DIK_S)) {
	//	fMove.z = -0.1f;
	//}
	//fMove.x = Input::GetPadStickL().x;//�����ȗ���0(1P)
	//fMove.z = Input::GetPadStickL().y;//�X�e�B�b�N��x,y�œ��͂����Ă�
	//XMVECTOR vMove;
	////���K���A�΂߈ړ��̑��x��}����
	//vMove = XMLoadFloat3(&fMove);
	////vMove = XMVector3Normalize(vMove);
	//vMove *= 0.1;
	//XMStoreFloat3(&fMove, vMove);

	transform_.position_.x += fMove.x;
	transform_.position_.z += fMove.z;

	XMVECTOR vMove;
	//�R���g���[���[����
	if (Input::IsPadButton(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		fMove.x = Input::GetPadStickL().x * dashSpeed_;//�����ȗ���0(1P)
		fMove.z = Input::GetPadStickL().y * dashSpeed_;//�X�e�B�b�N��x,y�œ��͂����Ă�

		vMove = XMLoadFloat3(&fMove);
		vMove *= 0.1;
		XMStoreFloat3(&fMove, vMove);

		transform_.position_.x += fMove.x;
		transform_.position_.z += fMove.z;
	}
	else if (Input::IsPadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
		fMove.x = Input::GetPadStickL().x * slowSpeed_;//�����ȗ���0(1P)
		fMove.z = Input::GetPadStickL().y * slowSpeed_;//�X�e�B�b�N��x,y�œ��͂����Ă�

		vMove = XMLoadFloat3(&fMove);
		vMove *= 0.1;
		XMStoreFloat3(&fMove, vMove);

		transform_.position_.x += fMove.x;
		transform_.position_.z += fMove.z;
	}
	else{
		fMove.x = Input::GetPadStickL().x;//�����ȗ���0(1P)
		fMove.z = Input::GetPadStickL().y;//�X�e�B�b�N��x,y�œ��͂����Ă�

		vMove = XMLoadFloat3(&fMove);
		vMove *= 0.1;
		XMStoreFloat3(&fMove, vMove);

		transform_.position_.x += fMove.x;
		transform_.position_.z += fMove.z;
	}
	//�W�����v
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && isJumping_ == false)
	{
		for (float y = 0.6; y > 0; y -= 0.1) {
			transform_.position_.y += y;
		}
		isJumping_ = true;
	}
	if (transform_.position_.y > 0) {
		transform_.position_.y -= 0.1f;

	}
	else {
		isJumping_ = false;
	}

	//������ύX
	//�x�N�g���̒��������߂�
	XMVECTOR vLength = XMVector3Length(vMove);
	float length = XMVectorGetX(vLength);

	if (length != 0)
	{
		XMVECTOR vFront = { 0,0,1,0 };//������
		vMove = XMVector3Normalize(vMove);
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);//����
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		XMVECTOR vCross = XMVector3Cross(vFront, vMove);//�O��
		//�O�ς�Y�����̒l�Ȃ�
		if (XMVectorGetY(vCross) < 0) {
			angle *= -1;
		}

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}

	//�ǂɂ߂荞�񂾂璼�O�̈ʒu�ɖ߂�
	int checkR, checkL;
	int checkB, checkF;
	//�E
	{
		checkR = (int)(transform_.position_.x + 0.3f);
		checkB = (int)(transform_.position_.z + 0.2f);
		checkL = (int)(transform_.position_.x + 0.3f);
		checkF = (int)(transform_.position_.z - 0.2f);

		if (pStage_->IsWall(checkR, checkB) || pStage_->IsWall(checkL, checkF))//�����Fplayer�̈ʒu
		{
			Debug::Log("�ڐG��");
			transform_.position_.x = (float)((int)transform_.position_.x) + (1.0f - 0.3f);
		}
	}
	//��
	{
		checkR = (int)(transform_.position_.x - 0.3f);
		checkB = (int)(transform_.position_.z + 0.2f);
		checkL = (int)(transform_.position_.x - 0.3f);
		checkF = (int)(transform_.position_.z - 0.2f);

		if (pStage_->IsWall(checkR, checkB) || pStage_->IsWall(checkL, checkF))//�����Fplayer�̈ʒu
		{
			Debug::Log("�ڐG��");
			transform_.position_.x = (float)((int)transform_.position_.x) + 0.3f;
		}
	}
	//��
	{
		checkR = (int)(transform_.position_.x + 0.2f);
		checkB = (int)(transform_.position_.z + 0.3f);
		checkL = (int)(transform_.position_.x - 0.2f);
		checkF = (int)(transform_.position_.z + 0.3f);

		if (pStage_->IsWall(checkR, checkB) || pStage_->IsWall(checkL, checkF))//�����Fplayer�̈ʒu
		{
			Debug::Log("�ڐG��");
			transform_.position_.z = (float)((int)transform_.position_.z) + (1.0f - 0.3f);
		}
	}
	//��O
	{
		checkR = (int)(transform_.position_.x + 0.2f);
		checkB = (int)(transform_.position_.z - 0.3f);
		checkL = (int)(transform_.position_.x - 0.2f);
		checkF = (int)(transform_.position_.z - 0.3f);

		if (pStage_->IsWall(checkR, checkB) || pStage_->IsWall(checkL, checkF))//�����Fplayer�̈ʒu
		{
			Debug::Log("�ڐG��");
			transform_.position_.z = (float)((int)transform_.position_.z) + 0.3f;
		}
	}

	//�Q�[�W����
	if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_RIGHT)) {
		nowHp_ += 1;
		if (nowHp_ > maxHp_) {
			nowHp_ = maxHp_;
		}
	}
	if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_LEFT)) {
		nowHp_ -= 1;
		if (nowHp_ < 0) {
			nowHp_ = 0;
		}
	}
	LifeGauge* pLife = (LifeGauge*)FindObject("LifeGauge");
	pLife->SetHp(nowHp_, maxHp_);
}

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}

