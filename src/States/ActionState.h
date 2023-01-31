#ifndef MANZELI_NET_BUTTON_ACTIONSTATE_H
#define MANZELI_NET_BUTTON_ACTIONSTATE_H

#define GREEN_LED_PIN           (14)
#define RED_LED_PIN             (12)

#include <sstream>
#include "IState.h"
#include "Settings/SettingsProvider.h"
#include "Sensors/Screen.h"
#include "Sensors/ButtonSensor.h"
#include "Sensors/LedSensor.h"
#include "Net/HttpQuerier.h"
#include "Net/MessageTranslater.h"
#include "StateManager.h"
#include "Net/WiFiCommunicator.h"

class ActionState : public IState
{
public:
    ActionState(StateManager& stateManager, SettingsProvider& settingsProvider, WiFiCommunicator& wiFiCommunicator,
                Screen& screen, std::shared_ptr<Button> button, std::shared_ptr<LedSensor> redLed,
                std::shared_ptr<LedSensor> greenLed, std::shared_ptr<HttpQuerier> httpQuerier);
    void OnResume() override;
    void OnStart() override;
    void OnStop() override;
    void Update() override;
    void OnButtonPressed(bool pressed);

private:
    void StartHttp();
    void StartWiFi();

    unsigned long m_lastResponse { 0 };
    Screen& m_screen;
    SettingsProvider& m_settings;
    WiFiCommunicator& m_wifiCommunicator;
    std::shared_ptr<Button> m_button;
    StateManager& m_stateManager;

    std::shared_ptr<LedSensor> m_greenLed;
    std::shared_ptr<LedSensor> m_redLed;
    std::shared_ptr<HttpQuerier> m_httpQuerier;
    MessageTranslater m_translater;
};


#endif //MANZELI_NET_BUTTON_ACTIONSTATE_H
