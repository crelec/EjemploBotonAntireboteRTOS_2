#include "mbed.h"

#define tiempo_rebote           100ms
#define BLINKING_RATE           1000ms

//static BufferedSerial serial_port(USBTX, USBRX);
static BufferedSerial serial_port(PA_2, PA_3);
char mensaje[40]={0};

//Variables globales
char EstadoPresente_boton,EstadoAnterior_Boton;
int contador=0;

//Defino pines del bus de salida y pin del boton entrada
DigitalOut miled(PA_5);//Led Tarjeta
BusOut mi_BusSalida(PA_10,PB_5,PB_4,PB_10,PA_8,PA_9,PC_7,PB_6); //D2,D4,D5,D6,D7,D8,D9,D10
DigitalIn mi_boton0(PC_13); //PC_13=Boton1 PB_3=D3 otro
//DigitalIn mi_boton0(PB_3);//,PullUp);     //Usar con PB_3 si uso PC_13 sobra

// Prototipo de la funcion a usar en el hilo
void Leer_Boton(void);

// Hilo 
Thread Hilo_Boton;

int main()
{
serial_port.write("Hola.! Arranque del programa.\n\r",31);
Hilo_Boton.start(Leer_Boton);
   
    while (true) {
    miled = !miled;
   ThisThread::sleep_for(BLINKING_RATE);
    }
}

void Leer_Boton(void)
{
    while(true) 
    {
    EstadoPresente_boton = mi_boton0;
    if(!EstadoPresente_boton && EstadoAnterior_Boton)
        {
        mi_BusSalida=contador;
        sprintf(mensaje,"Pulso %d\n\r",contador);
        serial_port.write(mensaje,sizeof(mensaje));
        contador++;
        }
    EstadoAnterior_Boton = EstadoPresente_boton; 
    ThisThread::sleep_for(tiempo_rebote);
    }
} 