'''
汉诺塔问题
P151
'''

def hannoiHelper(source, helper, dest, count):
    steps = []
    def hannoi(source, helper, dest, count):
        if(count == 1):
            steps.append("Move TOP from {} to {}".format(source,dest))
            return
        hannoi(source, dest, helper, count - 1)
        steps.append("Move TOP from {} to {}".format(source,dest))
        hannoi(helper, source, dest, count - 1)
    hannoi(source, helper, dest, count)
    return steps

source,helper,dest,count = "A","B","C",6
try:
    count = int(input("请输入汉诺塔的层数(默认6层):"))
except:
    pass

steps = hannoiHelper(source,helper,dest,count)
info = "{}层汉诺塔从{}移动到{}，借助{}，共需要{}步:".format(count,source,dest,helper,len(steps))

print(info)
for step in steps:
    print("\t",step)

# file = open("steps.txt", "w",encoding="utf-8")
# file.write(info+"\n")
# file.writelines(step + "\n" for step in steps)
# file.close()