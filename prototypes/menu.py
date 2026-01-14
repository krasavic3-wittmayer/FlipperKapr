from typing import Callable
import keyboard
import os
import time

index = 0

type menu_type = list[tuple[str, Callable[..., bool | None]]]

def show_string(menu: menu_type) -> None:
    str1: str = menu[index][0]

    if index + 1 >= len(menu):
        str2: str = menu[0][0]
    else:
        str2: str = menu[index + 1][0]
    
    os.system("cls")
    print("-> " + str1)
    print("  " + str2)

def menu(menu: menu_type) -> Callable[..., bool]:
    def run():
        global index
        index = 0
        show_string(menu)

        while True:
            if keyboard.is_pressed("down"):
                while keyboard.is_pressed("down"):
                    time.sleep(0.001)
                index += 1
                if index >= len(menu):
                    index = 0
                show_string(menu)
            
            elif keyboard.is_pressed("up"):
                while keyboard.is_pressed("up"):
                    time.sleep(0.001)
                index -= 1
                if index == -1:
                    index = len(menu) - 1
                show_string(menu)
            
            if keyboard.is_pressed("enter"):
                while keyboard.is_pressed("enter"):
                    time.sleep(0.001)

                temp_index = index

                if menu[index][1]():
                    break
                else:
                    index = temp_index

                show_string(menu)
            
            time.sleep(0.01)
        
        return False
    
    return run

menu([
    ("1.", lambda: True),
    ("2.", lambda: True),
    ("3.", lambda: True),
    ("4.", lambda: True),
    ("5.", menu([
        ("5.1", lambda: True),
        ("5.2", lambda: print("5.2")),
        ("5.3", lambda: True),
        ("5.4", lambda: True),
        ("5.5", lambda: True),
    ])),
])()