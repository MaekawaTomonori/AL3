#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "Player.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

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

	viewProjection_.Initialize();
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
	player_->applyMap(*map_);

	viewProjection_.farZ = 1200;
	viewProjection_.Initialize();

}

void GameScene::Update() {

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_A)){
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif

	if (isDebugCameraActive_){
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}
	else{
		viewProjection_.UpdateMatrix();
	}
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
	sky_->Draw(viewProjection_);

	//block
	map_->Draw(viewProjection_);

	//player
	player_->Draw(viewProjection_);

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
