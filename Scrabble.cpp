#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void imprimirTablero(char tablero[][15], int tableroPuntaje[][15]);
void cambiarLetras(char letras[7], bool cambiosLet[7]);
void llenarTablero(char letras[7], char tablero[][15], int tableroPuntaje[][15], bool cambiosLet[7]);
void imprimirLetras(char letras[7], bool cambiosLet[7]);
int contarPuntos(char letraIngresada, int posFila, int posColumn, int tableroPuntaje[][15]);
void tableroConPuntos(int tableroPuntaje[][15]);

int main(){ 
    char letras[7];
    char tablero[15][15];
    int tableroPuntaje[15][15];
    bool cambiosLet[7] = {0,0,0,0,0,0,0}; //flag para que solo pueda cambiar una vez la letra por turno
    srand(time(NULL));
    for (int i=0; i<7; i++){ //llenar arr de letras random
        letras[i] = (rand() % (90-65+1))+65;
    }
    for (int i=0; i<15; i++){ //declarar arreglo vacio que es el tablero donde se pondrán las letras
        for (int j=0; j<15; j++){
            tablero[i][j]=' ';
        }
    }
    tableroConPuntos(tableroPuntaje);
    llenarTablero(letras, tablero, tableroPuntaje, cambiosLet);
    
}

void imprimirTablero(char tablero[][15], int tableroPuntaje[][15]){
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
            if(i==j){
                if(tableroPuntaje[i][j]<7){ //diagonal para la izquierda pts extra
                    printf("\x1b[48;5;159m %c ", tablero[i][j]); // x2
                } else{
                    printf("\x1b[48;5;212m %c ", tablero[i][j]); // x3
                }
            } else{
                if(i+j==14){ //diagonal para la derecha pts extra
                    if(tableroPuntaje[i][j]<7){
                        printf("\x1b[48;5;159m %c ", tablero[i][j]); // x2
                    } else{
                        printf("\x1b[48;5;212m %c ", tablero[i][j]); // x3
                    }
                } else{
                    if((i==7) && (j==1 || j==3 || j==11 || j==13)){ // casillas de la linea de en medio horizontal pts extra
                        if(tableroPuntaje[i][j]<7){ 
                            printf("\x1b[48;5;159m %c ", tablero[i][j]); // x2
                        } else{
                            printf("\x1b[48;5;212m %c ", tablero[i][j]); // x3
                        }
                    } else{
                        if(j==7 && (i==1 || i==3 || i==13 || i==11)){ // casillas de la linea de en medio vertical pts extra
                            if(tableroPuntaje[i][j]<7){
                                printf("\x1b[48;5;159m %c ", tablero[i][j]); // x2
                            } else{
                                printf("\x1b[48;5;212m %c ", tablero[i][j]); // x3
                            }
                        } else{
                            if ((i+j)%2==0){ // intercalar colores tipo ajedrez
                                printf("\x1b[48;5;194m %c ", tablero[i][j]); 
                            }
                            else {
                                printf("\x1b[48;5;230m %c ", tablero[i][j]);
                            }
                        }
                    }
                }
            }
        }
        printf("\x1b[0m\n");
    }
    printf("\n");
}

void imprimirLetras(char letras[7], bool cambiosLet[7]){
    for (int i=0; i<7; i++){
        if(cambiosLet[i]==0){
            printf("\x1b[38;5;41m%c\x1b[0m       ",letras[i]);
        } else {
            printf("\x1b[38;5;1m%c\x1b[0m       ",letras[i]);
        }
        
    }
}

