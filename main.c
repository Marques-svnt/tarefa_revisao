// Bibliotecas padrão em C
#include <stdio.h>
#include <stdlib.h>

// Bibliotecas de hardware do Raspberry Pi Pico
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"

// Headers do projeto
#include "defines.h"    // Definições globais e configurações do projeto
#include "display.h"    // Funções de controle do display
#include "init.h"       // Funções de inicialização do hardware
#include "interrupt.h"  // Funções de manipulação de interrupções
#include "pio.h"        // Funções PIO para matriz 5x5
#include "quadrado.h"   // Movimentação do quadrado no display
#include "simulation.h" // Simulação dos dados do GLP

volatile int startSimulation = 0;

int main()
{
    init();

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Interrupção no botão A

    while (true)
    {
        movimentoJoystick();

        if (stdio_usb_connected())
        {
            set_one_led(0, 0, 20, 0);
            if (startSimulation == 1)
            {
                simulationGLP();
                startSimulation = 0;
            }
        }
        else
        {
            set_one_led(0, 20, 0, 0);
            if (startSimulation == 1)
            {
                limpar();
                display("Ative o Serial", 8, 10);
                display("Monitor", 36, 22);
                display("e tente", 36, 34);
                display("novamente", 28, 46);
                sleep_ms(4000);
                limpar();
                startSimulation = 0;
            }
        }
        sleep_ms(50);
    }
}
