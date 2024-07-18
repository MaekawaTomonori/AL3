#pragma once

#include "Audio.h"
#include "CameraController.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "MapChipField.h"
#include "Model.h"
#include "Skydome.h"
#include "ViewProjection.h"

enum class Phase{
	kPlay,
	kDeath
};

class Enemy;
class Player;

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

	bool IsDead() const{
		return isDead;
	}

	bool IsFinished() const {
		return finished_;
	}
private: // 定数
	static const int32_t kEnemyCount = 10;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	//Camera
	CameraController* cameraController_ = nullptr;

	//model
	Model* model_ = nullptr;
	Model* enemyModel_ = nullptr;

	//map
	std::shared_ptr<Map> map_ = nullptr;

	//Player
	std::shared_ptr<Player> player_ = nullptr;

	//Enemy
	std::list<std::shared_ptr<Enemy>> enemies_;

	//Sky
	std::unique_ptr<Skydome> sky_ = nullptr;

	//Debug Camera
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	//GameScene Phase
	Phase phase_;

	bool isDead = false;

	bool finished_ = false;

private: // メンバ関数
	/// <summary>
	/// 全ての衝突判定を行う
	/// </summary>
	void CheckAllCollisions() const;

	void ChangePhase();
};
