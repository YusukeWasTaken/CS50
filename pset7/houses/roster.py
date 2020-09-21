from cs50 import SQL
from sys import argv

db = SQL("sqlite:///students.db")

# Check the arguments
if len(argv) != 2:
    print("Usage: python import.py house_name")
    exit(1)


rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last ASC, first", argv[1])

for row in rows:
    if row["middle"] == None:
        print(row["first"], row["last"] + ", born", row["birth"])
    else:
        print(row["first"], row["middle"], row["last"] + ", born", row["birth"])

