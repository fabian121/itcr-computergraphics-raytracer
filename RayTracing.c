#include <math.h>
//#include <png.h>

#include "RayTracing.h"
#include "Framebuffer.h"
#include "Window3D.h"
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include "Sphere.h"
#include "Polygon.h"
#include "Disk.h"
#include "Cylinder.h"
#include "Cone.h"

int debugStop;
int visualizeOpenGLWindow;

/*para mostrar la ventana*/
void rayTracingAlgorithm_RAYTRACING(int argc, char** argv, int visualizeOpenGLWindow_) {

    //preguntar si quiero mostrar la ventana
    if (visualizeOpenGLWindow_ == 1) {
        visualizeOpenGLWindow = visualizeOpenGLWindow_;
        start_FRAMEBUFFER(argc, argv);
        glutDisplayFunc(rayTracing_RAYTRACING);
        glutMainLoop();
    } else {
        visualizeOpenGLWindow = 0;
        rayTracing_RAYTRACING();
    }

    debugStop = 0; //variable para hacer pruebas
}

/*recorrer todos los pixeles del framebuffer para pintar en la ventana*/
void rayTracing_RAYTRACING() {

    //variables
    double xW, yW, zW, l_norma, xD, yD, zD;

    //ciclo para recorrer todos los pixeles del framebuffer
    int i, j;
    for (i = 0; i < hSize_FRAMEBUFFER; i++) {
        for (j = 0; j < vSize_FRAMEBUFFER; j++) {

            //ESTE IF ES PARA HACER PRUEBAS Y DEPURAR DENTRO DEL CODIGO
            if (i == 450 && j == 200) {//450, 200
                debugStop = 1;
            }//TODO DELETE

            //obtener los valores de la ventana hacia el framebuffer
            xW = ((double) i + 0.5) * (xMax_3D - xMin_3D) / hSize_FRAMEBUFFER + xMin_3D;
            yW = ((double) (j) + 0.5)*(yMax_3D - yMin_3D) / vSize_FRAMEBUFFER + yMin_3D;
            zW = 0.0;

            //norma
            l_norma = sqrt(pow(xW - xE_3D, 2) + pow(yW - yE_3D, 2) + pow(zW - zE_3D, 2));

            //hago unitario el vector de direccion
            xD = (xW - xE_3D) / l_norma;
            yD = (yW - yE_3D) / l_norma;
            zD = (zW - zE_3D) / l_norma;

            VECTOR_3D currentEye;
            currentEye.x = xE_3D;
            currentEye.y = yE_3D;
            currentEye.z = zE_3D;

            VECTOR_3D direction;
            direction.x = xD;
            direction.y = yD;
            direction.z = zD;

            //ya tengo el punto tridimensional en el espacio 3D
            //ahora necesito definir el rayo desde el cual el ojo esta viendo
            RGB_3D currentRGB = get_color_RAYTRACING(currentEye, direction);


            framebuffer_FRAMEBUFFER[i][j] = currentRGB;
        }//end for
    }//end for

    //pintar en framebuffer en una ventana openGL
    paintFramebuffer();
}

