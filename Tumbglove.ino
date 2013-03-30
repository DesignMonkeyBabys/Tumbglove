/*!
 * Tumblglove - A awesome glove for Tumblr.
 * https://github.com/DesignMonkeyBabys/Tumbglove
 *
 * Released under the MIT license
 * Copyright 2013 ynakajima and satoshin2071
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
//sensor pin
const int flexSensorPin = 0;
const int pressSensorPin = 1;
const int xAxisPin = 2;
const int yAxisPin = 3;

//sensor base value
const int flexBaseVal = 430;
const int pressBaseVal = 900;

//for like
int flexCurrentValue = 0;
//for reblog
int pressCurrentValue = 0;
char altKey = KEY_LEFT_ALT;
//for prev next
int isXYZLocked = 0;

void setup() {
  //while(!Serial); //シリアルモニタが開いていたらループ開始
  //Serial.begin(9600); //シリアルポートを9600bpsで開く
  Keyboard.begin();
}

void loop() {
  int flexVal = analogRead(flexSensorPin);
  //Serial.println(flexVal); //for Debug
  int pressVal = analogRead(pressSensorPin); 
  //Serial.println(pressVal); //for Debug

  /** 
   *like 
   */
  if (flexVal > flexBaseVal && flexCurrentValue <= flexBaseVal) {
    Keyboard.write('l');
  }
  flexCurrentValue = flexVal; 
  delay(100);

  /**
   *reblog 
   */
  if(pressVal > pressBaseVal && pressCurrentValue <= pressBaseVal){
    Keyboard.press(altKey);
    Keyboard.press('r');
    Keyboard.releaseAll();
  }
  pressCurrentValue = pressVal;
  delay(100);

  /**
   * PrevNext
   */
  // read XY sensor value 
  int xAxisValue = analogRead(xAxisPin); 
  int yAxisValue = analogRead(yAxisPin);

  // 読み取った値を-1から1までの範囲にスケーリングしてsinθの値とする
  float xAxisSinTheta = mapInFloat(xAxisValue, 306, 716, -1, 1);
  float yAxisSinTheta = mapInFloat(yAxisValue, 306, 716, -1, 1);

  // それぞれの値を-1から1までの範囲に制限する
  xAxisSinTheta = constrain(xAxisSinTheta, -1, 1);
  yAxisSinTheta = constrain(yAxisSinTheta, -1, 1);

  // 逆サインを求めた結果（単位はラジアン）を度に変換
  int xAxisTilt = floor(asin(xAxisSinTheta) * 180 / PI);
  int yAxisTilt = floor(asin(yAxisSinTheta) * 180 / PI);

  // 傾きによってページ送り処理を行う
  if (xAxisTilt > -40 && xAxisTilt < 20 && yAxisTilt < -60 && isXYZLocked == 0) {
    Keyboard.write('k');
    isXYZLocked = 1;
  } 
  else if (xAxisTilt > -40 && xAxisTilt < 20 && yAxisTilt > 55 && isXYZLocked == 0) {
    Keyboard.write('j');
    isXYZLocked = 1;
  } 
  else if ((yAxisTilt > -40 && yAxisTilt < 10) || (yAxisTilt < 20 && yAxisTilt > 15)) {
    isXYZLocked = 0; 
  }
  // wait
  delay(30);
}

// 標準で用意されているmapは引数と戻り値の型がlongである
// 今回は-1から1までにスケーリングする必要があるためfloatで同じ計算をする
float mapInFloat(float x, float iMin, float iMax, float oMin, float oMax) {
  return (x - iMin) * (oMax - oMin) / (iMax - iMin) + oMin;
}



