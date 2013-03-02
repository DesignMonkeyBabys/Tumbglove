/*!
 * Tumblglove - A awesome glove for Tumblr.
 * https://github.com/DesignMonkeyBabys/Tumbglove
 *
 * Released under the MIT license
 * Copyright 2013 ynakajima and satoshin2017
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

// Flex sensor pin
const int sensorPin = 0;
int currentValue = 0;

//for reblog
const int pressSensorPin = 1;
int pressCurrentValue = 0;
char altKey = KEY_LEFT_ALT;

void setup() {
  while(!Serial); //シリアルモニタが開いていたらループ開始
  Serial.begin(9600); //シリアルポートを9600bpsで開く
 Keyboard.begin();
}

void loop() {
 // read Flex sensor value
 int value = analogRead(sensorPin);
 Serial.println(value); //とりあえず出力
 if (value > 430 && currentValue <= 430) {
   // LIKE!
   Keyboard.write('l');
 }
 currentValue = value; 
 // wait
 delay(100);
 
 //reblog
 int pressVal = analogRead(pressSensorPin); //曲センサーの値を読み取る
  Serial.println(pressVal); //とりあえず出力
  if(pressVal > 900 && pressCurrentValue <= 900){
    //Reblog
    Keyboard.press(altKey);
    Keyboard.press('r');
    Keyboard.releaseAll();
  }
  pressCurrentValue = pressVal;
  delay(100);
 
 
 
}
