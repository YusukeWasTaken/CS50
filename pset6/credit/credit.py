def main():
    while True:
        CCn = input("Type your credit card number: ")
        if CCn.isalpha() == False:
            if int(CCn) >= 0:
                break
   
    CCn = int(CCn)

    Sumf = CheckSum(CCn)
    
    if Sumf == 0:
        CCcheck(CCn)
    else:
        print("INVALID")

def CCcheck(CCn):
    if (CCn >= 340000000000000 and CCn < 350000000000000) or (CCn >= 370000000000000 and CCn < 380000000000000):
        print("AMEX")
    elif CCn >= 5100000000000000 and CCn < 5600000000000000:
        print("MASTERCARD")
    elif (CCn >= 4000000000000 and CCn < 5000000000000) or (CCn >= 4000000000000000 and CCn < 5000000000000000):
        print("VISA")
    else:
        print("INVALID 1")
        return 0

def CheckSum(CCn):
    n = 1; dig = 1; sumtraco = 0; sumntraco = 0; count = 2

    while CCn // n > 0:
        if count % 2 != 0:
            dig = (CCn // n) % 10
            dig *= 2
            if dig >= 10:
                dig = (dig % 10) + (dig // 10)
            sumtraco += dig
        else:
            dig = (CCn // n) % 10
            sumntraco += dig
        count += 1
        n *= 10

    Sum = sumntraco + sumtraco

    Sumf = Sum % 10

    print(Sum)
    return Sumf

main()
