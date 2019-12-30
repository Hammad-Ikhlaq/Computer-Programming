#define _CRT_SECURE_NO_WARNINGS

#include "gp142lib.h"                   /* Library specific header */
#define GP142_RCSREV    "$Revision: 1.17 $"
#define GP142_RCSDATE   "$Date"
#define GP142_VERSION   "2.2xx"
#define GP142_DATE      "April 2000"        

#define TIME_PER_STEP 50
#define MAXSTRLEN 200                   /* max string length for text fns */
#define UNUSED(parameter) (parameter = parameter)

#if defined(WINDOWS)
#define GP142_FUNC FAR EXPORT
#define FUDGE   40  /* On the PC, the window is off by 40 pixels in the */
                    /* Y dimension.  Until we find a general fix, we're */
                    /* stuck with this hack. -- brd */
#elif defined(MACINTOSH)
#define GP142_FUNC
#elif defined(X11R6)
#define GP142_FUNC
#endif

/* Don't use assembly instructions if we can avoid it. */
#define USE_ASM_FOR_TIMER 0


/************************************************************* global variables ****/
/* for double buffering.  Redraw if true - josh */
static int need_redraw = 1;

#ifdef MACINTOSH

#if USE_ASM_FOR_TIMER
typedef struct {
    TMTask atmTask;
    long tmWakeUp;
    long tmReserved;
    long tmRefCon;
} TMInfo, *TMInfoPtr;

TMInfo gMyTMInfo;
#endif

Rect dragRect = { 0, 0, 1024, 1024 };
Rect winrect = { 50, 20, 50+2*GP142_YMAX+1, 20+2*GP142_XMAX+1 };

RGBColor gRGBColors[MAX_COLORS] = {
    /* Black used to be 0x1000, 0x1000, 0x1000.  Why??? */
    { 0x0000, 0x0000, 0x0000 },         /* black */
    { 0xFFFF, 0xFFFF, 0xFFFF },         /* white */
    { 0xFFFF, 0x0000, 0x0000 },         /* red */
    { 0x0000, 0xFFFF, 0x0000 },         /* green */
    { 0x0000, 0x0000, 0xFFFF },         /* blue */
    { 0xFFFF, 0xFFFF, 0x0000 },         /* yellow */
    { 0xFFFF, 0x0000, 0xFFFF },         /* magenta */
    { 0x0000, 0xFFFF, 0xFFFF },         /* cyan */  
    { 0x9999, 0x0000, 0xCCCC },         /* purple */
    { 0x0000, 0x3333, 0x9999 },         /* navy blue */
    { 0x9999, 0x6666, 0x9999 },         /* dusty plum */
    { 0x9999, 0xFFFF, 0xFFFF },         /* ice blue */
    { 0x9999, 0xFFFF, 0xCCCC },         /* turquoise */
    { 0xFFFF, 0x6666, 0x0000 },         /* orange */
    { 0x9999, 0x6666, 0x3333 },         /* brown */
    { 0xFFFF, 0x9999, 0xCCCC },         /* pink */
    { 0xFFFF, 0xFFFF, 0x9999 },         /* chalk */
    { 0xCCCC, 0x9999, 0x3333 },         /* gold */
    { 0xFFFF, 0x9999, 0x6666 },         /* peach */
    { 0x0000, 0x6666, 0x3333 },         /* forest green */
    { 0x3333, 0xCCCC, 0x9999 },         /* sea green */
    { 0x9999, 0x9999, 0x3333 },         /* olive */
    { 0x8000, 0x8000, 0x8000 },         /* 50% gray */
    { 0xCCCC, 0xCCCC, 0xCCCC }          /* 20% gray -- 80% white */
};

enum {
    mAniRun = 1,
    mAniHalt,
    mAniSingle,
    mLog = 5,
    mScriptRecord = 7,
    mScriptPlay,
    mScriptOne,
    mQuit = 11};

char Menu_String[] = "\p"
        "Animate/A;"
        "Halt animation/H;"
        "Advance one frame/F;"
        "(-;"
        "Logging/L;"
        "(-;"
        "Record   " kScriptName "/R;"
        "Playback " kScriptName "/P;"
        "Playback one event/O;"
        "(-;"
        "Quit/Q;"
        "(-;"
        "(GP142 v" GP142_VERSION " " GP142_DATE ";"
        "(mckenzie@cs.washington.edu;"
        "(corin@cs.washington.edu;"
        "(casey@cs.washington.edu"
    ;   

MenuHandle RunMenu, DeskMenu;
CWindowPtr gpWin = (CWindowPtr) 0;

/* The offscreen GWorld where the GP142 graphics are rendered. */
GWorldPtr gGP142World = NULL;

char gColorFlag = 1;        /* true if the target Mac runs color Quickdraw */
PixPatHandle color_pp[MAX_COLORS];


int nrows = 32;
int ncols = 50;

#elif defined(WINDOWS)


/* Structure used to keep around variables we need for initialization, 
 * but the user shouldn't have to see.
 */
typedef struct  {
    HINSTANCE hInstance, hPrevInstance;
    LPSTR lpCmdLine;
    int nShowCmd;
} GP142Globals;

/* Only one item of type Global needs to exist.  */
static GP142Globals global;

/* We need to state that there exists a main() apriori.  */
void main();


HWND hDrawWnd = (HWND)NULL;     /* handles to 2 windows in application */
HWND hTextWnd = (HWND)NULL;  
HMENU hRunMenu;                 /* handle to menu */
HINSTANCE hInst;                /* Instance handle to this library */

/* need some stuff for double buffering - josh */
HBITMAP offscreen_bitmap;
HDC offscreen_DC, the_hdc;

/* Display context for text window */
HDC text_hdc;

/* Handle to ring buffer for debug statements.  We save the last 
MAX_CONOLE_LINES lines from the debuf window, so we can redraw them when
the text window receives a WM_PAINT message */
HANDLE gConsoleLines[MAX_CONSOLE_LINES];
int gRingFirst = -1; /* -1 indicates that the ring buffer is empty */
int gRingLast = 0;  /* last is the next available position */
#define RING_INC(i) (i = (i==MAX_CONSOLE_LINES-1)?0:i+1)

COLORREF gRGBColors[MAX_COLORS] = {
    RGB(0x00, 0x00, 0x00),      /* black */
    RGB(0xFF, 0xFF, 0xFF),      /* white */
    RGB(0xFF, 0x00, 0x00),      /* red */
    RGB(0x00, 0xFF, 0x00),      /* green */
    RGB(0x00, 0x00, 0xFF),      /* blue */
    RGB(0xFF, 0xFF, 0x00),      /* yellow */
    RGB(0xFF, 0x00, 0xFF),      /* magenta */
    RGB(0x00, 0xFF, 0xFF),      /* cyan */
    RGB(0x99, 0x00, 0xCC),      /* purple */
    RGB(0x00, 0x33, 0x99),      /* navy blue */
    RGB(0x99, 0x66, 0x99),      /* dusty plum */
    RGB(0x99, 0xFF, 0xFF),      /* ice blue */
    RGB(0x99, 0xFF, 0xCC),      /* turquoise */
    RGB(0xFF, 0x66, 0x00),      /* orange */
    RGB(0x99, 0x66, 0x33),      /* brown */
    RGB(0xFF, 0x99, 0xCC),      /* pink */
    RGB(0xFF, 0xFF, 0x99),      /* chalk */
    RGB(0xCC, 0x99, 0x33),      /* gold */
    RGB(0xFF, 0x99, 0x66),      /* peach */
    RGB(0x00, 0x66, 0x33),      /* forest green */
    RGB(0x33, 0xCC, 0x99),      /* sea green */
    RGB(0x99, 0x99, 0x33),      /* olive */
    RGB(0x80, 0x80, 0x80),      /* 50% gray */
    RGB(0xCC, 0xCC, 0xCC)       /* 20% gray -- 80% white */
};

#elif defined(X11R6)

#define MAX_FONTS 7

Display *display;
int screen;
char *prog_name;
Window window;
Window wincomm;
Window winc[8];
GC gc;
GC gccon;
FontDB* font_info;
FontDB* current_font;
XColor color_ids[MAX_COLORS];
int current_color_id;

/* for double-buffering - josh */
Pixmap offscreen_buffer;

RGBColor gRGBColors[MAX_COLORS] = {
    { 0x1000, 0x1000, 0x1000 },         /* black */
    { 0xFFFF, 0xFFFF, 0xFFFF },         /* white */
    { 0xFFFF, 0x0000, 0x0000 },         /* red */
    { 0x0000, 0xFFFF, 0x0000 },         /* green */
    { 0x0000, 0x0000, 0xFFFF },         /* blue */
    { 0xFFFF, 0xFFFF, 0x0000 },         /* yellow */
    { 0xFFFF, 0x0000, 0xFFFF },         /* magenta */
    { 0x0000, 0xFFFF, 0xFFFF },         /* cyan */  
    { 0x9999, 0x0000, 0xCCCC },         /* purple */
    { 0x0000, 0x3333, 0x9999 },         /* navy blue */
    { 0x9999, 0x6666, 0x9999 },         /* dusty plum */
    { 0x9999, 0xFFFF, 0xFFFF },         /* ice blue */
    { 0x9999, 0xFFFF, 0xCCCC },         /* turquoise */
    { 0xFFFF, 0x6666, 0x0000 },         /* orange */
    { 0x9999, 0x6666, 0x3333 },         /* brown */
    { 0xFFFF, 0x9999, 0xCCCC },         /* pink */
    { 0xFFFF, 0xFFFF, 0x9999 },         /* chalk */
    { 0xCCCC, 0x9999, 0x3333 },         /* gold */
    { 0xFFFF, 0x9999, 0x6666 },         /* peach */
    { 0x0000, 0x6666, 0x3333 },         /* forest green */
    { 0x3333, 0xCCCC, 0x9999 },         /* sea green */
    { 0x9999, 0x9999, 0x3333 },         /* olive */
    { 0x8000, 0x8000, 0x8000 },         /* 50% gray */
    { 0xCCCC, 0xCCCC, 0xCCCC }          /* 20% gray -- 80% white */
};

#endif

static char *gColorName[MAX_COLORS] = {
    "black",
    "white",
    "red",
    "green",
    "blue",
    "yellow",
    "magenta",
    "cyan",
    "purple",
    "navy blue",
    "dusty plum",
    "ice blue",
    "turquoise",
    "orange",
    "brown",
    "pink",
    "chalk",
    "gold",
    "peach",
    "forest green",
    "sea green",
    "olive",
    "50% gray",
    "20% gray"
};


static int gEventAction;
static GP142_event_t gEventRecord;

/* control flags */
static char gRunFlag;                   /* Running animation? */
static char gSingleStepFlag;            /* Single stepping animation? */
static char gDoneFlag;                  /* Program concluded? */
static char gLogging = LOG_ON;          /* Log actions to console? */
static char gRecordingFlag = FALSE;     /* Recording user actions for later playback? */
static char gScriptStepFlag = FALSE;    /* Playback one action? */
static char gScriptPlayFlag = FALSE;    /* Continuously playback actions? */
static int  gAnimExpired = FALSE;

/* scripting */
static FILE *gScriptFP = NULL;  /* file pointer to script file (in or out); NULL if not open */
static int gTaskCount = 0;      /* number of consecutive calls to GP142_user_task */

static int gXCenter, gYCenter;


/********************************************************* Library Initialization ***/
#ifdef MACINTOSH

#if USE_ASM_FOR_TIMER

#ifndef __MWERKS__

void timerFlagProc(void)
{
    long oldA5;
    TMInfoPtr recPtr;
    
    asm {                               /* The time manager puts the address */
        move.l a1, recPtr               /* of the expired timer in register a1*/ 
    }

    oldA5 = SetA5(recPtr->tmRefCon);    /* This is so we can touch the global */
                                        /* variables of GP142 app*/

    gAnimExpired = TRUE;

    oldA5 = SetA5(oldA5);               /* Change global variable start address */
                                        /* back to what it was*/
    
    PrimeTime((QElemPtr)recPtr, TIME_PER_STEP); /* Reprime the timer for another */
                                                /* .1 seconds */
}

#else /* __MWERKS__ */

/* 
** Metrowerks supports asm only for entire functions.
** This func is equiv to the preceding one:
**    Save A5; restore GP142's A5 from timer record;
**    set global flag; restore A5; requeue timer record.
** WLR 2/96.  Thanks to MAC.
*/
static asm void timerFlagProc(void)
{
    move.l A5, A0
    move.l struct(TMInfo_s.tmRefCon)(A1), A5
    move.w #1, gAnimExpired
    move.l A0, A5
    move.l A1, A0
    move.l #TIME_PER_STEP, D0
    _PrimeTime
    rts
}
#endif

#endif /* USE_ASM_FOR_TIMER */

extern int GP142_open(void)  /* was GP142_main() in GP142 v1.x */
{
    int console_flag =          /* 0 for either defers opening          */
        nrows!=0 && ncols!=0 ;  /*   console, but leaves default size.  */

    ToolboxInit();              /* Initialize the Mac toolbox */
#ifdef __MWERKS__
    if (nrows) SIOUXSettings.rows   = nrows;
    if (ncols) SIOUXSettings.columns= ncols;
    SIOUXSettings.initializeTB      = 0;    /*  Do we initialize the ToolBox ... */
    SIOUXSettings.setupmenus        = 0;    /*  Do we draw the SIOUX menus ...  */
    SIOUXSettings.autocloseonquit   = 1;    /*  Do we close the SIOUX window on program termination ... */
    SIOUXSettings.asktosaveonclose  = 0;    /*  Do we offer to save on a close ... */
    SIOUXSettings.toppixel          = 40;   /*  The topleft window position (in pixels) */
    SIOUXSettings.leftpixel         = 2;    /*      (0,0 centers on main screen) ...    */
#else
    if (nrows) console_options.nrows = nrows;
    if (ncols) console_options.ncols = ncols;
#endif
    if ( console_flag ) {   /* don't open console unnecessarily */
        printf("GP142 graphics package version " GP142_VERSION " (" GP142_DATE ")\n");
        printf("This is the console window\n");
        if (!gColorFlag) {
            printf("This Macintosh does not have Color Quickdraw.\n");
            printf("All objects will be drawn using black.\n");
        }
    }
    

/*Here we initialize a timer, add it to the queue, and prime it*/        
#if USE_ASM_FOR_TIMER
    gMyTMInfo.atmTask.tmAddr = (TimerUPP)timerFlagProc;
    gMyTMInfo.tmRefCon = SetCurrentA5();        /* This is so we can access */
                                                /* the Global variables later */
    gMyTMInfo.tmWakeUp = 0;
    gMyTMInfo.tmReserved = 0;
    InsTime((QElemPtr)&gMyTMInfo);
    PrimeTime((QElemPtr)&gMyTMInfo, TIME_PER_STEP);
#endif

    SelectWindow((void *)gpWin);   /* Better to do it once here than every time */
                                   /* through the event loop   -dia */
    return GP142_SUCCESS;
} 

/* Initialize Mac stuff */
static void ToolboxInit(void)
{
    int i;
    long myFeature;
    Rect r;
    
#if USES_NEW_HEADERS
    InitGraf(&qd.thePort);
#else
    InitGraf(&thePort);
#endif
    InitFonts();
    InitWindows();
    InitCursor();
    InitDialogs(0);
    TEInit();
    InitMenus();
    FlushEvents( everyEvent, 0 );

    /* Desk Accessory menu */
    DeskMenu = NewMenu(Desk_ID,"\p\024");
#if USES_NEW_HEADERS
    AppendResMenu(DeskMenu, 'DRVR');
#else
    AddResMenu(DeskMenu, 'DRVR');
#endif
    InsertMenu(DeskMenu, 0);
    
    /* Run menu */
    RunMenu = NewMenu(Run_ID, "\pRun");
    AppendMenu(RunMenu, (ConstStr255Param)Menu_String);
    InsertMenu(RunMenu, 0);
    CheckItem(RunMenu, 4, (int)gLogging);
    
    /* Let's see if we can use COLOR */
    Gestalt(gestaltQuickdrawVersion, &myFeature);
    if (myFeature < gestalt8BitQD) {
        gColorFlag = 0;
    }
    
    /* Create the window */
    DrawMenuBar();
    if (gColorFlag)
        gpWin = (CWindowPtr) NewCWindow(0,&winrect,"\pGP142 Graphics Window",
            1,0,(void *)(-1),1,0);
    else
        gpWin = (CWindowPtr) NewWindow(0,&winrect,"\pGP142 Graphics Window",
            1,0,(void *)(-1),1,0);
    
    gRunFlag = 0;
    gDoneFlag = 0;
    gSingleStepFlag = 0;
    
    /* Make some colors */
    if (gColorFlag) {
        for (i=0; i<MAX_COLORS; i++) {
            color_pp[i] = NewPixPat();
                MakeRGBPat(color_pp[i], &gRGBColors[i]);
        }
    }
    
    /* Find the offset to the center of the window */
    gXCenter = (winrect.right - winrect.left) >> 1;
    gYCenter = (winrect.bottom - winrect.top) >> 1;
    
    /* Create the offscreen GWorld into which we will render out GP142
       objects */
    SetRect(&r, 0, 0, 2*GP142_XMAX+1, 2*GP142_YMAX+1);
    if (noErr != NewGWorld(&gGP142World,    /* The returned offscreen world */
                8,                          /* bits per pixel */
                &r,                         /* size of buffer */
                nil,                        /* Color table.  Use the default. */
                nil,                        /* I forget why this is nil... */
                0)) {                       /* Don't need any flags */
        SysBeep(10);
        ExitToShell();
        return;
    }
}

