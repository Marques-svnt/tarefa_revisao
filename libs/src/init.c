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

// Inicializa o joystick (configura o ADC e o pino do joystick)
void joystick_init() {
    adc_init(); // Inicializa o ADC
    adc_gpio_init(JOYSTICK_Y_PIN); // Inicializa o pino Y do joystick
}

// Configura os botões A, B e os LEDs
void led_button_init() {
    
    // Configuração dos botões
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN); 
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN); 
    gpio_pull_up(BUTTON_B); 

    // Configuração dos LEDs
    gpio_init(VERDE);
    gpio_set_dir(VERDE, GPIO_OUT); 

    gpio_init(VERMELHO);
    gpio_set_dir(VERMELHO, GPIO_OUT); 
}

// Função que faz todas as inicializações do projeto
void init() {
    stdio_init_all(); // Inicializa a comunicação serial

    initI2C(); // Inicializa o barramento I2C

    uart_init(uart0, 115200); // Inicializa o UART com baud rate de 115200

    joystick_init(); // Inicializa o joystick

    led_button_init(); // Inicializa os botões e LEDs

    initializePio(); // Inicializa a PIO

}
