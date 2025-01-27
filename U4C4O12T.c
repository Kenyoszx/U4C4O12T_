//Inclusão das Bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"

// Definição dos Pinos
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define MATRIZ_LEDS 7
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

#define LED_COUNT 25 // Quantidade de pinos na Matriz

// Protótipos das Funções
void init();
void npInit(uint);
void npSetLED(const uint, const uint8_t, const uint8_t, const uint8_t);
void npClear();
void npWrite();
void NUMBER_0();
void NUMBER_1();
void NUMBER_2();
void NUMBER_3();
void NUMBER_4();
void NUMBER_5();
void NUMBER_6();
void NUMBER_7();
void NUMBER_8();
void NUMBER_9();

// Definição de pixel GRB
struct pixel_t
{
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t npLED_t;

npLED_t leds[LED_COUNT]; // buffer de pixels que formam a matriz.

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

int main()
{
    stdio_init_all();
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

void init(){
     // inicialização dos pinos
  npInit(MATRIZ_LEDS);
  npClear();
  npWrite();

  gpio_init(LED_PIN_GREEN);
  gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
  gpio_put(LED_PIN_GREEN, 0);

  gpio_init(LED_PIN_BLUE);
  gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
  gpio_put(LED_PIN_BLUE, 0);

  gpio_init(LED_PIN_RED);
  gpio_set_dir(LED_PIN_RED, GPIO_OUT);
  gpio_put(LED_PIN_RED, 0);
}

void npInit(uint pin){
  // Inicializa a máquina PIO para controle da matriz de LEDs.

  // Cria programa PIO.
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  // Toma posse de uma máquina PIO.
  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0)
  {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  // Inicia programa na máquina PIO obtida.
  ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i)
  {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b){
  // Atribui uma cor RGB a um LED.

  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}
void npClear(){
  // Limpa o buffer de pixels.

  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}
void npWrite(){
  // Escreve os dados do buffer nos LEDs.

  // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
  for (uint i = 0; i < LED_COUNT; ++i)
  {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}
void NUMBER_0(){}
void NUMBER_1(){}
void NUMBER_2(){}
void NUMBER_3(){}
void NUMBER_4(){}
void NUMBER_5(){}
void NUMBER_6(){}
void NUMBER_7(){}
void NUMBER_8(){}
void NUMBER_9(){}