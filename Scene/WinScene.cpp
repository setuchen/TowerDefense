#include <functional>
#include <string>
#include <fstream>
#include <ctime>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "WinScene.hpp"

void WinScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));

    // 在勝利畫面中間稍下方顯示「Name: 」，等待玩家輸入
    playerName.clear();
    nameLabel = new Engine::Label("Name: ", "pirulen.ttf", 24, halfW, halfH / 4 + 40, 255,255,255,255, 0.5, 0.5);
    AddNewObject(nameLabel);

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}
void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void WinScene::OnKeyDown(int keyCode) {
    if (nameEditing) {
        if (keyCode == ALLEGRO_KEY_ENTER && !playerName.empty()) {
            nameEditing = false;
            SaveScore();
        }
        else if (keyCode == ALLEGRO_KEY_BACKSPACE && !playerName.empty()) {
            playerName.pop_back();
        }
        else if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z
              && playerName.size() < 12) {
            char c = 'A' + (keyCode - ALLEGRO_KEY_A);
            playerName.push_back(c);
        }
        // 更新 Label 顯示
        nameLabel->Text = std::string("Name: ") + playerName;
        return;
    }
    // 如果已經輸入完，才執行原本的按鍵邏輯（例如切回關卡選單等）
    IScene::OnKeyDown(keyCode);
}

void WinScene::SaveScore() {
    // 取出 play 場景
    auto *playScene = dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetScene("play")
    );
    // 如果轉型成功，就拿生命值；失敗就當 0
    int lives = playScene ? playScene->GetLives() : 0;
    // 你原本就有的 GetMoney()
    int money = playScene ? playScene->GetMoney() : 0;

    int finalScore = lives * 10000 + money;

    // 2. 取得時間戳
    std::time_t t = std::time(nullptr);

    // 3. 依序 append 到兩個檔案
    std::ofstream fout1("Resource/scoreboard.txt", std::ios::app);
    //std::ofstream fout2("build/Resource/scoreboard.txt", std::ios::app);
    fout1 << playerName << ' ' << finalScore << ' ' << t << '\n';
    //fout2 << playerName << ' ' << finalScore << ' ' << t << '\n';
}
