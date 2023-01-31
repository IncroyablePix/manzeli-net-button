#ifndef SCREEN_INCLUDED
#define SCREEN_INCLUDED

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_ADDRESS      (0x3C)          ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class Screen
{
    public:
        Screen(int width, int height);
        bool Begin();
        void Display();
        void Clear();
        void DisplayText(const std::string& text);
        void DisplayHTML(const std::string& html);

    private:
        int m_width;
        int m_height;
        byte m_address;
        Adafruit_SSD1306 m_display;
};

#endif
