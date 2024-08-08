#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "Player.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "CameraController.h"
#include "Collision.h"
#include "Enemy.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	for (std::vector<WorldTransform*>& blockLine : worldTransformBlocks_){
		for (WorldTransform* wtfb : blockLine){
			delete wtfb;
		}
	}
	worldTransformBlocks_.clear();

	delete model_;
	delete playerModel_;
	delete enemyModel_;
	delete particleModel_;
	delete sky_;
	delete player_;
	delete debugCamera_;
	delete mapChipField_;
	delete cameraController_;
	for(auto& enemy : enemies_){
		delete enemy;
	}
	enemies_.clear();
	delete particle_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	mapChipField_ = new MapChipField;


	model_ = Model::CreateFromOBJ("Block");
	playerModel_ = Model::CreateFromOBJ("Player");
	enemyModel_ = Model::CreateFromOBJ("Enemy");
	particleModel_ = Model::CreateFromOBJ("DeathParticle");


	isDebugCameraActive_ = false;

	debugCamera_ = new DebugCamera(1280, 720);

	sky_ = new Skydome();
	sky_->Initialize();

	mapChipField_->LoadMapChipCsv("Resources/map.csv");
	GenerateBlocks();

	cameraController_ = new CameraController();
	cameraController_->Initialize();
	viewProjection_ = cameraController_->GetViewProjection();

	player_ = new Player();
	player_->Initialize(playerModel_, viewProjection_);
	player_->SetMapChipField(mapChipField_);

	Vector3 enemyP = { 6, 1, 0 };
	for (uint32_t i = kEnemyCount; i-- > 0;){
		Enemy* enemy = new Enemy();
		enemyP.x += 4;
		enemy->Initialize(enemyModel_, viewProjection_, enemyP);
		enemies_.push_back(enemy);
	}
	cameraController_->SetTarget(player_);
	cameraController_->Reset();

	phase_ = Phase::kPlay;
}

void GameScene::Update() {
	for (std::vector<WorldTransform*>& blockLine : worldTransformBlocks_){
		for (WorldTransform* wtfb : blockLine){
			if (!wtfb)continue;
			wtfb->UpdateMatrix();
		}
	}
	sky_->Update();

	if (!enemies_.empty()){
		for (auto& enemy : enemies_){
			enemy->Update();
		}

	}
	cameraController_->Update();
	switch (phase_){
	case Phase::kPlay:
		player_->Update();


		CheckAllCollisions();

		if(player_->IsDead()){
			ChangePhase();
			particle_ = new DeathParticle();
			particle_->Initialize(particleModel_, cameraController_->GetViewProjection(), player_->GetWorldPosition());
		}

		break;
	case Phase::kDeath:
		if(particle_){
			particle_->Update();

			if(particle_->isFinished()){
				delete particle_;
				particle_ = nullptr;
				finished_ = true;
			}
		}
		break;
	}
	

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_A)){
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif

	if (isDebugCameraActive_){
		debugCamera_->Update();

		viewProjection_->matView = debugCamera_->GetViewProjection().matView;
		viewProjection_->matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_->TransferMatrix();
	}	
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
	sky_->Draw(*viewProjection_);

	//block
	for (auto blockLine : worldTransformBlocks_){
		for (WorldTransform* block : blockLine){
			if (!block)continue;
			model_->Draw(*block, *viewProjection_);
		}
	}

	if (phase_ == Phase::kPlay){
		//player
		player_->Draw(*viewProjection_);
	}

	//enemy
	if (!enemies_.empty()){
		for(auto& enemy : enemies_){
			enemy->Draw();
		}
	}

	if(particle_){
		particle_->Draw();
	}

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

void GameScene::GenerateBlocks() {
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();

	worldTransformBlocks_.resize(numBlockVirtical);
	for(uint32_t i = 0; i < numBlockVirtical; ++i){
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	for(uint32_t i = 0; i < numBlockVirtical; ++i){
		for (uint32_t j = 0; j < numBlockHorizontal; ++j){
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock){
				WorldTransform* worldTransform = new WorldTransform;
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

void GameScene::CheckAllCollisions() {
	AABB playerAABB = player_->GetAABB();

	for(auto& enemy : enemies_){
		AABB enemyAABB = enemy->GetAABB();
		if (Collision::IsCollision(playerAABB, enemyAABB)){
			// プレイヤーと敵の衝突処理
			// ここに衝突時の処理を追加できる
			player_->onCollision(enemy);
			enemy->onCollision(player_);
		}
	}
}

void GameScene::ChangePhase() {
	switch (phase_){
	case Phase::kPlay:
		phase_ = Phase::kDeath;
		break;
	case Phase::kDeath:
		break;
	}
}
