/* 
 * File:   Window3D.h
 * Author: root
 *
 * Created on May 17, 2013, 4:53 PM
 */

#ifndef WINDOW3D_H
#define	WINDOW3D_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    //estructura para un color rgb*
    struct rgb{
        double red, green, blue;
    };
    typedef struct rgb RGB_3D;
    
    //estructura para crear un vector*
    struct vector{
        double x, y, z;
    };
    typedef struct vector VECTOR_3D;
    
    //estructura para representar una interseccion
    struct intersection{
        
        //especifo el tipo de objeto
        //0 indica que es una esfera
        //1 indica que es un poligono
        int type;
        int code;
        int isBackgound;
        double distanceToEye, red, green, blue;
        VECTOR_3D normalVector_N;//vector normal, perpendicular a la superficie del objeto
        double xi, yi, zi;//punto de interseccion
        double kd_diffuseReflectionCoefficient;//coeficiente de reflexion relacionado a cada objeto
        double kA_environmentLightCoefficient;//coeficiente de luz ambiente relacionado a cada objeto
        
        //double a_Polygon, b_Polygon, c_Polygon, d_Polygon;//PARA POLIGONOS
        //double xCenter_Sphere, yCenter_Sphere, zCenter_Sphere, radius_Sphere;//PARA ESFERAS
    };
    typedef struct intersection INTERSECTION_3D;
    
    //variable que me indica la posici[on de la luz
    struct vectorLightSource{
        double xp, yp, zp;//posicion
        
        double c1, c2, c3;//variables para calcular el factor de atenuacion
        
        double Ip_lightSourceIntensity;//numero real entre 1 y 0
    };
    typedef struct vectorLightSource VECTORLIGHTSOURCE_3D;
    
    VECTORLIGHTSOURCE_3D lightSource1_3D;
    VECTORLIGHTSOURCE_3D lightSource2_3D;
    VECTORLIGHTSOURCE_3D lightSource3_3D;
    int lightSourcesQuantity_3D;

    //valores de la ventana
    double xMin_3D, yMin_3D, xMax_3D, yMax_3D;
    
    //valores para la posicion del ojo
    double xE_3D, yE_3D, zE_3D;
    
    //valor para luz ambiente
    double Ia_environmentLight_3D;//numero real entre 1 y 0
    
    void init_WINDOW3D();


#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW3D_H */