/*para obtener el valor de la ventana*/
RGB_3D get_color_RAYTRACING(VECTOR_3D eye, VECTOR_3D direction) {
    //variable que se va a retornar
    RGB_3D currentRGB;

    //aqui se llama a first intersection
    INTERSECTION_3D currentIntersection = firstIntersection(eye, direction, 1);

    //pregunto si no encontro interseccion de camino
    if (currentIntersection.isBackgound == 1) {
        currentRGB.red = 0.3;
        currentRGB.green = 0.3;
        currentRGB.blue = 0.8;
    } else {

        //ANTES DE TODO NECESITO VERIFICAR SI EL VECTOR NORMAL ES EL QUE REALMENTE NECESITO
        //para esto saco el producto punto entre la direccion del ojo y el vector normal, esto NECESARIAMENTE
        // me va a dar mayor a cero porque los cosenos son negativos
        double N_pointProduct_D = direction.x * currentIntersection.normalVector_N.x +
                direction.y * currentIntersection.normalVector_N.y +
                direction.z * currentIntersection.normalVector_N.z;
        if (N_pointProduct_D > 0.0) {
            currentIntersection.normalVector_N.x = -1 * currentIntersection.normalVector_N.x;
            currentIntersection.normalVector_N.y = -1 * currentIntersection.normalVector_N.y;
            currentIntersection.normalVector_N.z = -1 * currentIntersection.normalVector_N.z;
        }
        /*---------------------------------------------------------------------*/



        /***********************************************************************/
        /*                   iterar por todas las fuentes de luz               */

        double I_intensity = 0.0; //almacenar la intensidad de las fuentes de luz
        double E_specularReflexion = 0.0; //almacenar la reflexion especular
        
        if(debugStop == 1){
            //printf(" ");
        }

        int i;
        for (i = 1; i <= lightSourcesQuantity_3D; i++) {
            //OBTENGO LA FUENTE DE LUZ
            VECTORLIGHTSOURCE_3D currentLightSource = getCurrentLightSource(i);

            //PRIMERO voy a calcular el VECTOR NORMAL L. Vector perpendicular a la fuente de luz
            //para esto primero necesito calcular la distancia a la fuente de luz
            double distanceToLight = sqrt(pow(currentIntersection.xi - currentLightSource.xp, 2) +
                    pow(currentIntersection.yi - currentLightSource.yp, 2) +
                    pow(currentIntersection.zi - currentLightSource.zp, 2));
            VECTOR_3D normalVector_L;
            normalVector_L.x = (currentLightSource.xp - currentIntersection.xi) / distanceToLight;
            normalVector_L.y = (currentLightSource.yp - currentIntersection.yi) / distanceToLight;
            normalVector_L.z = (currentLightSource.zp - currentIntersection.zi) / distanceToLight;

            //SEGUNDO calcular la intensidad
            //calculo el producto punto
            double L_pointProduct_N;
            L_pointProduct_N = normalVector_L.x * currentIntersection.normalVector_N.x +
                    normalVector_L.y * currentIntersection.normalVector_N.y +
                    normalVector_L.z * currentIntersection.normalVector_N.z;


            //*******************************************************************
            //*******************************************************************
            //        PARA LA REFLEXION ESPECULAR                              **
            VECTOR_3D vector_V_toEye;
            vector_V_toEye.x = -1 * direction.x;
            vector_V_toEye.y = -1 * direction.y;
            vector_V_toEye.z = -1 * direction.z;
            //*******************************************************************
            //*******************************************************************


            //SI PRODUCTO PUNTO ES MENOR A CERO: QUIERE DECIR QUE ESTOY A ESPALDAS DEL OBJETO
            //POR LO TANTO NO TOMO EN CUENTA ESE BOMBILLO
            if (L_pointProduct_N > EPSILON_ZERO) {

                //***************************************
                //******* CODIGO PARA SOMBRAS ***********
                VECTOR_3D currentObjectPoint;
                currentObjectPoint.x = currentIntersection.xi;
                currentObjectPoint.y = currentIntersection.yi;
                currentObjectPoint.z = currentIntersection.zi;
                normalVector_L.x = 1 * normalVector_L.x;
                normalVector_L.y = 1 * normalVector_L.y;
                normalVector_L.z = 1 * normalVector_L.z;
                INTERSECTION_3D obstacleToLight = firstIntersection(currentObjectPoint, normalVector_L, 0);
                
                //ANTES DE TODO NECESITO VERIFICAR SI EL VECTOR NORMAL ES EL QUE REALMENTE NECESITO
                //para esto saco el producto punto entre la direccion del ojo y el vector normal, esto NECESARIAMENTE
                // me va a dar mayor a cero porque los cosenos son negativos
/*
                double L_pointProduct_O = normalVector_L.x * obstacleToLight.normalVector_N.x +
                        normalVector_L.y * obstacleToLight.normalVector_N.y +
                        normalVector_L.z * obstacleToLight.normalVector_N.z;
                if (L_pointProduct_O > 0.0) {
                    obstacleToLight.isBackgound = 0;
                }
*/
/*
                if(obstacleToLight.type != 3){
                    obstacleToLight.normalVector_N.x = -1 * obstacleToLight.normalVector_N.x;
                    obstacleToLight.normalVector_N.y = -1 * obstacleToLight.normalVector_N.y;
                    obstacleToLight.normalVector_N.z = -1 * obstacleToLight.normalVector_N.z;
                }
*/
                /*---------------------------------------------------------------------*/

                //pregunto si no hay obstaculo y si lo hay pregunto si est[a en medio del objeto y el bombillo
                if (obstacleToLight.isBackgound == 1 ) {//|| (obstacleToLight.isBackgound == 0 && obstacleToLight.distanceToEye > distanceToLight)
                    //primero calculo el factor de atenuacion
                    double fatt = 1 / (currentLightSource.c1 + currentLightSource.c2 * distanceToLight + currentLightSource.c3 * pow(distanceToLight, 2));
                    fatt = (fatt > 1.0) ? 1.0 : fatt; //establecer el minimo entre 1 y el resultado del factor de atenuacion

                    I_intensity = I_intensity +
                            (L_pointProduct_N * //producto punto 1
                            currentIntersection.kd_diffuseReflectionCoefficient * //reflexion difusa del objeto 2
                            currentLightSource.Ip_lightSourceIntensity * //intensidad de la fuente de luz 3
                            fatt); //factor de atenuacion 6


                    //*******************************************************************
                    //*******************************************************************
                    //*        PARA LA REFLEXION ESPECULAR                              *
                    //*  CALCULO DEL VECTOR R - reflejo                                 *
                    VECTOR_3D vector_R_reflexion;
                    vector_R_reflexion.x = (2 * currentIntersection.normalVector_N.x) * L_pointProduct_N - normalVector_L.x;
                    vector_R_reflexion.y = (2 * currentIntersection.normalVector_N.y) * L_pointProduct_N - normalVector_L.y;
                    vector_R_reflexion.z = (2 * currentIntersection.normalVector_N.z) * L_pointProduct_N - normalVector_L.z;

                    //  producto punto de R y V
                    double R_pointProduct_V = vector_R_reflexion.x * vector_V_toEye.x +
                            vector_R_reflexion.y * vector_V_toEye.y +
                            vector_R_reflexion.z * vector_V_toEye.z;

                    //pregunto si la reflexion es valida
                    if (R_pointProduct_V > EPSILON_ZERO) {
                        E_specularReflexion = E_specularReflexion +
                                (pow(R_pointProduct_V, 20) *
                                currentIntersection.kd_diffuseReflectionCoefficient * //reflexion difusa del objeto 2
                                currentLightSource.Ip_lightSourceIntensity * //intensidad de la fuente de luz 3
                                fatt); //factor de atenuacion 6
                    }
                    //*******************************************************************
                    //*******************************************************************


                }//end if obstancle
                //***************************************


            }//end if
        }//end for lightSourcesQuantity*/


        //sumo las intensidades ambiente
        I_intensity = I_intensity + (currentIntersection.kA_environmentLightCoefficient * //coeficiente luz ambiente 4
                Ia_environmentLight_3D); //intensidad ambiente 5

        //verifico que no sea mayor a 1
        if (I_intensity > 1.0) {
            I_intensity = 1.0;
        }

        //verifico que la reflexion especular sea menor a 1
        if (E_specularReflexion > 1.0) {
            E_specularReflexion = 1.0;
        }

        /*para la visualizacion del objeto*/
        currentRGB.red = currentIntersection.red * I_intensity;
        currentRGB.green = currentIntersection.green * I_intensity;
        currentRGB.blue = currentIntersection.blue * I_intensity;

        /*PARA LA REFLEXION ESPECULAR*/
        currentRGB.red = currentRGB.red + E_specularReflexion * (1.0 - currentRGB.red);
        currentRGB.green = currentRGB.green + E_specularReflexion * (1.0 - currentRGB.green);
        currentRGB.blue = currentRGB.blue + E_specularReflexion * (1.0 - currentRGB.blue);
    }

    return currentRGB;
}

/*obtiene la primer interseccion con un objeto*/
INTERSECTION_3D firstIntersection(VECTOR_3D eye, VECTOR_3D direction, int isEyeRay) {

    //resultado de la interseccion
    INTERSECTION_3D intersection_result;
    intersection_result.isBackgound = 1; //indica que de momento no hay ninguna interseccion

    //variable que me calcula la distancia entre ventana y objeto
    double tmin;
    tmin = DBL_MAX;

    /**************************************************************************/
    /*              verificar las intersecciones con esferas                  */
    firstIntersection_Spheres(eye, direction, &intersection_result, &tmin);

    /**************************************************************************/
    /*                     interseccion poligonos                             */
    firstIntersection_Polygons(eye, direction, &intersection_result, &tmin, isEyeRay);

    /**************************************************************************/
    /*                     interseccion discos                                */
    firstIntersection_disks(eye, direction, &intersection_result, &tmin, isEyeRay);

    /**************************************************************************/
    /*                     interseccion cilindros                             */
    firstIntersection_cylinders(eye, direction, &intersection_result, &tmin);

    /**************************************************************************/
    /*                     interseccion conos                                 */
    firstIntersection_cone(eye, direction, &intersection_result, &tmin);


    //RETORNO LA MENOR INTERSECCION AL OJO
    return intersection_result;
}

