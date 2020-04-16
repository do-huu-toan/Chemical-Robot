
//Update 21/10/2019
/*Code by Toàn
 * Dành cho Control Slider
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "DHT.h"      
boolean quay1 = false;      
const int DHTPIN = 32;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
String data;int n;  
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3f,16,2);
unsigned long time1 = 0;
unsigned long time2 = 0;
byte tocdo = 40; 
byte relay1 = 30;
byte relay2 = 28;
byte relay3 = 26;
byte relay4 = 24;
byte nhietdo = 36;
byte khigas = 32;
//Chân điều khiển động cơ giá ống
byte inA = 46;
byte inB = 48;
boolean giabom = true; //true - trên, false - dưới
//----------------------------------------------------------------------------------------------------------------------------------------
boolean trangthai = false; 
int val;
Servo kep1;
Servo kep2;
Servo kep3;
Servo servo_cao;  
Servo servo_xa;  
Servo servo_quay; 
Servo servo_do; 
Servo servo_gap;
Servo tron;
//---------------------------------Nhiet do----------------------------------------------------------------
#include <OneWire.h>
#include <DallasTemperature.h>
 
// Chân nối với Arduino
#define ONE_WIRE_BUS 36
//Thiết đặt thư viện onewire
OneWire oneWire(ONE_WIRE_BUS);
//Mình dùng thư viện DallasTemperature để đọc cho nhanh
DallasTemperature sensors(&oneWire);
char unChar;

String readString;

void setup() { 
pinMode(inA, OUTPUT); digitalWrite(inA,LOW);
pinMode(inB, OUTPUT); digitalWrite(inB,LOW);
  // These pins have to be PWM pins for the servos to work.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pinMode(relay1, OUTPUT); digitalWrite(relay1,LOW);//bơm khí
pinMode(relay2, OUTPUT); digitalWrite(relay2,LOW);
pinMode(relay3, OUTPUT); digitalWrite(relay3,LOW);
pinMode(relay4, OUTPUT); digitalWrite(relay4,LOW);
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  servo_cao.attach(4);servo_cao.write(120);
  servo_xa.attach(3);servo_xa.write(40);
  servo_quay.attach(5);servo_quay.write(0);
  servo_do.attach(6);servo_do.write(30);
  servo_gap.attach(7);servo_gap.write(150);
  tron.attach(44);tron.write(0);
  //kep1.attach(12);kep1.write(180);
  kep2.attach(10);kep2.write(60);
  kep3.attach(11);kep3.write(180);
  Serial.begin(9600); //inisialisation of the serial
  Serial3.begin(9600); 
 
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  lcd.init();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình, cũng giống như dht.begin() trong chương trình trên
  
  lcd.backlight();   //Bật đèn nền
  //lcd.print("Robot hoa hoc");  //Xuất ra chữ Hello world, mặc định sau khi init thì con trỏ tại cột 0 hàng 0 (trong C, khác với quy ước của tiếng Việt, mọi chỉ số đều bắt đầu bằng số 0, vì vậy bạn cần hiểu rằng, nếu ta kẻ một bảng có 2 hàng và 16 cột thì ô góc trên cùng bên trái là ô (0,0) tương tự với các ô khác, ta cứ tăng dần giá trị lên!
  
  //--------------------------------NHIET DO-----------------------------------------------------------------------
  sensors.begin();
//-------------------------------------------------ĐỘNG CƠ----------------------------------------------------------

}

void loop() {
         
if ( (unsigned long) (millis() - time1) > 5000 )
    {
        float h = dht.readHumidity();    //Đọc độ ẩm
        float t = dht.readTemperature(); //Đọc nhiệt độ
         sensors.requestTemperatures(); 
        lcd.setCursor(0,1); //Đưa con trỏ tới hàng 1, cột 0
        lcd.print("Nhiet do:");// Bạn thấy trên màn hình rồi chứ? 
        lcd.print(sensors.getTempCByIndex(0));
        lcd.setCursor(0,0); //Đưa con trỏ tới hàng 1, cột 0
        //lcd.print("Nhiet do/do am:");// Bạn thấy trên màn hình rồi chứ? 
        lcd.print(t);lcd.print(" ");lcd.print(h);
        time1 = millis();
    }
 if(Serial.available()>0)
  {
  val = Serial.read();
  if (val == '1') 
    {
      if(giabom == false){dilen();giabom = true;}
      denvt3();vevt3();
    } 
    else if (val == '2') 
    {
      if(giabom == false){dilen();giabom = true;}
      denvt2();vevt2();
    }
    else if(val == '3')
    {
      quaylytam();
    }
    else if(val == '5')
    {
      FactoryReset();
    }
     else if(val == '7')
    {
      kep1.write(180);
      kep2.write(80);
      kep3.write(180);
    }
     else if(val == '8')
    {
      kep1.write(0);
      kep2.write(0);
      kep3.write(50);
    }
    else if(val == 'X')
    {
      if(giabom == true){dixuong();giabom = false;}
      bom1();
    }
    else if(val == 'Z')
    {
      if(giabom == true){dixuong();giabom = false;}
      bom2();
    }
    else if(val=='Y')
    {
      digitalWrite(relay1,HIGH);
    }
    else if(val =='T')
    {
      digitalWrite(relay1,LOW);
    }
     else if(val =='L')
    {
      if(giabom==false){dilen();giabom=true;}
    }
     else if(val =='X')
    {
      if(giabom==true){dixuong();giabom=false;}   
    }
  }

  if (Serial3.available()) {  // it identifies the firs character in serial port
    unChar = Serial3.read();
    if (unChar == 'G'){
      denvt2();
      vevt2();
    }
    if (unChar == '1'){
      kep1.write(0);
      kep2.write(0);
      kep3.write(50); 
    }
    if (unChar == '2'){
      kep1.write(180);
      kep2.write(80);
      kep3.write(180);
    }
    if (unChar == 'H'){
      denvt3();
      vevt3();
    }
    if (unChar == '3'){
      quaylytam();
    }
    if (unChar == '4'){
      servo_quay.write(150);
    }

    if (unChar == '5'){
      servo_quay.write(0);
    }
    if (unChar == '6'){
      servo_xa.write(80);
    }
    if (unChar == '7'){
      servo_xa.write(40);
    }
    
    
/*    else if(unChar == '5'){
      giam(servo_quay,tocdo,0);
    }
    else if(unChar == '6'){
      tang(servo_xa,tocdo,180);
    }
     else if(unChar == '7'){
      giam(servo_xa,tocdo,0);
    }
     else if(unChar == '0'){  
    }*/
    if (unChar == 'P'){
      digitalWrite(relay2,HIGH);
      digitalWrite(relay3,HIGH);
      digitalWrite(relay4,HIGH);
    }
    if (unChar == 'N'){
      digitalWrite(relay2,LOW);
      digitalWrite(relay3,LOW);
      digitalWrite(relay4,LOW);
    }
    if (unChar == 'M'){
      digitalWrite(relay1,HIGH);
    }
    if (unChar == 'I'){
      digitalWrite(relay1,LOW);
    }
    if (unChar == 'Y'){
      if(giabom == true){dixuong();giabom = false;}
      bomm1();
    }
    if (unChar == 'Z'){
      if(giabom == true){dixuong();giabom = false;}
      bomm2();
    }
    if (unChar == 'R'){
      trangthai = true;
    }
    else if (unChar == 'T'){
      trangthai = false;
    } 
  }
  if(trangthai = true)
    { 
      sensors.requestTemperatures();
      float h = dht.readHumidity();    //Đọc độ ẩm
      float t = dht.readTemperature(); //Đọc nhiệt độ
      Serial3.print("Nhiet do chat long:");Serial3.print(sensors.getTempCByIndex(0));Serial.print("  Nhiệt độ khí:");Serial.print(t);Serial.print("  Độ ẩm:");Serial.print(h);
    }
    else{}
}

