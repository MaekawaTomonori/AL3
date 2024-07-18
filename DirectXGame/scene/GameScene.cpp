#include "GameScene.h"
#include <cassert>

#include "Collision.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Sprite.h"

#include "Player.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
	enemies_.clear();
	delete enemyModel_;
	delete cameraController_;
}

void GameScene::Initialize() {
	srand(static_cast<unsigned int>(time(nullptr)));

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	model_ = Model::Create();

	isDebugCameraActive_ = false;
#ifdef _DEBUG
	isDebugCameraActive_ = true;
#endif

	debugCamera_ = new DebugCamera(1280, 720);

	sky_ = std::make_unique<Skydome>();
	sky_->Initialize();

	map_ = std::make_shared<Map>();
	map_->Initialize();

	player_ = std::make_shared<Player>();
	player_->Initialize();
	player_->SetMap(map_.get());

	enemyModel_ = Model::CreateFromOBJ("enemy");
	for(int32_t i = 0; i < kEnemyCount; ++i){
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		Vector3 pos = Vector3::Random() * 10.f;
		enemy->Initialize(enemyModel_, pos);

		enemies_.push_back(enemy);
	}

	cameraController_ = new CameraController;
	cameraController_->Initialize();
	cameraController_->SetTarget(player_.get());
	CameraController::Rect area = {12, 100 - 12, 6, 6};
	cameraController_->SetMovableArea(area);
	cameraController_->Reset();
	cameraController_->SetTarget(player_.get());

	phase_ = Phase::kPlay;
}

void GameScene::Update() {

#ifdef _DEBUG
	//if (input_->TriggerKey(DIK_A)){
		//isDebugCameraActive_ = !isDebugCameraActive_;
	//}
#endif
	
	map_->Update();
	sky_->Update();

	switch (phase_){
	case Phase::kPlay:
		cameraController_->Update();
		player_->Update();

		for (auto enemy : enemies_){
			enemy->Update();
		}

		CheckAllCollisions();

		if(isDead){
			ChangePhase();
			const Vector3& deathParticlePos = player_->GetWorldPosition();

			//deathparticle
			(void)deathParticlePos;
		}
		break;
	case Phase::kDeath:
		//deathparticleFinished
		finished_ = true;
		
		break;
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
	sky_->Draw(cameraController_->GetViewProjection());

	//block
	map_->Draw(cameraController_->GetViewProjection());

	//player
	player_->Draw(cameraController_->GetViewProjection());

	for (const auto& enemy : enemies_){
		enemy->Draw(cameraController_->GetViewProjection());
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

void GameScene::CheckAllCollisions() const {
	// プレイヤーと敵の当たり判定
	AABB playerAABB = player_->GetAABB();

	for (const auto& enemy : enemies_){
		if(Collision::IsCollision(playerAABB, enemy->GetAABB())){
			player_->OnCollision(enemy.get());
			enemy->OnCollision(player_.get());
		}
	}
}

void GameScene::ChangePhase() {
	switch (phase_){
	case Phase::kPlay:
		phase_ = Phase::kDeath;
		break;
	case Phase::kDeath:
	default:
		break;
	}
}
