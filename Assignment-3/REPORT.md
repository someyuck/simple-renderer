# Computer Graphics
## Samyak Mishra (2022101121)
# Assignment 3 Report

The codebase is in `/simple_renderer/`, without the git files, `.git/` and `extern/`. It contains the code for tasks 1, 2 and 3 (questiosn 2, 3 and 4 in the assignment document respectively) combined.
The output images for each question are in `/images/`, and are linked to here in the report as well.

## How to test
- Unzip the `images.zip` file and extract it here in the current directory.
- Add the `extern/` directory to `./simple_renderer/` for the external git repositories.
- Open a terminal into this directory.
- Run `chmod +x test.sh`. This script renders each scene one by one and thus will take considerable time to finish.
- Run `./test.sh path/to/scenes`, where the CL argument is the path to the scenes repository relative to this directory.

This will rebuild the renderer and run it for each question:
- For Q1, the Cornell Box scene for both `1 spp` and `32 spp`.
- For Q2, each of the four area light scenes, with `32 spp` each.
- For Q3, each of the four scenes, for each of three values of `spp` (`10`, `100` and `1000`), for each of the three sampling variants (uniform, cosine and area light sampling).

The script starts each render as a background process and so all cores will be used, resulting in faster execution. For cleanliness the output is redirected to `log.txt`.

The render times of the images of each question are as follows.

# Q1.

Note that for this question (and [Question 2](#q2)), I have used `4` as the value for the command line parameter `sampling_variant`, as using `0` (uniform hemisphere sampling), `1` (cosine weighted sampling) or `2` (light sampling) would cause the scene to render undesirably. Since `4` is an invalid value, light sampling is ignored. Since this question doesn't use area lights but only a directional light, it is rendered normally. And since the sampling method doesn't involve rendering lights themselves, the area lights in the next question are rendered as expected as well.

1 spp.

Render Time: 869.767029 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q1-1.png)

32 spp.
Render Time: 26554.072266 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q1-32.png)


# Q2

Scene 1 with 32 spp.

Render Time: 18555.826172 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q2-scene1.png)

Scene 2 with 32 spp.

Render Time: 18884.042969 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q2-scene2.png)

Scene 3 with 32 spp.

Render Time: 18822.941406 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q2-scene3.png)

Scene 4 with 32 spp.

Render Time: 33354.679688 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q2-scene4.png)

# Q3

## small.json

### 10 spp

Uniform hemisphere sampling

Render Time: 8709.507812 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-small-10-0.png)

Cosine hemisphere sampling

Render Time: 9044.310547 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-small-10-1.png)

Area light sampling

Render Time: 8217.016602 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-small-10-2.png)

### 100 spp

Uniform hemisphere sampling

Render Time: 86060.906250 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-small-100-0.png)

Cosine hemisphere sampling

Render Time: 86561.757812 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-small-100-1.png)

Area light sampling

Render Time: 82767.101562 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-small-100-2.png)

### 1000 spp

Uniform hemisphere sampling

Render Time: 857272.437500 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-small-1000-0.png)

Cosine hemisphere sampling

Render Time: 861830.312500 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-small-1000-1.png)

Area light sampling

Render Time: 823481.250000 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-small-1000-2.png)


## med.json

For this scene, one can observe some whitish dots on the front face of the small cube, for uniform and cosine hemisphere sampling. Moreover, this saltiness goes away as we increase the number of samples and is not present for area light sampling.
This is due to the following reasons.
- In this scene, the front edge of the area light is just ahead enough for the front face of the small cube to come into its field of view.
- Uniform and Cosine Hemisphere sampling do not direct the shadow ray at the light source and it can have any random direction (in the upper hemisphere), with just the distribution being different.
- Due to the above two facts, for some points on the front face, the sampled shadow ray has a certain (although small -- as the saltiness is only a few pixels) probability of hitting the light source. And thus for less number samples, there is a reasonable enough chance for a point on the front surface of the cube to have most of its shadow rays hit the area light, thus causing the salty pixels in the output image.
- As we increase the number of samples, we further decrease the chances of this happening, and so we do not see salty pixels in the output images for 1000 spp.
- We do not see this saltiness for area light sampling as well, because there each shadow ray will be directed towward the area light, and since there is only so much of the light visible to the front face of the cube, they will be nearly vertical (thus at angle $\frac{\pi}{2}$ with surface normal) and so will have near pitch black colouring and no salty pixels in the output images.

### 10 spp

Uniform hemisphere sampling

Render Time: 8771.849609 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-med-10-0.png)

Cosine hemisphere sampling

Render Time: 9053.147461 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-med-10-1.png)

Area light sampling

Render Time: 8308.673828 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-med-10-2.png)

### 100 spp

Uniform hemisphere sampling

Render Time: 85087.203125 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-med-100-0.png)

Cosine hemisphere sampling

Render Time: 88433.101562 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-med-100-1.png)

Area light sampling

Render Time: 80764.179688 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-med-100-2.png)

### 1000 spp

Uniform hemisphere sampling

Render Time: 886513.562500 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-med-1000-0.png)

Cosine hemisphere sampling

Render Time: 881275.625000 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-med-1000-1.png)

Area light sampling

Render Time: 799571.062500 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-med-1000-2.png)

## big.json

