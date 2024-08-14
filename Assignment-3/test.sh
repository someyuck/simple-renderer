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

if [ ! -f log.txt ]
then
    touch log.txt
fi

scenes_path="$1"

# Q1

##  Q1 scene with 1 spp > log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 1/directional_light.json ./images/a3q1-1.png 1 4 >> log.txt & 

##  Q1 scene with 1 spp >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 1/directional_light.json ./images/a3q1-32.png 32 4 >> log.txt & 


# Q2

##  Q2: scene 1 with 32 spp >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 2/scene1.json ./images/a3q2-scene1.png 32 4 >> log.txt & 

##  Q2: scene 2 with 32 spp >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 2/scene2.json ./images/a3q2-scene2.png 32 4 >> log.txt & 

##  Q2: scene 3 with 32 spp >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 2/scene3.json ./images/a3q2-scene3.png 32 4 >> log.txt & 

##  Q2: scene 4 with 32 spp >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 2/scene4.json ./images/a3q2-scene4.png 32 4 >> log.txt & 


# Q3

## 10 samples

##  Q3: small.json with 10 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/small.json ./images/a3q3-small-10-0.png 10 0 >> log.txt & 

##  Q3: small.json with 10 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/small.json ./images/a3q3-small-10-1.png 10 1 >> log.txt & 

##  Q3: small.json with 10 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/small.json ./images/a3q3-small-10-2.png 10 2 >> log.txt & 

##  Q3: med.json with 10 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/med.json ./images/a3q3-med-10-0.png 10 0 >> log.txt & 

##  Q3: med.json with 10 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/med.json ./images/a3q3-med-10-1.png 10 1 >> log.txt & 

##  Q3: med.json with 10 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/med.json ./images/a3q3-med-10-2.png 10 2 >> log.txt & 


##  Q3: big.json with 10 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/big.json ./images/a3q3-big-10-0.png 10 0 >> log.txt & 

##  Q3: big.json with 10 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/big.json ./images/a3q3-big-10-1.png 10 1 >> log.txt & 

##  Q3: big.json with 10 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/big.json ./images/a3q3-big-10-2.png 10 2 >> log.txt & 

##  Q3: many.json with 10 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/many.json ./images/a3q3-many-10-0.png 10 0 >> log.txt & 

##  Q3: many.json with 10 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/many.json ./images/a3q3-many-10-1.png 10 1 >> log.txt & 

##  Q3: many.json with 10 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/many.json ./images/a3q3-many-10-2.png 10 2 >> log.txt & 

## 100 samples


##  Q3: small.json with 100 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/small.json ./images/a3q3-small-100-0.png 100 0 >> log.txt & 

##  Q3: small.json with 100 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/small.json ./images/a3q3-small-100-1.png 100 1 >> log.txt & 

##  Q3: small.json with 100 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/small.json ./images/a3q3-small-100-2.png 100 2 >> log.txt & 

##  Q3: med.json with 100 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/med.json ./images/a3q3-med-100-0.png 100 0 >> log.txt & 

##  Q3: med.json with 100 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/med.json ./images/a3q3-med-100-1.png 100 1 >> log.txt & 

##  Q3: med.json with 100 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/med.json ./images/a3q3-med-100-2.png 100 2 >> log.txt & 

##  Q3: big.json with 100 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/big.json ./images/a3q3-big-100-0.png 100 0 >> log.txt & 

##  Q3: big.json with 100 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/big.json ./images/a3q3-big-100-1.png 100 1 >> log.txt & 

##  Q3: big.json with 100 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/big.json ./images/a3q3-big-100-2.png 100 2 >> log.txt & 

##  Q3: many.json with 100 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/many.json ./images/a3q3-many-100-0.png 100 0 >> log.txt & 

##  Q3: many.json with 100 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/many.json ./images/a3q3-many-100-1.png 100 1 >> log.txt & 

##  Q3: many.json with 100 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/many.json ./images/a3q3-many-100-2.png 100 2 >> log.txt & 


### 1000 samples

##  Q3: small.json with 1000 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/small.json ./images/a3q3-small-1000-0.png 1000 0 >> log.txt & 

##  Q3: small.json with 1000 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/small.json ./images/a3q3-small-1000-1.png 1000 1 >> log.txt & 

##  Q3: small.json with 1000 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/small.json ./images/a3q3-small-1000-2.png 1000 2 >> log.txt & 

##  Q3: med.json with 1000 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/med.json ./images/a3q3-med-1000-0.png 1000 0 >> log.txt & 

##  Q3: med.json with 1000 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/med.json ./images/a3q3-med-1000-1.png 1000 1 >> log.txt & 

##  Q3: med.json with 1000 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/med.json ./images/a3q3-med-1000-2.png 1000 2 >> log.txt & 


##  Q3: big.json with 1000 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/big.json ./images/a3q3-big-1000-0.png 1000 0 >> log.txt & 

##  Q3: big.json with 1000 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/big.json ./images/a3q3-big-1000-1.png 1000 1 >> log.txt & 

##  Q3: big.json with 1000 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/big.json ./images/a3q3-big-1000-2.png 1000 2 >> log.txt & 


##  Q3: many.json with 1000 spp and uniform hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/many.json ./images/a3q3-many-1000-0.png 1000 0 >> log.txt & 

##  Q3: many.json with 1000 spp and cosine hemisphere sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/many.json ./images/a3q3-many-1000-1.png 1000 1 >> log.txt & 

##  Q3: many.json with 1000 spp and area light sampling >> log.txt
./simple_renderer/build/render $scenes_path/Assignment\ 3/Question\ 3/many.json ./images/a3q3-many-1000-2.png 1000 2 >> log.txt & 