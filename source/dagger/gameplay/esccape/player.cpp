#include "player.h"

#include "core/engine.h"
#include "core/game/transforms.h"

#include "gameplay/racing/racing_game_logic.h"

using namespace dagger;
using namespace esccape;

void Player::SpinUp()
{
    Engine::Dispatcher().sink<KeyboardEvent>().connect<&Player::OnKeyboardEvent>(this);
}

void Player::WindDown()
{
    Engine::Dispatcher().sink<KeyboardEvent>().disconnect<&Player::OnKeyboardEvent>(this);
}

void Player::OnKeyboardEvent(KeyboardEvent kEvent_)
{
    Engine::Registry().view<ControllerMapping>().each([&](ControllerMapping& ctrl_)
        {

            if (kEvent_.key == ctrl_.leftKey && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held))
            {
                ctrl_.input.x = -1;
            }
            else if (kEvent_.key == ctrl_.leftKey && kEvent_.action == EDaggerInputState::Released && ctrl_.input.x < 0)
            {
                ctrl_.input.x = 0;
            }
            else if (kEvent_.key == ctrl_.rightKey && (kEvent_.action == EDaggerInputState::Held || kEvent_.action == EDaggerInputState::Pressed))
            {
                ctrl_.input.x = 1;
            }
            else if (kEvent_.key == ctrl_.rightKey && kEvent_.action == EDaggerInputState::Released && ctrl_.input.x > 0)
            {
                ctrl_.input.x = 0;
            }
            else if (kEvent_.key == ctrl_.downKey && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held))
            {
                ctrl_.input.y = -1;
            }
            else if (kEvent_.key == ctrl_.downKey && kEvent_.action == EDaggerInputState::Released && ctrl_.input.y < 0)
            {
                ctrl_.input.y = 0;
            }
            else if (kEvent_.key == ctrl_.upKey && (kEvent_.action == EDaggerInputState::Held || kEvent_.action == EDaggerInputState::Pressed))
            {
                ctrl_.input.y = 1;
            }
            else if (kEvent_.key == ctrl_.upKey && kEvent_.action == EDaggerInputState::Released && ctrl_.input.y > 0)
            {
                ctrl_.input.y = 0;
            }
        });
}

void Player::Run()
{
    //RacingGameFieldSettings fieldSettings;
    //if (auto* ptr = Engine::GetDefaultResource<RacingGameFieldSettings>())
    //{
    //    fieldSettings = *ptr;
    //}

    auto view = Engine::Registry().view<Transform, ControllerMapping, PlayerEntity>();
    for (auto entity : view)
    {
        auto& t = view.get<Transform>(entity);
        auto& ctrl = view.get<ControllerMapping>(entity);
        auto& player = view.get<PlayerEntity>(entity);

        t.position.x += ctrl.input.x * player.speed * Engine::DeltaTime();
        t.position.y += ctrl.input.y * player.speed * Engine::DeltaTime();

        //Float32 boarderX = fieldSettings.GetXBoarder();
        //if (t.position.x > boarderX)
        //{
        //    t.position.x = boarderX;
        //}

        //if (t.position.x < -boarderX)
        //{
        //    t.position.x = -boarderX;
        //}
    }
}
