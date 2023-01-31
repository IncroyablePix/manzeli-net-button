#include "DataProviders/SerialDataProvider.h"
#include "Settings/SettingsProvider.h"
#include "Net/HttpQuerier.h"
#include "Sensors/Screen.h"
#include "Sensors/LedSensor.h"
#include "Sensors/ButtonSensor.h"
#include "States/ActionState.h"
#include "Net/WiFiCommunicator.h"
#include <Preferences.h>
#include <memory>

#define BUTTON_PIN              (33)

// --- Global Variables
auto provider = SerialDataProvider();
auto store = Preferences();

auto settings = SettingsProvider(store, provider);
auto wifiCommunicator = WiFiCommunicator(25);
auto client = wifiCommunicator.GetClient();
auto screen = Screen(128, 32);

auto button = std::make_shared<Button>(BUTTON_PIN);

auto stateManager = StateManager();

auto greenLed = std::make_shared<LedSensor>(GREEN_LED_PIN);
auto redLed = std::make_shared<LedSensor>(RED_LED_PIN);
auto getter = std::make_shared<HttpQuerier>(client, "");

[[noreturn]] void Die()
{
    for (;;)
    {
        redLed->Enable(true);
        greenLed->Enable(false);
        delay(500);

        redLed->Enable(false);
        greenLed->Enable(true);
        delay(500);
    }
}

void setup()
{
    Serial.begin(9600);

    if (!screen.Begin())
    {
        Serial.println("Failed to start SSD1306 screen");
        Die();
    }

    std::unique_ptr<ActionState> initState(new ActionState(stateManager, settings, wifiCommunicator, screen, button, redLed, greenLed, getter));
    stateManager.PushState(std::move(initState));
}

void loop()
{
    stateManager.Update();
    delay(50);
}