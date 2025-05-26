#ifndef ScoreboardScene_HPP
#define ScoreboardScene_HPP
#include <memory>
#include <vector>
#include <string>
#include <ctime>

#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>

struct ScoreEntry
{
    std::string name;
    int score;
    std::time_t timestamp;
};


class ScoreboardScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    void LoadScores();
    void RefreshUI(); 
    std::vector<ScoreEntry> entries;
    int currentPage = 0;
    static constexpr int entriesPerPage = 10;
public:
    explicit ScoreboardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void PrevOnClick(int);
    void NextOnClick(int);
};

#endif   // ScoreboardScene_HPP
