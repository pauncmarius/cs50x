while True:
    try:
        n = int(input("Height: "))
        if n>0 and n<9:
            break
    except ValueError:
        print("Try a numeric one")

for i in range(1, n+1):
    for j in range(n-i):
        print(" ", end="")
    for j in range(i):
        print("#", end="")
    for j in [0,1]:
        print(" ", end="")
    for j in range(i):
        print("#", end="")
    print("")
