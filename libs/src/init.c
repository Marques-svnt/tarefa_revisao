// Bibliotecas padrão em C
#include <stdio.h>

// Bibliotecas de hardware do Raspberry Pi Pico
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

// Headers do projeto
#include "defines.h"
#include "display.h"
#include "pio.h"

// Configura os botões A, B e Push botton do Joystick e os LEDs
void led_button_init() {
    
    // Configuração dos botões
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN); 
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN); 
    gpio_pull_up(BUTTON_B);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN); 
    gpio_pull_up(BUTTON_A);

    // Configuração dos LEDs
    gpio_init(VERDE);
    gpio_set_dir(VERDE, GPIO_OUT); 

    gpio_init(VERMELHO);
    gpio_set_dir(VERMELHO, GPIO_OUT); 
}

// Função que faz todas as inicializações do projeto
void init() {
    stdio_init_all(); // Inicializa a comunicação serial

    adc_init(); // Inicializa o ADC

    initI2C(); // Inicializa o barramento I2C

    uart_init(uart0, 115200); // Inicializa o UART com baud rate de 115200

    led_button_init(); // Inicializa os botões e LEDs

    initializePio(); // Inicializa a PIO

}
