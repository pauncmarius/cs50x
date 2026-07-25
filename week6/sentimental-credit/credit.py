import re

while True:
    number = input("Number: ")
    if re.fullmatch(r"\d+", number):
        break

n = len(number)

temp_number = int(number)
total_temp1 = 0
total_temp2 = 0
result = '\0'

for i in range(n):
    digit = int(temp_number % 10);
    if (i % 2) == 0:
        total_temp1 += digit
    else:
        digit *= 2
        if digit > 9:
            digit -= 9
        total_temp2 += digit
    temp_number = int(temp_number/10)

total = total_temp1 + total_temp2

if (total % 10) == 0:
    result = 'y'
else:
    result = 'n'

if result == 'y':
    if (number[:2] == "34" or number[:2] == "37") and len(number) == 15:
        print("AMEX")
    elif (int(number[:2]) >= 51 and int(number[:2]) <= 55) and len(number) == 16:
        print("MASTERCARD")
    elif number[0] == "4" and (len(number) == 13 or len(number) == 16):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")