/*VERIFICA INTERSECCIONES CON CONOS*/
void firstIntersection_cone(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin) {
    //valores para calculo de intersecciones
    double a_cylinder, b_cylinder, c_cylinder;

    //recorro todos los conos
    NODEPTR_CONE aux_cone;
    aux_cone = startNode_CONE;
    while (aux_cone != NULL) {

        //precalculos para la ecuacion
        double a_partCommon, b_partCommon;
        double ax, bx, cx, ay, by, cy, az, bz, cz;
        double aRatio, bRatio, cRatio;


        //en el despeje esta parte es comun a los calculos que se haran despues
        a_partCommon = direction.x * aux_cone->vectorQ.x + direction.y * aux_cone->vectorQ.y + direction.z * aux_cone->vectorQ.z;

        b_partCommon = aux_cone->vectorQ.x * (eye.x - aux_cone->x0) +
                aux_cone->vectorQ.y * (eye.y - aux_cone->y0) +
                aux_cone->vectorQ.z * (eye.z - aux_cone->z0);

        //calculos de a               *****************************************************************************************
        ax = -2 * direction.x * (a_partCommon * aux_cone->vectorQ.x) +
                pow(a_partCommon * aux_cone->vectorQ.x, 2) + pow(direction.x, 2);
        ay = -2 * direction.y * (a_partCommon * aux_cone->vectorQ.y) +
                pow(a_partCommon * aux_cone->vectorQ.y, 2) + pow(direction.y, 2);
        az = -2 * direction.z * (a_partCommon * aux_cone->vectorQ.z) +
                pow(a_partCommon * aux_cone->vectorQ.z, 2) + pow(direction.z, 2);

        //calculos de b                 ****************************************************************************************
        bx = 2 * direction.x * eye.x - 2 * direction.x * aux_cone->x0 - 2 * direction.x * (b_partCommon * aux_cone->vectorQ.x)
                - 2 * (a_partCommon * aux_cone->vectorQ.x) * eye.x + 2 * (a_partCommon * aux_cone->vectorQ.x) * aux_cone->x0 + 2 * (a_partCommon * aux_cone->vectorQ.x) * (b_partCommon * aux_cone->vectorQ.x);

        by = 2 * direction.y * eye.y - 2 * direction.y * aux_cone->y0 - 2 * direction.y * (b_partCommon * aux_cone->vectorQ.y)
                - 2 * (a_partCommon * aux_cone->vectorQ.y) * eye.y + 2 * (a_partCommon * aux_cone->vectorQ.y) * aux_cone->y0 + 2 * (a_partCommon * aux_cone->vectorQ.y) * (b_partCommon * aux_cone->vectorQ.y);

        bz = 2 * direction.z * eye.z - 2 * direction.z * aux_cone->z0 - 2 * direction.z * (b_partCommon * aux_cone->vectorQ.z)
                - 2 * (a_partCommon * aux_cone->vectorQ.z) * eye.z + 2 * (a_partCommon * aux_cone->vectorQ.z) * aux_cone->z0 + 2 * (a_partCommon * aux_cone->vectorQ.z) * (b_partCommon * aux_cone->vectorQ.z);

        //calculos de los c             *****************************************************************************************
        cx = pow(eye.x, 2) + pow(aux_cone->x0, 2) + pow(b_partCommon * aux_cone->vectorQ.x, 2)
                - 2 * eye.x * aux_cone->x0 - 2 * eye.x * (b_partCommon * aux_cone->vectorQ.x) + 2 * aux_cone->x0 * (b_partCommon * aux_cone->vectorQ.x);

        cy = pow(eye.y, 2) + pow(aux_cone->y0, 2) + pow(b_partCommon * aux_cone->vectorQ.y, 2)
                - 2 * eye.y * aux_cone->y0 - 2 * eye.y * (b_partCommon * aux_cone->vectorQ.y) + 2 * aux_cone->y0 * (b_partCommon * aux_cone->vectorQ.y);

        cz = pow(eye.z, 2) + pow(aux_cone->z0, 2) + pow(b_partCommon * aux_cone->vectorQ.z, 2)
                - 2 * eye.z * aux_cone->z0 - 2 * eye.z * (b_partCommon * aux_cone->vectorQ.z) + 2 * aux_cone->z0 * (b_partCommon * aux_cone->vectorQ.z);


        /******************************************/
        /*Calculo de la parte de la razon del cono*/
        double ratio2 = pow(aux_cone->v_ratio / aux_cone->u_ratio, 2);
        aRatio = pow(a_partCommon, 2) * ratio2;
        bRatio = 2 * a_partCommon * ratio2 * b_partCommon;
        cRatio = pow(b_partCommon, 2) * ratio2;
        /******************************************/

        //VARIABLES FINALES
        double a_final, b_final, c_final, discriminating, t1, t2;
        a_final = (ax + ay + az) - aRatio;
        b_final = (bx + by + bz) - bRatio;
        c_final = (cx + cy + cz) - cRatio;

        //DE ESTA FORMULA FINAL, HAGO EL CALCULO DEL DISCRIMINANTE
        discriminating = pow(b_final, 2) - 4 * a_final * c_final;

        //preguntar si existen soluciones
        if (discriminating > EPSILON_ZERO) {
            //CALCULO T1 y T2
            t1 = (-1 * b_final + sqrt(discriminating)) / (2 * a_final);
            t2 = (-1 * b_final - sqrt(discriminating)) / (2 * a_final);

            //pregunto si el cono esta delante del ojo
            if (t1 > EPSILON_ZERO || t2 > EPSILON_ZERO) {

                //dejo el menor en t1
                if (t1 > t2 && t2 > EPSILON_ZERO) {
                    double temp;
                    temp = t1;
                    t1 = t2;
                    t2 = temp;
                }

                /***************************************************************/
                /***************************************************************/
                /***************************************************************/
                /*              PREGUNTA SI SON FINITOS O INFINITOS            */
                int goOn = 0;
                if (aux_cone->isInfinite == 0) {
                    double distanceOriginTo_XM_YM_ZM; //variable para el calculo de la distancia dentro de la misma linea

                    //calculo de d para ver si esta en medio de h1 y h2
                    distanceOriginTo_XM_YM_ZM = t1 * a_partCommon + b_partCommon;

                    //si resulta que NO se encuentra en medio, ahora calculo con respecto a t2... ya que puedo estar viendo el interior del cilindro
                    if (distanceOriginTo_XM_YM_ZM > aux_cone->h2_distance || distanceOriginTo_XM_YM_ZM < aux_cone->h1_distance) {

                        //NUEVAMENTE HAGO SWITCH PARA CALCULAR CON RESPECTO A LA OTRA INTERSECCION
                        double temp;
                        temp = t1;
                        t1 = t2;
                        t2 = temp;

                        if (t1 > EPSILON_ZERO) {
                            //calculo de d para ver si esta en medio de h1 y h2
                            distanceOriginTo_XM_YM_ZM = t1 * a_partCommon + b_partCommon;
                        } else {
                            distanceOriginTo_XM_YM_ZM = DBL_MAX;
                        }
                    }

                    if (distanceOriginTo_XM_YM_ZM < aux_cone->h2_distance && distanceOriginTo_XM_YM_ZM > aux_cone->h1_distance) {
                        goOn = 1;
                    }
                }//end  isInfinite == 0
                else {
                    goOn = 1;
                }
                /***************************************************************/
                /***************************************************************/
                /***************************************************************/

                //pregunto si es menor a cualquier otra interseccion
                if (t1 < *tmin && goOn == 1) {
                    //guardo la nueva distancia
                    *tmin = t1;

                    intersection_result->type = 1;

                    //calculo el lugar exacto de la interseccion
                    intersection_result->xi = eye.x + *tmin * direction.x;
                    intersection_result->yi = eye.y + *tmin * direction.y;
                    intersection_result->zi = eye.z + *tmin * direction.z;

                    //guardo la distancia en el objeto
                    intersection_result->distanceToEye = *tmin;

                    //indico que ya no es background
                    intersection_result->isBackgound = 0;

                    //establezco el nuevo rgb
                    intersection_result->red = aux_cone->red;
                    intersection_result->green = aux_cone->green;
                    intersection_result->blue = aux_cone->blue;

                    intersection_result->kA_environmentLightCoefficient = aux_cone->kA_environmentLightCoefficient;
                    intersection_result->kd_diffuseReflectionCoefficient = aux_cone->kd_diffuseReflectionCoefficient;


                    /*CODIGO PARA CALCULAR LA NORMAL DEL CONO-- SEGUN LOS CALCULOS DE DERIVADAS PARCIALES*/
                    double vu_ratio_square2 = pow(aux_cone->v_ratio / aux_cone->u_ratio, 2);

                    double x_temp = intersection_result->xi * pow(aux_cone->vectorQ.x, 2) * vu_ratio_square2 -
                            pow(aux_cone->vectorQ.x, 2) * vu_ratio_square2 * aux_cone->x0 +
                            aux_cone->vectorQ.x * aux_cone->vectorQ.y * vu_ratio_square2 * intersection_result->yi -
                            aux_cone->vectorQ.x * aux_cone->vectorQ.y * vu_ratio_square2 * aux_cone->y0 +
                            aux_cone->vectorQ.x * aux_cone->vectorQ.z * vu_ratio_square2 * intersection_result->zi -
                            aux_cone->vectorQ.x * aux_cone->vectorQ.z * vu_ratio_square2 * aux_cone->z0;

                    double y_temp = intersection_result->yi * pow(aux_cone->vectorQ.y, 2) * vu_ratio_square2 -
                            pow(aux_cone->vectorQ.y, 2) * vu_ratio_square2 * aux_cone->y0 +
                            aux_cone->vectorQ.x * aux_cone->vectorQ.y * vu_ratio_square2 * intersection_result->xi -
                            aux_cone->vectorQ.x * aux_cone->vectorQ.y * vu_ratio_square2 * aux_cone->x0 +
                            aux_cone->vectorQ.y * aux_cone->vectorQ.z * vu_ratio_square2 * intersection_result->zi -
                            aux_cone->vectorQ.y * aux_cone->vectorQ.z * vu_ratio_square2 * aux_cone->z0;

                    double z_temp = intersection_result->zi * pow(aux_cone->vectorQ.z, 2) * vu_ratio_square2 -
                            pow(aux_cone->vectorQ.z, 2) * vu_ratio_square2 * aux_cone->z0 +
                            aux_cone->vectorQ.x * aux_cone->vectorQ.z * vu_ratio_square2 * intersection_result->xi -
                            aux_cone->vectorQ.x * aux_cone->vectorQ.z * vu_ratio_square2 * aux_cone->x0 +
                            aux_cone->vectorQ.y * aux_cone->vectorQ.z * vu_ratio_square2 * intersection_result->yi -
                            aux_cone->vectorQ.y * aux_cone->vectorQ.z * vu_ratio_square2 * aux_cone->y0;


                    intersection_result->normalVector_N.x = (intersection_result->xi -
                            (aux_cone->x0 + aux_cone->vectorQ.x * (*tmin * a_partCommon + b_partCommon))) - x_temp;
                    intersection_result->normalVector_N.y = (intersection_result->yi -
                            (aux_cone->y0 + aux_cone->vectorQ.y * (*tmin * a_partCommon + b_partCommon))) - y_temp;
                    intersection_result->normalVector_N.z = (intersection_result->zi -
                            (aux_cone->z0 + aux_cone->vectorQ.z * (*tmin * a_partCommon + b_partCommon))) - z_temp;

                    //para hacerlo unitario
                    double norm = sqrt(pow(intersection_result->normalVector_N.x, 2) + pow(intersection_result->normalVector_N.y, 2) +
                            pow(intersection_result->normalVector_N.z, 2));

                    intersection_result->normalVector_N.x = intersection_result->normalVector_N.x / norm;
                    intersection_result->normalVector_N.y = intersection_result->normalVector_N.y / norm;
                    intersection_result->normalVector_N.z = intersection_result->normalVector_N.z / norm;
                }
            }//end  if (t1 > EPSILON_ZERO || t2 > EPSILON_ZERO)
        }//end   if (discriminating > EPSILON_ZERO)


        //analizo el siguiente cono
        aux_cone = aux_cone->nextPtr;
    }//end  while(aux_cone != NULL)
}