#elif defined(WINDOWS)            

/* 
 * Hide the four global variables from the user, permitting them to simply
 * define a main() function.  (idea by Shuichi Koga, implemented by Dan Boren).
 */
PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    global.hInstance = hInstance;
    global.hPrevInstance = hPrevInstance;
    global.lpCmdLine = lpCmdLine;
    global.nShowCmd = nShowCmd;

    main();
}


void   _GP142_pseudocall(void)
{
    int a,x,y;
    char c='a';
    GP142_point p = {0,0};
    GP142_event_t  t = {0, 0, 0};
    x = y =a = 0;
    if (a*a)      /* we won't actually call these functions
                     a trick to get rid of compiler warnings */
    {
        GP142_clear();
        GP142_undo();
        GP142_logging(LOG_OFF);
        GP142_animate(ANI_HALT);
        GP142_gets(NULL,NULL);
        GP142_pixelXY(0,0,0);
        GP142_lineXY(0,0,0,0,0,0);
        GP142_rectangleXY(0,0,0,0,0,0);
        GP142_triangleXY(0,0,0,0,0,0,0,0);
        GP142_ovalXY(0,0,0,0,0,0);
        GP142_circleXY(0,0,0,0);
        GP142_printfXY(0,0,0,0,NULL);
        GP142_textXY(0,0,0,0,NULL);
        GP142_await_eventP((GP142_event_t*)NULL);
        GP142_pixelP(0,p);
        GP142_lineP(0,p,p,0);
        GP142_rectangleP(0,p,p,0);
        GP142_triangleP(0,p,p,p,0);
        GP142_ovalP(0,p,p,0);
        GP142_circleP(0,p,0);
        GP142_printfP(0,p,0,NULL);
        GP142_textP(0,p,0,NULL);
        GP142_close();
        GP142_await_event(&x,&y,&c);
        PlayFromScript();
        CloseScript();
        SaveToScript(0,t);
    }
}

extern int GP142_FUNC GP142_open()
/*GP142_open(HANDLE hInstance, HANDLE hPrevInstance,
     LPSTR lpszCmdLine, int nCmdShow)*/


{
    WNDCLASS wc;
    int x, y;
    /* BOOL done = FALSE; */

     _GP142_pseudocall();  /* let the compiler think all
                              GP142 functions have been
                              called */
     UNUSED(global.lpCmdLine);

     /************ register window classes ****************/
     if (!global.hPrevInstance) /* initialize window classes when first run */
          {
                /* first, register the graphics window class */
                wc.hInstance = global.hInstance;
                wc.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
                wc.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
                wc.lpszMenuName = "generic";
                wc.style = CS_HREDRAW | CS_VREDRAW;
                wc.cbClsExtra = 0;
                wc.cbWndExtra = 0;
                wc.lpfnWndProc = (WNDPROC) DrawWndProc;
                wc.hbrBackground = CreateSolidBrush(gRGBColors[BKGND_COLOR]),
                wc.lpszClassName = "DrawWndClass";
                RegisterClass(&wc);

                /* now, register the text window, child of draw */
                wc.style = CS_HREDRAW | CS_VREDRAW;
                wc.lpfnWndProc = (WNDPROC)TextWndProc;
                wc.lpszClassName = "TextWndClass";
                RegisterClass(&wc);
          }


     /************* Initialize global variables *******************/
     x = GetSystemMetrics(SM_CXSCREEN);
     y = GetSystemMetrics(SM_CYSCREEN);
     gRunFlag = FALSE;
     gSingleStepFlag = FALSE;

     /************ Create windows ***************/
     /* Create our two windows: first graphics, then text */
     hDrawWnd = CreateWindow("DrawWndClass",
          "GP142 Graphics",                   /* Title of window */
          WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_BORDER, /* window style */
          0,                                  /* position in upper left */
          0,
          2*GP142_XMAX+1,                     /* pixels horz.*/
          2*GP142_YMAX+FUDGE,                 /* pixels vert.*/
          (HWND)NULL,                         /* draw has no parent */
          (HMENU)NULL,                        /* use class menu */
          global.hInstance,                   /* instance of program */
          NULL);                              /* NULL window data */

     hTextWnd = CreateWindow(
          "TextWndClass",                     /* window class name */
          "GP142 Text",                       /* Title of window */
          WS_OVERLAPPEDWINDOW,
          0,                                  /* all the way to the left */
          2*GP142_YMAX+FUDGE+10,              /* make it abut draw window */
          2*GP142_XMAX+1,/* x,*/              /* same width as draw window */
          y/4,                                /* 1/4 maximum height */
          (HWND)NULL,                         /* Text has no parent */
          (HMENU)NULL,                        /* no menu */
          global.hInstance,                   /* instance of program */
          NULL);                              /* NULL window data */

     hInst = global.hInstance;

     /* init the double-buffer windows - josh */
     the_hdc = GetDC(hDrawWnd);
     offscreen_bitmap = CreateCompatibleBitmap(the_hdc, 2*GP142_XMAX+1, 2*GP142_YMAX+FUDGE);
     offscreen_DC = CreateCompatibleDC(the_hdc);
     SelectObject (offscreen_DC, offscreen_bitmap);

     ShowWindow(hTextWnd, global.nShowCmd);
     ShowWindow(hDrawWnd, global.nShowCmd);

     SetTimer(hDrawWnd, 2, TIME_PER_STEP, NULL);

     return GP142_SUCCESS;
}

#elif defined(X11R6)

void create_GC(Window window, GC *gc, int fid) {

   XGCValues gc_val;

   *gc = XCreateGC(display, window, 0, &gc_val);
   XSetFont(display, *gc, fid);

   XSetForeground(display, *gc, color_ids[2].pixel);
   XSetLineAttributes(display, *gc, 3, LineSolid, CapRound, JoinRound);
   return;
}

extern int GP142_open(void) {

    char *win_name = "GP142 Graphics Window";
    char *win_name_comm = "GP142 Control Window";
    char *icon_name = "GP142";
    char *icon_name_comm = "GP142 Controls";
    char *display_name = NULL;
    int i;
    unsigned int border_width = 2;
    XSizeHints *size_hint;
    XWMHints *wm_hint;
    XClassHint *class_hint;
    XTextProperty WinNameComm, WinName, IconNameComm, IconName;
    Window dummy_win; 
    int dummy_x, dummy_y;
    unsigned int dummy_width, dummy_height, dummy_border, depth;
    prog_name = "GP142";
   
   if (!(size_hint = XAllocSizeHints()) || !(wm_hint = XAllocWMHints())
        || !(class_hint = XAllocClassHint())
        || (display = XOpenDisplay (display_name)) == NULL) {
      fprintf(stderr, "%s: Unable to open X display %s.\n", prog_name,
                                XDisplayName(display_name));
      exit(0);
   }

   screen = DefaultScreen(display);

   window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 
                10, GP142_XMAX*2, GP142_YMAX*2, border_width, 
                  BlackPixel(display, screen), WhitePixel(display, screen));
   wincomm = XCreateSimpleWindow(display, RootWindow(display, screen), 50, 
                    50, 200, 105, border_width, BlackPixel(display, screen), 
                                      WhitePixel(display, screen));
       /* double buffering - josh */
   XGetGeometry(display, window, &dummy_win, &dummy_x, &dummy_y, &dummy_width, &dummy_height,
                &dummy_border, &depth);
   offscreen_buffer = XCreatePixmap(display, window, GP142_XMAX*2, GP142_YMAX*2, depth);
   
   gXCenter = GP142_XMAX;
   gYCenter = GP142_YMAX;

/***TODO***/
   if (XStringListToTextProperty(&win_name, 1, &WinName) == 0) {
      fprintf(stderr, "\n%s: Ow.\n\n", prog_name);
      exit(0);
   }

   if (XStringListToTextProperty(&icon_name, 1, &IconName) == 0) {
      fprintf(stderr, "\n%s: Ow.\n\n", prog_name);
      exit(0);
   }

   if (XStringListToTextProperty(&win_name_comm, 1, &WinNameComm) == 0) {
      fprintf(stderr, "\n%s: Ow.\n\n", prog_name);
      exit(0);
   }

   if (XStringListToTextProperty(&icon_name_comm, 1, &IconNameComm) == 0) {
      fprintf(stderr, "\n%s: Ow.\n\n", prog_name);
      exit(0);
   }

   gRunFlag = 0;
   gDoneFlag = 0;
   gSingleStepFlag = 0;

   /* size hints to keep windows size from changing */ 

   size_hint -> flags = PSize | PPosition | PMinSize | PMaxSize;
   size_hint -> min_width = 600;
   size_hint -> min_height = 500;
   size_hint -> max_width = 600;
   size_hint -> max_height = 500;
   wm_hint -> flags = StateHint | InputHint;
   wm_hint -> input = True;
   wm_hint -> initial_state = NormalState;
   class_hint -> res_name = prog_name;
   class_hint -> res_class = prog_name;
   XSetWMProperties(display, window, &WinName, &IconName, 0, 0, 
                                        size_hint, wm_hint, class_hint);

   size_hint -> min_width = 200;
   size_hint -> min_height = 105;
   size_hint -> max_width = 200;
   size_hint -> max_height = 105;
   XSetWMProperties(display, wincomm, &WinNameComm, &IconNameComm, 0, 0, 
                                        size_hint, wm_hint, class_hint);

   XSelectInput(display, window, StructureNotifyMask | ExposureMask | 
       KeyPressMask | ButtonPressMask | EnterWindowMask | LeaveWindowMask); 
   XSelectInput(display, wincomm, StructureNotifyMask | ExposureMask | 
       KeyPressMask | ButtonPressMask | EnterWindowMask | LeaveWindowMask); 

   font_info = (FontDB*) malloc (sizeof(FontDB));
   if ((font_info == NULL) ||
       (font_info->thefont = XLoadQueryFont(display, 
                 "-adobe-times-medium-r-normal--0-150-75-75-p-0-iso8859-1"))
                                                == NULL) {
      fprintf(stderr, "Cannot open adobe-times scalable font.\n\n");
      exit(0);
   }
   font_info -> point_size = 15;
   font_info -> next = NULL;
   current_font = font_info;

   for (i = 0; i < MAX_COLORS; i++) {
        color_ids[i].red = gRGBColors[i].red;
        color_ids[i].green = gRGBColors[i].green;
        color_ids[i].blue = gRGBColors[i].blue;
        color_ids[i].flags = DoRed | DoGreen | DoBlue;
        XAllocColor(display, DefaultColormap(display, screen), &color_ids[i]);
   }

   current_color_id = 2;

   create_GC(window, &gc, font_info->thefont->fid);
   create_GC(window, &gccon, font_info->thefont->fid);
   XSetForeground(display, gccon, BlackPixel(display, screen));

   XMapWindow(display, window);
   XMapWindow(display, wincomm);

   for (i = 0; i < 8; i++) {
      winc[i] = XCreateSimpleWindow(display, wincomm, (i / 4) * 100,  
                       ((i % 4) * 25) + 5, 95, 20, 2, BlackPixel(display,
                                      screen), WhitePixel(display, screen));
      XSelectInput(display, winc[i], StructureNotifyMask | ExposureMask | 
          KeyPressMask | ButtonPressMask | EnterWindowMask | LeaveWindowMask); 
      XMapWindow(display,winc[i]);
   }

   /* We must be open and waiting for drawing commands at this
    * point.  However, X does not guarantee this until we receive the first
    * XExpose event
    */

   while(1)
      {
      XEvent event;
      XNextEvent(display, &event);
      if(event.type == Expose)
         if (event.xany.window == window)
            break;
         else
            Process_event(event);
      }

   return GP142_SUCCESS;
}
#endif 


/************************************************************** Library Closure ***/
#ifdef MACINTOSH
extern int GP142_close(void)
{
#if USE_ASM_FOR_TIMER
    /* Remove the timer entry from the queue*/
    RmvTime((QElemPtr)&gMyTMInfo);
#endif

    /* Is there anything we should do here? */
    CloseScript();

    return GP142_SUCCESS;
}

#elif defined (WINDOWS)
/* Windows Exit Procedure */
int FAR PASCAL EXPORT WEP (int nParameter)
{
    UNUSED(nParameter);
    return (1);
}

extern int GP142_FUNC 
GP142_close(void)
{
    /* Free the memory used by our offscreen graphics world */
    ReleaseDC(hDrawWnd, the_hdc);    
    CloseScript();
                         
    return GP142_SUCCESS;
}

#elif defined(X11R6)

extern int GP142_close(void) {

   CloseScript();
   while (font_info) {
      FontDB* temp;
      XUnloadFont(display, font_info -> thefont -> fid);
      temp = font_info;
      font_info = font_info -> next;
      free(temp); /* no need to free memory at the end of the program
                   * but do it anyway */
   }

   XFreeGC(display, gc);
   XCloseDisplay(display);

   return GP142_SUCCESS;

}

#endif



/******************************************************* Event Handling ***/
/*  Concept:  Students will call GP142_await_event() in their own event loop, 
    and handle the returned value accordingly.  Possible return values are 
    GP142_MOUSE, GP142_KBD, GP142_SK, and GP142_QUIT */

/*********************************************************** GP142_await_event()
*/
extern int GP142_FUNC
GP142_await_event(int *x, int *y, char *c)
{
    GP142_event_t e;
    int a;
    
    a = GP142_await_eventP(&e);

    *x = e.x;
    *y = e.y;
    *c = e.c;
    
    return a;
}

extern int GP142_FUNC
GP142_await_eventP(GP142_event_t *e)
{
     int eventCounter;
#ifdef WINDOWS
     BOOL done = FALSE;
#endif

     /*  GP142_await_event() should return only with a message that student
          might want to handle.  That is, only with mouse, keyboard,
          idle, or quit messages.  If we're in animiate mode, we'll pass
          an idle event after handleing MAX_EVENTS events (or if some
          user interaction occurs).  Otherwise, we won't return until the
          user does some action. */

     gEventAction = GP142_NONE;
     gEventRecord.x = gEventRecord.y = gEventRecord.c = 0;

     eventCounter = 0;
     while ( gEventAction == GP142_NONE ||
            (gEventAction == GP142_PERIODIC && gAnimExpired == FALSE))
          {
                eventCounter = 1;
                YieldToSystem();

                /* If we're reading from a script file, don't honor user's actions;
                obey the script instead */
                if (gScriptStepFlag || gScriptPlayFlag)
                     {
                          gScriptStepFlag = FALSE;
                          /* This will fill in global data */
                          if (PlayFromScript() == GP142_SUCCESS)
                                break;
                          else
                                {
                                     gScriptStepFlag = FALSE;
                                     gScriptPlayFlag = FALSE;
                                }
                     }

                /* Only pass back a GP142_PERIODIC if we're animating, or
                single stepping */
                if ((gSingleStepFlag || gRunFlag) && gEventAction == GP142_NONE)
                     {
                          gEventAction = GP142_PERIODIC;
                          gAnimExpired = FALSE;
                          gSingleStepFlag = FALSE;
                          gScriptStepFlag = FALSE;
                     }

          }

     /* Also, if we're recording to a script, we'll want to save the information */
     if (gRecordingFlag)
          {
                if (gEventAction == GP142_PERIODIC)
                     gTaskCount++;
                else
                     {
                          if (gTaskCount > 0)
                                {
                                     SaveToScript(GP142_PERIODIC, gEventRecord);
                                     gTaskCount = 0;
                                }
                          SaveToScript(gEventAction, gEventRecord);
                     }
          }

     *e = gEventRecord;
/*   UNUSED(done);  // there should be a reason we declared
                         // done and eventCounter, just leave them here. */
     UNUSED(eventCounter);
     return gDoneFlag?GP142_QUIT:gEventAction;
}

