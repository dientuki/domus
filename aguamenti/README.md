# Aguamenti
Water level indicator in arduino

## Name
From [here](https://harrypotter.fandom.com/wiki/Water-Making_Spell)

## Parts

### Arduino

Arduino pro mini 3.3V

### Ultrasonic sensor

It's use an US-100

### Wake up

It's use a RTC Clock

### Comunication

It's use a Nrf21l01 transceiver

## Power consumption

| Part     | Consumption | Sleep |
|----------|-------------|-------|
| Arduino  |  5mA        | 1mA   |
| US-100   | 2mA         | 2mA   |
| RTC      | 1mA         | 1mA   |
| Nrf24l01 |  12mA       | 1mA   |
|  Total   |       20mA  | 5mA   |





Power consumption, all working with 3.3v

Arduino pro mini
ACT 4.74mA
PDS 0.90mA

Us-100
ACT 2mA
PDS 1.8mA

Ds3231
1mA

wifi
ACT 250mA
PDS 0.01mA
