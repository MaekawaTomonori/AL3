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

	//map
	Map* map_ = nullptr;

	//Player
	Player* player_ = nullptr;

	//Enemy
	Enemy* enemy_ = nullptr;

	//Sky
	Skydome* sky_ = nullptr;

	//Debug Camera
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

};
