import os

sound_name: str = input("Sound name: ")
sound_id: int = int(input("Sound id: "))

os.system(f"ffmpeg -i assets/sfx/sounds/{sound_name}.wav -ac 1 -ar 22050 -sample_fmt s16 romfs/sfx/sounds/{sound_id}.wav")