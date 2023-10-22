#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"
int tablero[5][5];
char tablero_color[5][5];
#include "functions.h"
int main(){
	int inicio_turno;
    int modo = 0;
    int maquina = 0;
    char jugador_color;
    char jugador_actual;
    while(modo != 1 && modo!= 2){
    printf("Seleccione modo de juego:\n");
    printf("1. Jugador vs Jugador.\n");
    printf("2. Jugador vs Maquina.\n");
    scanf("%d",&modo);
    }
    if(modo == 2){
        maquina = 1;
        int opcion_color = 0;
        while(opcion_color != 1 && opcion_color!= 2){
        printf("Seleccione su color:\n");
        printf("1. Rojo.\n");
        printf("2. Verde.\n");
        scanf("%d",&opcion_color);
        }

        if (opcion_color == 2){
            jugador_color = VERDE;
        }else{
        	jugador_color = ROJO;
        }
        printf("Seleccione quién empieza el juego:\n");
        printf("1. Rojo.\n");
        printf("2. Verde.\n");
        scanf("%d", &inicio_turno);
        if(inicio_turno == 2){
        	jugador_actual = VERDE;
        }else{
        	jugador_actual = ROJO;
        }

    }

    mostrar_tablero();
    char aux;
    scanf("%c",&aux);
    //Mientras el tablero no este lleno
    while(casillas_vacias() != 0){
        /*
            Elige donde colocar su dado
            Captura si es posible
            Se retornan los dados capturados a sus duenhos
        */
        printf("Es el turno del jugador %c\n", jugador_actual);
        if(maquina == 1 && jugador_actual != jugador_color){
            //Si es jugador vs maquina y es el turno de la maquina;
            turno_maquina(jugador_actual);
        }else{
            char letra, numero;
            int i,j;
            do{
                leer_jugada(&letra,&numero);
                traducir_coordenadas(letra,numero,&i,&j);
            }while(!es_jugada_valida(i,j));

            ubicar_dado(i,j,jugador_actual);
        }
        mostrar_tablero();


        if(jugador_actual == ROJO){
            jugador_actual = VERDE;
        }else{
            jugador_actual = ROJO;
        }
    }

    char ganador = evaluar_tablero();

    declarar_ganador(ganador);

    return 0;
}
