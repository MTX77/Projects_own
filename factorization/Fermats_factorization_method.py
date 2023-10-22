import math
print("Fermat's factorization method\n ")

n = input()

x = math.ceil (sqrt (int (n)))

y = math.sqrt(int (x) * int (x) - int(n))

i = 1

while (y - int (y) != 0):
    x += 1
    i +=1
    y = math.sqrt(int (x) * int (x) - int(n))
    
p = int (x) + int (y)
q = int (x) - int (y)
    
print(f"p: {p}\nq: {q}\nIterations: {i}")