/*VERIFICA INTERSECCIONES CON cilindros*/
void firstIntersection_cylinders(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin) {

    //valores para calculo de intersecciones
    double a_cylinder, b_cylinder, c_cylinder;

    //recorro todos los cilindros
    NODEPTR_CYLINDER aux_cylinder;
    aux_cylinder = startNode_CYLINDER;
    while (aux_cylinder != NULL) {

        //precalculos para la ecuacion
        double a_partCommon, b_partCommon;
        double ax, bx, cx, ay, by, cy, az, bz, cz;

        //en el despeje esta parte es comun a los calculos que se haran despues
        a_partCommon = direction.x * aux_cylinder->vectorQ.x + direction.y * aux_cylinder->vectorQ.y + direction.z * aux_cylinder->vectorQ.z;

        b_partCommon = aux_cylinder->vectorQ.x * (eye.x - aux_cylinder->x0) +
                aux_cylinder->vectorQ.y * (eye.y - aux_cylinder->y0) +
                aux_cylinder->vectorQ.z * (eye.z - aux_cylinder->z0);


        //calculos de a               *****************************************************************************************
        ax = -2 * direction.x * (a_partCommon * aux_cylinder->vectorQ.x) +
                pow(a_partCommon * aux_cylinder->vectorQ.x, 2) + pow(direction.x, 2);
        ay = -2 * direction.y * (a_partCommon * aux_cylinder->vectorQ.y) +
                pow(a_partCommon * aux_cylinder->vectorQ.y, 2) + pow(direction.y, 2);
        az = -2 * direction.z * (a_partCommon * aux_cylinder->vectorQ.z) +
                pow(a_partCommon * aux_cylinder->vectorQ.z, 2) + pow(direction.z, 2);

        //calculos de b                 ****************************************************************************************
        bx = 2 * direction.x * eye.x - 2 * direction.x * aux_cylinder->x0 - 2 * direction.x * (b_partCommon * aux_cylinder->vectorQ.x)
                - 2 * (a_partCommon * aux_cylinder->vectorQ.x) * eye.x + 2 * (a_partCommon * aux_cylinder->vectorQ.x) * aux_cylinder->x0 + 2 * (a_partCommon * aux_cylinder->vectorQ.x) * (b_partCommon * aux_cylinder->vectorQ.x);

        by = 2 * direction.y * eye.y - 2 * direction.y * aux_cylinder->y0 - 2 * direction.y * (b_partCommon * aux_cylinder->vectorQ.y)
                - 2 * (a_partCommon * aux_cylinder->vectorQ.y) * eye.y + 2 * (a_partCommon * aux_cylinder->vectorQ.y) * aux_cylinder->y0 + 2 * (a_partCommon * aux_cylinder->vectorQ.y) * (b_partCommon * aux_cylinder->vectorQ.y);

        bz = 2 * direction.z * eye.z - 2 * direction.z * aux_cylinder->z0 - 2 * direction.z * (b_partCommon * aux_cylinder->vectorQ.z)
                - 2 * (a_partCommon * aux_cylinder->vectorQ.z) * eye.z + 2 * (a_partCommon * aux_cylinder->vectorQ.z) * aux_cylinder->z0 + 2 * (a_partCommon * aux_cylinder->vectorQ.z) * (b_partCommon * aux_cylinder->vectorQ.z);

        //calculos de los c             *****************************************************************************************
        cx = pow(eye.x, 2) + pow(aux_cylinder->x0, 2) + pow(b_partCommon * aux_cylinder->vectorQ.x, 2)
                - 2 * eye.x * aux_cylinder->x0 - 2 * eye.x * (b_partCommon * aux_cylinder->vectorQ.x) + 2 * aux_cylinder->x0 * (b_partCommon * aux_cylinder->vectorQ.x);

        cy = pow(eye.y, 2) + pow(aux_cylinder->y0, 2) + pow(b_partCommon * aux_cylinder->vectorQ.y, 2)
                - 2 * eye.y * aux_cylinder->y0 - 2 * eye.y * (b_partCommon * aux_cylinder->vectorQ.y) + 2 * aux_cylinder->y0 * (b_partCommon * aux_cylinder->vectorQ.y);

        cz = pow(eye.z, 2) + pow(aux_cylinder->z0, 2) + pow(b_partCommon * aux_cylinder->vectorQ.z, 2)
                - 2 * eye.z * aux_cylinder->z0 - 2 * eye.z * (b_partCommon * aux_cylinder->vectorQ.z) + 2 * aux_cylinder->z0 * (b_partCommon * aux_cylinder->vectorQ.z);


        //VARIABLES FINALES
        double a_final, b_final, c_final, discriminating, t1, t2;
        a_final = ax + ay + az;
        b_final = bx + by + bz;
        c_final = (cx + cy + cz) - pow(aux_cylinder->radius, 2);


        //DE ESTA FORMULA FINAL, HAGO EL CALCULO DEL DISCRIMINANTE
        discriminating = pow(b_final, 2) - 4 * a_final * c_final;

        //preguntar si existen soluciones
        if (discriminating > EPSILON_ZERO) {
            //CALCULO T1 y T2
            t1 = (-1 * b_final + sqrt(discriminating)) / (2 * a_final);
            t2 = (-1 * b_final - sqrt(discriminating)) / (2 * a_final);

            //pregunto si el cilindro esta delante del ojo
            if (t1 > EPSILON_ZERO || t2 > EPSILON_ZERO) {

                //switch para dejar el menor en t1
                if (t1 > t2 && t2 > EPSILON_ZERO) {
                    double temp;
                    temp = t1;
                    t1 = t2;
                    t2 = temp;
                }


                /***************************************************************/
                /***************************************************************/
                /***************************************************************/
                /*              PREGUNTA SI SON FINITOS O INFINITOS            */
                int goOn = 0;
                if (aux_cylinder->isInfinite == 0) {
                    double distanceOriginTo_XM_YM_ZM; //variable para el calculo de la distancia dentro de la misma linea

                    //calculo de d para ver si esta en medio de h1 y h2
                    distanceOriginTo_XM_YM_ZM = t1 * a_partCommon + b_partCommon;

                    //si resulta que NO se encuentra en medio, ahora calculo con respecto a t2... ya que puedo estar viendo el interior del cilindro
                    if (distanceOriginTo_XM_YM_ZM > aux_cylinder->h2_distance || distanceOriginTo_XM_YM_ZM < aux_cylinder->h1_distance) {

                        //NUEVAMENTE HAGO SWITCH PARA CALCULAR CON RESPECTO A LA OTRA INTERSECCION
                        double temp;
                        temp = t1;
                        t1 = t2;
                        t2 = temp;

                        if (t1 > EPSILON_ZERO) {
                            //calculo de d para ver si esta en medio de h1 y h2
                            distanceOriginTo_XM_YM_ZM = t1 * a_partCommon + b_partCommon;
                        } else {
                            distanceOriginTo_XM_YM_ZM = DBL_MAX;
                        }
                    }

                    if (distanceOriginTo_XM_YM_ZM < aux_cylinder->h2_distance && distanceOriginTo_XM_YM_ZM > aux_cylinder->h1_distance) {
                        goOn = 1;
                    }
                }//end  isInfinite == 0
                else {
                    goOn = 1;
                }
                /***************************************************************/
                /***************************************************************/
                /***************************************************************/


                if (t1 < *tmin && goOn == 1) {
                    //guardo la nueva distancia
                    *tmin = t1;

                    intersection_result->type = 2;

                    //calculo el lugar exacto de la interseccion
                    intersection_result->xi = eye.x + *tmin * direction.x;
                    intersection_result->yi = eye.y + *tmin * direction.y;
                    intersection_result->zi = eye.z + *tmin * direction.z;

                    //calculo la normal
                    intersection_result->normalVector_N.x = (intersection_result->xi -
                            (aux_cylinder->x0 + aux_cylinder->vectorQ.x * (*tmin * a_partCommon + b_partCommon))) / aux_cylinder->radius;
                    intersection_result->normalVector_N.y = (intersection_result->yi -
                            (aux_cylinder->y0 + aux_cylinder->vectorQ.y * (*tmin * a_partCommon + b_partCommon))) / aux_cylinder->radius;
                    intersection_result->normalVector_N.z = (intersection_result->zi -
                            (aux_cylinder->z0 + aux_cylinder->vectorQ.z * (*tmin * a_partCommon + b_partCommon))) / aux_cylinder->radius;

                    //guardo la distancia en el objeto
                    intersection_result->distanceToEye = *tmin;

                    //indico que ya no es background
                    intersection_result->isBackgound = 0;

                    //establezco el nuevo rgb
                    intersection_result->red = aux_cylinder->red;
                    intersection_result->green = aux_cylinder->green;
                    intersection_result->blue = aux_cylinder->blue;

                    intersection_result->kA_environmentLightCoefficient = aux_cylinder->kA_environmentLightCoefficient;
                    intersection_result->kd_diffuseReflectionCoefficient = aux_cylinder->kd_diffuseReflectionCoefficient;
                }//end  t1 < *tmin && goOn == 1

            }//end  if (t1 > EPSILON_ZERO || t2 > EPSILON_ZERO)
        }// end   if (discriminating > EPSILON_ZERO)

        //analizo el siguiente cilindro
        aux_cylinder = aux_cylinder->nextPtr;
    }//end while(aux_cylinder != NULL)
}

