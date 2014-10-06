#include "Polygon.h"
#include <stdlib.h>
#include <stdio.h>

void init_POLYGON(){
   
    startNode_POLYGON = NULL;
}

void insertNode_POLYGON(int code_,
            double red_, double green_, double blue_,
            VECTOR_3D *polygon_points_, int polygon_points_quantity_,
            double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_){
    
    /*VARIABLES TEMPORALES*/
    NODEPTR_POLYGON temp = (NODEPTR_POLYGON)malloc(sizeof(POLYGON));
    temp->code = code_;
    temp->red = red_;
    temp->green = green_;
    temp->blue = blue_;
    
    temp->polygon_points = polygon_points_;
    temp->alreadyCalculateNormABCD = 0;

    temp->polygon_points_quantity = polygon_points_quantity_;
    temp->kA_environmentLightCoefficient = kA_environmentLightCoefficient_;
    temp->kd_diffuseReflectionCoefficient = kd_diffuseReflectionCoefficient_;
    temp->nextPtr = NULL;
    
    /*nodo que apunta al inicio*/
    NODEPTR_POLYGON currentNode = startNode_POLYGON;
    
    /*indico la relacion de los punteros... siempre insertare al inicio de la lista*/
    temp->nextPtr = currentNode;
    startNode_POLYGON = temp;
}

/*para imprimir la lista*/
void printList_POLYGON(){
    NODEPTR_POLYGON aux;//para recorrer la lista
    aux = startNode_POLYGON;
    
    while(aux != NULL){
        printf("( %d ) --> ",aux->code);
        aux = aux->nextPtr;
    }
    printf("NULL\n");
}