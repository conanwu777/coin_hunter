# coin_hunter
This is a small game which takes place in a 3d maze. The goal is to collect all coins in the maze to pass levels.

This project was done in collaboration with Liam Dehaudt at 42 as a spin-off from 42 graphics project Wolf3D.

The basic requirements of which is to display a room with walls (taten as input file) in perspective in 3D.
We implemented our own version of ray-casting where a linear transformation is applied to transform visible space into a rectangle and depth of each pixel is saved inside a buffer to handle overlapping planes and transparency.

All graphics are produced in-house with Marmoset Hexels.

## Compiling and running
Run `make`. An executable will compile. Currently only tested on OS X.

Run `./coin_hunter`.

![alt text](https://github.com/conanwu777/coin_hunter/blob/master/1.png)
![alt text](https://github.com/conanwu777/coin_hunter/blob/master/2.png)
![alt text](https://github.com/conanwu777/coin_hunter/blob/master/3.png)
![alt text](https://github.com/conanwu777/coin_hunter/blob/master/4.png)
![alt text](https://github.com/conanwu777/coin_hunter/blob/master/5.png)
![alt text](https://github.com/conanwu777/coin_hunter/blob/master/6.png)
