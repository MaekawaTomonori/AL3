#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "Player.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	for (std::vector<WorldTransform*>& blockLine : worldTransformBlocks_){
		for (WorldTransform* wtfb : blockLine){
			delete wtfb;
		}
	}
	worldTransformBlocks_.clear();

	delete model_;
	delete sky_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	const uint32_t kNumBlockVertical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	const float kBlockWidth = 2.f;
	const float kBlockHeight = 2.f;
	worldTransformBlocks_.resize(kNumBlockVertical);
	for (uint32_t row = 0; row < kNumBlockVertical; ++row){
		worldTransformBlocks_[row].resize(kNumBlockHorizontal);
		for (uint32_t column = 0; column < kNumBlockHorizontal; ++column){
			if(row % 2 == 0 && column % 2 != 0 || row%2!=0 && column%2==0)continue;
			worldTransformBlocks_[row][column] = new WorldTransform();
			worldTransformBlocks_[row][column]->Initialize();
			worldTransformBlocks_[row][column]->translation_.x = kBlockWidth * column;
			worldTransformBlocks_[row][column]->translation_.y = kBlockHeight * row;
		}
	}
	blockTexture_ = TextureManager::Load("dirt.png");

	viewProjection_.Initialize();
	model_ = Model::Create();

	isDebugCameraActive_ = false;
#ifdef _DEBUG
	isDebugCameraActive_ = true;
#endif

	debugCamera_ = new DebugCamera(1280, 720);

	sky_ = new Skydome();
	sky_->Initialize();

	player_ = new Player();
	player_->Initialize();

	viewProjection_.farZ = 1200;
	viewProjection_.Initialize();
}

void GameScene::Update() {
	for (std::vector<WorldTransform*>& blockLine : worldTransformBlocks_){
		for (WorldTransform* wtfb : blockLine){
			if (!wtfb)continue;
			wtfb->UpdateMatrix();
		}
	}

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
	for (auto blockLine : worldTransformBlocks_){
		for (WorldTransform* block : blockLine){
			if (!block)continue;
			model_->Draw(*block, viewProjection_, blockTexture_);
		}
	}

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
