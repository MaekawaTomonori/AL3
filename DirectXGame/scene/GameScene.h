#pragma once

#include "Audio.h"
#include "DeathParticle.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "MapChipField.h"
#include "Model.h"
#include "Skydome.h"
#include "ViewProjection.h"

class Enemy;
class Player;
class CameraController;


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // static va
	static inline const uint32_t kEnemyCount = 3;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	ViewProjection* viewProjection_ = nullptr;

	Model* model_ = nullptr;
	Model* playerModel_ = nullptr;
	Model* enemyModel_ = nullptr;
	Model* particleModel_ = nullptr;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	MapChipField* mapChipField_;

	//Player
	Player* player_ = nullptr;

	std::list<Enemy*> enemies_;

	//Sky
	Skydome* sky_ = nullptr;

	//Debug Camera
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	CameraController* cameraController_ = nullptr;

	DeathParticle* particle_ = nullptr;

private: //method

	void GenerateBlocks();
	void CheckAllCollisions();
};
