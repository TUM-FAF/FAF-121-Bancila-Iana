Windows Programming
=====================
#Laboratory Work #3
###### student of FAF-121 gr.: IANA Bancila

##Topic: Basics of Working with Mouse. GDI Primitives. Bezier Curve.

Contents
--------
* Mouse
* Device context
* GDI Primitives
  * Line
  * Curve
  * Plane
  * Bitmap image
* Bezier curve

Mandatory Objectives
--------------------
* Draw few lines of different colors and weights
* Draw a Bezier curve
* Draw few plane objects (ex. circle, square, pie, polygon...) of different colors, weights, filled and not
* Draw 2 different objects using mouse

Completed Objectives With Points
-----------------------------------
* Draw a custom bitmap image **(1 pt)**
* Add a switch (button, select list...) that will change mouse ability to draw objects **(2 pt)**
* Draw a Bezier curve using mouse **(1 pt)**
* Fill an object with a gradient **(1 pt)**
* Use mouse as an eraser of a adjustable width **(2 pt)**

Application Creation Steps
--------------------------
*	First of all I've sketched my laboratory work on a paper. Designed all the buttons elements to control the drawing. After that I've added the elements. Then I've set their functionality step by step. And in the end I've added the properties to draw stuff.
*	In order to understand more clearly I made a wireframe model of my application general layout and functionality. Here is the mockup I came up with:

![mokup] (https://raw.github.com/TUM-FAF/FAF-121-Bancila-Iana/master/WP/Lab%233/Images/mockup.png)

1.	Rectangle filled with gradient.
2.	The drawing area.
3.	The configuration variables, such as:
   *	Custom rectangle that will stand for color picking. I used ChooseColor Dialog Box.
   *	Text field used for border and eraser width.
4.	Tools and Shapes which we will use in order to draw, such as:
   *	**Pencil** tool will draw a continuous line with the stroke weight equal to 1, and the selectable stroke color and weight by selecting this tool, and left-clicking on the drawing area.
   *	**Rubber** tool will erase the drawing area, with a selectable weight.
   *	**Line** tool will draw a straight line between two points, with the selectable stroke weight and color and dragging & releasing the mouse button.
   *	**Ellipse** tool will draw an ellipse, with selectable stroke weight and color, filled with a selectable color, or not, and dragging & releasing the mouse button.
   *	**Rectangle** tool will draw a rectangle, with selectable stroke weight and color, filled with a selectable color, or not, and dragging & releasing the mouse button.
   *	**Bezier curve.** You can draw Bezier curve using mouse, just click and drag two times and you're done.
5.	Custom bitmap image.

Result Application
------------------
This is the screenshot of the application in the virtual Windows 8.1 environment: 

![Application] (https://raw.github.com/TUM-FAF/FAF-121-Bancila-Iana/master/WP/Lab%233/Images/Application.png)

Conclusions
-----------

Well, this laboratory work was very addictive because I’ve tried to manage all the features as good as possible. But I didn’t manage all of them because of limited time. Although I experienced some issues when I had to draw an ellipse or rectangle, or even a line (you can’t see those plane object until you will finish). 

In this laboratory work I familiarized myself with all the drawing possibilities the Windows API gives us, and with the right way of working with the mouse, and letting the user control the application features using mouse clicks. 

It was challenging to complete the tasks, I really enjoyed performing them. For me it’s a new experience and it improve my skills as programmer.  I think there are a little bit space for improvements, and I'll make them as soon as possible. This laboratory work broadened and deepened my understanding of Event-Driven Programming, message-sending, and Win32 API in particular. 


