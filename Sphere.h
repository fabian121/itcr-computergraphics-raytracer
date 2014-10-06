/* 
 * File:   Sphere.h
 * Author: root
 *
 * Created on May 18, 2013, 4:41 PM
 */

#ifndef SPHERE_H
#define	SPHERE_H

#include "Window3D.h"


#ifdef	__cplusplus
extern "C" {
#endif

    struct Sphere{
        int code;//identificador unico
        
        double radius;//radio de la esfera
        
        double xCenter, yCenter, zCenter;//punto medio de la esfera
        
        double red, green, blue;//color de la esfera
        
        VECTOR_3D normalVector_N;
        
        double kd_diffuseReflectionCoefficient;//numero real entre 1 y 0
        
        double kA_environmentLightCoefficient;//numero real entre 1 y 0
        
        struct Sphere *nextPtr;
    };
    
    typedef struct Sphere SPHERE;
    typedef SPHERE *NODEPTR_SPHERE;
    
    NODEPTR_SPHERE startNode_SPHERE;
    
    void init_SPHERE();
    void printList_SPHERE();
    void insertNode_SPHERE(int code_, double radius_, double xCenter_, double yCenter_, double zCenter_, double red_, double green_, double blue_,
            double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_);


#ifdef	__cplusplus
}
#endif

#endif	/* SPHERE_H */

