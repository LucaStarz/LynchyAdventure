# Zone files

## Preamble

- u16 : left neighbor (0 = none)
- u16 : top neighbor (0 = none)
- u16 : right neighbor (0 = none)
- u16 : bottom neighbor (0 = none)
- list[u16] : list of spritesheets' id to load
- u16(0) : end of the previous list

## Data section

- list[u16,u16] (25x15) : background entities (spritesheet id + sprite index)
- list[u16,u16] (25x15) : more background entities (spritesheet id + sprite index)
- list[u16,u16] (25x15) : foreground entities (spritesheet id + sprite index)
- list[u16,u16] (25x15) : more foreground entities (spritesheet id + sprite index)
- list[u16,u16,u16,u16,u8] : list of colliders (x, y, w, h, layer)
- u16(0),u16(0),u16(0),u16(0),u8(0) : end of the previous list

Note : Lines could be smaller than expecting if terminated by a 1.

Note : 0 and 1 are special spritesheets' id, without sprite index.
