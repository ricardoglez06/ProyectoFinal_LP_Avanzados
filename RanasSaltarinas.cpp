#include <stdio.h>
#include <algorithm>
#include <stdbool.h>
#include <string.h>

bool comparar(char pos[], char objetivo[], int tamano); // Declarar prototipos de funciones
void llenarArreglo(char pos[], char objetivo[], int tamano);
void imprimirRanas(char pos[], int tamano);
int funcionJuego(char pos[], char objetivo[], int tamano);

int main(){
    int tamano;
    printf("\x1b[38;5;147m¿Cuántas ranas de cada color quieres para esta juego?: "); // Preguntar al usuario el tamaño del tablero del juego
    scanf("%d", &tamano);
    tamano = tamano*2+1;
    char pos[tamano], objetivo[tamano]; // Declarar arreglos, uno inicial y otro final para evaluar el ciclo 

    char *usuarios[10];
    char nombre[20];
    int scores[10];
    int contador=0;
    int decision;
    do {
        if (contador == 10){
            printf("\nHas excedido el numero de partidas. Si quieres seguir jugando vuelve a iniciar el programa");
            break;
        }
        llenarArreglo(pos,objetivo,tamano); // Llamar a la funcion que llena los arreglos dependiendo el número de ranas ingresadas

        puts("\n\x1b[38;5;37mIngresa tu nombre de usuario");
        while (getchar() != '\n'); // Limpiar el salto de línea residual
        gets(nombre);
        printf("\n");
        usuarios[contador] = strdup(nombre);

        int intentos = funcionJuego(pos,objetivo,tamano);
        scores[contador] = intentos;

        for (int i=0; i<=contador;i++) { // for para recorrer los puntajes
            for (int k=contador; k>=0; k--) { // for para ordenar de mayor a menor
                if (scores[k] < scores[k-1]){
                    // intercambiar los puntajes
                    int aux = scores[k-1];
                    scores[k-1] = scores[k];
                    scores[k] = aux;

                    //intercambiar los nombres correspondientes a los puntajes
                    char *auxUsuario = usuarios[k-1];
                    usuarios[k-1] = usuarios[k];
                    usuarios[k] = auxUsuario;
                }
            }
        }

        printf("\x1b[38;5;249mTABLA DE SCORES\n");
        printf("Nombre\t Puntaje\n\n");

        for (int j=0; j<=contador; j++){ // for para imprimir la tabla de scores
            printf("%s", usuarios[j]);
            printf("\t %d\n\n", scores[j]);
        }

        printf("\x1b[38;5;9m¿Quieres terminar el juego? Ingresa 0 si así lo deseas, sino ingresa cualquier otro numero.\n");
        scanf("%d", &decision);

        contador++;
    } while (decision != 0);

    return 0;
}

bool comparar(char pos[], char objetivo[], int tamano){ // Funcion que compara que el arreglo inicial sea igual que el final
    for (int i=0; i<tamano; i++){ // For que recorre todas las posiciones del arreglo
        if (pos[i]!=objetivo[i]){ // If que revisa si la posición en i es diferente en los dos arreglos, si es diferente retorna- 
            return false;       // false y termina de evaluar
        }
    }
    return true; // Si son iguales todos los elementos en la posicion i, retorna true
}

void llenarArreglo(char pos[], char objetivo[], int tamano){ // Funcion para llenar el arreglo con n ranas
    for (int i=0; i<tamano;i++){ // For que recorre todas las posiciones del arreglo 
        if (i<(tamano/2)){ // If que obtiene n posiciones de la primera mitad del arreglo y le asigna valores al array inicial y al final
            pos[i]='A'; 
            objetivo[i]='R';
        }
        else if (i==(tamano/2)){ // If para buscar la mitad del array, si i es igual a la mitad de tamano se le asigna un espacio
            pos[i]=' ';
            objetivo[i]=' ';
        } else {
            pos[i]='R'; // Asignar valores a las posiciones restantes
            objetivo[i]='A';
        }
    }
}

