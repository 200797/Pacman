#include "Stage.h"
#include "Engine/csvReader.h"
#include "Engine/Model.h"


//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
	CsvReader map;

	map.Load("Map.csv");
	w = map.GetWidth();
	h = map.GetHeight();
	table_ = new int* [h];
	for (int i = 0; i < w; i++) {
		table_[i] = new int[w];
	}
	for (int x = w - 1; x >= 0; x--) {
		for (int z = h - 1; z >= 0; z--) {
			table_[z][x] = map.GetValue(z, x);
		}
	}
}

//������
void Stage::Initialize()
{
	const char* fileName[] = { "Floor.fbx","Wall.fbx" };
	for (int i = 0; i < TYPE_MAX; i++) {
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
	Transform cluster;

	for (int x = 0; x < 15; x++) {

		for (int z = 0; z < 15; z++) {

			cluster.position_.x = x + 1;
			cluster.position_.z = z;
			int i = table_[x][z];

			Model::SetTransform(hModel_[i], cluster);
			Model::Draw(hModel_[i]);

		}
	}
}

//�J��
void Stage::Release()
{
	for (int i = 0; i < w; i++) {
		delete[] table_[i];
	}
	delete[] table_;
}