# Simple Renderer

In the Computer Graphics class during the Spring 2024 semester, I had three assignments involving building upon a simple rendered, using concepts from physically-based rendering, namely ray tracing.

## Assignment Topics:

### Assignment 1

Involved mainly building an acceleration structure on the objects provided in the models, namely a Bounding Volume Hierarchy (BVH), using Axis Aligned Bounding Boxes (AABBs). I built a top-level BVH (TLAS) on the surfaces (objects) in the whole model, and a bottom-level BHV (BLAS) on the traingles inside each surface (object).

A detailed description can be found [here](./Assignment-1/REPORT.md).

### Assignment 2

This assignment involved implementing direct lighting and texture mapping. I implemented direct lighting with point and directional lighting, which involved using the light transport equations to calculate the colour of the pixel being targeted due to the lights present in the scenes. Texture mapping included loading the textures assigned to each object, and choosing the base colour to take using a fetching strategy for the targeted pixel, namely either nearest neighbour fetching or bilinear interpolation.

A detailed description can be found [here](./Assignment-2/REPORT.md).

### Assignment 3

This assignment involved implementing direct lighting for area lights using Monte Carlo integration. I implemented pixel sub-sampling for anti-aliasing and rendereing of the area lights themeselves. To implement the direct lighting, I implemented Monte Carlo integration to calculate the shade of the targeted pixel using various importance sampling strategies, namely uniform hemisphere sampling, cosine weighted sampling, and light sampling.

The detailed description can be found [here](./Assignment-3/REPORT.md).

## Future Scope

In the foreseeable future, I wish to put together all codebases by building one on top of the other.