/*VERIFICA INTERSECCIONES CON DISCOS*/
void firstIntersection_disks(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin, int isEyeRay) {

    //recorro todos los discos
    NODEPTR_DISK aux_disk;
    aux_disk = startNode_DISK;
    while (aux_disk != NULL) {

        //valores de la ecuacion para el plano
        double a_disk, b_disk, c_disk, d_disk;
        
        if(debugStop == 1){
            //printf(" ");
        }
        
        //****************************************************************************************
        //Pregunto si NO viene el vector normal... en lugar vienen 3 puntos pertenecientes al plano
        if(aux_disk->isNormalVector == 0){
            
            /*pregunto si ya calcule la norma-- RECORDAR QUE LOS DISCOS SON PLANOS, POR LO TANTO LA NORMA SE CALCULA UNA SOLA VEZ*/
            //if (aux_disk->alreadyCalculateNormABCD == 0) {
                //utilizo los tres puntos que tengo para calcular los dos vectores DEL PLANO y con esta informacion obtener el vector NORMAL AL PLANO
                VECTOR_3D vector1;
                vector1.x = aux_disk->disk_points[1].x - aux_disk->disk_points[0].x;
                vector1.y = aux_disk->disk_points[1].y - aux_disk->disk_points[0].y;
                vector1.z = aux_disk->disk_points[1].z - aux_disk->disk_points[0].z;
                VECTOR_3D vector2;
                vector2.x = aux_disk->disk_points[2].x - aux_disk->disk_points[0].x;
                vector2.y = aux_disk->disk_points[2].y - aux_disk->disk_points[0].y;
                vector2.z = aux_disk->disk_points[2].z - aux_disk->disk_points[0].z;

                //producto cruz para sacar el vector normal del plano
                VECTOR_3D croiseProduct;
                croiseProduct.x = vector1.y * vector2.z - vector2.y * vector1.z;
                croiseProduct.y = vector1.z * vector2.x - vector1.x * vector2.z;
                croiseProduct.z = vector1.x * vector2.y - vector2.x * vector1.y;

                //con el resultado del producto cruz ya se los valores a, b y c... calculo a D        
                //sustituyo en la ecuacion para obtener el valor d
                double dTemp = -1 * (croiseProduct.x * aux_disk->xCenter + croiseProduct.y * aux_disk->yCenter +
                        croiseProduct.z * aux_disk->zCenter);

                //calculo la NORMA DEL VECTOR
                double vector_norm = sqrt(pow(croiseProduct.x, 2) + pow(croiseProduct.y, 2) + pow(croiseProduct.z, 2));

                //establezco los valores ya normalizados
                a_disk = croiseProduct.x / vector_norm;
                b_disk = croiseProduct.y / vector_norm;
                c_disk = croiseProduct.z / vector_norm;
                d_disk = dTemp / vector_norm;

                if(isEyeRay == 0){
                    a_disk = -1 * a_disk;
                    b_disk = -1 * b_disk;
                    c_disk = -1 * c_disk;
                    d_disk = -1 * d_disk;
                }

                //indicar que ya se calculo todo
                aux_disk->alreadyCalculateNormABCD = 1;
            } else {
            
                if(isEyeRay == 1){
                    a_disk = aux_disk->a * -1;
                    b_disk = aux_disk->b * -1;
                    c_disk = aux_disk->c * -1;
                    d_disk = aux_disk->d * -1;
                }else{
                    a_disk = aux_disk->a;
                    b_disk = aux_disk->b;
                    c_disk = aux_disk->c;
                    d_disk = aux_disk->d;
                }
                
            }
/*
        }//end  if(aux_disk->isNormalVector == 0)
        else{
            //YA VIENE EL VECTOR NORMALIZADO
            a_disk = aux_disk->a;
            b_disk = aux_disk->b;
            c_disk = aux_disk->c;
            d_disk = aux_disk->d;
        }
*/

        //****************************************
        //EN ESTE PUNTO YA TENGO TODO LO NECESARIO
        //CALCULAR EL VALOR T, QUE ES LA DISTANCIA
        double t_denominator = a_disk * direction.x + b_disk * direction.y + c_disk * direction.z;

        //como estoy haciendo el producto punto entre el vector de direccion y la normal del poligono, si esto da cero
        //me indica que las normales forman un angulo de 90 grados, si eso es as[i entonces el rayo y el plano son paralelos y no hay intersecci[on
        //EL PRODUCTO PUNTO ME DA NEGATIVO, YA QUE EL ANGULO DEBE SER MAYOR A 90 GRADOS!!!!
        if (t_denominator < EPSILON_ZERO) {

            double t_numerator = (-1)*(a_disk * eye.x + b_disk * eye.y + c_disk * eye.z
                    + d_disk);

            double t_diskDistanceToEye = t_numerator / t_denominator; //calculo el resultado de la inecuancion

            //ES MENOR QUE LA DISTANCIA DE ALGUN OBJETO, ENTONCES PUEDO CONTINUAR
            if (t_diskDistanceToEye < *tmin && t_diskDistanceToEye > EPSILON_ZERO) {

                //CALCULO LA INTERSECCION EXACTA EN LA QUE SE ENCUENTRA EL PUNTO DE INTERSECCION
                double xi = eye.x + t_diskDistanceToEye * direction.x;
                double yi = eye.y + t_diskDistanceToEye * direction.y;
                double zi = eye.z + t_diskDistanceToEye * direction.z;

                //meto todo en la inecuaci[on para saber si pertenece al disco
                double final_result = pow((xi - aux_disk->xCenter), 2) +
                        pow((yi - aux_disk->yCenter), 2) +
                        pow((zi - aux_disk->zCenter), 2);

                double r_square_2 = pow(aux_disk->radius, 2); //saco el doble del radio

                //si el resultado de la inecuacion es menor o igual a cero entonces esta dentro del disco
                if (final_result < r_square_2) {

                    //empiezo a crear la interseccion que retornara
                    //tipo indica que es un DISCO
                    intersection_result->type = 3;

                    //indico que SI encontro una interseccion
                    intersection_result->isBackgound = 0;

                    //indico la distancia desde el ojo
                    intersection_result->distanceToEye = t_diskDistanceToEye;
                    *tmin = t_diskDistanceToEye; //actualizo la distancia minima

                    //guardo el color rgb
                    intersection_result->red = aux_disk->red;
                    intersection_result->green = aux_disk->green;
                    intersection_result->blue = aux_disk->blue;

                    //GUARDO EL VECTOR NORMAL
                    VECTOR_3D normalVectorTemp;
                    normalVectorTemp.x = a_disk;
                    normalVectorTemp.y = b_disk;
                    normalVectorTemp.z = c_disk;
                    intersection_result->normalVector_N = normalVectorTemp;

                    //guardo el punto de interseccion
                    intersection_result->xi = xi;
                    intersection_result->yi = yi;
                    intersection_result->zi = zi;

                    //guardo el coeficiente de iluminacion difusa del objeto
                    intersection_result->kd_diffuseReflectionCoefficient = aux_disk->kd_diffuseReflectionCoefficient;

                    //guardo el coeficiente de iluminacion ambiente
                    intersection_result->kA_environmentLightCoefficient = aux_disk->kA_environmentLightCoefficient;

                }//end  

            }//end if(t_polygonDistanceToEye < *tmin)
        }//end if (t_denominator < EPSILON_ZERO)

        aux_disk = aux_disk->nextPtr; //analizo el siguiente disco
    }//end (aux_disk != NULL)
}

