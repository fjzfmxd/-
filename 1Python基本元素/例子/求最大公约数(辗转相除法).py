m = int(input("请输入第一个整数:"))
n = int(input("请输入第二个整数:"))

if m < n:
	m, n = n, m

while True:
	r = m % n
	if r != 0:
		m, n = n, r
	else:
		break
print("最大公约数为：", n)
