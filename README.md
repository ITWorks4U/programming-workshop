#	programming workshop with C and Python
-	written examples, like:
	-	(double) linked lists
	-	binary trees
	-	AVL trees
	-	backtracking
	-	...

-	allows you to take an overview how to write algorithms in C and / or Python
-	these code projects are well made for hobby projects, educational studying, ...

##	build and run
######	C programming
> Linux / macos:
-	run the makefile by using: ```make```
-	the executable file ends with *.run

> Windows:
-	run build.bat or build.ps1 with an argument of "build" or "clean"
	-	it may happen, that the batch file won't create your compiled application, depending on the Windows security settings itself
	-	by using the powershell script make sure, that a powershell script can be run on your system
		-	bypass the restriction with this command, if required, which is active until the windows session ends:
		-	```Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass```
-	the executable file ends with *.exe

######	Python programming
-	these codes are written with Python 3 (at least with version 3.10)
-	just run the python interpreter
	-	**UNIX/Linux**: ```python3 main.py```
	-	**Windows**: ```python.exe main.py```