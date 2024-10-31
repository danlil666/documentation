---
layout: post
title:  "Assignment 2 - The Three-Body Problem"
date:   2021-10-14 10:05
parent: "MakingIt"
---
Today we are making sensors and visualizing the sensor signal in Rhino by a Grasshopper add-on called Firefly.

Let me walk you through why this is titled *The Three-Body Problem*.

## Ideation

As a reflection of this week's reading, I was brainstorming around these keywords: folding, unfolding, integration, extensibility, stacking. It didn't take me too long to come to my *muse* - a armchair covered in clothes. (Do they call it a couch closet or something? /ponder)

![clothesoncouch](https://c8.alamy.com/comp/R6P6F4/messy-clothes-pile-on-leather-couch-R6P6F4.jpg)

I decided to create a soft sensor in the form of a garment that indicates the messiness of such piling. In the tangible world, the messiness could be (but not necessarily) proportional to the amount of misplaced clothes on top of the sensor, *i.e.* weight.

[Kobakant](https://www.kobakant.at/DIY/) has a great collection of soft fabric sensors and I am most fond of this kind: squishy [felt pompom pressure sensor](https://www.kobakant.at/DIY/?p=2395).

![pompomsensor](http://farm3.static.flickr.com/2802/4498265720_c97fcacaed_m.jpg)

![pompomsensor2](http://farm5.static.flickr.com/4033/4497629015_6294ba0c98_m.jpg)

## Swatching

It feels like velostat is frequently used in thin, sensitive pressure sensors (such as [neoprene pressure sensor](https://www.kobakant.at/DIY/?p=65)). With the materials I have in hand, which are wool roving, wool yarn, and non-woven fabrics, I first validated the effectiveness of the wool/conductive yarn blend as a pressure sensor. The motivation is trying it out before it is made into a felted sensor because felting is irreversible.

I compared roving wool and wool yarn, both twisted with conductive yarn.

The both have similar range of analog readings as shown in the figures below. The roving wool shows slightly better stability in reading. However, the yarn design is squeezed tighter in the test. When I tried twisting the roving wool into a tighter blob, the reading range decreased. Thus, the wool yarn+conductive thread swatch is chosen to be made into a sensor.

![figure1](../files/project2/project2_testwool.jpg)

![gif1](../files/project2/project2_testwool.gif)

![figure2](../files/project2/project2_testyarn.jpg)

## Making

Now that the material composition is decided, here comes the exciting part - making it!

Another reason for using yarn over loose wool, although the crafting technique is felting, is this [3D printing Teddy Bear](https://dl.acm.org/doi/abs/10.1145/2556288.2557338).

[![3dprintingteddybear](https://i.ytimg.com/vi/YhXIWyfI7Cw/maxresdefault.jpg)](https://youtu.be/YhXIWyfI7Cw "3dprintingteddybear")

The felted yarn symbolizes entanglement, yet the sanity of the machine guarantees order. I shaped the sensor in a fashion that is similar to this machine - layering yarns in a path and felting along the way. Eventually, there are two layers of yarn patterned as grid to enhance entanglement and an extra layer on top to conceal the conductive yarn.

![sweater](../files/project2/project2_sweater.jpg)

The circuit is very simple. It is supposed to read analog input. There is a resistor for buffering.

![final](../files/project2/project2_final.jpg)

## Visualization

This part was initially daunting for me, a Rhino/Grasshopper novice, but I ended having a lot of fun. I was thinking of different ways to visualize messiness or order. Originally, I wanted to draw a increasingly messy, circularly revolving path as the sensor reads stronger signals. After following [this tutorial](https://www.youtube.com/watch?v=qHtRqGRnDBM&ab_channel=RhinoGrasshopper), I decided to present a poor-man version of the [three-body problem](https://en.wikipedia.org/wiki/Three-body_problem). It is also the name of a [sci-fi novel](https://en.wikipedia.org/wiki/The_Three-Body_Problem_(novel)) I really enjoyed.

![gravity](https://upload.wikimedia.org/wikipedia/commons/1/11/3bodyproblem.gif)

I will have to give the tutorial a lot of credit in creating this Grasshopper/Firefly file.

![firefly](../files/project2/project2_Capture.PNG)

Here is a *live* demo:

![final](../files/project2/project2_demo.gif)

