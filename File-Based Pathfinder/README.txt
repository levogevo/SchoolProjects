-author: Levon Gevorgyan
-This was the final project for Data Structures and Algorithms from Fall 2019, UT Dallas.

-Source files are included in the "Project Files" folder
-To run the program, execute PathFinder.exe with the following 3 arguments
	PathFinder.exe "flightsFile" "pathsFile" "outputFile"
	
	flightsFile is the file path of the raw flights data in the following format
		The first line of flightsFile is the number of following lines.
		Every line after includes a start and end location followed by the cost and then time.
		Each of these different variables is separated by a pipe ('|') character.
		Example of flightsFile.txt:
			3 						//number of following lines
			Dallas|Houston|20|40	//Dallas->Houston takes $20, 40 minutes
			Dallas|Austin|10|30		//Dallas->Austin takes $10, 30 minutes
			Houston|Austin|40|20	//Houston->Austin takes $40, 20 minutes
			
	pathsFile is the file path of the paths the user wants to find.
		The first line of pathsFile is the number of following lines.
		Every line after includes a start and end location followed by either 'C' or 'T'.
		Each of these different variables is separated by a pipe ('|') character.
		Example of pathsFile.txt:
			2					//number of following lines
			Dallas|Houston|T	//find path from Dallas->Houston with shortest time ('T')
			Houston|Austin|C	//find path from Houston->Austin with least cost ('C')
			
	outputFile is the file path of the file where the resulting optimized paths will be stored.
		Only the 3 most optimized paths will be included if there are more than 3 ways to find a path.