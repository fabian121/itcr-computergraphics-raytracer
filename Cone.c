#include <stdlib.h>

#include "Cone.h"
#include <stdio.h>
#include <math.h>

/*Para inicializar la lista*/
void init_CONE(){
    startNode_CONE = NULL;
}

/*para insertar un nuevo cono en la lista*/
void insertNode_CONE(int code_,
        double red_, double green_, double blue_,
        double x0_, double y0_, double z0_,
        VECTOR_3D vectorQ_, int isInfinite_,
        double v_ratio_, double u_ratio_,
        double h1_distance_, double h2_distance_,
        double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_){
    
    NODEPTR_CONE temp = (NODEPTR_CONE)malloc(sizeof(CONE));
    temp->code = code_;
    temp->red = red_;
    temp->green = green_;
    temp->blue = blue_;
    
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
    
    temp->v_ratio = v_ratio_;
    temp->u_ratio = u_ratio_;

    temp->kA_environmentLightCoefficient = kA_environmentLightCoefficient_;
    temp->kd_diffuseReflectionCoefficient = kd_diffuseReflectionCoefficient_;
    temp->nextPtr = NULL;
    
    /*nodo que apunta al inicio*/
    NODEPTR_CONE currentNode = startNode_CONE;
    
    /*indico la relacion de los punteros... siempre insertare al inicio de la lista*/
    temp->nextPtr = currentNode;
    startNode_CONE = temp;
}

/*para imprimir la lista actual*/
void printList_CONE(){
    NODEPTR_CONE aux;//para recorrer la lista
    aux = startNode_CONE;
    
    while(aux != NULL){
        printf("( %d ) --> ",aux->code);
        aux = aux->nextPtr;
    }
    printf("NULL\n");
}