void cambiarLetras(char letras[7], bool cambiosLet[7]){
    char letACamb;
    int posEncont, totCambios=0;
    

    for (int i=0; i<7; i++){ //llenar arr de letras random
        if(letras[i]==' '){ // si hay espacio vacio, llenar con random
            letras[i] = (rand() % (90-65+1))+65;
        }
    }
    
    while(true){
        printf("\n\x1b[41m- - - - - C A M B I O  D E  L E T R A S - - - - -\x1b[0m\n\n");
        imprimirLetras(letras,cambiosLet);
        printf("\n\x1b[38;5;229mSi gustas cambiar una letra, ingresala, si no, ingresa un punto (.) para dejar de cambiar y continuar: \x1b[0m");
        scanf(" %c", &letACamb);
        printf("\n");
        if(letACamb=='.'){
            break;
        } else{
            if (isalpha(letACamb)){ //verificar que sea letra
                letACamb = toupper(letACamb); // a mayuscula
                for (int i=0; i<7; i++){ //recorrer el las 7 letras
                    if (letras[i]==letACamb){ // si la letra ingresada existe
                        if (cambiosLet[i]==0){ // y si no se ha cambiado
                            letras[i] = rand()%(90-65+1)+65; // cambia la letra
                            cambiosLet[i] = 1; // y pone true para que no se pueda cambiar de nuevo
                            totCambios++; // suma total de cambios
                            printf("\nLa letra \x1b[38;5;33m%c\x1b[0m ha cambiado a \x1b[38;5;33m%c\x1b[0m\n\n",letACamb, letras[i]);
                            break; //romper ciclo para q no evalue las demás
                        } else{
                            printf("\n\x1b[38;5;214mYa has cambiado esa letra.\x1b[0m\n\n");
                        }
                    }
                }
            } else{
                printf("\n\x1b[38;5;214mDebes ingresar una letra.\x1b[0m\n\n");
            }
        }
        if(totCambios==7){
            printf("\n\x1b[38;5;214mYa cambiaste todas las letras. Continuando.\x1b[0m\n\n");
            break;
        }
    }

    for(int i=0; i<7; i++){ //volver a poner las banderas en false para el siguiente turno
        cambiosLet[i]=0;
    }
}

void llenarTablero(char letras[7], char tablero[][15], int tableroPuntaje[][15], bool cambiosLet[7]){
    char letraIngresada, auxFila;
    int posColumn, posFila, turno=0, letrasPuestas, puntos, totalPuntos;
    //for(int k=0; k<7; k++){ // for de 7 porque son 7 letras nada mas 
         //llamar funcion para cambiar las letras
    while(turno<=15){
        letrasPuestas = 0;  
        printf("\x1b[38;5;135mTurno: %d\x1b[0m\n", turno);
        cambiarLetras(letras, cambiosLet);
        imprimirTablero(tablero, tableroPuntaje);
        do{
            printf("\x1b[41m- - - - - A C O M O D O  D E  L E T R A S - - - - -\x1b[0m\n\n");
            imprimirLetras(letras, cambiosLet); 
            printf("\n\x1b[38;5;229mIngrese una letra, si quiere dejar de ingresar letras ingrese un punto (.): \x1b[0m");
            scanf(" %c", &letraIngresada); // ingresar letra a utilizar en el tablero
            if(isalpha(letraIngresada)){
                letraIngresada = toupper(letraIngresada);
                if (letraIngresada=='.'){
                    break;
                }
                for(int i=0; i<7; i++){ // for de 7 para verificar todas las posiciones del arreglo letras
                    if(letraIngresada==letras[i]){ // si la letra ingresada existe en el arreglo letras, ejecutar.
                        if (turno==0 && letrasPuestas==0){
                            printf("\n\x1b[38;5;214mEn el primer turno SIEMPRE tienes que empezar en la casilla central (H,8)\x1b[0m\n");
                        }

                        printf("Ingrese la \x1b[31mLETRA\x1b[0m de la \x1b[31mFILA\x1b[0m donde pondrá la letra: ");
                        scanf(" %c", &auxFila);
                        auxFila = toupper(auxFila);
                        if(!isalpha(auxFila) || auxFila > 'O'){ //verificar que si sea letra y esté en el tablero
                            printf("\n\x1b[38;5;214LETRA de fila inválida.\x1b[0m\n\n");
                            break;
                        }
                        posFila = auxFila-64;

                        printf("Ingrese el \x1b[31mNÚMERO\x1b[0m de la \x1b[31mCOLUMNA\x1b[0m donde pondrá la letra: ");
                        scanf(" %d", &posColumn);
                        if(posColumn<1 || posColumn>15){
                            printf("\n\x1b[38;5;214NÚMERO de columna inválido.\x1b[0m\n\n");
                            break;
                        }

                        if(turno==0 && letrasPuestas==0){ // hacer que en el primer turno se coloque casilla en medio
                            if(posColumn!=8 || posFila!=8){
                                printf("\n\x1b[38;5;214mCasillas invalidas, en el primer turno SIEMPRE tienes que empezar en la casilla central (H,8)\x1b[0m\n\n");
                                break;
                            }
                        }

                        if(tablero[posFila-1][posColumn-1]==' '){
                            //verificar que haya letra arriba o a la derecha o a la izquierda o abajo
                            if((turno==0 && letrasPuestas==0) || tablero[posFila-2][posColumn-1]!=' ' || tablero[posFila-1][posColumn]!=' ' || tablero[posFila-1][posColumn-2]!=' ' || tablero[posFila][posColumn-1]!=' '){
                                tablero[posFila-1][posColumn-1]=letraIngresada;//acomodar la letra ingresada en la fila y columna seleccionada
                                puntos = contarPuntos(letraIngresada, posFila, posColumn, tableroPuntaje);
                                totalPuntos+=puntos;
                                letras[i]=' '; // quitar letra de tus letras disponibles
                            } else{
                                printf("\n\x1b[38;5;214mNo puedes ingresar letras en una casilla donde no exista una letra al lado\x1b[0m\n\n");
                            }
                        } else{
                            printf("\n\x1b[38;5;214mLa casilla ingresada ya está ocupada por otra letra\x1b[0m\n\n");
                        }

                        letrasPuestas++;
                        if (letrasPuestas==7){
                            printf("\nHas utilizado todas tus letras disponibles. Continuando.\n\n");
                            break;
                        }

                        imprimirTablero(tablero, tableroPuntaje); //imprimir el tablero.
                        printf("\n");
                        break;
                    }
                }
            } else{
                if(letraIngresada!='.'){
                    printf("\n\x1b[38;5;214mIngresa una letra.\x1b[0m\n\n");
                }
            }
        } while(letraIngresada!='.');
        turno++;
        continue;
    }
    printf("\n\n\x1b[38;5;42mEl juego se ha terminado porque se te acabaron los turnos.\x1b[0m\n");
    printf("\x1b[38;5;10mHas terminado el juego con una puntuación de:\x1b[0m \x1b[38;5;202m%d\x1b[0m", totalPuntos);
}

