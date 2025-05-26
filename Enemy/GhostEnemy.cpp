// Enemy/GhostEnemy.cpp
#include "Enemy/GhostEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include <cmath>

GhostEnemy::GhostEnemy(float x, float y)
    // 建議自行調整：圖檔路徑、碰撞半徑、速度、血量、破壞後給予金錢
    : Enemy("play/enemy-2.png",
            x, y,
            10,             // CollisionRadius
            20,            // speed (pixels/sec)
            10,            // hp
            30)                // money
{
    
}

void GhostEnemy::Update(float deltaTime) {
    auto scene = getPlayScene();
    // 目標點：格子座標 -> 世界座標 (格子中心)
    Engine::Point endPoint = PlayScene::EndGridPoint * PlayScene::BlockSize
                             + Engine::Point(PlayScene::BlockSize/2, PlayScene::BlockSize/2);
    Engine::Point dir = endPoint - Position;
    float dist = dir.Magnitude();

    // 如果這一幀能抵達終點，就直接造成玩家受傷並刪除自己
    if (dist <= speed * deltaTime) {
        scene->Hit();  // 玩家生命 -1
        scene->EnemyGroup->RemoveObject(objectIterator);
        return;
    }

    // 否則按速度往終點飛
    Engine::Point vel = dir.Normalize() * speed;
    Velocity = vel;
    Rotation = std::atan2(vel.y, vel.x);
    Sprite::Update(deltaTime);
}