static void YieldToSystem(void)
{    
#ifdef MACINTOSH
     EventRecord event;
#elif defined(WINDOWS)
     MSG msg;
     BOOL done = FALSE;
#elif defined(X11R6)
     XEvent event;
#endif

/*   UNUSED(done); */
#ifdef MACINTOSH
#if !USE_ASM_FOR_TIMER      /* This stuff was moved out of HandleMessage to fix bug */
    UnsignedWide now;       /* concerning autoKey event stopping animation  -dia */
    static UnsignedWide lastExpired = {0,0};
    unsigned long delta_microseconds;
    
    /* Has it been long enough since the last animation step? */
    Microseconds(&now);
    
    /* Calculate how many microseconds have elapsed since the last time 
    we set the gAnimExpired flag. */
    if (lastExpired.hi == 0 && lastExpired.lo == 0) {
        lastExpired = now;
        gAnimExpired = TRUE;
    } else if (now.hi == lastExpired.hi) {
        delta_microseconds = now.lo - lastExpired.lo;
    } else if (now.hi == lastExpired.hi + 1) {
        delta_microseconds = now.hi + ((unsigned long)(-1) - lastExpired.lo);
    } else {
        /* It's been a _really_ long time since the last timer overflow. */
        delta_microseconds = (unsigned long)(-1);
    }
    
    /* !!! The 840 number here is kinda a kludge.  TIME_PER_STEP represents
        the number of milliseconds between animation steps.  Thus, we should
        multiply TIME_PER_STEP by 1000 to determine the number of microseconds
        between steps.  However, I found that doing so didn't give the same time 
        delay between animation steps as did the original Mac code.  So 
        840 is used, which is pretty close. */
    if (delta_microseconds > TIME_PER_STEP * 840) {
        gAnimExpired = TRUE;
        lastExpired = now;
    }
#endif
/*   SelectWindow((void *)gpWin);
     GetNextEvent(everyEvent, &event);
     SystemTask();*/
     if ((!gSingleStepFlag && !gRunFlag) || !gAnimExpired)
     {
         WaitNextEvent(everyEvent, &event, 1, 0);   /* Use WaitNextEvent  -dia */
         HandleMessage(&event);
     }
#elif defined(WINDOWS)
     /*found_message = PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE);*/
     /* GetMessage() returns 0 if a WM_QUIT message was received */
     if (!GetMessage(&msg, (HWND)NULL, 0, 0)) 
     {
        gEventAction = GP142_QUIT;
        return;
     } else {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
     }
     if (need_redraw) {
         BitBlt (the_hdc,0,0,2*GP142_XMAX+1, 2*GP142_YMAX+FUDGE,
             offscreen_DC,0,0,SRCCOPY);
         need_redraw = 0;
     }
#elif defined(X11R6)
     
     if (XPending(display)) {
         XNextEvent(display, &event);
         Process_event(event);
     }
     if (need_redraw) {
         XCopyArea(display, offscreen_buffer, window, gc, 0, 0, GP142_XMAX*2, GP142_YMAX*2, 0, 0);
         XFlush(display);
         need_redraw = 0;
     }
   else {
        usleep(30000);
    gAnimExpired = TRUE;
   }

#endif

}

#ifdef MACINTOSH
static void HandleMessage(EventRecord *event)
{
    short windowcode;
    CWindowPtr mouseWindow;
    int c;
    int console_flag =          /* 0 for either defers opening          */
        nrows!=0 && ncols!=0 ;  /*   console, but leaves default size.  */

#ifdef __MWERKS__
    /* If we're using the SIOUX console, let it potentially handle an event */
    if (SIOUXHandleOneEvent(event))
        return;
#endif 

    switch ( event->what )
        {
            case keyDown:
                if ((event->modifiers & cmdKey))
                    {
                        DoMenu(MenuKey(event->message));
                        break;
                    }
            case autoKey:
                c = event->message & 0x7f;
                if (FrontWindow() == (GrafPtr)gpWin) {
                    gEventAction = GP142_KBD;
                    gEventRecord.c = c;
                }
                break;    

            case mouseDown:
                windowcode = FindWindow(event->where, (void *)&mouseWindow);
                switch ( windowcode )
                    {
                        case inMenuBar:
                            DoMenu(MenuSelect(event->where));
                            break;
                    
                        case inSysWindow:
                            SystemClick(event, (void *)mouseWindow);
                            break;
                    
                        case inGoAway:
                            if (TrackGoAway((void *)mouseWindow, event->where))
                                gEventAction = GP142_QUIT;
                            break;
                    
                        case inDrag:
                            DragWindow( (void *)mouseWindow, 
                                    event->where, &dragRect);
                            break;
                    
                        case inGrow:
                        case inContent:
                            if (mouseWindow != (CWindowPtr) FrontWindow())
                                {
                                    SelectWindow((void *)mouseWindow);
                                    WaitMouseUp();
                                }
                            else
                                {
                                    DoMouseClick(event, mouseWindow);
                                }
                            break;
                    }
            break;
        
            case activateEvt:
                break;
        
            case updateEvt:
                BeginUpdate((void *)gpWin);
                refresh(gpWin);
                EndUpdate((void *)gpWin);
                break;
            
            default:
                
                if (need_redraw)
                    refresh(gpWin);
                break;
        }
}


static void refresh(CWindowPtr w)
{
    CGrafPtr saveport;
    PixMapHandle pixmap;


    GetPort((void *) &saveport);
    SetPort((void *) w);

    pixmap = GetGWorldPixMap(gGP142World);
    LockPixels(pixmap);
    CopyBits((BitMap *)*pixmap, &((WindowPtr)w)->portBits, 
                &(*pixmap)->bounds, &w->portRect, srcCopy, nil);
    UnlockPixels(pixmap);

    SetPort((void *)saveport);

    need_redraw = 0;
}

/* react to user input */
static void DoMenu(long menuresult)
{ 
    short menuID, itemNumber;
    Str255 AccessoryName;

    menuID = HiWord(menuresult);
    itemNumber = menuresult;
    
    switch ( menuID ) {
    case Desk_ID:   
#if USES_NEW_HEADERS
        GetMenuItemText(DeskMenu, itemNumber, (void *)&AccessoryName);
#else
        GetItem(DeskMenu, itemNumber, (void *)&AccessoryName);
#endif
        OpenDeskAcc((void *)&AccessoryName);
        EnableItem(RunMenu, 0);
        DrawMenuBar();
        break;
    
    case Run_ID:
        switch ( itemNumber ) {
        case mAniRun:           /* run */
            gRunFlag = TRUE;
            break;
            
        case mAniHalt:          /* halt */
            gSingleStepFlag = FALSE;
            gRunFlag = FALSE;
            break;
            
        case mAniSingle:        /* single step */
            gSingleStepFlag = TRUE;
            break;
            
        case mLog:              /* logging */
            gLogging = !gLogging;
            CheckItem(RunMenu, mLog, (int)gLogging);
            break;
            
        case mScriptRecord:     /* record actions */
            gRecordingFlag = !gRecordingFlag;
            CheckItem(RunMenu, mScriptRecord, (int)gRecordingFlag);
            if (!gRecordingFlag)
                {
                    if (gTaskCount > 0)
                        SaveToScript(GP142_PERIODIC, gEventRecord);
                    CloseScript();
                }
            break;
            
        case mScriptPlay:       /* playback actions */
            gScriptPlayFlag = !gScriptPlayFlag;
            CheckItem(RunMenu, mScriptPlay, (int)gScriptPlayFlag);
            gRunFlag = FALSE;
            gSingleStepFlag = FALSE;
            break;
            
        case mScriptOne:        /* playback one action */
            gRunFlag = FALSE;
            gSingleStepFlag = FALSE;
            gScriptStepFlag = TRUE;
            break;
            
        case mQuit:             /* quit */
            gEventAction = GP142_QUIT;
            break;
            
        default:
            SysBeep(1);
            break;
            
        }   /* end switch (itemNumber) */
        break;
    }   /* end switch (menuID) */
    HiliteMenu(0);
}


static void DoMouseClick(EventRecord *the_event, CWindowPtr theWin)
{
    Point newPt;
    CGrafPtr saveport;

    UNUSED(the_event);

    /* If the user clicked in the console window, just ignore it */
    if (theWin != gpWin)
        return;

    GetPort((void *)&saveport);
    SetPort((void *)theWin);
    GetMouse(&newPt);   

    gEventAction = GP142_MOUSE;
    gEventRecord.x = newPt.h - gXCenter;
    gEventRecord.y = gYCenter - newPt.v;
    
    SetPort((void *)saveport);
}

#elif defined(WINDOWS)

#ifdef WIN32
long FAR PASCAL DrawWndProc(HWND hWnd, UINT message,
                            WPARAM wParam, LPARAM lParam)
#else
long FAR PASCAL DrawWndProc(HWND hWnd, WORD message,
                            WORD wParam, LONG lParam)
#endif
{
#ifndef WIN32
     HANDLE hInstance;
#endif
     RECT rClient;
     PAINTSTRUCT ps;
     HMENU hMenu;
     static BOOL bCtrlDown = FALSE;
     
     int click_x, click_y;

     switch(message)
          {
                case WM_CREATE:
/* Shuichi: Why do this? Not used anywhere */
#ifndef WIN32
                     /* get a handle to the instance handle of the window */
                     hInstance = (HANDLE)GetWindowWord(hWnd, GWW_HINSTANCE);
#endif
                     /* Slap the menu on to the window */
                     /* In windows, the menu bar is considered to be a 'menu'
                     and all pull-down things are popup menus.  */
                     hMenu = CreateMenu();
                     hRunMenu = CreatePopupMenu();
                     AppendMenu(hRunMenu,
                          MF_ENABLED | MF_STRING | MF_UNCHECKED,  /* menu format */
                          IDM_ANIMATE, "&Animate\tCtrl+A");
                     AppendMenu(hRunMenu,
                          MF_ENABLED | MF_STRING | MF_UNCHECKED,
                          IDM_HALT, "&Halt animation\tCtrl+H");
                     AppendMenu(hRunMenu,
                          MF_ENABLED | MF_STRING | MF_UNCHECKED,
                          IDM_ADVANCE_ONE, "Advance one &frame\tCtrl+F");

                     AppendMenu(hRunMenu, MF_SEPARATOR, 0, NULL);

                     /* Logging is initially TRUE */
                     AppendMenu(hRunMenu,
                          MF_ENABLED | MF_STRING | MF_CHECKED,
                          IDM_LOGGING, "&Logging\tCtrl+L");

                     AppendMenu(hRunMenu, MF_SEPARATOR, 0, NULL);

                     AppendMenu(hRunMenu,
                          MF_ENABLED | MF_STRING | MF_UNCHECKED,
                          IDM_RECORD_SCRIPT, "&Record Script\tCtrl+R");
                     AppendMenu(hRunMenu,
                          MF_ENABLED | MF_STRING | MF_UNCHECKED,
                          IDM_PLAY_SCRIPT, "&Playback Script\tCtrl+P");
                     AppendMenu(hRunMenu,
                          MF_ENABLED | MF_STRING | MF_UNCHECKED,
                          IDM_STEP_SCRIPT, "Play &One Script\tCtrl+O");

                     AppendMenu(hRunMenu, MF_SEPARATOR, 0, NULL);

                     AppendMenu(hRunMenu,
                          MF_ENABLED | MF_STRING | MF_UNCHECKED,
                          IDM_QUIT, "&Quit\tCtrl+Q");

                     AppendMenu(hRunMenu, MF_SEPARATOR, 0, NULL);

                     AppendMenu(hRunMenu,
                          MF_STRING | MF_UNCHECKED | MF_GRAYED,
                          IDM_ABOUT, "GP142 v" GP142_VERSION " " GP142_DATE);
                     AppendMenu(hRunMenu,
                          MF_STRING | MF_UNCHECKED | MF_GRAYED,
                          IDM_ABOUT, "MAC: mckenzie@cs.washington.edu");
                     AppendMenu(hRunMenu,
                          MF_STRING | MF_UNCHECKED | MF_GRAYED,
                          IDM_ABOUT, "WINDOWS: corin@cs.washington.edu");
                     AppendMenu(hRunMenu,
                          MF_STRING | MF_UNCHECKED | MF_GRAYED,
                          IDM_ABOUT, "UPDATES: casey@cs.washington.edu");

                     AppendMenu(hMenu,
                          MF_ENABLED | MF_POPUP | MF_UNCHECKED,
                          (UINT)hRunMenu, "&Run");
                     SetMenu(hWnd, hMenu);
                     DrawMenuBar(hWnd);
                     return 0;


                case WM_LBUTTONDOWN:
                     /* the user has clicked the left button on the window */
                     click_x = LOWORD(lParam) - gXCenter;
                     click_y = gYCenter - HIWORD(lParam);

                     /* For the program to link, the user must have this
                     function defined in their module, even if it is an
                     empty definition */
                     gEventAction = GP142_MOUSE;
                     gEventRecord.x = click_x;
                     gEventRecord.y = click_y;
                     return 0;

                case WM_PAINT:
                     BeginPaint(hWnd, &ps);
                /* we'll need to do an offscreen blit here.
                   - josh */
                     BitBlt (the_hdc,0,0,2*GP142_XMAX+1, 2*GP142_YMAX+FUDGE,
                         offscreen_DC,0,0,SRCCOPY);
                     EndPaint(hWnd, &ps);
                     need_redraw = 0;
                     return 0;


                case WM_KEYDOWN:    /* do things like CTRL-xx shortcuts */
                     switch(wParam)
                          {
                                case VK_CONTROL:
                                     bCtrlDown = TRUE;
                                     break;

                                case 'H':
                                case 'h':
                                     if (bCtrlDown == TRUE)
                                          gRunFlag = FALSE;
                                     break;

                                case 'A':
                                case 'a':
                                     if (bCtrlDown == TRUE)
                                          gRunFlag = TRUE;
                                     break;

                                case 'F':
                                case 'f':
                                     if (bCtrlDown == TRUE)
                                          {
                                                gRunFlag = FALSE;
                                                gSingleStepFlag = TRUE;
                                          }
                                     break;

                                case 'L':
                                case 'l':
                                     if (bCtrlDown && gLogging)
                                          {
                                                gLogging = LOG_OFF;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_LOGGING,
                                                     MF_BYCOMMAND | MF_UNCHECKED);
                                          }
                                     else if (bCtrlDown && !gLogging)
                                          {
                                                gLogging = LOG_ON;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_LOGGING,
                                                     MF_BYCOMMAND | MF_CHECKED);
                                          }
                                     break;


                                case 'R':
                                case 'r':
                                     if (bCtrlDown && gRecordingFlag)
                                          {
                                                gRecordingFlag = FALSE;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_RECORD_SCRIPT,
                                                     MF_BYCOMMAND | MF_UNCHECKED);
                                                if (gTaskCount > 0)
                                                     SaveToScript(GP142_PERIODIC, gEventRecord);
                                                CloseScript();
                                          }
                                     else if (bCtrlDown && !gRecordingFlag)
                                          {
                                                gRecordingFlag = TRUE;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_RECORD_SCRIPT,
                                                     MF_BYCOMMAND | MF_CHECKED);
                                          }
                                     break;

                                case 'P':
                                case 'p':
                                     if (bCtrlDown && gScriptPlayFlag)
                                          {
                                                gScriptPlayFlag = FALSE;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_PLAY_SCRIPT,
                                                     MF_BYCOMMAND | MF_UNCHECKED);
                                                CloseScript();
                                          }
                                     else if (bCtrlDown && !gScriptPlayFlag)
                                          {
                                                gRunFlag = FALSE;
                                                gSingleStepFlag = FALSE;
                                                gScriptPlayFlag = TRUE;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_PLAY_SCRIPT,
                                                     MF_BYCOMMAND | MF_CHECKED);
                                          }
                                     break;

                                case 'O':
                                case 'o':
                                     if (bCtrlDown)
                                          {
                                                gScriptStepFlag = TRUE;
                                                gRunFlag = FALSE;
                                                gSingleStepFlag = FALSE;
                                          }
                                     break;

                                case 'Q':
                                case 'q':
                                     if (bCtrlDown == TRUE)
                                          PostQuitMessage(0);
                                     break;
                          }
                     break;

                case WM_CHAR:
                     /* call the user's keyboard handler */
                     if (bCtrlDown == TRUE)
                          break;

                     gEventAction = GP142_KBD;
                     gEventRecord.c = (char)wParam;
                     break;


                case WM_KEYUP:
                     switch (wParam)
                          {
                                case VK_CONTROL:
                                     bCtrlDown = FALSE;
                                     break;
                          }
                     break;



                case WM_COMMAND:    /* menu item selected */
                     switch (wParam)
                          {
                                case IDM_ANIMATE:
                                     gRunFlag = TRUE;
                                     break;

                                case IDM_HALT:
                                     gRunFlag = FALSE;
                                     break;

                                case IDM_ADVANCE_ONE:
                                     gRunFlag = FALSE;
                                     gSingleStepFlag = TRUE;
                                     break;

                                case IDM_LOGGING:
                                    /* Changed TRUE/FALSE to LOG_ON/LOG_OFF */
                                     if (gLogging == LOG_ON)
                                          {
                                                gLogging = LOG_OFF;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_LOGGING,
                                                     MF_BYCOMMAND | MF_UNCHECKED);
                                          }
                                     else
                                          {
                                                gLogging = LOG_ON;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_LOGGING,
                                                     MF_BYCOMMAND | MF_CHECKED);
                                          }
                                     break;

                                case IDM_RECORD_SCRIPT:
                                     if (gRecordingFlag)
                                          {
                                                gRecordingFlag = FALSE;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_RECORD_SCRIPT,
                                                     MF_BYCOMMAND | MF_UNCHECKED);
                                                if (gTaskCount > 0)
                                                     SaveToScript(GP142_PERIODIC, gEventRecord);
                                                CloseScript();
                                          }
                                     else
                                          {
                                                gRecordingFlag = TRUE;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_RECORD_SCRIPT,
                                                     MF_BYCOMMAND | MF_CHECKED);
                                          }
                                     break;

                                case IDM_PLAY_SCRIPT:
                                     if (gScriptPlayFlag)
                                          {
                                                gScriptPlayFlag = FALSE;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_PLAY_SCRIPT,
                                                     MF_BYCOMMAND | MF_UNCHECKED);
                                                CloseScript();
                                          }
                                     else
                                          {
                                                gRunFlag = FALSE;
                                                gSingleStepFlag = FALSE;
                                                gScriptPlayFlag = TRUE;
                                                CheckMenuItem(hRunMenu,
                                                     IDM_PLAY_SCRIPT,
                                                     MF_BYCOMMAND | MF_CHECKED);
                                          }
                                     break;

                                case IDM_STEP_SCRIPT:
                                     gScriptStepFlag = TRUE;
                                     gRunFlag = FALSE;
                                     gSingleStepFlag = FALSE;
                                     break;

                                case IDM_QUIT:
                                     PostQuitMessage(0);
                                     break;
                          }
                     break;

                case WM_SIZE:   /* Graphics window's size has changed */
                     /*
                     ** Hmmm.. As of version 2.1, window size on both PC
                     ** and Mac should be immutable, so this code is
                     ** probably unnecessary, but I don't think it's
                     ** harmful, so I'll leave it in case we ever change
                     ** back to resizable windows.  --- WLR 10/95
                     */
                     GetClientRect(hWnd, &rClient);
                     gXCenter = (rClient.right - rClient.left)/2 +
                          rClient.left;
                     gYCenter = (rClient.bottom - rClient.top)/2 +
                          rClient.top;
                     break;

                case WM_TIMER:
                     gAnimExpired = TRUE;
                     break;

                case WM_DESTROY:
                case WM_QUIT:
                     KillTimer(hWnd, wParam);
                     PostQuitMessage(0);
                     return 0;

                default:
                     return (DefWindowProc(hWnd, message, wParam, lParam));
          }
