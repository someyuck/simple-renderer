#!/bin/bash

cd simple_renderer
if [ ! -d build ]
then 
    mkdir build
fi

cd build; cmake .. ; make -j8
cd ../..

if [ ! -d images ]
then 
    mkdir images
fi

scenes_path="$1"

echo "Q1: Cornell Box: Directional Light"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 1/CornellBox/directional_light.json ./images/cb_dir.png 0
echo
echo "Q1: Cornell Box: Point Light"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 1/CornellBox/point_light.json ./images/cb_point.png 0
echo
echo "Q1: Cornell Box: Multiple Lights"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 1/CornellBox/many_lights.json ./images/cb_many.png 0
echo
echo; echo

echo "Q1: Donuts"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 1/Donuts/scene.json ./images/donuts0.png 0
echo; echo

# Q2
echo "Q2: Cornell Box: Directional Light: Nearest Neighbour Interpolation"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 2/CornellBox/directional_light.json ./images/cb_dir_nn.png 0
echo
echo "Q2: Cornell Box: Directional Light: Bilinear Interpolation"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 2/CornellBox/directional_light.json ./images/cb_dir_bi.png 1
echo; echo

echo "Q2: Cornell Box: Point Light: Nearest Neighbour Interpolation"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 2/CornellBox/point_light.json ./images/cb_point_nn.png 0
echo
echo "Q2: Cornell Box: Point Light: Bilinear Interpolation"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 2/CornellBox/point_light.json ./images/cb_point_bi.png 1
echo; echo

echo "Q2: Cornell Box: Multiple Lights: Nearest Neighbour Interpolation"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 2/CornellBox/many_lights.json ./images/cb_many_nn.png 0
echo
echo "Q2: Cornell Box: Multiple Lights: Bilinear Interpolation"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 2/CornellBox/many_lights.json ./images/cb_many_bi.png 1
echo; echo

echo "Q2: Donuts: Nearest Neighbour Interpolation"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 2/Donuts/scene.json ./images/donuts_nn.png 0
echo
echo "Q2: Donuts: Bilinear Interpolation"
./simple_renderer/build/render "$scenes_path"/Assignment\ 2/Question\ 2/Donuts/scene.json ./images/donuts_bi.png 1
echo; echo

# my scene

echo "My scene: Nearest Neighbour Interpolation"
./simple_renderer/build/render myscene/myscene.json images/myscene_nn.png 0
echo
echo "My scene: Bilinear Interpolation"
./simple_renderer/build/render myscene/myscene.json images/myscene_bi.png 1
