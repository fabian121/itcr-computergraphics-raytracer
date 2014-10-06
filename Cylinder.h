/* 
 * File:   Cylinder.h
 * Author: root
 *
 * Created on June 7, 2013, 10:51 PM
 */

#ifndef CYLINDER_H
#define	CYLINDER_H

#include "Window3D.h"


#ifdef	__cplusplus
extern "C" {
#endif

    struct Cylinder {
        int code; //identificador unico

        double red, green, blue; //color del cilindro
        
        double x0, y0, z0, radius;
        
        int isInfinite;
        
        
        VECTOR_3D normalVector;
        
        VECTOR_3D vectorQ;
        
        double h1_distance, h2_distance; 

        double kd_diffuseReflectionCoefficient; //numero real entre 1 y 0

        double kA_environmentLightCoefficient; //numero real entre 1 y 0

        struct Cylinder *nextPtr;
    };

    typedef struct Cylinder CYLINDER;
    typedef CYLINDER *NODEPTR_CYLINDER;

    NODEPTR_CYLINDER startNode_CYLINDER;

    void init_CYLINDER();
    void printList_CYLINDER();
    void insertNode_CYLINDER(int code_,
            double red_, double green_, double blue_,
            double x0_, double y0_, double z0_, double radius_,
            VECTOR_3D vectorQ_, int isInfinite_,
            double h1_distance_, double h2_distance_,
            double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_);


#ifdef	__cplusplus
}
#endif

#endif	/* CYLINDER_H */

