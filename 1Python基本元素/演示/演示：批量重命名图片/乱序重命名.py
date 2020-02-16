import os,random

chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-=@#$%^&~'

def generateRandomName(minLength = 30, maxLength = 50):
	length = random.randint(minLength, maxLength)
	name = "".join([random.choice(chars) for i in range(length)])
	return name

path='.\图片\\'
fileNameList=os.listdir(path)
for fileName in fileNameList:
	oldPathName = path + fileName
	newPathName = path + generateRandomName() + ".jpg"
	os.rename(oldPathName, newPathName)
print("已乱序重命名{0}个文件".format(len(fileNameList)))