#ifndef WIN32
     UNUSED(hInstance);
#endif
     return 0;
}


/****** TextWndProc() *******************************************/

#ifdef WIN32
long FAR PASCAL TextWndProc(HWND hWnd, UINT message,
                            WPARAM wParam, LPARAM lParam)
#else
long FAR PASCAL TextWndProc(HWND hWnd, WORD message,
                            WORD wParam, LONG lParam)
#endif
{

    /* Begin addition of Clear Window */
    switch (message)
        {
            /* if user selects a keyboard shortcut while the text window
            is active, send the keystroke to the graphics window */
            case WM_KEYDOWN:
                PostMessage(hDrawWnd,   /* send to graphics window */
                    WM_KEYDOWN,         /* message to send */
                    wParam,             /* send same paramaters */
                    lParam);
                break;    

            case WM_KEYUP:
                PostMessage(hDrawWnd, WM_KEYUP, wParam, lParam);
                break;

            case WM_PAINT:
                RedrawTextWnd(hWnd);
                return 0;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
        }

    return 0;
}
                                                                  

#elif defined(X11R6)

void Process_event(XEvent event) {
   if (event.xany.window == window) {
      switch(event.type) {
          int i;
          char keybuff[11];
          KeySym thekeysym;
          XComposeStatus compstat;
        case Expose:
          XCopyArea(display, offscreen_buffer, window, gc, 0, 0, GP142_XMAX*2, GP142_YMAX*2, 0, 0);
          XFlush(display);
          need_redraw = 0;
          break;
        case ButtonPress:
          gEventRecord.x = event.xbutton.x - GP142_XMAX;
          gEventRecord.y = GP142_YMAX - event.xbutton.y;
          gEventAction = GP142_MOUSE;
          break;
        case KeyPress:
          if (XLookupString((XKeyEvent*) &event, keybuff, 10, 
                            &thekeysym, &compstat) == 1) {
               if (thekeysym > 31 && thekeysym < 127) {
                  gEventRecord.c = thekeysym;
                  gEventAction = GP142_KBD;
                  }
               }
          break;
      }
   }
   if (event.xany.window == winc[0]) {
         switch (event.type) {
            case Expose:
               XDrawString(display, winc[0], gccon, 5, 15, "Animate", 7);
               break;
            case ButtonPress:
               gRunFlag=TRUE;
         }
   }
   if (event.xany.window == winc[1]) {
         switch (event.type) {
            case Expose:
               XDrawString(display, winc[1], gccon, 5, 15, "Stop", 4);
               break;
            case ButtonPress:
               gRunFlag=FALSE;
               gSingleStepFlag=FALSE;
         }
   }
   if (event.xany.window == winc[2]) {
         switch (event.type) {
            case Expose:
               XDrawString(display, winc[2], gccon, 5, 15, "SingleStep", 10);
               break;
            case ButtonPress:
               gSingleStepFlag=TRUE;
         }
   }
   if (event.xany.window == winc[3]) {
         switch (event.type) {
            case ButtonPress:
               gLogging=!gLogging;
               XClearWindow(display,winc[3]);
               /* drop through to redraw strings */
            case Expose:
               if (gLogging)
                  XDrawString(display, winc[3], gccon, 5, 15, "Logging on", 10);
               else
                  XDrawString(display, winc[3], gccon, 5, 15, "Logging off", 11);
               break;
         }
   }
   if (event.xany.window == winc[4]) {
         switch (event.type) {
            case ButtonPress:
               gRecordingFlag=!gRecordingFlag;
               XClearWindow(display,winc[4]);
               /* drop through to redraw strings */
            case Expose:
               if (gRecordingFlag)
                  XDrawString(display, winc[4], gccon, 5, 15, "Recording on", 12);
               else
                  XDrawString(display, winc[4], gccon, 5, 15, "Recording off", 13);
               break;
         }
   }
   if (event.xany.window == winc[5]) {
         switch (event.type) {
            case ButtonPress:
               gScriptPlayFlag=!gScriptPlayFlag;
               gRunFlag=FALSE;
               gSingleStepFlag=FALSE;
               XClearWindow(display,winc[5]);
               /* drop through to redraw strings */
            case Expose:
               if (gScriptPlayFlag)
                  XDrawString(display, winc[5], gccon, 5, 15, "Playback on", 11);
               else
                  XDrawString(display, winc[5], gccon, 5, 15, "Playback off", 12);
               break;
         }
   }
   if (event.xany.window == winc[6]) {
         switch (event.type) {
            case ButtonPress:
               gRunFlag = FALSE;
               gSingleStepFlag = FALSE;
               gScriptStepFlag = TRUE;
               break;
            case Expose:
               XDrawString(display, winc[6], gccon, 5, 15, "SingleScript", 12);
               break;
         }
   }
   if (event.xany.window == winc[7]) {
         switch (event.type) {
            case Expose:
               XDrawString(display, winc[7], gccon, 5, 15, "Quit", 4);
               break;
            case ButtonPress:
               gEventAction = GP142_QUIT;
         }
   }
}
#endif



/*********************************************************** Scripting Functions ***/
/*  ClearPlayFlag()
*/
static void ClearPlayFlag(void)
{
    gScriptPlayFlag = FALSE;
    gScriptStepFlag = FALSE;
    
#ifdef MACINTOSH
    CheckItem(RunMenu, mScriptPlay, FALSE);
#elif defined(WINDOWS)
    CheckMenuItem(hRunMenu,
    IDM_PLAY_SCRIPT,
    MF_BYCOMMAND | MF_UNCHECKED);
#elif defined(X11R6)
    XClearWindow(display,winc[5]);
    XDrawString(display, winc[5], gccon, 5, 15, "Playback off", 12);
#endif
}


/*  SaveToScript()
*/
static void 
SaveToScript(int a, GP142_event_t e)
{
    if (gScriptFP == NULL)
        if ((gScriptFP = fopen(kScriptName, "wt")) == NULL)
            {
                printf("Cannot open script file %s for writing\n", kScriptName);
                return;
            }
            
    switch (a)
        {
            case GP142_MOUSE:
                fprintf(gScriptFP, "GP142_MOUSE(%d, %d);\n", e.x, e.y);
                break;
                
            case GP142_KBD:
                fprintf(gScriptFP, "GP142_KBD(%d);\n", e.c);
                break;
                
            case GP142_PERIODIC:
                fprintf(gScriptFP, "GP142_PERIODIC(%d);\n", gTaskCount);
                break;
                
            default:
                break;
        }
}

/*  PlayFromScript()
*/
static int  
PlayFromScript(void)
{
    char buf[512];  
    char s[12];
    int c, i, k;

    /* The only way PlayFromScript will be called is if GP142_await_event() is 
    processing a message.  So we can simply fill in the global data structures 
    gEventAction and gEventRecord. */
    
    if (gScriptFP == NULL)
        if ((gScriptFP = fopen(kScriptName, "rt")) == NULL)
            {
                printf("Cannot open script file %s for reading\n", kScriptName);
                ClearPlayFlag();
                return GP142_FAILURE;
            }
            
    /* See if we're working on a block of user tasks right now */
    if (gTaskCount > 0)
        {
            gEventAction = GP142_PERIODIC;
            gTaskCount--;
            return GP142_SUCCESS;
        }

    /* We want to remember to skip over blank lines */
    fgets(buf, 512, gScriptFP);
    while (!feof(gScriptFP) && buf[0] == '\n')
        fgets(buf, 512, gScriptFP);

    if (feof(gScriptFP))
        {
            printf("EOF encountered in script file %s\n", kScriptName);
            ClearPlayFlag();
            return GP142_FAILURE;
        }

    /* We don't get fscanf() or sscanf() services with Windows DLLs, so
    we'll have to be more sneaky about how we parse the script file */

    c = buf[6]; /* buf[] = GP142_%c */
    switch (c)
        {
            case 'M':   /* GP142_MOUSE(x, y); */
                gEventAction = GP142_MOUSE;
                
                k = 6;
                while (!(isdigit(buf[k]) || buf[k] == '-'))
                    k++;
                    
                i = 0;
                while (isdigit(s[i] = buf[k+i]) || buf[k+i] == '-')
                    i++;
                s[i] = '\0';
                gEventRecord.x = atoi(s);
                                     
                k += i;
                while (!(isdigit(buf[k]) || buf[k] == '-'))
                    k++;
                    
                i = 0;
                while (isdigit(s[i] = buf[k+i]) || buf[k+i] == '-')
                    i++;
                s[i] = '\0';
                gEventRecord.y = atoi(s);
                break;
                
            case 'K':   /* GP142_KBD(c); */
                gEventAction = GP142_KBD;

                k = 6;  /* skip over the 'GP142_' */
                while (!isdigit(buf[k]))
                    k++;
                    
                i = 0;
                while (isdigit(s[i] = buf[k+i]))
                    i++;
                s[i] = '\0';
                gEventRecord.c = atoi(s);
                break;
                
            case 'P':   /* GP142_PERIODIC(i); */
                gEventAction = GP142_PERIODIC;

                k = 6;
                while (!isdigit(buf[k]))
                    k++;
                    
                i = 0;
                while (isdigit(s[i] = buf[k+i]))
                    i++;
                s[i] = '\0';
                
                /* we substract 1 because we've already counted 
                this task */
                gTaskCount = atoi(s) - 1;
                break;
                
            default:
                return GP142_FAILURE;

        }
    return GP142_SUCCESS;
}


/*  CloseScript()
*/
static void  
CloseScript(void)
{
    if (gScriptFP != NULL)
        fclose(gScriptFP);
}



/********************************************************** API Helper functions ***/
#ifdef WINDOWS
static void RedrawTextWnd(HWND hWnd)
{
    PAINTSTRUCT ps;
    HBRUSH hBrush, hOldBrush;
    HDC our_DC, offscreen_DC;
    HBITMAP offscreen_bitmap;
    RECT windowRect, lastLineRect;
    TEXTMETRIC tm;
    int nScrollHeight;
    int len,i,j;
    char far *pStr;

    BeginPaint(hWnd, &ps);

    GetClientRect(hWnd, &windowRect);

    /* We'll do all the drawing to an off-screen DC and then BitBlt it to the screen */
    our_DC = GetDC(hTextWnd);
    offscreen_DC = CreateCompatibleDC(our_DC);
    offscreen_bitmap = CreateCompatibleBitmap(offscreen_DC, windowRect.right, windowRect.bottom);
    SelectObject (offscreen_DC, offscreen_bitmap);

    /* First, clear window. Just draw a white rectangle */
    hBrush = CreateSolidBrush(GetBkColor(offscreen_DC));
    hOldBrush = SelectObject(offscreen_DC, hBrush);
    FillRect(offscreen_DC, &windowRect, hBrush);
            
    /* Get ready to draw strings */

    /* set the device context's font */
    SelectObject(offscreen_DC, GetStockObject(ANSI_FIXED_FONT));

    /* we'll need to figure out the height of the font.  We'll do this
    by asking Windows to fill in a structure telling all about the
    default font, which we have just set */ 
    GetTextMetrics(offscreen_DC, &tm);
    nScrollHeight = tm.tmHeight + tm.tmExternalLeading;

    /* This is the rectangle we'll use to erase the last line of text 
       that was scrolled up. We now know how big to make it. */
    lastLineRect.top = windowRect.bottom-nScrollHeight;
    lastLineRect.bottom = windowRect.bottom + 1;
    lastLineRect.left = windowRect.left;
    lastLineRect.right = windowRect.right;

    /* Walk through message ring, printing messages */
    for (i=gRingFirst, j=0;
        (i!=gRingLast || j==0) && i >= 0;
        RING_INC(i), j++)
    {             
        pStr = GlobalLock(gConsoleLines[i]);

        /* Move everything that was written so far up one line */
        ScrollDC(offscreen_DC,
            0,              /* no horizontal scrolling */
            -nScrollHeight, /* just vertical scrolling; negative means up */
            NULL,           /* scroll entire client area */
            NULL,           /* and leave clipping rectangle alone */
            (HRGN)NULL,     /* Windows needn't compute update region */
            NULL);          /* or update rectangle */

        /* Erase the place where the last line was  */
        FillRect(offscreen_DC, &lastLineRect, hBrush);

        /* omit trailing newlines */
        len = far_strlen(pStr);
        if (len > 0 && pStr[len-1] == '\n')
        {
            pStr[len-1] = '\0';
            len--;
        }

        TextOut(offscreen_DC,
            windowRect.left + 5,               /* leave ~5 pixel left margin */
            windowRect.bottom - nScrollHeight, /* new line appears at bottom */
            pStr,                              /* the string to display (far pointer) */
            len);                              /* and the string's length */

        GlobalUnlock(gConsoleLines[i]);
    }


    /* SelectObject(offscreen_DC, hOldBrush); */

    BitBlt (our_DC,0,0,windowRect.right, windowRect.bottom,
                         offscreen_DC,0,0,SRCCOPY);
    EndPaint(hWnd, &ps);

    DeleteObject(hBrush);
    DeleteObject(offscreen_bitmap);

    ReleaseDC(hTextWnd, our_DC);
    ReleaseDC(hTextWnd, offscreen_DC);
    DeleteDC(our_DC);
    DeleteDC(offscreen_DC);
}


