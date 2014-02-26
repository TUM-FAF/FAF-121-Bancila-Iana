Windows Programming Laboratory Work #1
======================================

Title
-----
Window. Window handling. Basic window’s form elements.

Introduction
------------
Purpose
*	Event-driven programming (message-oriented)
*	API
*	Windows applications development

Additional Purposes
*	Version Control Systems (GIT)
*	Programming Style Guidelines
*	Debugging
*	Testing

Mandatory Objectives
--------------------
*	Create a Windows application
*	Choose Programming Style Guidelines that you'll follow
*	Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
*	Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
*	Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)

Objectives with Points
----------------------
*	Make elements to fit window on resize. **(1 pt.)**
*	Make elements to interact or change other elements. **(2 pt.)**
*	Change behavior of different window actions (at least 3). **(1 pt.)**

Application Creation Steps
--------------------------
*	For present app I’ve tried, really, I’ve read almost all chapters from the recommended book (["Programming Windows, 5th Edition", by Charles Petzold](http://www.charlespetzold.com/pw5/)) in order to understand how to develop my ideas in such a way as to be understood not only by me. During the process I consult the documentation on the [MSDN](http://msdn.microsoft.com) page and [Win32 Tips & Tricks] (http://www.catch22.net/tuts/win32-tips-tricks#ResizeNoMove).
*	I checked if the exact project I’m considering has not been done before.
*	The application first of all is about my favorite animals: cats and dogs. I would like people to make the difference between these two types of animals. So, application has one text label, 5 buttons which are very important ( CAT button, DOG button, BUY button, ADD and CLEAR buttons), one field input, and two header titles ( My name and surname, and the number of laboratory work).
*	For this laboratory work (and for future personal projects), I used C style guide.
*	The UI elements are mixed and different, they have different sizes and fonts, different styles.
*	In order to understand more clearly I made a wireframe model of my application general layout and functionality using paint. Here is the mockup I came up with:

1.	Read-only multiline text label, with vertical scrollbar which keeps the information and added topics.
2.	After pressing the Minimize (or Maximize) button will appear a message box, but will not minimize (or maximize) the window.
3.	Pressing the Close button the user will be prompted if he (or she) is sure that he (or she) wants to close the window.
4.	Add the text written in the field input on the text label.
5.	Clear the text label.
6.	The field input is made in HTML5 placeholder form. The placeholder text is the grey text that you find in an input field that is used to give a hint to the users on what input is expected in that field. Once users start typing in the input field, the placeholder text will disappear.
7.	Pressing the BUY button the user will be asked to specify what type of animal he (or she) wants to buy.
8.	Pressing the CAT button the user will take the available information about cats, all facts and arguments.
9.	Pressing the DOG button the user will take the available information about dogs, all facts and arguments.
10.	The Window’s Title.

![mockup] (https://raw.github.com/TUM-FAF/FAF-121-Bancila-Iana/master/WP/Lab%231/mockup.png)

Result Application
------------------
This is a screen shot of the application in the virtual Windows 7 environment:

![appimg] (https://raw.github.com/TUM-FAF/FAF-121-Bancila-Iana/master/WP/Lab%231/appimg.png)

Conclusions
-----------
  Well, I can say that it was my first serious laboratory work based on C++ language, and I enjoyed executing it. What I have learned from this lab is that in a graphical Windows-based application, a window is a rectangular area of the screen where the application displays output and receives input from the user. Therefore, one of the first tasks of a graphical Windows-based application is to create a window. A window shares the screen with other windows, including those from other applications. Only one window at a time can receive input from the user. The user can use the mouse, keyboard, or other input device to interact with this window and the application that owns it.
The main concepts of the event-driven programming are clear for me, so, from this point of view I haven't issues.
I think that this laboratory work was very important, because it laid a good foundation, on which to build upon. 

