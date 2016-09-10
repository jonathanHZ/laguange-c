//
//  main.c
//  factorizacionLu
//
//  Created by Jonathan Hernandez Zapata on 9/10/16.
//  Copyright © 2016 Jonathan Hernandez Zapata. All rights reserved.
//


#include<stdio.h>
#include<stdlib.h>


int main()
{
    int i,j,k,nIncognitas;
    
    printf ("\nIngresa el numero de incognitas: ");
    scanf("%d",&nIncognitas);
    
    float a[nIncognitas][nIncognitas],b[nIncognitas],x[nIncognitas],l[nIncognitas][nIncognitas],y[nIncognitas],u[nIncognitas][nIncognitas],sum;
    float coeficienteMayor, auxiliarA, auxiliarB;
    int ecuacionPivote;
    
    
    //Ingreso de datos
    printf ("\nIngrese los coeficientes:\n\n");
    for(i=0;i<nIncognitas;i++){
        for(j=0;j<=nIncognitas;j++){
            if(j<nIncognitas){
                printf("Coeficiente %i de la ecuacion %i: ", j+1, i+1);
                scanf("%f",&a[i][j]);
                
            } else {
                printf("Termino independiente ecuacion %i: ", i+1);
                scanf("%f",&b[i]);
                printf("\n");
            }
        }
    }
    
    printf("\n\n A =");
    for(i=0;i<nIncognitas;i++) {
        for(j=0;j<nIncognitas;j++) {
            printf ("%10.5f",a[i][j]);
        }
        printf("\n    ");
    }
    
    printf("\n\n B =");
    for(i=0;i<nIncognitas;i++){
        printf ("%10.5f",b[i]);
        printf("\n    ");
    }
    
    //Verificar la fila pivote
    coeficienteMayor = a[0][0];
    ecuacionPivote = 0;
    for(i = 1; i < nIncognitas; i++){
        if(a[i][0] > coeficienteMayor){
            coeficienteMayor = a[i][0];
            ecuacionPivote = i;
        }
    }

    printf("\nEcuacion mayor: %i ", ecuacionPivote+1);
    
    //Intercambiar filas
    for(j = 0; j < nIncognitas; j++){
        auxiliarA = a[0][j];
        a[0][j] = a[ecuacionPivote][j];
        a[ecuacionPivote][j] = auxiliarA;
    }
    
    auxiliarB = b[0];
    b[0] = b[ecuacionPivote];
    b[ecuacionPivote] = auxiliarB;
    
    printf("\n\n despues del intercambio \n\n A =");
    for(i=0;i<nIncognitas;i++) {
        for(j=0;j<nIncognitas;j++) {
            printf ("%10.5f",a[i][j]);
        }
        printf("\n    ");
    }
    
    printf("\n\n B =");
    for(i=0;i<nIncognitas;i++){
        printf ("%10.5f",b[i]);
        printf("\n    ");
    }
    
    //inicialización de matrices l y u
    for(i=0;i<nIncognitas;i++) {
        for(j=0;j<nIncognitas;j++) {
            if(i>j) {
                u[i][j]=0;
            } else if(i==j) {
                l[i][j]=1;
            } else {
                l[i][j]=0;
            }
        }
    }
    
    //operar datos
    for(i=0;i<nIncognitas;i++) {
        for(j=0;j<nIncognitas;j++) {
            sum=0;
            if(i<=j){
                for(k=0;k<nIncognitas;k++) {
                    if(k!=i){
                        sum=sum+l[i][k]*u[k][j];
                    }
                }
                u[i][j]=a[i][j]-sum;
            } else {
                for(k=0;k<nIncognitas;k++) {
                    if(k!=j) {
                        sum=sum+l[i][k]*u[k][j];
                    }
                }
                l[i][j]=(a[i][j]-sum)/u[j][j];
            }
        }
    }
    
    printf("\n\n L =");
    for(i=0;i<nIncognitas;i++) {
        for(j=0;j<nIncognitas;j++) {
            printf ("%10.5f",l[i][j]);
        }
        printf("\n    ");
    }
    
    printf("\n\n U =");
    for(i=0;i<nIncognitas;i++) {
        for(j=0;j<nIncognitas;j++) {
            printf ("%10.5f",u[i][j]);
        }
        printf("\n    ");
    }
    
    y[0]=b[0]/l[0][0];
    for(i=1;i<nIncognitas;i++) {
        sum=0;
        for(j=0;j<i;j++) {
            sum=sum+y[j]*l[i][j];
            
        }
        y[i]=b[i]-sum;
    }
    
    printf("\n\n Y =");
    for(i=0;i<nIncognitas;i++){
        printf ("%10.5f",y[i]);
        printf("\n    ");
    }
    
    x[nIncognitas-1]=y[nIncognitas-1]/u[nIncognitas-1][nIncognitas-1];
    for(i=nIncognitas-2;i>=0;i--){
        sum=0;
        for(j=nIncognitas-1;j>i;j--) {
            sum=sum+x[j]*u[i][j];
        }
        x[i]=(y[i]-sum)/u[i][i];
    }
    
    printf("\nLa solucion es :\n");
    for(i=0;i<nIncognitas;i++) {
        printf("\n x[%d] = %.5f ",i+1,x[i]);
    }
    printf("\n\n");
    
    system("pause");
}



