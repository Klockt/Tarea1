import random
import re
import os
import time

#Variables globales#
binario = r'^[01]+$'
octal = r'^[0-7]+$'
hexa = r'^[0-9A-F]+$'
template = "\nIngresa una acción!\nw:moverse hacia arriba\ns:moverse hacia abajo\na:moverse a la izquierda\nd:moverse a la derecha\n-1:salir\n"
template2 = "Escribe la cantidad de pasos que quieres moverte hacia {} en formato {}: "
template3 = "Esta transmisión está encriptada con un código {} crítico: {}."
win_msj = "\033[33m\n¡Misión cumplida, Snake!\nHas descifrado el código con precisión quirúrgica.\nGracias a ti, el equipo podrá avanzar con la operación.\nEl Coronel está impresionado… ¡y yo también!\nPrepárate para la siguiente misión.\nEsto solo es el principio.\033[0m"
lose_msj = "\033[31m\nSnake... fallaste en descifrar el código.\nLa operación fue comprometida, y el enemigo ahora tiene ventaja.\nNo todo está perdido, pero debes mantener la concentración.\nEl mundo depende de ti.\n¡Prepárate para intentarlo de nuevo!\n\033[0m"
move = {"w":"arriba", "s":"abajo", "a":"la izquierda", "d":"la derecha", "-1":"salir"}
hex_to_decimal = {"A": 10, "B": 11, "C": 12, "D": 13, "E": 14, "F": 15}
decimal_to_hex = {10: "A", 11: "B", 12: "C", 13: "D", 14: "E", 15: "F"}
snake_status = "alive" # alive, dead, hacking, win
snake_position = {"X": 5, "Y": 0}
#------------------#


def print_board():
    '''
    ***
    Sin parametro
    ***
    Sin retorno
    ***
    Limpia la terminal y limpia el tablero
    '''
    os.system("clear")  
    for list in mx_b:
        print("".join(list))
    if snake_status == "dead":
        print("\033[31mSnaaaake! Snaaaaaake!\033[0m\nGame Over")
    elif snake_status == "hacking":
        print("\nINICIANDO PROTOCOLO...\nAccediendo a la transmisión enemiga...\n\033[32m'Snake, esto no tiene vuelta atrás... La misión depende de ti.'\033[0m\n[HACKING EN PROCESO]\n")


def matrix( large, guards ):
    '''
    ***
    large : int
    guards : int
    ***
    mx_base : lista de listas
    ***
    crea la matriz base dependiendo de large, colocando el objetivo, los guardias y a Snake, retornando una matriz
    '''
    mx_base = []
    i = 0
    x = random.randint(0, 10)
    while i < 11:
        mx_base.append(['X'] * large)
        if i == 5:
            mx_base[i][0] = '\033[32mS\033[0m' # S EN VERDE
        if i == x:
            mx_base[i][large - 1] = '\033[33m*\033[0m' # * EN AMARILLO
        i += 1
    i = 0
    while i < guards:
        x, y = random.randint(0,10), random.randint(0, large-1)
        if mx_base[x][y] != '\033[32mS\033[0m' and mx_base[x][y] != '\033[33m*\033[0m':
            mx_base[x][y] = '\033[31m!\033[0m' # ! EN ROJO
        i += 1
    return mx_base

def generate_bin(decimal):
    '''
    ***
    decimal : int
    ***
    binario : str
    ***
    convierte un número decimal a binario
    '''
    bin_str = ""
    while decimal != 0:
        bin_str += str(decimal % 2)
        decimal //= 2
    return bin_str[::-1]

def generate_oct(decimal):
    '''
    ***
    decimal : int
    ***
    octal : str
    ***
    convierte un número decimal a octal
    '''
    oct_str = ""
    while decimal != 0:
        oct_str += str(decimal % 8)
        decimal //= 8
    return oct_str[::-1]

def generate_hex(decimal):
    '''
    ***
    decimal : int
    ***
    hexadecimal : str
    ***
    convierte un número decimal a hexadecimal
    '''
    hex_str = ""
    while decimal != 0:
        rest =decimal % 16
        if rest in decimal_to_hex:
            hex_str += decimal_to_hex[rest]
        else:
            hex_str += str(rest)
        decimal //= 16
    return hex_str[::-1]


def binary(bin_str): 
    '''
    ***
    bin_str : str.
    ***
    total : int
    ***
    realiza la conversion de binario a decimal, retornando un entero
    '''
    count, total = 0, 0
    for bit in bin_str[::-1]:  # [::-1] invierte el string bin_str = "1011"
        bit = int(bit)
        total += bit * (2**count)
        count += 1
    return total

def oct(oct_str):
    '''
    ***
    oct_str : str
    ***
    total : int
    ***
    realiza la conversion de octal a decimal, retornando un entero
    '''
    count, total = 0, 0
    for bit3 in oct_str[::-1]:
        bit3 = int(bit3)
        total += bit3 * (8**count)
        count += 1
    return total

def hex(hex_str):
    '''
    ***
    hex_str : str
    ***
    total : int
    ***
    realiza la conversion de binario a hexadecimal, retornando un entero
    '''
    count, total = 0, 0
    for nibble in hex_str[::-1]:
        if nibble in hex_to_decimal:
            nibble = hex_to_decimal[nibble]
        else:
            nibble = int(nibble)
        total += nibble * (16**count)
        count += 1
    return total

