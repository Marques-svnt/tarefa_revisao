#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "display.h"
#include "defines.h"


uint16_t lastvrx_value = 2048;
uint16_t lastvry_value = 2048;

void movimentoJoystick()
{
    // Mapeando valores do ADC para o display
    adc_select_input(0);
    sleep_us(5); // Pequeno delay para estabilidade
    uint16_t vrx_value = adc_read();
    adc_select_input(1);
    sleep_us(5); // Pequeno delay para estabilidade
    uint16_t vry_value = adc_read();

    // Variável que faz o controle para que haja atualização apenas quando o joystick se mover evitando que ele fique tremendo o tempo todo
    int flick_x = vrx_value - lastvrx_value;
    int flick_y = vry_value - lastvry_value;

    if (!(flick_x < 100 && flick_x > -100 && flick_y < 100 && flick_y > -100)) // Apenas ocorre o código quando o valor de flick fugir do intervalo entre -100 e 100
    {
        int coord_x = (vry_value * 126) / 4095; // Mapeando para intervalo de 0-127
        int coord_y = (vrx_value * 40) / 4095;  // Mapeando para intervalo de 0-63

        lastvry_value = vry_value;
        lastvrx_value = vrx_value;

        // Definir limites para coordenadas
        int min_x = 10, max_x = 112;
        int min_y = 10, max_y = 48;

        // Inversão do eixo Y devido ao display exibir os movimentos ao contrário
        coord_y = max_y - coord_y;

        // Garantir que as coordenadas fiquem dentro dos limites
        if (coord_x < min_x)
        {
            coord_x = min_x;
        }
        if (coord_x > max_x)
        {
            coord_x = max_x;
        }
        if (coord_y < min_y)
        {
            coord_y = min_y;
        }
        if (coord_y > max_y)
        {
            coord_y = max_y;
        }

        // Exibir as coordenadas
        displayQuadrado(coord_x, coord_y);

        // Delay de estabilização
        sleep_us(5);
    }
}
