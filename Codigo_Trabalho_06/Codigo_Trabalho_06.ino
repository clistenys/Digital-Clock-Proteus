// Titulo: Relógio Digital
// Autor:  Clistenys Eduardo

#include <TimerOne.h>
#include "TM1637.h"

// Mapeando portas analogicas
#define    AD_OPT0   A0
#define    AD_OPT1   A1

// Mapeando portas digitais por linha da matriz
#define    ROW_PIN_A    3
#define    ROW_PIN_B    4
#define    ROW_PIN_C    5

// Mapeando portas digitais por coluna da matriz
#define    COL_PIN_A    6
#define    COL_PIN_B    7
#define    COL_PIN_C    8

// Pins definitions for TM1637 and can be changed to other ports
#define ON 1
#define OFF 0
#define CLK 9
#define DIO 10

// Variáveis de controle do Display
int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
TM1637 tm1637(CLK,DIO);

// Variáveis para o fluxo de tempo
unsigned char metadeSegundo = 0;
unsigned char segundo;
unsigned char minuto = 0;
unsigned char hora = 0;

// Variavel para controle da leitura do valor de linha
int linha = 0;
// Variavel para controle da leitura do valor de coluna
int coluna = 0;

void setup() 
{
    // Inicia comunicação na porta serial
    Serial.begin(9600);

    // Definindo todos os pinos como de saída
    for(int i = 3; i < 9; i++) pinMode(i, OUTPUT);

    // Inicializando o display
    InitDisplay();
    // Inicializando as portas utilizadas
    InitPorts();
} 

void loop() 
{
    if(Update == ON)
    {
        TimeUpdate();
        tm1637.display(TimeDisp);
    }

    // Define os numeros de linha e coluna a serem usados
    SetLinha(linha);
    SetColuna(coluna);

    analogWrite(AD_OPT0, 255);
    analogWrite(AD_OPT1, 255);
}

// Inicializando as portas utilizadas 
void InitPorts()
{
    // Definindo o pino AD_OPT0 como de saída
    pinMode(AD_OPT0, OUTPUT);

    // Definindo o pino AD_OPT1 como de saída
    pinMode(AD_OPT1, OUTPUT);

    // Configurando os demais pinos com nivel lógico LOW 
    digitalWrite(ROW_PIN_A, LOW);
    digitalWrite(ROW_PIN_B, LOW);
    digitalWrite(ROW_PIN_C, LOW);
    digitalWrite(COL_PIN_A, LOW);
    digitalWrite(COL_PIN_B, LOW);
    digitalWrite(COL_PIN_C, LOW);
}

// Define o numero da coluna a ser usada no multiplexador em binario
// Decimal  0 1 2 3 4 5 6 7
// Binário  0 1 10  11  100 101 110 111
void SetLinha(int value)
{
    switch (value)
    {
        case 0:
            // linha 0 = 0 0 0
            digitalWrite(ROW_PIN_C, LOW);
            digitalWrite(ROW_PIN_B, LOW);
            digitalWrite(ROW_PIN_A, LOW);
            break;
        case 1:
            // linha 1 = 0 0 1
            digitalWrite(ROW_PIN_C, LOW);
            digitalWrite(ROW_PIN_B, LOW);
            digitalWrite(ROW_PIN_A, HIGH);
            break;
        case 2:
            // linha 2 = 0 1 0
            digitalWrite(ROW_PIN_C, LOW);
            digitalWrite(ROW_PIN_B, HIGH);
            digitalWrite(ROW_PIN_A, LOW);
            break;
        case 3:
            // linha 3 = 0 1 1
            digitalWrite(ROW_PIN_C, LOW);
            digitalWrite(ROW_PIN_B, HIGH);
            digitalWrite(ROW_PIN_A, HIGH);
            break;
        case 4:
            // linha 4 = 1 0 0
            digitalWrite(ROW_PIN_C, HIGH);
            digitalWrite(ROW_PIN_B, LOW);
            digitalWrite(ROW_PIN_A, LOW);
            break;
        case 5:
            // linha 5 = 1 0 1
            digitalWrite(ROW_PIN_C, HIGH);
            digitalWrite(ROW_PIN_B, LOW);
            digitalWrite(ROW_PIN_A, HIGH);
            break;
        case 6:
            // linha 6 = 1 1 0
            digitalWrite(ROW_PIN_C, HIGH);
            digitalWrite(ROW_PIN_B, HIGH);
            digitalWrite(ROW_PIN_A, LOW);
            break;
        case 7:
            // linha 7 = 1 1 1
            digitalWrite(ROW_PIN_C, HIGH);
            digitalWrite(ROW_PIN_B, HIGH);
            digitalWrite(ROW_PIN_A, HIGH);
            break;
        default:
            // linha 0 = 0 0 0
            digitalWrite(ROW_PIN_C, LOW);
            digitalWrite(ROW_PIN_B, LOW);
            digitalWrite(ROW_PIN_A, LOW);
            break;
    }
}

