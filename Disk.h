/* 
 * File:   Disk.h
 * Author: root
 *
 * Created on June 4, 2013, 4:40 PM
 */

#ifndef DISK_H
#define	DISK_H

#include "Window3D.h"


#ifdef	__cplusplus
extern "C" {
#endif

    struct Disk{
        int code;//identificador unico
        
        double radius;//radio de la esfera
        
        double xCenter, yCenter, zCenter;//punto medio de la esfera
        
        VECTOR_3D *disk_points;
        
        int isNormalVector;
        
        int alreadyCalculateNormABCD;
        
        //VECTOR_3D normalVector;
        double a, b, c, d;
        
        double red, green, blue;//color de la esfera
        
        double kd_diffuseReflectionCoefficient;//numero real entre 1 y 0
        
        double kA_environmentLightCoefficient;//numero real entre 1 y 0
        
        struct Disk *nextPtr;
    };

    typedef struct Disk DISK;
    typedef DISK *NODEPTR_DISK;
    
    NODEPTR_DISK startNode_DISK;

    void init_DISK();
    void printList_DISK();
    void insertNode_DISK(int code_, double radius_, double xCenter_, double yCenter_, double zCenter_, 
            VECTOR_3D *disk_points_,
            double red_, double green_, double blue_,
            int isNormalVector_,
            double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_);

#ifdef	__cplusplus
}
#endif

#endif	/* DISK_H */

