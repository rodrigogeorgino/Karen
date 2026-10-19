# WOKWI
## Link do exemplo em teste: https://wokwi.com/projects/478003180485823489

> **Importante:** este projeto é apenas uma simulação visual. Não mede batimentos cardíacos reais e não deve ser utilizado para diagnóstico ou monitoramento médico.

## 🛠️ Componentes utilizados no teste

- ESP32
- Display OLED de 0,96 polegada, com resolução de 128 × 64 pixels
- Cabos jumper
- Protoboard (opcional) 

## 🔌 Ligações do display OLED

### Quando, se o display utiliza comunicação I²C com --> quatro pinos.

| OLED | ESP32 |
|---|---|
| GND | GND |
| VCC | 3V3 |
| SDA | GPIO 21 |
| SCL | GPIO 22 |


### OU quando, o display utiliza comunicação I²C com -->sete pinos.

| ESP32 | OLED |
|---|---|
| 18 | D0 |
| 23 | D1 |
| SDA | GPIO 18 |
| SCL | GPIO 23 |

**Endereço I²C utilizado:** `0x3C`

*Observação: confirme o endereço e a pinagem do seu display antes de ligar o circuito.*

## 💻 Bibliotecas necessárias

Instale as seguintes bibliotecas pela Arduino IDE:

- **Adafruit SSD1306**
- **Adafruit GFX Library**

A biblioteca `Wire.h`, utilizada na comunicação I²C, já faz parte do ambiente Arduino para ESP32.

## ⚙️ Funcionamento

O programa executa as seguintes etapas:

1. Inicializa a comunicação I²C do ESP32.
2. Configura o display OLED.
3. Desenha o título `KAREN`.
4. Exibe uma frequência cardíaca simulada em BPM.
5. Gera pulsos gráficos periódicos.
6. Desenha a linha do ECG continuamente na tela.

   '' <img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/e8976d3a-f800-482d-af93-000969a5212b" />
# WOOKIE — Simulador de ECG com ESP32 e OLED

A frequência é definida pela variável `bpm` no código-fonte.

```cpp
const int bpm = 90;
```

Por exemplo, para simular 60 BPM, altere o valor para `60`.

O intervalo entre os pulsos é calculado automaticamente:

```cpp
const int intervalo = 60000 / bpm;
```

O cálculo utiliza 60.000 milissegundos por minuto.

## 🚀 Como executar com ESP32 e Oled

1. Abra a Arduino IDE.
2. Instale as bibliotecas necessárias.
3. Conecte o ESP32 ao computador por USB.
4. Abra o arquivo `.ino` do projeto.
5. Selecione a placa ESP32 correspondente.
6. Escolha a porta serial correta.
7. Compile e envie o programa para a placa.
8. Observe a animação no display OLED.

## 📁 Estrutura sugerida

```text
WOOKIE/
├── README.md
└── wookie_ecg/
    └── wookie_ecg.ino
```

O nome da pasta e do arquivo `.ino` pode ser ajustado conforme a organização do projeto.

## 🔧 Possíveis melhorias

- Ajustar a velocidade e o formato da onda.
- Adicionar uma grade de fundo semelhante à de um monitor cardíaco.
- Criar diferentes padrões de animação.
- Permitir alterar o BPM por botões.
- Integrar sensores em projetos experimentais futuros, com as devidas validações.

## 📚 Tecnologias utilizadas

- ESP32
- Arduino IDE
- C/C++
- Comunicação I²C
- Display OLED SSD1306
- Bibliotecas Adafruit GFX e SSD1306

## 👨‍💻 Projeto

## 📈 Formato da onda simulada

A onda do ECG é gerada por uma sequência de valores que deslocam a linha verticalmente no display OLED. Cada valor representa uma posição em relação à linha central da tela.

No código, essa sequência é definida assim:

```cpp
const int onda[] = {0, -3, -15, 25, -30, 8, 0, 0};
```

### Como interpretar os valores

Considerando a linha central como referência (`centroY = 35`):

| Valor | Efeito visual | Descrição |
|---:|---|---|
| `0` | Linha central | Início do pulso |
| `-3` | Pequena subida | Pequena variação inicial |
| `-15` | Subida acentuada | Início de uma deflexão positiva |
| `25` | Descida | Deslocamento para baixo da linha central |
| `-30` | Pico para cima | Pico mais acentuado da animação |
| `8` | Pequena descida | Retorno em direção à linha central |
| `0` | Linha central | Recuperação |
| `0` | Linha central | Final do pulso |

**Atenção:** no display, valores negativos de deslocamento fazem a linha subir, enquanto valores positivos fazem a linha descer, pois o eixo vertical da tela aumenta de cima para baixo.

### ⏱️ Duração do pulso

Cada ponto da onda é desenhado com um intervalo aproximado de 20 milissegundos. Como o vetor possui oito valores, a sequência dura cerca de 160 ms.

O intervalo entre os batimentos é calculado por:

```cpp
const int intervalo = 60000 / bpm;
```

Com `bpm = 90`, o intervalo entre os pulsos é de aproximadamente 667 ms.

### ⚠️ Diferença em relação a um ECG real

A forma de onda utilizada é **artificial e simplificada**. Ela não representa fielmente as ondas P, o complexo QRS e a onda T de um eletrocardiograma real. O objetivo é criar uma animação semelhante à de um monitor cardíaco para fins didáticos e experimentais.


O valor exibido em BPM também é definido no programa: não é uma medição fisiológica.

**WOOKIE — Robótica e programação com ESP32**

Projeto experimental para aprendizado de programação embarcada, comunicação I²C e representação gráfica em displays OLED.
