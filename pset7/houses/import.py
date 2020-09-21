from cs50 import SQL
from sys import argv
import csv

db = SQL("sqlite:///students.db")

# Check the arguments
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# Open DB
row = {}
with open(argv[1], newline='') as csvfile:
    Dbase = csv.DictReader(csvfile)
    for row in Dbase:
        # Separate each part of the name First // Middle // Last
        name = row["name"].split(" ")
        # Check for the number of names, if it doesn't have a middle one insert none
        if len(name) != 3:
            name.insert(1, None)
        db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?,?,?,?,?)",
        name[0], name[1], name[2], row["house"], row["birth"])