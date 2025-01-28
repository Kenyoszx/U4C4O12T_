//Inclusão das Bibliotecas
#include <stdio.h>
#include <stdlib.h>
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

// Quantidade de pinos na Matriz
#define LED_COUNT 25

// Variáveis globais
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
int counter;

// Protótipos das Funções
void init();
void npInit(uint);
void npSetLED(const uint, const uint8_t, const uint8_t, const uint8_t);
void npClear();
void npWrite();
void show_number();
void blink();
void increase();
void decrement();
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
static void gpio_irq_handerA(uint gpio,uint32_t events);
static void gpio_irq_handerB(uint gpio,uint32_t events);

// Definição de pixel GRB
struct pixel_t
{
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t npLED_t;

// buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT]; 

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

int main()
{
  stdio_init_all(); // Inicializa a entrada e saída 
  init();
  while (true) {
    blink();
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

  //inicialização dos botões com resistor interno pull-up
  gpio_init(BUTTON_A_PIN);
  gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_A_PIN);
  gpio_set_irq_enabled_with_callback(BUTTON_A_PIN,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handerA); //Rotina de Interrupção
  
  gpio_init(BUTTON_B_PIN);
  gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_B_PIN);
  gpio_set_irq_enabled_with_callback(BUTTON_B_PIN,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handerB); //Rotina de Interrupção
  
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
void show_number(){
  // Para cada número no contador mostra a animação do mesmo na matriz
  switch (counter)
  {
  case 0:
    NUMBER_0();
    break;
  case 1:
    NUMBER_1();
    break;
  case 2:
    NUMBER_2();
    break;
  case 3:
    NUMBER_3();
    break;
  case 4:
    NUMBER_4();
    break;
  case 5:
    NUMBER_5();
    break;
  case 6:
    NUMBER_6();
    break;
  case 7:
    NUMBER_7();
    break;
  case 8:
    NUMBER_8();
    break;
  case 9:
    NUMBER_9();
    break;
  default:
    // Se encontrar algum valor fora do intervalo de 1 à 9 encerra a execução
    printf("[ERRO] Valor Inesperado no Contador"); 
    exit (1);
    break;
  }
}
void NUMBER_0(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(2,50,50,50);
  npSetLED(3,50,50,50);
  npSetLED(6,50,50,50);
  npSetLED(8,50,50,50);
  npSetLED(11,50,50,50);
  npSetLED(13,50,50,50);
  npSetLED(16,50,50,50);
  npSetLED(18,50,50,50);
  npSetLED(21,50,50,50);
  npSetLED(22,50,50,50);
  npSetLED(23,50,50,50);
  npWrite();
}
void NUMBER_1(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(2,50,50,50);
  npSetLED(3,50,50,50);
  npSetLED(7,50,50,50);
  npSetLED(12,50,50,50);
  npSetLED(17,50,50,50);
  npSetLED(22,50,50,50);
  npWrite();
}
void NUMBER_2(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(2,50,50,50);
  npSetLED(3,50,50,50);
  npSetLED(6,50,50,50);
  npSetLED(11,50,50,50);
  npSetLED(12,50,50,50);
  npSetLED(13,50,50,50);
  npSetLED(18,50,50,50);
  npSetLED(21,50,50,50);
  npSetLED(22,50,50,50);
  npSetLED(23,50,50,50);
  npWrite();
}
void NUMBER_3(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(2,50,50,50);
  npSetLED(3,50,50,50);
  npSetLED(8,50,50,50);
  npSetLED(11,50,50,50);
  npSetLED(12,50,50,50);
  npSetLED(13,50,50,50);
  npSetLED(18,50,50,50);
  npSetLED(21,50,50,50);
  npSetLED(22,50,50,50);
  npSetLED(23,50,50,50);
  npWrite();
}
void NUMBER_4(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(6,50,50,50);
  npSetLED(11,50,50,50);
  npSetLED(12,50,50,50);
  npSetLED(13,50,50,50);
  npSetLED(16,50,50,50);
  npSetLED(18,50,50,50);
  npSetLED(21,50,50,50);
  npSetLED(23,50,50,50);
  npWrite();
}
void NUMBER_5(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(2,50,50,50);
  npSetLED(3,50,50,50);
  npSetLED(21,50,50,50);
  npSetLED(22,50,50,50);
  npSetLED(23,50,50,50);
  npWrite();
}
void NUMBER_6(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(2,50,50,50);
  npSetLED(3,50,50,50);
  npSetLED(21,50,50,50);
  npSetLED(22,50,50,50);
  npSetLED(23,50,50,50);
  npWrite();
}
void NUMBER_7(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(2,50,50,50);
  npSetLED(3,50,50,50);
  npSetLED(21,50,50,50);
  npSetLED(22,50,50,50);
  npSetLED(23,50,50,50);
  npWrite();
}
void NUMBER_8(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(2,50,50,50);
  npSetLED(3,50,50,50);
  npSetLED(21,50,50,50);
  npSetLED(22,50,50,50);
  npSetLED(23,50,50,50);
  npWrite();
}
void NUMBER_9(){
  npClear();
  npSetLED(1,50,50,50);
  npSetLED(2,50,50,50);
  npSetLED(3,50,50,50);
  npSetLED(21,50,50,50);
  npSetLED(22,50,50,50);
  npSetLED(23,50,50,50);
  npWrite();
}
static void gpio_irq_handerA(uint gpio,uint32_t events){
// Configura a ação ao apertar o botão A e implementa o Debouce  

  // Obtém o tempo atual em microssegundos
  uint32_t current_time = to_us_since_boot(get_absolute_time());

  // Verifica se passou tempo suficiente desde o último evento
  if (current_time - last_time > 50000) // 50 ms de debouncing
  {
    last_time = current_time; // Atualiza o tempo do último evento
    //Código Função:
    increase();
  }
  
}
static void gpio_irq_handerB(uint gpio,uint32_t events){
// Configura a ação ao apertar o botão B e implementa o Debouce

  // Obtém o tempo atual em microssegundos
  uint32_t current_time = to_us_since_boot(get_absolute_time());

  // Verifica se passou tempo suficiente desde o último evento
  if (current_time - last_time > 50000) // 50 ms de debouncing
  {
    last_time = current_time; // Atualiza o tempo do último evento
    //Código Função:
    decrement();
  }

}
void blink(){
  // Pisca o LED 5 vezes por segundo em cores alternadas
  gpio_put(LED_PIN_RED,true);
  sleep_ms(100);
  gpio_put(LED_PIN_RED,false);
  sleep_ms(100);
  gpio_put(LED_PIN_BLUE,true);
  sleep_ms(100);
  gpio_put(LED_PIN_BLUE,false);
  sleep_ms(100);
  gpio_put(LED_PIN_GREEN,true);
  sleep_ms(100);
  gpio_put(LED_PIN_GREEN,false);
  sleep_ms(100);
  gpio_put(LED_PIN_RED,true);
  gpio_put(LED_PIN_BLUE,true);
  gpio_put(LED_PIN_GREEN,true);
  sleep_ms(100);
  gpio_put(LED_PIN_RED,false);
  gpio_put(LED_PIN_BLUE,false);
  gpio_put(LED_PIN_GREEN,false);
  sleep_ms(100);
  gpio_put(LED_PIN_BLUE,true);
  sleep_ms(100);
  gpio_put(LED_PIN_BLUE,false);
  sleep_ms(100);  
}
void increase(){
  // incrementa o contador e Atualiza o número na Matriz
  counter ++;
  if (counter > 9)
    counter = 0;
  show_number();
}
void decrement(){
  // Decrementa o Contador e atualiza o número na Matriz
  counter --;
  if (counter < 9)
    counter = 9;
  show_number();
}