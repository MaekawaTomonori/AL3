#include "GameScene.h"
#include <cassert>

#include "TextureManager.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Sprite.h"

#include "Player.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete sky_;
	delete debugCamera_;
	delete map_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	model_ = Model::Create();

	isDebugCameraActive_ = false;
#ifdef _DEBUG
	isDebugCameraActive_ = true;
#endif

	debugCamera_ = new DebugCamera(1280, 720);

	sky_ = new Skydome();
	sky_->Initialize();

	map_ = new Map();
	map_->Initialize();

	player_ = new Player();
	player_->Initialize();
	player_->SetMap(map_);

	cameraController_ = new CameraController;
	cameraController_->Initialize();
	cameraController_->SetTarget(player_);
	CameraController::Rect area = {12, 100 - 12, 6, 6};
	cameraController_->SetMovableArea(area);
	cameraController_->Reset();
}

void GameScene::Update() {

#ifdef _DEBUG
	//if (input_->TriggerKey(DIK_A)){
		//isDebugCameraActive_ = !isDebugCameraActive_;
	//}
#endif
	cameraController_->Update();
	
	map_->Update();
	sky_->Update();
	player_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//sky
	sky_->Draw(cameraController_->GetViewProjection());

	//block
	map_->Draw(cameraController_->GetViewProjection());

	//player
	player_->Draw(cameraController_->GetViewProjection());

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
