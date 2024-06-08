
# Aqua Sense Pro - Monitor de Qualidade da Água

Aqua Sense Pro é um datalogger projetado para monitorar a qualidade da água em tempo real, coletando dados de sensores de pH, temperatura da água, turbidez e TDS (Total Dissolved Solids). Este projeto utiliza um Arduino UNO R3 para processar e armazenar os dados, e a memória EEPROM do Arduino para salvar os registros coletados.

Para fins de simulação no Wokwi, foram utilizados potenciômetros no lugar dos sensores reais, uma vez que a plataforma não possui suporte para esses sensores específicos.

## Funcionalidades
- **Medição de pH**: Monitora o nível de acidez/alcali da água.
- **Medição de Temperatura**: Monitora a temperatura da água.
- **Medição de Turbidez**: Monitora a clareza da água.
- **Medição de TDS**: Monitora a quantidade de sólidos dissolvidos totais na água.
- **Armazenamento de Dados**: Salva os dados coletados na memória EEPROM do Arduino.
- **Visualização de Dados**: Exibe os dados armazenados através do monitor serial.

# Simulação
<a href="[https://wokwi.com/projects/400042593520835585](https://wokwi.com/projects/400042593520835585)">Link da Simulação</a>

## Requisitos de Hardware
- **Arduino UNO R3**
- **Sensor de pH** (Simulado por potenciômetro no Wokwi)
- **Sensor de Temperatura da Água** (Simulado por potenciômetro no Wokwi)
- **Sensor de Turbidez** (Simulado por potenciômetro no Wokwi)
- **Sensor de TDS** (Simulado por potenciômetro no Wokwi)
- **LEDs e resistores** para feedback visual (opcional)

## Configuração da EEPROM
A EEPROM do Arduino é utilizada para armazenar os dados coletados. Cada registro de dados ocupa 8 bytes na EEPROM. O código está configurado para armazenar até 100 registros antes de sobrescrever os dados mais antigos.

# Vídeo Explicativo
<a href="https://www.youtube.com/watch?v=D8t3XD4dwaE">Link do Vídeo</a>


