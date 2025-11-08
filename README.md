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

## Date Utility Implementation

### Bit-Packed Month Days Algorithm

The date utility uses a clever bit-packing technique to store month lengths efficiently. Each month's day count (28-31) is encoded using 2 bits:

```
Binary → Decimal → Days
11100  → 28      → 00  (28 days)
11101  → 29      → 01  (29 days)
11110  → 30      → 10  (30 days)
11111  → 31      → 11  (31 days)
```

Each hexadecimal digit represents the day counts of 2 consecutive months, starting from January:

```
Month order: Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec

Non-leap year:
11 00 11 10 11 10 11 11 10 11 10 11  →  0x00CEEFBB
31 28 31 30 31 30 31 31 30 31 30 31

Leap year:
11 01 11 10 11 10 11 11 10 11 10 11  →  0x00DEEFBB
31 29 31 30 31 30 31 31 30 31 30 31
```

### Extracting Month Days

To retrieve a specific month's day count:

```c
int get_month_days(int val, int index)
{
    int shift_count;
    
    // Index 1 = January (shift 22 bits right)
    // Index 2 = February (shift 20 bits right)
    // ...
    shift_count = 24 - (2 * index);
    
    // Extract 2 bits and add base value 28
    return (((val >> shift_count) & 0b11) + 28);
}
```

This approach:
- Uses only 24 bits (3 bytes) instead of 12 integers (48 bytes on 32-bit systems)
- Provides O(1) lookup time
- Handles leap years by simply changing one hex digit (0xCE → 0xDE)

## Building

```bash
make          # Build project
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild everything
```
