/* 
 * This is the main source code for the RX-8 coolant monitor project.
 * It targets an Arduino based Pro Micro.
 * Author: Stephane Gilbert
 * BSD tree clause licence (SPDX: BSD-3-Clause)
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "coolant_monitor.h"
#include "FreeSans18pt7bNum.h"

#define OLED_RESET 4 // Reset for Adafruit SSD1306

// Using this constructor to have the maximum I2C communication speed.
Adafruit_SSD1306 display_1(128, 32, &Wire, OLED_RESET);
Adafruit_SSD1306 display_2(128, 32, &Wire, OLED_RESET);
Adafruit_SSD1306 display_3(128, 32, &Wire, OLED_RESET);

Adafruit_SSD1306* displays [] = { &display_1, &display_2, &display_3 };
uint8_t display_count = sizeof(displays) / sizeof(Adafruit_SSD1306*);

// Values to cache the current reading in memory
float current_coolant_temp;
float current_coolant_psi;
float current_supply_voltage;
bool thermistor_reference_mode_high = true;
bool temperatureUnitIsFahrenheit = false;
bool currentDaylight = true;

// Select the specified display. All further write operation will go to that display
// display: An instance reference of the Adafruit_SSD1306 class
void selectDisplay(Adafruit_SSD1306 &display)
{
    if ((int)&display == (int)&display_1) {
        digitalWrite(DISPLAY_2_SELECT_OUTPUT_PIN, LOW);
        digitalWrite(DISPLAY_3_SELECT_OUTPUT_PIN, LOW);
        digitalWrite(DISPLAY_1_SELECT_OUTPUT_PIN, HIGH);
    }

    if ((int)&display == (int)&display_2) {
        digitalWrite(DISPLAY_1_SELECT_OUTPUT_PIN, LOW);
        digitalWrite(DISPLAY_3_SELECT_OUTPUT_PIN, LOW);
        digitalWrite(DISPLAY_2_SELECT_OUTPUT_PIN, HIGH);
    }

    if ((int)&display == (int)&display_3) {
        digitalWrite(DISPLAY_1_SELECT_OUTPUT_PIN, LOW);
        digitalWrite(DISPLAY_2_SELECT_OUTPUT_PIN, LOW);
        digitalWrite(DISPLAY_3_SELECT_OUTPUT_PIN, HIGH);
    }
}

// Read the specified analog input pin many times and return the mean
// pin: The pin on which the analog read will occur
// Return: A float between 0 and 1023 representing the analog value on the specieid pin
float readAnalogInputRaw(uint8_t pin)
{
    uint16_t cumulative_value = 0;
    int single_value;

    // The first read is a dummy read only to warm up the ADC, so we Loop from zero to
    // ANALOG_SAMPLES_COUNT inclusively, in fact ANALOG_SAMPLES_COUNT + 1 times.
    for (size_t i = 0; i <= ANALOG_SAMPLES_COUNT; i++)
    {
        single_value = analogRead(pin);

        // If it's the first read, force the value to zero, it it will not be taken into account
        cumulative_value += i > 0 ? single_value : 0;
        delay(ANALOG_DELAY_BETWEEN_ACQUISITIONS);
    }

    // Return the arithmetic mean
    return (float)cumulative_value / (float)ANALOG_SAMPLES_COUNT;
}

// Returns the voltage on the specified pin using an external reference voltage for maximum accuracy
// pin: The pin on which the analog read will occur
// Return: A float representing the voltage read at the specified pin
float readVoltage(uint8_t pin)
{
    float reference = readAnalogInputRaw(REFERENCE_ANALOG_INPUT_PIN);
    float value = readAnalogInputRaw(pin);

    return (ANALOG_REFERENCE_VOLTAGE * value) / reference;
}

// Invalidate the display value so the next reading will force the display to be redrawn
// display: An instance reference of the Adafruit_SSD1306 class
void forceDisplayRefresh(Adafruit_SSD1306 &display)
{
    if ((int)&display == (int)&display_1)
        current_coolant_temp = __FLT_MIN__;

    if ((int)&display == (int)&display_2)
        current_coolant_psi = __FLT_MIN__;

    if ((int)&display == (int)&display_3)
        current_supply_voltage = __FLT_MIN__;
}

// Draw an icon using specified display object
// display: An instance reference of the Adafruit_SSD1306 class
// icon: The specific icon to draw, emum value
// xpos, ypos: The top left corner to start the drawing 
void drawIcon(Adafruit_SSD1306 &display, const Icon icon, const uint8_t xpos, const uint8_t ypos)
{
    display.drawBitmap(
        (uint16_t)xpos,
        (uint16_t)ypos,
        epd_bitmap_allArray[(uint8_t)icon],
        pgm_read_byte(&iconSize[(uint8_t)icon].width),
        pgm_read_byte(&iconSize[(uint8_t)icon].height),
        1);
}

// Draw the warning icon using the the specified display object
// display: An instance reference of the Adafruit_SSD1306 class, the display to write to
void drawWarning(Adafruit_SSD1306 &display)
{
    drawIcon(display, Icon::warning_icon, 95, 0);
}

// Display a fault message using the the specified display object
// display: An instance reference of the Adafruit_SSD1306 class, the display to write to
// Note: The display is cleared, draw and updated
void displayFault(Adafruit_SSD1306 &display)
{
    display.clearDisplay();
    drawIcon(display, Icon::fault_message, 11, 3);
    selectDisplay(display);
    display.display();

    // Ensure if we go out of fault, the display will refresh the actual value
    forceDisplayRefresh(display);
}

// Sets the reference resistor (pull down) for the thermistor
// value: True to set the high resistor value, False to select the low resistor value.
void setThermistorHighReference(const bool value)
{
    // The logic is inverted here by the 2n7000 on the PCB
    digitalWrite(THERMISTOR_REFERENCE_SELECT_OUTPUT_PIN, value ? LOW : HIGH);
    thermistor_reference_mode_high = value;
}

// Convert the provided temperature from Celsius to Fahrenheit
// temperature: The temperature to convert from Celsius
// Return: A float representing the converted temperature, in Fahrenheit
float convertToFahrenheit(float temperature)
{
    return temperature * 9.0 / 5.0 + 32.0;
}

// Read the thermistor resistor value and convert it to temperature in Celsius
// using the Steinhart-Hart equation.
// TC: The variable that will hold the returned temperature value
// Return: ENOERR if the conversion succeeded and the value has been placed in the TC parameter, otherwise the error code
// Note: The function also manage the pull-down resistor set related to the sensor
int getCoolantTempCelsius(float &TC)
{
    float tResValue;
    float logTResValue;
    float TK;
    float analogValue;

    // The constant values for the AEM-30-2012 have been calculated with this online calculator:
    // https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
    // The reference resistor and temperature used for the calculator was extracted from the
    // following datasheet from AEM:
    // https://www.aemelectronics.com/files/instructions/30-2012%20Sensor%20Data.pdf
    float c1 = 1.144169514e-3;   // -40C, 402392 OHMs
    float c2 = 2.302830665e-4;   // 50C, 3911 OHMs
    float c3 = 0.8052469400e-7;  // 150C, 189.3 OHMs

    // Get the analog value on the input pin
    analogValue = readAnalogInputRaw(COOLANT_ANALOG_INPUT_PIN);

    // Avoid dividing by zero
    if (analogValue == 0) {
        return EDIVZERO;
    }

    // Discard any values that do not make sense
    if (analogValue < 0) {
        return ERANGE;
    }

    // Use the correct pull down resistor reference value according to the actual configured value
    float t_res_ref = thermistor_reference_mode_high ? THERMISTOR_RESISTOR_REFERENCE_HIGH : THERMISTOR_RESISTOR_REFERENCE_LOW;

    // Compute the thermistor resistor value, using the equation R2 = R1 * (Vin / Vout - 1)
    tResValue = t_res_ref * (1023.0 / ((float)analogValue) - 1.0);

    // Convert the thermistor resistor value to temperature in Kelvin using the Steinhart-Hart equation
    logTResValue = log(tResValue);
    TK = (1.0 / (c1 + c2 * logTResValue + c3 * logTResValue * logTResValue * logTResValue));

    // Ensure the temperature is between the sensor range: 233.15K to 425.15K (-40C to 150C)
    if (TK < 233.15 || TK > 423.15) {
        return ERANGE;
    }

    // Convert the temperation from Kelvin to Celsius
    TC = TK - 273.15;

    // Manage the pull-down resistor reference for the next run
    if (thermistor_reference_mode_high && TC > THERMISTOR_RESISTOR_REFERENCE_LOW_TRESHOLD)
        setThermistorHighReference(false);

    if (! thermistor_reference_mode_high && TC < THERMISTOR_RESISTOR_REFERENCE_HIGH_TRESHOLD)
        setThermistorHighReference(true);

    return ENOERR;
}

// Get the Coolant pressure in PSI.
// psi: The variable that will hold the returned PSI value
// Return: ENOERR if the conversion succeeded and the value has been placed in the psi
//         parameter, otherwise the error code
int getCoolantPsi(float &psi)
{
    float volts;
    volts = readVoltage(PSI_ANALOG_INPUT_PIN);

    // Ensure the voltage is between the sensor range, otherwise return an error
    if (volts < 0.2 || volts > 4.8) {
        return ERANGE;
    }

    // Convert voltage to PSI
    // According to this datasheet, PSI = (3.7529*(Voltage)) - 1.8765
    // https://www.aemelectronics.com/files/instructions/30-2131-15G%20Sensor%20Data.pdf
    psi = 3.7529 * volts - 1.8765;
    if (psi < 0)
        psi = 0;

    return ENOERR;
}

// Read the supply voltage before the DC-DC converter
// It should be between 11.5 and 14.5
// voltage: The variable that will hold the returned voltage value
// Return: ENOERR if the conversion succeeded and the value has been placed in the voltage
//         parameter, otherwise the error code
int getSupplyVoltage(float &voltage)
{
    float volts, supply_voltage;
    volts = readVoltage(VOLTAGE_ANALOG_INPUT_PIN);

    // Convert pin voltage to actual voltage based on the onboard tension divider
    supply_voltage = volts / (VOLTAGE_DIVIDER_R2 / (VOLTAGE_DIVIDER_R1 + VOLTAGE_DIVIDER_R2));

    // We can't be alive and have a supply voltage below 7V at the same time
    if (supply_voltage < 7)
        return ERANGE;

    voltage = supply_voltage;
    return ENOERR;
}

// Return true if the illumination (pakring lights) are turned off, otherwise false
// Valid voltage are between 0V and 15V. Anything below 1.7v is considered day lignt
// Note: There a voltage divisor on the board that divide by roughly 3.127
// 10K and 4.7K = 14.7K / 4.7K = 3.127
// So 1.7V input would read .543V and 16V would read 4.79V at the analog pin
// Note: There is no needs to use high precision function here. A simple analog read
// is good enaugh.
bool isDayLight()
{
    float v;
    v = (float)analogRead(ILLUMINATION_ANALOG_INPUT_PIN) * (5.0 / 1023.0);
    return (v < 0.5) ? true : false;
}

// If daylight is true, set all display to their maximum luminosity, dim them otherwise
void setDayLight(bool dayLight)
{
    currentDaylight = dayLight;
    for (size_t d = 0; d < display_count; d++)
    {
        selectDisplay(*displays[d]);
        displays[d]->dim(!dayLight);
    }
}

// Ensure the display intensity is set according to the current daylight status
void processDayLight()
{
    bool dayLight = isDayLight();
    if (dayLight != currentDaylight) {
        setDayLight(dayLight);
    }
}

// Update the temperature on the specified display with the specified temperature.
// If the Fahrenheit selector jumper has been present during boot time, display the
// temperature in Fahrenheit, display in Celsius otherwise.
// display: An instance of the Adafruit_SSD1306 class representing the display
//          on wich the value will be displayed
// temperature: The temperature to display, in Celsius
void updateCoolant(Adafruit_SSD1306 &display, float temperature)
{
    current_coolant_temp = temperature;
    selectDisplay(display);
    display.clearDisplay();

    // Print the coolant value and the icon according to the desired units
    display.setCursor(TEXT_POS_X, TEXT_POS_Y + 24);
    if (! temperatureUnitIsFahrenheit) {
        // Jumper not present, Display in Celsius
        drawIcon(display, Icon::coolant_icon_c, 0, 5);
        display.print(round(temperature));
    } else {
        // Jumper present. Convert to Fahrenheit
        drawIcon(display, Icon::coolant_icon_f, 0, 5);
        display.print(round(convertToFahrenheit(temperature)));
    }

    // Print the degree sign after the numeric value
    drawIcon(display, Icon::degree_sign, display.getCursorX() + 1, TEXT_POS_Y);

    // Print a warning if we have to
    if (temperature >= COOLANT_TEMP_WARNING_CELSIUS)
        drawWarning(display);

    display.display();
}

// Update the PSI on the specified display with the provided value
// display: An instance of the Adafruit_SSD1306 class representing the display
//          on wich the value will be displayed
// psi: The pressure in PSI
void updatePsi(Adafruit_SSD1306 &display, float psi)
{
    current_coolant_psi = psi;

    selectDisplay(display);
    display.clearDisplay();
    drawIcon(display, Icon::radiator_pressure_icon, 0, 3);

    // Print the PSI value
    // Move slightly the displayed value to the left if we are in warning state to give room for the warning sign
    display.setCursor(TEXT_POS_X - (psi < COOLANT_PSI_WARNING ? 0 : 10), TEXT_POS_Y + 24);
    display.print(psi, 1);

    // Print the PSI sign
    drawIcon(display, Icon::psi_sign, display.getCursorX() + 1, TEXT_POS_Y);
    
    if (psi >= COOLANT_PSI_WARNING)
        drawWarning(display);

    display.display();
}

// Update the supply voltage on the specified display with the provided value
// display: An instance of the Adafruit_SSD1306 class representing the display
//          on wich the value will be displayed
// voltage: The voltage value to display
void updateSupplyVoltage(Adafruit_SSD1306 &display, float voltage)
{
    current_supply_voltage = voltage;

    selectDisplay(display);
    display.clearDisplay();
    drawIcon(display, Icon::voltage_icon, 6, 3);

    display.setCursor(TEXT_POS_X - (voltage < 10.0 ? 0 : 8), TEXT_POS_Y + 24);
    display.print(voltage, 1);
     
     // Print the voltage sign
    drawIcon(display, Icon::voltage_sign, display.getCursorX() + 1, TEXT_POS_Y);

    if (voltage < BATTERY_VOLTAGE_LOW_WARNING || voltage > BATTERY_VOLTAGE_HIGH_WARNING)
        drawWarning(display);

    display.display();
}

// Display a small animation
// The logo width must be a multiple of 8. Typically, 8 bits in an unsigned char
void displayIntro()
{
    // The icon to use for the animation
    const Icon icon = Icon::rx8_logo;

    // Compute the size of an unsigned char in bits
    const uint8_t u_char_bits_size = sizeof(unsigned char) * __CHAR_BIT__;

    // Get a pointer to the logo bitmap array. We will need it to display only some parts of the image
    const unsigned char* logo_ptr { epd_bitmap_allArray[(uint8_t)icon] };

    // Get the logo size in pixels
    uint8_t width = pgm_read_byte(&iconSize[(uint8_t)icon].width);
    uint8_t height = pgm_read_byte(&iconSize[(uint8_t)icon].height);

    for (size_t x = u_char_bits_size - 1; x < width; x = x + u_char_bits_size)
    {
        for (size_t d = 0; d < display_count; d++)
        {
            displays[d]->clearDisplay();
        }

        for (size_t y = 0; y < height; y++)
        {
            for (size_t d = 0; d < display_count; d++)
            {
                displays[d]->drawBitmap(0, y + (display_1.height() - height) / 2, logo_ptr + y * width / u_char_bits_size  + (width - x - 1) / u_char_bits_size, x + 1, 1 ,1);
            }
        }

        for (size_t d = 0; d < display_count; d++)
        {
            selectDisplay(*displays[d]);
            displays[d]->display();
        }

        // Adjust the delay to have a smooth animation.
        // As more parts of the image is drawn, the more time it take to transfert it with i2c.
        delay((width - x) / 3);
        processDayLight();
    }

    delay(3000);
}

// Configures the Arduino IO pins
// All unused pins are put in three state with pull-ups
void configureIOs()
{
    // Set VCC as analog reference
    analogReference(DEFAULT);

    // Unused pins
    //pinMode(UNUSED_PIN_0, INPUT_PULLUP);
    pinMode(UNUSED_PIN_1, INPUT_PULLUP);
    pinMode(UNUSED_PIN_2, INPUT_PULLUP);
    pinMode(UNUSED_PIN_3, INPUT_PULLUP);
    pinMode(UNUSED_PIN_5, INPUT_PULLUP);
    pinMode(UNUSED_PIN_6, INPUT_PULLUP);
    pinMode(UNUSED_PIN_14, INPUT_PULLUP);
    pinMode(UNUSED_PIN_15, INPUT_PULLUP);

    // In use pins
    pinMode(TEMPERATURE_UNIT_SELECTOR_INPUT_PIN, INPUT_PULLUP);
    pinMode(DISPLAY_1_SELECT_OUTPUT_PIN, OUTPUT);
    pinMode(DISPLAY_2_SELECT_OUTPUT_PIN, OUTPUT);
    pinMode(DISPLAY_3_SELECT_OUTPUT_PIN, OUTPUT);
    pinMode(THERMISTOR_REFERENCE_SELECT_OUTPUT_PIN, OUTPUT);

    // Analog inputs have to be set to input (no pull-ups)
    pinMode(PSI_ANALOG_INPUT_PIN, INPUT);
    pinMode(ILLUMINATION_ANALOG_INPUT_PIN, INPUT);
    pinMode(REFERENCE_ANALOG_INPUT_PIN, INPUT);
    pinMode(COOLANT_ANALOG_INPUT_PIN, INPUT);
    pinMode(VOLTAGE_ANALOG_INPUT_PIN, INPUT);
}

// Initialize the specified display, set font, size and color
// display: An instance of the Adafruit_SSD1306 class representing the display
//          to be initialized
void initDisplay(Adafruit_SSD1306 &display)
{
    selectDisplay(display);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setFont(&FreeSans18pt7bNum);
    display.clearDisplay();
    display.display();
    forceDisplayRefresh(display);
}

void setup()
{
    configureIOs();
    for (size_t d = 0; d < display_count ; d++)
    {
        initDisplay(*displays[d]);
    }

    // Start with the high reference pull-down value
    setThermistorHighReference(true);

    // Read the onboard jumper.
    // Jupmer absent = Celsius
    // Jupmer present = Fahrenheit
    temperatureUnitIsFahrenheit = ! digitalRead(TEMPERATURE_UNIT_SELECTOR_INPUT_PIN);

    displayIntro();
}

void loop()
{
    float coolant_temp;
    float coolant_psi;
    float supply_voltage;
    bool dayLight;
    int err;

    // The following value are used to compute and enforce the refresh rate
    uint64_t startMs;
    int32_t elapsedMs;
    int32_t waitMs;

    // Sample the current timer counter
    startMs = millis();

    err = getCoolantTempCelsius(coolant_temp);
    if (err == ENOERR) {
        if (coolant_temp != current_coolant_temp)
        updateCoolant(display_1, coolant_temp);
    } else {
        displayFault(display_1);
    }

    err = getCoolantPsi(coolant_psi);
    if (err == ENOERR) {
        if (coolant_psi != current_coolant_psi)
            updatePsi(display_2, coolant_psi);
    } else {
        displayFault(display_2);
    }

    err = getSupplyVoltage(supply_voltage);
    if (err == ENOERR) {
        if (supply_voltage != current_supply_voltage)
            updateSupplyVoltage(display_3, supply_voltage);
    } else {
        displayFault(display_3);
    }

    processDayLight();

    // Wait the correct amount of time to respect the desired refresh rate
    // Note: There is no needs to take the timer overflow into account here. The timer overflows every
    //       50 days, which is much longer than a car would runs continuously
    elapsedMs = (int32_t)(millis() - startMs);
    waitMs = int32_t((int32_t)((1.0 / (float)DISPLAY_REFRESH_RATE_HZ) * 1000.0) - (int32_t)elapsedMs);
    if (waitMs > 0)
        delay(waitMs);
}
