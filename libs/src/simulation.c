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
#include "quadrado.h" // Movimentação do quadrado no display
#include "buzzer.h"

#define DELAY 5000

// Variáveis globais
static volatile uint32_t last_time_A = 0; // Armazena o tempo do último evento (em microssegundos)
static volatile uint32_t last_time_B = 0;
extern uint freq_atual;
bool vazamento = 0;
bool trava = 0;
bool registro = 0;
int percentGLP = 100;
bool exec = 1;

// Função de interrupção para manipular a troca de unidades e saída do programa
void gpio_irq_handler_glp(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (gpio == BUTTON_B && debounce(&last_time_A, 200000))
    {
        last_time_A = current_time;
        vazamento = !vazamento;

        if (vazamento == true && trava == false)
        {
            trava = true;
            registro = false;
            printf("---------------------------------------------------------\nVazamento detectado! Trava ativada, registro fechado.\n---------------------------------------------------------\n");
        }
        else if (vazamento == false && trava == true)
        {
            trava = false;
            printf("---------------------------------------------------------\nVazamento resolvido! Trava liberada.\n---------------------------------------------------------\n");
        }
    }

    else if (gpio == BUTTON_A && debounce(&last_time_B, 300000))
    {
        last_time_B = current_time;
        if (trava == false)
        {
            registro = !registro;
            printf("---------------------------------------------------------\nRegistro %s\n---------------------------------------------------------\n", registro ? "Aberto" : "Fechado");
        }
    }
}

void relatorio()
{
    printf("\nPorcentagem de gás presente no botijão: %d%%\n", percentGLP);
    printf("Estado do registro: %s\n", registro ? "Aberto" : "Fechado");
}

void ledRegistro()
{
    gpio_put(VERDE, registro);
    gpio_put(VERMELHO, !registro);
}

void vazamentoBuzz()
{
    if (vazamento)
    {
        buzz(freq_atual);
    }
    else
    {
        buzzer_stop();
    }
}

void matrizRegistro()
{
    if (registro)
    {
        set_one_led(1, 0, 20, 0);
    }
    else
    {
        set_one_led(2, 20, 0, 0);
    }
}

void reset(){
    exec = 1;
    vazamento = 0;
    registro = 0;
    trava = 0;
    percentGLP = 100;

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Interrupção no botão A
}

int simulationGLP()
{
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler_glp);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler_glp);

    uint32_t last_relatorio_time = to_ms_since_boot(get_absolute_time());

    while (exec == 1)
    {
        ledRegistro();
        vazamentoBuzz();
        movimentoJoystick();
        matrizRegistro();

        uint32_t now = to_ms_since_boot(get_absolute_time());
        if (now - last_relatorio_time >= DELAY)
        {
            last_relatorio_time = now;
            if (registro)
            {
                percentGLP -= 10;
            }
            relatorio();
            if (percentGLP == 0)
            {
                printf("\n\n---------------------------------------------------------\nBotijão esvaziou, substitua por um novo\n---------------------------------------------------------\n");
                exec = 0;
            }
        }
        sleep_ms(50);
    }
    reset();
    return 0;
}
