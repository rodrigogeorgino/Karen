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
const int intervalo = 60000 / bpm; // Tempo em ms entre cada batimento

unsigned long ultimoBatimento = 0;
bool batendo = false;
int tamanhoCoracao = 0; // Controla a animação do coração (0 = normal, 1 = grande)

// Função auxiliar para desenhar um coração
void desenharCoracao(int centroX, int centroY, int tamanho) {
  // Coração pequeno
  if (tamanho == 0) {
    tela.fillCircle(centroX - 6, centroY - 5, 6, SSD1306_WHITE);
    tela.fillCircle(centroX + 6, centroY - 5, 6, SSD1306_WHITE);
    tela.fillTriangle(centroX - 12, centroY - 3, centroX + 12, centroY - 3, centroX, centroY + 13, SSD1306_WHITE);
  } 
  // Coração maior (no momento do batimento)
  else {
    tela.fillCircle(centroX - 8, centroY - 6, 8, SSD1306_WHITE);
    tela.fillCircle(centroX + 8, centroY - 6, 8, SSD1306_WHITE);
    tela.fillTriangle(centroX - 16, centroY - 4, centroX + 16, centroY - 4, centroX, centroY + 17, SSD1306_WHITE);
  }
}

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

  // Inicia um novo batimento cardíaco no tempo do BPM
  if (agora - ultimoBatimento >= intervalo) {
    ultimoBatimento = agora;
    batendo = true;
  }

  // Define o tamanho do coração (expande por 150ms a cada batimento)
  if (batendo && (agora - ultimoBatimento < 150)) {
    tamanhoCoracao = 1; // Coração grande (pulsando)
  } else {
    tamanhoCoracao = 0; // Coração normal
    batendo = false;
  }

  // Limpa o display
  tela.clearDisplay();

  // Cabeçalho (mantido igual ao original)
  tela.fillRect(0, 0, 128, 13, SSD1306_BLACK);
  tela.setTextSize(1);
  tela.setCursor(0, 3);
  tela.print("KAREN BPM");

  tela.setCursor(83, 3);
  tela.print(bpm);
  tela.print(" OK");

  // Desenha uma linha divisória abaixo do cabeçalho
  tela.drawFastHLine(0, 14, 128, SSD1306_WHITE);

  // Desenha o coração no centro da área principal (x: 64, y: 40)
  desenharCoracao(64, 40, tamanhoCoracao);

  tela.display();
}
