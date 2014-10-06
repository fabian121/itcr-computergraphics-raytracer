#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Cylinder.h"

//para inicializar la lista
void init_CYLINDER(){
    startNode_CYLINDER = NULL;
}

//para insertar en la lista de cilindros
void insertNode_CYLINDER(int code_,
            double red_, double green_, double blue_,
            double x0_, double y0_, double z0_, double radius_,
            VECTOR_3D vectorQ_, int isInfinite_,
            double h1_distance_, double h2_distance_,
            double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_){
    
    NODEPTR_CYLINDER temp = (NODEPTR_CYLINDER)malloc(sizeof(CYLINDER));
    temp->code = code_;
    temp->red = red_;
    temp->green = green_;
    temp->blue = blue_;
    temp->radius = radius_;
    
    temp->x0 = x0_;
    temp->y0 = y0_;
    temp->z0 = z0_;
    
    temp->isInfinite = isInfinite_;
    temp->h1_distance = h1_distance_;
    temp->h2_distance = h2_distance_;
    
    //normalizo el vector Q
    double normQ = sqrt(pow(vectorQ_.x, 2) + pow(vectorQ_.y, 2) + pow(vectorQ_.z, 2));
    temp->vectorQ.x = vectorQ_.x / normQ;
    temp->vectorQ.y = vectorQ_.y / normQ;
    temp->vectorQ.z = vectorQ_.z / normQ;

    temp->kA_environmentLightCoefficient = kA_environmentLightCoefficient_;
    temp->kd_diffuseReflectionCoefficient = kd_diffuseReflectionCoefficient_;
    temp->nextPtr = NULL;
    
    /*nodo que apunta al inicio*/
    NODEPTR_CYLINDER currentNode = startNode_CYLINDER;
    
    /*indico la relacion de los punteros... siempre insertare al inicio de la lista*/
    temp->nextPtr = currentNode;
    startNode_CYLINDER = temp;
}

//metodo para imprimir la lista de discos
void printList_CYLINDER(){
    NODEPTR_CYLINDER aux;//para recorrer la lista
    aux = startNode_CYLINDER;
    
    while(aux != NULL){
        printf("( %f ) --> ",aux->x0);
        aux = aux->nextPtr;
    }
    printf("NULL\n");
}