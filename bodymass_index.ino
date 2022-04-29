#include "HX711.h"
#include <Adafruit_SSD1306.h>
const int LOADCELL_DOUT_PIN = 7;
const int LOADCELL_SCK_PIN = 6;
float BMI_height1 = 0;
#define echoPin 2
//green = 3
//blue = 2
#define trigPin 3
float BMI_height = 0;
float weight;
String reply;
long duration;
int height;
float calibration_factor = -24630;
float BMI = 0;
HX711 scale;
Adafruit_SSD1306 display(4);
int speakerPin = 8;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  Serial.println("How Fit Are You?");
  Serial.println("Initializing the set up!!");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("How Fit Are You? !!");
  display.display();
  delay(100);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  height = duration * 0.034 / 2;
  int new_height = (214-2.1-height);
    //Serial.print("your height in cms is: ");
    //Serial.println(new_height);
    if (new_height > 100) {
   tone (speakerPin, 100);
  
   } else {
    noTone (speakerPin);

  }
  //Serial.print("your height in foot is: ");
    //Serial.println(new_height*0.0328084);
    //delay(1000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(4, 4);
  display.println(height);
  //delay(100);
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  weight = scale.get_units(5);
 // Serial.print(scale.get_units(), 2);
  // Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  //Serial.print("your weight is :");
  weight = abs(weight);
  //Serial.println( weight);
  //delay(100);
  BMI_height = new_height*0.01;
  BMI_height1 =BMI_height*BMI_height;
  BMI = weight/BMI_height1;
  if(BMI >= 16 && BMI <= 40){
  Serial.print("your BMI is :");
  Serial.println(BMI);
  delay(1000);
  }
  else{
    Serial.println("wait! we are tracking you...........");
    //delay(10000);
    Serial.println("1");
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(4, 4);
  display.println(scale.get_units(5));



  display.display();
}
