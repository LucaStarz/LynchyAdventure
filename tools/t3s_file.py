t3s_file_id: str = input("T3S file id: ")
t3s_count: int = int(input("T3S sprites count: "))
t3s_folder: str = input("T3S gfx folder: ")

with open(f"assets/gfx/{t3s_file_id}.t3s", "w") as output_file:
    output_file.write("--atlas -f rgba8888 -z auto\n")
    for i in range(t3s_count):
        output_file.write(f"{t3s_folder}/{i}.png\n")