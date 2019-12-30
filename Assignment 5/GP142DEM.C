/*
 * CSE/ENGR 142 GP142_Demo
 *
 * 1/25/95
 * Author(s):         Larry Ruzzo
 * Email Address(s):  ruzzo@cs.washington.edu
 *
 * This program is a demo of some of the features of 
 * GP142 --- the CSE/ENGR 142 Graphics Package.
 * It includes simple drawing commands, keyboard and mouse 
 * interaction, and a simple animation.
 *
 * Revision history:
 * 11/18/97 Dan Boren  - Removed calls to obsolete function GP142_undo()
 *      
 */
 
#include "GP142.h"
#include <stdio.h>
#include <math.h>
#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
/* 
 * Function prototypes.
 */
void demo_handle_kbd(char key_pressed);
void demo_handle_mouse(int x,int y);
void demo_handle_periodic(void);
void demo_draw_stuff(void);
void demo_draw_house(int x, int y);
void demo_draw_arrow(double tail_x, double tail_y, double angle, 
					 double length, int color);
void demo_draw_circle_overhanging(void);
double ellipse_radius(double theta, double a, double b);
double polar_to_x(double r, double theta);
double polar_to_y(double r, double theta);
double degrees_to_radians(double degrees);
int rnd(double x);

/******************************************************************************
 *
 * The Main Program
 * ----------------
 *
 * The main program takes care of initialization and cleanup, and the high-level
 * control of all actions in the program, but most of the detail work is 
 * relegated to sub-functions, so that the structure of main stays clear and 
 * simple.
 *
 */
int main(void)
{                                
    int quit = 0;           /* has user signaled quit yet?                      */
    int mouse_x, mouse_y;
    char key_pressed;
    GP142_open();           /* Open and initialize the GP142 Graphics Window    */
    
    GP142_logging(LOG_OFF); /* logging is useful to students during debugging,  */
                            /* but annoying during the demo; turn it off.       */
    /*
     * Demonstrate basic drawing of shapes and text 
     */
     
    demo_draw_stuff();

    /*
     * The main event loop:
     * --- ---- ----- -----
     * wait for the next user action, such as a mouse click or keyboard
     * keypress, or a periodic update event (allowing us to display the
     * next frame of an animation) and call the appropriate function to
     * handle it.  Repeat this until the user signals "quit".
     */
     
    while (!quit) {
    
        switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
            case GP142_QUIT:
                quit = 1;   /* set flag to terminate loop                */
                break;
   
            case GP142_MOUSE:
                demo_handle_mouse(mouse_x,mouse_y);
                break;
               
            case GP142_KBD:
                demo_handle_kbd(key_pressed);
                break;
            case GP142_PERIODIC:
                demo_handle_periodic();
                break;
            default:
                break;
        }
    }
        
    GP142_close();          /* Clean up and close graphics window           */
    
    return 0;
}
/******************************************************************************
 *
 * demo_draw_stuff
 * ---------------
 *
 * draws coordinate axes and a few sample shapes 
 * to demonstrate the basics of drawing and text.
 *
 */
void 
demo_draw_stuff(void)
{
    int i;
    #define AXIS_COLOR  RED
    #define TICK          3
    #define TEXT_SIZE    12
    
    /* draw over the entire window in black, to change the background color */
    /* GP142_XMAX/GP142_YMAX are from GP142.h                               */
    GP142_rectangleXY(BLACK, -GP142_XMAX, -GP142_YMAX, GP142_XMAX, GP142_YMAX, 0);
   
    /* 3 concentric rectangles, varying line width and color */
    GP142_rectangleXY(CYAN,  -25,-20,25,20,9);
    GP142_rectangleXY(GREEN, -25,-20,25,20,5);
    GP142_rectangleXY(BLACK, -25,-20,25,20,1);
    /* 2 concentric triangles, varying line width and color */
    GP142_triangleXY(GREEN, -90, -37, -40, -37, -65, -57, 5);
    GP142_triangleXY(RED,   -90, -37, -40, -37, -65, -57, 1);
    /* rectangle surrounding an oval */
    GP142_rectangleXY(MAGENTA, -90, -90, -40, -60, 1);
    GP142_ovalXY     (BLUE,    -90, -90, -40, -60, 0);

    /* circle overhanging (circular) oval */
	demo_draw_circle_overhanging();

    /* Y-axis, with tick marks every 10 pixels */
    GP142_lineXY(AXIS_COLOR,0,-GP142_YMAX,0,GP142_YMAX,1);
    for (i=-(GP142_YMAX/10*10); i <= GP142_YMAX/10*10 ; i=i+10){
        GP142_lineXY(AXIS_COLOR,-TICK,i,+TICK,i,1);
    }
    /* X-axis, with tick marks every 10 pixels */  
    GP142_lineXY(AXIS_COLOR,-GP142_XMAX,0,GP142_XMAX,0,1);
    for (i=-(GP142_XMAX/10*10); i <= GP142_XMAX/10*10 ; i=i+10){
        GP142_lineXY(AXIS_COLOR,i,-TICK,i,+TICK,1);
    }
    /* One pixel at the origin                  */
    GP142_pixelXY(GREEN,0,0);

    /* draw that cute little house twice */
    demo_draw_house(- 80,10);
    demo_draw_house(-110,10);
    
    /* text examples */
    GP142_printfXY(BLUE, -60, 40,   TEXT_SIZE, "Go,\nDog,\nGo!");
    GP142_printfXY(YELLOW,40,-95, 2*TEXT_SIZE, "GP142");
    
    /* Promt user to turn on animation */
    GP142_printfXY(MAGENTA,10,70,TEXT_SIZE, ANIMATE_MSG);
}

