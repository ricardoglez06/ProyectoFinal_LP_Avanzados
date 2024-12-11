#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// doble letra YA, verificar diccionario, tablero color puntuacion YA, puntuacion x letra YA, 
//matriz false con true en casillas cn puntos extra para poder multiplicarlos YA, 
// arreglar loop infinito (usar solo letras) YA
// verificar que tenga letra arriba,abajo,izq,derecha. Poner cordenadas cn numero/letra YA
// limitar letras/numeros al ingresar fila columna (1-15) YA
// si turno != 0 se puede poner letra donde sea YA.
// duplicado al ingresar una letra en vez de numero de fila

void imprimirTablero(char tablero[][15], int tableroPuntaje[][15]);
void cambiarLetras(char letras[7], bool cambiosLet[7]);
bool palabraValida(char palabraIngresada[], char letras[7], int tamano, char tablero[][15], int posFila, int posColumn);
bool procesarOrientacion(int orientacion, char palabraIngresada[], char tablero[][15], int posFila, int posColumn, int tamano, int tableroPuntaje[][15], int turno);
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
        printf("\n\x1b[38;5;229mSi gustas cambiar una letra, ingresala, si no, ingresa un punto (.) para dejar de cambiar y continuar: \x1b[0m\n");
        
        char input[100];
        scanf("%s", input);

        // Validar que no se ingrese más de un carácter
        if (strlen(input) != 1) {
            printf("\n\x1b[38;5;214mDebes ingresar un solo carácter.\x1b[0m\n\n");
            continue;
        }

        letACamb = input[0];

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

bool palabraValida(char palabraIngresada[], char letras[7], int tamano, char tablero[][15], int posFila, int posColumn, int orientacion){
    int letrasUsadas[7] = {0,0,0,0,0,0,0};
    int contador = 0;

    for (int i=0; i<tamano; i++){
        for (int j=0; j<7; j++){
            if (palabraIngresada[i] == letras[j] && letrasUsadas[j] == 0) {
                contador++;
                letrasUsadas[j] = 1;
                letras[j] = ' ';
                break;
            }
        }
    }

    if (contador != tamano){
        return false;
    } else {
        return true;
    }
}

