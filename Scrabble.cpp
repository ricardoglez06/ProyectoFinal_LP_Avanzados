//CREADO POR:
//*Erick Fernando Pérez Cruz
//*Ángel Ricardo González Soto
//*Valeria Alejandra Araujo Martínez

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

void imprimirTablero(char tablero[][15], int tableroPuntaje[][15]);
int cambiarLetras(char letras[7], bool cambiosLet[7]);
bool palabraValida(char palabraIngresada[], char letras[7], int tamano, char tablero[][15], int posFila, int posColumn);
bool diccionarioValid(char palabraAValidar[]);
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

int cambiarLetras(char letras[7], bool cambiosLet[7]){
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

    return totCambios;
}

// Función que valida si la palabra ingresada es válida, comparándola con las letras disponibles
// y verificando que no se repitan letras de las disponibles.
// Función que verifica si una palabra ingresada es válida dentro de un tablero de juego
bool palabraValida(char palabraIngresada[], char letras[7], int tamano, char tablero[][15], int posFila, int posColumn, int orientacion){
    // Arreglo que mantiene el control de las letras que ya han sido usadas (inicialmente todas en 0)
    int letrasUsadas[7] = {0,0,0,0,0,0,0};
    // Contador que se utiliza para verificar que todas las letras coincidan
    int contador = 0;

    // Recorre cada letra de la palabra ingresada
    for (int i=0; i<tamano; i++){
        // Compara si la letra ingresada es igual a la letra de cruce para que el contador aumente aunque la letra que coincide no este en el mazo del usuario
        switch (orientacion)
        {
            case 1: { // Orientación hacia arriba
                if (tablero[posFila - 1 - i][posColumn - 1] == palabraIngresada[i]){
                    contador++; // Si la letra coincide, se incrementa el contador
                }
                break;
            }
            case 2: { // Orientación hacia abajo
                if (tablero[posFila - 1 + i][posColumn - 1] == palabraIngresada[i]){
                    contador++; // Si la letra coincide, se incrementa el contador
                }
                break;
            }
            case 3: { // Orientación hacia la derecha
                if (tablero[posFila - 1][posColumn - 1 + i] == palabraIngresada[i]){
                    contador++; // Si la letra coincide, se incrementa el contador
                }
                break;
            }
            case 4: { // Orientación hacia la izquierda
                if (tablero[posFila - 1][posColumn - 1 - i] == palabraIngresada[i]){
                    contador++; // Si la letra coincide, se incrementa el contador
                }
                break;
            }
        }

        // Verifica si la letra de la palabra ingresada está en las letras disponibles y no ha sido usada
        for (int j=0; j<7; j++){
            if (palabraIngresada[i] == letras[j] && letrasUsadas[j] == 0) {
                contador++; // Se incrementa el contador por la coincidencia
                letrasUsadas[j] = 1; // Se marca la letra como usada
                letras[j] = ' '; // Se elimina la letra del arreglo de letras disponibles
                break;
            }
        }
    }

    // Si el contador no es igual al tamaño de la palabra, significa que no todas las letras coincidieron
    if (contador != tamano){
        return false; // La palabra no es válida
    } else {
        return true; // La palabra es válida
    }
}



bool diccionarioValid(char palabraAValidar[]){
    char linea[100];  // Buffer para leer cada palabra del archivo
    bool encontrada;  // Variable para indicar si la palabra se encontró

    // Convertir palabraAValidar a minúsculas para comparación
    for (int i = 0; palabraAValidar[i] != '\0'; i++) {
        palabraAValidar[i] = tolower(palabraAValidar[i]);  // Convierte cada letra a minúsculas
    }

    // Abrir el archivo del diccionario
    FILE *fp = fopen("C:\\Users\\Ricardoo\\OneDrive\\Desktop\\ProyectoGithub\\diccionario_filtrado.txt", "r"); //Cambiar por la ruta del diccionario donde lo tiene el usuario
    if (fp == NULL) {
        printf("\033[31mError al abrir el archivo. ASEGURATE DE PONER CORRECTAMENTE LA RUTA DEL DICCIONARIO\033[0m\n");  // Si no se puede abrir el archivo, muestra un error
        return 1;  // Salir con código de error
    } 

    // Leer el archivo palabra por palabra usando fscanf
    while (fscanf(fp, "%s", linea) != EOF) {
        // Limpiar el salto de línea al final de la palabra leída
        linea[strcspn(linea, "\n")] = '\0';  // Eliminar salto de línea si está presente

        // Comparar la palabra leída con la palabra ingresada
        if (strcmp(linea, palabraAValidar) == 0) {
            encontrada = true;  // Se encuentra la palabra
            break;  // Salir del bucle al encontrar la palabra
        }
    }

    // Cerrar el archivo después de la lectura
    fclose(fp);

    // Mostrar el resultado de la búsqueda
    if (encontrada) {
        printf("\033[32mLa palabra '%s' SI EXISTE en el diccionario.\033[0m\n", palabraAValidar);
        return true;  // Retorna true si la palabra fue encontrada
    } else {
        printf("\033[32mLa palabra '%s' NO EXISTE en el diccionario.\033[0m\n", palabraAValidar);
        return false;  // Retorna false si la palabra no fue encontrada
    }
}

