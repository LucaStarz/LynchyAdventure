weapon_name: str = input("Weapon name: ")

with open(f"assets/weapons/{weapon_name}.txt", "r") as weapon_src_file:
    weapon_data: list[str] = weapon_src_file.readline().replace("\n", "").split(" ")
    weapon_data += weapon_src_file.readline().replace("\n", "").split(" ")
    weapon_data += weapon_src_file.readline().replace("\n", "").split(" ")
    weapon_data += weapon_src_file.readline().replace("\n", "").split(" ")
    weapon_data += weapon_src_file.readline().replace("\n", "").split(" ")
    
    with open(f"romfs/weapons/{int(weapon_data[0])}.wdf", "wb") as weapon_out_file:
        weapon_out_file.write(int(weapon_data[1]).to_bytes(2, "little")) # duration
        weapon_out_file.write(int(weapon_data[2]).to_bytes(1, "little")) # damage

        for i in range(4):
            weapon_out_file.write(int(weapon_data[i * 4 + 3]).to_bytes(2, "little", signed=True)) # offset x
            weapon_out_file.write(int(weapon_data[i * 4 + 4]).to_bytes(2, "little", signed=True)) # offset y
            weapon_out_file.write(int(weapon_data[i * 4 + 5]).to_bytes(2, "little")) # width
            weapon_out_file.write(int(weapon_data[i * 4 + 6]).to_bytes(2, "little")) # height