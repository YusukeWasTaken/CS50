from sys import argv

while True:
    y = input("Height: ")
    if y.isnumeric() == True:
        if int(y) > 0 and int(y) < 9:
            break

nY = int(y)

for i in range(nY):
    print(" " * (nY - (i + 1)) + "#" * (i + 1) + "  " + "#" * (i + 1))