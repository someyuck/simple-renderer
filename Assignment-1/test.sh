#!/bin/bash

cd ./simple_renderer;
if [ ! -d build ]
then
    mkdir build;
fi

cd build; cmake .. ; make -j8
cd ../../

# Question 1
./simple_renderer/build/render $1/Assignment\ 1/Question\ 1/correct.json      ./images/correct3.png   3
echo
./simple_renderer/build/render $1/Assignment\ 1/Question\ 1/incorrect.json    ./images/incorrect3.png 3
echo


# Cornell Box
## hi poly
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/CornellBox/scene_hi_poly.json    ./images/cb_hi_poly_mode_0.png 0
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/CornellBox/scene_hi_poly.json    ./images/cb_hi_poly_mode_1.png 1
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/CornellBox/scene_hi_poly.json    ./images/cb_hi_poly_mode_2.png 2
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/CornellBox/scene_hi_poly.json    ./images/cb_hi_poly_mode_3.png 3
echo
# # ## low poly
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/CornellBox/scene_lo_poly.json    ./images/cb_lo_poly_mode_0.png 0
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/CornellBox/scene_lo_poly.json    ./images/cb_lo_poly_mode_1.png 1
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/CornellBox/scene_lo_poly.json    ./images/cb_lo_poly_mode_2.png 2
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/CornellBox/scene_lo_poly.json    ./images/cb_lo_poly_mode_3.png 3
echo
# # Donuts
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/Donuts/scene.json                ./images/donuts_mode_0.png 0
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/Donuts/scene.json                ./images/donuts_mode_1.png 1
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/Donuts/scene.json                ./images/donuts_mode_2.png 2
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/Donuts/scene.json                ./images/donuts_mode_3.png 3
echo
# # Table top
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/TableTop/scene.json                ./images/tabletop_mode_0.png 0
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/TableTop/scene.json                ./images/tabletop_mode_1.png 1
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/TableTop/scene.json                ./images/tabletop_mode_2.png 2
./simple_renderer/build/render $1/Assignment\ 1/Question\ 2/TableTop/scene.json                ./images/tabletop_mode_3.png 3
