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
#include "defines.h"         // Definições globais e configurações do projeto
#include "display.h"         // Funções de controle do display
#include "init.h"            // Funções de inicialização do hardware
#include "interrupt.h"       // Funções de manipulação de interrupções
#include "pio.h"             // Funções PIO para matriz 5x5


int main()
{
    init();

    while (true) {
        set_one_led(20, 0, 0); // Liga o LED na posição 0 com a cor vermelha
        sleep_ms(50);
    }
}