/* little function used just inside DLL; no reason to export it */
static int far_strlen(char far *s)
{
    int i=0;
    
    while (*(s+i) != '\0')
        i++;
    return i;
}

/*
 * The following function, thanks to Chris Anderson, provides 
 * printint to the text window, essentially just like printf; 
 * the only main difference is that newlines ("\n") are ignored.
 */
extern int GP142_FUNC
WINprintf(
    const char fmt[],           /* the printf format string     */
    ... )                       /* list of variables to print   */
{
    va_list  vlist;             /* Argument list pointer        */
    char str[1024];             /* Buffer to build string into  */
    int cnt;                    /* Result of SPRINTF for return */  
    char far *pStr;        
    int i;
    RECT rClient;               

    va_start( vlist, fmt );     /* Initialize va_ functions     */

                                /* prints string to buffer      */
    cnt = vsprintf(str, fmt, vlist);
    va_end( vlist );            /* Close va_ functions          */
                                /* Send string to graphics wind */

    /* Save this string to the text window's ring buffer */

    /* Determine length of string, and store in i */
    i = 0;
    while (str[i] != '\0')
        i++;

    if (gRingFirst == gRingLast) /* ring is full, so overwrite the first */
        {
            GlobalFree(gConsoleLines[gRingFirst]);
            RING_INC(gRingFirst);
        }
    
    
    gConsoleLines[gRingLast] = GlobalAlloc(GMEM_MOVEABLE,
                                        (long unsigned)i+1L);
    pStr = GlobalLock(gConsoleLines[gRingLast]);

    /* Copy string into globally allocated memory */
    i = 0;
    while (str[i] != '\0')
        {
            pStr[i] = str[i];
            i++;
        }
    pStr[i] = '\0';         

    GlobalUnlock(gConsoleLines[gRingLast]);
                               
    /* if this was the first string in the buffer, treat it special */
    if (gRingFirst < 0)
        gRingFirst = gRingLast;
                        
    RING_INC(gRingLast);

    /* Display the string */
    /* DrawString(str); Commented out by Dan 2/3/00 */

    /* Try force the whole text window to be redrawn  */
    GetClientRect(hTextWnd, &rClient);
    InvalidateRect(hTextWnd, &rClient, 1);

    return( cnt );              /* Return the conversion count  */
}
#endif


/***************************************************************** API functions ***/
/* There are two types of API calls: GP142_gggXY() and GP142_gggP, where
ggg is the graphics symbol being drawn.  The XY indicates that the function
uses seperate integer values for the x and y components of the coordinates.
The P means that coordinates are specified in a Point structure.  In many
of the functions, an offset of width/2 has been subtracted from the coords;
this is meant to split the width of the object's outline across the logical
outline of the object.  This seems to make more intuitive sense to new Mac
programmers, and increases cross platform (Windows) portability. */


/**************************************************************** GP142_gets()
**  It is assumed that the string s is large enough for whatever string the user
**  enters.
*/
/***********TODO*************/
#ifdef MACINTOSH
extern int
GP142_gets(const char prompt[], char result[])
{
    Str255 pasStr;
    DialogPtr dialog;
    Handle itemHandle;
    char *itemPtr;
    Rect itemBox, dialogBounds = {154, 168, 279, 488};
    int i;
    short itemHit = 0;
    short itemType;

    for (i=1; i<255 && prompt[i-1] != '\0'; i++)
        pasStr[i] = prompt[i-1];
    pasStr[0] = i-1;

    itemHandle = (Handle)NewHandle(50);
    HLock(itemHandle);
    itemPtr = *itemHandle;

    itemPtr[0] = 0;     /* There are 2 + 1 = 3 items in the list */
    itemPtr[1] = 2;
    
    /* The Okay button */
    itemPtr[2] = 0;     /* Parent window pointer */
    itemPtr[3] = 0;
    itemPtr[4] = 0;
    itemPtr[5] = 0;
    itemPtr[6] = 0;     /* Top of button */
    itemPtr[7] = 94;
    itemPtr[8] = 0;     /* 64 - right of button */
    itemPtr[9] = -125;
    itemPtr[10] = 0;    /* bottom of button */
    itemPtr[11] = 114;
    itemPtr[12] = 0;    /* 64 - left of button */
    itemPtr[13] = -67;
    itemPtr[14] = btnCtrl + ctrlItem;
    itemPtr[15] = 4;    /* 4 bytes in variable-length field */
    itemPtr[16] = 'O';  /* Variable-length field */
    itemPtr[17] = 'k';
    itemPtr[18] = 'a';
    itemPtr[19] = 'y';
    
    /* The static text region */
    itemPtr[20] = 0;    /* Parent window pointer */
    itemPtr[21] = 0;
    itemPtr[22] = 0;
    itemPtr[23] = 0;
    itemPtr[24] = 0;    /* Top of control */
    itemPtr[25] = 10;
    itemPtr[26] = 0;    /* left of control */
    itemPtr[27] = 25;
    itemPtr[28] = 0;    /* bottom of control */
    itemPtr[29] = 40;
    itemPtr[30] = 1;    /* right of control (1*256 + 40)*/
    itemPtr[31] = 40;
    itemPtr[32] = statText;
    itemPtr[33] = 2;    /* 2 bytes of additional data */
    itemPtr[34] = '^';  /* Additional data */
    itemPtr[35] = '0';
    
    /* The edit text region */
    itemPtr[36] = 0;    /* Parent window pointer */
    itemPtr[37] = 0;
    itemPtr[38] = 0;
    itemPtr[39] = 0;
    itemPtr[40] = 0;    /* Top of control */
    itemPtr[41] = 41;
    itemPtr[42] = 0;    /* left of control */
    itemPtr[43] = 25;
    itemPtr[44] = 0;    /* bottom of control */
    itemPtr[45] = 82;
    itemPtr[46] = 1;    /* right of control */
    itemPtr[47] = 40;
    itemPtr[48] = editText;
    itemPtr[49] = 0;

    HUnlock(itemHandle);

    dialog = NewDialog(nil,     /* Let the OS allocate memory */
        &dialogBounds,          /* Bounding box of dialog */
        "\pGP142_gets()",       /* Title string, pascal style */
        FALSE,                  /* Don't show the dialog, yet */
        dBoxProc,               /* Dialog Box procedure ID */
        (WindowPtr)-1L,         /* Dialog will be in front of all windows */
        FALSE,                  /* Don't have a GoAway close box */
        0,                      /* Nothing in the RefCon field */
        itemHandle);            /* Handle to item list */



    ParamText(pasStr, "\p", "\p", "\p");
    ShowWindow(dialog);
    
    while (itemHit != ok)
        ModalDialog(nil, &itemHit);
            
    /* Get a handle to the edit text of the dialog box */
#if USES_NEW_HEADERS
    GetDialogItem(dialog, kGetsEditTextID, &itemType, &itemHandle, &itemBox);
#else
    GetDItem(dialog, kGetsEditTextID, &itemType, &itemHandle, &itemBox);
#endif
    /* Convert the handle to a pascal string */
#if USES_NEW_HEADERS
   GetDialogItemText(itemHandle, pasStr); 
#else
    GetIText(itemHandle, pasStr); 
#endif
    
#if USES_NEW_HEADERS
    DisposeDialog(dialog);
#else
    DisposDialog(dialog);
#endif
    
    for (i=0; i<pasStr[0]; i++)
        result[i] = pasStr[i+1];
    result[i] = '\0';   
    
    return GP142_SUCCESS;
}

#elif defined(WINDOWS)
#ifdef WIN32
// Win32 version by Zack Ives, 6/19/98
// 
// tested on WinNT 4.0
#pragma pack(push,before)
#pragma pack(4)
#define MAX_PROMPT 79
typedef struct {
    DLGTEMPLATE dt;
    unsigned short
        menuarray,
        classarray;
    WCHAR title[11];

    DLGITEMTEMPLATE edit;
    unsigned short
        editClassArray[2];
    WCHAR editTitleArray[1];
    unsigned short editCreationArray[2];
    
    DLGITEMTEMPLATE button;
    unsigned short
        buttonClassArray[2];
    WCHAR buttonTitleArray[5];
    unsigned short buttonCreationArray[2];

    DLGITEMTEMPLATE text;
    unsigned short
        textClassArray[2];
    WCHAR textTitleArray[MAX_PROMPT];
    unsigned short textCreationArray[2];
    
} dialogInfo;
#pragma pack(pop, before)


extern int GP142_FUNC 
GP142_gets(const char prompt[], char result[])
{
     unsigned long size;
     int promptLen;
     dialogInfo d;
     dialogInfo far *di;
     char title[] = "GP142_gets";

     int temp;
     long unsigned
          dialogStyle = WS_CAPTION | WS_SYSMENU | WS_POPUP | WS_VISIBLE |
                DS_MODALFRAME,
          okayStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
          editStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE |
                ES_AUTOVSCROLL | WS_BORDER,
          staticStyle = WS_CHILD | WS_VISIBLE | SS_LEFT | WS_GROUP;

     for (promptLen=0; prompt[promptLen] != '\0'; promptLen++);
         promptLen++;    /* Add room for NULL terminator */

     size = sizeof(dialogInfo);

     ZeroMemory(&d, sizeof(dialogInfo));
     di = &d;

     di->dt.style = dialogStyle;
     di->dt.dwExtendedStyle = 0;
     di->dt.cdit = 3;
     di->dt.x = 50;
     di->dt.y = 50;
     di->dt.cx = 185;
     di->dt.cy = 92;
     di->menuarray = 0;
     di->classarray = 0;

     for (temp = 0; (unsigned)temp < strlen(title); temp++)
         di->title[temp] = title[temp];
     di->title[temp] = 0;

        /* Okay button */
     di->button.style = okayStyle;
     di->button.x = 67;
     di->button.y = 74;
     di->button.cx = 50;
     di->button.cy = 14;
     di->button.id = kOkayID;
     di->buttonClassArray[0] = 0xFFFF;
     di->buttonClassArray[1] = 0x0080;
     di->buttonTitleArray[0] = 'O';
     di->buttonTitleArray[1] = 'k';
     di->buttonTitleArray[2] = 'a';
     di->buttonTitleArray[3] = 'y';
     di->buttonTitleArray[4] = 0;
     di->buttonCreationArray[0] = 0;

        /* Edit text */
     di->edit.style = editStyle;
     di->edit.x = 8;
     di->edit.y = 30;
     di->edit.cx = 167;
     di->edit.cy = 37;
     di->edit.id = kEditID;
     di->editClassArray[0] = 0xFFFF;
     di->editClassArray[1] = 0x0081;
     di->editTitleArray[0] = 0;
     di->editCreationArray[0] = 0;

        /* Static text */
     di->text.style = staticStyle;
     di->text.x = 8;
     di->text.y = 3;
     di->text.cx = 167;
     di->text.cy = 24;
     di->text.id = kStaticID;
     di->textClassArray[0] = 0xFFFF;
     di->textClassArray[1] = 0x0082;
     
     for (temp = 0; temp < MAX_PROMPT; temp++)
         if ((unsigned)temp < strlen(prompt))
             di->textTitleArray[temp] = prompt[temp];
         else
             di->textTitleArray[temp] = ' ';
     di->textTitleArray[temp] = 0;
     di->textCreationArray[0] = 0;

    /* Display the dialog box */
    temp = DialogBoxIndirectParam(hInst, (DLGTEMPLATE *)di, 
        hDrawWnd, getsDialogProc, (DWORD)result);
                                
    return (temp == -1)?GP142_FAILURE:GP142_SUCCESS;
}

#else
GP142_gets(const char prompt[], char result[])
{
     unsigned long size;
     int promptLen;
     FARPROC lpDlgProc;
     HANDLE hDialogTemplate;
     unsigned char far *dialogPtr;
     int i, temp;
     long unsigned
          dialogStyle = WS_CAPTION | WS_SYSMENU | WS_POPUP | WS_VISIBLE |
                DS_MODALFRAME,
          okayStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
          editStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE |
                ES_AUTOVSCROLL | WS_BORDER,
          staticStyle = WS_CHILD | WS_VISIBLE | SS_LEFT | WS_GROUP;


     for (promptLen=0; prompt[promptLen] != '\0'; promptLen++);
     promptLen++;    /* Add room for NULL terminator */

     size = 82 + promptLen;

     hDialogTemplate = GlobalAlloc(GMEM_MOVEABLE, (long unsigned)size);
     dialogPtr = (unsigned char far *)GlobalLock(hDialogTemplate);

     dialogPtr[0] = (unsigned char)((dialogStyle & 0x000000FFL) >> 0);
     dialogPtr[1] = (unsigned char)((dialogStyle & 0x0000FF00L) >> 8);
     dialogPtr[2] = (unsigned char)((dialogStyle & 0x00FF0000L) >> 16);
     dialogPtr[3] = (unsigned char)((dialogStyle & 0xFF000000L) >> 24);
    dialogPtr[4] = (unsigned char)3;       /* number of controls */
    dialogPtr[5] = (unsigned char)(((50) & 0x00FF)) >> 0; /* left edge pos, LSB */
    dialogPtr[6] = (unsigned char)(((50) & 0xFF00)) >> 8;
    dialogPtr[7] = (unsigned char)(((50) & 0x00FF)) >> 0; /* top edge pos,  LSB */
    dialogPtr[8] = (unsigned char)(((50) & 0xFF00)) >> 8;
    dialogPtr[9] = (unsigned char)185;     /* width, LSB */
    dialogPtr[10] = (unsigned char)0;
    dialogPtr[11] = (unsigned char)92;     /* height, LSB */
    dialogPtr[12] = (unsigned char)0;
    dialogPtr[13] = (unsigned char)0;      /* menu */
    dialogPtr[14] = (unsigned char)0;      /* class */
    dialogPtr[15] = (unsigned char)'G';    /* caption */
    dialogPtr[16] = (unsigned char)'P';
    dialogPtr[17] = (unsigned char)'1';
    dialogPtr[18] = (unsigned char)'4';
    dialogPtr[19] = (unsigned char)'2';
    dialogPtr[20] = (unsigned char)'_';
    dialogPtr[21] = (unsigned char)'g';
    dialogPtr[22] = (unsigned char)'e';
    dialogPtr[23] = (unsigned char)'t';
    dialogPtr[24] = (unsigned char)'s';
    dialogPtr[25] = (unsigned char)'(';
    dialogPtr[26] = (unsigned char)')';
    dialogPtr[27] = (unsigned char)'\0';

    /* Okay button */

    dialogPtr[28] = (unsigned char)67; /* left edge of button */
    dialogPtr[29] = (unsigned char)0;
    dialogPtr[30] = (unsigned char)74; /* top edge of button */
    dialogPtr[31] = (unsigned char)0;
    dialogPtr[32] = (unsigned char)50; /* width of button */
    dialogPtr[33] = (unsigned char)0;
    dialogPtr[34] = (unsigned char)14; /* height of button */
    dialogPtr[35] = (unsigned char)0;
    dialogPtr[36] = (unsigned char)((kOkayID & 0x00FF) >> 0);    /* button ID */
    dialogPtr[37] = (unsigned char)((kOkayID & 0xFF00) >> 8);
     dialogPtr[38] = (unsigned char)((okayStyle & 0x000000FFL) >> 0);/* Button style */
     dialogPtr[39] = (unsigned char)((okayStyle & 0x0000FF00L) >> 8);
     dialogPtr[40] = (unsigned char)((okayStyle & 0x00FF0000L) >> 16);
     dialogPtr[41] = (unsigned char)((okayStyle & 0xFF000000L) >> 24);
    dialogPtr[42] = (unsigned char)0x80;   /* Button class */
    dialogPtr[43] = (unsigned char)'O';    /* Button text */
    dialogPtr[44] = (unsigned char)'k';
    dialogPtr[45] = (unsigned char)'a';
    dialogPtr[46] = (unsigned char)'y';
    dialogPtr[47] = (unsigned char)'\0';
    dialogPtr[48] = (unsigned char)0;      /* size of variable length field */
    
    
    /* Edit text */
    dialogPtr[49] = (unsigned char)8;  /* left edge of control */
    dialogPtr[50] = (unsigned char)0;
    dialogPtr[51] = (unsigned char)30; /* top edge of control */
    dialogPtr[52] = (unsigned char)0;
    dialogPtr[53] = (unsigned char)167;/* width of control */
    dialogPtr[54] = (unsigned char)0;
    dialogPtr[55] = (unsigned char)37; /* height of control */
    dialogPtr[56] = (unsigned char)0;
    dialogPtr[57] = (unsigned char)((kEditID & 0x00FF) >> 0);/* control ID */
    dialogPtr[58] = (unsigned char)((kEditID & 0xFF00) >> 8);
     dialogPtr[59] = (unsigned char)((editStyle & 0x000000FFL) >> 0);/* control style */
     dialogPtr[60] = (unsigned char)((editStyle & 0x0000FF00L) >> 8);
     dialogPtr[61] = (unsigned char)((editStyle & 0x00FF0000L) >> 16);
     dialogPtr[62] = (unsigned char)((editStyle & 0xFF000000L) >> 24);
    dialogPtr[63] = (unsigned char)0x81;   /* control class */
    dialogPtr[64] = (unsigned char)'\0';   /* control text */
    dialogPtr[65] = (unsigned char)0;      /* size of variable length field */


    /* Static text */   
    dialogPtr[66] = (unsigned char)8;  /* left edge of control */
    dialogPtr[67] = (unsigned char)0;
    dialogPtr[68] = (unsigned char)3;  /* top edge of control */
    dialogPtr[69] = (unsigned char)0;
    dialogPtr[70] = (unsigned char)167;/* width of control */
    dialogPtr[71] = (unsigned char)0;
    dialogPtr[72] = (unsigned char)24; /* height of control */
    dialogPtr[73] = (unsigned char)0;
    dialogPtr[74] = (unsigned char)((kStaticID & 0x00FF) >> 0);/* control ID */
    dialogPtr[75] = (unsigned char)((kStaticID & 0xFF00) >> 8);
     dialogPtr[76] = (unsigned char)((staticStyle & 0x000000FFL) >> 0);/* control style */
     dialogPtr[77] = (unsigned char)((staticStyle & 0x0000FF00L) >> 8);
     dialogPtr[78] = (unsigned char)((staticStyle & 0x00FF0000L) >> 16);
     dialogPtr[79] = (unsigned char)((staticStyle & 0xFF000000L) >> 24);
    dialogPtr[80] = (unsigned char)0x82;   /* control class */
    for (i=0; i<promptLen; i++)
        dialogPtr[81 + i] = (unsigned char)prompt[i];
    dialogPtr[81 + promptLen] = (unsigned char)0;

    GlobalUnlock(hDialogTemplate);

    /* Display the dialog box */
    lpDlgProc = MakeProcInstance(getsDialogProc, hInst);
    temp = DialogBoxIndirectParam(hInst, hDialogTemplate, 
        hDrawWnd, lpDlgProc, (DWORD)result);
    FreeProcInstance(lpDlgProc);
                                
    /* Free the memory */
    GlobalFree(hDialogTemplate);

    return temp==-1?GP142_FAILURE:GP142_SUCCESS;
}
#endif

