#include "Disk.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//inicializar la lista de discos
void init_DISK(){
    startNode_DISK = NULL;
}

//insertar un disco en la lista
void insertNode_DISK(int code_, 
        double radius_, 
        double xCenter_, double yCenter_, double zCenter_, 
        VECTOR_3D *disk_points_, 
        double red_, double green_, double blue_, 
        int isNormalVector_,
        double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_){
    /*VARIABLES TEMPORALES*/
   
    NODEPTR_DISK temp = (NODEPTR_DISK)malloc(sizeof(DISK));
    temp->code = code_;
    temp->red = red_;
    temp->green = green_;
    temp->blue = blue_;
    temp->radius = radius_;
    
    temp->xCenter = xCenter_;
    temp->yCenter = yCenter_;
    temp->zCenter = zCenter_;
    
    temp->disk_points = disk_points_;
    
    //si viene el vector normal, lo normalizo
    if(isNormalVector_ == 1){
        temp->a = temp->disk_points[0].x;
        temp->b = temp->disk_points[0].y;
        temp->c = temp->disk_points[0].z;
        
        //calculo la norma
        double norm = sqrt(pow(temp->a, 2) + pow(temp->b, 2) + pow(temp->c, 2));
        
        //calculo el valor de 'd'
        double dTemp = -1 * (temp->a * temp->xCenter + temp->b * temp->yCenter +
                    temp->c * temp->zCenter);
            
        temp->d = dTemp;
            
        //normalizo
        temp->a = 1 * temp->a / norm;
        temp->b = 1 * temp->b / norm;
        temp->c = 1 * temp->c / norm;
        temp->d = 1 * temp->d / norm; 
    }
    
    temp->alreadyCalculateNormABCD = 0;
    temp->isNormalVector = isNormalVector_;
   
    temp->kA_environmentLightCoefficient = kA_environmentLightCoefficient_;
    temp->kd_diffuseReflectionCoefficient = kd_diffuseReflectionCoefficient_;
    temp->nextPtr = NULL;
    
    /*nodo que apunta al inicio*/
    NODEPTR_DISK currentNode = startNode_DISK;
    
    /*indico la relacion de los punteros... siempre insertare al inicio de la lista*/
    temp->nextPtr = currentNode;
    startNode_DISK = temp;
}

//metodo para imprimir la lista de discos
void printList_DISK(){
    NODEPTR_DISK aux;//para recorrer la lista
    aux = startNode_DISK;
    
    while(aux != NULL){
        printf("( %d ) --> ",aux->code);
        aux = aux->nextPtr;
    }
    printf("NULL\n");
}