/******************************************************************************
 *
 * demo_draw_house
 * ---------------
 *
 * Draw a cute little house roughly at position x,y
 *
 */
void
demo_draw_house(int x, int y)
{
    GP142_rectangleXY(GREEN, x-10, y- 5, x+10, y+8 , 0); /* walls */
    GP142_rectangleXY(BLACK, x- 2, y- 5, x+ 2, y+2 , 0); /* door  */
    GP142_rectangleXY(BLACK, x- 7, y   , x- 5, y+2 , 0); /* window*/
    GP142_rectangleXY(BLACK, x+ 5, y   , x+ 7, y+2 , 0); /* window*/
    GP142_triangleXY (RED,   x-12, y+ 8,                 /* roof  */
                             x+12, y+ 8,
                             x,    y+14,             0);
}

/******************************************************************************
 *
 * demo_draw_circle_overhanging
 * ---------------
 *
 * Draw a magenta circle outlined in yellow
 *
 */
void 
demo_draw_circle_overhanging(void)
{
    GP142_circleXY(YELLOW,  40, 40, 11);
    GP142_ovalXY(  MAGENTA, 30, 30, 50, 50, 0);
}


/******************************************************************************
 *
 * demo_handle_mouse
 * -----------------
 *
 * This function handles mouse clicks, echoing coordinates 
 * both to the console and in the graphics window.
 *
 */
void demo_handle_mouse(int x, int y){
    printf("Mouse clicked at (%d,%d)\n", x, y);
    GP142_printfXY(RED,x,y,9,"Mouse at (%d,%d)", x, y);
}

/******************************************************************************
 *
 * demo_handle_kbd
 * ---------------
 *
 * This function handles keyboard keystrokes.
 * Characters are simply echoed along the top of the 
 * graphics window.  They wrap around when it's about to 
 * go off screen, but overwritten characters are NOT erased.
 *
 */
void demo_handle_kbd(char c)
{
    const  int typing_width = 200;      /* pixels   */
    const  int typing_y     = 80;       /* pixels   */
    const  int point_size   = 20;
    const  int wrap_count   = (typing_width/point_size);    
    static int key_count    = 0;        /* count number of keypresses   */
    
    GP142_printfXY(RED, -typing_width/2+point_size*key_count,
                    typing_y, point_size, "%c", c);
    key_count = (key_count+1) % wrap_count;
}

/******************************************************************************
 *
 * demo_handle_periodic
 * --------------------
 *
 * GP142_await_event() periodically (say, 10-20 times per second) returns a
 * "clock tick" event.  It can be used to do simple animations.  In this
 * demo, the animation is to move a "clock hand" (a blue arrow) around an
 * oval "clock face".  Every tick event calls demo_handle_periodic, which
 * redraws the arrow degrees_per_frame further around the clock face.
 *
 * Since this clock overlaps the circle drawn by demo_draw_circle_overhanging(),
 * on every clock tick we must: 1) Erase the last hand 2) redraw this circle
 * 3) drawing or redrawing the outline of the clock face, and finally, 4) drawing
 * or redrawing the hand in its new position.
 */