/*VERIFICA INTERSECCIONES CON POLIGONOS*/
void firstIntersection_Polygons(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin, int isEyeRay) {

    //recorro todos los poligonos
    NODEPTR_POLYGON aux_polygon;
    aux_polygon = startNode_POLYGON;
    while (aux_polygon != NULL) {

        double a_polygon, b_polygon, c_polygon, d_polygon; //valores de la ecuacion

        //PREGUNTO SI PREVIAMENTE YA HIZO LOS CALCULOS, ya que como poligonos son planos la norma la calculo una sola vez
        //if (aux_polygon->alreadyCalculateNormABCD == 0) {
            //primero obtengo el vector normal de ese poligono
            //utilizo tres puntos de ese poligono para ese calculo
            VECTOR_3D vector1;
            vector1.x = aux_polygon->polygon_points[1].x - aux_polygon->polygon_points[0].x;
            vector1.y = aux_polygon->polygon_points[1].y - aux_polygon->polygon_points[0].y;
            vector1.z = aux_polygon->polygon_points[1].z - aux_polygon->polygon_points[0].z;

            VECTOR_3D vector2;
            vector2.x = aux_polygon->polygon_points[aux_polygon->polygon_points_quantity - 1].x - aux_polygon->polygon_points[0].x;
            vector2.y = aux_polygon->polygon_points[aux_polygon->polygon_points_quantity - 1].y - aux_polygon->polygon_points[0].y;
            vector2.z = aux_polygon->polygon_points[aux_polygon->polygon_points_quantity - 1].z - aux_polygon->polygon_points[0].z;

            VECTOR_3D croiseProduct;
            croiseProduct.x = vector1.y * vector2.z - vector2.y * vector1.z;
            croiseProduct.y = vector1.z * vector2.x - vector1.x * vector2.z;
            croiseProduct.z = vector1.x * vector2.y - vector2.x * vector1.y;

            //con el resultado del producto cruz ya se los valores a, b y c... calculo a D        
            //sustituyo en la ecuacion para obtener el valor d
            double dTemp = -1 * (croiseProduct.x * aux_polygon->polygon_points[0].x + croiseProduct.y * aux_polygon->polygon_points[0].y +
                    croiseProduct.z * aux_polygon->polygon_points[0].z);

            //calculo la NORMA DEL VECTOR
            double vector_norm = sqrt(pow(croiseProduct.x, 2) + pow(croiseProduct.y, 2) + pow(croiseProduct.z, 2));

            //establezco los valores ya normalizados
            a_polygon = croiseProduct.x / vector_norm;
            b_polygon = croiseProduct.y / vector_norm;
            c_polygon = croiseProduct.z / vector_norm;
            d_polygon = dTemp / vector_norm;

            //almaceno la normal, si es del ojo la invierto
            if(isEyeRay == 1){
                aux_polygon->a = 1 * a_polygon;
                aux_polygon->b = 1 * b_polygon;
                aux_polygon->c = 1 * c_polygon;
                aux_polygon->d = 1 * d_polygon;
            }else{
                aux_polygon->a = -1 * a_polygon;
                aux_polygon->b = -1 * b_polygon;
                aux_polygon->c = -1 * c_polygon;
                aux_polygon->d = -1 * d_polygon;
            }

            //indico que ya se hicieron los calculos
            aux_polygon->alreadyCalculateNormABCD = 1;
/*
        } else {
            
            if(isEyeRay == 1){
                //los cargo
                aux_polygon->a = aux_polygon->a;
                aux_polygon->b = aux_polygon->b;
                aux_polygon->c = aux_polygon->c;
                aux_polygon->d = aux_polygon->d;
            }
            else{
                aux_polygon->a = -1*aux_polygon->a;
                aux_polygon->b = -1*aux_polygon->b;
                aux_polygon->c = -1*aux_polygon->c;
                aux_polygon->d = -1*aux_polygon->d;
            }
        }
*/

        //****************************************
        //EN ESTE PUNTO YA TENGO TODO LO NECESARIO
        //CALCULAR EL VALOR T, QUE ES LA DISTANCIA

        double t_denominator = aux_polygon->a * direction.x + aux_polygon->b * direction.y + aux_polygon->c * direction.z;

        //como estoy haciendo el producto punto entre el vector de direccion y la normal del poligono, si esto da cero
        //me indica que las normales forman un angulo de 90 grados, si eso es as[i entonces el rayo y el plano son paralelos y no hay intersecci[on
        //EL PRODUCTO PUNTO ME DA NEGATIVO, YA QUE EL ANGULO DEBE SER MAYOR A 90 GRADOS!!!!
        if (t_denominator < EPSILON_ZERO) {
            double t_numerator = (-1)*(aux_polygon->a * eye.x + aux_polygon->b * eye.y + aux_polygon->c * eye.z
                    + aux_polygon->d);

            double t_polygonDistanceToEye = t_numerator / t_denominator;

            //ES MENOR QUE LA DISTANCIA que habia encontrado hasta el momento, ENTONCES PUEDO CONTINUAR
            if (t_polygonDistanceToEye < *tmin && t_polygonDistanceToEye > EPSILON_ZERO) {

                //CALCULO LA INTERSECCION EXACTA EN LA QUE SE ENCUENTRA EL PUNTO DE INTERSECCION
                double xi = eye.x + t_polygonDistanceToEye * direction.x;
                double yi = eye.y + t_polygonDistanceToEye * direction.y;
                double zi = eye.z + t_polygonDistanceToEye * direction.z;


                //DETERMINAR SI EL PUNTO ESTA CONTENIDO EN EL POLIGONO O NO
                //1. aplastar el poligono ************** 
                VECTOR_3D polygonTemp[aux_polygon->polygon_points_quantity];
                int i;


                /*               VALORES ABSOLUTOS                              */
                /****************************************************************/
                double atemp = (aux_polygon->a > 0.0) ? aux_polygon->a : (-1 * aux_polygon->a);
                double btemp = (aux_polygon->b > 0.0) ? aux_polygon->b : (-1 * aux_polygon->b);
                double ctemp = (aux_polygon->c > 0.0) ? aux_polygon->c : (-1 * aux_polygon->c);
                /****************************************************************/

                //recorro todos los puntos para aplastar el poligono
                for (i = 0; i < aux_polygon->polygon_points_quantity; i++) {
                    if (atemp > btemp && atemp > ctemp) {
                        //significa que voy a omitir el eje x
                        polygonTemp[i].x = aux_polygon->polygon_points[i].y - yi;
                        polygonTemp[i].y = aux_polygon->polygon_points[i].z - zi;
                    } else if (btemp > atemp && btemp > ctemp) {
                        //significa que voy a omitir el eje y
                        polygonTemp[i].x = aux_polygon->polygon_points[i].x - xi;
                        polygonTemp[i].y = aux_polygon->polygon_points[i].z - zi;
                    } else {
                        //significa que voy a omitir el eje z
                        polygonTemp[i].x = aux_polygon->polygon_points[i].x - xi;
                        polygonTemp[i].y = aux_polygon->polygon_points[i].y - yi;
                    }
                }//end for

                //EMPIEZO A CONTAR PAREDES
                double u1, v1, u2, v2; //variables temporales para preguntar si la pared la atravieso o no!!
                int wallsCont = 0;
                for (i = 0; i < aux_polygon->polygon_points_quantity; i++) {

                    //OBTENGO DOS PUNTOS PARA ANALIZAR ESA RECTA
                    //pregunto si estoy en la ultima posicion
                    if (i == aux_polygon->polygon_points_quantity - 1) {
                        u1 = polygonTemp[i].x;
                        v1 = polygonTemp[i].y;

                        //primer elemento
                        u2 = polygonTemp[0].x;
                        v2 = polygonTemp[0].y;
                    } else {
                        u1 = polygonTemp[i].x;
                        v1 = polygonTemp[i].y;

                        //siguiente punto
                        u2 = polygonTemp[i + 1].x;
                        v2 = polygonTemp[i + 1].y;
                    }

                    //ACEPTACION TRIVIAL DE PARED
                    // Las dos U son positivas y
                    // al menos una v es negativa y la otra positiva
                    if ((u1 > 0.0 && u2 > 0.0) && ((v1 > 0.0 && v2 < 0.0) || (v1 < 0.0 && v2 > 0.0))) {
                        ++wallsCont;
                    } else {
                        //preguntar si es un caso complicado
                        //En el que una v sea positiva y la otra negativa y 
                        // una u sea negativa y la otra positiva
                        if (((u1 > 0.0 && u2 < 0.0) || (u1 < 0.0 && u2 > 0.0)) && ((v1 > 0.0 && v2 < 0.0) || (v1 < 0.0 && v2 > 0.0))) {

                            //COMO SI ES UN CASO COMPLICADO, CALCULO LA INTERSECCION DE LA LINEA CON EL EJE U
                            double m_line, b_line, x_line;

                            //pendiente de la recta
                            m_line = (v2 - v1) / (u2 - u1);
                            //interseccion con el eje y
                            b_line = v1 - (m_line * u1);

                            //con la informacion anterior puedo saber la interseccion con las x
                            x_line = (-1 * b_line) / m_line;

                            //si es mayor a cero entonces si interseca el eje de las x
                            if (x_line >= EPSILON_ZERO) {
                                ++wallsCont;
                            }
                        }//end if caso complicado
                    }//end else
                }//end for

                ///*************************************************************
                // finalizado el for CUENTO LAS PAREDES y digo si el punto esta dentro del poligono
                if (wallsCont % 2 != 0 || wallsCont == 1) {
                    //DIGO QUE ESTE OBJETO ES UN POLIGONO
                    //1 INDICA QUE ES POLIGONO
                    intersection_result->type = 4;

                    //guardo la nueva distancia
                    *tmin = t_polygonDistanceToEye;

                    //indico que este punto 3d contiene interseccion
                    intersection_result->isBackgound = 0;
                    //intersection_result->code = aux_polygon->code;

                    //establezco el nuevo rgb
                    intersection_result->red = aux_polygon->red;
                    intersection_result->green = aux_polygon->green;
                    intersection_result->blue = aux_polygon->blue;

                    //guardo la distancia en el objeto
                    intersection_result->distanceToEye = t_polygonDistanceToEye;

                    /***********************************************************/
                    /*        indico el vector normal de este poligono         */
                    VECTOR_3D normalTemp;
                    normalTemp.x = aux_polygon->a;
                    normalTemp.y = aux_polygon->b;
                    normalTemp.z = aux_polygon->c;
                    intersection_result->normalVector_N = normalTemp;

                    /*       indico los valores xi, yi, zi                     */
                    intersection_result->xi = xi;
                    intersection_result->yi = yi;
                    intersection_result->zi = zi;
                    /***********************************************************/

                    //guardo el coeficiente de reflexion difusa y el coeficiente de iluminacion ambiente
                    intersection_result->kd_diffuseReflectionCoefficient = aux_polygon->kd_diffuseReflectionCoefficient;
                    intersection_result->kA_environmentLightCoefficient = aux_polygon->kA_environmentLightCoefficient;
                }//end  if(wallsCont % 2 != 0)

            }//end (if t_polygonDistanceToEye < tmin)
        }//end (if t_denominator < 0)

        //analizo el siguiente poligono
        aux_polygon = aux_polygon->nextPtr;
    }//end while(aux_polygon != NULL) 
}

