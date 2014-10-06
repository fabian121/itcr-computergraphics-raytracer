#include "Window3D.h"

/*metodo para inicializar las variables*/
void init_WINDOW3D(){
    
    //valores de la ventana
    xMin_3D = 0.0;
    yMin_3D = 0.0;
    
    xMax_3D = 1008;
    yMax_3D = 567;
    
    //valores del ojo
    xE_3D = (xMax_3D + xMin_3D)/2;
    yE_3D = (yMax_3D + yMin_3D)/2;
    zE_3D = -1000;
    
    //valores de la luz 1
    lightSource1_3D.xp = 700;
    lightSource1_3D.yp = 300;
    lightSource1_3D.zp = -500;
    
    lightSource1_3D.c1 = 0.0001;
    lightSource1_3D.c2 = 0.0001;
    lightSource1_3D.c3 = 0.000000001;
    lightSource1_3D.Ip_lightSourceIntensity = 1.0;
    
    //valores de luz 2
    lightSource2_3D.xp = 1500;
    lightSource2_3D.yp = 600;
    lightSource2_3D.zp = -400;
    
    lightSource2_3D.c1 = 0.01;
    lightSource2_3D.c2 = 0.001;
    lightSource2_3D.c3 = 0.000001;
    lightSource2_3D.Ip_lightSourceIntensity = 1.0;
    
    //valores de luz 3
    lightSource3_3D.xp = 1500;
    lightSource3_3D.yp = 800;
    lightSource3_3D.zp = 300;
    
    lightSource3_3D.c1 = 0.01;
    lightSource3_3D.c2 = 0.001;
    lightSource3_3D.c3 = 0.000001;
    lightSource3_3D.Ip_lightSourceIntensity = 1.0;
    
    
    
    //cantidad de fuentes de luz
    lightSourcesQuantity_3D = 2;

    
    //establecer el valor de la luz ambiente
    Ia_environmentLight_3D = 0.1;
}
