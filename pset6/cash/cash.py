def main():
    while True:
        dollars = input("How much dollars do you owe?")
        if dollars.isalpha() == False and dollars != " " and dollars != "":
            if float(dollars) >= 0:
                break
    cents = round(float(dollars) * 100)
    count(cents)


def count(cents):

    coins = 0
    
    while cents >= 25:
        cents -= 25
        coins += 1
    while cents >= 10:
        cents -= 10
        coins += 1
    while cents >= 5:
        cents -= 5
        coins += 1
    while cents >= 1:
        cents -= 1
        coins += 1
    
    print(coins)


main()