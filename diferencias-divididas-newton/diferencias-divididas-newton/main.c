//
//  main.c
//  diferencias-divididas-newton
//
//  Created by Jonathan Hernandez Zapata on 9/24/16.
//  Copyright © 2016 Jonathan Hernandez Zapata. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    //Se recorre el archivo para encontrar las incognitas, número de puntos, y cantidad de datos
    int posiciones = 0, puntos, incognitas = 0;
    float temporal;
    FILE *fp;
    fp = fopen ( "archivo.txt", "r" );
    if (fp==NULL) {
        fputs ("Error",stderr);
        exit (1);
    } else {
        while(feof(fp)==0){
            fscanf(fp, "%f", &temporal);
            if (temporal == 666) {
                incognitas++;
                temporal = 0;
            }
            posiciones++;
        }
    }
    fclose(fp);
    
    posiciones--;
    puntos = (posiciones/2) - incognitas;
    printf("\nValores a interpolar: %i\n", incognitas);
    printf("Puntos: %i\n", puntos);
    printf("Datos: %i\n\n", posiciones);
    
    //Se almacena en un vector los datos del archivo
    float number[posiciones];
    int i=0;
    FILE *fpo;
    fpo = fopen ( "archivo.txt", "r" );
    if (fpo==NULL) {
       fputs ("Error",stderr);
        exit (1);
    } else {
        while(feof(fpo)==0){
            fscanf(fpo, "%f", &number[i]);
            i++;
        }
    }
    
    fclose(fpo);

    
    int j, k, contador, contadorX, contadorY;
    float xInterpolar[incognitas], x[puntos], y[puntos];
    
    float diferencias[puntos][puntos];
    
    contadorX = 0;
    contadorY = 0;
    contador = 0;
    
    // Se construyen los vectores x e y
    for (j = 0; j < posiciones; j = j+2) {
        if (number[j + 1] != 666) {
            x[contador] = number[j];
            y[contador] = number[j + 1];
            contador++;
        } else {
            xInterpolar[contadorX] = number[j];
            contadorX++;
        }
    }
    
    //Se muestran los valores a interpolar
    printf("\nValores de x a interpolar\n");
    printf("[  ");
    for (j = 0; j < contadorX; j++) {
        printf("%f  ", xInterpolar[j]);
    }
    printf("] \n\n");
    
    //llenar tabla cde difrencias divididas con ceros
    for (j = 0; j < puntos; j++) {
        for (i = 0; i < puntos - j; i++) {
            diferencias[j][i] = 0;
        }
    }
    
    //Inicializar tabla de direncias dividas con datos de y
    for (j = 0; j < puntos; j++) diferencias[j][0] = y[j];
    
    //Se cálcula la matriz de direncias divididas
    for (j = 1; j < puntos; j++) {
        for (i = 0; i < puntos - j; i++) {
            diferencias[i][j] = (diferencias[i + 1][j - 1] - diferencias[i][j - 1])/(x[i + j] - x[i]);
        }
    }
    
    //Se muestra la matriz de diferencias divididas
    printf("\nMatriz de diferencias divididas");
    for (j = 0; j < puntos; j++) {
        printf("\n");
        for (k = 0; k < puntos; k++) {
            printf("%.13f ", diferencias[j][k]);
        }
    }
    printf("\n\n");
    
    //Interpolar valores
    float xt = 1;
    float yi = diferencias[0][0];
    for (j = 0; j < contadorX; j++) {
        for (k = 0; k < puntos - 1; k++) {
            xt = xt * (xInterpolar[j] - x[k]);
            yi = yi + diferencias[0][k+1] * xt;
        }
        xInterpolar[j] = yi;
        xt = 1;
        yi = diferencias[0][0];
    }
    
    //Se muestran los valores interpolados
    printf("\nValores interpolados\n");
    for (i = 0; i < contadorX; i++) {
        printf("x%i: %.10f \n", i, xInterpolar[i]);
    }
    printf("\n\n");
    
    system("PAUSE");	
    return 0;
}
