#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimirTablero(char tablero[][15]);
void cambiarLetras(char letras[7]);
void llenarTablero(char letras[7], char tablero[][15]);
void imprimirLetras(char letras[7]);
int contarPuntos(char letras[7], char letraIngresada);

int main(){ 
    char letras[7];
    char tablero[15][15];
    srand(time(NULL));
    for (int i=0; i<7; i++){ //llenar arr de letras random
        letras[i] = (rand() % (90-65+1))+65;
    }
    for (int i=0; i<15; i++){ //declarar arreglo vacio
        for (int j=0; j<15; j++){
            tablero[i][j]=' ';
        }
    }
    llenarTablero(letras,tablero);
    
}

void imprimirTablero(char tablero[][15]){
    printf("   ");
    for (int k=1; k<=15; k++){ // for para los numeros de columnas
        if(k<=9){
            printf(" %d ", k);
        } else{
            printf("%d ", k);
        }
    }

    printf("\n");
    for (int i=0; i<15; i++){ //filas
        printf(" %c ",'A'+i); //letras filas
        for (int j=0; j<15; j++){ //columnas
            if ((i+j)%2==0){ // intercalar colores
                printf("\x1b[48;5;194m %c ", tablero[i][j]); 
            }
            else {
                printf("\x1b[48;5;230m %c ", tablero[i][j]);
            }
        }
        printf("\x1b[0m\n");
    }
    
}

void imprimirLetras(char letras[7]){
    for (int i=0; i<7; i++){
        printf("%c ",letras[i]);
    }
}

void cambiarLetras(char letras[7]){
    int posLet, contCambios=0;
    bool letCambio[7] = {0,0,0,0,0,0,0}; //flag para que solo pueda cambiar una vez la letra por turno
    for (int i=0; i<7; i++){ //llenar arr de letras random
        if(letras[i]==' '){ // si hay espacio vacio, llenar con random
            letras[i] = (rand() % (90-65+1))+65;
        }
    }

    do {
        printf("\n");
        imprimirLetras(letras); // llamar funcion para imprimir el tablero
        puts("\n1 2 3 4 5 6 7");
        printf("Presione 0 para continuar, si quiere cambiar una letra ingrese la posición numérica: ");
        scanf("%d",&posLet); //pedir posición de letra para cambiar
        printf("\n");
        if (posLet<=7 && posLet>=0){
            if (posLet==0){ // continuar
                printf("Continuando\n");
            } else { //cambiar letra de la posicion
                if (letCambio[posLet-1]==0){ // si todavia no se ha cambiado la letra entra al if
                    letras[posLet-1]=(rand() % (90-65+1))+65; //cambiar letra en la posición ingresada
                    letCambio[posLet-1] = true; // asignar true al arreglo con flags para que ya no se pueda cambiar
                    contCambios++;
                }
                else{
                    printf("Ya has cambiado esa letra, solo puedes cambiarla una vez por turno.\n\n");
                }
            }
        } else{
            printf("Posición no válida");
        }
    } while (posLet!=0);
    for(int i=0; i<7; i++){ //volver a poner las banderas en false
        letCambio[i]=0;
    }
}

void llenarTablero(char letras[7], char tablero[][15]){
    char letraIngresada;
    int puntuacion[27] = {1,3,3,2,1,4,2,4,1,6,5,1,3,1,1,3,8,1,1,1,1,4,4,6,4,8};
    int posFila, posColumn, turno=0, puntajeTotal=0;
    for(int k=0; k<7; k++){ // for de 7 porque son 7 letras nada mas 
        cambiarLetras(letras); //llamar funcion para cambiar las letras
        do{
            imprimirLetras(letras); 
            printf("\nIngrese una letra, si quiere dejar de ingresar letras ingrese un punto (.): ");
            scanf(" %c", &letraIngresada); // ingresar letra a utilizar en el tablero
            if (letraIngresada=='.'){ 
                break;
            }
            for(int i=0; i<7; i++){ // for de 7 para verificar todas las posiciones del arreglo letras
                if(letraIngresada==letras[i]){ // si la letra ingresada existe en el arreglo letras, ejecutar.
                    letras[i]=' '; // poner espacio en la posicion ingresada para que no se pueda utilizar de nuevo
                    if (turno==0){
                        printf("En el primer turno SIEMPRE tienes que empezar en la casilla central (8,8)\n");
                    }
                    printf("Ingrese el numero de la fila donde pondrá la letra: ");
                    scanf("%d", &posFila);
                    printf("Ingrese el numero de la columna donde pondrá la letra: ");
                    scanf("%d", &posColumn);
                    if(turno==0){ // hacer que en el primer turno se coloque casilla en medio
                        if(posColumn!=8 || posFila!=8){
                            turno--;
                            printf("Casillas invalidas, en el primer turno SIEMPRE tienes que empezar en la casilla central (8,8)\n");
                            continue;
                        }
                    }
                    turno++;
                    tablero[posFila-1][posColumn-1]=letraIngresada; //acomodar la letra ingresada en la fila y columna seleccionada
                    imprimirTablero(tablero); //imprimir el tablero.
                    //parte de puntuacion
                    puntajeTotal+=puntuacion[letraIngresada-65];
                    
                }
            }
            printf("%d", puntajeTotal);
        } while(1);
    }
}
