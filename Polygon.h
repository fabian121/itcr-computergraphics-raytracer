/* 
 * File:   Polygon.h
 * Author: root
 *
 * Created on May 31, 2013, 9:31 AM
 */

#ifndef POLYGON_H
#define	POLYGON_H
#include "Window3D.h"

#ifdef	__cplusplus
extern "C" {
#endif

    struct Polygon {
        int code; //identificador unico

        double red, green, blue; //color del poligono

        //VECTOR_3D normalVector;
        double a, b, c, d;
        
        VECTOR_3D *polygon_points;
        
        int polygon_points_quantity;

        double kd_diffuseReflectionCoefficient; //numero real entre 1 y 0

        double kA_environmentLightCoefficient; //numero real entre 1 y 0
        
        int alreadyCalculateNormABCD;

        struct Polygon *nextPtr;
    };

    typedef struct Polygon POLYGON;
    typedef POLYGON *NODEPTR_POLYGON;

    NODEPTR_POLYGON startNode_POLYGON;

    void init_POLYGON();
    void printList_POLYGON();
    void insertNode_POLYGON(int code_,
            double red_, double green_, double blue_,
            VECTOR_3D *polygon_points_, int polygon_points_quantity_,
            double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_);


#ifdef	__cplusplus
}
#endif

#endif	/* POLYGON_H */

