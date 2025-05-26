#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
//#include "UI/Component/Slider.hpp"

void ScoreboardScene::LoadScores() {
    // TODO
    entries.clear();
    std::ifstream fin("Resource/scoreboard.txt");   // 資料檔與可執行同目錄 :contentReference[oaicite:0]{index=0}
    std::string name; int score;
    std::time_t ts;
    while (fin >> name >> score >> ts) {
        entries.push_back({name, score, ts});
    }
    fin.close();
    // 由高到低排序 :contentReference[oaicite:1]{index=1}
    std::sort(entries.begin(), entries.end(),
        [](auto &a, auto &b){ 
            if (a.score != b.score) return a.score > b.score; 
            else return a.timestamp < b.timestamp;
        }
    );
 }


void ScoreboardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    // Engine::ImageButton *btn;
    // btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    // btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 1));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);

    LoadScores();
    currentPage = 0;
    RefreshUI();
    
}
void ScoreboardScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}

void ScoreboardScene::RefreshUI() {
    // 清掉前一頁 UI
    AudioHelper::StopSample(bgmInstance);
    IScene::Terminate();
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    // ← Back 按鈕
    
    auto *btn = new Engine::ImageButton(
        "stage-select/dirt.png","stage-select/floor.png",
        20, 20, 120, 50
    );
//    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 1));
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 0));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label(
        "Back", "pirulen.ttf", 18, 80, 45, 255,255,255,255, 0.5,0.5
    ));
    
     // 計算本頁範圍
    int start = currentPage * entriesPerPage;
    int end   = std::min(start + entriesPerPage, (int)entries.size());
    for (int i = start; i < end; i++) {
        auto &e = entries[i];
        int y = 80 + (i - start) * 40;
        // 顯示「第幾名. 名字 — 分數」
        char buf[20];
        std::tm *lt = std::localtime(&e.timestamp);
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt);

        AddNewObject(new Engine::Label(
            std::to_string(i+1) + ". " + e.name + " — " + std::to_string(e.score)
            + " (" + buf + ")",
            "pirulen.ttf", 20, w/2, y, 255,255,255,255, 0.5,0.5
        ));
    }
     // Prev 按鈕
    if (currentPage > 0) {
        auto *btnP = new Engine::ImageButton(
            "stage-select/dirt.png","stage-select/floor.png",
//            50, h - 80, 100, 50
            50, h - 80, 100, 50
        );
//        btnP->SetOnClickCallback(std::bind(&ScoreboardScene::PrevOnClick, this, 0));      
        btnP->SetOnClickCallback(std::bind(&ScoreboardScene::PrevOnClick, this, 0));
        AddNewControlObject(btnP);
        AddNewObject(new Engine::Label("Prev", "pirulen.ttf", 18, 100, h-55, 0,0,0,255, 0.5,0.5));
    }
    // Next 按鈕
    if (end < (int)entries.size()) {
        auto *btnN = new Engine::ImageButton(
            "stage-select/dirt.png","stage-select/floor.png",
//            w-150, h - 80, 100, 50
            w-150, h - 80, 100, 50
        );
//        btnN->SetOnClickCallback(std::bind(&ScoreboardScene::NextOnClick, this, 0));
        btnN->SetOnClickCallback(std::bind(&ScoreboardScene::NextOnClick, this, 0));
        AddNewControlObject(btnN);
        AddNewObject(new Engine::Label("Next", "pirulen.ttf", 18, w-100, h-55, 0,0,0,255, 0.5,0.5));
    }
}

void ScoreboardScene::PrevOnClick(int) {
    currentPage--;
    RefreshUI();
}

void ScoreboardScene::NextOnClick(int) {
    currentPage++;
    RefreshUI();
}
