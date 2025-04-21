
# Monitoramento e controle de gás GLP em um registro inteligente

## Descrição do Projeto

Este projeto consiste em um **simulador de monitoramento e controle de gás GLP em um registro inteligente** desenvolvido para a plataforma **BitDogLab** utilizando a **Raspberry Pi Pico**. O sistema permite a simulação de leituras da quantidade de gás GLP dentro de um botijão, o controle do estado do registro travando o valor e também a simulação de um evento onde há vazamento.

## Funcionalidades Principais

- **Simulação**: O valor da porcentagem vai decair 10% a cada 5s e possui os botões A e B disponíveis para manipulação de eventos.
- **Geração de Relatórios**: Registra eventos e variáveis do sistema, exportando os dados via UART.
- **Feedback Visual e Sonoro**: Indicação de estados do sistema por meio de LEDs RGB, matriz de LEDs e buzzer para alertas.

## Estrutura do Projeto

A organização dos diretórios e arquivos é a seguinte:

- **`/libs`**: Contém bibliotecas auxiliares utilizadas no projeto.
- **`/extras`**: Inclui arquivos adicionais e recursos complementares.
- **`main.c`**: Arquivo principal que contém a função `main` e orquestra a inicialização e o loop principal do programa.
- **`CMakeLists.txt`**: Arquivo de configuração do CMake para gerenciamento da construção do projeto.
- **`pico_sdk_import.cmake`**: Script para importação do SDK da Raspberry Pi Pico.

## Requisitos de Hardware e Software

- **Hardware**:
  - Placa **BitDogLab** com **Raspberry Pi Pico** integrada.
  - Componentes integrados: joystick, LEDs RGB, matriz de LEDs, display OLED e buzzer.

- **Software**:
  - Ambiente de desenvolvimento **Visual Studio Code** com extensão para Raspberry Pi Pico.
  - **CMake** para gerenciamento de build.
  - **SDK do Raspberry Pi Pico** configurado no ambiente.

## Instruções de Compilação e Execução

1. **Clonar o Repositório**:
   ```bash
   git clone https://github.com/Marques-svnt/tarefa_revisao.git
   ```

2. **Configurar o Ambiente**:
   - Certifique-se de que o SDK do Raspberry Pi Pico esteja corretamente instalado e configurado.
   - Instale o CMake e o Visual Studio Code, caso ainda não estejam disponíveis.

3. **Compilar o Projeto**:
   - Abra o terminal no diretório raiz do projeto.
   - Crie uma pasta para os arquivos de build:
     ```bash
     mkdir build
     cd build
     ```
   - Configure o projeto com o CMake:
     ```bash
     cmake ..
     ```
   - Compile o código:
     ```bash
     make
     ```

4. **Carregar o Firmware**:
   - Conecte a Raspberry Pi Pico ao computador em modo de armazenamento USB.
   - Copie o arquivo `.uf2` gerado na pasta `build` para o dispositivo de armazenamento correspondente à Pico.

5. **Interagir com o Sistema**:
   - Utilize um monitor serial (como o integrado no Visual Studio Code) para visualizar os logs e interagir com o sistema via UART.

## Colaboradores

- Gabriel Marques de Andrade ([@marques-svnt](https://github.com/Marques-svnt))

## Licença

Este projeto está licenciado sob a licença MIT. Consulte o arquivo `LICENSE` para mais informações.
