#include "Screen.h"

Screen::Screen(int width, int height) :
        m_width(width),
        m_height(height),
        m_address(m_height == 32 ? 0x3C : 0x3D),
        m_display(-1)
{

}

bool Screen::Begin()
{
    return m_display.begin(SSD1306_SWITCHCAPVCC, m_address);
}

void Screen::Display()
{
    m_display.display();
}

void Screen::Clear()
{
    m_display.clearDisplay();
    Display();
}

void Screen::DisplayText(const std::string& text)
{
    int y = 0;
    m_display.clearDisplay();

    m_display.setTextSize(1);               // Normal 1:1 pixel scale
    m_display.setTextColor(SSD1306_WHITE);  // Draw white text
    m_display.setCursor(0, y);              // Start at top-left corner
    m_display.cp437(true);                  // Use full 256 char 'Code Page 437' font

    for(const auto c : text)
        m_display.print(c);

    m_display.println();

    Display();
}

void Screen::DisplayHTML(const std::string& html)
{
    int y = 0;
    m_display.clearDisplay();

    m_display.setTextSize(1);               // Normal 1:1 pixel scale
    m_display.setTextColor(SSD1306_WHITE);  // Draw white text
    m_display.setCursor(0, y);              // Start at top-left corner
    m_display.cp437(true);                  // Use full 256 char 'Code Page 437' font

    for(const auto c : html)
    {
        if(c == '>')
            m_display.setTextColor(SSD1306_WHITE);

        m_display.print(c);

        if(c == '<')
            m_display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }

    Display();
}
