import os
import subprocess
from os_list import os_list

def choose_menu(options, prompt="Выберите вариант: "):
    while True:
        print("Варианты:")
        for idx, option in enumerate(options, 1):
            print(f"{idx}. {option}")
        try:
            choice = int(input(prompt))
            if 1 <= choice <= len(options):
                return options[choice - 1]
        except ValueError:
            pass
        print("Некорректный ввод. Попробуйте снова.\n")

def remove_until_second_slash(s):
    first = s.find('/')
    if first == -1:
        return ''
    second = s.find('/', first + 1)
    if second == -1:
        return ''
    return s[second+1:]



def print_line():
    print(f"__________________________________")


if __name__ == "__main__"       :
    path = './tests'
    dirs = [name for name in os.listdir(path) if os.path.isdir(os.path.join(path, name))]
    # dirs = list(map(remove_until_second_slash, [x[0] for x in dirs]))
    dirs = [item for item in dirs if item != '']

    print_line()

    choose_dir = choose_menu(dirs)
    print(f"Вы выбрали тест: {choose_dir}")
    print_line()

    choose_os = choose_menu(os_list)
    print(f"Вы выбрали операционную систему: {choose_os}")
    print_line()

    subprocess.run([f"./tests/{choose_dir}/{choose_os}.sh"])