def snake_collision():
    '''
    ***
    Sin parametros
    ***
    Sin retorno
    ***
    Detecta si Snake colisiona con el objetivo o con un guardia
    '''
    snake = mx_b[snake_position["X"]][snake_position["Y"]]
    global snake_status
    if snake == '\033[31m!\033[0m':
        snake_status = "dead"
        mx_b[snake_position["X"]][snake_position["Y"]] = '\033[31m[RIP]\033[0m' # RIP EN ROJO
    elif snake == '\033[33m*\033[0m':
        snake_status = "hacking"
        mx_b[snake_position["X"]][snake_position["Y"]] = '\033[31m[H\033[33mA\033[32mC\033[36mK\033[34mI\033[35mN\033[31mG\033[33m]\033[0m' # [HACKING] EN RAINBOW
    return

def snake_mov(direction, steps, large):  # X : Filas , Y : Columnas
    '''
    ***
    direction : str
    steps : int
    large : int
    ***
    Sin retorno
    ***
    Mueve a Snake en la dirección especificada
    '''
    mx_b[snake_position["X"]][snake_position["Y"]] = 'X'
    count = 1
    if direction == "w":
        while count <= steps and snake_status == "alive":
            if snake_position["X"] - 1 > -1:
                snake_position["X"] -= 1
                snake_collision()
            count += 1
    elif direction == "s":
        while count <= steps and snake_status == "alive":
            if snake_position["X"] + 1 < 11:
                snake_position["X"] += 1
                snake_collision()
            count += 1
    elif direction == "a":
        while count <= steps and snake_status == "alive":
            if snake_position["Y"] - 1 > -1:
                snake_position["Y"] -= 1
                snake_collision()
            count += 1
    elif direction == "d":
        while count <= steps and snake_status == "alive":
            if snake_position["Y"] + 1 < large:
                snake_position["Y"] += 1
                snake_collision()
            count += 1
    if snake_status == "alive":
        mx_b[snake_position["X"]][snake_position["Y"]] = '\033[32mS\033[0m'
    return

def main():
    large = input( "Ingresar largo de los pasillos: ")
    while not re.match(r'^[1-9][0-9]*$', large):
        large = input( "Ingresar largo de los pasillos: ")
    guards = input( "Ingresar cantidad de guardias: ")
    while not re.match(r'^([1-9][0-9]*|0)$', guards):
        guards = input( "Ingresar cantidad de guardias: ")

    large, guards = int(large), int(guards)

    global mx_b, snake_status
    mx_b = matrix( large, guards ) 
    for list in mx_b:
        list = "".join(list)
        print(list)
    direction = (input(template))
    while direction not in move:
            direction = (input(template))
    
    while direction != "-1" and snake_status == "alive": # Mientras no se ejecute comando -1 o snake viva o llegue al punto este while debera seguir (idea)
        if large <= 20:
            steps = input(template2.format((move[direction]), "Binario"))
            while not re.match(binario, steps):
                steps = input(template2.format((move[direction]), "Binario"))
            snake_mov(direction, binary(steps), large)

        elif large > 20 and large <= 100:
            steps = input(template2.format((move[direction]), "Octal"))
            while not re.match(octal, steps):
                steps = input(template2.format((move[direction]), "Octal"))
            snake_mov(direction, oct(steps), large)
            
        elif large > 100:
            steps = input(template2.format((move[direction]), "Hexadecimal"))
            while not re.match(hexa, steps):
                steps = input(template2.format((move[direction]), "Hexadecimal"))
            snake_mov(direction, hex(steps), large)
        
        print_board()
        time.sleep(0.1)
        if snake_status == "alive":
            direction = (input(template))
            while direction not in move:
                direction = (input(template))

    if snake_status == "hacking":
        if large <= 20:        
            range = random.randint(0, 20) 
            code = generate_bin(range)
            print(template3.format("Binario", code))
            msj = input("Desencripta el mensaje y entrega el número decimal equivalente: ")
            if not re.match(r'^[0-9]+$', msj):
                snake_status = "lose"
            elif code == generate_bin(int(msj)):
                snake_status = "win"
            else:
                snake_status = "lose"

        elif large > 20 and large <= 100:
            range = random.randint(0, 100)
            code = generate_oct(range)
            print(template3.format("Octal", code))
            msj = input("Desencripta el mensaje y entrega el número decimal equivalente: ")
            if not re.match(r'^[0-9]+$', msj):
                snake_status = "lose"
            elif code == generate_oct(int(msj)):
                snake_status = "win"
            else:
                snake_status = "lose"

        elif large > 100:
            range = random.randint(0, 500)
            code = generate_hex(range)
            print(template3.format("Hexadecimal", code))
            msj = input("Desencripta el mensaje y entrega el número decimal equivalente: ")
            if not re.match(r'^[0-9]+$', msj):
                snake_status = "lose"
            elif code == generate_hex(int(msj)):
                snake_status = "win"
            else:
                snake_status = "lose"

    if snake_status == "lose":
        print(lose_msj)
    elif snake_status == "win":
        print(win_msj)
    return

if __name__ == "__main__":
    main()