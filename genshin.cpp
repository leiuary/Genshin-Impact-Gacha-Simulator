#include <stdio.h>
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

// 新增的进度条函数
void show_progress(float progress) {
    const int bar_width = 50;
    static int spin_counter = 0;
    const char spin[] = {'|', '/', '-', '\\'};
    
    int pos = static_cast<int>(bar_width * progress);
    
    cout << "[";
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    
    cout << "] " << int(progress * 100) << "% "
         << spin[spin_counter++ % 4] << " \r";
    cout.flush();
}

int RATE(int a){//RATE为出金概率计算, a为抽数count
    a++;
    if (a>=90) return 1000;
    else if (a>=74) return 6+(a-73)*60;
    else return 6;
}

int main() {
    setlocale(LC_ALL, "zh_CN.UTF-8");
    
    // 使用随机设备和mt19937生成随机数
    std::random_device rd;
    std::mt19937 gen(rd());
    // 生成 0 到 999 的均匀整数
    uniform_int_distribution<> coin(0, 1);
    std::uniform_int_distribution<> distrib(0, 999);


restart:
    long long int y = 0, n = 0, g = 0;//y为出货数，n为总抽数，g为出金数
    int baodi = 0,count = 0;//baodi为保底标志，count为抽数
    double c[90] = {0};//c为出货数统计数组
    printf("请输入抽数：");
    scanf("%llu",&n);

    // 新增进度跟踪变量
    int last_percent = -1;

    for (long long int i = 0; i < n; i++)
    {
        // 新增的进度显示（每1%更新）
        int current_percent = (i * 100) / n;
        if (current_percent != last_percent) {
            show_progress(float(i)/n);
            last_percent = current_percent;
        }

        if (distrib(gen) >= RATE(count))//未出货
        {
            count++;
        }
        else//出货
        {
            g++;
            if (baodi == 0)//小保底
            {   
                if (coin(gen))//出货
                {
                    c[count]++;
                    y++;
                }
                else//未出货
                {
                    baodi = 1;
                }
            }
            else//大保底
            {
                c[count]++;
                baodi = 0;
                y++;
            }
            count = 0;
        }
    }

    // 显示最终进度
    show_progress(1.0f);
    cout << endl;

    // 创建并输出到文件
    ofstream newFile("出货抽数占比.txt");
    std::ofstream output_file("出货抽数占比.txt");
    if (output_file.is_open()) {
        for (int i = 0; i < n; ++i) {
            double probability = (double)c[i] / y;
            output_file << i+1  << " " << probability << std::endl;
        }
        output_file.close();
    } else {
        std::cerr << "无法打开文件！" << std::endl;
    }

    printf("出货%llu,出金%llu,总抽数%llu\n出货率%f%%,出金率%f%%,不歪率%f%%\n出货抽数占比.txt已生成\n", y,g,n, (double)y / n * 100, (double)g / n * 100, (double)y / g * 100);
    goto restart;
    return 0;
}