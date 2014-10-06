/* 
 * File:   Framebuffer.h
 * Author: root
 *
 * Created on May 17, 2013, 4:51 PM
 */

#ifndef FRAMEBUFFER_H
#define	FRAMEBUFFER_H

#ifdef	__cplusplus
extern "C" {
#endif

//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
#include "Window3D.h"

    int hSize_FRAMEBUFFER, vSize_FRAMEBUFFER;
    RGB_3D framebuffer_FRAMEBUFFER[1008][567];
    
    void start_FRAMEBUFFER(int argc, char** argv);

    
    


#ifdef	__cplusplus
}
#endif

#endif	/* FRAMEBUFFER_H */

