# IMPORTS
from enum import Enum
import json
import math


# CONSTANTS
ZERO: bytes = bytes.fromhex("00 00")
ZONE_WIDTH: int = 25
ZONE_HEIGHT: int = 15


# SPRITESHEETS
class Spritesheet(Enum):
    # id, name, count, first_id(runtime), linked_ids(optional)
    # 0 ->              empty tile
    # 1 ->              end of line
    GreenFloor =        [2, "green_floor.tsx", 60, math.inf]
    Plant =             [3, "plant.tsx", 1, math.inf]
    GreenWater =        [4, "green_water.tsx", 47, math.inf]
    DarkMill =          [5, "dark_mill.tsx", 1, math.inf]
    BlackFlag =         [6, "black_flag.tsx", 1, math.inf]
    # 7 ->              player_left
    # 8 ->              player_top
    # 9 ->              player_right
    # 10 ->             player_bottom
    LightMill =         [11, "light_mill.tsx", 1, math.inf]
    SimpleHouse =       [12, "simple_house.tsx", 9, math.inf]
    WoodFence =         [13, "wood_fence.tsx", 14, math.inf]
    GreenBamboo =       [17, "green_bamboo.tsx", 1, math.inf, (14, 15, 16)]
    # 18 ->             life_receptacle
    # 19 ->             axe
    # 20 ->             stick
    # 21 ->             dead
    # 22 ->             coin
    DarkGreenFloor =    [23, "dark_green_floor.tsx", 60, math.inf]
    BlueFlag =          [24, "blue_flag.tsx", 1, math.inf]
    BrownFlag =         [25, "brown_flag.tsx", 1, math.inf]
    GrayFlag =          [26, "gray_flag.tsx", 1, math.inf]
    GreenFlag =         [27, "green_flag.tsx", 1, math.inf]
    RedFlag =           [28, "red_flag.tsx", 1, math.inf]
    WhiteFlag =         [29, "white_flag.tsx", 1, math.inf]
    YellowFlag =        [30, "yellow_flag.tsx", 1, math.inf]
    GreenPipe =         [31, "green_pipe.tsx", 14, math.inf]
    # 32 ->             heart


# VARIABLES
zone_id: int = int(input("Zone id: "))
left_id: int = 0
top_id: int = 0
right_id: int = 0
bottom_id: int = 0

zone_spritesheets: list[int] = []
zone_sprites: list[tuple[int, int]] = []
zone_collisions: list[tuple[int, int, int, int, int]] = []


# FUNCTIONS
def read_tileset(tileset) -> None:
    for sprt in Spritesheet:
        if sprt.value[1] == tileset["source"]:
            sprt.value[3] = tileset["firstgid"]
            return

def read_layer(layer, sprites: list[tuple[int, int]], spritesheets: list[int]) -> None:
    pos: int = 0
    for y in range(ZONE_HEIGHT):
        last_used: int = 0
        line: list[tuple[int, int]] = []

        for x in range(ZONE_WIDTH):
            sprite: int = layer[pos]
            pos += 1

            spritesheet: Spritesheet = None
            for sprt in Spritesheet:
                if sprite >= sprt.value[3] and sprite <= sprt.value[3] + sprt.value[2] - 1:
                    spritesheet = sprt
                    break
            
            if spritesheet is not None:
                if spritesheet.value[0] not in spritesheets:
                    spritesheets.append(spritesheet.value[0])
                    if len(spritesheet.value) > 4:
                        for linked in spritesheet.value[4]:
                            spritesheets.append(linked)

                line.append((spritesheet.value[0], sprite - spritesheet.value[3]))
                last_used = x + 1
            else:
                line.append((0, 0))
        
        for i in range(last_used):
            sprites.append(line[i])
        if last_used < ZONE_WIDTH:
            sprites.append((1, 0))

def read_collision(collision, collisions: list[tuple[int, int, int, int, int]]) -> None:
    col_layer: int = 0
    if "water" in collision["type"]: col_layer |= 0b0000_1000
    if "terrain" in collision["type"]: col_layer |= 0b0000_0010

    if col_layer == 0:
        print(f"La collision en ({collision["x"]}, {collision["y"]}) ne contient aucune classe !")
        exit(0)

    collisions.append((collision["x"], collision["y"], collision["width"], collision["height"], col_layer))

def read_neighbours(background_layer) -> None:
    global left_id, right_id, top_id, bottom_id
    bottom_id = int(background_layer[0]["value"])
    left_id = int(background_layer[1]["value"])
    right_id = int(background_layer[2]["value"])
    top_id = int(background_layer[3]["value"])


# READ INPUT
with open(f"assets/zones/{zone_id}.tmj", "r") as json_file:
    json_data: dict = json.load(json_file)
    for tileset in json_data["tilesets"]:
        read_tileset(tileset)

    read_neighbours(json_data["layers"][0]["properties"])

    for layer in json_data["layers"][:4]:
        read_layer(layer["data"], zone_sprites, zone_spritesheets)
    
    for collision in json_data["layers"][-1]["objects"]:
        read_collision(collision, zone_collisions)


# WRITE OUTPUT
with open(f"romfs/zones/{zone_id}.zdf", "wb") as zone_file:
    # Preamble
    zone_file.write(left_id.to_bytes(2, "little"))
    zone_file.write(top_id.to_bytes(2, "little"))
    zone_file.write(right_id.to_bytes(2, "little"))
    zone_file.write(bottom_id.to_bytes(2, "little"))

    for sprt in zone_spritesheets:
        zone_file.write(sprt.to_bytes(2, "little"))
    zone_file.write(ZERO)

    # Data section
    for spr in zone_sprites:
        zone_file.write(spr[0].to_bytes(2, "little"))
        if spr[0] > 1:
            zone_file.write(spr[1].to_bytes(2, "little"))
    
    for col in zone_collisions:
        for elt in col[:4]:
            zone_file.write(elt.to_bytes(2, "little"))
        zone_file.write(col[-1].to_bytes(1, "little"))
    for _ in range(4):
        zone_file.write(ZERO)
    zone_file.write(bytes.fromhex("00"))