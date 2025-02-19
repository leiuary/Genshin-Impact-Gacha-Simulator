import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

# 读取概率数据
x = []
y = []

with open("出货抽数占比.txt", "r") as file:
    for line in file:
        num, prob = line.split()
        x.append(int(num))
        y.append(float(prob))

# 绘制概率分布图
plt.bar(x, y, width=0.8, color='skyblue', edgecolor='black')
plt.xlabel('抽数')
plt.ylabel('出现概率')
plt.title('出货概率分布')
plt.show()