bool procesarOrientacion(int orientacion, char palabraIngresada[], char tablero[][15], int posFila, int posColumn, int tamano, int tableroPuntaje[][15], int turno) {
    bool movCorrecto = true, extensionPalabra = false;
    char auxPalabra[15] = "", palabraExtendida[15] = "", palabraAValidar[15] = "";
    int puntos, totalPuntos, letrasDescruzadas=0;

    switch (orientacion) {
        case 1: { // Hacia arriba
            if (posFila - tamano < 0) {
                printf("\033[1;31m\nError: La palabra se sale del tablero hacia arriba.\n\033[0m");
                return false;
            }
            if (tablero[posFila][posColumn - 1] != ' ') {
                extensionPalabra = true;
                strcpy(auxPalabra, palabraIngresada);

                for (int i = 1; tablero[posFila - 1 + i][posColumn - 1] != ' '; i++) {
                    palabraExtendida[i - 1] = tablero[posFila - 1 + i][posColumn - 1];
                }
                strcpy(palabraExtendida, strrev(palabraExtendida));
                strcat(palabraExtendida, auxPalabra);
                strcpy(palabraAValidar, palabraExtendida);
            } else {
                strcpy(palabraAValidar, palabraIngresada);
            }

            for (int i = 0; i < tamano; i++) {
                if (tablero[posFila - 1 - i][posColumn - 1] == ' '){
                    letrasDescruzadas++;
                }
                if (tablero[posFila - 1 - i][posColumn - 1] != ' ' && tablero[posFila - 1 - i][posColumn - 1] != palabraIngresada[i]) {
                    movCorrecto = false;
                    break;
                } 
            }

            if (letrasDescruzadas==tamano && !extensionPalabra && turno!=0){
                printf("\033[1;31m\nLa palabra debe estar cruzada con otra\n\033[0m");
                return false;
            }

            if (movCorrecto) {
                for (int i = 0; i < tamano; i++) {
                    tablero[posFila - 1 - i][posColumn - 1] = palabraIngresada[i];
                    puntos = contarPuntos(palabraIngresada[i], posFila, posColumn, tableroPuntaje);
                    totalPuntos += puntos;
                }
                return true;
            } else {
                printf("\033[1;31m\nLa palabra no puede ser colocada en esa posición porque no coincide con la palabra existente.\n\n\033[0m");
                return false;
            }
            break;
        }
        case 2: { // Hacia abajo
            if (posFila + tamano > 16) {
                printf("\033[1;31m\nError: La palabra se sale del tablero hacia abajo.\n\033[0m");
                return false;
            }
            if (tablero[posFila - 2][posColumn - 1] != ' ') {
                extensionPalabra = true;
                strcpy(auxPalabra, palabraIngresada);

                for (int i = 1; tablero[posFila - 1 - i][posColumn - 1] != ' '; i++) {
                    palabraExtendida[i - 1] = tablero[posFila - 1 - i][posColumn - 1];
                }
                strcpy(palabraExtendida, strrev(palabraExtendida));
                strcat(palabraExtendida, auxPalabra);
                strcpy(palabraAValidar, palabraExtendida);
            } else {
                strcpy(palabraAValidar, palabraIngresada);
            }
            for (int i = 0; i < tamano; i++) {
                if (tablero[posFila - 1 + i][posColumn - 1] == ' '){
                    letrasDescruzadas++;
                }
                if (tablero[posFila - 1 + i][posColumn - 1] != ' ' && tablero[posFila - 1 + i][posColumn - 1] != palabraIngresada[i]) {
                    movCorrecto = false;
                    break;
                }
            }

            if (letrasDescruzadas==tamano && !extensionPalabra && turno!=0){
                printf("\033[1;31m\nLa palabra debe estar cruzada con otra\n\033[0m");
                return false;
            }

            if (movCorrecto) {
                for (int i = 0; i < tamano; i++) {
                    tablero[posFila - 1 + i][posColumn - 1] = palabraIngresada[i];
                    puntos = contarPuntos(palabraIngresada[i], posFila, posColumn, tableroPuntaje);
                    totalPuntos += puntos;
                }
                return true;
            } else {
                printf("\033[1;31m\nLa palabra no puede ser colocada en esa posición porque no coincide con la palabra existente.\n\n\033[0m");
                return false;
            }
            break;
        }
        case 3: { // Hacia la derecha
            if (posColumn + tamano > 16) {
                printf("\033[1;31m\nError: La palabra se sale del tablero hacia la derecha.\n\033[0m");
                return false;
            }
            if (tablero[posFila - 1][posColumn - 2] != ' ') {
                extensionPalabra = true;
                strcpy(auxPalabra, palabraIngresada);

                for (int i = 1; tablero[posFila - 1][posColumn - 1 - i] != ' '; i++) {
                    palabraExtendida[i - 1] = tablero[posFila - 1][posColumn - 1 - i];
                }
                strcpy(palabraExtendida, strrev(palabraExtendida));
                strcat(palabraExtendida, auxPalabra);
                strcpy(palabraAValidar, palabraExtendida);
            } else {
                strcpy(palabraAValidar, palabraIngresada);
            }

            for (int i = 0; i < tamano; i++) {
                if (tablero[posFila - 1][posColumn - 1 + i] == ' '){
                    letrasDescruzadas++;
                }
                if (tablero[posFila - 1][posColumn - 1 + i] != ' ' && tablero[posFila - 1][posColumn - 1 + i] != palabraIngresada[i]) {
                    movCorrecto = false;
                    break;
                }
            }

            if (letrasDescruzadas==tamano && !extensionPalabra && turno!=0){
                printf("\033[1;31m\nLa palabra debe estar cruzada con otra\n\033[0m");
                return false;
            }

            if (movCorrecto) {
                for (int i = 0; i < tamano; i++) {
                    tablero[posFila - 1][posColumn - 1 + i] = palabraIngresada[i];
                    puntos = contarPuntos(palabraIngresada[i], posFila, posColumn, tableroPuntaje);
                    totalPuntos += puntos;
                }
                return true;
            } else {
                printf("\033[1;31m\nLa palabra no puede ser colocada en esa posición porque no coincide con la palabra existente.\n\n\033[0m");
                return false;
            }
            break;
        }
        case 4: { // Hacia la izquierda
            if (posColumn - tamano < 0) {
                printf("\033[1;31m\nError: La palabra se sale del tablero hacia la izquierda.\n\033[0m");
                return false;
            }
            if (tablero[posFila - 1][posColumn] != ' ') {
                extensionPalabra = true;
                strcpy(auxPalabra, palabraIngresada);

                for (int i = 1; tablero[posFila - 1][posColumn - 1 + i] != ' '; i++) {
                    palabraExtendida[i - 1] = tablero[posFila - 1][posColumn - 1 + i];
                }
                strcpy(palabraExtendida, strrev(palabraExtendida));
                strcat(palabraExtendida, auxPalabra);
                strcpy(palabraAValidar, palabraExtendida);
            } else {
                strcpy(palabraAValidar, palabraIngresada);
            }
            for (int i = 0; i < tamano; i++) {
                if (tablero[posFila - 1][posColumn - 1 - i] == ' '){
                    letrasDescruzadas++;
                }
                if (tablero[posFila - 1][posColumn - 1 - i] != ' ' && tablero[posFila - 1][posColumn - 1 - i] != palabraIngresada[i]) {
                    movCorrecto = false;
                    break;
                }
            }

            if (letrasDescruzadas == tamano && !extensionPalabra && turno!=0){
                printf("\033[1;31m\nLa palabra debe estar cruzada con otra\n\033[0m");
                return false;
            }
            
            if (movCorrecto) {
                for (int i = 0; i < tamano; i++) {
                    tablero[posFila - 1][posColumn - 1 - i] = palabraIngresada[i];
                    puntos = contarPuntos(palabraIngresada[i], posFila, posColumn, tableroPuntaje);
                    totalPuntos += puntos;
                }
                return true;
            } else {
                printf("\033[1;31m\nLa palabra no puede ser colocada en esa posición porque no coincide con la palabra existente.\n\n\033[0m");
                return false;
            }
            break;
        }
    }
}


