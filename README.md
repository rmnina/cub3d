# Cub3D

Cub3D is a **graphics project** introducing the concept of **raycasting**. The graphics library used is MinilibX from 42. This was a group project, which I completed with the excellent [@Moyaxzan](https://github.com/Moyaxzan).

To quote [Lode V](https://lodev.org/cgtutor/raycasting.html) and their very good tutorial on raycasting:

> *“Raycasting is a **rendering technique** to **create a 3D perspective in a 2D map**. Back when computers were slower it wasn't possible to run real 3D engines in realtime, and raycasting was the first solution. Raycasting can go very fast, because only a calculation has to be done for every vertical line of the screen. The most well known game that used this technique, is of course Wolfenstein 3D”*
> 

## The 2D map

The idea here is to **recover a 2D map** composed of :

- '0' for floors;
- '1' for walls;
- 'N', 'S', 'E' or 'W' for the observer's position and orientation.

We also retrieve a **texture** for each north, south, east and west side of the walls, and the colors of the floor and ceiling.

The maps have the **.cub extension**, and we've put plenty of examples in the src/maps/ folder (warning: some of these maps are invalid and were used to test our parsing!).

Now, the whole purpose of the project was to be able to go from that :

```bash
111111111111111111111111111
100000000000000000000000001
1000N0001110000001111100001
100000110110000010001100001
100001100110000000011000001
100011111111100000110000001
100000000110000011000000001
100000000110000111111000001
100000000000000000000000001
111111111111111111111111111
```

... to this :

![Screenshot from 2024-04-27 00-01-06](https://github.com/rmnina/cub3d/assets/118455014/84396ecb-ff01-46af-9e6c-17e7808223de)


## From 2D to 3D

This is where the raycasting technique comes into play. Basically, **our observer will launch a bunch of rays**, which will be **traced step by step until they hit a wall**. To calculate these rays, we use an algorithm called **DDA (digital differential analyzer)**. This algorithm assumes that, since we're in a grid map, we'll always have intersections between our grid and our rays: we can use these intersections as stops, and **advance our ray from intersection to intersection until we reach the wall.**

Here's a little sheet I made when I was learning raycasting. Not that my notes necessarily make it any clearer, but at least there are cool little drawings.

![IMG_0460](https://github.com/rmnina/cub3d/assets/118455014/c43b0474-66f6-4eef-a7dc-6ae3e29141e5)


For these notions, I followed [this video](https://youtu.be/NbSee-XM7WA?si=ME5OvpRHsrJnycY8).

Once we've got all our rays, we can **use the distances obtained to calculate the size of the walls encountered**, and thus give the **perspective effect**. And the result is…

![Screenshot from 2024-04-27 00-41-15](https://github.com/rmnina/cub3d/assets/118455014/8ab2e500-c13e-4af3-81ea-72fc6d431b93)


Tadaaaa! It doesn't look like much, but in fact, it's a great example of what raycasting does: it just **rescales squares according to their distance from the observer.** Now it's just a matter of **adding colors and textures** to make the magic happen. Calculating the perspective of the textures is a bit tricky, but once it's done, it turns out like this:

![Screenshot from 2024-04-27 00-42-22](https://github.com/rmnina/cub3d/assets/118455014/73cc1a73-4ed1-402a-9d00-51a5c6973cee)


Better, isn't it? The trick is done, it really looks like real 3D! From there, all we had to do was adjust our values to **calculate our moves and rotations**. We also thought it would be cool to add a **minimap:**

![Screenshot from 2024-04-27 01-38-42](https://github.com/rmnina/cub3d/assets/118455014/c3de8b99-8d9c-4cba-8981-ac456917079a)

For the labyrinth, it helps... 🙂

## Overall

Cub3D is an interesting graphics project. The raycasting technique enabled us to discover a **practical application of maths as a means of creating algorithms**, and to become even more familiar with **graphics tools and techniques**. Indeed, as well as successfully rendering a 2D map into 3D, we've also implemented **vertical and lateral movements for the observer**, as well as **keyboard and mouse rotations**. The search for **optimization** was also challenging, and we were pleased with the fluidity and final rendering.

### To try out our project

```bash
git clone https://github.com/rmnina/cub3d.git
cd cub3d
git clone https://github.com/42Paris/minilibx-linux.git
make
./cub3D --help
**Cub3d program usage:
  ./cub3D file_path.cub

The file.cub should contain the following mandatory elements:
  - NO north_texture_path (Example: NO ./path_to_the_north_texture)
  - SO south_texture_path
  - WE west_texture_path
  - EA east_texture_path
  - F XXX,XXX,XXX (RGB format, for the Floor)
  - C XXX,XXX,XXX (RGB format, for the Ceiling)
  - A map

The map must fulfill the following specifications:
  - The map must be composed of only 6 possible characters: 
    • 0 for an empty space
    • 1 for a wall
    • N, S, E, or W for the player’s start position and orientation.
  - The map must be closed/surrounded by walls.
  - The map content always has to be the last element of the file.
see [-h] or [--help] for further informations**
```

### Resources

I already quoted [this tutorial from Lode V.](https://lodev.org/cgtutor/raycasting.html) that I highly recommend.

I made my memo sheet thanks to [this video](https://youtu.be/NbSee-XM7WA?si=1wRkBGU-X9wbycq8), but [this one](https://youtu.be/gYRrGTC7GtA?si=7mt_Pb7H9faGO9tD) helped me too.

And a bunch of our textures came from [there](https://opengameart.org/textures/all).
