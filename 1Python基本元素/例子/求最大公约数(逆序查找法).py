m = int(input("请输入第一个整数:"))
n = int(input("请输入第二个整数:"))

k = min(m, n)

for i in range(k+1, 0, -1):
	if m % i == 0 and n % i == 0:
		print("最大公约数为：", i)
		break
