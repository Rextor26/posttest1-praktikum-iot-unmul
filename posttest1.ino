// Inisialisasi Pin LED dan BUZZER

//PIN BUZZER dan LED
const int led = D4;
const int buzzer = D8;

// PIN Button Enable dan Disable
const int buzzer_onOf = D3;
const int onOf_led = D7;

// Button untuk kontrol cerah dan redup led
const int button_cerah = D5; 
const int button_redup = D6;

// BUtton untuk kontol Volume Buzzer
const int button_keras = D2; 
const int button_pelan = D1;



// Inisialisasi Variabel dan Nilai
int on_led = 0;
int on_buzzer = 0;
int add;
int minus;
int volume_tambah;
int volume_kurang;
int kecerahan = 10;
int status_kecerahan = 15;
int frequensi = 0;
int status_frequensi = 100;
int cerah = 250;
int redup = 0;
int kelipatan = 5;
int max_volume_buzzer = 2500;
int min_volume_buzzer = 105;



void setup() {
  Serial.begin(9600);
  
  // Inisialisasi pin
  pinMode(led, OUTPUT);
  pinMode(onOf_led, INPUT_PULLUP);
  pinMode(button_cerah, INPUT_PULLUP);
  pinMode(button_redup, INPUT_PULLUP);
  pinMode(buzzer_onOf, INPUT_PULLUP);
  pinMode(button_keras, INPUT_PULLUP);
  pinMode(button_pelan, INPUT_PULLUP);
}

void loop() {
  
  // Variabel Button
  add = digitalRead(button_cerah);
  minus = digitalRead(button_redup);
  volume_tambah = digitalRead(button_keras);
  volume_kurang = digitalRead(button_pelan);

  //ON / OF LED
  if ( digitalRead(onOf_led) == LOW && on_led == 0 ) {// Kondisi Button Mati
    on_led = 1;
    kecerahan = status_kecerahan;
    Serial.println(on_led);
  } else if ( digitalRead(onOf_led) == LOW && on_led == 1 ) {// Kondisi Button Nyala
    on_led = 0;
    status_kecerahan = kecerahan;
    kecerahan = 0;
    Serial.println(on_led);
  }

 // Tingkat Kecerahan dan Redup LED
  if ( add == LOW && kecerahan < cerah && on_led == 1 ) {
    kecerahan += kelipatan;
    Serial.println(kecerahan);
  }else if ( add == LOW && kecerahan >= cerah && on_led == 1 ) {
    kecerahan = 250;
    Serial.println(kecerahan);
  }else if ( minus == LOW && kecerahan > redup && on_led == 1 ) {
    kecerahan -= kelipatan;
    Serial.println(kecerahan);
  }else if ( minus == LOW && kecerahan <= redup && on_led == 1 ) {
    kecerahan = 0;
    Serial.println(kecerahan);
  }

  // ON / OF BUZZER
  if ( digitalRead(buzzer_onOf) == LOW && on_buzzer == 0 ) { // Kondisi Button Buzzer Nyala
    on_buzzer = 1;
    frequensi = status_frequensi;
    Serial.println(on_buzzer);
  } else if ( digitalRead(buzzer_onOf) == LOW && on_buzzer == 1 ) { // Kondisi Button Buzzer Mati
    on_buzzer = 0;
    status_frequensi = frequensi;
    frequensi = 0;
    Serial.println(on_buzzer);
  }

  //Volume Buzzer
  if ( volume_tambah == LOW && frequensi < max_volume_buzzer && on_buzzer == 1 ) {
    frequensi += kelipatan;
    Serial.println(frequensi);
  }else if ( volume_tambah == LOW && frequensi >= max_volume_buzzer && on_buzzer == 1 ) {
    frequensi = 2500;
    Serial.println(frequensi);
  }else if ( volume_kurang == LOW && frequensi > min_volume_buzzer && on_buzzer == 1 ) {
    frequensi -= kelipatan;
    Serial.println(frequensi);
  }else if ( volume_kurang == LOW && frequensi <= min_volume_buzzer && on_buzzer == 1 ) {
    frequensi = 100;
    Serial.println(frequensi);
  }
    


  delay(300);
  analogWrite(led, kecerahan);
  analogWrite(buzzer, frequensi);
}
