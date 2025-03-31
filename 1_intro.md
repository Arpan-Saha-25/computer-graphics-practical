## Basic GLUT Initialization

```cpp
glutInit();  // Initialize GLUT
glutCreateWindow("Title of the window");
glutDisplayFunc(lineSegment);

glutMainLoop();  // Completes window processing operations. This function must be the last one in the program.
```

### Set Initial Window Position

We use the `glutInitWindowPosition` function to set the initial location for the upper-left corner of the display window.

```cpp
/* The upper-left corner of the display window should be placed 50 pixels
   to the right of the left edge of the screen and 100 pixels down from 
   the top edge of the screen: */
glutInitWindowPosition(50, 100);
```

### Set Background Color for the Display Window

To set the background color for the display window, we use the following code:

```cpp
glClearColor(1.0, 1.0, 1.0, 0.0);  // White (rgba)
```

To apply the assigned background color to the window, we need to invoke the following OpenGL function:

```cpp
glClear(GL_COLOR_BUFFER_BIT);
```

The `GL_COLOR_BUFFER_BIT` is an OpenGL symbolic constant that specifies that the bit values in the color buffer (refresh buffer) should be set to the values indicated in the `glClearColor` function.

### Set Object Color

We can choose a variety of color schemes for the objects we want to display in a scene. For our initial programming example, we will set the object color to dark green.

```cpp
glColor3f(0.0, 0.4, 0.2);  // Dark green
```

The `3f` suffix on the `glColor` function indicates that we are specifying the three RGB color components using floating-point (`f`) values. The values must be in the range from 0.0 to 1.0, and in this case, we have set:

- Red = 0.0
- Green = 0.4
- Blue = 0.2

### Switch to 2D Mode

OpenGL always displays objects in a 3D space. To make the display 2D, we need to use the special case of 3D.

```cpp
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0.0, 200.0, 0.0, 150.0);  // 0 to 200 in x, 0 to 150 in y
```

This code sets the orthographic projection, defining the 2D view window's boundaries. The x-axis will range from 0 to 200, and the y-axis from 0 to 150.