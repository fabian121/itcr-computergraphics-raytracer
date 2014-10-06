#include "Sphere.h"
#include <stdlib.h>
#include <malloc.h>

/*metodo para inicializar la lista*/
void init_SPHERE(){
    startNode_SPHERE = NULL;
}

/*metodo para insertar un nuevo nodo en la lista*/
void insertNode_SPHERE(int code_, double radius_, 
        double xCenter_, double yCenter_, double zCenter_, 
        double red_, double green_, double blue_,
        double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_){
    /*VARIABLES TEMPORALES*/
    NODEPTR_SPHERE temp = (NODEPTR_SPHERE)malloc(sizeof(SPHERE));
    temp->code = code_;
    temp->radius = radius_;
    temp->xCenter = xCenter_;
    temp->yCenter = yCenter_;
    temp->zCenter = zCenter_;
    temp->red = red_;
    temp->green = green_;
    temp->blue = blue_;
    temp->kA_environmentLightCoefficient = kA_environmentLightCoefficient_;
    temp->kd_diffuseReflectionCoefficient = kd_diffuseReflectionCoefficient_;
    temp->nextPtr = NULL;
    
    /*nodo que apunta al inicio*/
    NODEPTR_SPHERE currentNode = startNode_SPHERE;
    
    /*indico la relacion de los punteros... siempre insertare al inicio de la lista*/
    temp->nextPtr = currentNode;
    startNode_SPHERE = temp;
}

/*para imprimir la lista*/
void printList_SPHERE(){
    NODEPTR_SPHERE aux;//para recorrer la lista
    aux = startNode_SPHERE;
    
    while(aux != NULL){
        printf("( %d ) --> ", (int)aux->radius);
        aux = aux->nextPtr;
    }
    printf("NULL\n");
}