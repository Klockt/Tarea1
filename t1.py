import random

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
            mx_base[i][0] = 'S'
        if i == x:
            mx_base[i][large - 1] = '*'
        i += 1
    i = 0
    while i < guards:
        x, y = random.randint(0,10), random.randint(0, large-1)
        if mx_base[x][y] != 'S' and mx_base[x][y] != '*':
            mx_base[x][y] = '!'
        i += 1
    return mx_base


def main():
    large = int (input( "Ingresar largo de los pasillos: "))
    guards = int (input( "Ingresar cantidad de guardias: "))
    mx_b = matrix( large, guards ) 
    for list in mx_b:
        list = "".join(list)
        print(list)
    
    return



if __name__ == "__main__":
    main()