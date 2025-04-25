Este projeto simula um sistema inteligente de **monitoramento de luminosidade** para a Vinheria Agnello, utilizando Arduino, sensor LDR, LEDs de sinalização, buzzer e um display LCD animado com a logo da empresa. Ele oferece feedback **visual, auditivo e informativo** para ambientes onde a luz precisa ser cuidadosamente controlada.
## Objetivo
- Medir a luminosidade do ambiente com um **sensor LDR**.
- Exibir mensagens e animações em um **LCD 16x2 I2C**.
- Ativar **LEDs indicativos** e **buzzer** conforme a intensidade da luz.
- Reforçar a identidade visual da empresa com **logo animada** no LCD.
- Oferecer múltiplas telas de informação acessíveis via botão ou rotação automática.

## Componentes Utilizados
- Arduino Uno
- Sensor de luz (LDR) com módulo
- 1 Display LCD 16x2 I2C
- LEDs: verde (OK), amarelo (alerta) e vermelho (risco)
- Resistores para LEDs
- Buzzer piezoelétrico
- Botão para interação do usuário
- Jumpers e Protoboard

## Esquema de Montagem
- O LDR está ligado à entrada analógica **A0**.
- Os LEDs estão conectados às portas **4 (verde), 5 (amarelo), 6 (vermelho)**.
- O buzzer está ligado ao pino **7**.
- O LCD I2C está conectado aos pinos SDA e SCL.
- O botão de interação está no pino **2**.

## Funcionamento
### Leitura da Luminosidade
A luminosidade é lida pelo Arduino através da entrada **A0**, e convertida em uma porcentagem com a função `map()`.
### Indicadores de Luz

| Faixa de Luz | LED Ativo | Mensagem no LCD | Buzzer |
| --- | --- | --- | --- |
| 0% - 30% | Verde | "Ambiente ideal" | Desligado |
| 31% - 50% | Amarelo | "Alerta de luz" | Desligado |
| 51% - 100% | Vermelho | "Luz excessiva!" | Toca por 3s |
O buzzer só toca **uma vez por entrada na zona vermelha**, evitando repetições constantes.
### Sistema de Telas Múltiplas
O sistema alterna automaticamente entre 6 telas diferentes a cada 5 segundos:
1. **Tela DATAVINE**: Exibe a logo e o nome da empresa.
2. **Tela do Contador**: Mostra um contador que incrementa com o botão.
3. **Tela de Boas-Vindas**: Mostra "Bem-vindo!" com animação de folha.
4. **Tela de Tempo**: Exibe o tempo de funcionamento do sistema.
5. **Tela de Mensagem**: Apresenta texto rolante institucional.
6. **Tela de Luminosidade**: Mostra percentual de luz e status do ambiente.

### Animações no LCD
O display LCD mostra:
- **Logo animada da Datavine** nos 3 primeiros blocos (caracteres customizados).
- Texto "DATAVINE" sendo revelado letra por letra.
- Mensagem **"Bem-vindo!"** com animação de uma folha "voando" na segunda linha.
- Efeito de piscar na inicialização.
- Texto rolante na tela de mensagem.

## Características Técnicas
### Criação de Caracteres Customizados
O projeto utiliza 7 caracteres personalizados:
- 6 blocos para formar a logo Datavine
- 1 caractere de folha para animação

### Interação do Usuário
- O botão no pino 2 permite incrementar um contador.
- As telas alternam automaticamente a cada 5 segundos.
- Informações relevantes como tempo de funcionamento e nível de luminosidade são atualizadas em tempo real.

### Debug
O projeto envia informações detalhadas para o Monitor Serial (9600 baud), facilitando o diagnóstico e monitoramento.
## Código Principal
O código do Arduino integra:
- Leitura de luminosidade pelo LDR
- Controle de LEDs e buzzer
- Gerenciamento do LCD I2C
- Animações customizadas
- Sistema de rotação de telas
- Tratamento de eventos do botão

O código completo está disponível no arquivo `vinheria_agnello.ino`.
## Testando o Projeto
1. Carregue o código no Arduino.
2. Conecte os componentes conforme o esquema de montagem.
3. Para simulação, acesse o [Wokwi](https://wokwi.com/) Ou diretamente o projeto [Wokwi](https://wokwi.com/projects/429218607912979457)
4. Varie a luminosidade cobrindo ou iluminando o LDR.
5. Observe as mudanças nos LEDs, mensagens no LCD e o acionamento do buzzer.
6. Pressione o botão para incrementar o contador.

## Créditos
**Desenvolvido por:** Kauê de Almeida Pena - 564211, Gabriel Ferreira Machado - 562330, João Paulo Santana Basta - 565383, Alexandre Wesley - 561622, João Stellare - 565813
**Equipe:** Data-Vine
**Instituição:** Vinheria Agnello
**Simulado com:** Wokwi Arduino Simulator
**Ano:** 2025
