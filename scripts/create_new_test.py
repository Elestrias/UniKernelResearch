import os
from os_list import os_list
import shutil

dir_name = "./tests/" + input("New test name: ")

script_names = list(map(lambda x: x + '.sh', os_list))
os.makedirs(dir_name, exist_ok=True)


for name in script_names:
    shutil.copy('scripts/runners/' + name, dir_name)
shutil.copy('scripts/unikraft_files/Dockerfile', dir_name)
shutil.copy('scripts/unikraft_files/Kraftfile', dir_name)
file_path = os.path.join(dir_name, 'main.c')
try:
    with open(file_path, 'x') as f:
        f.write("#include <stdio.h>\n\nint main() {\n\tprintf(\"Hello world!\");\n\treturn 0;\n}")
except FileExistsError:
    print('File already exists.')

print("Done!")
