'''
这是一个简单的Python程序示例，用于展示各个元素
程序功能为计算输出身体质量指数，并给出WHO标准下的是否正常提示
BMI = 体重/(身高的平方)
'''

weight = float(input("请输入您的体重(KG): "))
height = float(input("请输入您的身高(M): "))
bmi = weight / height**2  # 计算身体质量指数
print("您的身体质量指数为:", bmi)
# WHO标准下，正常的BMI指数范围为18.5~24.9
if 18.5 <= bmi <= 24.9:
    print("指数在正常范围内，继续保持！")
else:
    print("指数不在正常范围内，请注意调整！")
print("程序结束")
