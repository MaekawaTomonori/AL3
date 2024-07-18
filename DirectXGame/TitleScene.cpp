#include "TitleScene.h"

#include "Input.h"

void TitleScene::Initialize() {
    finished_ = false;
}

void TitleScene::Update() {
    Input::GetInstance()->Update();
    if(Input::GetInstance()->PushKey(DIK_SPACE)){
        finished_ = true;
    }
}

void TitleScene::Draw() {
}
