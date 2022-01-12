

/******************************************************************
 * HCDER
 * Constants, libraries, etc
/*****************************************************************/

// LIGHTS
const int RED_PIN = 9; //fitness
const int GREEN_PIN = 10; //mood ring
const int BLUE_PIN = 11;//productivity

const int DISPLAY_TIME = 1000;  // used in mainColors() to determine the 
// length of time each color is displayed.
char currentColor;

// TEMPERATURE
const int temperaturePin = A0;
float myTemp = 0;
float myAverageTemp = 0;

// MOODS
char myMood;
char boundR; //--->PURPLE
char boundB; // Sad or Calm -----> BLUE
char boundD; // Neutral Down---> TEAL
char boundN;  // Neutral  ------> GREEN
char boundU;  // Neutral Up ----> YELLOW
char boundO; // Happy or Anxious ----> ORANGE
char boundC; // Excited or Angry ----> RED

int boundR_Purple[3] = { 149,0,179 }; //--->PURPLE
int boundB_Blue[3] = { 0,0,255 }; // Sad or Calm -----> BLUE
int boundD_Teal[3] = { 84,255,209 }; // Neutral Down---> TEAL
int boundN_Green[3] = { 0,255,0 };  // Neutral  ------> GREEN
int boundU_Yellow[3] = { 255,255,51 };  // Neutral Up ----> YELLOW
int boundO_Orange[3] = { 255,166,77 }; // Happy or Anxious ----> ORANGE
int boundC_Red[3] = { 255,0,0 }; // Excited or Angry ----> RED

 /******************************************************************
  * SETUP
  * Declare inputs and outputs
 /*****************************************************************/

void setup()  //Configure the Arduino pins to be outputs to drive the LEDs
{
    // Light Output
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    // Temperature Input
    Serial.begin(9600); //Initialize serial port & set baud rate to 9600 bits per second (bps)
}

void loop()
{
    // Measures the average temperature for the first 2 minutes
    if (myAverageTemp == 0) {

        float totalTemp = 0;
        for (int x = 30; x > 0; x--) {
            totalTemp += temperature();
            // Display reading mode
            digitalWrite(RED_PIN, HIGH);
            digitalWrite(GREEN_PIN, LOW);
            digitalWrite(BLUE_PIN, HIGH);
            delay(500);
        }

        // SETTING ALL BASELINE TEMPERATURES
        myAverageTemp = totalTemp / 30;

        boundR = myAverageTemp - 3;
        boundB = myAverageTemp - 2; // Sad or Calm -----> BLUE
        boundD = myAverageTemp - 1; // Neutral Down---> TCL
        boundN = myAverageTemp; // Neutral  ------> GREEN
        boundU = myAverageTemp + 1; // Neutral Up ----> YELLOW
        boundO = myAverageTemp + 2; // Happy or Anxious ----> ORANGE
        boundC = myAverageTemp + 3; // Excited or Angry ----> RED
    }

    // TEMPERATURE
    myTemp = temperature();

    // GET COLOR WITH TEMPERATURE (DICTIONARY)
   // myMood = switchMood(myTemp);
    DisplayMood(myTemp);
    // myMood color transition
  //  transitionColor(currentColor, myMood);
    //currentColor = myMood;

    // PRINT LOG       
   //printLog(char myMood);

}

/******************************************************************
 * void temperature()
 * This function executes the reading and celsius transformation
/*****************************************************************/

void DisplayMood(float myTemp) {

    if (myTemp > boundR && myTemp <= boundB) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 255);
        delay(10);
    }

    else if (myTemp <= boundD) {
        analogWrite(RED_PIN, 84);
        analogWrite(GREEN_PIN, 255);
        analogWrite(BLUE_PIN, 209);
        delay(10);
    }
    else if (myTemp <= boundN) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 255);
        analogWrite(BLUE_PIN, 0);
        delay(10);
    }
    else if (myTemp <= boundU) {
        analogWrite(RED_PIN, 255);
        analogWrite(GREEN_PIN, 255);
        analogWrite(BLUE_PIN, 51);
        delay(10);
    }
    else if (myTemp <= boundO) {
        analogWrite(RED_PIN, 255);
        analogWrite(GREEN_PIN, 166);
        analogWrite(BLUE_PIN, 77);
        delay(10);
    }
    else if (myTemp <= boundC) {
        analogWrite(RED_PIN, 255);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 0);
        delay(10);
    } // C for Crimson
    else {
        analogWrite(RED_PIN, 149);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 179);
        delay(10);
    }

}


char switchMood(float myTemp) {

    if (myTemp > boundR && myTemp <= boundB) { return 'B'; }
    else if (myTemp <= boundD) { return 'D'; }
    else if (myTemp <= boundN) { return 'N'; }
    else if (myTemp <= boundU) { return 'U'; }
    else if (myTemp <= boundO) { return 'O'; }
    else if (myTemp <= boundC) { return 'C'; } // C for Crimson
    else { return 'R'; }

}

