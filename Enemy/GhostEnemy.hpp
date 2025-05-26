// Enemy/GhostEnemy.hpp
#ifndef GHOSTENEMY_HPP
#define GHOSTENEMY_HPP

#include "Enemy.hpp"

class GhostEnemy : public Enemy {
public:
    // x, y 為生成時的世界座標 (pixel)
    GhostEnemy(float x, float y);

    // 完全覆寫 Update，使其無視 path，直接飛向終點
    void Update(float deltaTime) override;
};

#endif // GHOSTENEMY_HPP
