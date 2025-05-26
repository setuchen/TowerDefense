// ShovelTool.hpp
#ifndef SHOVELTOOL_HPP
#define SHOVELTOOL_HPP

#include <string>
#include "UI/Component/ImageButton.hpp"

class PlayScene;

// ShovelTool: 點擊後進入鏟子模式，可移除已放置的炮塔並退還一半售價
class ShovelTool : public Engine::ImageButton {
protected:
    // 取得當前場景，需為 PlayScene
    PlayScene* getPlayScene();

public:
    // img: 按鈕正常貼圖，imgIn: 按鈕按下/懸停貼圖
    ShovelTool(const std::string& img, const std::string& imgIn, float x, float y);

    // 更新按鈕狀態
    void Update(float deltaTime) override;
    // 繪製按鈕
    void Draw() const override;
};

#endif // SHOVELTOOL_HPP