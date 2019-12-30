This readme file describes the steps to build GP142.exe on PC's running
MSVC 5.0 and above.  Users of other compilers (including MSVC 4.x) will not 
be able to use the project files contained in this archive.

After running the self-extracting archive, you will find ready made project
and workspace files to build the demo program.  To build the demo:

   1.  Using Explorer, find the directory where you extracted this archive.
   2.  Open MSVC by double clicking GP142demo.dsw.  DO NOT double click the
       .c file and expect this to work.  If you are using MSVC version 6.0
       or above, go ahead and let MSVC convert the project to the newer
       format.
   3.  From the Build menu, select "Build GP142demo.exe".

The general procedure for setting up a project using GP142 from scratch
under MSVC 5.0 is:


   1.Pull down the File menu, and select New... Be sure the Projects tab is 
     selected from the dialog box that pops up. 
   2.Tell MSVC how to create your workspace by filling out the dialog box, making 
     sure to observe the following points: 
        - Select Win32 Application (NOT Win32 Console Application, or anything else). 
        - If you want your files kept in a directory different from the default,
          make that change under Location.  For example, type in c:\junk. Do this 
          before you fill in the project name, even though the project name is listed 
          first. 
        - Under Project Name, enter a name for your project (HW4, for example). 
          Notice that as you type this, the path in the Location box is ammended to 
          read c:\junk\HW4. 
        - Click OK to dismiss the dialog box and create your workspace. 
   3.Move the files gp142.h, gp142lib.h, and gp142.c into the directory that was created
     above (c:\junk\HW4, in this example).  This is also where you put your .c file,
     such as hw4_orig.c.
   4.From Project menu in MSVC, click Add to project and then select Files... You should 
     see gp142.c and your own .c file.  Select them with the mouse and add them to your
     current project by clicking OK (you only need to add the .c files). 
   5.Be sure that your compiler is set to build your project with the debugging 
     information included. To do this, pull down the Build menu and select Set active 
     configuration... Be sure that <your file name> - Win32 Debug is selected, and click OK. 
   6.Build your program by pulling down the Build menu and selecting Build 
     <your file name>.exe. 
