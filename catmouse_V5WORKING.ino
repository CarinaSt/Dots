#include <DmxSimple.h>
#include <Controllino.h>

int redbuttonState = 0;
int bluebuttonState = 0;
int greenbuttonState = 0;
int yellowbuttonState = 0;
int debug = 0;
int state = 0;
int color1 = 0;
int rotation1 = 0;
float rotation2 = 0;
int position1 = 0;
float position2 = 0;
int colorArray1[4] = {7, 17, 43, 39};
float starttime = 0;
int presscount = 0;
float finaltime;
boolean finish = false;
int savedColor;
boolean count = false;
int timecount = 0;
boolean gameStart = true;
float highscore = 100.00;

void setup() {

  Serial.begin(57600);

  Controllino_RS485Init();
  Controllino_RS485TxEnable();

  DmxSimple.usePin(CONTROLLINO_RS485_TX);
  DmxSimple.maxChannel(20);
  starttime = millis();

}

void loop() {

  // States
  // 0 = Filling the variables with random numbers
  // 1 = Waiting for Button Interaction
  // 2 = Transition: Keep color white until projector is finished moving, then turn to state 0.

  yellowbuttonState = digitalRead(CONTROLLINO_A0);
  greenbuttonState = digitalRead(CONTROLLINO_A1);
  bluebuttonState = digitalRead(CONTROLLINO_A2);
  redbuttonState = digitalRead(CONTROLLINO_A3);


  //Variablen werden befüllt
  if (state == 0) {
    state = 1;
    color1 = random(0, 4);
    rotation1 = random(0, 150); // links rechts
    rotation2 = random(0, 150);
    position1 = random(20, 90); //hhöhhe / tilt
    position2 = random(20, 90);

    Serial.print("Farbe: " );
    Serial.println(color1 );  

    DmxSimple.write(3, colorArray1[color1]);
  }



  if (gameStart) {
    Serial.println("GAME START");
    //Starting position / Initialisierung
    DmxSimple.write(1, rotation1);
    DmxSimple.write(2, position1);
    DmxSimple.write(4, 4);
    DmxSimple.write(5, 1);
    DmxSimple.write(6, 0);
    gameStart = false;

  }
  // STATE 1: check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (presscount < 10) {

    if (color1 == 0) {
      if (yellowbuttonState == HIGH && bluebuttonState == LOW && redbuttonState == LOW && greenbuttonState == LOW) {
        // turn LED on:
        Serial.println("yellow");
        DmxSimple.write(1, rotation1);
        DmxSimple.write(2, position1);
        DmxSimple.write(3, 0);
        DmxSimple.write(4, 4);
        DmxSimple.write(5, 1);
        DmxSimple.write(6, 0);
        state = 2;
        presscount++;
      }
    }
    if (color1 == 1) {
      if (greenbuttonState == HIGH) {
        // turn LED on:
        Serial.println("green");
        DmxSimple.write(1, rotation1);
        DmxSimple.write(2, position1);
        DmxSimple.write(3, colorArray1[color1]);
        DmxSimple.write(4, 4);
        DmxSimple.write(5, 1);
        DmxSimple.write(6, 0);
        state = 2;
        presscount++;
      }
    }
    if (color1 == 2) {
      if (bluebuttonState == HIGH) {
        // turn LED on:
        Serial.println("blue");
        DmxSimple.write(1, rotation1);
        DmxSimple.write(2, position1);
        DmxSimple.write(3, colorArray1[color1]);
        DmxSimple.write(4, 4);
        DmxSimple.write(5, 1);
        DmxSimple.write(6, 0);
        state = 2;
        presscount++;
      }
    }
    if (color1 == 3) {
      if (redbuttonState == HIGH) {
        // turn LED on:
        Serial.println("red");
        DmxSimple.write(1, rotation1);
        DmxSimple.write(2, position1);
        DmxSimple.write(3, colorArray1[color1]);
        DmxSimple.write(4, 4);
        DmxSimple.write(5, 1);
        DmxSimple.write(6, 0);
        state = 2;
        presscount++;

      }
    }
    if (color1 == 4) {
      if (bluebuttonState == HIGH) {
        // turn LED on:
        Serial.println("blue");
        DmxSimple.write(1, rotation1);
        DmxSimple.write(2, position1);
        DmxSimple.write(3, colorArray1[color1]);
        DmxSimple.write(4, 4);
        DmxSimple.write(5, 1);
        DmxSimple.write(6, 0);
        state = 2;
        presscount++;
      }
    }

  }  else if (presscount = 10) {
     finish = true;
     if(finaltime < highscore){
      highscore = finaltime;
        Serial.print("New Highscore");
     }
     Serial.print("Finaltime");
   Serial.println((char)finaltime);
  Serial.print("Highscore: ");
   Serial.println(highscore);
   state = 3;
  }








  if (state == 2) {
    count = true;

    DmxSimple.write(3, 0); // Make it White

    for (int i = 0; i <= 1000; i++) {
  
      DmxSimple.write(1, rotation1);
      DmxSimple.write(2, position1);
      if (i == 1000) {

        state = 0;
      }
    }


  }


  if (finish == false) {
    finaltime = ((millis() - starttime) / 1000);
  }  else {
    //Wenn 10 Worte rum sind, zeige finale Zeit an
    Serial.print("Finaletime: ");
    Serial.println(finaltime);
  }

}
