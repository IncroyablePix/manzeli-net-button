#include <HardwareSerial.h>
#include "StateManager.h"

StateManager::StateManager()
{
}

void StateManager::PushState(std::unique_ptr<IState> state)
{
    if(!m_states.empty())
        m_states.top()->OnStop();

    m_states.push(std::move(state));
    m_states.top()->OnStart();
    m_states.top()->OnResume();
}

void StateManager::PopState()
{
    m_states.top()->OnStop();
    m_states.pop();

    if(m_states.empty())
    {
        Sleep();
    }
    else
    {
        m_states.top()->OnResume();
    }
}

void StateManager::Update()
{
    if(!m_states.empty())
    {
        m_states.top()->Update();
    }
}

bool StateManager::IsWakeUpBoot()
{
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch(wakeup_reason)
    {
        case ESP_SLEEP_WAKEUP_EXT0:
        case ESP_SLEEP_WAKEUP_EXT1:
            return true;
        case ESP_SLEEP_WAKEUP_TIMER:
        case ESP_SLEEP_WAKEUP_TOUCHPAD:
        case ESP_SLEEP_WAKEUP_ULP:
        default:
            return false;
    }
}

void StateManager::Sleep() const
{
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, HIGH);
    esp_deep_sleep_start();
}
