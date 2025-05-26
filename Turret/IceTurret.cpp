// IceTurret.cpp
#include <cmath>
#include "IceTurret.hpp"
#include "Bullet/IceBullet.hpp"       
#include "Scene/PlayScene.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"

const int IceTurret::Price = 50;      // 可依需求調整售價

IceTurret::IceTurret(float x, float y)
    : Turret("play/tower-base.png", "play/turret-6.png", x, y, 200, Price, 1.5) {
    Anchor.y += 8.0f / GetBitmapHeight();
}

void IceTurret::CreateBullet() {
    // originRotation 跟 Turret.cpp 一致，用轉過 PI/2 的 Rotation 來算射擊方向 :contentReference[oaicite:0]{index=0}
    Engine::Point diff = Engine::Point(
        std::cos(Rotation - ALLEGRO_PI/2),
        std::sin(Rotation - ALLEGRO_PI/2)
    );
    // 2. 算出子彈本身要用的 rotation
    float rotation = std::atan2(diff.y, diff.x);
    // 3. 正規化方向向量
    Engine::Point normalized = diff.Normalize();
    // 4. 設定子彈出現的位置：往前推 36 個像素到炮管口
    Engine::Point spawnPos = Position + normalized * 36;
    // 5. 建立、加入子彈
    auto b = new IceBullet(spawnPos,    // 起點
                           diff,        // forwardDirection
                           rotation,    // rotation
                           this);       // parent
    getPlayScene()->BulletGroup->AddNewObject(b);
}