For this scene (and [many.json](#manyjson)), in the area light sampling case, one can observe some graininess at the top edges of the walls. This is because
with increase in the size of the light, we have more light points farther away (and so towards us) from the top edge of the walls. And as the size of the light increases, the probability of the sampled shadow ray hitting the farther end of the area light (the side closer to us) increases, which means that the shadow ray becomes more and more parallel to the plane of the area light and hence the angle between the shadow ray and the normal of the area light gets closer and closer to $\frac{\pi}{2}$.

Now the colour at a point is proportional to the cosine of the angle between the shadow ray hitting the light, and the normal at the light. So we will observe the following:

$\cos{\theta_l} = \vec{d} \cdot \vec{n} \rightarrow \cos{\frac{\pi}{2}} = 0$

where $\vec{d}$ is the direction unit vector of the shadow ray and $\vec{n}$ is the normal unit vector of the area light and $\theta_l$ is the angle between them.
 
This means that more points will get no colour due to the area light and thus their corresponding pixels will be blacker. And since this is all random, we will observe graininess at the top edge of the walls for bigger lights.

### 10 spp

Uniform hemisphere sampling

Render Time: 8592.948242 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-big-10-0.png)

Cosine hemisphere sampling

Render Time: 8490.769531 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-big-10-1.png)

Area light sampling

Render Time: 8035.689941 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-big-10-2.png)

### 100 spp

Uniform hemisphere sampling

Render Time: 82839.070312 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-big-100-0.png)

Cosine hemisphere sampling

Render Time: 83408.593750 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-big-100-1.png)

Area light sampling

Render Time: 80675.203125 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-big-100-2.png)

### 1000 spp

Uniform hemisphere sampling

Render Time: 816172.687500 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-big-1000-0.png)

Cosine hemisphere sampling

Render Time: 822660.562500 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-big-1000-1.png)

Area light sampling

Render Time: 786561.000000 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-big-1000-2.png)


## many.json

### 10 spp

Uniform hemisphere sampling

Render Time: 18930.660156 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-many-10-0.png)

Cosine hemisphere sampling

Render Time: 18959.732422 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-many-10-1.png)

Area light sampling

Render Time: 16865.095703 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-many-10-2.png)

### 100 spp

Uniform hemisphere sampling

Render Time: 184099.171875 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-many-100-0.png)

Cosine hemisphere sampling

Render Time: 196573.578125 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-many-100-1.png)

Area light sampling

Render Time: 169709.843750 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-many-100-2.png)

### 1000 spp

Uniform hemisphere sampling

Render Time: 1794644.875000 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-many-1000-0.png)

Cosine hemisphere sampling

Render Time: 1848371.750000 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-many-1000-1.png)

Area light sampling

Render Time: 1669562.875000 ms
![Sorry the image is unavailable. Add the `images/` directory or run `./test.sh` or `./run`.](./images/a3q3-many-1000-2.png)

# Questions

## Q1.

**Why can’t we render point and directional lights with uniform hemisphere sampling or cosine weighted sampling?**

In uniform and cosine weighted hemisphere sampling, we sample the direction of the shadow ray at random from within the upper hemishere. The only difference is in the distribution of the sampling: in the former, it is uniform (equally likely everywhere) and in the latter: it is cosine-weighted, where the cosine is with the (outward) surface normal, and so the shadow ray is more likely to be sampled near the outward normal. In any case, it is random and moreover we use continous random variables (using the method of inversion) to sample the direction, and continuous random variables have probability *density*, and not probability *mass*, i.e. the probability of getting any one point in the range of the random variable (here any one particular direction), is zero.

And since for both point lights and directional lights, the shadow ray from a point on an object will only hit the light if it is in a particular direction (toward the point light in the former case and along (well actually opposite) the light direction in the latter). So only one particular direction in the entirety of the upper hemisphere will lead to a light hit, and since the probability mass for any one direction is zero, **hitting the light is a zero probability event**.
Zero probability does not mean it is impossible, but extremely unlikely. And since in real life point lights and directional lights deterministically do contribute to lighting objects, we will not be able to correctly render scenes if we use these randomised sampling methods.

Therefore, for point and directional lights, uniform and cosine weighted hemisphere sampling will lead to the image not being rendered (at least not with contributions from these lights) and so we should not use them to render point and directional lights.

## Q2.

**Why does the noise increase for the same number of samples in the case of uniform hemisphere and cosine weighted sampling as the size of the area light decreases?**

In uniform and cosine weighted hemisphere sampling, we sample the direction of the shadow ray at random from within the upper hemishere. The only difference is in the distribution of the sampling: in the former, it is uniform (equally likely everywhere) and in the latter: it is cosine-weighted, where the cosine is with the (outward) surface normal, and so the shadow ray is more likely to be sampled near the outward normal.

Now, for the same number of samples, the size of the area light affects the fraction of the upper hemisphere at a point from which the shadow ray can be sampled.
As we decrease the size of the area light, a lesser fraction of the upper hemisphere will be covered, resulting in less directions that the shadow ray can take to be able to hit the light. Therefore the **probability of the randomly sampled shadow ray hitting the area light** would decrease with decreasing size of the light.

And since the color of the point in the image is the average of all the samples we take, we will observe a lesser fraction of the samples hitting the light source and therefore a lesser fraction contributing colour to the pixel. Therefore with decrease in the size of the area light we will see more pixels (again, at random) being black.

In other words, for the same number of samples, the noise in the image increases with decrease in the size of the area light, in the case of uniform and cosine weighted hemisphere sampling.

