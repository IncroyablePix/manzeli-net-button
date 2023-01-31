#include "ShellState.h"
#include "StateManager.h"
#include "Waves/ConfigWave.h"

ShellState::ShellState(StateManager& stateManager, SettingsProvider& settings, Screen& screen,
                       std::shared_ptr<LedSensor> redLed, std::shared_ptr<LedSensor> greenLed) :
    m_stateManager(stateManager),
    m_screen(screen),
    m_settings(settings),
    m_redLed(std::move(redLed)),
    m_greenLed(std::move(greenLed))
{
    m_waveFunction = std::make_shared<ConfigWave>();
}

void ShellState::OnResume()
{
    Blink();
}

void ShellState::OnStart()
{
    m_screen.Clear();
    m_screen.DisplayText("Command Mode\n Plug into serial\n Press button to exit");
    Serial.println("Command Mode");
    Serial.print(">>> ");
}

void ShellState::OnStop()
{
    m_redLed->Enable(false);
    m_greenLed->Enable(false);
    m_screen.Clear();
}

void ShellState::Update()
{
    auto output = m_settings.Update();
    if(output == 0)
    {
        OnStop();
        m_stateManager.Sleep();
        return;
    }

    if(output == 1)
    {
        Serial.print("\n>>> ");
    }

    Blink();
}

void ShellState::Blink() const
{
    auto currentTime = millis();
    auto length = 2500;
    auto moment = (int) (100 * (((double)(currentTime % length)) / (double)length));

    auto signal = m_waveFunction->GetSignal(moment);
    m_redLed->Enable(signal);
    m_greenLed->Enable(signal);
}