// Define o numero da coluna a ser usada no multiplexador em binario
// Decimal  0 1 2 3 4 5 6 7
// Binário  0 1 10  11  100 101 110 111
void SetColuna(int value)
{
    switch (value)
    {
        case 0:
            // linha 0 = 0 0 0
            digitalWrite(COL_PIN_C, LOW);
            digitalWrite(COL_PIN_B, LOW);
            digitalWrite(COL_PIN_A, LOW);
            break;
        case 1:
            // linha 1 = 0 0 1
            digitalWrite(COL_PIN_C, LOW);
            digitalWrite(COL_PIN_B, LOW);
            digitalWrite(COL_PIN_A, HIGH);
            break;
        case 2:
            // linha 2 = 0 1 0
            digitalWrite(COL_PIN_C, LOW);
            digitalWrite(COL_PIN_B, HIGH);
            digitalWrite(COL_PIN_A, LOW);
            break;
        case 3:
            // linha 3 = 0 1 1
            digitalWrite(COL_PIN_C, LOW);
            digitalWrite(COL_PIN_B, HIGH);
            digitalWrite(COL_PIN_A, HIGH);
            break;
        case 4:
            // linha 4 = 1 0 0
            digitalWrite(COL_PIN_C, HIGH);
            digitalWrite(COL_PIN_B, LOW);
            digitalWrite(COL_PIN_A, LOW);
            break;
        case 5:
            // linha 5 = 1 0 1
            digitalWrite(COL_PIN_C, HIGH);
            digitalWrite(COL_PIN_B, LOW);
            digitalWrite(COL_PIN_A, HIGH);
            break;
        case 6:
            // linha 6 = 1 1 0
            digitalWrite(COL_PIN_C, HIGH);
            digitalWrite(COL_PIN_B, HIGH);
            digitalWrite(COL_PIN_A, LOW);
            break;
        case 7:
            // linha 7 = 1 1 1
            digitalWrite(COL_PIN_C, HIGH);
            digitalWrite(COL_PIN_B, HIGH);
            digitalWrite(COL_PIN_A, HIGH);
            break;
        default:
            // linha 0 = 0 0 0
            digitalWrite(COL_PIN_C, LOW);
            digitalWrite(COL_PIN_B, LOW);
            digitalWrite(COL_PIN_A, LOW);
            break;
    }
}


// Definindo linha e coluna do led mediante aos segundos
void UpdateLedPosition()
{
    if(linha >= 7 && coluna >= 3)
    {
        linha = 0;
        coluna = 0;
        return;
    }

    coluna++;
    if(coluna >= 8)
    {
        coluna = 0;
        linha++;
    }
    
    if(linha >= 8)
    {
        linha = 0;   
    }    
}

void InitDisplay()
{
    tm1637.set();
    tm1637.init();
    
    // timing for 500ms
    Timer1.initialize(500000);
    
    // declare the interrupt serve routine:TimingISR
    Timer1.attachInterrupt(TimingISR);
}

void TimingISR()
{
    metadeSegundo ++;
    Update = ON;

    if(metadeSegundo == 2)
    {
        segundo ++;
        UpdateLedPosition();

        if(segundo == 60)
        {
            minuto ++;
            if(minuto == 60)
            {
                hora ++;
                if(hora == 24)hora = 0;
                minuto = 0;
            }
            segundo = 0;
        }
        metadeSegundo = 0;
    }
    // Serial.println(segundo);
    ClockPoint = (~ClockPoint) & 0x01;
}

void TimeUpdate(void)
{
    if(ClockPoint)tm1637.point(POINT_ON);
    else tm1637.point(POINT_OFF);

    TimeDisp[0] = hora / 10;
    TimeDisp[1] = hora % 10;
    TimeDisp[2] = minuto / 10;
    TimeDisp[3] = minuto % 10;
    
    Update = OFF;
}
