//Date:2020-03-27
//MyName:2018051604006范玉杰
//简介：一个简单的计算器
//版本号1.0(也许、可能、大概会尝试去更新迭代,检查BUG,修改BUG)
//PS:1.0版本只支持2个数字之间的四则运算
//会出现较大计算结果自动转化为科学计数法输出的情况,例如20000121×20200329=4.04009e+14,还在想办法...

#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calculator w;
    w.show();
    return a.exec();
}
