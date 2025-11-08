# So Long

A 2D game project using MiniLibX graphics library.

## MiniLibX Manual Pages Installation

To install MiniLibX manual pages system-wide:

```bash
# Copy man pages to system directory
sudo cp -r minilibx-linux/man/man1 /usr/local/share/man
sudo cp -r minilibx-linux/man/man3 /usr/local/share/man

# Update man database
sudo mandb
```

After installation, you can access documentation using:
- `man mlx`
- `man mlx_new_window`
- `man mlx_new_image`
- `man mlx_pixel_put`
- `man mlx_loop`

Check your manual paths with `manpath` command.

## Git Submodules

### Adding MiniLibX as a Submodule

```bash
git submodule add https://github.com/42paris/minilibx-linux
```

### Cloning Repository with Submodules

```bash
# Clone with all submodules
git clone --recurse-submodules <repo-url>

# Clone only a specific branch
git clone --single-branch --branch <branch_name> <repo-url>
```

### Updating Submodules

```bash
git submodule update --init --recursive
```

## MiniLibX RGB Color Tool

The `rgb2c.pl` script converts RGB color names to hexadecimal values. It requires the X11 RGB database:

```bash
# Download RGB database
wget 'https://gitlab.freedesktop.org/xorg/app/rgb/-/raw/master/rgb.txt'

# Install to system directory
sudo mkdir -p /usr/X11/lib/X11
sudo cp rgb.txt /usr/X11/lib/X11/rgb.txt
```

Usage:
```bash
./minilibx-linux/rgb2c.pl ColorName
```

## MiniLibX Resource Management

**Important**: When destroying MiniLibX resources, follow this order:

1. **Images** - `mlx_destroy_image()`
2. **Windows** - `mlx_destroy_window()`
3. **Display** - `mlx_destroy_display()`

Example:
```c
// Clean up in correct order
mlx_destroy_image(mlx_ptr, img_ptr);
mlx_destroy_window(mlx_ptr, win_ptr);
mlx_destroy_display(mlx_ptr);
free(mlx_ptr);
```

Destroying resources in the wrong order may cause memory leaks or segmentation faults.

## Building

```bash
make          # Build project
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild everything
```