void transitionColor(char currentColor, char myMood) {
    int currentLight[3] = { 0,0,0 };
    int nextLight[3] = { 0,0,0 };

    if (currentColor == 'R') {
        currentLight[1] = 255;
        currentLight[2] = 255;
        currentLight[3] = 255;
        //  currentLight[1] = boundR_Purple[1];
        //  currentLight[2] = boundR_Purple[2];
        //  currentLight[3] = boundR_Purple[3];
    }
    else if (currentColor == 'B') {
        currentLight[1] = boundB_Blue[1];
        currentLight[2] = boundB_Blue[2];
        currentLight[3] = boundB_Blue[3];
    }
    else if (currentColor == 'D')
    {
        currentLight[1] = boundD_Teal[1];
        currentLight[2] = boundD_Teal[2];
        currentLight[3] = boundD_Teal[3];
    }
    else if (currentColor == 'N') {
        currentLight[1] = boundN_Green[1];
        currentLight[2] = boundN_Green[2];
        currentLight[3] = boundN_Green[3];
    }
    else if (currentColor == 'U') {
        currentLight[1] = boundU_Yellow[1];
        currentLight[2] = boundU_Yellow[2];
        currentLight[3] = boundU_Yellow[3];
    }
    else if (currentColor == 'O') {
        currentLight[1] = boundO_Orange[1];
        currentLight[2] = boundO_Orange[2];
        currentLight[3] = boundO_Orange[3];
    }
    else if (currentColor == 'C') {
        currentLight[1] = boundC_Red[1];
        currentLight[2] = boundC_Red[2];
        currentLight[3] = boundC_Red[3];
    }
    else {
        //  currentLight[1] = boundR_Purple[1];
         // currentLight[2] = boundR_Purple[2];
         // currentLight[3] = boundR_Purple[3];
        currentLight[1] = 255;
        currentLight[2] = 255;
        currentLight[3] = 255;
    }


    if (myMood == 'R') {
        nextLight[1] = 255;
        nextLight[2] = 255;
        nextLight[3] = 255;
        //nextLight[1] = boundR_Purple[1];
       // nextLight[2] = boundR_Purple[2];
       // nextLight[3] = boundR_Purple[3];
    }
    else if (myMood == 'B') {
        nextLight[1] = boundB_Blue[1];
        nextLight[2] = boundB_Blue[2];
        nextLight[3] = boundB_Blue[3];
    }
    else if (myMood == 'D')
    {
        nextLight[1] = boundD_Teal[1];
        nextLight[2] = boundD_Teal[2];
        nextLight[3] = boundD_Teal[3];
    }
    else if (myMood == 'N') {

        nextLight[1] = boundN_Green[1];
        nextLight[2] = boundN_Green[2];
        nextLight[3] = boundN_Green[3];
    }
    else if (myMood == 'U') {
        nextLight[1] = boundU_Yellow[1];
        nextLight[2] = boundU_Yellow[2];
        nextLight[3] = boundU_Yellow[3];
    }
    else if (myMood == 'O') {
        nextLight[1] = boundO_Orange[1];
        nextLight[2] = boundO_Orange[2];
        nextLight[3] = boundO_Orange[3];
    }
    else if (myMood == 'C') {
        nextLight[1] = boundC_Red[1];
        nextLight[2] = boundC_Red[2];
        nextLight[3] = boundC_Red[3];
    }
    else {
        nextLight[1] = 255;
        nextLight[2] = 255;
        nextLight[3] = 255;
        //  nextLight[1] = boundR_Purple[1];
         // nextLight[2] = boundR_Purple[2];
        //  nextLight[3] = boundR_Purple[3];
    }

    int redIntensity1 = currentLight[1];
    int greenIntensity1 = currentLight[2];
    int blueIntensity1 = currentLight[3];

    int redIntensity2 = nextLight[1];
    int greenIntensity2 = nextLight[2];
    int blueIntensity2 = nextLight[3];

    while (redIntensity1 != redIntensity2 && greenIntensity1 != greenIntensity2 && blueIntensity1 != blueIntensity2) {

        if (redIntensity1 < redIntensity2) { redIntensity1++; }
        if (redIntensity1 > redIntensity2) { redIntensity1--; }

        if (greenIntensity1 < greenIntensity2) { greenIntensity1++; }
        if (greenIntensity1 > greenIntensity2) { greenIntensity1--; }

        if (blueIntensity1 < blueIntensity2) { blueIntensity1++; }
        if (blueIntensity1 > blueIntensity2) { blueIntensity1--; }

        analogWrite(RED_PIN, redIntensity1);
        analogWrite(GREEN_PIN, greenIntensity1);
        analogWrite(BLUE_PIN, blueIntensity1);
        delay(100);
    }
}