// Función que maneja la colocación de la palabra según la orientación y la posición en el tablero.
bool procesarOrientacion(int orientacion, char palabraIngresada[], char tablero[][15], int posFila, int posColumn, int tamano, int tableroPuntaje[][15], int turno) {
    bool movCorrecto = true, extensionPalabra = false; // Variables para verificar si el movimiento es correcto y si hay una extensión de palabra
    char auxPalabra[15] = "", palabraExtendida[15] = "", palabraAValidar[15] = ""; // Variables para manipular las palabras
    int puntos, totalPuntos, letrasDescruzadas=0; // Variables para el puntaje y el conteo de letras descruzadas

    switch (orientacion) {
        case 1: { // Hacia arriba
            if (posFila - tamano < 0) { // Verifica si la palabra se sale del tablero hacia arriba
                printf("\033[1;31m\nError: La palabra se sale del tablero hacia arriba.\n\033[0m");
                return false;
            }
            // Verifica si ya hay palabras en la posición donde se quiere colocar la nueva palabra
            if (tablero[posFila][posColumn - 1] != ' ') {
                extensionPalabra = true;
                strcpy(auxPalabra, palabraIngresada);

                // Extiende la palabra si ya hay una palabra en la dirección opuesta
                for (int i = 1; tablero[posFila - 1 + i][posColumn - 1] != ' '; i++) {
                    palabraExtendida[i - 1] = tablero[posFila - 1 + i][posColumn - 1];
                }
                strcpy(palabraExtendida, strrev(palabraExtendida)); // Reversa la palabra extendida
                strcat(palabraExtendida, auxPalabra); // Concatenar la palabra original
                strcpy(palabraAValidar, palabraExtendida);
            } else {
                strcpy(palabraAValidar, palabraIngresada);
            }

            if (!diccionarioValid(palabraAValidar)){
                return false;
            }

            // Verifica que la palabra que se va a colocar coincida con el tablero existente
            for (int i = 0; i < tamano; i++) {
                if (tablero[posFila - 1 - i][posColumn - 1] == ' '){
                    letrasDescruzadas++; // Cuenta las letras descruzadas
                }
                if (tablero[posFila - 1 - i][posColumn - 1] != ' ' && tablero[posFila - 1 - i][posColumn - 1] != palabraIngresada[i]) {
                    movCorrecto = false; // Si no coincide, el movimiento no es correcto
                    break;
                } 
            }

            // Si no hay cruce y la palabra no es extensión, muestra un error
            if (letrasDescruzadas == tamano && !extensionPalabra && turno != 0){
                printf("\033[1;31m\nLa palabra debe estar cruzada con otra\n\033[0m");
                return false;
            }

            // Si el movimiento es correcto, coloca la palabra en el tablero
            if (movCorrecto) {
                for (int i = 0; i < tamano; i++) {
                    tablero[posFila - 1 - i][posColumn - 1] = palabraIngresada[i]; // Coloca la palabra
                    puntos = contarPuntos(palabraIngresada[i], posFila, posColumn, tableroPuntaje); // Calcula los puntos
                    totalPuntos += puntos; // Suma los puntos
                }
                return true;
            } else {
                printf("\033[1;31m\nLa palabra no puede ser colocada en esa posición porque no coincide con la palabra existente.\n\n\033[0m");
                return false;
            }
            break;
        }
        case 2: { // Hacia abajo
            if (posFila + tamano > 16) { // Verifica si la palabra se sale del tablero hacia abajo
                printf("\033[1;31m\nError: La palabra se sale del tablero hacia abajo.\n\033[0m");
                return false;
            }
            // Similar al caso hacia arriba, verifica y maneja la extensión de palabras hacia abajo
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

            if (!diccionarioValid(palabraAValidar)){
                return false;
            } 

            // Verificación de la colocación correcta
            for (int i = 0; i < tamano; i++) {
                if (tablero[posFila - 1 + i][posColumn - 1] == ' '){
                    letrasDescruzadas++; // Cuenta las letras descruzadas
                }
                if (tablero[posFila - 1 + i][posColumn - 1] != ' ' && tablero[posFila - 1 + i][posColumn - 1] != palabraIngresada[i]) {
                    movCorrecto = false; // Si no coincide, el movimiento no es correcto
                    break;
                }
            }

            // Maneja errores similares al caso anterior
            if (letrasDescruzadas == tamano && !extensionPalabra && turno != 0){
                printf("\033[1;31m\nLa palabra debe estar cruzada con otra\n\033[0m");
                return false;
            }

            if (movCorrecto) {
                for (int i = 0; i < tamano; i++) {
                    tablero[posFila - 1 + i][posColumn - 1] = palabraIngresada[i]; // Coloca la palabra en el tablero
                    puntos = contarPuntos(palabraIngresada[i], posFila, posColumn, tableroPuntaje); // Calcula los puntos
                    totalPuntos += puntos; // Suma los puntos
                }
                return true;
            } else {
                printf("\033[1;31m\nLa palabra no puede ser colocada en esa posición porque no coincide con la palabra existente.\n\n\033[0m");
                return false;
            }
            break;
        }
        case 3: { // Hacia la derecha
            if (posColumn + tamano > 16) { // Verifica si la palabra se sale del tablero hacia la derecha
                printf("\033[1;31m\nError: La palabra se sale del tablero hacia la derecha.\n\033[0m");
                return false;
            }
            // Similar a los casos anteriores, verifica la colocación de palabras hacia la derecha
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
            
            if (!diccionarioValid(palabraAValidar)){
                return false;
            } 

            for (int i = 0; i < tamano; i++) {
                if (tablero[posFila - 1][posColumn - 1 + i] == ' '){
                    letrasDescruzadas++; // Cuenta las letras descruzadas
                }
                if (tablero[posFila - 1][posColumn - 1 + i] != ' ' && tablero[posFila - 1][posColumn - 1 + i] != palabraIngresada[i]) {
                    movCorrecto = false; // Si no coincide, el movimiento no es correcto
                    break;
                }
            }

            if (letrasDescruzadas == tamano && !extensionPalabra && turno != 0){
                printf("\033[1;31m\nLa palabra debe estar cruzada con otra\n\033[0m");
                return false;
            }

            if (movCorrecto) {
                for (int i = 0; i < tamano; i++) {
                    tablero[posFila - 1][posColumn - 1 + i] = palabraIngresada[i]; // Coloca la palabra en el tablero
                    puntos = contarPuntos(palabraIngresada[i], posFila, posColumn, tableroPuntaje); // Calcula los puntos
                    totalPuntos += puntos; // Suma los puntos
                }
                return true;
            } else {
                printf("\033[1;31m\nLa palabra no puede ser colocada en esa posición porque no coincide con la palabra existente.\n\n\033[0m");
                return false;
            }
            break;
        }
        case 4: { // Hacia la izquierda
            if (posColumn - tamano < 0) { // Verifica si la palabra se sale del tablero hacia la izquierda
                printf("\033[1;31m\nError: La palabra se sale del tablero hacia la izquierda.\n\033[0m");
                return false;
            }
            // Similar a los casos anteriores, maneja la colocación de palabras hacia la izquierda
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

            if (!diccionarioValid(palabraAValidar)){
                return false;
            } 

            for (int i = 0; i < tamano; i++) {
                if (tablero[posFila - 1][posColumn - 1 - i] == ' '){
                    letrasDescruzadas++; // Cuenta las letras descruzadas
                }
                if (tablero[posFila - 1][posColumn - 1 - i] != ' ' && tablero[posFila - 1][posColumn - 1 - i] != palabraIngresada[i]) {
                    movCorrecto = false; // Si no coincide, el movimiento no es correcto
                    break;
                }
            }

            if (letrasDescruzadas == tamano && !extensionPalabra && turno != 0){
                printf("\033[1;31m\nLa palabra debe estar cruzada con otra\n\033[0m");
                return false;
            }

            if (movCorrecto) {
                for (int i = 0; i < tamano; i++) {
                    tablero[posFila - 1][posColumn - 1 - i] = palabraIngresada[i]; // Coloca la palabra en el tablero
                    puntos = contarPuntos(palabraIngresada[i], posFila, posColumn, tableroPuntaje); // Calcula los puntos
                    totalPuntos += puntos; // Suma los puntos
                }
                return true;
            } else {
                printf("\033[1;31m\nLa palabra no puede ser colocada en esa posición porque no coincide con la palabra existente.\n\n\033[0m");
                return false;
            }
            break;
        }
    }
    return false; // En caso de no coincidir ninguna orientación
}