void llenarTablero(char letras[7], char tablero[][15], int tableroPuntaje[][15], bool cambiosLet[7]){
    char palabraIngresada[15], auxFila, auxLetras[7];
    int posColumn, posFila, turno=0, puntos, totalPuntos, tamano, orientacion;
    bool inputValido;

    while(turno<=15){
        inputValido = true;

        printf("\033[1;34mTurno: %d\033[0m\n", turno);
        cambiarLetras(letras, cambiosLet);
        imprimirTablero(tablero, tableroPuntaje);

        do {
            printf("\033[1;33mINGRESO DE PALABRA\033[0m\n");
            printf("\033[1;32mInstrucciones:\033[0m\n");
            printf("\033[1;33m---Si vas a cruzar una palabra, ingresa la palabra completa (aunque la letra donde se va a hacer el cruce no la tengas en tu mazo de letras)\033[0m\n");
            printf("\033[1;33m---Si vas a hacer una extension de palabra, solo ingresa la parte extendida, NO la palabra completa\033[0m\n");
            printf("\033[1;33m---Si es el primer turno, simplemente ingresa la palabra que deseas\033[0m\n");
            imprimirLetras(letras, cambiosLet); 

            printf("\n\033[1;31m~Si no tiene letras con las que formar una palabra valida, ingrese 'R' para revolver todo su mazo de letras, sino ingrese cualquier otra tecla~\033[0m\n");
            printf("\033[1;31mPRECAUCION: Al hacer esto perderá un turno\033[0m\n");

            // Limpiar el buffer y leer la decisión
            char decision;
            scanf(" %c", &decision);  // Espacio antes de %c para evitar leer un salto de línea residual
            while (getchar() != '\n');  // Limpiar el buffer de entrada

            if (decision == 'R' || decision == 'r') {
                for (int i=0; i<7; i++){
                    letras[i] = ' ';
                }
                continue;  // Revolver el mazo de letras y perder turno
            }

            for (int i=0; i<7; i++){
                auxLetras[i] = letras[i];
            }

            printf("\n\033[1;36m¿Cual palabra quiere ingresar en el tablero? \033[0m\n");
            while (getchar() != '\n'); // Limpiar el buffer
            gets(palabraIngresada);
            tamano = strlen(palabraIngresada);

            if (tamano > 8){
                printf("\033[1;31mIngresa palabras de 8 letras o menos\033[0m\n");
                turno--;
                continue;
            }

            for (int i=0; i<tamano; i++){
                if(!isalpha(palabraIngresada[i])){
                    printf("\033[1;31mIngresa unicamente letras\033[0m\n");
                    inputValido = false;
                    break;
                } else {
                    palabraIngresada[i] = toupper(palabraIngresada[i]);
                }
            }

            if (!inputValido){
                turno--;
                continue;
            } 
            
            if (turno == 0){
                auxFila = 'H';
                posFila = auxFila - 64;
                posColumn = 8;
                orientacion = 3;
            } else {
                printf("\033[1;32mIngrese la LETRA de la FILA donde pondrá la PRIMERA letra: \033[0m\n");
                scanf(" %c", &auxFila);
                auxFila = toupper(auxFila);
                posFila = auxFila - 64;
                if(!isalpha(auxFila) || auxFila > 'O'){ //verificar que si sea letra y esté en el tablero
                    printf("\033[1;31m\nLETRA de fila inválida.\033[0m\n\n");
                    inputValido = false;
                    turno--;
                    continue;
                }

                printf("\033[1;32mIngrese el NÚMERO de la COLUMNA donde pondrá la PRIMERA letra: \033[0m\n");
                scanf(" %d", &posColumn);
                if(posColumn<1 || posColumn>15){
                    printf("\033[1;31m\nNÚMERO de columna inválido.\033[0m\n\n");
                    inputValido = false;
                    turno--;
                    continue;
                }

                printf("\033[1;36mELIGE EL NUMERO DE LA ORIENTACION QUE QUIERE: \033[0m");
                printf("\n'1' - La palabra va hacia arriba\n'2' - La palabra va hacia abajo\n'3' - La palabra va hacia la derecha\n'4' La palabra va hacia la izquierda\n");
                scanf("%d", &orientacion);
            }

            if (!palabraValida(palabraIngresada, letras, tamano, tablero, posFila, posColumn, orientacion)){
                printf("\033[1;31m\nIngresa una palabra con las letras disponibles\n\033[0m");
                printf("\033[1;33mO si es que quieres cruzar la palabra con otra ya existente, ingresa toda la palabra aun cuando no tengas en el mazo la letra que vas a cruzar\033[0m\n");
                for (int i=0; i<7; i++){
                    letras[i] = auxLetras[i];
                }
                
                turno--;
                continue;
            } 
        
            procesarOrientacion(orientacion, palabraIngresada, tablero, posFila, posColumn, tamano, tableroPuntaje, turno);

            if (!procesarOrientacion(orientacion, palabraIngresada, tablero, posFila, posColumn, tamano, tableroPuntaje, turno)){
                for (int i=0; i<7; i++){
                    letras[i] = auxLetras[i];
                }
                turno--;
                continue;
            }
        } while (!inputValido || !procesarOrientacion);

        imprimirTablero(tablero, tableroPuntaje); // Imprime el tablero
        printf("\n");

        turno++; 
    }

    printf("\n\n\033[1;32mEl juego se ha terminado porque se te acabaron los turnos.\033[0m\n");
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