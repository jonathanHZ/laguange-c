//
//  main.c
//  integracion-numerica
//
//  Created by Jonathan Hernandez Zapata on 9/29/16.
//  Copyright © 2016 Jonathan Hernandez Zapata. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

float funcion(float x, float l){
//    return 1 / sqrt(1 - (l * pow(sin(x), 2)));
    
    return ( pow(FLT_EPSILON, x) - (2 * x) );
};

float trapecioCompuesto(int m, float a, float b, float l) {
    int i;
    float valor = 0, h, x[m + 1], y[m + 1], temporal;
    
    h = (b -a)/m;
    
    x[0] = a;
    y[0] = funcion(a,l);
    
    for (i = 1; i <= m; i++) {
        temporal = x[i - 1] + h;
        x[i] = temporal;
        y[i] = funcion(temporal, l);
    }
    
    
    valor = 0;
    
    for (i = 0; i < m; i++) {
        valor = valor + ( h/2 * (y[i] + y[i + 1]));
    }
    
    return valor;
};

float simpson13compuesto(int m, float a, float b, float l) {
    float h, integ = 0, sumaPar = 0, sumaImpar = 0;
    
    if (m % 2 != 0) {
        printf("el numero de intervalos debe ser par.");
        return 99999;
    } else {
        
        h = (b - a) / (2 * m);
        
        integ = funcion(a, l);
        
        for (int i = 1; i < m; i++) {
            if (i % 2 == 1) {
                sumaImpar += funcion((a + (i * h)), l);
            } else {
                sumaPar += funcion((a + (i * h)), l);
            }
        }
        
        integ += 4 * sumaImpar;
        integ += 2 * sumaPar;
        integ += funcion(b, l);
        integ = (h / 3) * integ;
        
        return integ;
    }
}

void simpson38compuesto(int m, float a, float b, float l) {
    float h, x;
    
    h = (b - a) / (3 * m);
    
    for (int i = 0; i <= 3 * m; i++) {
        x = a + (i * h);
        printf("x%i = %f , y%i = %f \n",i , x, i, funcion(x, l));
    }
}

int main(int argc, const char * argv[]) {
    int m, i;
    float l, a, b;

    printf("Ingrese el valor de a: ");
    scanf("%f",&a);
    printf("Ingrese el valor de b: ");
    scanf("%f",&b);
    printf("Ingrese el valor de l: ");
    scanf("%f",&l);
    printf("Ingrese el valor de m: ");
    scanf("%i",&m);
    
    //para hallar los valores de la integral de forma normal
    //http://www.wolframalpha.com/widgets/view.jsp?id=27b5c10580589766332d905efb60a6f
    
    printf("\n\nIngrese el número del método que desea usar \n\n[0]Trapecio\n[1]Simpson 1/3\n[2]Simpson 3/8\n[100]Para salir\n");
    scanf("%i",&i);
    switch (i) {
        case 0:
            printf("I= %f\n",trapecioCompuesto(m, a, b, l));
            break;
        
        case 1:
            printf("I= %f\n",simpson13compuesto(m, a, b, l));
            break;
        
        case 2:
            simpson38compuesto(m, a, b, l);
            break;
            
        default:
            break;
    }

    return 0;
}
