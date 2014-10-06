/* 
 * File:   Cone.h
 * Author: root
 *
 * Created on June 15, 2013, 10:42 AM
 */

#ifndef CONE_H
#define	CONE_H

#include "Window3D.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    struct Cone {
        int code; //identificador unico

        double red, green, blue; //color del cilindro
        
        double x0, y0, z0, radius;
        
        int isInfinite;
        
        double v_ratio, u_ratio;
        
        VECTOR_3D normalVector;
        
        VECTOR_3D vectorQ;
        
        double h1_distance, h2_distance; 

        double kd_diffuseReflectionCoefficient; //numero real entre 1 y 0

        double kA_environmentLightCoefficient; //numero real entre 1 y 0

        struct Cone *nextPtr;
    };

    typedef struct Cone CONE;
    typedef CONE *NODEPTR_CONE;

    NODEPTR_CONE startNode_CONE;

    void init_CONE();
    void printList_CONE();
    void insertNode_CONE(int code_,
            double red_, double green_, double blue_,
            double x0_, double y0_, double z0_,
            VECTOR_3D vectorQ_, int isInfinite_,
            double v_ratio_, double u_ratio_, 
            double h1_distance_, double h2_distance_,
            double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_);



#ifdef	__cplusplus
}
#endif

#endif	/* CONE_H */

