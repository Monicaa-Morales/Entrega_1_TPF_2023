int casillas_vacias();
char evaluar_tablero();
void declarar_ganador(char);
void mostrar_tablero();
void leer_jugada(char*, char*);
int es_jugada_valida(int,int);
void ubicar_dado(int,int,char);
void traducir_coordenadas(char,char,int*,int*);
void turno_maquina(char);

int casillas_vacias(){
    int cantidad = 0;
    for(int i=0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(tablero[i][j] == VACIO){
                cantidad++;
            }
        }
    }
    return cantidad;
}

char evaluar_tablero(){
    int cant_rojo = 0;
    int cant_verde = 0;
     for(int i=0; i < 5; i++){
        for(int j=0; j < 5; j++){
            if(tablero[i][j] != VACIO && tablero_color[i][j] == ROJO){
                cant_rojo++;
            }else if(tablero[i][j] != VACIO && tablero_color[i][j] == VERDE){
                cant_verde++;
            }
        }
    }
    if (cant_rojo > cant_verde)
        return ROJO;
    return VERDE;
}

void declarar_ganador(char ganador){
    printf("El ganador es el jugador de color ");
    if(ganador == ROJO)
        printf("ROJO!\n");
    else
        printf("VERDE!\n");
}

void mostrar_tablero(){

    int x = 5;
    printf("    A   B   C   D   E\n");
    printf("  +---+---+---+---+---+\n");
  for (int i = 0; i < 5; i++) {
    printf("%d | ", x--);
    for (int j = 0; j < 5; j++) {
        if(tablero[i][j] == VACIO){
            printf("  | ");
        }else{
            if(tablero_color[i][j] == ROJO){
                //ROJO
                printf("\033[1;31m");
            }else{
                printf("\033[1;32m");
            }
            printf("%d", tablero[i][j]);
            //Resettea el color
            printf("\033[0m");
            printf(" | ");
        }
    }
    printf("\n  +---+---+---+---+---+\n");
  }
}

void leer_jugada(char* letra, char* numero){
	char entrada[32]; // Array para almacenar la entrada del usuario

    do {
        printf("Ingrese la letra: ");
        scanf("%s", entrada);
        *letra = entrada[0];

        // Verifica si el entrada tiene solo un carácter alfabético
        if (strlen(entrada) != 1 || !isalpha(*letra)) {
            printf("Entrada no válida. Ingrese una letra válida (A, B, C, D, o E).\n");
        }
    } while (strlen(entrada) != 1 || !isalpha(*letra));

    // Limpia el búfer de entrada
    while (getchar() != '\n');

    do {
        printf("Ingrese el número: ");
        scanf("%s", entrada);
        *numero = entrada[0];

        // Verifica si el entrada tiene solo un carácter numérico
        if (strlen(entrada) != 1 || !isdigit(*numero)) {
            printf("Entrada no válida. Ingrese un número válido (1, 2, 3, 4, o 5).\n");
        }
    } while (strlen(entrada) != 1 || !isdigit(*numero));

    // Limpia el búfer de entrada
    while (getchar() != '\n');
}

int es_jugada_valida(int i, int j){
    if(i == -1 || j == -1)
        return 0;
    if(tablero[i][j] != VACIO){
    	printf("¡POSICION OCUPADA!\n");
        return 0;
    }
    // es valida
    return 1;
}
void mostrar_coordenadas(int i, int j){
    printf("(%c,%d)",'A'+j,5-i);
}
void traducir_coordenadas(char letra,char numero, int * i, int *j){
    switch(letra){
        case 'A':
        case 'a':
            *j = 0;
            break;
        case 'B':
        case 'b':
            *j = 1;
            break;
        case 'C':
        case 'c':
            *j = 2;
            break;
        case 'D':
        case 'd':
            *j = 3;
            break;
        case 'E':
        case 'e':
            *j = 4;
            break;
        default:
            *j = -1;
    }
    switch(numero){
        case '1':
            *i = 4;
            break;
        case '2':
            *i = 3;
            break;
        case '3':
            *i = 2;
            break;
        case '4':
            *i = 1;
            break;
        case '5':
            *i = 0;
            break;
        default:
            *i = -1;


    }

}




