# BMesh Modeler

## Installation

* run the install script : ```bash install```

## Implementation Description

* main.cpp simply creates a window with a MyViewer element and a toolbar
* MyViewer.h extends QGLViewer. It provides with different operations linked to the mesh view, such as saving or mouse events.
* Mesh.h is used by MyViewer. It defines three structures : Vertex, Triangle, and Mesh.
* point3.h implements various mathematic structures and functions related to matrices and points.
* The gl file contains colors and various utility methods.
