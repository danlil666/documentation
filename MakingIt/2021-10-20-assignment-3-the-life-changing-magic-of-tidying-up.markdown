---
layout: post
title:  "Assignment 3 - The Life-Changing Magic of Tidying Up"
date:   2021-10-20 10:53
parent: "MakingIt"
---
There is no such thing as life-changing magic because hard work pays off.

But again I am practicing making funny titles so walk with me. 

## Ideation

The ideation revolves around these keywords: folding + extension, rigid bodies + flexible joints, simulated poultry defecation (fake duck poops). This is not a big leap from last week's [cloth piling sensor](https://danlil666.github.io/2021/10/14/assignment-2-3-body-problem.html) to this week's multifunctional cloth hanging device. Some inspirational designs are attached below.

![hanger0](https://competition.adesignaward.com/designersorg-heroimage.php?ID=77247&N=0)

![hanger1](https://m.media-amazon.com/images/I/51lmEYXuTtL._AC_SL1001_.jpg)

![hanger2](https://i.pinimg.com/originals/52/9b/26/529b26c5099384da5c741685e29ce7f5.jpg)

While the first two are quite practical designs, I decided to make a multifunctional hanger closer to the third design.

![sketch](../files/project3/project3_sketch.jpg)

## Test print

I want the joints to rotate and slide inside a slot and stay at a fixed angle when the two beams are positioned at the desired states. I test-printed a 12-pointed star to try out the fits and tolerance.

![testprint](../files/project3/project3_test.jpg)

The top disk that prevents the insert from coming out of the sliding slot has a big overhang. In the next iteration, I chamfered the edge to increase printability.

## Making

The test print and the final artifact were both made on the Prusa i3 MK3.

![prusa](../files/project3/project3_printing.jpg)

I also decided to add a hook.

![models](../files/project3/project3_rhino.PNG)

The beams are design to fold together to save space.

![finalhanger](../files/project3/project3_hanger.jpg)

The circuit is *remixed* from the sweater sensor circuit. While I really wated to hang the sweater, I can hardly think of a use of a not-so-sensitive pressure sensor in this case.

## Visualization

I played with Kangaroo for a while, trying to get a close resemblance of the hanger mechanism. It ended up taking me too long and it's difficult to map out the sensor reading accurately with such huge fluctuation. So I decided to play with the randomness and go along with a twitchy visualization. The position is roughly mapped onto the Rhino projection.

![visual](../files/project3/project3_viz.PNG)

Here is a *live* demo:

![final](../files/project3/project3_demo.gif)

