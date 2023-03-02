#include "Engine/GameObject.h"
enum
{
	TYPE_FLOOR,
	TYPE_WALL,
	TYPE_MAX
};
class Stage : public GameObject
{
private:
	int hModel_[TYPE_MAX];
	int** table_;
	int width_, heigth_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�w�肵���ʒu���ǂ��ǂ������`�F�b�N
	//�����Fx,z�@���ׂ�ʒu
	//�ߒl�F��=ture/�ǂ���Ȃ�=false
	bool IsWall(int x, int z)
	{
		if (table_[x][z] == TYPE_WALL){
			return true;
		}
		else
			return false;
	}
};