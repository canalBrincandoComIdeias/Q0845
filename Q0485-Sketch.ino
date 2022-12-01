/*
     CÓDIGO:    Q0485
     AUTOR:     BrincandoComIdeias
     ACOMPANHE: https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
     APRENDA:   https://cursodearduino.net/ ; https://cursoderobotica.net
     COMPRE:    https://www.arducore.com.br/
     SKETCH:    Random (Dezenas para Megasena)
     DATA:      19/02/2022
*/
#define DEBUG true
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
#if DEBUG == true
  Serial.begin(9600);
#endif

  lcd.init();
  lcd.backlight();
  lcd.print("NUMEROS DA SORTE");

  randomSeed(analogRead(0));

  lcd.setCursor(0, 1);
  lcd.print("procurando");

  int numeros[6];
  for (int nL = 0; nL <= 5; nL++) {

    bool achado = false;
    while (!achado) {
      int numero = random(1, 61);

      //verifica se já foi sorteado
      bool sorteado = false;
      for (int nV = 0; nV < nL; nV++) {
        if (numeros[nV] == numero) {
          sorteado = true;
          break;
        }
      }

      if (!sorteado) {
        numeros[nL] = numero;
        achado = true;
      }
    }

    lcd.print(".");
    delay(random(2, 11) * 100);
  }

  //Ordena o Array
  int numeros_length = sizeof(numeros) / sizeof(numeros[0]);
  qsort(numeros, numeros_length, sizeof(numeros[0]), sort_array);

  lcd.setCursor(0, 1);
  for (int nL = 0; nL <= 5; nL++) {

    lcd.print(numeros[nL]);

    if ((nL < 4) || (numeros[0] < 10)) {
      lcd.print(" ");
    }
  }
}

void loop() {
}

void dbgBreakPoint(int ponto) {
#if DEBUG == true
  Serial.print("[");
  Serial.print(ponto);
  Serial.print("]");

  bool aguarda = true;
  while (aguarda) {
    while (Serial.available()) {
      Serial.read();
      aguarda = false;
    }
  }
  Serial.println(">");
#endif
}

int sort_array(const void *cmp1, const void *cmp2)
{
  int a = *((int *)cmp1);
  int b = *((int *)cmp2);
  return a < b ? -1 : (a > b ? 1 : 0);
}