#ifdef WIN32
BOOL CALLBACK getsDialogProc(HWND hDlg, UINT wMessage, WPARAM wParam, LONG lParam)
#else
BOOL FAR PASCAL EXPORT getsDialogProc(HWND hDlg, WORD wMessage,
                                        WORD wParam, LONG lParam)
#endif
{
    static char *result;
    
    switch (wMessage)
        {
            case WM_INITDIALOG:
                result = (char *)lParam;
                     return TRUE;

                case WM_COMMAND:
                switch (wParam)
                    {
                        case kOkayID:
                            /* Copy the edit text into the result */
                            GetDlgItemText(hDlg, kEditID, result, 256);
                            EndDialog(hDlg, TRUE);
                            return TRUE;
                    }
                break;
        }
        
    return FALSE;
}
#endif /* Windows version of GP142_gets() */



/********************************************************* GP142_animate()
**
**  let the user control animation:
**      f == 0  => halt
**      f == 1  => single step
**      f == 2  => run
**      f == 5  => quit
**
*/
extern int GP142_FUNC
GP142_animate(int f)
{
#ifdef MACINTOSH
    if (!gpWin)
#elif defined(WINDOWS)
    if (!hDrawWnd)
#elif defined(X11R6)
    if (!display)
#endif
        return GP142_FAILURE;           

    switch ( f )
        {
            case ANI_RUN:           /* run          */
                gRunFlag = TRUE;
                break;
            case ANI_HALT:          /* halt         */
                gSingleStepFlag = FALSE;
                gRunFlag = FALSE;
                break;
            case ANI_SINGLE_STEP:   /* single step  */
                gSingleStepFlag = TRUE;
                break;
            case ANI_QUIT:          /* quit         */
                gDoneFlag = TRUE;
                break;
            default:     
#ifdef MACINTOSH            
                SysBeep(1);
#endif
                break;
        }

    return GP142_SUCCESS;
}



/******************************************************** GP142_logging() **
**  let the user set the logging flag
**
*/
extern int GP142_FUNC
GP142_logging(int f)
{
#ifdef MACINTOSH
    if (!gpWin)
#elif defined(WINDOWS)
    if (!hDrawWnd)
#elif defined(X11R6)
    if (!display)
#endif
        return GP142_FAILURE;   /* GP142_open hasn't been called yet; do nothing */
    gLogging = !!f;             /* !! forces value to be either 0 or 1 */
#ifdef MACINTOSH
    CheckItem(RunMenu, mLog, (int)gLogging);
#elif defined(WINDOWS)
    if (gLogging)
        CheckMenuItem(hRunMenu, IDM_LOGGING, MF_BYCOMMAND | MF_CHECKED);
    else
        CheckMenuItem(hRunMenu, IDM_LOGGING, MF_BYCOMMAND | MF_UNCHECKED);
#elif defined(X11R6)
    XClearWindow(display,winc[3]);
    if (gLogging)
        XDrawString(display, winc[3], gccon, 5, 15, "Logging on", 10);
    else
        XDrawString(display, winc[3], gccon, 5, 15, "Logging off", 11);
#endif
    if (gLogging)
        GP142_show_text(TRUE);

   return GP142_SUCCESS ;
}

/*
** Verify that color is legal; print error and reset if not.
** In all cases, return a legal color.
*/
static int Legalize_Color(int color)
{
    if ( ! ( 0 <= color && color <= MAX_COLORS ) )
        {
            printf("Illegal color %d; using RED.\n", color);
            color = RED;
        }
    return (color);
}


/******************************************************** GP142_pixel() ***/
extern int GP142_FUNC
GP142_pixelXY (int color, int x, int y)
{
    GP142_point p;
    p.x = x;
    p.y = y;

    return GP142_pixelP(color, p);
}

extern int GP142_FUNC
GP142_pixelP (int color, GP142_point p)
{
    Graphics new_item;
    
    color = Legalize_Color(color);
    if (gLogging) {
        printf("%s pixel at (%d,%d)\n",
            gColorName[color], p.x, p.y);
    }

    new_item.obj_type = obj_pixel;
    new_item.g.pixel.p = p;
    new_item.color = color;
    
    Draw_Graphic_Item(&new_item);

    return GP142_SUCCESS;
}


/******************************************************* GP142_circle() ***/
extern int GP142_FUNC
GP142_circleXY (int color, int x, int y, int radius)
{
    GP142_point p;
    
    p.x = x;
    p.y = y;
    
    return GP142_circleP(color, p, radius);
}
    
extern int GP142_FUNC
GP142_circleP (int color, GP142_point center, int radius)
{
    Graphics new_item;
    
    color = Legalize_Color(color);
    if (radius < 0)
        {
            printf("Radius of %d not possible, using radius %d\n", radius, -radius);
            radius = -radius;
        }
        
    if (gLogging) {
        printf("%s circle at (%d,%d), radius %d\n",
            gColorName[color], center.x, center.y, radius);
    }
    
    new_item.obj_type = obj_oval;
    new_item.g.oval.upper_left.x = center.x - radius;
    new_item.g.oval.upper_left.y = center.y + radius;
    new_item.g.oval.lower_right.x = center.x + radius;
    new_item.g.oval.lower_right.y =center.y - radius;
    new_item.color = color;
    new_item.width = 0;

    Draw_Graphic_Item(&new_item);

    return GP142_SUCCESS;
}


/***************************************************** GP142_triangle() ***/
extern int GP142_FUNC
GP142_triangleXY (
    int color,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    int width)
{
    GP142_point p1, p2, p3;
    
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    p3.x = x3;
    p3.y = y3;
    
    return GP142_triangleP(color, p1, p2, p3, width);
}

