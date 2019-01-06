#include <Adafruit_SSD1306.h>
#include <splash.h>


int toneFrequency = 261; //Frequency of tone to play
int incrementAmt = 5; //Increment amount for tone adjustment buttons
int adjustIncrementBtn = 13; //Btn to adjust increment/decrement of other 2 buttons
int incrementBtn = 12; //Button to increase Frequency
int decrementBtn = 11; //Button to decrease Frequency
int playBtn = 10; //Button to play tone
int buzzerPin = 9; //Passive piezo buzzer
Adafruit_SSD1306 display(128, 32, &Wire, -1); //Defines the display object


//Will display the current frequency on the LCD
void updateDisplay() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(F("F: "));
    display.print(toneFrequency);
    display.println(F("Hz"));
    display.print("-");
    display.print(incrementAmt);
    display.println("+");
    display.display();
}

void setup() {
    //Set all buttons as inputs using pull up resistors
    pinMode(incrementBtn, INPUT_PULLUP);
    pinMode(decrementBtn, INPUT_PULLUP);
    pinMode(playBtn, INPUT_PULLUP);
    pinMode(incrementBtn, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Set up display
    updateDisplay(); //Display initial frequency on the display
}

void loop() {
    if(digitalRead(incrementBtn) == LOW){
        toneFrequency += incrementAmt;
        updateDisplay();
    }
    else if(digitalRead(decrementBtn) == LOW){
        toneFrequency -= incrementAmt;
        updateDisplay();
    }
    else if(digitalRead(playBtn) == LOW){
        while(digitalRead(playBtn) == LOW)
        {
            int pulse_width = (1000000/toneFrequency)/2;
            digitalWrite(buzzerPin, HIGH);
            delayMicroseconds(pulse_width);
            digitalWrite(buzzerPin, LOW);
            delayMicroseconds(pulse_width);
        }
    }
    else if(digitalRead(adjustIncrementBtn) == LOW){
        switch(incrementAmt){
            case 1:
                incrementAmt = 2;
                break;
            case 2:
                incrementAmt = 5;
                break;
            case 5:
                incrementAmt = 10;
                break;
            case 10:
                incrementAmt = 1;
                break;
        }
        updateDisplay();
        while(digitalRead(adjustIncrementBtn) == LOW){

        }
    }
    delay(500);
}
