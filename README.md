# Contador com Matriz de Leds e Rotina de Interrupção

Este projeto utiliza uma matriz de LEDs e dois botões para exibir números de 0 a 9 em uma tela de LEDs e manipular o valor mostrado utilizando interrupções nos botões. Além disso, um LED RGB pisca em diferentes cores a cada 200 milissegundos, ou seja 5 vezes por segundo
## Funcionalidades

- **Contador**: O contador é incrementado ou decrementado ao pressionar os botões A ou B, e o número é exibido na matriz de LEDs.
- **Matriz de LEDs**: A matriz de LEDs exibe os números de 0 a 9 utilizando LEDs individuais, com cada número representado por uma combinação de LEDs acesos.
- **LED RGB piscante**: Um LED RGB (vermelho, verde e azul) pisca em diferentes cores, alternando entre vermelho, azul e verde, 5 vezes por segundo.
- **Rotina de interrupção**: O código utiliza interrupções para detectar o pressionamento dos botões A e B, que alteram o contador de acordo com a ação desejada.

## Componentes

- **Pinos de LEDs**: 3 pinos (vermelho, verde e azul) para o LED RGB.
- **Matriz de LEDs**: 25 LEDs controlados por uma máquina PIO.
- **Botões**: 2 botões para incrementar ou decrementar o contador.
- **Microcontrolador**: Raspberry Pi Pico w (rp2040).

## Configuração do Ambiente

Antes de começar, certifique-se de que você tenha o ambiente de desenvolvimento do **Raspberry Pi Pico** configurado corretamente. Siga as instruções do [Raspberry Pi Pico SDK](https://www.raspberrypi.org/documentation/rp2040/getting-started/) para configurar o SDK e as ferramentas de compilação.

## Compilação e Upload

1. Compile o código usando o ambiente de desenvolvimento configurado.
2. Após a compilação, faça o upload do código para o seu **Raspberry Pi Pico**.

## Tecnologias Utilizadas

- **C/C++**
- **Raspberry Pi Pico SDK**
- **PIO (Programmable Input/Output)** para controle de LEDs

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir um problema ou enviar um pull request.
