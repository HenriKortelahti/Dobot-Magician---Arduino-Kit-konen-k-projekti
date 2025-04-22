/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-06-05
** Version:             V2.0.0
** Descriptions:        Visual recognition for DOBOT Magician
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "SmartKit.h"

static int start_run = 0;
static int fixed_r = -135;        // Työkalun kääntö, jotta pumpun letku ei ole kameran edessä.
static int timer = 0;

void setup()
{
    Serial.begin(115200);
    SmartKit_VISSetAT(177.5512, -149.8084, 91.3197, fixed_r);
    SmartKit_VISSetPixyMatrix(188, 136, 42, 37, 172, 72, 38, 37, 132, 139, 36, 35);
    SmartKit_VISSetColorSignature(RED, 1);
    SmartKit_VISSetColorSignature(GREEN, 2);
    SmartKit_VISSetColorSignature(BLUE, 3);
    SmartKit_VISSetDobotMatrix(234.9246, -147.4185, 195.3470, -129.4851, 207.7654, -178.9480);	
    SmartKit_VISSetGrapAreaZ(-78);
    SmartKit_VISSetBlockTA(RED, 58.8141, -237.2399, -70, fixed_r);
    SmartKit_VISSetBlockTA(GREEN, 60.1272, -275.5655, -70, fixed_r);
    SmartKit_VISSetBlockTA(BLUE, 62.2674, -196.5721, -70, fixed_r);
    SmartKit_VISSetBlockHeight(RED, 26);
    SmartKit_VISSetBlockHeight(GREEN, 26);
    SmartKit_VISSetBlockHeight(BLUE, 26);
    SmartKit_VISInit();
    SmartKit_Init();
    Serial.println("Smart Init...");
}

bool start_timer(int timer_in)
{
  if (timer_in > 4000 || timer_in == 0)
  {
    return true;
  }
  return false;
}

