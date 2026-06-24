#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal main_lcd(12, 11, 10, 9, 8, 7);

const byte K_LINII = 4;
const byte K_COLS = 4;
byte l_pins[K_LINII] = {5, 4, 3, 2};
byte c_pins[K_COLS] = {A3, A2, A1, A0};
char p_map[K_LINII][K_COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'.', '0', '=', '/'}
};

Keypad custom_keys = Keypad(makeKeymap(p_map), l_pins, c_pins, K_LINII, K_COLS);

char operatormatematica = 0;
String num1 = "";
String num2 = "";

void rulare_ecran(){
  String tag1 = "UNIBUC FMI 2026";
  for (byte i = 0; i < tag1.length(); i++){
    main_lcd.print(tag1[i]);
    delay(100);
  }
  delay(1000);
  main_lcd.clear();
  String tag2 = "Rusanescu";
  for (byte i = 0; i < tag2.length(); i++){
    main_lcd.print(tag2[i]);
    delay(100);
  }
  main_lcd.setCursor(0, 1);
  String tag3 = "Gabriel";
  for (byte i = 0; i < tag3.length(); i++){
    main_lcd.print(tag3[i]);
    delay(100);
  }
  delay(2000);
}

void sync_blink(){
  if (millis() / 300 % 2 == 0){
    main_lcd.cursor();
  } else {
    main_lcd.noCursor();
  }
}

double operatiemate(char type, double a, double b){
  if (type == '+') return a + b;
  if (type == '-') return a - b;
  if (type == '*') return a * b;
  if (type == '/'){
    if(b == 0){
      main_lcd.clear();
      main_lcd.print("S-a incercat");
      main_lcd.setCursor(0, 1);
      main_lcd.print("impartirea la 0");
      delay(2500);
      main_lcd.clear();
      return 0;
    }
    return a / b;
    }
  return 0;
}

void proces_tasta(char k){
  if (k == '-' && num2 == ""){
    num2 = "-";
    main_lcd.print("-");
    return;
  }

  if (k == '+' || k == '-' || k == '*' || k == '/'){
    if (!operatormatematica){
      num1 = num2;
      num2 = "";
    }
    operatormatematica = k;
    main_lcd.setCursor(0, 1);
    main_lcd.print(k);
    main_lcd.setCursor(num2.length() + 1, 1);
    return;
  }

  if (k == '='){
    double val_a = num1.toDouble();
    double val_b = num2.toDouble();
    num1 = String(operatiemate(operatormatematica, val_a, val_b));
    num2 = "";
    main_lcd.clear();
    main_lcd.setCursor(1, 0);
    main_lcd.print(num1);
    main_lcd.setCursor(0, 1);
    main_lcd.print(operatormatematica);
    return;
  }

  if (k == '.' && num2.indexOf('.') >= 0){
    return;
  }
  if (k == '.' || num2 != "0"){
    num2 += String(k);
  } else{
    num2 = String(k);
  }

  main_lcd.print(k);
}

void setup(){
  Serial.begin(115200);
  main_lcd.begin(16, 2);
  rulare_ecran();
  main_lcd.clear();
  main_lcd.cursor();
  main_lcd.setCursor(1, 0);
}

void loop(){
  sync_blink();
  char input = custom_keys.getKey();
  if (input){
    proces_tasta(input);
  }
}