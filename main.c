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

volatile int startSimulation = 0; // Variável global que vai controlar quando a simulação vai funcionar

int main()
{
    init(); // Inicialização dos componentes

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Interrupção no botão A que faz a simulação começar

    while (true)
    {
        movimentoJoystick(); // Função responsável por criar o quadrado no display e controlar seu movimento

        // Garante que a simulação só possa começar caso a placa tenha conectividade USB
        if (stdio_usb_connected())
        {
            set_one_led(0, 0, 20, 0); // Sinalização de qual botão deve-se apertar para começar a simulação e feedback visual se tudo está conectado (verde)
            if (startSimulation == 1)
            {
                simulationGLP();
                startSimulation = 0;
            }
        }
        // Condição que impede o funcionamento e dá um feedback no display para ligar o serial monitor
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
        sleep_ms(50); // Pequeno delay
    }
}
