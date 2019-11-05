# Scan Line Polygon Fill Algorithm

**Implementation of SLPF, Using OpenGL, Practice of Balanced Tree**

![](demo.png)
![](demo2.png)

## Explanation

- Left click in the window to draw the point
- Right click to close the polygon, and then fill the polygon 
- Note that: Self-crossing polygon is not allowed in the program, so it banned you from drawing lines that cross others.
- Press space to restart. 

## Structure

- Header files in 3rd_party directory are basically modified version of another project of mine.
    - [Here's the link](https://github.com/PTYin/data_structure.git) 
    - Though I only use AVLTree class of this project, but it depends on a few other classes due to inheritance so that there are several files in this folder.
- Files in freeglut are the Prepackaged Releases of freeglut
    - You may want to use other version of freeglut, [download from here](http://freeglut.sourceforge.net/index.php#download)
    - CMakeLists.txt are based on this structure. So if you want to use other version, you should modify the CMakeLists.txt
- Files in src are the main source code of this project

## Build
    git clone https://github.com/PTYin/SLPF.git
    cd SLPF
    mkdir cmake-build-debug
    cd cmake-build-debug
    cmake .. && make
    ./SLPF.exe