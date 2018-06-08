# coin_hunter
This is a small game which takes place in a 3d maze. The goal is to collect all coins in the maze to pass levels.

This project done in collaboration with Liam Dehaudt at 42 as a spin-off from 42 graphics project Wolf3D.

The basic requirements of which is to display a room with walls (taten as input file) in perspective in 3D.
We implemented our own version of ray-casting where a linear transformation is applied to transform visible space into a rectangle and depth of each pixel is saved inside a buffer to handle overlapping planes and transparency.

