Windows Programming Laboratory Work #2
======================================

Title
-----
Advanced Form Elements. Child Windowses. Basics of Working With Keyboard.

Contents
--------
- The Keyboard
- Child Window Controls
  - Scroll Bar
  - Listbox
- Menus and Other Resources
- Dialog Boxes

Mandatory Objectives (completed)
--------------------------------
- Display a dialog box on some event.
- Add a system menu to your application with at least 3 items.
- Add a scroll bar that will change any visible parameter of any other element.
- Hook keyboard input. Add 2 custom events for 2 different keyboard combinations.

Objectives With Points (completed)
----------------------------------
- Add a listbox and attach some events when any element is accessed (double-clicked). **(2 pt)**
- Add 2 scroll bars that will manage main window size or position. **(1 pt)**
- Customize your application by adding an icon and using different cursor in application. **(1 pt)**
- Use a scroll bar to scroll through application working space. Scroll should appear only when necessary. **(1 pt)**

Application Creation Steps
--------------------------
*	For present app I’ve read almost all chapters from the recommended book (["Programming Windows, 5th Edition", by Charles Petzold](http://www.charlespetzold.com/pw5/)) in order to understand how to develop my ideas in such a way as to be understood not only by me. During the process I consult the documentation on the [MSDN](http://msdn.microsoft.com) page and [Win32 Tips & Tricks] (http://www.catch22.net/tuts/win32-tips-tricks#ResizeNoMove).
*	I checked if the exact project I’m considering has not been done before.
*	This application proceed the same topic “Cats & Dogs”. So, application has one text label, one field input, here I add 5 buttons ( CAT button, DOG button, ADD button, REMOVE and CLEAR buttons), two static labels, two scrollbars (which change the height and the width of the window), two traversal scrollbars, the main menu (file, view, help).
*	In order to understand more clearly I made a wireframe model of my application general layout and functionality using paint. Here is the mockup I came up with:

![mockup] (https://raw.github.com/TUM-FAF/FAF-121-Bancila-Iana/master/WP/Lab%232/Images/mockup.png)

![AboutBoxMockup] (https://raw.github.com/TUM-FAF/FAF-121-Bancila-Iana/master/WP/Lab%232/Images/AboutBoxMockup.png)

Result Application
------------------
These are the screenshots of the application in the virtual Windows 7 environment: 

![screenshot1] (https://raw.github.com/TUM-FAF/FAF-121-Bancila-Iana/master/WP/Lab%232/Images/screenshot1.png)

![screenshot2] (https://raw.github.com/TUM-FAF/FAF-121-Bancila-Iana/master/WP/Lab%232/Images/screenshot2.png)

![AboutBox] (https://raw.github.com/TUM-FAF/FAF-121-Bancila-Iana/master/WP/Lab%232/Images/AboutBox.png)

Conclusions
-----------
Well, this laboratory work was very addictive because I’ve tried to manage all the features as good as possible. Although I experienced some issues working with scrollbars (they work with some delay). 

I was impressed how rapidly I understood almost all concepts of manipulation of keyboard, dialog boxes, listboxes and menus. Another topics I covered either using additional documentation or asking my colleagues. 

It was challenging to complete all the tasks, I really enjoyed performing all of them. For me it’s new experience and it improve my skills as programmer.  I think there are a little bit space for improvements, and I'll make them as soon as possible. This laboratory work broadened and deepened my understanding of Event-Driven Programming, message-sending, and Win32 API in particular. 