void loop()
{
  Serial.print(timer);
  if (!start_timer(timer))
    timer++;
  if (start_timer(timer) && start_run == 0)
  {
    SmartKit_LedTurn(RED, ON);
    delay(200);
    SmartKit_LedTurn(RED, OFF);
    timer = 0;
    timer++;
  }
  if (start_run != 0)
  {
    SmartKit_VISRun();
  }
  if (SmartKit_ButtonCheckState(RED) == TRUE && start_run == 0)
  {
    start_run = 1;
  }
  /*if (SmartKit_ButtonCheckState(RED) == TRUE && start_run != 0)
  {
    SmartKit_LedTurn(RED, ON);
    Dobot_SetPTPJumpParams(10);
    while (SmartKit_VISGrabBlock(RED, 1, fixed_r + 45) == TRUE)
    {
        Dobot_SetPTPJumpParams(30);
        SmartKit_VISPlaceBlock(RED);
    }
    SmartKit_VISSetBlockPlaceNum(RED, 0);
  }
  else
  {
    SmartKit_LedTurn(RED, OFF);
  }*/
  if (SmartKit_ButtonCheckState(BLUE) == TRUE)
  {
    SmartKit_LedTurn(BLUE, ON);
    Dobot_SetPTPJumpParams(10);
    while (SmartKit_VISGrabBlock(BLUE, 1, fixed_r + 45) == TRUE)
    {
        Dobot_SetPTPJumpParams(30);
        SmartKit_VISPlaceBlock(BLUE);
    }
    SmartKit_VISSetBlockPlaceNum(BLUE, 0);
    //start_run = 0;
  }
  else
  {
    SmartKit_LedTurn(BLUE, OFF);
  }
  if (SmartKit_ButtonCheckState(GREEN) == TRUE)
  {
    SmartKit_LedTurn(GREEN, ON);
    Dobot_SetPTPJumpParams(10);
    while (SmartKit_VISGrabBlock(GREEN, 1, fixed_r + 45) == TRUE)
    {
        Dobot_SetPTPJumpParams(30);
        SmartKit_VISPlaceBlock(GREEN);
    }
    SmartKit_VISSetBlockPlaceNum(GREEN, 0);
  }
  else
  {
    SmartKit_LedTurn(GREEN, OFF);
  }
  /*static int flag = 0;
  static int Zflag = 1;
  int x = 0, y = 0, z = 0, b1 = 0, b2 = 0, b3 = 0;
  int direction = 0;                                                //The direction of JoyStick
  x = SmartKit_JoyStickReadXYValue(AXISX);
  y = SmartKit_JoyStickReadXYValue(AXISY);
  z = SmartKit_JoyStickCheckPressState();
  b1 = SmartKit_ButtonCheckState(RED);
  b2 = SmartKit_ButtonCheckState(GREEN);
  b3 = SmartKit_ButtonCheckState(BLUE);
  if (y > 600){                                                      //JoyStick moves alongt Y-axis in the positive direction
      direction = 1;
  }
  else if (y < 400){                                                 //JoyStick moves alongt Y-axis in the negative direction
      direction = 2;
  }
  else if (x > 600){                                                 //JoyStick moves alongt X-axis in the positive direction
      direction = 3;
  }
  else if (x < 400){                                                 //JoyStick moves alongt X-axis in the negative direction
      direction = 4;
  }
  else if (b1 == 1){                                                 //press Red_Button
      direction = 5;
  }
  else if (b2 == 1){                                                 //press Green_Button
      direction = 6;
  }
  else if (b3 == 1){                                                 //press Blue_Button
      direction = 7;
  }
  else if (z == 0){                                                  //press JoyStick
      direction = 8;
  }
  switch (direction) {
  case 1:
      Serial.println("forward");
      Dobot_SetPTPCmd(MOVL_INC, 20, 0, 0, 0);                       //Dobot Magician moves forward
      Serial.print("x=");
      Serial.println(x);
      Serial.print("y=");
      Serial.println(y);
      break;
  case 2:
      Serial.println("backward");
      Dobot_SetPTPCmd(MOVL_INC, -20, 0, 0, 0);                      //Dobot Magician moves backward
      Serial.print("x=");
      Serial.println(x);
      Serial.print("y=");
      Serial.println(y);
      break;
  case 3:
      Serial.println("right");
      Dobot_SetPTPCmd(MOVL_INC, 0, -20, 0, 0);                      //Dobot Magician turns right
      Serial.print("x=");
      Serial.println(x);
      Serial.print("y=");
      Serial.println(y);
      break;
  case 4:
      Serial.println("left");
      Dobot_SetPTPCmd(MOVL_INC, 0, 20, 0, 0);                       //Dobot Magician turns left
      Serial.print("x=");
      Serial.println(x);
      Serial.print("y=");
      Serial.println(y);
      break;
  case 5:
      Serial.println("down");
      Dobot_SetPTPCmd(MOVL_INC, 0, 0, -20, 0);                       //Dobot Magician moves down
      Serial.print("x=");
      Serial.println(x);
      Serial.print("y=");
      Serial.println(y);
      break;
  case 6:
      Serial.println("up");
      Dobot_SetPTPCmd(MOVL_INC, 0, 0, 20, 0);                       //Dobot Magician moves up
      Serial.print("x=");
      Serial.println(x);
      Serial.print("y=");
      Serial.println(y);
      break;
  case 7:
      if (flag){                                               //whether Blue_Button the first time is pressed
          Dobot_SetEndEffectorSuctionCup(false);
          Serial.println("Turn off the air pump");
          flag = !flag;
      }
      else{
          Dobot_SetEndEffectorSuctionCup(true);
          Serial.println("Turn on thr air pump");
          flag = !flag;
      }
      break;
  case 8:
      if (Zflag){                                              //whether JoyStick the first time is pressed
          Dobot_SetPTPCommonParams(100, 100);
          Serial.println("Accelerate");
          Zflag = !Zflag;
      }
      else{
          Dobot_SetPTPCommonParams(20, 20);
          Serial.println("Decelerate");
          Zflag = !Zflag;
      }
      break;
  }*/
}


