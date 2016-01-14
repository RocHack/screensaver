// from http://www.dis.uniroma1.it/~liberato/screensaver/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xproto.h>

#include "vroot.h"

#define NCOLORS 3
#define NUMPROGRAMS 28

int getWinFromEnv() {
    char *s, *end;
    long w;

    // Read environment var
    s = getenv("XSCREENSAVER_WINDOW");
    if (!s || !*s) {
	printf("No env\n");
        return -1;
    }

    // Scan as int
    w = strtol(s, &end, 0);
    if (*end) {
	printf("Bad value: %s\n", s);
        return -1;
    }

    return w > INT_MAX ? -1 : (int)w;
}

int main(int argc, char **argv) {
    srand(time(NULL));
    Display *dpy;
    Window root;
    XWindowAttributes wa;
    GC g;
    char *progclass = "java screensaver";

    Font f;
    XFontStruct *fs;
    XGCValues v;

    // from http://stackoverflow.com/questions/7684359/using-nanosleep-in-c
    const struct timespec *tim = (const struct timespec[]) { {0, 100000000L} };
    const struct timespec *endtim = (const struct timespec[]) { {2, 0} };

    char *colors[NCOLORS] = { "red", "green", "blue" };
    XColor xcolors[NCOLORS];
    XColor xc, sc;
    int x, y;
    int c;

    /* open the display (connect to the X server) */
    XtAppContext app;
    Widget app_App;

    app_App = XtAppInitialize(&app, progclass, NULL, 0, &argc, argv, NULL, 0, 0);
    dpy = XtDisplay(app_App);

    /* get the root window */
    root = getWinFromEnv();
    printf("envroot: %d\n", root);
    if (root == -1)
	root = RootWindowOfScreen(XtScreen(app_App));
    printf("root: %d\n", root);

    /* get attributes of the root window */
    XGetWindowAttributes(dpy, root, &wa);\

    /* create a GC for drawing in the window */
    g = XCreateGC(dpy, root, 0, NULL);

    /* load a font */
    f = XLoadFont(dpy, "-*-helvetica-bold-r-*-*-20-*-*-*-*-*-*-*");
    XSetFont(dpy, g, f);

    /* get font metrics */
    XGetGCValues(dpy, g, GCFont, &v);
    fs = XQueryFont(dpy, v.font);

    /* allocate colors */
    for (c = 0; c < NCOLORS; c++) {
	XAllocNamedColor(dpy, DefaultColormapOfScreen(DefaultScreenOfDisplay (dpy)), colors[c], &sc, &xc);
	xcolors[c] = sc;
    }

    /* draw something */
    x = 0;
    y = fs->ascent;

    /* set a random foreground color */
    XSetForeground(dpy, g, xcolors[random() % NCOLORS].pixel);

    char s;
    while ((s = fgetc(stdin)) != EOF) {
	char *string;
	char buf[2];
	buf[1] = '\0';

	// check for newline
	if (s == '\n') {
	    x = 0;
	    y = y + fs->ascent + fs->descent;
	    continue;
	}

	// check for tab character
	if (s == '\t') {
	    string = "    ";
	} else {
	    string = buf;
	    string[0] = s;
	}

	/* draw the string */
	XDrawString(dpy, root, g, x, y, string, strlen(string));

	/* increase x and y */
	x = x + XTextWidth(fs, string, strlen(string));

	if (x > wa.width) {
	    x = 0;
	    y = y + fs->ascent + fs->descent;
	}

	if (y - fs->ascent > wa.height) {
	    XClearWindow(dpy, root);
	    x = 0;
	    y = fs->ascent;
	}

	/* flush changes and sleep */
	XFlush(dpy);
	nanosleep(tim, NULL);
    }

    nanosleep(endtim, NULL);
    XClearWindow(dpy, root);

    XCloseDisplay(dpy);
}
