import csv

k = int(input())
new = [[-1, -1, 10 ** 9]]
with open('new.csv') as f:
    reader = csv.DictReader(f)
    for row in reader:
        new.append([row["date"], row["time"], float(row["price"])])


n = len(new) - 1
k = min(k, n // 2)
max_money = [[0] * (k + 1) for _ in range(n + 1)]
p = [[(0, 0)] * (k + 1) for _ in range(n + 1)]
for i in range(n + 1):
    max_money[i][0] = 1

for j in range(1, k + 1):
    max_ind = 0
    for i in range(1, n + 1):
        max_money[i][j] = max_money[i - 1][j]
        p[i][j] = p[i - 1][j]
        if (max_money[max_ind][j - 1] * new[i][2] / new[max_ind][2]) > max_money[i][j]:
                max_money[i][j] = max_money[max_ind][j - 1] * new[i][2] / new[max_ind][2]
                p[i][j] = (max_ind, j - 1)
        if (max_money[i][j - 1] / new[i][2] > max_money[max_ind][j - 1] / new[max_ind][2]):
            max_ind = i


optimal_k = 0
for j in range(k + 1):
    if (max_money[n][j] > max_money[n][optimal_k]):
        optimal_k = j
current_k = optimal_k
current_i = n
buys = []
while True:
    if (p[current_i][current_k][1] == current_k):
        current_i -= 1
    else:
        buys.append((p[current_i][current_k][0], current_i))
        current_i = p[current_i][current_k][0]
        current_k -= 1
    if (current_i == 0 or current_k == 0):
        break



for i in buys[::-1]:
    print(f"Date buy: {new[i[0]][0]}, Date sell: {new[i[1]][0]}, profit: {new[i[1]][2] / new[i[0]][2]}")