extern int GP142_FUNC
GP142_triangleP (int color, GP142_point p1, 
                GP142_point p2, GP142_point p3, int width)
{
    Graphics new_item;

    color = Legalize_Color(color);
    if (width < 0)
        {
            printf("Width of %d not possible, using width %d\n", width, -width);
            width = -width;
        }
        
    if (gLogging) {
        printf("%s triangle at (%d,%d), (%d,%d), (%d,%d)\n",
            gColorName[color], p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    }
    new_item.obj_type = obj_triangle;
    new_item.g.triangle.p1.x = p1.x;
    new_item.g.triangle.p1.y = p1.y;
    new_item.g.triangle.p2.x = p2.x;
    new_item.g.triangle.p2.y = p2.y;
    new_item.g.triangle.p3.x = p3.x;
    new_item.g.triangle.p3.y = p3.y;
    new_item.color = color;
    new_item.width = width;

    Draw_Graphic_Item(&new_item);

    return GP142_SUCCESS;
}

/************************************************** GP142_rectangle() ****/
extern int GP142_FUNC
GP142_rectangleXY (
    int color,
    int x1, int y1,
    int x2, int y2,
    int width)
{
    GP142_point p1, p2;
    
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    
    return GP142_rectangleP(color, p1, p2, width);
}

extern int GP142_FUNC
GP142_rectangleP (
    int color, GP142_point p_upper_left, GP142_point p_lower_right,
    int width)
{
    Graphics new_item;
    int temp; 
    
    /* Determine proper ordering of points */
    if (p_upper_left.x > p_lower_right.x)
        {
            temp = p_upper_left.x;
            p_upper_left.x = p_lower_right.x;
            p_lower_right.x = temp;
        }
    if (p_upper_left.y < p_lower_right.y)
        {
            temp = p_upper_left.y;
            p_upper_left.y = p_lower_right.y;
            p_lower_right.y = temp;
        }
    
    color = Legalize_Color(color);
    if (width < 0)
        {
            printf("Width of %d not possible, using width %d\n", width, -width);
            width = -width;
        }
    
    if (gLogging) {
        if (width == 0)
            printf("%s rectangle with bounding box (%d,%d) to (%d,%d)"
                    ", filled\n",
                    gColorName[color],
                    p_upper_left.x, p_upper_left.y,
                    p_lower_right.x, p_lower_right.y);
        else
            printf("%s rectangle with bounding box (%d,%d) to (%d,%d)"
                    " with line width %d\n",
                    gColorName[color],
                    p_upper_left.x, p_upper_left.y,
                    p_lower_right.x, p_lower_right.y, width);
    }
    
    
    
    new_item.obj_type = obj_rectangle;
    new_item.g.rectangle.upper_left.x = p_upper_left.x;
    new_item.g.rectangle.upper_left.y = p_upper_left.y;
    new_item.g.rectangle.lower_right.x = p_lower_right.x;
    new_item.g.rectangle.lower_right.y = p_lower_right.y;
    new_item.color = color;
    new_item.width = width;

    Draw_Graphic_Item(&new_item);

    return GP142_SUCCESS;
}


/********************************************************* GP142_oval() ***/
extern int GP142_FUNC
GP142_ovalXY (
    int color,
    int x1, int y1,
    int x2, int y2,
    int width)
{
    GP142_point p1, p2;
    
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    
    return GP142_ovalP(color, p1, p2, width);
}


extern int GP142_FUNC
GP142_ovalP (
    int color, 
    GP142_point p_upper_left, GP142_point p_lower_right,
    int width)
{
    Graphics new_item;
    int temp;

    /* Determine proper ordering of points */
    if (p_upper_left.x > p_lower_right.x)
        {
            temp = p_upper_left.x;
            p_upper_left.x = p_lower_right.x;
            p_lower_right.x = temp;
        }
    if (p_upper_left.y < p_lower_right.y)
        {
            temp = p_upper_left.y;
            p_upper_left.y = p_lower_right.y;
            p_lower_right.y = temp;
        }

    if (width < 0)
        {
            printf("Width of %d not possible, using width %d\n", width, -width);
            width = -width;
        }
        
    color = Legalize_Color(color);
    if (gLogging) {
        if (width == 0)
            printf("%s oval with bounding box (%d,%d) to (%d,%d), "
                    "filled\n",
                    gColorName[color],
                    p_upper_left.x, p_upper_left.y,
                    p_lower_right.x, p_lower_right.y);
        else
            printf("%s oval with bounding box (%d,%d) to (%d,%d), "
                    "line width %d\n",
                    gColorName[color],
                    p_upper_left.x, p_upper_left.y,
                    p_lower_right.x, p_lower_right.y, width);
    }
    
    new_item.obj_type = obj_oval;
    new_item.g.oval.upper_left.x = p_upper_left.x;
    new_item.g.oval.upper_left.y = p_upper_left.y;
    new_item.g.oval.lower_right.x = p_lower_right.x;
    new_item.g.oval.lower_right.y = p_lower_right.y;
    new_item.color = color;
    new_item.width = width;

    Draw_Graphic_Item(&new_item);
    
    return GP142_SUCCESS;
}


/********************************************************* GP142_line() ***/
extern int GP142_FUNC
GP142_lineXY (int color, int x1, int y1, int x2, int y2, int width)
{
    GP142_point p1, p2;
    
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    
    return GP142_lineP(color, p1, p2, width);
}                                                      


extern int GP142_FUNC
GP142_lineP (int color, GP142_point pUL, GP142_point pLR, int width)
{
    Graphics new_item;
    
    if (width < 0)
        {
            printf("Width of %d not possible, using width %d\n", width, -width);
            width = -width;
        }
        
    color = Legalize_Color(color);
    if (gLogging) {
        printf("%s line from (%d,%d) to (%d,%d), width %d\n",
            gColorName[color], pUL.x, pUL.y, pLR.x, pLR.y, width);
    }
    new_item.obj_type = obj_line;
    new_item.g.line.upper_left.x = pUL.x;
    new_item.g.line.upper_left.y = pUL.y;
    new_item.g.line.lower_right.x = pLR.x;
    new_item.g.line.lower_right.y = pLR.y;
    new_item.color = color;
    if (width < 1) width = 1;
    new_item.width = width;

    Draw_Graphic_Item(&new_item);

    return GP142_SUCCESS;
}
                            

/********************************************************* GP142_text() ***/
extern int GP142_FUNC
GP142_textXY(int color, int x, int y, int ptsize, const char *string)
{
    GP142_point p;
    
    p.x = x;
    p.y = y;
    
    return GP142_textP(color, p, ptsize, string);
}

                            
extern int GP142_FUNC
GP142_textP (int color, GP142_point p, int ptsize, const char string[])
{
    Graphics new_item;
#ifdef MACINTOSH
    int len;
#elif defined(WINDOWS)
    char far *pStr;
    int i;
#elif defined(X11R6)
    int len;
#endif  
    
    if (ptsize < 0)
        {
            printf("ptsize of %d not possible, using ptsize %d\n", ptsize, -ptsize);
            ptsize = -ptsize;
        }
    if (ptsize > 127)
        {
            printf("ptsize of %d not possible, using ptsize %d\n", ptsize, 127);
            ptsize = 127;
        }
    
    color = Legalize_Color(color);
    if (gLogging) {
        printf("%s text at (%d,%d), \"%s\"\n",
            gColorName[color], p.x, p.y, string);
    }
    new_item.obj_type = obj_text;
    new_item.g.text.p.x = p.x;
    new_item.g.text.p.y = p.y;
    new_item.color = color;
    new_item.g.text.ptsize = ptsize;

#ifdef MACINTOSH
    len = strlen(string) + 1;
    if (len > MAXSTRLEN) len = MAXSTRLEN;
    if ((new_item.g.text.the_text = malloc(len)) == NULL) {
        printf("GP142 library error: out of memory\n");
        return GP142_FAILURE;
    }
    strncpy(new_item.g.text.the_text, string, len);
    new_item.g.text.the_text[len - 1] = 0;  /* to be for sure, for sure */
    CtoPstr(new_item.g.text.the_text);
    Draw_Graphic_Item(&new_item);
    free(new_item.g.text.the_text);
    
#elif defined(WINDOWS)
       
    i = 0;
    while (string[i] != '\0')
        i++;
    new_item.g.text.hText = 
        GlobalAlloc(GMEM_MOVEABLE, (long unsigned)i+1L);
    pStr = GlobalLock(new_item.g.text.hText);

    i = 0;
    while (string[i] != '\0')
        {
            pStr[i] = string[i];
            i++;
        }
    pStr[i] = '\0';         

    GlobalUnlock(new_item.g.text.hText);

    Draw_Graphic_Item(&new_item);
    GlobalFree(new_item.g.text.hText);

#elif defined(X11R6)

    len = strlen(string) + 1;

    if (len > MAXSTRLEN) len = MAXSTRLEN;

    if ((new_item.g.text.the_text = (char *) malloc(len)) == NULL) {
        printf("GP142 library error: out of memory\n");
        return GP142_FAILURE;
    }

    strncpy(new_item.g.text.the_text, string, len);
    new_item.g.text.the_text[len - 1] = 0; 
    Draw_Graphic_Item(&new_item);
    free(new_item.g.text.the_text);

#endif

    return GP142_SUCCESS;
}


/****************************************************** GP142_getDimensions() ***/
/*
 * functions to get the on-screen dimensions of text
 */

extern int GP142_FUNC
GP142_getDimensions2 (int ptsize, int *height, int *width, const char string[])
{
#ifdef MACINTOSH
    int len;
    FontInfo fontInfo;
    char *theString;
#elif defined(WINDOWS)
    char far *pStr;
    int i;
    HFONT hFont, hOldFont;
    HANDLE hText;
    SIZE textSize;
#elif defined(X11R6)
    int len;
#endif  
    
    if (ptsize < 0)
        {
            printf("ptsize of %d not possible, using ptsize %d\n", ptsize, -ptsize);
            ptsize = -ptsize;
        }
    if (ptsize > 127)
        {
            printf("ptsize of %d not possible, using ptsize %d\n", ptsize, 127);
            ptsize = 127;
        }
    
#ifdef MACINTOSH
    len = strlen(string) + 1;
    if (len > MAXSTRLEN) len = MAXSTRLEN;
    if ((theString = malloc(len)) == NULL) {
        printf("GP142 library error: out of memory\n");
        return GP142_FAILURE;
    }
    strncpy(theString, string, len);
    theString[len - 1] = 0;  /* to be for sure, for sure */
    CtoPstr(theString);
    TextSize(ptsize);
    GetFontInfo(&fontInfo);
    *width = TextWidth(theString, 1, strlen(string));
    *height = fontInfo.ascent + fontInfo.descent + fontInfo.leading;
    free(theString);
    
#elif defined(WINDOWS)
  
    i = 0;
    while (string[i] != '\0')
        i++;
    hText = 
        GlobalAlloc(GMEM_MOVEABLE, (long unsigned)i+1L);
    pStr = GlobalLock(hText);

    i = 0;
    while (string[i] != '\0')
        {
            pStr[i] = string[i];
            i++;
        }
    pStr[i] = '\0';         

    GlobalUnlock(hText);

    hFont = CreateFont(-ptsize,
       0,          /* let Windows choose width */
       0,          /* escapement, in 10ths of degrees */
       0,          /* orientation, in 10ths of degrees */
       FW_NORMAL,  /* normal weight */
       FALSE,      /* no italic */
       FALSE,      /* no underline */
       FALSE,      /* no strikeout */
       ANSI_CHARSET,   /* use ANSI character set */
       OUT_DEFAULT_PRECIS, /* output precision */
       CLIP_DEFAULT_PRECIS,    /* clip precision */
       DEFAULT_QUALITY,    /* quality */
       DEFAULT_PITCH | FF_DONTCARE,    /* pitch and family */
       "GP142-font");  /* way-cool name of font */

    hOldFont = SelectObject(offscreen_DC, hFont);

    pStr = GlobalLock(hText);

    /* To be compatible with the Mac, we want to bump the
    text string 'up' by the height of the string */
    GetTextExtentPoint(offscreen_DC,
      pStr,
      far_strlen(pStr),
      &textSize);
    *width = textSize.cx;
    *height = textSize.cy;

    GlobalUnlock(hText);

    SelectObject(offscreen_DC, hOldFont);
    DeleteObject(hFont);
      
#elif defined(X11R6)

    if (ptsize != current_font->point_size) {

      FontDB *temp = font_info;

      while (temp) {
        if (ptsize == temp->point_size)
          break;
        temp = temp->next;
      }

      /* Or else add it to the list and load it.  */

      if (!temp) {
        char fontname[100];
        temp = (FontDB*) malloc(sizeof(FontDB));
        sprintf(fontname, "-adobe-helvetica-medium-r-normal--0-%d-75-75-p-0-iso8859-1", ptsize * 10);
        if ((temp == NULL) ||
            (temp->thefont = XLoadQueryFont(display, 
                                    fontname)) == NULL) {
          fprintf(stderr, "Cannot open Adobe scalable font.\n");
          exit(0);
        }

        /* Set font to requested point size and put node at  
         * the head of the list.  */

        temp->point_size = ptsize;
        temp->next = font_info;
        font_info = temp;
      }

      /* Set gc to new point size */
      XSetFont(display, gc, temp->thefont->fid);
      current_font = temp;
    }

    *height = current_font->thefont->ascent + current_font->thefont->descent;
    *width = XTextWidth(current_font->thefont, string, strlen(string));

#endif

    return GP142_SUCCESS;
}


/****************************************************** GP142_printf() ***/
/*
 * The following function, thanks to Chris Anderson, subsumes 
 * GP142_int and GP142_text (from v1.9 and previous), from users 
 * perspective. It provides formated printout to the graphics window, 
 * essentially just like printf; newlines ("\n") do advance text to the
 * next line.
 */
extern int GP142_FUNC
GP142_printfXY( 
    int color,                  /* text color                   */
    int x, int y,               /* x, y coords of left end of text */
    int point_size,             /* text size                    */
    const char fmt[],           /* the printf format string     */
    ... )                       /* list of variables to print   */
{
  va_list  vlist;               /* Argument list pointer        */
  char str[1024];               /* Buffer to build string into  */
  int cnt;                      /* Result of SPRINTF for return */

  va_start( vlist, fmt );       /* Initialize va_ functions     */

                                /* prints string to buffer      */
  cnt = vsprintf( str, fmt, vlist ); 
  va_end( vlist );              /* Close va_ functions          */
                                /* Send string to graphics wind */
  GP142_textXY( color,x,y,point_size,str ); 
  return( cnt );                /* Return the conversion count  */
}

extern int GP142_FUNC
GP142_printfP(
    int color,                  /* text color                   */
    GP142_point p,              /* x, y coords of left end of text */
    int point_size,             /* text size                    */
    const char fmt[],           /* the printf format string     */
    ... )                       /* list of variables to print   */
{
  va_list  vlist;               /* Argument list pointer        */
  char str[1024];               /* Buffer to build string into  */
  int cnt;                      /* Result of SPRINTF for return */

  va_start( vlist, fmt );       /* Initialize va_ functions     */

                                /* prints string to buffer      */
  cnt = vsprintf( str, fmt, vlist ); 
  va_end( vlist );              /* Close va_ functions          */
                                /* Send string to graphics wind */
  GP142_textP( color,p,point_size,str ); 
  return( cnt );                /* Return the conversion count  */
} 

extern int GP142_FUNC
GP142_getDimensions( 
    int point_size,             /* text size                    */
    int *height,
    int *width,
    const char fmt[],           /* the printf format string     */
    ... )                       /* list of variables to print   */
{
  va_list  vlist;               /* Argument list pointer        */
  char str[1024];               /* Buffer to build string into  */
  int cnt;                      /* Result of SPRINTF for return */

  va_start( vlist, fmt );       /* Initialize va_ functions     */

                                /* prints string to buffer      */
  cnt = vsprintf( str, fmt, vlist ); 
  va_end( vlist );              /* Close va_ functions          */
                                /* get dimensions of string     */
  GP142_getDimensions2( point_size,height,width,str );
  return ( cnt );               /* Return the conversion count  */
}


/******************************************************** GP142_undo() ***/
extern int GP142_FUNC
GP142_undo(void)
{
    printf("GP142_undo is no longer supported.\n");
    return GP142_SUCCESS;
}

/******************************************************* GP142_flush() ***/
extern int GP142_FUNC
GP142_flush(void)
{
    if (gLogging) {
        printf("Flushing the graphics window\n");
    }
#ifdef MACINTOSH
    refresh(gpWin);

#elif defined(WINDOWS)
     if (need_redraw) {
         BitBlt (the_hdc,0,0,2*GP142_XMAX+1, 2*GP142_YMAX+FUDGE,
             offscreen_DC,0,0,SRCCOPY);
         need_redraw = 0;
     }
#elif defined(X11R6)
     if (need_redraw) {
         XCopyArea(display, offscreen_buffer, window, gc, 0, 0, GP142_XMAX*2, GP142_YMAX*2, 0, 0);
         XFlush(display);
         need_redraw = 0;
     }
#endif

    return GP142_SUCCESS;
}


/******************************************************* GP142_clear() ***/
extern int GP142_FUNC
GP142_clear(void)
{
    if (gLogging) {
        printf("Clearing the graphics window\n");
    }

    /* Clear the offscreen buffer */
    GP_clear();

    return GP142_SUCCESS;
}


static void GP_clear(void)
{
#ifdef MACINTOSH
    GDHandle oldGD;
    GWorldPtr oldGWorld;

    GetGWorld(&oldGWorld, &oldGD);
    LockPixels(gGP142World->portPixMap);
    SetGWorld(gGP142World, nil);
    
    EraseRect(&(*gGP142World->portPixMap)->bounds);
    
    SetGWorld(oldGWorld, oldGD);
    UnlockPixels(gGP142World->portPixMap);
#elif defined(WINDOWS)
    /* Just draw a white rectangle */
    HBRUSH hBrush, hOldBrush;
    hBrush = CreateSolidBrush(gRGBColors[1]);
    hOldBrush = SelectObject(offscreen_DC, hBrush);

    /* Windows draws lines in a very odd fashion.  Windows 
    will include the first endpoint when drawing a line, but
    _exclude_ the next endpoint.  I gather that this allows
    for poly-lines, but very strange things happen when you
    draw single lines this way.  That is why we add 1 to the
    ending x and y coords in the rectangle, oval, etc. */
    Rectangle(offscreen_DC,
        0, 0, GP142_XMAX*2+1, GP142_YMAX*2+FUDGE); 
    SelectObject(offscreen_DC, hOldBrush);
    DeleteObject(hBrush);
#elif defined(X11R6)
    XGCValues gc_val;
    GC gc_clear;
    
    gc_clear = XCreateGC(display, window, 0, &gc_val);
    XSetForeground(display, gc_clear, WhitePixel(display, screen));
    XFillRectangle(display, offscreen_buffer, gc_clear, 0, 0, 
                    GP142_XMAX*2, GP142_YMAX*2);
#endif  

    need_redraw = 1;
}


/******************************************** Graphics Output function ***/
#ifdef MACINTOSH
static void 
Draw_Graphic_Item(Graphics *item)
{
    GDHandle oldGD;
    GWorldPtr oldGWorld;
    PolyHandle poly;
    Rect r;
    int color;
    RGBColor savecolor;
    int width;
    int done, j, line, total, length;
    char *s;
    FontInfo fontInfo;

    /* Save the old graphics world */
    GetGWorld(&oldGWorld, &oldGD);

    /* Grab the offscreen graphics world buffer, and set it as the current world */
    LockPixels(gGP142World->portPixMap);
    SetGWorld(gGP142World, nil);

    color = Legalize_Color(item->color); /* just in case...*/
    if (color == 0 || gColorFlag == 0)
        PenPat(&qd.black);
    else
        PenPixPat(color_pp[color]);
    width = item->width;
    PenSize(width, width);
    switch (item->obj_type) {
    case obj_triangle:
        /* triangles are very strange beasts.  That is, they are polygons, so they don't
        behave _exactly_ like rectangles or ovals, which are bound by rects.  The problem
        has been that filled triangles aren't including their edges.  The easiest thing 
        to fix this is to explicitly draw the frame of the triangle whenever the width
        is 0.  To do this, we simply change the pen size to 1x1 if the the width is 0, 
        and _always_ draw the frame.  This seems to be working, though I haven't done
        much testing yet... */
        poly = OpenPoly();
        MoveTo(gXCenter+item->g.triangle.p1.x-width/2,
            gYCenter-item->g.triangle.p1.y-width/2);
        LineTo(gXCenter+item->g.triangle.p2.x-width/2,
            gYCenter-item->g.triangle.p2.y-width/2);
        LineTo(gXCenter+item->g.triangle.p3.x-width/2,
            gYCenter-item->g.triangle.p3.y-width/2);
        LineTo(gXCenter+item->g.triangle.p1.x-width/2,
            gYCenter-item->g.triangle.p1.y-width/2);
        ClosePoly();

        if (width == 0)
            {
                if (gColorFlag)
                    FillCPoly(poly, color_pp[color]);
                else
                    PaintPoly(poly);
                PenSize(1,1);  /* force a thin outline */
            }
        FramePoly(poly);
        KillPoly(poly);
        break;
        
    case obj_rectangle:
        /* As of v1.4 to v1.5, I (Corey) have realized that we have a major inconsistency.
        That is, all the GP142 functions which require a bounding box expect the coords 
        for those boxes in Upper-Left, Lower-Right order.  The GP142.h file describes these
        functions as taking first the Lower-Left, then Upper-right coords.  Luckily, every-
        thing is symmetric about the X and Y midpoint lines.  But it is just terribly 
        confusing for maintaing the code.  This problem also persists to the WIndows 
        version. Oh, how I wish that I had found this error when going from v1.3 to v1.4.
        Then, I could have corrected everything, and no one would have needed to change
        any of their GP142 application code.  Ah, well.  */

        /* left top right bottom! */
        SetRect(&r,
            gXCenter+item->g.rectangle.upper_left.x-width/2,
            gYCenter-item->g.rectangle.upper_left.y-width/2,
            gXCenter+item->g.rectangle.lower_right.x+width/2 +1,
            gYCenter-item->g.rectangle.lower_right.y+width/2 +1);
        if (width == 0)
            if (gColorFlag)
                FillCRect(&r, color_pp[color]);
            else
                PaintRect(&r);
        else
            FrameRect(&r);
        break;
        
    case obj_oval:
        SetRect(&r,
            gXCenter+item->g.oval.upper_left.x-width/2,
            gYCenter-item->g.oval.upper_left.y-width/2,
            gXCenter+item->g.oval.lower_right.x+width/2 +1,
            gYCenter-item->g.oval.lower_right.y+width/2 +1);
        if (width == 0)
            if (gColorFlag)
                FillCOval(&r, color_pp[color]);
            else
                PaintOval(&r);
        else
            FrameOval(&r);
        break;
        
    case obj_line:
        MoveTo( gXCenter+item->g.line.upper_left.x-width/2,
                gYCenter-item->g.line.upper_left.y-width/2);
        LineTo( gXCenter+item->g.line.lower_right.x-width/2,
                gYCenter-item->g.line.lower_right.y-width/2);
        break;
        
    case obj_pixel:
        PenSize(1,1);
        MoveTo( gXCenter+item->g.pixel.p.x,
                gYCenter-item->g.pixel.p.y );
        LineTo( gXCenter+item->g.pixel.p.x,
                gYCenter-item->g.pixel.p.y );
        break;
        
    case obj_text:
        if (gColorFlag) {
            GetForeColor(&savecolor);
            if (color != 0)
                RGBForeColor(&gRGBColors[color]);
        }
        
        TextSize(item->g.text.ptsize);

        GetFontInfo(&fontInfo);

        /* We want to honor newline characters in the string by
        advancing the current line some height */
        
        done = FALSE;
        s = item->g.text.the_text;
        total = 1; /* skip over the pascal length byte */
        length = s[0];
        line = 0;
        while (done != TRUE)
            {
                for (j=0; s[total+j] != '\n' && s[total+j] != '\0'
                            && total+j <= length; j++)
                ;
                if (total+j >= length || s[total+j] == '\0')
                    done = TRUE;
                
                MoveTo( gXCenter+item->g.text.p.x,
                        gYCenter-item->g.text.p.y + 
                            line*(fontInfo.ascent + 
                                    fontInfo.descent + 
                                    fontInfo.leading));
                DrawText(s, total, j);
                
                line++;
                total += j+1;
            }

        if (gColorFlag)
            RGBForeColor(&savecolor);
        break;
    }
    

    SetGWorld(oldGWorld, oldGD);
    UnlockPixels(gGP142World->portPixMap);

    need_redraw = 1;
}



#elif defined(WINDOWS)

/* The idea here is to actually to the drawing of the object.  In fact,
when the DrawWndProc() recieves a WM_PAINT message, it will simply loop
through the graphics database, calling Draw_Graphic_Item().  For that
reason, we don't want to make any Windows API calls that may generate
a WM_PAINT message in the graphics window! */ 
static void FAR Draw_Graphic_Item(Graphics *item)
{
    HBRUSH hBrush, hOldBrush;
    HPEN hPen, hOldPen;
    HFONT hFont, hOldFont;
    POINT pTriPoints[3];
    LPSTR pStr;
    SIZE textSize;
    int done, j, line, total, length, iPrevBackMode;

    switch (item->obj_type)
        {
            case obj_pixel:
                SetPixel(offscreen_DC,
                    gXCenter + item->g.pixel.p.x,
                    gYCenter - item->g.pixel.p.y,
                    gRGBColors[item->color]);
                break;

            case obj_line:
                /* If we were using Windows NT, we could call ExtCreatePen,
                which would allow for square endcaps of lines.  Alas, we're
                stuck with Windows 3.1, with round endcaps.  Ah, well. */
                hPen = CreatePen(PS_SOLID,
                    item->width,
                    gRGBColors[item->color]);
                /* we want to hold on to the old pen to reset it
                after we're done here */
                hOldPen = SelectObject(offscreen_DC, hPen);


#ifdef WIN32
                MoveToEx(offscreen_DC,
                    gXCenter + item->g.line.upper_left.x,
                    gYCenter - item->g.line.upper_left.y,
                    NULL);
#else
                MoveTo(offscreen_DC,
                    gXCenter + item->g.line.upper_left.x,
                    gYCenter - item->g.line.upper_left.y);
#endif
                LineTo(offscreen_DC,
                    gXCenter + item->g.line.lower_right.x,
                    gYCenter - item->g.line.lower_right.y);

                SelectObject(offscreen_DC, hOldPen);
                DeleteObject(hPen);
                break;

            case obj_triangle:
                hPen = CreatePen(PS_SOLID,
                    item->width,
                    gRGBColors[item->color]);
                hOldPen = SelectObject(offscreen_DC, hPen);

                /* copy the triangle points into a different array */
                pTriPoints[0].x = gXCenter + item->g.triangle.p1.x;
                pTriPoints[0].y = gYCenter - item->g.triangle.p1.y;
                pTriPoints[1].x = gXCenter + item->g.triangle.p2.x;
                pTriPoints[1].y = gYCenter - item->g.triangle.p2.y;
                pTriPoints[2].x = gXCenter + item->g.triangle.p3.x;
                pTriPoints[2].y = gYCenter - item->g.triangle.p3.y;

                if (item->width == 0)
                    hBrush = CreateSolidBrush(gRGBColors[item->color]);
                else
                    hBrush = GetStockObject(HOLLOW_BRUSH);
                hOldBrush = SelectObject(offscreen_DC, hBrush);

                Polygon(offscreen_DC, pTriPoints, 3);

                SelectObject(offscreen_DC, hOldPen);
                SelectObject(offscreen_DC, hOldBrush);
                DeleteObject(hPen);
                DeleteObject(hBrush);
                break;

            case obj_rectangle:
                hPen = CreatePen(PS_SOLID,
                    item->width,
                    gRGBColors[item->color]);
                /* if width == 0, fill in rectangle */
                if (item->width == 0)
                    hBrush = CreateSolidBrush(gRGBColors[item->color]);
                else /* leave rectangle hollow */
                    hBrush = GetStockObject(HOLLOW_BRUSH);

                hOldPen = SelectObject(offscreen_DC, hPen);
                hOldBrush = SelectObject(offscreen_DC, hBrush);

                /* Windows draws lines in a very odd fashion.  Windows 
                will include the first endpoint when drawing a line, but
                _exclude_ the next endpoint.  I gather that this allows
                for poly-lines, but very strange things happen when you
                draw single lines this way.  That is why we add 1 to the
                ending x and y coords in the rectangle, oval, etc. */
                Rectangle(offscreen_DC,
                    gXCenter + item->g.rectangle.upper_left.x,
                    gYCenter - item->g.rectangle.upper_left.y,
                    gXCenter + item->g.rectangle.lower_right.x+1,
                    gYCenter - item->g.rectangle.lower_right.y+1);

                SelectObject(offscreen_DC, hOldPen);
                SelectObject(offscreen_DC, hOldBrush);
                DeleteObject(hPen);
                DeleteObject(hBrush);
                break;

            case obj_oval:
                hPen = CreatePen(PS_SOLID,
                    item->width,
                    gRGBColors[item->color]);
                /* if width == 0, fill in rectangle */
                if (item->width == 0)
                    hBrush = CreateSolidBrush(gRGBColors[item->color]);
                else /* leave rectangle hollow */
                    hBrush = GetStockObject(HOLLOW_BRUSH);

                hOldPen = SelectObject(offscreen_DC, hPen);
                hOldBrush = SelectObject(offscreen_DC, hBrush);

                Ellipse(offscreen_DC,
                    gXCenter + item->g.oval.upper_left.x,
                    gYCenter - item->g.oval.upper_left.y,
                    gXCenter + item->g.oval.lower_right.x+1,
                    gYCenter - item->g.oval.lower_right.y+1);

                SelectObject(offscreen_DC, hOldPen);
                SelectObject(offscreen_DC, hOldBrush);
                DeleteObject(hPen);
                DeleteObject(hBrush);
                break;

            case obj_text:
                /* Text will be drawn on multiple lines, according to
                where newline characters appear. */
                /* Text is special in Windows.  Text color is set with
                a special function, as opposed to the current pen
                color.  Go figure! */
                SetTextColor(offscreen_DC, gRGBColors[item->color]);
                /* added by P. Schimpf, v 2.02*/
                iPrevBackMode = GetBkMode(offscreen_DC) ;
                SetBkMode(offscreen_DC, TRANSPARENT) ;

                /* Windows gives us a default font, but the only way
                to specify a particular point size is to create a
                new font. */        
                /* the negative number indicates point size as opposed
                to pixel size */
                hFont = CreateFont(-item->g.text.ptsize,
                    0,          /* let Windows choose width */
                    0,          /* escapement, in 10ths of degrees */
                    0,          /* orientation, in 10ths of degrees */
                    FW_NORMAL,  /* normal weight */
                    FALSE,      /* no italic */
                    FALSE,      /* no underline */
                    FALSE,      /* no strikeout */
                    ANSI_CHARSET,   /* use ANSI character set */
                    OUT_DEFAULT_PRECIS, /* output precision */
                    CLIP_DEFAULT_PRECIS,    /* clip precision */
                    DEFAULT_QUALITY,    /* quality */
                    DEFAULT_PITCH | FF_DONTCARE,    /* pitch and family */
                    "GP142-font");  /* way-cool name of font */

                hOldFont = SelectObject(offscreen_DC, hFont);

                pStr = GlobalLock(item->g.text.hText);

                /* To be compatible with the Mac, we want to bump the
                text string 'up' by the height of the string */
                GetTextExtentPoint(offscreen_DC,
                    pStr,
                    far_strlen(pStr),
                    &textSize);

#if 1
                /* We want to honor newline characters in the string by
                advancing the current line some height */
        
                done = FALSE;
                total = 0;
                length = far_strlen(pStr);
                line = 0;
                while (done != TRUE)
                    {
                        for (j=0; pStr[total+j] != '\n' && 
                                    pStr[total+j] != '\0' &&
                                    total+j <= length; j++);
                        if (total+j >= length || pStr[total+j] == '\0')
                            done = TRUE;
                
                        TextOut(offscreen_DC,
                            gXCenter + item->g.text.p.x,
                            gYCenter - item->g.text.p.y + 
                                (line-1)*textSize.cy,
                            pStr + total, j);

                        line++;
                        total += j+1;
                    }
#else
                TextOut(offscreen_DC,
                    gXCenter + item->g.text.p.x,
                    gYCenter - item->g.text.p.y - textSize.cy,
                    pStr,
                    far_strlen(pStr));
#endif
                GlobalUnlock(item->g.text.hText);

                SetBkMode(offscreen_DC, iPrevBackMode) ;
                SelectObject(offscreen_DC, hOldFont);
                DeleteObject(hFont);
                break;
        }
    need_redraw = 1;
}

#elif defined(X11R6)

static void Draw_Graphic_Item(Graphics *item) {

   int j, total, line, length, done;
   char *s;

   if (current_color_id != item->color) {
      XSetForeground(display, gc, color_ids[item->color].pixel);
      current_color_id = item->color;
   }

   switch (item->obj_type)
      {
         case obj_pixel:
            XDrawPoint(display, offscreen_buffer, gc,
               gXCenter + item->g.pixel.p.x,
               gYCenter - item->g.pixel.p.y);
            break;

         case obj_triangle:
            XSetLineAttributes(display, gc, item->width, LineSolid,
                 CapRound, JoinRound);
            if (item->width==0) {
               XPoint points[3];
               points[0].x = gXCenter+item->g.triangle.p1.x;
               points[0].y = gYCenter-item->g.triangle.p1.y;
               points[1].x = gXCenter+item->g.triangle.p2.x;
               points[1].y = gYCenter-item->g.triangle.p2.y; 
               points[2].x = gXCenter+item->g.triangle.p3.x;
               points[2].y = gYCenter-item->g.triangle.p3.y;
               XFillPolygon(display, offscreen_buffer, gc, points, 3, 
                                             Convex, CoordModeOrigin);
            }

            else
               XDrawLine(display, offscreen_buffer, gc,
                  gXCenter+item->g.triangle.p1.x,
                  gYCenter-item->g.triangle.p1.y,
                  gXCenter+item->g.triangle.p2.x,
                  gYCenter-item->g.triangle.p2.y);
               XDrawLine(display, offscreen_buffer, gc,
                  gXCenter+item->g.triangle.p2.x,
                  gYCenter-item->g.triangle.p2.y,
                  gXCenter+item->g.triangle.p3.x,
                  gYCenter-item->g.triangle.p3.y);
               XDrawLine(display, offscreen_buffer, gc,
                  gXCenter+item->g.triangle.p3.x,
                  gYCenter-item->g.triangle.p3.y,
                  gXCenter+item->g.triangle.p1.x,
                  gYCenter-item->g.triangle.p1.y);
            break;


/* It's a conspiracy. The same problem with excluding the second
 * (lower right) endpoint happens in X too for _filled rectangles_. 
 * Similar solution used, adding 1 to the height and width of the 
 * filled rectangle drawn.  */
  
         case obj_rectangle:
            XSetLineAttributes(display, gc, item->width, 
                                   LineSolid, CapRound, JoinRound);
            if (item->width==0)
               XFillRectangle(display, offscreen_buffer, gc,
                  gXCenter+item->g.rectangle.upper_left.x,
                  gYCenter-item->g.rectangle.upper_left.y,
                  item->g.rectangle.lower_right.x
                        -item->g.rectangle.upper_left.x+1,
                  item->g.rectangle.upper_left.y
                        -item->g.rectangle.lower_right.y+1);
            else
               XDrawRectangle(display, offscreen_buffer, gc,
                  gXCenter+item->g.rectangle.upper_left.x,
                  gYCenter-item->g.rectangle.upper_left.y,
                  item->g.rectangle.lower_right.x
                        -item->g.rectangle.upper_left.x,
                  item->g.rectangle.upper_left.y
                        -item->g.rectangle.lower_right.y);
            break;

        case obj_line:
            XSetLineAttributes(display, gc, item->width, 
                                     LineSolid, CapRound, JoinRound);
            XDrawLine(display, offscreen_buffer, gc,
                gXCenter+item->g.line.upper_left.x,
                gYCenter-item->g.line.upper_left.y,
                gXCenter+item->g.line.lower_right.x,
                gYCenter-item->g.line.lower_right.y);
            break;

        case obj_oval:
            XSetLineAttributes(display, gc, item->width, LineSolid,
                 CapRound, JoinRound);
            if (item->width==0)
               XFillArc(display, offscreen_buffer, gc,
                    gXCenter+item->g.oval.upper_left.x,
                    gYCenter-item->g.oval.upper_left.y,
                    item->g.oval.lower_right.x
                          -item->g.oval.upper_left.x,
                    item->g.oval.upper_left.y
                          -item->g.oval.lower_right.y,
                    0, 23360);
            else

                /* The 23360 is 365 (degrees) * 64; the angles are signed ints
                 * in 64ths of a degree. I put 365 degrees for good measure -- it
                 * automatically truncates anything past 360.  */
  
               XDrawArc(display, offscreen_buffer, gc, 
                    gXCenter+item->g.oval.upper_left.x, 
                    gYCenter-item->g.oval.upper_left.y, 
                    item->g.oval.lower_right.x
                          -item->g.oval.upper_left.x,
                    item->g.oval.upper_left.y
                          -item->g.oval.lower_right.y,
                    0, 23360);
            break;

        case obj_text:

           /* Check to see if the requested font is currently loaded;
            * if not, search the list and point temp at it if it's there.
            */        
 
           if (item->g.text.ptsize != current_font->point_size) {

              FontDB *temp = font_info;

              while (temp) {
                 if (item->g.text.ptsize == temp->point_size)
                    break;
                 temp = temp->next;
              }

              /* Or else add it to the list and load it.  */

              if (!temp) {
                 char fontname[100];
                 temp = (FontDB*) malloc(sizeof(FontDB));
                 sprintf(fontname, "-adobe-helvetica-medium-r-normal--0-%d-75-75-p-0-iso8859-1", item->g.text.ptsize * 10);
                 if ((temp == NULL) ||
                     (temp->thefont = XLoadQueryFont(display, 
                                               fontname)) == NULL) {
                    fprintf(stderr, "Cannot open Adobe scalable font.\n");
                    exit(0);
                 }

                 /* Set font to requested point size and put node at  
                  * the head of the list.  */

                 temp->point_size = item->g.text.ptsize;
                 temp->next = font_info;
                 font_info = temp;
              }

              /* Set gc to new point size */

              XSetFont(display, gc, temp->thefont->fid);
              current_font = temp;
           }

          /* We want to honor newline characters in the string by
          advancing the current line some height */
          
           line = 0, total = 0;
           done = FALSE;
           s = item->g.text.the_text;
           length = strlen(s);
           while (done != TRUE) {
               
                   for (j = 0; s[total + j] != '\n' && s[total + j] != '\0'
                               && total + j <= length; j++);

                   if (total + j >= length || s[total + j] == '\0')
                       done = TRUE;
                   
                   XDrawString(display, offscreen_buffer, gc,
                      gXCenter+item->g.text.p.x,
                      gYCenter-item->g.text.p.y +
                           line*(current_font->thefont->ascent+
                                 current_font->thefont->descent),
                                                        s+total ,j);
                   line++;
                   total += j + 1;
           }
           break;
      }
   need_redraw = 1;
}

#endif

/* Show or hide the GP142 text window - zives 6/19/98 */
void GP142_show_text(int showit) 
{
#ifdef WINDOWS
    ShowWindow(hTextWnd, (showit) ? SW_SHOW : SW_HIDE);
#else
	showit = 0; /* HACK: kill compiler warnings */
#endif
}