int imprimir_capturas(int i, int j){
 /*
                1. Izquierda y Arriba.
                2.  Izquierda y Derecha.
                3. Izquierda y Abajo.
                4. Arriba y Derecha.
                5. Arriba y Abajo.
                6. Derecha y Abajo.
                7. Izquierda Arriba Derecha
                8. Izquierda Arriba Abajo
                9. Izquierda Derecha Abajo
                10. Arriba Derecha Abajo
            */
    int opc = 0;

    //Todas las combinaciones con izquierda (2)
    if(j > 0 && tablero[i][j-1] != 0){
        if( i > 0 && tablero[i-1][j] != 0){
            if(tablero[i][j-1] + tablero[i-1][j] <= 6){
            opc++;
            printf("%d. ",opc);
            mostrar_coordenadas(i,j-1);
            printf(" y ");
            mostrar_coordenadas(i-1,j);
            printf("\n");
            }
        }
        if(j < 4 && tablero[i][j+1] != 0){
            if(tablero[i][j-1]+tablero[i][j+1] <= 6){
            opc++;
             printf("%d. ",opc);
             mostrar_coordenadas(i,j-1);
             printf(" y ");
             mostrar_coordenadas(i,j+1);
             printf("\n");
            }
        }
        if(i < 4 && tablero[i+1][j] != 0){
            if(tablero[i][j-1] + tablero[i+1][j] <= 6){
            opc++;
             printf("%d. ",opc);
            mostrar_coordenadas(i,j-1);
            printf(" y ");
            mostrar_coordenadas(i+1,j);
            printf("\n");
        }
    }
    }
    if(i > 0 && tablero[i-1][j] != 0){
        if(j < 4 && tablero[i][j+1] != 0){
            if(tablero[i-1][j] + tablero[i][j+1] <= 6){
                opc++;
                printf("%d. ",opc);
                mostrar_coordenadas(i-1,j);
                printf(" y ");
                mostrar_coordenadas(i,j+1);
                printf("\n");
            }
        }
        if(i < 4 && tablero[i+1][j] != 0){
            if(tablero[i-1][j] + tablero[i+1][j] <= 6){
                opc++;
                printf("%d. ",opc);
                mostrar_coordenadas(i-1,j);
                printf(" y ");
                mostrar_coordenadas(i+1,j);
                printf("\n");
            }
        }
    }
    if(j < 4 && i < 4 && tablero[i][j+1] != 0 && tablero[i+1][j] != 0){
        if(tablero[i][j+1] + tablero[i+1][j] <= 6){
            opc++;
            printf("%d. ",opc);
            mostrar_coordenadas(i,j+1);
            printf(" y ");
            mostrar_coordenadas(i+1,j);
            printf("\n");
        }
    }

    // Izquierda - Arriba - Derecha
    // Izquierda - Arriba - Abajo
    // Izquieda  - Derecha - Abajo

    if(j > 0 && tablero[i][j-1]!=0){
        if(i > 0 && tablero[i-1][j] != 0){
            if(j < 4 && tablero[i][j+1]!= 0){
                if (tablero[i][j-1] + tablero[i-1][j] + tablero[i][j+1] <= 6){
                    opc++;
                    printf("%d. ",opc);
                    mostrar_coordenadas(i,j-1);
                    printf(" , ");
                    mostrar_coordenadas(i-1,j);
                    printf(" y ");
                    mostrar_coordenadas(i,j+1);
                    printf("\n");
                }
            }
            if(i < 4 && tablero[i+1][j] != 0){
                  if (tablero[i][j-1] + tablero[i-1][j] + tablero[i+1][j] <= 6){
                    opc++;
                    printf("%d. ",opc);
                    mostrar_coordenadas(i,j-1);
                    printf(" , ");
                    mostrar_coordenadas(i-1,j);
                    printf(" y ");
                    mostrar_coordenadas(i+1,j);
                    printf("\n");
                }
            }
        }

        if(j < 4 && tablero[i][j+1] != 0){
            if(i < 4 && tablero[i+1][j] != 0){
                if (tablero[i][j-1] + tablero[i][j+1] + tablero[i+1][j] <= 6){
                    opc++;
                    printf("%d. ",opc);
                    mostrar_coordenadas(i,j-1);
                    printf(" , ");
                    mostrar_coordenadas(i,j+1);
                    printf(" y ");
                    mostrar_coordenadas(i+1,j);
                    printf("\n");
                }
            }
        }
    }

    if(i > 0 && j < 4 && i < 4 && tablero[i-1][j] != 0 && tablero[i][j+1] != 0 && tablero[i+1][j] != 0){
        if(tablero[i-1][j] + tablero[i][j+1] +  tablero[i+1][j] <= 6){
            opc++;
                    printf("%d. ",opc);
                    mostrar_coordenadas(i-1,j);
                    printf(" , ");
                    mostrar_coordenadas(i,j+1);
                    printf(" y ");
                    mostrar_coordenadas(i+1,j);
                    printf("\n");
        }
    }

   if(i > 0 && j > 0 && j < 4 && i < 4 && tablero[i-1][j] != 0 && tablero[i][j-1] != 0 && tablero[i][j+1] != 0 && tablero[i+1][j] != 0){
        if(tablero[i-1][j] + tablero[i][j-1] + tablero[i][j+1] +  tablero[i+1][j] <= 6){
                    opc++;
                    printf("%d. ",opc);
                    mostrar_coordenadas(i-1,j);
                    printf(" , ");
                    mostrar_coordenadas(i,j-1);
                    printf(" , ");
                    mostrar_coordenadas(i,j+1);
                    printf(" y ");
                    mostrar_coordenadas(i+1,j);
                    printf("\n");
        }
    }
    return opc;

}

