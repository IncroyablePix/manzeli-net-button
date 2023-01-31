#ifndef MANZELI_NET_BUTTON_SHELLSTATE_H
#define MANZELI_NET_BUTTON_SHELLSTATE_H


#include "IState.h"
#include "Sensors/Screen.h"
#include "Settings/SettingsProvider.h"
#include "StateManager.h"
#include "Sensors/LedSensor.h"
#include "Waves/IDigitalWave.h"

class ShellState : public IState
{
public:
    ShellState(StateManager& stateManager, SettingsProvider& settings, Screen& screen,
               std::shared_ptr<LedSensor> redLed, std::shared_ptr<LedSensor> greenLed);
    void OnResume() override;
    void OnStart() override;
    void OnStop() override;
    void Update() override;

private:
    Screen& m_screen;
    SettingsProvider& m_settings;
    std::shared_ptr<LedSensor> m_redLed;
    std::shared_ptr<LedSensor> m_greenLed;
    std::shared_ptr<IDigitalWave> m_waveFunction;
    StateManager& m_stateManager;

    void Blink() const;
};


#endif //MANZELI_NET_BUTTON_SHELLSTATE_H
