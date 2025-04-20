// Bibliotecas padrão em C
#include <stdio.h>

// Bibliotecas de hardware do Raspberry Pi Pico
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"

// Headers do projeto
#include "defines.h"
#include "display.h"
#include "init.h"
#include "interrupt.h"
#include "pio.h"

// Variáveis globais
static volatile uint32_t last_time_A = 0; // Armazena o tempo do último evento (em microssegundos)
static volatile uint32_t last_time_B = 0;
bool vazamento = 0;
bool registro = 0;
int percentGLP = 100;

// Função de interrupção para manipular a troca de unidades e saída do programa
void gpio_irq_handler_glp(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time());


    if (gpio == BUTTON_A && debounce(&last_time_A, 200000))
    {
        last_time_A = current_time;
        vazamento = !vazamento;

    }

    else if (gpio == BUTTON_B && debounce(&last_time_B, 300000))
    {
        last_time_B = current_time;
        registro = !registro;
    }
}

int simulationGLP()
{
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler_glp);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler_glp);

    while(true){
        // evento de clock q vai decrescer se o registro tiver aberto e verificar vazamento
    }
    return 0;
}
