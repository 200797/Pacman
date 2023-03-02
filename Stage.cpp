#include "Stage.h"
#include "Engine/csvReader.h"
#include "Engine/Model.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
	CsvReader map;

	map.Load("Map.csv");
	width_ = map.GetWidth();
	heigth_ = map.GetHeight();
	table_ = new int* [width_];
	for (int x = 0; x < width_; x++) {
		table_[x] = new int[heigth_];
	}
	for (int x = 0; x < width_; x++) {
		for (int z = 0; z < heigth_; z++) {
			table_[x][z] = map.GetValue(x, heigth_ - z -1);
		}
	}
}

//初期化
void Stage::Initialize()
{
	const char* fileName[] = { "Floor.fbx","Wall.fbx" };
	for (int i = 0; i < TYPE_MAX; i++) {
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
	Transform cluster;

	for (int x = 0; x < width_; x++) {

		for (int z = 0; z < heigth_; z++) {

			cluster.position_.x = x + 1;
			cluster.position_.z = z;
			int i = table_[x][z];

			Model::SetTransform(hModel_[i], cluster);
			Model::Draw(hModel_[i]);

		}
	}
}

//開放
void Stage::Release()
{
	for (int i = 0; i < width_; i++) {
		delete[] table_[i];
	}
	delete[] table_;
}