Modules in project: 

	RayVect (rayvect.hpp, rayvect.cpp)
		The RayVect module defines a 3d vector class and the basic operations needed for 
        manipulation thereof.
        
	SceneObjects (sceneobjects.hpp, sceneobjects.cpp)
		The SceneObjects module defines Object, Sphere, Plane, and Light classes in 
        order to represent all values in the scene, as well as operations on those classes. 
        The functions that test for ray intersection are class members of Sphere and Plane. 
        Sphere and Plane are derived from the Object class for ease of use in other parts 
        of the program, and share multiple functions.
        
	Parse (parse.hpp, parse.cpp)
		The Parse module creates an internal representation of the scene in the provided 
        JSON file. This module also checks for input syntax/value errors. The previous two 
        modules, RayVect and SceneObjects, contain the classes that comprise the internal 
        representation of the scene.
        
	Render (render.hpp, render.cpp)
		The Render module is where the main work of tracing a scene takes place. This module 
        sends a ray through each pixel in the image, determines the closest point of intersection, 
        and shades the pixel based on the object color and the lights/shadows in the scene. 
        This can be done with multiple threads, the amount of which is passed in from the command 
        line. Each thread is handed an equivalent portion of the image to trace. Finally, this 
        module writes the pixels to an output file, which was passed as an argument from the 
        command line.
        
	VTRay (vtray.cpp)
		The VTRay module is the command line interface portion of the project. It takes the 
        arguments from the command line, checks for validity, and then calls the modules 
        in order. It also handles output of errors thrown from deeper within the program.
