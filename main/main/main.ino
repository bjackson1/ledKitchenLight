#include <Adafruit_NeoPixel.h>

#define PIN 2
#define LED_COUNT 8

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRBW + NEO_KHZ800);

int mid[] = {64, 64, 64, 64};
int ambient[] = {0, 0, 64, 0};

int currentLevel[4] = {0, 0, 0, 0};

void setup() {

    Serial.begin(115200);
    delay(100);

    leds.begin();
    leds.setPixelColor(0, 0, 255, 0, 0);
    leds.show();

    delay(3000);
    fullOn();

    delay(3000);
    fadeToMid();

    delay(3000);
    fadeToAmbient();

    delay(3000);
    fadeOff();
}


void loop() {

    delay(1000);
}


void fullOn()
{
    for(int i = 0; i < 255; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (currentLevel[j] < i)
            {
                currentLevel[j] = i;
            }
        }

        for (int l = 0; l < LED_COUNT; l++)
        {
            leds.setPixelColor(l, currentLevel[0], currentLevel[1], currentLevel[2], currentLevel[3]);
        }

        leds.show();
        delay(1);
    }
}

void fadeToMid()
{
    for(int i = 255; i >= 63; i--)
    {
        for (int j = 0; j < 3; j++)
        {
            if (currentLevel[j] > i)
            {
                currentLevel[j] = i;
            }
        }

        for (int l = 0; l < LED_COUNT; l++)
        {
            leds.setPixelColor(l, currentLevel[0], currentLevel[1], currentLevel[2], currentLevel[3]);
        }

        leds.show();
        delay(25);
    }
}

void fadeToAmbient()
{
    for(int i = 255; i >= 0; i--)
    {
        for (int j = 0; j < 3; j++)
        {
            if (currentLevel[j] > i)
            {
                currentLevel[j] = max(i, ambient[j]);
            }
        }

        for (int l = 0; l < LED_COUNT; l++)
        {
            leds.setPixelColor(l, currentLevel[0], currentLevel[1], max(currentLevel[2], 64), currentLevel[3]);
        }

        leds.show();
        delay(25);
    }    
}

void fadeOff()
{
    for(int i = 255; i >= 0; i--)
    {
        for (int j = 0; j < 3; j++)
        {
            if (currentLevel[j] > i)
            {
                currentLevel[j] = i;
            }
        }

        for (int l = 0; l < LED_COUNT; l++)
        {
            leds.setPixelColor(l, currentLevel[0], currentLevel[1], currentLevel[2], currentLevel[3]);
        }

        leds.show();
        delay(25);
    }   
}

void clearPixels()
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        leds.setPixelColor(i, 0, 0, 0, 0);
    }

    leds.show();
}


