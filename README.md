# N-Body Simulation in Unreal Engine 4

As modern game engines have become more powerful as they have evolved - through utilization of different API's and middleware - they often use physics engines to create realistic physics for their games.  With this in mind, I investigated how a game engine - in this case Unreal Engine 4 - could be used to fill the role of a simulation engine by creating a high cost, calculation heavy virtual simulation – in this case a N-Body Simulation.

I also researched optimization methods could be used and decided to implement the Barnes-Hut algorithm though the use of a TOctree.  This was scrapped, however, due to TOctrees being static and not dynamic which I needed.   plan to return to this simulation and design my own octree generation code, implement the Barnes-Hut algorithm successfully and convert the game into a virtual toy.  Some elements of the virual toy have already been implemented, such as camera manipulation through rotation and zoom.

The simulation was able to run 1000 bodies at a stable 40 FPS, while also being able to simulate 2,500 bodies at 8 FPS.  I speculate this is due to how many objects are rendered in the scene and not the calculations made.

## - [Technical Report](https://github.com/profdambledore/UE4-N_Body_Simulation)

### Controls
* WASD - Rotate Simulation
* Scroll Wheel - Zoom In / Out