// Función para llenar el tablero con las palabras ingresadas por los jugadores
void llenarTablero(char letras[7], char tablero[][15], int tableroPuntaje[][15], bool cambiosLet[7]) {
    char palabraIngresada[15], auxFila, auxLetras[7], opcion; // Variables para almacenar la palabra ingresada y la fila seleccionada
    int posColumn, posFila, turno = 0, puntos, totalPuntos, tamano, orientacion; // Variables para la posición, puntos y orientación
    bool inputValido; // Variable para validar la entrada

    printf("\033[31mPARA QUE EL JUEGO SE EJECUTE CORRECTAMENTE ES NECESARIO QUE LA RUTA DEL DICCIONARIO ESTE PUESTA CORRECTAMENTE\033[0m\n");  
    //Advertencia para que sobre la llamada al archivo del diccionario

    // Bucle principal que se ejecuta hasta que se alcancen los 15 turnos
    while(turno <= 15) {
        inputValido = true; // Inicializa la validez de la entrada

        // Muestra el turno y actualiza las letras del jugador
        printf("\033[1;34mTurno: %d\033[0m\n", turno);

        int cambiosLetras = cambiarLetras(letras, cambiosLet); // Cambia las letras del jugador

        if (cambiosLetras == 7){
            // Ofrecer al usuario la opción de cambiar todo el mazo
            printf("\033[1;33m¿Quieres perder un turno para cambiar todas tus letras? Ingresa 'S' para Si, cualquier otra letra para No: \033[0m");
            scanf(" %c", &opcion);
            opcion = toupper(opcion);

            if (opcion == 'S' || opcion == 's') {
                for (int i = 0; i < 7; i++) {
                    letras[i] = (rand() % (90 - 65 + 1)) + 65; // Generar nuevas letras aleatorias
                }
                printf("\033[1;32mHas cambiado todas tus letras y perdido un turno (estara reflejado en el sig turno).\033[0m\n");
            }
        }

        // Ingreso de palabra en el tablero
        bool resOrientacion = false; // Inicializado en false, porque aún no se ha validado.

        do {
            imprimirTablero(tablero, tableroPuntaje); // Imprime el estado actual del tablero
            printf("\033[1;33mINGRESO DE PALABRA\033[0m\n");
            printf("\033[1;32mInstrucciones:\033[0m\n");
            printf("\033[1;33m---Si vas a cruzar una palabra, ingresa la palabra completa (aunque la letra donde se va a hacer el cruce no la tengas en tu mazo de letras)\033[0m\n");
            printf("\033[1;33m---Si vas a hacer una extension de palabra, solo ingresa la parte extendida, NO la palabra completa\033[0m\n");
            printf("\033[1;33m---Si es el primer turno, simplemente ingresa la palabra que deseas\033[0m\n");
            imprimirLetras(letras, cambiosLet); // Muestra las letras disponibles

            // Guarda las letras actuales para restaurarlas en caso de error
            for (int i = 0; i < 7; i++) {
                auxLetras[i] = letras[i];
            }

            // Solicita la palabra que el jugador quiere ingresar
            printf("\n\033[1;36m¿Cual palabra quiere ingresar en el tablero? \033[0m\n");
            while (getchar() != '\n'); // Limpiar el buffer
            gets(palabraIngresada); // Leer la palabra ingresada
            tamano = strlen(palabraIngresada); // Obtener el tamaño de la palabra

            // Verifica que la palabra no sea mayor de 8 letras
            if (tamano > 8) {
                printf("\033[1;31mIngresa palabras de 8 letras o menos\033[0m\n");
                turno--; // Reduce el turno en caso de error
                continue;
            }

            // Verifica que la palabra esté compuesta solo por letras
            for (int i = 0; i < tamano; i++) {
                if (!isalpha(palabraIngresada[i])) {
                    printf("\033[1;31mIngresa unicamente letras\033[0m\n");
                    inputValido = false; // Marca la entrada como inválida
                    break;
                } else {
                    palabraIngresada[i] = toupper(palabraIngresada[i]); // Convierte la palabra a mayúsculas
                }
            }

            // Si la entrada es inválida, se resta el turno y se reinicia el ciclo
            if (!inputValido) {
                turno--;
                continue;
            }

            // Si es el primer turno, configura la posición inicial y orientación predeterminada
            if (turno == 0) {
                auxFila = 'H';
                posFila = auxFila - 64; // Convierte la letra a número (A = 1, B = 2, ...)
                posColumn = 8; // Coloca la palabra en la columna central
                orientacion = 3; // Orientación hacia la derecha
            } else {
                // Solicita la fila y columna donde se colocará la primera letra
                printf("\033[1;32mIngrese la LETRA de la FILA donde pondrá la PRIMERA letra: \033[0m\n");
                scanf(" %c", &auxFila);
                auxFila = toupper(auxFila); // Convierte la letra a mayúsculas
                posFila = auxFila - 64; // Convierte la letra a número
                if (!isalpha(auxFila) || auxFila > 'O') { // Verifica que la fila esté dentro del tablero
                    printf("\033[1;31m\nLETRA de fila inválida.\033[0m\n\n");
                    inputValido = false; // Marca la entrada como inválida
                    turno--;
                    continue;
                }

                // Solicita el número de la columna
                printf("\033[1;32mIngrese el NÚMERO de la COLUMNA donde pondrá la PRIMERA letra: \033[0m\n");
                scanf(" %d", &posColumn);
                if (posColumn < 1 || posColumn > 15) { // Verifica que la columna esté dentro del tablero
                    printf("\033[1;31m\nNÚMERO de columna inválido.\033[0m\n\n");
                    inputValido = false; // Marca la entrada como inválida
                    turno--;
                    continue;
                }

                // Solicita la orientación de la palabra
                printf("\033[1;36mELIGE EL NUMERO DE LA ORIENTACION QUE QUIERE: \033[0m");
                printf("\n'1' - La palabra va hacia arriba\n'2' - La palabra va hacia abajo\n'3' - La palabra va hacia la derecha\n'4' La palabra va hacia la izquierda\n");
                scanf("%d", &orientacion);
            }

            // Verifica que la palabra sea válida con las letras disponibles
            if (!palabraValida(palabraIngresada, letras, tamano, tablero, posFila, posColumn, orientacion)) {
                printf("\033[1;31m\nPalabra invalida\n\033[0m");
                for (int i = 0; i < 7; i++) {
                    letras[i] = auxLetras[i]; // Restaura las letras del jugador
                }

                turno--; // Reduce el turno en caso de error
                continue;
            }

            // Procesa la orientación de la palabra en el tablero
            resOrientacion = procesarOrientacion(orientacion, palabraIngresada, tablero, posFila, posColumn, tamano, tableroPuntaje, turno);

            // Verifica si el procesamiento de la palabra fue exitoso
            if (!resOrientacion) {
                for (int i = 0; i < 7; i++) {
                    letras[i] = auxLetras[i]; // Restaura las letras del jugador
                }
                turno--; // Reduce el turno en caso de error
                continue;
            }
        } while (!inputValido || !resOrientacion); // Repite si la entrada es inválida o el procesamiento falla

        imprimirTablero(tablero, tableroPuntaje); // Imprime el tablero después de cada turno
        printf("\n");

        turno++; // Incrementa el turno
        if (opcion == 'S' || opcion == 's') {
            turno++;
            continue; // Saltar al siguiente turno
        }
    }

    // Mensaje final cuando se terminan los turnos
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