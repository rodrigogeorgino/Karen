
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LARGURA 128
#define ALTURA 64
#define RESET_OLED -1

Adafruit_SSD1306 tela(
  LARGURA, ALTURA, &Wire, RESET_OLED
);

const int bpm = 72;
const int centroY = 35;
const int intervalo = 60000 / bpm;

int x = 0;
int anteriorY = centroY;
int fase = 0;

unsigned long ultimoPasso = 0;
unsigned long ultimoBatimento = 0;
bool pico = false;

void setup() {
  Wire.begin(21, 22);

  if (!tela.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) delay(2);
  }

  tela.clearDisplay();
  tela.setTextColor(SSD1306_WHITE);
}

void loop() {
  unsigned long agora = millis();

  // Gera um batimento simulado a cada intervalo
  if (agora - ultimoBatimento >= intervalo) {
    ultimoBatimento = agora;
    pico = true;
    fase = 0;
  }

  // Velocidade de desenho da linha
  if (agora - ultimoPasso < 10) return;
  ultimoPasso = agora;

  int y = centroY;

  if (pico) {
    // Forma do pulso cardíaco
    const int onda[] = {0, -3, -15, 25, -30, 8, 0, 0};
    const int tamanho = sizeof(onda) / sizeof(onda[0]);

    y = centroY + onda[fase];

    fase++;
    if (fase >= tamanho) {
      pico = false;
      y = centroY;
    }
  }

  // Cabeçalho
  tela.fillRect(0, 0, 128, 13, SSD1306_BLACK);
  tela.setTextSize(1);
  tela.setCursor(0, 3);
  tela.print("KAREN BPM");

  tela.setCursor(83, 3);
  tela.print(bpm);
  tela.print(" OK");

  // Desenha a linha contínua
  tela.drawLine(x - 1, anteriorY, x, y, SSD1306_WHITE);

  anteriorY = y;
  x++;

  if (x >= 128) {
    x = 0;
    anteriorY = centroY;
    tela.fillRect(0, 14, 128, 50, SSD1306_BLACK);
  }

  tela.display();
}
