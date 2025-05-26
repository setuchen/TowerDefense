// IceTurret.hpp
#ifndef ICE_TURRET_HPP
#define ICE_TURRET_HPP

#include "Turret.hpp"

class IceTurret : public Turret {
public:
    static const int Price;
    IceTurret(float x, float y);
    void CreateBullet() override;
};

#endif // ICE_TURRET_HPP
