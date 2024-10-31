---
layout: post
title:  "Assignment 2 - tetratrum"
date:   2021-10-17 15:03
parent: "DigitalFabrication"
---
Today we are making parametrically designed press-fit assembly using Rhino with the Grasshopper plugin!

![overview](../files/533_2/overview.PNG)

## Ideation

I continue with the idea of making triangular surfaces and connectors that would construct tetrahedra. Then I learned that there two more polyhedra that are made of triangular surfaces - or [deltahedra](https://en.wikipedia.org/wiki/Deltahedron) - than tetrahedron. They are the octahedron and the icosahedron.

![tetrahedron](https://upload.wikimedia.org/wikipedia/commons/8/83/Tetrahedron.jpg)
![octahedron](https://upload.wikimedia.org/wikipedia/commons/thumb/0/07/Octahedron.svg/1920px-Octahedron.svg.png)
![icosahedron](https://upload.wikimedia.org/wikipedia/commons/e/eb/Icosahedron.jpg)

## Modeling

I used a slightly different method to press-fit adjascent pieces this time to avoid the trouble of adjusting the angle of the connector piece. The idea is that I truncated one vertex on a tetrahedron and make the three trapezoid sides flaps. For the fabrication part, these flaps are made by scoring the cardboard rather than cutting through it. A connector piece connects two flaps on adjascent surfaces. To save material, a circular connector is carved out of a triangular surface.

![connected](../files/533_2/IMG_1968.JPG)

To make the workflow of generating laser cut file parametric, I first define three parameters that can be played with - size of the triangle (**O**rigin to vertex, which is the default parameter of parametric polygon in Grasshopper), radius of the center circular connector, and thickness of the cardboard.

Luckily, Rhino generates polygons and circles from the origin, which is also the relative placement of these pieces.

![param](../files/533_2/param.PNG)

Then I ran through a series of Grasshopper definitions for the press-fit slits. The slits will be half as wide as the radius of the circle so that the trapizoid flaps and the circular connectors have the deepest insertion. The rectangle slits are polarly arrayed.

![arrays](../files/533_2/arrays.PNG)

After a series of trimming actions I got the outlines that needs to be cut through. The triangle is scored so it should be baked separatedly on another layer. There is an extra slider to make copies.

![pattern](../files/533_2/pattern.PNG)

## Making

I used a Trotec laser cutter to cut a cardboard I recycled from a package.

Most laser cutters recognize colors for different cutting or engraving settings. I assigned a higher power and lower speed for the cut lines in black and lower power and higher speed for the folding lines in red.

![lasercut](../files/533_2/IMG_1967.JPG)

This time the cardboard is much flatter, making the cutting and engraving more uniform and precise. I started assembly and realized that I couldn't close the icosahedron from the inside.

![outside](../files/533_2/IMG_1969.JPG)

So I flipped the inside out.

![side](../files/533_2/IMG_1970.JPG)

![top](../files/533_2/IMG_1971.JPG)

Bonus cup holder assembly!

![cup](../files/533_2/IMG_1988.JPG)


Rhino file:

[Cut path](../files/533_2/tetratrum_24.3dm)

[Grasshopper](../files/533_1/tetratrum.gh)