void bomm1()
{
  delay(5);
  while (Serial3.available()) {
    //delayMicroseconds(100);
    char c = Serial3.read(); 
    readString += c;        
  }
  if (readString.length() > 0) {  
    Serial.println(readString.toInt()); 
    digitalWrite(relay2,HIGH);
    delay(readString.toInt()/0.008);
    digitalWrite(relay2,LOW);
    readString = ""; // Clear string
  }
}
void bomm2()
{
  delay(5);
  while (Serial3.available()) {
    //delayMicroseconds(100);
    char c = Serial3.read(); 
    readString += c;        
  }
  if (readString.length() > 0) {  
    Serial.println(readString.toInt()); 
    digitalWrite(relay3,HIGH);
    delay(readString.toInt()/0.006);
    digitalWrite(relay3,LOW);
    readString = ""; // Clear string
  }
}
/*void motor1() {
  delay(5);
  while (Serial3.available()) {
    //delayMicroseconds(100);
    char c = Serial3.read(); 
    readString += c;        
  }
  if (readString.length() > 0) {  
    Serial.println(readString.toInt()); 
    servo_cao.write(readString.toInt());
    readString = ""; // Clear string
  }
}

void motor2() {
  delay(5);
  while (Serial3.available()) {
    //delayMicroseconds(100);
    char c = Serial3.read();
    readString += c;
  }
  if (readString.length() > 0) {
    Serial.println(readString.toInt());
    servo_xa.write(readString.toInt());
    readString = "";
  }
}

void motor3() {
  delay(5);
  while (Serial3.available()) {
    //delayMicroseconds(100);
    char c = Serial3.read();
    readString += c;
  }
  if (readString.length() > 0) {
    Serial.println(readString.toInt());
    servo_quay.write(readString.toInt());
    readString = "";
  }
}
void motor4() {
  delay(5);
  while (Serial3.available()) {
    //delayMicroseconds(100);
    char c = Serial3.read();
    readString += c;
  }
  if (readString.length() > 0) {
    Serial.println(readString.toInt());
    servo_do.write(readString.toInt());
    readString = "";
  }
}
void motor5() {
  delay(5);
  while (Serial3.available()) {
    //delayMicroseconds(100);
    char c = Serial3.read();
    readString += c;
  }
  if (readString.length() > 0) {
    Serial.println(readString.toInt());
    servo_gap.write(readString.toInt());
    readString = "";
  }
}
//-------------------------------------------------------------------------------Phần chuyển động-----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void denvt1()
{
 reset();
 quay(servo_quay,tocdo, 100);
 quay(servo_cao,tocdo,80);
 quay(servo_gap,tocdo,150);
 quay(servo_xa,tocdo,93);
 delay(500);
 servo_gap.write(60);
 delay(1000);
 kep1.write(40);
 quay(servo_quay,tocdo,100);
 quay(servo_cao,tocdo,150);
 quay(servo_quay,tocdo,0);
 quay(servo_cao,tocdo,80);
 quay(servo_xa,tocdo,100);
 delay(100);
 quay(servo_quay,tocdo,31);
 quay(servo_do,tocdo,120);
}*/
void bom1() {
  delay(5);
  while (Serial.available()) {
    //delayMicroseconds(100);
    char c = Serial.read();
    if(c==' '){break;}
    data += c;
  }
  n=chuyenkieu(data);
  digitalWrite(relay2,HIGH);
  delay(n);
  digitalWrite(relay2,LOW);
  n=0;data=""; 
}
void bom2() {
  delay(5);
  while (Serial.available()) {
    //delayMicroseconds(100);
    char c = Serial.read();
    if(c==' '){break;}
    data += c;
  }
  n=chuyenkieu(data);
  digitalWrite(relay3,HIGH);
  delay(n); 
  digitalWrite(relay3,LOW);
  n=0;data=""; 
}
void denvt2()
{
 reset();
 quay(servo_quay,tocdo, 93);
 quay(servo_gap,tocdo,160);
 quay(servo_cao,tocdo,105);
 quay(servo_xa,tocdo,78);
 delay(500);
 quay(servo_gap,tocdo,60);
 delay(1000);
 kep2.write(0);
 quay(servo_xa,tocdo,30);
 quay(servo_cao,tocdo,120);
 delay(100);
 quay(servo_quay,tocdo,7);
 quay(servo_cao,tocdo,115);
 quay(servo_xa,tocdo,80);
 delay(500);
 quay(servo_do,tocdo,130);
 delay(2000);
}
void denvt3()
{
 reset();
 quay(servo_quay,tocdo, 77); //87,116
 quay(servo_gap,tocdo,160);
 quay(servo_cao,tocdo,110); //lúc gắp
 quay(servo_xa,tocdo,95);
 delay(500);
 quay(servo_gap,tocdo,60);
 delay(1000);
 kep3.write(50);
 delay(500);
 quay(servo_xa,tocdo,30);
 quay(servo_cao,tocdo,120);
 delay(100);
 quay(servo_quay,tocdo,5);
 quay(servo_cao,tocdo,110);
 quay(servo_xa,tocdo,80);
 delay(500);
 quay(servo_do,tocdo,130);
 delay(2000);
}
/* void vevt1()
{
 quay(servo_do,tocdo, 77);
 quay(servo_cao,tocdo,115);
 quay(servo_xa,tocdo,60);
 quay(servo_quay,tocdo, 161);
 quay(servo_xa,tocdo,84);
 quay(servo_xa,tocdo,82);
}*/
void vevt2()
{
  quay(servo_do,tocdo,33);
  quay(servo_xa,tocdo,31);
  quay(servo_cao,tocdo,120);
  quay(servo_quay,tocdo, 93);
  quay(servo_cao,tocdo,105);
  quay(servo_xa,tocdo,78);
  delay(1000);
  quay(kep2,tocdo,80);
  delay(1000);
  quay(servo_gap,tocdo,160);
  quay(servo_xa,tocdo,40);
  reset();
}
void vevt3()
{
  quay(servo_do,tocdo,32);
  quay(servo_xa,tocdo,29);
  quay(servo_cao,tocdo,120);
  quay(servo_quay,tocdo,77);
 quay(servo_cao,tocdo,110);
 quay(servo_xa,tocdo,95);
  delay(1000);
  quay(kep3,30,180);
  delay(1000);
  quay(servo_gap,tocdo,160);
  quay(servo_xa,tocdo,40);
  reset();
  
}
void reset()
{
 quay(servo_quay,tocdo,0);
 quay(servo_cao,tocdo,120);
 quay(servo_xa,tocdo,40);
 quay(servo_do,tocdo,30);
 quay(servo_gap,tocdo,150);
}
void quay(Servo s, byte tocdo, byte goc)
{
  while(s.read()<goc){
    s.write(s.read()+1);
    delay(tocdo);
  }
  while(s.read()>goc){
    s.write(s.read()-1);
    delay(tocdo);
  }
}
void FactoryReset()
{
  asm volatile ( "jmp 0");  
}
int chuyenkieu(String s)
{
  int res=0;
  for(int i=0;i<s.length();i++)
  {
    res = res*10 + s[i] - 48;
  }
  return res;
} 
void quaylytam()
{
  for(int i=1;i<=10;i++)
  {
    tron.write(180);
    delay(1000);
    tron.write(0);
    delay(1000);
  }
}
void tang(Servo s, byte tocdo, byte lim)
{
   if(s.read() >= lim){s.write(lim);}
   else {s.write(s.read()+1);}
   delay(tocdo);
}
void giam(Servo s, byte tocdo, byte lim)
{
   if(s.read() <= lim){s.write(lim);}
   else {s.write(s.read()-1);}
   delay(tocdo);
}
//----------------------------------------------GIÁ BƠM------------------------------------------------------
void dixuong(){
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  delay(3000);
  digitalWrite(inA,LOW);
  digitalWrite(inB,LOW);
}                                                                               
void dilen(){
  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  delay(3000);
  digitalWrite(inA,LOW);
  digitalWrite(inB,LOW);
}
