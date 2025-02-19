
[42 Docs](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)<br>
[MiniLibX - gontjarow](https://gontjarow.github.io/MiniLibX/mlx_new_window.html)<br>
[So_Long - sample](https://github.com/madebypixel02/so_long/)<br>
[A comprehensive guide](https://reactive.so/post/42-a-comprehensive-guide-to-so_long/)<br>
[XLib - Events](https://tronche.com/gui/x/xlib/events/types.html)<br>
[Open Game Art](https://opengameart.org/)

# MiniLibX

### Fedora
```shell
sudo yum install -y libXext-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libbsd-devel xdotool 
```

### Ubuntu
```shell
sudo apt update
sudo apt install -y libxext-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libbsd-dev xdotool
```

### Install MinilibX

    - no installation script is provided. You may want to install
	```
        libmlx.a and/or libmlx_$(HOSTTYPE).a in /usr/X11/lib or /usr/local/lib
        mlx.h in /usr/X11/include or /usr/local/include
        man/man3/mlx*.1 in /usr/X11/man/man3 or /usr/local/man/man3
	```