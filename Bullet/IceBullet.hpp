// IceBullet.hpp
#ifndef ICEBULLET_HPP
#define ICEBULLET_HPP

#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine { struct Point; }

class IceBullet : public Bullet {
public:
    explicit IceBullet(Engine::Point position,
                       Engine::Point forwardDirection,
                       float rotation,
                       Turret* parent);
    void OnExplode(Enemy* enemy) override;
};

#endif // ICEBULLET_HPP
