#include <stdio.h>
#include <algorithm>

int main(){
    int rana;

    char pos[7] = {'A','A','A',' ','R','R','R'};

    for (int i=0; i<7; i++){
        printf("%c", pos[i]);
    }

    printf("\nElige posicion 1-7\n");
    scanf("%d", &rana);
    rana--;

    if (pos[rana]== ' '){
        printf("Movimiento invalido");
    }

    if (pos[rana+1] == ' '){
        pos[rana+1] = pos[rana];
        pos[rana] = ' ';
    } 
    else if (pos[rana-1] == ' '){
        pos[rana-1] = pos[rana];
        pos[rana] = ' ';
    } 
    else if (pos[rana+1]!=pos[rana] && pos[rana+2] == ' '){
        pos[rana+2] = pos[rana];
        pos[rana] = ' ';
    }
    else if (pos[rana-1]!=pos[rana] && pos[rana-2] == ' '){
        pos[rana-2] = pos[rana];
        pos[rana] = ' ';
    }
    else {
        printf("Movimiento invalido");
    }

       
    for (int i=0; i<7; i++){
        printf("%c", pos[i]);
    }
}