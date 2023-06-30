# 42_so_long
#### A graphical project(A 2d game working with textures, sprites, and some other  gameplay elements)
#### Sprites, Tiles, Images gotten from itch.io  && MLX42 Libary used for graphics

```
git clone https://github.com/Kingsolomon445/42_so_long

make mlx  # For the MLX42 library

make dep  # for dependencies e.g cmake && glfw

make all  # without enemies feature

make bonus  # with enemies feature

./so_long <path/to/map>     # Run executable without enemies feature

./so_long_bonus <path/to/bonus/maps>   # Run executable with enemies feature

```

##### Note:  If you get a compile error, you may need to edit this Makefile line: INC_GLFW = -lglfw -L "/opt/homebrew/Cellar/glfw/3.3.8/lib" as this may not be in thesame path on your computer

##### Note:  This game was originally designed on Mac (May not work as expected on other platforms) Read MLX42 Doc

* **W or UP key**: Moves up
* **A or DOWN key**: Moves down
* **S or LEFT key**: Moves left
* **D or RIGHT key**: Moves right
* **SPACE key**: Shoot fire at enemy (This is for so_long_bonus)
* **ESC key**: Quits game