int  realizar_captura_parcial(int i,int j, int opcion){
    int opc = 0;

    //Todas las combinaciones con izquierda (2)
    if(j > 0 && tablero[i][j-1] != 0){
        if( i > 0 && tablero[i-1][j] != 0){
            if(tablero[i][j-1] + tablero[i-1][j] <= 6){
            opc++;
            if(opc == opcion){
                tablero[i][j] = tablero[i][j-1] + tablero[i-1][j];
                tablero[i][j-1] = 0;
                tablero[i-1][j] = 0;

            }
            }
        }
        if(j < 4 && tablero[i][j+1] != 0){
            if(tablero[i][j-1]+tablero[i][j+1] <= 6){
            opc++;
             if(opc == opcion){
                tablero[i][j] = tablero[i][j-1] + tablero[i][j+1];
                tablero[i][j-1] = 0;
                tablero[i][j+1] = 0;

            }

            }
        }
        if(i < 4 && tablero[i+1][j] != 0){
            if(tablero[i][j-1] + tablero[i+1][j] <= 6){
            opc++;
            if(opc == opcion){
                tablero[i][j] = tablero[i][j-1] + tablero[i+1][j];
                tablero[i][j-1] = 0;
                tablero[i+1][j] = 0;

            }
            }
    }
    }
    if(i > 0 && tablero[i-1][j] != 0){
        if(j < 4 && tablero[i][j+1] != 0){
            if(tablero[i-1][j] + tablero[i][j+1] <= 6){
                opc++;
               if(opc == opcion){
                tablero[i][j] = tablero[i-1][j] + tablero[i][j+1];
                tablero[i-1][j] = 0;
                tablero[i][j+1] = 0;
            }
            }
        }
        if(i < 4 && tablero[i+1][j] != 0){
            if(tablero[i-1][j] + tablero[i+1][j] <= 6){
                opc++;
                if(opc == opcion){
                    tablero[i][j] = tablero[i-1][j] + tablero[i+1][j];
                    tablero[i-1][j] = 0;
                    tablero[i+1][j] = 0;
                }
            }
        }
    }
    if(j < 4 && i < 4 && tablero[i][j+1] != 0 && tablero[i+1][j] != 0){
        if(tablero[i][j+1] + tablero[i+1][j] <= 6){
             opc++;
             if(opc == opcion){
                    tablero[i][j] = tablero[i][j+1] + tablero[i+1][j];
                    tablero[i][j+1] = 0;
                    tablero[i+1][j] = 0;
            }
        }
    }

    // Izquierda - Arriba - Derecha
    // Izquierda - Arriba - Abajo
    // Izquieda  - Derecha - Abajo

    if(j > 0 && tablero[i][j-1]!=0){
        if(i > 0 && tablero[i-1][j] != 0){
            if(j < 4 && tablero[i][j+1]!= 0){
                if (tablero[i][j-1] + tablero[i-1][j] + tablero[i][j+1] <= 6){
                    opc++;
                    if(opc == opcion){
                        tablero[i][j] = tablero[i][j-1] + tablero[i-1][j] + tablero[i][j+1];
                        tablero[i][j-1] = 0;
                        tablero[i-1][j] = 0;
                        tablero[i][j+1] = 0;
                    }
                }
            }
            if(i < 4 && tablero[i+1][j] != 0){
                  if (tablero[i][j-1] + tablero[i-1][j] + tablero[i+1][j] <= 6){
                    opc++;
                     if(opc == opcion){
                        tablero[i][j] = tablero[i][j-1] + tablero[i-1][j] + tablero[i+1][j];
                        tablero[i][j-1] = 0;
                        tablero[i-1][j] = 0;
                        tablero[i+1][j] = 0;
                    }
                }
            }
        }

        if(j < 4 && tablero[i][j+1] != 0){
            if(i < 4 && tablero[i+1][j] != 0){
                if (tablero[i][j-1] + tablero[i][j+1] + tablero[i+1][j] <= 6){
                    opc++;
                     if(opc == opcion){
                        tablero[i][j] = tablero[i][j-1] + tablero[i][j+1] + tablero[i+1][j];
                        tablero[i][j-1] = 0;
                        tablero[i][j+1] = 0;
                        tablero[i+1][j] = 0;
                    }
                }
                }
            }
        }
    if(i > 0 && j < 4 && i < 4 && tablero[i-1][j] != 0 && tablero[i][j+1] != 0 && tablero[i+1][j] != 0){
        if(tablero[i-1][j] + tablero[i][j+1] +  tablero[i+1][j] <= 6){
            opc++;
            if(opc == opcion){
                        tablero[i][j] = tablero[i-1][j] + tablero[i][j+1] +  tablero[i+1][j];
                        tablero[i-1][j] = 0;
                        tablero[i][j+1] = 0;
                        tablero[i+1][j] = 0;
            }
        }
    }

    if(i > 0 && j > 0 && j < 4 && i < 4 && tablero[i-1][j] != 0 && tablero[i][j-1] != 0 && tablero[i][j+1] != 0 && tablero[i+1][j] != 0){
        if(tablero[i-1][j] + tablero[i][j-1] + tablero[i][j+1] +  tablero[i+1][j] <= 6){
                    opc++;
                    if(opc == opcion){
                        tablero[i][j] = tablero[i-1][j] + tablero[i][j-1] + tablero[i][j+1] +  tablero[i+1][j];
                        tablero[i-1][j] = 0;
                        tablero[i][j-1] = 0;
                        tablero[i][j+1] = 0;
                        tablero[i+1][j] = 0;
                    }
        }
    }
    return opc;
}
void ubicar_dado(int i, int j, char jugador){
    tablero[i][j] = 1;
    tablero_color[i][j] = jugador;
    //Cantidad de vecinos del dado colocado
    int cant_opc = imprimir_capturas(i,j);
    if(cant_opc > 0){
        cant_opc++;
        printf("%d. No capturar\n",cant_opc);
        int opcion;
        char aux;
        scanf("%d",&opcion);
        scanf("%c",&aux);
        realizar_captura_parcial(i,j,opcion);
    }
}

void turno_maquina(char color){
    srand(time(NULL));
    int decision = (rand() % casillas_vacias())+1;
    int cuenta= 0;
    int pos_i = 0, pos_j = 0;
    for(int i=0; i < 5; i++){
        for(int j=0; j < 5; j++){
            if(tablero[i][j] == VACIO){
                cuenta++;
                if(cuenta == decision){
                    pos_i = i;
                    pos_j = j;
                    tablero[i][j] = 1;
                    tablero_color[i][j] = color;
                }
            }
        }
    }
    //Llama una vez para saber la cantidad de opciones
    int cant_opc = realizar_captura_parcial(pos_i,pos_j,-1);
    //Elige la ultima opcion
    realizar_captura_parcial(pos_i,pos_j,cant_opc);
}
