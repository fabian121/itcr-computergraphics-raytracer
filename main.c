/* 
 * File:   main.c
 * Author: root
 *
 * Created on May 17, 2013, 2:45 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "Framebuffer.h"
#include "RayTracing.h"
#include "Window3D.h"
#include "Sphere.h"
#include "Polygon.h"
#include "Disk.h"
#include "Cylinder.h"
#include "Cone.h"

int dataTest(int argc, char** argv);
int scene1(int argc, char** argv);

int main(int argc, char** argv) {
     
    return scene1(argc, argv);
    
}

int scene1(int argc, char** argv){
    //inicializo las listas de cada una de las figuras
    init_SPHERE();
    init_POLYGON();
    init_DISK();
    init_CYLINDER();
    
    /***************************************************************************/
    /************************** POLIGONOS **************************************/
    /***************************************************************************/
    //PARAMETROS>     int code_,
    //                          double red_, double green_, double blue_,
    //                                                                  VECTOR_3D *polygon_points_, int polygon_points_quantity_,
    //                                                                  double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_
    
    /*                          Piso                               */
    /*-------------------*/
    VECTOR_3D p1[4];
    p1[0].x = -474;
    p1[0].y = 0;
    p1[0].z = -2;
    
    p1[1].x = -498;
    p1[1].y = 0;
    p1[1].z = 431;
    
    p1[2].x = 1593;
    p1[2].y = 0;
    p1[2].z = 473;
    
    p1[3].x = 1640;
    p1[3].y = 0;
    p1[3].z = -2;
    insertNode_POLYGON(1,
                           0.545098039, 0.450980392, 0.333333333,
                           p1, 4,
                           1.0,1.0);
    /*---------------------*/
    /*-------------------*/
    VECTOR_3D p2[4];
    p2[0].x = -498;
    p2[0].y = 0;
    p2[0].z = 431;
    
    p2[1].x = -498;
    p2[1].y = 24;
    p2[1].z = 431;
    
    p2[2].x = 1593;
    p2[2].y = 24;
    p2[2].z = 473;
    
    p2[3].x = 1593;
    p2[3].y = 0;
    p2[3].z = 473;
    insertNode_POLYGON(2,
                           0.545098039, 0.450980392, 0.333333333,
                           p2, 4,
                           1.0,1.0);
    /*---------------------*/
    /*-------------------*/
    VECTOR_3D p3[4];
    p3[0].x = -498;
    p3[0].y = 24;
    p3[0].z = 431;
    
    p3[1].x = -507;
    p3[1].y = 24;
    p3[1].z = 604;
    
    p3[2].x = 1582;
    p3[2].y = 24;
    p3[2].z = 659;
    
    p3[3].x = 1593;
    p3[3].y = 24;
    p3[3].z = 473;
    insertNode_POLYGON(3,
                           0.545098039, 0.450980392, 0.333333333,
                           p3, 4,
                           1.0,1.0);
    /*---------------------*/
    /*-------------------*/
    VECTOR_3D p4[4];
    p4[0].x = -562;
    p4[0].y = -207;
    p4[0].z = 730;
    
    p4[1].x = -562;
    p4[1].y = 28;
    p4[1].z = 730;
    
    p4[2].x = 1829;
    p4[2].y = 28;
    p4[2].z = 935;
    
    p4[3].x = 1829;
    p4[3].y = -207;
    p4[3].z = 935;
    insertNode_POLYGON(4,
                           0.545098039, 0.450980392, 0.333333333,
                           p4, 4,
                           1.0,1.0);
    /*---------------------*/
    /*-------------------*/
    VECTOR_3D p5[4];
    p5[0].x = -562;
    p5[0].y = 28;
    p5[0].z = 730;
    
    p5[1].x = -7000;
    p5[1].y = 28;
    p5[1].z = 15000;
    
    p5[2].x = 10000;
    p5[2].y = 28;
    p5[2].z = 15000;
    
    p5[3].x = 1829;
    p5[3].y = 28;
    p5[3].z = 935;
    insertNode_POLYGON(5,
                           0.545098039, 0.450980392, 0.333333333,
                           p5, 4,
                           1.0,1.0);
    /*---------------------*/
    
    //                    MARIO
    VECTOR_3D p6[4];
    p6[0].x = 299;
    p6[0].y = 3;
    p6[0].z = -8;
    
    p6[1].x = 299;
    p6[1].y = 44;
    p6[1].z = -8;
    
    p6[2].x = 316;
    p6[2].y = 44;
    p6[2].z = -8;
    
    p6[3].x = 316;
    p6[3].y = 3;
    p6[3].z = -8;
    insertNode_POLYGON(6,
                           0.0, 0.0, 0.9,
                           p6, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p7[4];
    p7[0].x = 320;
    p7[0].y = 3;
    p7[0].z = -8;
    
    p7[1].x = 320;
    p7[1].y = 44;
    p7[1].z = -8;
    
    p7[2].x = 337;
    p7[2].y = 44;
    p7[2].z = -8;
    
    p7[3].x = 337;
    p7[3].y = 3;
    p7[3].z = -8;
    insertNode_POLYGON(7,
                           0.0, 0.0, 0.9,
                           p7, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p8[4];
    p8[0].x = 299;
    p8[0].y = 34;
    p8[0].z = -8;
    
    p8[1].x = 299;
    p8[1].y = 56;
    p8[1].z = -8;
    
    p8[2].x = 337;
    p8[2].y = 56;
    p8[2].z = -8;
    
    p8[3].x = 337;
    p8[3].y = 34;
    p8[3].z = -8;
    insertNode_POLYGON(8,
                           0.0, 0.0, 0.9,
                           p8, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p9[4];
    p9[0].x = 299;
    p9[0].y = 56;
    p9[0].z = -8;
    
    p9[1].x = 299;
    p9[1].y = 68;
    p9[1].z = -8;
    
    p9[2].x = 337;
    p9[2].y = 68;
    p9[2].z = -8;
    
    p9[3].x = 337;
    p9[3].y = 56;
    p9[3].z = -8;
    insertNode_POLYGON(9,
                           1.0, 0.0, 0.0,
                           p9, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p10[4];
    p10[0].x = 275;
    p10[0].y = 37;
    p10[0].z = 0;
    
    p10[1].x = 268;
    p10[1].y = 46;
    p10[1].z = 0;
    
    p10[2].x = 299;
    p10[2].y = 68;
    p10[2].z = -8;
    
    p10[3].x = 299;
    p10[3].y = 56;
    p10[3].z = -8;
    insertNode_POLYGON(10,
                           1.0, 0.0, 0.0,
                           p10, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p11[4];
    p11[0].x = 307;
    p11[0].y = 56;
    p11[0].z = -8;
    
    p11[1].x = 307;
    p11[1].y = 68;
    p11[1].z = -8;
    
    p11[2].x = 312;
    p11[2].y = 68;
    p11[2].z = -8;
    
    p11[3].x = 312;
    p11[3].y = 56;
    p11[3].z = -8;
    insertNode_POLYGON(11,
                           0.0, 0.0, 0.9,
                           p11, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p12[4];
    p12[0].x = 324;
    p12[0].y = 56;
    p12[0].z = -8;
    
    p12[1].x = 324;
    p12[1].y = 68;
    p12[1].z = -8;
    
    p12[2].x = 328;
    p12[2].y = 68;
    p12[2].z = -8;
    
    p12[3].x = 328;
    p12[3].y = 56;
    p12[3].z = -8;
    insertNode_POLYGON(12,
                           0.0, 0.0, 0.9,
                           p12, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p13[4];
    p13[0].x = 337;
    p13[0].y = 68;
    p13[0].z = 8;
    
    p13[1].x = 327;
    p13[1].y = 68;
    p13[1].z = 8;
    
    p13[2].x = 327;
    p13[2].y = 89;
    p13[2].z = 40;
    
    p13[3].x = 337;
    p13[3].y = 89;
    p13[3].z = 40;
    insertNode_POLYGON(13,
                           1.0, 0.0, 0.0,
                           p13, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p14[4];
    p14[0].x = 327;
    p14[0].y = 68;
    p14[0].z = -8;
    
    p14[1].x = 327;
    p14[1].y = 68;
    p14[1].z = 8;
    
    p14[2].x = 337;
    p14[2].y = 68;
    p14[2].z = 8;
    
    p14[3].x = 337;
    p14[3].y = 68;
    p14[3].z = -8;
    insertNode_POLYGON(14,
                           1.0, 0.0, 0.0,
                           p14, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p15[4];
    p15[0].x = 337;
    p15[0].y = 68;
    p15[0].z = 8;
    
    p15[1].x = 337;
    p15[1].y = 89;
    p15[1].z = 40;
    
    p15[2].x = 337;
    p15[2].y = 77;
    p15[2].z = 39;
    
    p15[3].x = 337;
    p15[3].y = 56;
    p15[3].z = 8;
    insertNode_POLYGON(15,
                           1.0, 0.0, 0.0,
                           p15, 4,
                           1.0,1.0);
    
    /*---------------------*/
    VECTOR_3D p16[4];
    p16[0].x = 337;
    p16[0].y = 56;
    p16[0].z = -8;
    
    p16[1].x = 337;
    p16[1].y = 68;
    p16[1].z = -8;
    
    p16[2].x = 337;
    p16[2].y = 68;
    p16[2].z = 8;
    
    p16[3].x = 337;
    p16[3].y = 56;
    p16[3].z = 8;
    insertNode_POLYGON(16,
                           1.0, 0.0, 0.0,
                           p16, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p17[4];
    p17[0].x = 337;
    p17[0].y = 3;
    p17[0].z = -8;
    
    p17[1].x = 337;
    p17[1].y = 56;
    p17[1].z = -8;
    
    p17[2].x = 337;
    p17[2].y = 56;
    p17[2].z = 8;
    
    p17[3].x = 337;
    p17[3].y = 3;
    p17[3].z = 8;
    insertNode_POLYGON(17,
                           0.0, 0.0, 0.9,
                           p17, 4,
                           1.0,1.0);
    /*---------------------*/
    VECTOR_3D p18[6];
    p18[0].x = 312;
    p18[0].y = 81;
    p18[0].z = -13;
    
    p18[1].x = 307;
    p18[1].y = 90;
    p18[1].z = -11;
    
    p18[2].x = 312;
    p18[2].y = 98;
    p18[2].z = -8;
    
    p18[3].x = 322;
    p18[3].y = 98;
    p18[3].z = -8;
    
    p18[4].x = 327;
    p18[4].y = 90;
    p18[4].z = -11;
    
    p18[5].x = 322;
    p18[5].y = 81;
    p18[5].z = -13;
    insertNode_POLYGON(18,
                           1.0, 0.0, 0.0,
                           p18, 6,
                           0.5,1.0);
    /*---------------------*/
    VECTOR_3D p19[4];
    p19[0].x = 275;
    p19[0].y = 37;
    p19[0].z = 8;
    
    p19[1].x = 275;
    p19[1].y = 37;
    p19[1].z = -8;
    
    p19[2].x = 299;
    p19[2].y = 53;
    p19[2].z = -8;
    
    p19[3].x = 299;
    p19[3].y = 53;
    p19[3].z = 8;
    insertNode_POLYGON(19,
                           1.0, 0.0, 0.0,
                           p19, 4,
                           0.5,1.0);
    
    
    
    
    
    /*---------------------          cajas*/
    VECTOR_3D p20[4];
    p20[0].x = 416;
    p20[0].y = 1;
    p20[0].z = 23;
    
    p20[1].x = 416;
    p20[1].y = 24;
    p20[1].z = 23;
    
    p20[2].x = 441;
    p20[2].y = 24;
    p20[2].z = 23;
    
    p20[3].x = 441;
    p20[3].y = 1;
    p20[3].z = 23;
    insertNode_POLYGON(20,
                           0.9, 0.270588235, 0.0,
                           p20, 4,
                           0.5,1.0);
    /*       -------------          */
    VECTOR_3D p21[4];
    p21[0].x = 416;
    p21[0].y = 24;
    p21[0].z = 23;
    
    p21[1].x = 416;
    p21[1].y = 24;
    p21[1].z = 44;
    
    p21[2].x = 441;
    p21[2].y = 24;
    p21[2].z = 44;
    
    p21[3].x = 441;
    p21[3].y = 24;
    p21[3].z = 23;
    insertNode_POLYGON(21,
                           0.9, 0.270588235, 0.0,
                           p21, 4,
                           0.5,1.0);
    /*       -------------          */
    VECTOR_3D p22[4];
    p22[0].x = 441;
    p22[0].y = 1;
    p22[0].z = 23;
    
    p22[1].x = 441;
    p22[1].y = 24;
    p22[1].z = 23;
    
    p22[2].x = 441;
    p22[2].y = 24;
    p22[2].z = 44;
    
    p22[3].x = 441;
    p22[3].y = 1;
    p22[3].z = 44;
    insertNode_POLYGON(22,
                           0.9, 0.270588235, 0.0,
                           p22, 4,
                           0.5,1.0);
    /*       -------------          */
    /***************************************************************************/
    /*************************** cilindros *************************************/
    /***************************************************************************/
    //PARAMETROS>     int code_,
    //        double red_, double green_, double blue_,
    //        double x0_, double y0_, double z0_, double radius_,
    //        VECTOR_3D vectorQ_, int isInfinite_,
    //          double h1_distance, double h2_distance,
    //        double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_)
    VECTOR_3D c1;
    c1.x = 0;
    c1.y = -6660;
    c1.z = 0;
    insertNode_CYLINDER(1,
                        0.2,1.0,0.1,
                        -179,198,1096,100,
                        c1, 0,
                        0, 400,
                        1.0,1.0);
    insertNode_CYLINDER(2,
                        0.2,1.0,0.1,
                        -346,274,1392,100,
                        c1, 0,
                        0, 400,
                        1.0,1.0);
    insertNode_CYLINDER(3,
                        0.2,1.0,0.1,
                        272,390,2605,100,
                        c1, 0,
                        0, 400,
                        1.0,1.0);
    insertNode_CYLINDER(4,
                        0.2,1.0,0.1,
                        -1000,515,4488,100,
                        c1, 0,
                        0, 800,
                        1.0,1.0);
    insertNode_CYLINDER(5,
                        0.2,1.0,0.1,
                        600,98,736,100,
                        c1, 0,
                        0, 800,
                        1.0,1.0);
    insertNode_CYLINDER(6,
                        0.960784313, 0.960784313, 0.862745098,
                        315,75,0,7,
                        c1, 0,
                        0, 20,
                        1.0,1.0);
    /***************************************************************************/
    /***********************  ESFERAS   ****************************************/
    /***************************************************************************/
    //PARAMETROS>     radius, 
    //                       xCenter, yCenter, zCenter, 
    //                                                  red, green, blue
    //                                                                    kd_diffuseReflectionCoefficient, kA_environmentLightCoefficient
    
    /*                          ESFERAS                               */
    FILE *fspheres;
    
    //variables de la espera
    int code, radius;
    double xcenter, ycenter, zcenter, red, green, blue, kd, ka;
    fspheres = fopen("spheres.txt", "r");
    
    //recorro el archivo de esferas para ir insertandolas
    while(1 == 1){
        if(fscanf(fspheres, "%d %d %lf %lf %lf %lf %lf %lf %lf %lf", &code, &radius, &xcenter, &ycenter, &zcenter, &red, &green, &blue, &kd, &ka) < 1) 
            break;
        insertNode_SPHERE(code, radius, xcenter, ycenter, zcenter, red, green, blue, kd, ka);
    }  
    fclose(fspheres);
    
    /***************************************************************************/
    /***************************   CONOS   *************************************/
    /***************************************************************************/
    //PARAMETROS> int code_,
    //        double red_, double green_, double blue_,
    //        double x0_, double y0_, double z0_,
    //        VECTOR_3D vectorQ_, int isInfinite_,
    //        double v_ratio_, double u_ratio_, 
    //        h1,h2
    //        double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_
    insertNode_CONE(1,
                        0.411764705, 0.545098039, 0.411764705,
                        1200,600,2500,
                        c1, 0,
                        4,3,
                        200, 3000,
                        0.6,1.0);
    
    insertNode_CONE(1,
                        0.411764705, 0.545098039, 0.411764705,
                        -3116,600,6855,
                        c1, 0,
                        4,3,
                        200, 3000,
                        0.6,1.0);
    insertNode_CONE(1,
                        0.411764705, 0.545098039, 0.411764705,
                        -2516,900,7200,
                        c1, 0,
                        4,3,
                        200, 3000,
                        0.6,1.0);
    
    
    insertNode_CONE(1,
                        0.9, 0.245098039, 0.411764705,
                        0,1800,12000,
                        c1, 0,
                        4,3,
                        0, 3000,
                        0.6,1.0);
    
    
    
    //inicializar los valores para la ventana
    init_WINDOW3D();

    //establezco el tamanno del framebuffer
    hSize_FRAMEBUFFER = 1008;
    vSize_FRAMEBUFFER = 567;
    rayTracingAlgorithm_RAYTRACING(argc, argv, 0);
    
    return (EXIT_SUCCESS);
}


int dataTest(int argc, char** argv){
    //inicializo las listas de cada una de las figuras
    init_SPHERE();
    init_POLYGON();
    init_DISK();
    init_CYLINDER();
    
    //cargar los datos de prueba
    //dataTest();
    /***************************************************************************/
    /***********************  ESFERAS   ****************************************/
    /***************************************************************************/
    //PARAMETROS>     radius, 
    //                       xCenter, yCenter, zCenter, 
    //                                                  red, green, blue
    //                                                                    kd_diffuseReflectionCoefficient, kA_environmentLightCoefficient
    
    /*                          ESFERAS                               */
    FILE *fspheres;
    
    //variables de la espera
    int code, radius;
    double xcenter, ycenter, zcenter, red, green, blue, kd, ka;
    fspheres = fopen("xfile_spheres.txt", "r");
    
    //recorro el archivo de esferas para ir insertandolas
    while(1 == 1){
        if(fscanf(fspheres, "%d %d %lf %lf %lf %lf %lf %lf %lf %lf", &code, &radius, &xcenter, &ycenter, &zcenter, &red, &green, &blue, &kd, &ka) < 1) 
            break;
        insertNode_SPHERE(code, radius, xcenter, ycenter, zcenter, red, green, blue, kd, ka);
    }  
    fclose(fspheres);
    
    /***************************************************************************/
    /************************** POLIGONOS **************************************/
    /***************************************************************************/
    //PARAMETROS>     int code_,
    //                          double red_, double green_, double blue_,
    //                                                                  VECTOR_3D *polygon_points_, int polygon_points_quantity_,
    //                                                                  double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_
    
    /*                          Poligonos                               */
    /*-------------------*/
    VECTOR_3D pol_0_0[3];
    pol_0_0[0].x = 390;//300
    pol_0_0[0].y = 216;
    pol_0_0[0].z = 124;//230
    pol_0_0[1].x = 529;
    pol_0_0[1].y = 216;
    pol_0_0[1].z = 50;
    pol_0_0[2].x = 529;
    pol_0_0[2].y = 29;
    pol_0_0[2].z = 50;
    insertNode_POLYGON(1000,
                           1.0, 1.0, 0.0,
                           pol_0_0, 3,
                           1.0,1.0);// poligono amarillo
    /*---------------------*/

    /*---------------------*/
    VECTOR_3D pol_1_0[4];
    pol_1_0[0].x = 21;
    pol_1_0[0].y = 15;
    pol_1_0[0].z = 6;
    pol_1_0[1].x = 90;
    pol_1_0[1].y = 316;
    pol_1_0[1].z = 124;
    pol_1_0[2].x = 229;
    pol_1_0[2].y = 129;
    pol_1_0[2].z = 50;
    pol_1_0[3].x = 209;
    pol_1_0[3].y = 39;
    pol_1_0[3].z = 15;
    insertNode_POLYGON(1001,
                           0.0, 0.0, 1.0,
                           pol_1_0, 4,
                           1.0,1.0);// poligono azul
    VECTOR_3D pol_1_1[3];
    pol_1_1[0].x = 90;//300
    pol_1_1[0].y = 316;
    pol_1_1[0].z = 124;//230
    pol_1_1[1].x = 229;
    pol_1_1[1].y = 316;
    pol_1_1[1].z = 50;
    pol_1_1[2].x = 229;
    pol_1_1[2].y = 129;
    pol_1_1[2].z = 50;

    insertNode_POLYGON(1002,
                           0.0, 0.0, 1.0,
                           pol_1_1, 3,
                           1.0,1.0);// poligono azul
    /*----------------------*/
    
    /*----------------------*/
    VECTOR_3D pol_2_0[3];
    pol_2_0[0].x = 300;//300
    pol_2_0[0].y = 700;
    pol_2_0[0].z = 230;//230
    pol_2_0[1].x = 350;
    pol_2_0[1].y = 750;
    pol_2_0[1].z = 200;
    pol_2_0[2].x = 400;
    pol_2_0[2].y = 700;
    pol_2_0[2].z = 200;

    insertNode_POLYGON(1003,
                           0.0, 1.0, 0.0,
                           pol_2_0, 3,
                           1.0,1.0);// poligono verde
    /*-----------------------*/
    
    /*----------------------*/
    int xtemp = 80, ytemp = 250;
    VECTOR_3D pol_3_0[3];
    pol_3_0[0].x =  480 + xtemp;
    pol_3_0[0].y =  160 + ytemp;
    pol_3_0[0].z =  -250;
    pol_3_0[1].x =  450 + xtemp;
    pol_3_0[1].y =  200 + ytemp;
    pol_3_0[1].z =  -300;
    pol_3_0[2].x =  550+ xtemp;
    pol_3_0[2].y = 200 + ytemp;
    pol_3_0[2].z =  -250;

    insertNode_POLYGON(1004,
                           0.0, 1.0, 0.0,
                           pol_3_0, 3,
                           1.0,1.0);// poligono verde

    
    /***************************************************************************/
    /*************************** DISCOS ****************************************/
    /***************************************************************************/
    //PARAMETROS>     int code_, 
    //                        double radius_, 
    //                        double xCenter_, double yCenter_, double zCenter_, 
    //                                        VECTOR_3D disk_points_, 
    //                                        double red_, double green_, double blue_, 
    //                                                  int isNormalVector,
    //                                                        double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_
    VECTOR_3D disk1[3];
    disk1[0].x =  480;
    disk1[0].y =  160;
    disk1[0].z =  -120;
    disk1[1].x =  500;
    disk1[1].y =  250;
    disk1[1].z =  -5;
    disk1[2].x =  550;
    disk1[2].y = 200;
    disk1[2].z =  -5;
/*
    insertNode_DISK(500,
                        50,
                        500,200,0,
                        disk1,
                        1.0, 0.0, 1.0,
                        0,
                        1.0,1.0);// magenta 
*/
    
    VECTOR_3D disk2[1];
    disk2[0].x = 50;//-420;//579;
    disk2[0].y = 50;//-595;//101;
    disk2[0].z = 120;//-400;//129;
/*
    disk2[1].x = 599;
    disk2[1].y = 101;
    disk2[1].z = 108;
    disk2[2].x = 614;
    disk2[2].y = 81;
    disk2[2].z = 122;
*/
    insertNode_DISK(501,
                        45,
                        300,100,-160,
                        disk2,
                        1.0, 0.0, 0.5,
                        1,
                        1.0,1.0);// magenta 
    
    
    /***************************************************************************/
    /*************************** cilindros *************************************/
    /***************************************************************************/
    //PARAMETROS>     int code_,
    //        double red_, double green_, double blue_,
    //        double x0_, double y0_, double z0_, double radius_,
    //        VECTOR_3D vectorQ_, int isInfinite_,
    //          double h1_distance, double h2_distance,
    //        double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_)
    VECTOR_3D cylinder1;
    cylinder1.x = 50;
    cylinder1.y = 50;
    cylinder1.z = 100;
    insertNode_CYLINDER(600,
                        0.0,1.0,0.0,
                        400,400,70,80,
                        cylinder1, 0,
                        -50, 150,
                        1.0,1.0);
    
    /***************************************************************************/
    /***************************   CONOS   *************************************/
    /***************************************************************************/
    //PARAMETROS> int code_,
    //        double red_, double green_, double blue_,
    //        double x0_, double y0_, double z0_,
    //        VECTOR_3D vectorQ_, int isInfinite_,
    //        double v_ratio_, double u_ratio_, 
    //        double kd_diffuseReflectionCoefficient_, double kA_environmentLightCoefficient_
    VECTOR_3D cone1;
    cone1.x = 50;
    cone1.y = 50;
    cone1.z = 80;
    insertNode_CONE(1,
                        1.0, 0.0, 0.0,
                        400,180,100,
                        cone1, 0,
                        1,2,
                        200, 2000,
                        1.0,1.0);
    
    /***************************************************************************/
    /***************************************************************************/
    /***************************************************************************/
    
    //inicializar los valores para la ventana
    init_WINDOW3D();

    //establezco el tamanno del framebuffer
    hSize_FRAMEBUFFER = 1008;
    vSize_FRAMEBUFFER = 567;
    rayTracingAlgorithm_RAYTRACING(argc, argv, 1);
    
    return (EXIT_SUCCESS);
}










/*
    insertNode_SPHERE(0, 100, 
            300, 700, 300, 
            0.0, 0.0, 1.0, 
            1.0, 1.0);//azul
    
    insertNode_SPHERE(1, 50, 
            300, 550, 50, 
            0.0, 1.0, 0.0, 
            0.5, 0.0);//verde
    
    insertNode_SPHERE(2, 150, 
            650, 600, 0, 
            1.0, 0.0, 0.0, 
            1.0, 1.0);//roja
    
    insertNode_SPHERE(3, 100,
            400,400, 200,
            1.0, 1.0, 0.0,
            1.0, 0.8);//amarilla
    
    insertNode_SPHERE(4, 25,
            445, 460, -10,
            1.0, 1.0, 1.0,
            1.0, 1.0);//magenta
    
    insertNode_SPHERE(5, 25,
            100, 100, -5,
            1.0, 0.2, 0.2,
            1.0, 1.0);//roja
*/