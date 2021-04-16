// Modul Praktikum 3 - Sistem Kendali PID kasus P
// Nama Tim :  Gemoy
// Nama Anggota 1 : Hudiya Sukma
// Nama Anggota 2 : Nadia Novemi Wilza
// Versi Program : 1.0

//pin buat sensor analog
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;
int baca_sensor[6];
int button1 = 8;
int button2 = 9;

//variabel motor
int pinEnable =4;
int pinEnable2 = 2;

//motor kiri
int motor_kiri1 = 5;
int motor_kiri2 = 6;

//motor kanan
int motor_kanan1 = 3;
int motor_kanan2 = 11;

int maxpwm = 255; //Agar output motor tidak overflow

//variabel bantuan
int x;

//Error Code
int LastError = 0; //Nilai 0 berarti tidak ada error
int error = 0;
int PID_value;
int kecepatanMotorKanan, kecepatanMotorKiri, kecepatanSetPoint = 150;

void setup(){
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
   
  pinMode(pinEnable, OUTPUT);
  pinMode(pinEnable2, OUTPUT);
  pinMode(motor_kiri1, OUTPUT);
  pinMode(motor_kiri2, OUTPUT);
  pinMode(motor_kanan1, OUTPUT);
  pinMode(motor_kanan2, OUTPUT);
  
  Serial.begin(9600);
}

void readsensor() { 
  baca_sensor[0] = analogRead(sensor1);
  baca_sensor[1] = analogRead(sensor2);
  baca_sensor[2] = analogRead(sensor3);
  baca_sensor[3] = analogRead(sensor4);
  baca_sensor[4] = analogRead(sensor5);
  baca_sensor[5] = analogRead(sensor6);
/*    
  for (x = 0; x <= 5; x++){
    Serial.println (baca_sensor[x]);
  }  
*/
}

void If_Error(){
  
 //Sensor 1 saja yang mendeteksi gelap
if (baca_sensor[0] < 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] > 34){  

    LastError = -2;
    try_PID(LastError);
   }
  
 //Sensor 2 saja yang mendeteksi gelap
if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] > 34){
  
   LastError = -1;
   try_PID(LastError);
   }

 //Sensor 3 saja yang mendeteksi gelap
if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] < 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] > 34){

  LastError = 0;

  digitalWrite(pinEnable, HIGH);
  analogWrite(motor_kiri1, 255);
  analogWrite(motor_kiri2, 0);

  digitalWrite(pinEnable2, HIGH);
  analogWrite(motor_kanan1, 255);
  analogWrite(motor_kanan2, 0);
   }

 //Sensor 4 saja yang mendeteksi gelap
if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] < 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] > 34){
  
  LastError = 0;
  try_PID(LastError);
   }
  
 //Sensor 5 saja yang mendeteksi gelap
if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] < 34 && baca_sensor[5] > 34){
  
  LastError = 1;
  try_PID(LastError);
   }  

 //Sensor 6 saja yang mendeteksi gelap
if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] < 34){
  
  LastError = 2;
  try_PID(LastError);
   }  
}

void loop(){
    
  readsensor();
  
  //Sensor 1 dan 2 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] < 34 && baca_sensor[1] < 34 && 
      baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
      baca_sensor[4] > 34 && baca_sensor[5] > 34){

    LastError = -2;
    try_PID(LastError);
  }
  //Sensor 2 dan 3 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
      baca_sensor[2] < 34 && baca_sensor[3] > 34 && 
      baca_sensor[4] > 34 && baca_sensor[5] > 34){

    LastError = -1;
    try_PID(LastError);
  }
  //Sensor 3 dan 4 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
      baca_sensor[2] < 34 && baca_sensor[3] < 34 && 
      baca_sensor[4] > 34 && baca_sensor[5] > 34){
    
    LastError = 0;

    digitalWrite(pinEnable, HIGH);
    analogWrite(motor_kiri1, 255);
    analogWrite(motor_kiri2, 0);

    digitalWrite(pinEnable2, HIGH);
    analogWrite(motor_kanan1, 255);
    analogWrite(motor_kanan2, 0);
  }
  //Sensor 4 dan 5 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
      baca_sensor[2] > 34 && baca_sensor[3] < 34 && 
      baca_sensor[4] < 34 && baca_sensor[5] > 34){
    
    LastError = 1;
    try_PID(LastError);
  }  
  //Sensor 5 dan 6 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
      baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
      baca_sensor[4] < 34 && baca_sensor[5] < 34){

    LastError = 2;
    try_PID(LastError);
  }  
  //Semua sensor mendeteksi terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
      baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
      baca_sensor[4] > 34 && baca_sensor[5] > 34){

      digitalWrite(pinEnable, HIGH);
      analogWrite(motor_kiri1, 0);
      analogWrite(motor_kiri2, 0);

      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0);
      analogWrite(motor_kanan2, 0);
  }
  If_Error();
}

void try_PID(int LastError){

//  Serial.print ("Error Sensor Detect : ");
//  Serial.println (LastError);
//  Serial.print ("\n");

  int kp = 30, ki = 0, kd = 0; // kp range = 1 - 5
  int rate = error - LastError; // 0 - (-2) = 2
  PID_value = (kp*LastError) + (kd*rate) + (ki/rate);
  kecepatanMotorKanan = kecepatanSetPoint - PID_value;//255-60 = 195
  kecepatanMotorKiri  = kecepatanSetPoint + PID_value;//255+60 = 60
  
  kecepatanMotorKiri  = constrain(kecepatanMotorKiri, 0, 255);
  kecepatanMotorKanan = constrain(kecepatanMotorKanan, 0, 255);

/*
  Serial.print ("error : ");
  Serial.print (error);
  Serial.print ("\n");
  Serial.print ("rate : ");
  Serial.print (rate);
  Serial.print ("\n");
  Serial.print ("PID : ");
  Serial.print (PID_value);
  Serial.print ("\n");
  Serial.print ("Motor Kanan : ");
  Serial.print (kecepatanMotorKanan);
  Serial.print ("\n");
  Serial.print ("Motor Kiri : ");
  Serial.print (kecepatanMotorKiri);
  Serial.print ("\n");
  delay (1000);
*/  
  digitalWrite(pinEnable, HIGH);
  analogWrite(motor_kiri1, kecepatanMotorKiri);
  analogWrite(motor_kiri2, 0);

  digitalWrite(pinEnable2, HIGH);
  analogWrite(motor_kanan1, kecepatanMotorKanan);
  analogWrite(motor_kanan2, 0);
}