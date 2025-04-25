#include <LiquidCrystal.h>

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 3);

// Pinos sensores/atuadores
const int LED_VERDE = 4;
const int LED_AMARELO = 5;
const int LED_VERMELHO = 6;
const int BUZZER = 7;
const int LDR = A0;
int pegarLuz = 0;
int mediaLuz = 0;
int contMedia = 0;

// Controle de buzzer
unsigned long tempoAlarme = 0;
bool buzzerTocando = false;
bool jaSoouNaZonaVermelha = false;

// Blocos da logo "Datavine"
byte bloco1[8] = { B00111, B00011, B00000, B00111, B00100, B01110, B01010, B01110 };
byte bloco2[8] = { B11001, B11011, B00100, B11111, B00100, B01110, B01010, B01110 };
byte bloco3[8] = { B00000, B00000, B00000, B11100, B00100, B01110, B01010, B01110 };
byte bloco4[8] = { B00111, B00101, B00111, B00000, B00000, B00000, B00000, B00000 };
byte bloco5[8] = { B00000, B11111, B00000, B01110, B01010, B01110, B00000, B00000 };
byte bloco6[8] = { B11100, B10100, B11100, B00000, B00000, B00000, B00000, B00000 };
byte folha[8]  = { B00000, B00010, B00101, B01010, B01100, B00100, B00010, B00000 };

// ---------- FUNÇÕES DE ANIMAÇÃO LCD ----------

void desenharLogo() {
  lcd.setCursor(0, 0);
  lcd.write(byte(0)); lcd.write(byte(1)); lcd.write(byte(2));
  lcd.setCursor(0, 1);
  lcd.write(byte(3)); lcd.write(byte(4)); lcd.write(byte(5));
}

void animarEntradaLogo() {
  lcd.setCursor(0, 0); lcd.write(byte(0)); delay(200);
  lcd.setCursor(1, 0); lcd.write(byte(1)); delay(200);
  lcd.setCursor(2, 0); lcd.write(byte(2)); delay(200);
  lcd.setCursor(0, 1); lcd.write(byte(3)); delay(200);
  lcd.setCursor(1, 1); lcd.write(byte(4)); delay(200);
  lcd.setCursor(2, 1); lcd.write(byte(5)); delay(200);
}

void limparTextoLinha1() {
  lcd.setCursor(5, 0);
  for (int i = 0; i < 11; i++) lcd.print(" ");
}

void mostrarTextoComFolha(String texto, int porcentagem) {
  int colunaFolha = 3;

  for (int i = 0; i < texto.length(); i++) {
    lcd.setCursor(i + 5, 0);
    lcd.print(texto[i]);

    if (colunaFolha > 3) {
      lcd.setCursor(colunaFolha - 1, 1);
      lcd.print(" ");
    }
    lcd.setCursor(colunaFolha, 1);
    lcd.write(byte(6));
    colunaFolha++;
    delay(150);
  }

  lcd.setCursor(colunaFolha - 1, 1);
  lcd.print(" ");

  // Mostra a porcentagem no canto direito da linha de baixo
  lcd.setCursor(10, 1);
  lcd.print(String(porcentagem) + "%   ");
}

// ---------- SETUP PRINCIPAL ----------

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);

  lcd.createChar(0, bloco1);
  lcd.createChar(1, bloco2);
  lcd.createChar(2, bloco3);
  lcd.createChar(3, bloco4);
  lcd.createChar(4, bloco5);
  lcd.createChar(5, bloco6);
  lcd.createChar(6, folha);

  animarEntradaLogo();

  for (int i = 0; i < 3; i++) {
    delay(400);
    lcd.noDisplay(); delay(200);
    lcd.display();
  }

  desenharLogo();

  for (int i = 0; i < 8; i++) {
    lcd.setCursor(i + 5, 0);
    lcd.print("DATAVINE"[i]);
    delay(150);
  }

  delay(2000);
}

// ---------- LOOP PRINCIPAL ----------

void loop() {
  int valorLDR = analogRead(LDR);
  int porcentagem = map(valorLDR, 0, 1023, 0, 100);

  Serial.print("Valor LDR: ");
  Serial.print(valorLDR);
  Serial.print(" | Luminosidade: ");
  Serial.print(porcentagem);
  Serial.println("%");

  desenharLogo(); // mantém a logo no canto
  limparTextoLinha1();

  if (porcentagem <= 30) {
    Serial.println("Status: OK (LED VERDE)");
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
    buzzerTocando = false;
    jaSoouNaZonaVermelha = false;
    mostrarTextoComFolha("OK", porcentagem);
    pegarLuz = porcentagem;
  } 
  else if (porcentagem > 30 && porcentagem <= 50) {
    Serial.println("Status: Alerta (LED AMARELO)");
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
    buzzerTocando = false;
    jaSoouNaZonaVermelha = false;
    mostrarTextoComFolha("Alerta", porcentagem);
    pegarLuz = porcentagem;
  } 
  else {
    Serial.println("Status: Perigo (LED VERMELHO + BUZZER UMA VEZ)");
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    if (!jaSoouNaZonaVermelha && !buzzerTocando) {
      tone(BUZZER, 1000);
      tempoAlarme = millis();
      buzzerTocando = true;
      jaSoouNaZonaVermelha = true;
      pegarLuz = porcentagem;
    }

    if (buzzerTocando && millis() - tempoAlarme >= 3000) {
      noTone(BUZZER);
      buzzerTocando = false;
    }

    mostrarTextoComFolha("Perigo", porcentagem);
  }

  mediaLuz = mediaLuz + pegarLuz;
  contMedia++;
  delay(1000);
  if (contMedia == 10){
    mediaLuz = mediaLuz / 10;
    Serial.print("Sua média de porcentagens é: ");
    Serial.print(mediaLuz);
    Serial.println("%");
    mediaLuz = 0;
    contMedia = 0;
    pegarLuz= 0;
    delay(600);
  }
}
