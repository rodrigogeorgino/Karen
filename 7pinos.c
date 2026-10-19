#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI tela(
  U8G2_R0,
  18,  // D0 - clock
  23,  // D1 - dados
  22,  // CS
  19,  // DC
  16   // RES
);

void setup() {
  tela.begin();
  tela.clearBuffer();

  tela.setFont(u8g2_font_ncenB14_tr);
  tela.drawStr(22, 25, "KAREN");

  tela.setFont(u8g2_font_6x10_tr);
  tela.drawStr(10, 48, "Sistema iniciado");

  tela.sendBuffer();
}

void loop() {
}
