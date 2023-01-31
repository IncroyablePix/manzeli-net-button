#include "ActionState.h"
#include "ShellState.h"

ActionState::ActionState(StateManager &stateManager, SettingsProvider &settingsProvider,
                         WiFiCommunicator &wiFiCommunicator, Screen &screen, std::shared_ptr<Button> button,
                         std::shared_ptr<LedSensor> redLed, std::shared_ptr<LedSensor> greenLed,
                         std::shared_ptr<HttpQuerier> httpQuerier) :
        m_screen(screen),
        m_settings(settingsProvider),
        m_wifiCommunicator(wiFiCommunicator),
        m_button(std::move(button)),
        m_stateManager(stateManager),
        m_greenLed(std::move(greenLed)),
        m_redLed(std::move(redLed)),
        m_httpQuerier(std::move(httpQuerier))
{

}

void ActionState::StartWiFi()
{
    connection_attempt:

    auto hostname = m_settings.GetHostname();
    auto ssid = m_settings.GetSsid();
    auto password = m_settings.GetPassword();

    Serial.println("Connecting to " + ToArduinoString(ssid));
    if (!m_wifiCommunicator.Begin(ssid, password, hostname, []
    { Serial.print('o'); }))
    {
        Serial.println("\nUnable to connect to WiFi network");
        m_settings.AskWiFiCredentials();
        goto connection_attempt;
    }

    m_settings.Save();

    Serial.print("\nConnected to WiFi network as ");
    Serial.println(m_wifiCommunicator.getIpAddress());
}

void ActionState::StartHttp()
{
    hostname_attempt:

    auto url = m_settings.GetURL();
    auto method = m_settings.GetMethod();
    auto auth = m_settings.GetAuth();

    if (url.length() == 0)
    {
        Serial.println("\nNo HTTP configuration");
        m_settings.AskHttpSettings();
        goto hostname_attempt;
    }

    m_httpQuerier->SetEndpoint(url);
    m_httpQuerier->SetMethod(method);
    m_httpQuerier->SetAuth(auth);

    m_settings.Save();
}

void ActionState::OnResume()
{

}

void ActionState::OnStart()
{
    m_screen.Display();
    m_screen.Clear();

    if(!m_stateManager.IsWakeUpBoot())
    {
        m_stateManager.Sleep();
    }

    m_settings.Begin();

    StartWiFi();
    StartHttp();
    m_lastResponse = millis();

    if (m_button->IsPressed())
    {
        std::unique_ptr<ShellState> shellState(new ShellState(m_stateManager, m_settings, m_screen, m_redLed, m_greenLed));
        m_stateManager.PushState(std::move(shellState));
        return;
    }

    m_button->SetOnPressedListener([this](bool pressed){ this->OnButtonPressed(pressed); });
    OnButtonPressed(true);
}

void ActionState::OnStop()
{
    m_greenLed->Enable(false);
    m_redLed->Enable(false);
    m_screen.Clear();
}

void ActionState::Update()
{
    auto currentTime = millis();

    if (currentTime - m_lastResponse > 10000)
    {
        m_stateManager.PopState();
    }

    m_button->CheckButton();
}

void ActionState::OnButtonPressed(bool pressed)
{
    auto result = m_httpQuerier->Execute();

    if(result.Success())
    {
        m_greenLed->Enable(true);
        m_screen.DisplayText(m_translater.FormatMessage(result.Content, m_settings.GetMessage()));
    }
    else
    {
        m_redLed->Enable(true);
        std::stringstream ss;
        ss << "Error (" << std::to_string(result.ResponseCode) << ")...\n" << ToArduinoString(result.Content);
        m_screen.DisplayText(ss.str());
    }

    m_lastResponse = millis();
}