void tableroConPuntos(int tableroPuntaje[][15]){
    srand(time(NULL));
    for (int i=0; i<15; i++){ //filas
        for (int j=0; j<15; j++){ //columnas
            if(i==j){
                    tableroPuntaje[i][j]=rand()%11; //diagonal para la izquierda
            } else{
                if(i+j==14){ //diagonal para la derecha
                    tableroPuntaje[i][j]=rand()%11;
                } else{
                    if((i==7) && (j==1 || j==3 || j==11 || j==13)){
                        tableroPuntaje[i][j]=rand()%11; // linea de en medio 
                    } else{
                        if(j==7 && (i==1 || i==3 || i==13 || i==11)){ // (3-2+1)+2
                            tableroPuntaje[i][j]=rand()%11; // linea de en medio para abajo 
                        } else{
                            if ((i+j)%2==0){ 
                                tableroPuntaje[i][j]=0;
                            }
                            else {
                                tableroPuntaje[i][j]=0;
                            }
                        }
                    }
                }
            }
        }
    }
}

int contarPuntos(char letraIngresada, int posFila, int posColumn, int tableroPuntaje[][15]){
    int puntuacion[27] = {1,3,3,2,1,4,2,4,1,6,5,1,3,1,1,3,8,1,1,1,1,4,4,6,4,8}; //A=1, B=3, C=3, D=2 etc.
    int puntajeTurno=0;
    if(tableroPuntaje[posFila-1][posColumn-1]==0){ // sumar puntaje
        puntajeTurno+=puntuacion[letraIngresada-65]; //letra - 65 porque el ASCII número 65 es A, entonces A-65 = 0, la posición 0 en el arreglo puntuación equivaldrá a los puntos de la letra A.
    }
    else{
        if(tableroPuntaje[posFila-1][posColumn-1]<7){ // menor a 7 porque se generan números aleatorios del 0 al 10
            puntajeTurno = (puntuacion[letraIngresada-65])*2;
        } else{
            puntajeTurno = (puntuacion[letraIngresada-65])*3;
        }
        //puntajeTotal+=(puntuacion[letraIngresada-65]*tableroPuntaje[posFila-1][posColumn-1]); // multiplicar x el numero que se declaró aleatoriamente (2-3)
    }
    return puntajeTurno;
}