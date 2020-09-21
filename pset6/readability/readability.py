text = input("Write the text you want to grade: ")

letter = 0
words = 0
sentence = 0

for i in range(len(text)):
    if text[i].isalpha():
        letter += 1
    if text[i] == " " or i == 0:
        words += 1
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentence += 1

L = letter * 100 / words
S = sentence * 100 / words

index = 0.0588 * L - 0.296 * S - 15.8

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade " + str(round(index)))