void demo_handle_periodic(void)
{
    const double degrees_per_frame  = -10.0;
    const double ell_a              = 50.0;     /* ellipse x radius */
    const double ell_b              = 20.0;     /* ellipse y radius */
    const int    center_x           = 65;       /* ellipse x center */
    const int    center_y           = 60;       /* ellipse y center */
    
    static int t=0;                 /* count number of calls ("time") */
    double theta, radius;
    
    if ( t == 0 ) {
        /* first time, hide the prompt  */
        GP142_printfXY(BLACK,10,70,TEXT_SIZE, ANIMATE_MSG);
    } else {
		/* Erase the last arrow by drawing the arrow drawn on the last clock 
		   tick, but this time in black */
	    theta  = degrees_to_radians((t-1) * degrees_per_frame);
        radius = ellipse_radius(theta, ell_a, ell_b);
		demo_draw_arrow(center_x, center_y, theta, radius, BLACK);

		/*Redraw circle that the clock face overlaps */
		demo_draw_circle_overhanging();

    }

	/* (Draw the outline of the clock face */
    GP142_ovalXY(RED,center_x - (int)ell_a - 1, center_y - (int)ell_b - 1,
                         center_x + (int)ell_a + 1, center_y + (int)ell_b + 1, 1);

	/* Draw the hand */
    theta  = degrees_to_radians(t * degrees_per_frame);
    radius = ellipse_radius(theta, ell_a, ell_b);
    demo_draw_arrow(center_x, center_y, theta, radius, BLUE);
    t++;
}

/******************************************************************************
 *
 * ellipse_radius
 * polar_to_x
 * polar_to_y
 * --------------
 *
 * An ellipse centered at the origin and passing through 
 * x = +- a, y = +- b satisfies (x*x/a*a + y*y/b*b ==1).
 * With a little trig, this can be converted to polar coordinates:
 *
 *  r*r = a*a*b*b/(a*a*sin(theta)*sin(theta) + b*b*cos(theta)*cos(theta))
 *
 * The following functions compute r, x, and y, given a, b, and theta.
 * (Understanding this math is *NOT* essential to understanding GP142.)
 *
 */
double
ellipse_radius(double theta, double a, double b)
{
    return ( a*b/sqrt( a*a*pow(sin(theta),2.0)+b*b*pow(cos(theta),2.0)));
}
double
polar_to_x(double r, double theta)
{
    return ( r * cos(theta) );
}
double
polar_to_y(double r, double theta)
{
    return ( r * sin(theta) );
}
/******************************************************************************
 *
 * degrees_to_radians
 * ------------------
 * convert degrees to radians, according to the formula
 *   2 Pi radians == 360 degrees
 *
 */
double
degrees_to_radians(double degrees)
{
    return ( degrees * 2.0 * PI / 360.0 );
}

/******************************************************************************
 *
 * rnd
 * ---
 * round a double to the nearest int
 *
 */
int
rnd(double x)
{
    return ( (int)(x+0.5) );
}

/******************************************************************************
 *
 * demo_draw_arrow
 * ---------------
 *
 * draw a blue arrow with tail at the indicated x,y coordinates, of length
 * "radius", and angle "theta" (radians).
 *
 * Quite arbitrarily, the arrow head is approximately 4 pixels long, 
 * and its base is 3 degrees wide when viewed from the tail.
 *
 */
void
demo_draw_arrow(double tail_x, double tail_y, double theta, double radius, int color)
{
    const double ptr_angle = degrees_to_radians(3.0);
    const double ptr_len   = 4.0;
    double x0,x1,x2,y0,y1,y2;
    
    x0 = polar_to_x(radius, theta);                 /* tip of arrow head    */
    y0 = polar_to_y(radius, theta);
    x1 = polar_to_x(radius - ptr_len, theta - ptr_angle);/* corner of head  */
    y1 = polar_to_y(radius - ptr_len, theta - ptr_angle);
    x2 = polar_to_x(radius - ptr_len, theta + ptr_angle);/* the other corner*/
    y2 = polar_to_y(radius - ptr_len, theta + ptr_angle);
    
    /* implicit conversion from doubles to ints in the function calls below */
    GP142_lineXY(color,    rnd(tail_x),      rnd(tail_y), 
                          rnd(tail_x + x0), rnd(tail_y + y0), 1);
    GP142_triangleXY(color,rnd(tail_x + x0), rnd(tail_y + y0),
                          rnd(tail_x + x1), rnd(tail_y + y1),
                          rnd(tail_x + x2), rnd(tail_y + y2), 0);
}

/*****************************************************************************/
