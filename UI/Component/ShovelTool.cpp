// ShovelTool.cpp
#include <allegro5/color.h>

#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "ShovelTool.hpp"

PlayScene* ShovelTool::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

ShovelTool::ShovelTool(const std::string& img, const std::string& imgIn, float x, float y)
    : ImageButton(img, imgIn, x, y) {
    // 點擊後觸發鏟子模式
    SetOnClickCallback([this]() {
        auto scene = getPlayScene();
        scene->shovelMode = true;        // 需在 PlayScene.hpp 新增 bool shovelMode;
        scene->preview = nullptr;        // 取消任何建塔預覽
        scene->imgTarget->Visible = false; // 隱藏建塔指標
    });
}

void ShovelTool::Update(float deltaTime) {
    ImageButton::Update(deltaTime);
    // 若想根據狀態禁用可在此判斷並修改 Enabled
}

void ShovelTool::Draw() const {
    ImageButton::Draw();
}