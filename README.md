# README - Projeto de Monitoramento de Luminosidade - Vinheria Agnello
Este projeto simula um sistema inteligente de **monitoramento de luminosidade** para a Vinheria Agnello, utilizando Arduino, sensor LDR, LEDs de sinalização, buzzer e um display LCD com a logo animada da Datavine.
## Objetivo
- Medir a luminosidade do ambiente com um **sensor LDR**.
- Exibir a logo Datavine e mensagens de status no **LCD 16x2**.
- Ativar **LEDs indicativos** e **buzzer** conforme a intensidade da luz.
- Reforçar a identidade visual da empresa com **logo animada** no LCD.
- Calcular e exibir médias de luminosidade a cada 10 ciclos.

## Componentes Utilizados
- Arduino Uno
- Sensor de luz (LDR) com módulo
- 1 Display LCD 16x2 (conexão direta)
- LEDs: verde (OK), amarelo (alerta) e vermelho (risco)
- Resistores para LEDs
- Buzzer piezoelétrico
- Jumpers e Protoboard

## Esquema de Montagem
- O LDR está ligado à entrada analógica **A0**.
- Os LEDs estão conectados às portas **4 (verde), 5 (amarelo), 6 (vermelho)**.
- O buzzer está ligado ao pino **7**.
- O LCD está conectado aos pinos: RS=12, E=11, D4=10, D5=9, D6=8, D7=3.

## Funcionamento
### Leitura da Luminosidade
A luminosidade é lida pelo Arduino através da entrada **A0**, e convertida em uma porcentagem com a função `map()`.
### Indicadores de Luz

| Faixa de Luz | LED Ativo | Mensagem no LCD | Buzzer |
| --- | --- | --- | --- |
| 0% - 30% | Verde | "OK" | Desligado |
| 31% - 50% | Amarelo | "Alerta" | Desligado |
| 51% - 100% | Vermelho | "Perigo" | Toca por 3s |
O buzzer só toca **uma vez por entrada na zona vermelha**, evitando repetições constantes.
### Animações no LCD
O display LCD mostra:
- **Logo animada da Datavine** nos primeiros 3 blocos de cada linha (caracteres customizados).
- Texto "DATAVINE" sendo revelado letra por letra durante a inicialização.
- Efeito de piscar na inicialização.
- Animação de uma folha "voando" ao exibir as mensagens de status.
- Porcentagem atual de luminosidade no canto direito.

### Cálculo de Médias
O sistema calcula a média de luminosidade a cada 10 ciclos e a exibe no monitor serial, permitindo acompanhar tendências ao longo do tempo.
## Características Técnicas
### Criação de Caracteres Customizados
O projeto utiliza 7 caracteres personalizados:
- 6 blocos para formar a logo Datavine
- 1 caractere de folha para animação

### Debug
O projeto envia informações detalhadas para o Monitor Serial (9600 baud):
- Valores instantâneos do LDR e porcentagem de luminosidade
- Status atual do sistema (OK, Alerta, Perigo)
- Médias de luminosidade calculadas a cada 10 ciclos

## Código Principal
O código do Arduino integra:
- Leitura de luminosidade pelo LDR
- Controle de LEDs e buzzer
- Gerenciamento do LCD
- Animações personalizadas
- Sistema de cálculo de médias

O código completo está disponível no arquivo do projeto.
## Testando o Projeto
1. Carregue o código no Arduino.
2. Conecte os componentes conforme o esquema de montagem.
3. Para simulação, acesse o [Wokwi](https://wokwi.com/) Ou diretamente pelo projeto [Wokwi]([https://wokwi.com/](https://wokwi.com/projects/429232136290264065).
4. Varie a luminosidade cobrindo ou iluminando o LDR.
5. Observe as mudanças nos LEDs, mensagens no LCD e o acionamento do buzzer.
6. Observe o cálculo da média a cada 10 ciclos no monitor serial.

## Créditos
**Desenvolvido por:** Kauê de Almeida Pena - 564211, Gabriel Ferreira Machado - 562330, João Paulo Santana Basta - 565383, Alexandre Wesley - 561622, João Stellare - 565813
**Equipe:** Data-Vine
**Instituição:** Vinheria Agnello
**Simulado com:** Wokwi Arduino Simulator
**Ano:** 2025
