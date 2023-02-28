#include "Player.h"
#include "LifeGauge.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr), maxHp_(180), nowHp_(180)
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

	////�R���g���[���[����
	//fMove.x = Input::GetPadStickL().x;//�����ȗ���0(1P)
	//fMove.z = Input::GetPadStickL().y;//s�e�B�b�N��x,y�œ��͂����Ă�

	//���K���A�΂߈ړ��̑��x��}����
	XMVECTOR vMove;
	vMove = XMLoadFloat3(&fMove);
	vMove = XMVector3Normalize(vMove);//�R���g���[���[�ɂ���Ȃ�R�����g�A�E�g
	vMove *= 0.1;
	XMStoreFloat3(&fMove, vMove);

	transform_.position_.x += fMove.x;
	transform_.position_.z += fMove.z;


	//������ύX���鏈��

	//�x�N�g���̒��������߂�
	XMVECTOR vLength = XMVector3Length(vMove);//�x�N�g���^�Ŏ󂯎��
	float length = XMVectorGetX(vLength);

	if (length != 0)//vMove�̒�����0����Ȃ��Ƃ�(�����Ă���Ƃ�)
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
	int checkX1, checkX2;
	int checkZ1, checkZ2;
	//�E
	{
		checkX1 = (int)(transform_.position_.x + 0.3f);
		checkZ1 = (int)(transform_.position_.z + 0.2f);
		checkX2 = (int)(transform_.position_.x + 0.3f);
		checkZ2 = (int)(transform_.position_.z - 0.2f);

		if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))//�����Fplayer�̈ʒu
		{
			Debug::Log("�ڐG��");
			transform_.position_.x = (float)((int)transform_.position_.x) + (1.0f - 0.3f);
		}
	}
	//��
	{
		checkX1 = (int)(transform_.position_.x - 0.3f);
		checkZ1 = (int)(transform_.position_.z + 0.2f);
		checkX2 = (int)(transform_.position_.x - 0.3f);
		checkZ2 = (int)(transform_.position_.z - 0.2f);

		if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))//�����Fplayer�̈ʒu
		{
			Debug::Log("�ڐG��");
			transform_.position_.x = (float)((int)transform_.position_.x) + 0.3f;
		}
	}
	//��
	{
		checkX1 = (int)(transform_.position_.x + 0.2f);
		checkZ1 = (int)(transform_.position_.z + 0.3f);
		checkX2 = (int)(transform_.position_.x - 0.2f);
		checkZ2 = (int)(transform_.position_.z + 0.3f);

		if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))//�����Fplayer�̈ʒu
		{
			Debug::Log("�ڐG��");
			transform_.position_.z = (float)((int)transform_.position_.z) + (1.0f - 0.3f);
		}
	}
	//��O
	{
		checkX1 = (int)(transform_.position_.x + 0.2f);
		checkZ1 = (int)(transform_.position_.z - 0.3f);
		checkX2 = (int)(transform_.position_.x - 0.2f);
		checkZ2 = (int)(transform_.position_.z - 0.3f);

		if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))//�����Fplayer�̈ʒu
		{
			Debug::Log("�ڐG��");
			transform_.position_.z = (float)((int)transform_.position_.z) + 0.3f;
		}
	}
	//M�L�[��������HP��30���₷
	if (Input::IsKeyDown(DIK_M)) {
		nowHp_ += 30;
		if (nowHp_ > maxHp_) {
			nowHp_ = maxHp_;
		}
	}
	//N�L�[��������HP��30���炷
	if (Input::IsKeyDown(DIK_N)) {
		nowHp_ -= 30;
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

