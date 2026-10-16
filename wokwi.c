//Display Oled 0,96 128x64 Spi Azul Amarelo Arduino 4pinos
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LARGURA 128
#define ALTURA 64
#define RESET_OLED -1
#define ENDERECO_OLED 0x3C

Adafruit_SSD1306 tela(
  LARGURA, ALTURA, &Wire, RESET_OLED
);

const int bpm = 90;
const int centroY = 39;

int x = 0;
int anteriorY = centroY;
unsigned long ultimoPasso = 0;
int fase = 0;

const int onda[] = {
  0,0,0,0,0,0,-2,-5,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  -4,-10,30,-34,12,0,-3,0,0,0,0,0
};

const int tamanhoOnda = sizeof(onda) / sizeof(onda[0]);

void setup() {
  Wire.begin(21, 22);

  if (!tela.begin(SSD1306_SWITCHCAPVCC, ENDERECO_OLED)) {
    while (true) delay(20);
  }

  tela.clearDisplay();
  tela.display();
}

void loop() {
  if (millis() - ultimoPasso < 35) return;
  ultimoPasso = millis();

  tela.fillRect(0, 0, 128, 15, SSD1306_BLACK);
  tela.setTextColor(SSD1306_WHITE);
  tela.setTextSize(1);
  tela.setCursor(0, 3);
  tela.print("KAREN");

  tela.setCursor(42, 3);
  tela.print("do Plancton");

  // Linha de monitor
  tela.drawFastHLine(0, centroY, 128, SSD1306_WHITE);

  int deslocamento = onda[fase] ;
  int y = centroY - deslocamento;

  tela.drawLine(x - 1, anteriorY, x, y, SSD1306_WHITE);

  anteriorY = y;
  x++;
  fase++;

  if (fase >= tamanhoOnda) fase = 0;

  // Indicador de BPM simulado
  tela.fillRect(0, 49, 128, 15, SSD1306_BLACK);
  tela.setCursor(0, 51);
  tela.setTextSize(2);
  tela.print(bpm);
  tela.setTextSize(1);
  tela.print(" BPM");

  if (x >= 128) {
    x = 0;
    anteriorY = centroY;
    tela.fillRect(0, 16, 128, 32, SSD1306_BLACK);
  }

  tela.display();
}

