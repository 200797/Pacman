#include "Engine/GameObject.h"

enum
{
	TYPE_FLOOR,
	TYPE_WALL,
	TYPE_MAX
};

//テストシーンを管理するクラス
class Stage : public GameObject
{
private:
	int hModel_[TYPE_MAX];
	int** table_;
	int w, h;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//指定した位置が壁かどうかをチェック
	//引数：x,z　調べる位置
	//戻値：壁=ture/壁じゃない=false
	bool IsWall(int x, int z)
	{
		if (table_[x][z] == TYPE_WALL)
			return true;
		else
			return false;
	}
};