import re

def count_letters(text, n):
    count =0
    for i in range(n):
        if text[i].isalpha():
            count += 1
    return count

def count_words(text, n):
    count =0
    for i in range(n):
        if text[i].isspace():
            count += 1
    return count+1

def main():
    text = input("Text:")
    n = len(text)
    counter_letters = count_letters(text, n)
    counter_words = count_words(text, n)
    counter_sent = len(re.findall(r"[.!?]", text))

    L = (counter_letters / counter_words) * 100
    S = (counter_sent / counter_words) *100
    index = (0.0588 * L) - (0.296 * S) - 15.8

    if index < 1:
        print("Before Grade 1")
    elif (index >= 16):
        print("Grade 16+")
    else:
        print("Grade " + str(round(index)))

if __name__ == "__main__":
    main()
