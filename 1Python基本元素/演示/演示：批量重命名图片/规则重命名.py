import os

path='.\图片\\'
prefix = input("请输入文件名前缀(直接回车表示无前缀):")

index = 1
fileNameList=os.listdir(path)
for fileName in fileNameList:
	oldPathName = path + fileName
	newPathName = path + prefix + str(index) + ".jpg"
	os.rename(oldPathName, newPathName)
	index += 1
print("已规则重命名{0}个文件".format(len(fileNameList)))