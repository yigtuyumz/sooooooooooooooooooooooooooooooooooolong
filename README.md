# So Long

A 2D game project using MiniLibX graphics library.

## Project Overview

So Long is a simple 2D game where the player must collect all collectibles and reach the exit. The game implements:
- Map parsing and validation
- Floodfill pathfinding algorithm
- MiniLibX graphics rendering
- Memory-safe resource management
- Fixed window size with dynamic tile scaling

## Window and Rendering

The game uses a **fixed window size** of **1152x864 pixels** with a **base tile size of 48x48 pixels**. The actual tile dimensions are calculated dynamically based on the map size:

```c
tile_width = WINDOW_WIDTH / map_cols
tile_height = WINDOW_HEIGHT / map_rows
```

This means:
- Window size is always constant (1152x864)
- Tiles scale to fit the map within the window
- Larger maps = smaller tiles
- Smaller maps = larger tiles
- Maximum comfortable map size: 24 columns x 18 rows (at 48x48)

### Rendering Colors
- **Walls (1)**: Gray (`0x808080`)
- **Empty space (0)**: Black (`0x000000`)
- **Player (P)**: Green (`0x00FF00`)
- **Exit (E)**: Red (`0xFF0000`)
- **Collectible (C)**: Yellow (`0xFFFF00`)

## Usage

```bash
./solong <map.ber>
```

### Map File Requirements

- File must have `.ber` extension
- Map must be rectangular
- Map must be surrounded by walls (`1`)
- Must contain exactly one player (`P`)
- Must contain exactly one exit (`E`)
- Must contain at least one collectible (`C`)
- All collectibles and exit must be reachable from player position

### Map Characters

| Character | Description |
|-----------|-------------|
| `1` | Wall |
| `0` | Empty space |
| `P` | Player starting position |
| `E` | Exit |
| `C` | Collectible |

### Example Map

```
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
```

## Map Validation System

The map validation uses a **floodfill algorithm** to ensure all game objectives are reachable:

### Validation Steps

1. **File Checks**
   - Extension validation (`.ber`)
   - File existence and readability

2. **Structural Validation**
   - Rectangular shape verification
   - Wall enclosure check (all edges are walls)
   - Minimum dimensions (3x3)

3. **Element Validation**
   - Exactly 1 player (`P`)
   - Exactly 1 exit (`E`)
   - At least 1 collectible (`C`)
   - Only valid characters (`1`, `0`, `P`, `E`, `C`)

4. **Pathfinding Validation** (Floodfill)
   - Player can reach the exit
   - Player can collect all collectibles
   - No unreachable areas

### Floodfill Algorithm

The floodfill algorithm recursively explores the map from the player's starting position:

```c
// Pseudo-code
floodfill(x, y):
    if position is wall or already visited:
        return
    mark position as visited
    if position is exit: mark exit as reachable
    if position is collectible: mark collectible as found
    
    floodfill(x+1, y)  // right
    floodfill(x-1, y)  // left
    floodfill(x, y+1)  // down
    floodfill(x, y-1)  // up
```

This ensures all required game elements are accessible before starting the game.

### Error Messages

- `Error\nUsage: ./solong <map.ber>` - Invalid number of arguments
- `Error\nMap file must have .ber extension` - Wrong file extension
- `Error\nCannot open map file` - File doesn't exist or not readable
- `Error\nInvalid map dimensions` - Map too small or not rectangular
- `Error\nMap not surrounded by walls` - Missing wall borders
- `Error\nInvalid map elements` - Wrong number of P/E/C or invalid characters
- `Error\nNo valid path to exit/collectibles` - Unreachable objectives

## Map Reading Implementation

The map reader uses a **linked list approach** for efficient memory usage:

1. Read file line by line using `get_next_line()`
2. Store each line in a linked list node
3. Count total rows during reading
4. Convert linked list to `char **` array
5. Extract column count from first row
6. Clean up newline characters

This approach:
- Single-pass file reading (no need to read file twice)
- Dynamic memory allocation (handles any map size)
- Memory efficient (no realloc needed)
- Clean separation between reading and processing

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

## Testing

```bash
# Test with valid map
./solong maps/pass.ber

# Test with invalid map (unreachable areas)
./solong maps/fail.ber

# Memory leak check
valgrind --leak-check=full ./solong maps/pass.ber
```

## Project Structure

```
.
├── src/
│   ├── main.c              # Entry point and argument handling
│   ├── map.c               # Map reading and file validation
│   ├── map_validate.c      # Map validation and floodfill
│   ├── app_alloc.c         # Memory allocation
│   ├── app_free.c          # Memory deallocation
│   ├── solong.h            # Main header file
│   └── utils/              # Utility functions
│       ├── utils.c
│       ├── gnl.c           # Get next line implementation
│       └── utils.h
├── maps/                   # Map files
│   ├── pass.ber           # Valid test map
│   └── fail.ber           # Invalid test map (for testing)
├── printf/                 # Custom fprintf implementation
├── minilibx-linux/        # MiniLibX graphics library
└── Makefile
```

## Memory Management

The project implements strict memory management:
- All allocated memory is properly freed
- Valgrind reports: **0 memory leaks**
- Error handling includes memory cleanup
- Linked list intermediate storage is freed after conversion

```
HEAP SUMMARY:
  total heap usage: 43 allocs, 43 frees
All heap blocks were freed -- no leaks are possible
```

Thanks to tileset creator
https://toadzillart.itch.io/dungeons-pack