void RGB(int color)
{
    int redIntensity;
    int greenIntensity;
    int blueIntensity;

    color = constrain(color, 0, 767); // constrain the input value to a range of values from 0 to 767

      // if statement breaks down the "color" into three ranges:
    if (color <= 255)       // RANGE 1 (0 - 255) - red to green
    {
        redIntensity = 255 - color;    // red goes from on to off
        greenIntensity = color;        // green goes from off to on
        blueIntensity = 0;             // blue is always off
    }
    else if (color <= 511)  // RANGE 2 (256 - 511) - green to blue
    {
        redIntensity = 0;                     // red is always off
        greenIntensity = 511 - color;         // green on to off
        blueIntensity = color - 256;          // blue off to on
    }
    else                    // RANGE 3 ( >= 512)- blue to red
    {
        redIntensity = color - 512;         // red off to on
        greenIntensity = 0;                 // green is always off
        blueIntensity = 767 - color;        // blue on to off
    }

    // "send" intensity values to the Red, Green, Blue Pins using analogWrite()
    analogWrite(RED_PIN, redIntensity);
    analogWrite(GREEN_PIN, greenIntensity);
    analogWrite(BLUE_PIN, blueIntensity);

}

//void printLog(char mood) {
//}

float temperature()
{

    float voltage, degreesC, degreesF; //Declare 3 floating point variables

    voltage = getVoltage(temperaturePin); //Measure the voltage at the analog pin

    degreesC = (voltage - 0.5) * 100.0; // Convert the voltage to degrees Celsius

    degreesF = degreesC * (9.0 / 5.0) + 32.0; //Convert degrees Celsius to Fahrenheit

    //Now print to the Serial monitor. Remember the baud must be 9600 on your monitor!
    // These statements will print lines of data like this:
    // "voltage: 0.73 deg C: 22.75 deg F: 72.96"

    Serial.print("  deg C: ");
    Serial.print(degreesC);
    Serial.print("   ");
    delay(1000); // repeat once per second (change as you wish!)

    return degreesC;
}


float getVoltage(int pin)   //Function to read and return
                            //floating-point value (true voltage)
                            //on analog pin 
{

    return (analogRead(pin) * 0.004882814);
    // This equation converts the 0 to 1023 value that analogRead()
    // returns, into a 0.0 to 5.0 value that is the true voltage
    // being read at that pin.
}


/******************************************************************
 * void moodColors()
 * This function allows for the LED display for the mood mode
 * Color represents emotion based on heartrate
 * blue should be calm
 * green happy
 * red angry
 * pink nervous
  */
  /*****************************************************************/
void moodColors(char myMood)
{
    //mood mode
// Red
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    delay(DISPLAY_TIME);

    // Green
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
    delay(DISPLAY_TIME);

    // Blue
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    delay(DISPLAY_TIME);

    // Yellow (Red and Green)
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
    delay(DISPLAY_TIME);

    // Cyan (Green and Blue)
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);
    delay(DISPLAY_TIME);

    // Purple (Red and Blue)
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    delay(DISPLAY_TIME);

}


/******************************************************************
 * void showSpectrum()
 *
 * Steps through all the colors of the RGB LED, displaying a rainbow.
 * showSpectrum() calls a function RGB(int color) that translates a number
 * from 0 to 767 where 0 = all RED, 767 = all RED
 *
 * Breaking down tasks down into individual functions like this
 * makes your code easier to follow, and it allows.
 * parts of your code to be re-used.
/*****************************************************************/



/******************************************************************
 * void RGB(int color)
 *
 * RGB(###) displays a single color on the RGB LED.
 * Call RGB(###) with the number of a color you want
 * to display. For example, RGB(0) displays pure RED, RGB(255)
 * displays pure green.
 *
 * This function translates a number between 0 and 767 into a
 * specific color on the RGB LED. If you have this number count
 * through the whole range (0 to 767), the LED will smoothly
 * change color through the entire spectrum.
 *
 * The "base" numbers are:
 * 0   = pure red
 * 255 = pure green
 * 511 = pure blue
 * 767 = pure red (again)
 *
 * Numbers between the above colors will create blends. For
 * example, 640 is midway between 512 (pure blue) and 767
 * (pure red). It will give you a 50/50 mix of blue and red,
 * resulting in purple.
/*****************************************************************/

// CODE SOURCES
/******************************************************************
 * SparkFun Inventor's Kit
 * Example sketch 03 -- RGB LED
 *
 * Make an RGB LED display a rainbow of colors!

 * Version 2.0 6/2012 MDG
 * Version 2.1 9/2014 BCH
 *****************************************************************/