void imprimirRanas(char pos[], int tamano){
    int cuadradoTamano=8;
    const char *bloque = "\u2588\u2588"; // Declarar constante con el unicode 2588 que es el ascii 219 para poder imprimir cuadritos
    if (tamano==11){
        cuadradoTamano=7;
    } else if (tamano==13){
        cuadradoTamano=6;
    } else if (tamano==15){
        cuadradoTamano=5;
    }

    for (int i=1; i<=cuadradoTamano; i++){ // For que recorre las filas del cuadrado
        for (int nVeces=0; nVeces<tamano; nVeces++){ // For que hace que se impriman los n cuadrados del tamaño ingresado pegados en la misma linea
            for (int j=1; j<=cuadradoTamano; j++){ // For que recorre las columnas del cuadro
                if (i==1 || i==cuadradoTamano || j==1 || j==cuadradoTamano){ // If que selecciona las orillas del cuadrado
                    printf("\x1b[38;5;11m%s", bloque); // Poner marco amarillo
                }
                else{
                    if ((i==2 || i==cuadradoTamano-1) && (j==2 || j==cuadradoTamano-1)){ // Quitar esquinas del cuadrado interno
                        printf("\x1b[38;5;11m%s", bloque); // Pintar las esquinas de amarillo
                    }
                    else{
                        if(pos[nVeces]=='A'){ // If que verifica el valor del arreglo, si es 'A', se imprime color azul los huecos restantes
                            printf("\x1b[38;5;4m%s", bloque); // Azul
                        } 
                        else if(pos[nVeces]=='R'){ // If que verifica el valor del arreglo, si es 'R', se imprime color rojo los huecos restantes
                            printf("\x1b[38;5;1m%s", bloque); // Rojo
                        }
                        else {
                            printf("\x1b[38;5;11m%s", bloque); // Amarillo lo que falta
                        }
                    }
                }
            }
        }
        printf("\n"); // Espacio para que no quede todo pegado
    }
}

int funcionJuego(char pos[], char objetivo[], int tamano){ // Funcion para mover las ranas de posicion
    int rana, intentos=0;
    do{
        imprimirRanas(pos, tamano);
        printf("\nElige posicion (1-%d): ",tamano); // Elegir la casilla de la rana a cambiar
        scanf("%d", &rana);
        printf("\n");
        rana--; // Restarle 1 a la casilla de la rana ingresada para que coincida con la posicion del arreglo

        if (pos[rana+1] == ' '){ // Verificar que exista un espacio en la siguiente posicion de la rana ingresada
            pos[rana+1] = pos[rana]; // Si hay espacio, asignar el valor de la posicion de la rana ingresada a la siguiente posicion
            pos[rana] = ' '; // Asignar el espacio nuevamente en la casilla ingresada ya que fue reemplazado por el valor de la rana ingresada
            intentos++;
        } 
        else if (pos[rana-1] == ' '){ // Verificar que exista un espacio en la posicion anterior de la rana ingresada
            pos[rana-1] = pos[rana];
            pos[rana] = ' ';
            intentos++;
        } 
        else if (pos[rana+1]!=pos[rana] && pos[rana+2] == ' '){ // Verificar que en la siguiente posicion de la rana ingresada no tenga el mismo-
            pos[rana+2] = pos[rana]; // valor (mismo color) y verificar que exista un espacio en las siguientes dos posiciones para que la rana
            pos[rana] = ' '; // pueda saltar y reemplazar su valor 
            intentos++;
        }
        else if (pos[rana-1]!=pos[rana] && pos[rana-2] == ' '){ // Lo mismo pero con la posicion anterior 
            pos[rana-2] = pos[rana];
            pos[rana] = ' ';
            intentos++;
        }
        else { 
            printf("Movimiento invalido\n"); // Cualquier otro movimiento va a ser invalido
        }
    }
    while (!comparar(pos, objetivo, tamano));
    
    imprimirRanas(pos, tamano);
    printf("\nHas ganado en %d intentos.\n\n", intentos); 

    return intentos;
}