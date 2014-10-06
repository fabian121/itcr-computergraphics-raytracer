/* 
 * File:   RayTracing.h
 * Author: root
 *
 * Created on May 17, 2013, 5:24 PM
 */

#include "Window3D.h"
#include "Framebuffer.h"

#ifndef RAYTRACING_H
#define	RAYTRACING_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    //constante cero
    //const double EPSILON_ZERO = 0.0005;
    #define EPSILON_ZERO 0.0005

    //variables para hacer pruebas
    int xtemp, ytemp;
    
    void rayTracingAlgorithm_RAYTRACING(int argc, char** argv, int visualizeOpenGLWindow_);
    void rayTracing_RAYTRACING();
    
    RGB_3D get_color_RAYTRACING(VECTOR_3D eye, VECTOR_3D direction);
    INTERSECTION_3D firstIntersection(VECTOR_3D eye, VECTOR_3D direction, int isEyeRay);
    void paintFramebuffer();
    void storeNormalVectorIntoSphereList(int code, VECTOR_3D normalVector);
    VECTORLIGHTSOURCE_3D getCurrentLightSource(int position);
    void controlLines_RAYTRACING();
    
    //calcula intersecciones
    void firstIntersection_Spheres(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin);
    void firstIntersection_Polygons(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin, int isEyeRay);
    void firstIntersection_disks(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin, int isEyeRay);
    void firstIntersection_cylinders(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin);
    void firstIntersection_cone(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin);

    int save_png_to_file(const char *path);
#ifdef	__cplusplus
}
#endif

#endif	/* RAYTRACING_H */