/*VERIFICA INTERSECCIONES CON LAS ESFERAS*/
void firstIntersection_Spheres(VECTOR_3D eye, VECTOR_3D direction, INTERSECTION_3D *intersection_result, double *tmin) {
    //coeficientes de la ecuacion
    double a_Sphere, b_Sphere, c_Sphere;
    double discriminating, t1, t2;

    /***************************************************************************/
    //recorro todas las esferas
    NODEPTR_SPHERE aux_sphere; //para recorrer la lista de esferas
    aux_sphere = startNode_SPHERE;
    while (aux_sphere != NULL) {

        //calculo el discriminante para ver si existe interseccion
        //a_Sphere = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);
        //por OPTIMIZACION -- SOLO PARA ESFERAS
        a_Sphere = 1;

        b_Sphere = 2 * (direction.x * (eye.x - aux_sphere->xCenter) +
                direction.y * (eye.y - aux_sphere->yCenter) +
                direction.z * (eye.z - aux_sphere->zCenter));

        c_Sphere = pow(eye.x - aux_sphere->xCenter, 2) + pow(eye.y - aux_sphere->yCenter, 2) + pow(eye.z - aux_sphere->zCenter, 2) -
                pow(aux_sphere->radius, 2);
        
        a_Sphere = 1 * a_Sphere;
        b_Sphere = 1 * b_Sphere;
        c_Sphere = 1 * c_Sphere;

        discriminating = pow(b_Sphere, 2) - 4 * a_Sphere * c_Sphere;

        //preguntar si existen soluciones
        if (discriminating > EPSILON_ZERO) {
            //CALCULO T1 y T2
            t1 = (-1 * b_Sphere + sqrt(discriminating)) / (2); //(2 * a_Sphere); como a_sphere es 1 lo omito
            t2 = (-1 * b_Sphere - sqrt(discriminating)) / (2); //(2 * a_Sphere); como a_sphere es 1 lo omito

            //switch para dejar el menor en t1
            if (t1 > t2) {
                double temp;
                temp = t1;
                t1 = t2;
                t2 = temp;
            }

            //pregunto si la esfera esta delante del ojo
            if (t1 > EPSILON_ZERO || t2 > EPSILON_ZERO) {

                //PREGUNTO SI ES LA MENOR INTERSECCION QUE ME HE TOPADO
                if (t1 < *tmin) {
                    //DIGO QUE ESTE OBJETO ES UNA ESFERA
                    //0 INDICA QUE ES ESFERA
                    intersection_result->type = 5;

                    //guardo la nueva distancia
                    *tmin = t1;

                    //indico que este punto 3d contiene interseccion
                    intersection_result->isBackgound = 0;
                    intersection_result->code = aux_sphere->code;

                    //establezco el nuevo rgb
                    intersection_result->red = aux_sphere->red;
                    intersection_result->green = aux_sphere->green;
                    intersection_result->blue = aux_sphere->blue;

                    //guardo la distancia en el objeto
                    intersection_result->distanceToEye = *tmin;

                    //guardo el coeficiente de reflexion difusa y el coeficiente de iluminacion ambiente
                    intersection_result->kd_diffuseReflectionCoefficient = aux_sphere->kd_diffuseReflectionCoefficient;
                    intersection_result->kA_environmentLightCoefficient = aux_sphere->kA_environmentLightCoefficient;


                    //FINALMENTE calculo el punto de interseccion xi, yi, zi... que es el punto de interseccion en la superficie de la esfera
                    intersection_result->xi = eye.x + *tmin * direction.x;
                    intersection_result->yi = eye.y + *tmin * direction.y;
                    intersection_result->zi = eye.z + *tmin * direction.z;
                    /*--------------*/

                    //luego voy a calcular el VECTOR NORMAL N. Vector perpendicular a la superficie del punto
                    //VECTOR_3D normalVector_N;
                    intersection_result->normalVector_N.x = (intersection_result->xi - aux_sphere->xCenter) / aux_sphere->radius;
                    intersection_result->normalVector_N.y = (intersection_result->yi - aux_sphere->yCenter) / aux_sphere->radius;
                    intersection_result->normalVector_N.z = (intersection_result->zi - aux_sphere->zCenter) / aux_sphere->radius;

                    //ALMACENO EN LA ESFERA EL VECTOR NORMAL AL OJO
                    aux_sphere->normalVector_N = intersection_result->normalVector_N;

                    //lo almaceno en la informacion de la esfera
                    //int myCode = intersection_result->code;
                    //storeNormalVectorIntoSphereList(myCode, intersection_result->normalVectorToEye_N); /**********************************************/
                    /*--------------*/

                }//if(t1 < tmin)

            }//if(t1 > EPSILON_ZERO && t2 > EPSILON_ZERO)

        }//if(discriminating > EPSILON_ZERO)


        aux_sphere = aux_sphere->nextPtr;
    }//end while
    /***************************************************************************/
}



/*almacena en la esfera actual el vector normal correspondiente*/
void storeNormalVectorIntoSphereList(int code, VECTOR_3D normalVector) {

    //recorro la lista
    NODEPTR_SPHERE aux_sphere; //para recorrer la lista de esferas
    aux_sphere = startNode_SPHERE;
    while (aux_sphere != NULL) {
        if (aux_sphere->code == code) {
            aux_sphere->normalVector_N = normalVector;
            break;
            return;
        }
        aux_sphere = aux_sphere->nextPtr;
    }//end while
}

/*obtiene la fuente de luz actual*/
VECTORLIGHTSOURCE_3D getCurrentLightSource(int position) {
    switch (position) {
        case 1:
        {
            return lightSource1_3D;
            break;
        }
        case 2:
        {
            return lightSource2_3D;
            break;
        }
        case 3:
        {
            return lightSource3_3D;
            break;
        }
    }//end switch
}