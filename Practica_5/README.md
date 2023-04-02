Practica 5 de PdM

Implementacion de una API para envío de mensajes por UART. Las funciones a implementar son:

bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

Las funciones deben implementarse en el archivo API_uart.c y sus correspondientes declaraciones en API_uart.h

uartInit() debe realizar toda la inicialización de la UART.  Adicionalmente, debe imprimir por la terminal serie un mensaje con sus parámetros de configuración.

	La función devuelve:
	true: si la inicialización es exitosa.
	false: si la inicialización no es exitosa.
uartSendString(uint8_t *pstring) recibe un puntero a un string que se desea enviar por la UART completo (hasta el caracter ‘\0’) y debe utilizar la función de la HAL HAL_UART_Transmit(...) para transmitir el string.

uartSendStringSize(uint8_t * pstring, uint16_t size) recibe un puntero a un string que se desea enviar por la UART y un entero con la cantidad de caracteres que debe enviar. La función debe utilizar HAL_UART_Transmit(...) para transmitir el string.
