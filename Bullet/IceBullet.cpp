// IceBullet.cpp
#include "Bullet/IceBullet.hpp"
#include "Enemy/Enemy.hpp"           
#include "Scene/PlayScene.hpp"

static const float ICE_BULLET_SPEED = 400.0f;  
static const float ICE_BULLET_DAMAGE = 0.0f;   
static const std::string ICE_BULLET_IMG = "play/bullet-10.png";

IceBullet::IceBullet(Engine::Point position,
                     Engine::Point forwardDirection,
                     float rotation,
                     Turret* parent)
    : Bullet(
        ICE_BULLET_IMG,
        ICE_BULLET_SPEED,
        ICE_BULLET_DAMAGE,
        position,
        forwardDirection,
        rotation - ALLEGRO_PI/2,
        parent)
{
}

void IceBullet::OnExplode(Enemy* enemy) {
    // 冰凍敵人 1 秒（需在 Enemy.hpp 已新增 Freeze/凍結計時器）
    enemy->Freeze(1.0f);
    // 不呼叫父類 OnExplode，也不造成額外傷害
}
