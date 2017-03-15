///Users/JhernandezZ/Documents/c/integracion-numerica/integracion-numerica/main.c
//  main.c
//  runge-kutta
//
//  Created by Jonathan Hernandez Zapata on 10/20/16.
//  Copyright © 2016 Jonathan Hernandez Zapata. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

float yUno = 1;
float zUno = 3.5;
float xUno = 1;
int intervalos = 3;
float a = 1;
float b = 1.3;
float xi[4];
float yi[4];
float zi[4];

float f(float x, float y, float z){
    return z;
}

float F(float x, float y, float z){
    return ( ((8.75 * y)/(pow(x, 2))) + z - (3.5 * pow(x, 2.5)) );
}

int main(int argc, const char * argv[]) {
    
    float k, k1, k2, k3, k4, K, K1, K2, K3, K4;
    
    float h = (b -a)/intervalos;
    
    xi[0] = xUno;
    yi[0] = yUno;
    zi[0] = zUno;
    
    for (int i = 0; i < intervalos; i++) {
        k1 = f(xi[i], yi[i], zi[i]);
        K1 = F(xi[i], yi[i], zi[i]);
        
        k2 = f(xi[i] + (h/2), yi[i] + ((h/2) * k1), zi[i] + ((h/2) * K1));
        K2 = F(xi[i] + (h/2), yi[i] + ((h/2) * k1), zi[i] + ((h/2) * K1));
        
        k3 = f(xi[i] + (h/2), yi[i] + ((h/2) * k2), zi[i] + ((h/2) * K2));
        K3 = F(xi[i] + (h/2), yi[i] + ((h/2) * k2), zi[i] + ((h/2) * K2));
        
        k4 = f(xi[i] + h, yi[i] + (h * k3), zi[i] + (h * K3));
        K4 = F(xi[i] + h, yi[i] + (h * k3), zi[i] + (h * K3));
        
        k = (k1 + (2 * k2) + (2 + k3) + k4)/6;
        K = (K1 + (2 * K2) + (2 + K3) + K4)/6;
        
        xi[i + 1] = xi[i] + h;
        yi[i + 1] = yi[i] + (h * k);
        zi[i + 1] = zi[i] + (h * K);
    }
    
    for (int i = 1; i < intervalos + 1; i++) {
        printf("x%i = %f \n",i ,xi[i]);
        printf("y%i = %f \n",i ,yi[i]);
        printf("z%i = %f \n\n",i ,zi[i]);
    }
    return 0;
}
