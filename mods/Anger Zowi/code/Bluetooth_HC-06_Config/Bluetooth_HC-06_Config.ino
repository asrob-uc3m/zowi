/* 0_ Este es un código diseñado para ejecutar sobre una Arduino Mega para mayor comodidad. Solamente será necesario para la configuración por lo que la puedes pedir prestada.
 *  
 *    -- En el caso de que no tengas acceso a una Arduino Mega, puedes utilizar la librería SoftwareSerial (https://www.arduino.cc/en/Reference/SoftwareSerial)
 * 
 * 1_ Tras realizar las conexiones, lo primero es fijarse en el módulo, verás una luz roja parpadeando. Eso significa que el modulo está listo para vincularse a un dispositivo BlueTooth o para aceptar comandos AT, 
 *   el modulo HC-06 no necesita nada mas para entrar en modo de aceptar comandos AT.
 *
 *   - De hecho siempre que veas la luz parpadeando significa que el modulo no retransmitirá los comandos AT, sino que los interpretara como ordenes internas.
 *   
 *   - Pero si realizas una conexión (y la luz roja se queda fija, ignorará los comandos AT y los transferirá sin más.
 *
 *  Si no te has vinculado aún, y la luz roja parpadea, ya podemos enviar comandos AT. Veamos algún ejemplo.
 *
-* 2_ El primer comando y más básico es enviar (siempre en mayúsculas) un simple AT desde la consola, tecleamos AT y pulsamos enviar. Se supone que debería responder con OK.
 *
 *   - La terminal de Arduino debe estar configurada en modo "sin ajuste de línea", este ajuste se encuentra junto a la velocidad de la terminal (en baudios).
 *
 *   - En caso de que no se reciba respuesta se debe modificar la velocidad de Serial1 hasta lograrlo.
 *
-* 3_ Otros comandos:
 *
 *   - AT+VERSION, escrito tal cual, el módulo devuelve la versión del Firmware.
 *
 *   - AT+NAMEXXX, define el nombre que queremos presentar cuando alguien nos busque:
 *
 *            Ejemplo: AT+NAMEZowimanoid establece el nombre del módulo a Zowimanoid (admite incluso espacios).
 *
 *   - AT+BAUDX, Fija la velocidad de comunicación entre el modulo y la consola según a la siguiente tabla:
 *
 *            Sustituir X por 1 configura        1200bps
 *            Sustituir X por 2 configura        2400bps
 *            Sustituir X por 3 configura        4800bps
 *            Sustituir X por 4 configura        9600bps (Default)
 *            Sustituir X por 5 configura        19200bps
 *            Sustituir X por 6 configura        38400bps
 *            Sustituir X por 7 configura        57600bps
 *            Sustituir X por 8 configura        115200bps
 *
 *            Ejemplo: AT+BAUD7 configura la comunicación a 57600 baudios
 *
 *    - AT+PINXXXX, configura el número de identificación personal, que se requerirá para establecer la vinculación
 *
 *            Ejemplo: AT+PIN4516, establece 4516 como PIN
 *
-* 4_ En caso de que probando varios de estos comandos, no obtuvierais respuesta, o vierais caracteres extraños en la consola, probad con otras velocidades en la línea:
 *      Serial1.begin(9600);
 *   o aseguraos de que el led del módulo parpadea. Si no parpadea, los comandos no funcionarán.
*/

void setup()
{
Serial1.begin(9600); // Por defecto viene de fábrica con 9600
                     // Deben conectarse los pines cruzados
                     // RX1(Placa) -> TX(Bluetooth)
                     // TX1(Placa) -> RX(Bluetooth)
Serial.begin(9600);
}
void loop()
{
if(Serial1.available()) Serial.write(Serial1.read());
if(Serial.available()) Serial1.write(Serial.read());
}
