//MCP4018検証用プログラム
//抵抗の値を変化→シリアル通信で表示
#include <Wire.h>

int value = 0;

int pin0 = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(); //Wireライブラリの初期化．スレーブ用のaddressをは指定しないので．Arduino自身がマスタとしてバスに接続される．
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x2F); //指定したアドレスのI2Cスレーブに対して送信処理を始める．MCP4018のアドレスは，0101111(2)→2F(16)．
  Wire.write(value);
  Wire.endTransmission(); //スレーブデバイス(MCP4018)へのデータ送信を完了する．

  float resist = value / 127.0 * 10.0;
  float volt = pin0 / 1024.0 * 5.0;
  //Serial.print("resistor data = "); 
  //Serial.print(resist);  //抵抗値(Vss→W間)を疑似表示．キロオーム(kΩ)でシリアル出力．(最大が10kΩ，全ステップ数が128なので，左のような計算をしている．）
  //Serial.print(" kΩ ");
  Serial.print("Voltage = ");
  Serial.print(volt);
  Serial.println(" V");

  value += 5; //5ステップずつ増加させる．

  if(value > 127) //128ステップを超えたら0に戻す．
  {
    value = 0;
  }

  delay(50);
}
