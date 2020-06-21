//Date:2020-03-27
//MyName:2018051604006范玉杰
//简介：一个简单的计算器
//版本号1.0(也许、可能、大概会尝试去更新迭代,检查BUG,修改BUG)
//PS:1.0版本只支持2个数字之间的四则运算
//会出现较大计算结果自动转化为科学计数法输出的情况,例如20000121×20200329=4.04009e+14,还在想办法...

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();

private slots:
    void on_pushButton_quit_clicked();

    void on_pushButton_dian_clicked();

    void on_pushButton_dengyu_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_AC_clicked();

    void on_pushButton_chu_clicked();

    void on_pushButton_cheng_clicked();

    void on_pushButton_jian_clicked();

    void on_pushButton_jia_clicked();

    void on_pushButton_00_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:

    Ui::calculator *ui;
    QString S;//第1个数
    QString S2;//第2个数
    float result;//计算结果
    int choose;//根据choose的值来判断按了哪个运算符,choose为0,1,2,3,4分别代表无运算符,加,减,乘,除，默认值为0
    int point;//point为1说明一个数字中已有小数点，则不能再添加小数点,默认值为0
    int dh;//用于判断：dh=0,还没按下等号;dh=-1,按下等号紧接着按下运算符按钮;dh=1,按下等号后按数字,进行新一轮的运算,所有变量回到默认值
    int num;//算式中数的个数
    float sum;//计算结果的暂存变量
    int sum2;//计算结果的暂存变量2
};

#endif // CALCULATOR_H

