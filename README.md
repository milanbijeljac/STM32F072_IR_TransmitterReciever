# STM32F072_IR_TransmitterReciever

This is project that uses STM32F072 Nucleo board to interface IR receiver (KY-022), IR transmitter (KY-005) and analog temperature sensor (KY-013) in order to turn ON/OFF AC depending on temperature value.

Receiving and transmitting is not currently separated by any compiler switches in global config. If receiver needs to be active, transmitter needs to be disconnected from pin and vice versa.

In order to use temperature sensor, connect it to pin PB1.
In order to use IR transmitter, connect it to pin PA0.
In order to use IR receiver, connect it to pin PB12.

In this case remote ZHJT-03 is used which sends 3 bytes of data when transmitting message. In global configuration it can be set which message will be received.
