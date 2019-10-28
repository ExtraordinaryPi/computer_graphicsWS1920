C++ Practice: Exercise 1
========================

This is the project template for Exercise 1 of the "C++ Practice" lecture.


## Dependencies

* [CMakeshift](https://github.com/mbeutel/CMakeshift)
* [fmt](https://fmt.dev/latest)
* [Catch2](https://github.com/catchorg/Catch2)


## Getting started

It is assumed that you are working on a computer that is prepared for modern C++ development.
If you have not done so already, follow the [guide in the Wiki][1] to set up your computer.

Use Git to clone this repository on your computer.

Open a command-line window. Use Vcpkg to install the libraries we depend on:

```
my-vcpkg install cmakeshift fmt catch2
```

Now configure the project with CMake in the way you prefer, e.g.:

- by creating a build directory and calling `cmake-configure`, or
- by opening the folder in Visual Studio (cf. [wiki][2]), or
- by opening the folder in Visual Studio Code (cf. [wiki][3]).

To complete the exercise, implement the stubbed-out functions and classes as specified on the
exercise sheet.

When submitting your exercise project to Moodle, include the entire source directory in your ZIP
package, but be sure to exclude the ".git" subdirectory, the build directory, and any build and
configuration artifacts from your submission.


[1]: https://mp-force.ziti.uni-heidelberg.de/asc/doc/wiki/wikis/Getting-started/C++/Setting-up-a-development-environment/Setting-up-a-development-environment
[2]: https://mp-force.ziti.uni-heidelberg.de/asc/doc/wiki/wikis/Getting-started/C++/Setting-up-a-development-environment/Setting-up-a-development-environment-on-Windows#develop-an-application-with-visual-studio
[3]: https://mp-force.ziti.uni-heidelberg.de/asc/doc/wiki/wikis/Getting-started/C++/Develop-with-Visual-Studio-Code#developing-c-projects-with-visual-studio-code
