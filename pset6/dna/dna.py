from sys import argv
import csv

# Check if it were given 3 arguments
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# Open DB
row = {}
with open(argv[1], newline='') as csvfile:
    Dbase = csv.DictReader(csvfile)
    for row in Dbase:
        pass

# Open Sequence // seq = Sequence
seq = open(argv[2], "r")
seq = seq.read()

# Sequences
lista = list(row.keys())

NewList = []
NewList.append("name")

for i in lista[1:]:

    maxcount = 0
    count = 0
    tamanho = len(i)
    k = 0
    sequence = len(seq)

    while k < sequence:
        if i == seq[k:k + tamanho]:
            count += 1
            k += tamanho
        else:
            count = 0
            k += 1
        if maxcount < count:
            maxcount = count
    NewList.append(maxcount)

# print(NewList)
# print(len(lista) - 1)

# Open DB
row = {}
with open(argv[1], newline='') as csvfile:
    Dbase = csv.DictReader(csvfile)
    for row in Dbase:
        counter = 0
        # For each combination
        for i in range(1, len(lista)):
            # Compare the DB to the Seq
            if (NewList[i]) != int(row[lista[i]]):
                break
            counter += 1
        if counter == len(lista) - 1:
            print(row[lista[0]])
            exit(0)
    if counter != len(lista) - 1:
        print("No Match")