//Date:2020-03-27
//MyName:2018051604006范玉杰
//简介：一个简单的计算器
//版本号1.0(也许、可能、大概会尝试去更新迭代,检查BUG,修改BUG)
//PS:1.0版本只支持2个数字之间的四则运算
//会出现较大计算结果自动转化为科学计数法输出的情况,例如20000121×20200329=4.04009e+14,还在想办法...

#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)//进行初始化
{
    ui->setupUi(this);
    ui->lineEdit->setText("请输入数字：");
    S="";//第1个数
    S2="";//第2个数
    result=0;//计算结果默认为0
    num =0;//算式中数的个数
    choose=0;//式中没有运算符
    point=0;//式中不存在小数点
    dh=0;//表示呈现初始化状态,即未按下等号按钮
    sum=0;//计算结果的暂存变量
    sum2 =0;//计算结果的暂存变量2
}

calculator::~calculator()
{
    delete ui;
}

void calculator::on_pushButton_quit_clicked()//退出按钮
{
    close();
}

void calculator::on_pushButton_dengyu_clicked()//等于号
{
    if(dh==0 && choose==0)//无运算符,即处理01=1,003=3等等这类
    {
            result=S.toFloat();
            QString data = QString("%1").arg(result);
            ui->lineEdit->setText(data);
    }
    if(dh==0 && choose==0 && num ==1)//类似"2+","9-"等不完整表达式，一律报错
    {
            ui->lineEdit->setText("输入有误,请检查后重新输入...");
    }
    if(choose==1){//加法运算
        if(dh==0){//作为一次全新的计算
            result=S.toFloat()+S2.toFloat();//result为float类型
            QString data = QString("%1").arg(result);
            ui->lineEdit->setText(S+"+"+S2+"="+data);
            sum=result;//暂存计算结果,用于处理"1+1=2,+3+5"这类情况
            choose=0;//此时表达式中无运算符
            S="";//第一个字符串置空(第1个数所在)
            S2="";//第2个字符串置空(第2个数所在)
            dh=1;//如果刚按了等号又按数字，相当于做了一次AC，如果按了等号再按加号，就继续计算。
            num=0;
            sum2=1;
        }
        else if(dh==-1){//以上一轮计算结果作为第一个加数
            result+=S.toFloat()+S2.toFloat();//result为float类型
            QString data = QString("%1").arg(result);//float类型转为QString字符串类型
            QString data2 = QString("%1").arg(sum);
            ui->lineEdit->setText(data2+"+"+S2+"="+data);
            sum=result;
            choose=0;//此时表达式中无运算符
            S="";//第一个字符串置空(第1个数所在)
            S2="";//第2个字符串置空(第2个数所在)
            dh=1;//如果刚按了等号又按数字，相当于做了一次AC，如果按了等号再按加号，就继续计算。
            num=0;
            sum2=1;
        }
    }

    if(choose==2){//减法运算
        if(dh==0){//作为一次全新的计算
            result=S.toFloat()-S2.toFloat();//result为float类型
            QString data = QString("%1").arg(result);
            ui->lineEdit->setText(S+"-"+S2+"="+data);
            sum=result;
            choose=0;//此时表达式中无运算符
            S="";//第一个字符串置空(第1个数所在)
            S2="";//第2个字符串置空(第2个数所在)
            dh=1;//如果刚按了等号又按数字，相当于做了一次AC，如果按了等号再按加号，就继续计算。
            num=0;
            sum2=1;
        }
        else if(dh==-1){//以上一轮计算结果作为减数
            result+=S.toFloat()-S2.toFloat();//result为float类型
            QString data = QString("%1").arg(result);//float类型转为QString字符串类型
            QString data2 = QString("%1").arg(sum);
            ui->lineEdit->setText(data2+"-"+S2+"="+data);
            sum=result;
            choose=0;//此时表达式中无运算符
            S="";//第一个字符串置空(第1个数所在)
            S2="";//第2个字符串置空(第2个数所在)
            dh=1;//如果刚按了等号又按数字，相当于做了一次AC，如果按了等号再按加号，就继续计算。
            sum2=1;
            num=0;
        }
    }



    if(choose==3){//乘法运算
        if(dh==0){//作为一次全新的计算
            result=S.toFloat()*S2.toFloat();//result为float类型
            QString data = QString("%1").arg(result);
            ui->lineEdit->setText(S+"×"+S2+"="+data);
            sum=result;
            choose=0;//此时表达式中无运算符
            S="";//第一个字符串置空(第1个数所在)
            S2="";//第2个字符串置空(第2个数所在)
            dh=1;//如果刚按了等号又按数字，相当于做了一次AC，如果按了等号再按加号，就继续计算。
            num=0;
            sum2=1;
        }
        else if(dh==-1){//以上一轮计算结果作为第一个乘数
            result=sum*S2.toFloat();//result为float类型
            QString data = QString("%1").arg(result);//float类型转为QString字符串类型
            QString data2 = QString("%1").arg(sum);
            ui->lineEdit->setText(data2+"×"+S2+"="+data);
            sum=result;
            choose=0;//此时表达式中无运算符
            S="";//第一个字符串置空(第1个数所在)
            S2="";//第2个字符串置空(第2个数所在)
            dh=1;//如果刚按了等号又按数字，相当于做了一次AC，如果按了等号再按加号，就继续计算。
            sum2=1;
            num=0;
        }
    }

    if(choose==4){//除法运算
        if(S2.toFloat()==0){//除数为零，清空表达式,并告知用户
            ui->lineEdit->setText("输入有误,请检查后重新输入...");
            S="";
            S2="";
            result=0;
            num = 0;
            choose=0;
            sum=0;
            point=0;
            dh=1;
        }else if(S2.toFloat()!=0){//除数不为零
            if(dh==0){//作为一次全新的计算
                result=S.toFloat()/S2.toFloat();//result为float类型
                QString data = QString("%1").arg(result);
                ui->lineEdit->setText(S+"÷"+S2+"="+data);
                sum=result;
                choose=0;//此时表达式中无运算符
                S="";//第一个字符串置空(第1个数所在)
                S2="";//第2个字符串置空(第2个数所在)
                dh=1;//如果刚按了等号又按数字，相当于做了一次AC，如果按了等号再按加号，就继续计算。
                num=0;
                sum2=1;
            }
            else if(dh==-1){//以上一轮计算结果作为被除数
                result=sum/S2.toFloat();//result为float类型
                QString data = QString("%1").arg(result);//float类型转为QString字符串类型
                QString data2 = QString("%1").arg(sum);
                ui->lineEdit->setText(data2+"÷"+S2+"="+data);
                sum=result;
                choose=0;//此时表达式中无运算符
                S="";//第一个字符串置空(第1个数所在)
                S2="";//第2个字符串置空(第2个数所在)
                dh=1;//如果刚按了等号又按数字，相当于做了一次AC，如果按了等号再按加号，就继续计算。
                sum2=1;
                num=0;
            }
        }
    }
}

void calculator::on_pushButton_jia_clicked()//加号按钮
{
    if(choose==0){//式中无运算符号
        if(dh==0){//未按下等号
        {
             ui->lineEdit->setText(S+"+");
        }
        choose=1;
        num+=1;
        }
        else if(dh==1){//按下了等号
        {
            QString data2 = QString("%1").arg(sum);
            ui->lineEdit->setText(data2+"+");
        }
        choose=1;
        num+=1;
        dh=-1;
        }
    }
    else if(choose !=0){//式中已有运算符号
        //暂不支持多项式,等待后续更新
        //暂不支持多项式,等待后续更新
        //暂不支持多项式,等待后续更新
    }
}

void calculator::on_pushButton_jian_clicked()//减号按钮
{
    if(choose==0){
        if(dh==0){
        {
             ui->lineEdit->setText(S+"-");
        }
        choose=2;
        num+=1;
        }
        else if(dh==1){
        {
            QString data2 = QString("%1").arg(sum);
            ui->lineEdit->setText(data2+"-");
        }
        choose=2;
        num+=1;
        dh=-1;
        }
    }
    else if(choose !=0){}
}

void calculator::on_pushButton_cheng_clicked()//乘号按钮
{
    if(choose==0){
        if(dh==0){
        {
             ui->lineEdit->setText(S+"×");
        }
        choose=3;
        num+=1;
        }
        else if(dh==1){
        {
            QString data2 = QString("%1").arg(sum);
            ui->lineEdit->setText(data2+"×");
        }
        choose=3;
        num+=1;
        dh=-1;
        }
    }
    else if(choose !=0){}
}

void calculator::on_pushButton_chu_clicked()//除号按钮
{
    if(choose==0){
        if(dh==0){
        {
             ui->lineEdit->setText(S+"÷");
        }
        choose=4;
        num+=1;
        }
        else if(dh==1){
        {
            QString data2 = QString("%1").arg(sum);
            ui->lineEdit->setText(data2+"÷");
        }
        choose=4;
        num+=1;
        dh=-1;
        }
    }
    else if(choose !=0){}
}

void calculator::on_pushButton_AC_clicked()//归零操作,初始化所有变量
{
    ui->lineEdit->setText("");//显示框清屏
    result=0;
    S="";
    S2="";
    choose=0;
    sum=0;
    point=0;
    num=0;
    dh=0;
}

void calculator::on_pushButton_1_clicked()//按钮1,测试时所用按钮，所有其他数字按钮都以按钮1为基础复制粘贴更改
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="1";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="1";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="1";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="1";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="1";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="1";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="1";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="1";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="1";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="1";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="1";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="1";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="1";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="1";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="1";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_2_clicked()//按钮2
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="2";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="2";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="2";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="2";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="2";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="1";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="2";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="2";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="2";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="2";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="2";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="2";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="2";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="2";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="2";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_3_clicked()//按钮3
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="3";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="3";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="3";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="3";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="3";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="3";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="3";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="3";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="3";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="3";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="1";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="3";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="3";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="3";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="3";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_4_clicked()//按钮4
{QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="4";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="4";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="4";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="4";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="4";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="4";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="4";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="4";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="4";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="4";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="1";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="4";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="4";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="4";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="4";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_5_clicked()//按钮5
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="5";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="5";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="5";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="5";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="5";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="5";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="5";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="5";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="5";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="5";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="1";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="5";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="5";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="5";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="5";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_6_clicked()//按钮6
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="6";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="6";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="6";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="6";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="6";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="6";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="6";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="6";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="6";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="6";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="6";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="6";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="6";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="6";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="6";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_7_clicked()//按钮7
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="7";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="7";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="7";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="7";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="7";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="1";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="7";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="7";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="7";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="7";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="7";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="7";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="7";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="7";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="7";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_8_clicked()//按钮8
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="8";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="8";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="8";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="8";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="8";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="8";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="8";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="8";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="8";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="8";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="1";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="8";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="8";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="8";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="8";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_9_clicked()//按钮9
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="9";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="9";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="9";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="9";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="9";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="9";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="9";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="9";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="9";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="9";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="9";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="9";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="9";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="9";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="9";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_0_clicked()//按钮0
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="0";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="0";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="0";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="0";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="0";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="0";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="0";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="0";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="0";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="0";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="0";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="0";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="0";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="0";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="0";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_00_clicked()//按钮00
{
    QString data2 = QString("%1").arg(sum);
    if(dh==0 && num==0){
        S+="00";
        ui->lineEdit->setText(S);
    }
    if(dh==0 && num!=0){
        if(choose==1){
            S2+="00";
            ui->lineEdit->setText(S+"+"+S2);
        }else if(choose==2){
            S2+="00";
            ui->lineEdit->setText(S+"-"+S2);
        }else if(choose==3){
            S2+="00";
            ui->lineEdit->setText(S+"×"+S2);
        }else if(choose==4){
            S2+="00";
            ui->lineEdit->setText(S+"÷"+S2);
        }
    }
    else if(dh==1)//进行新一轮计算
    {
        if(num==0){
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="00";
                ui->lineEdit->setText(S);
            }
        }else if(num !=0){
            if(choose==1){
                S2+="00";
                ui->lineEdit->setText(S+"+"+S2);
            }else if(choose==2){
                S2+="00";
                ui->lineEdit->setText(S+"-"+S2);
            }else if(choose==3){
                S2+="00";
                ui->lineEdit->setText(S+"×"+S2);
            }else if(choose==4){
                S2+="00";
                ui->lineEdit->setText(S+"÷"+S2);
            }
        }
    }
    else if(dh==-1){//接着上次计算结果进行新一轮计算
            QString data2 = QString("%1").arg(sum);
            if(choose==0){//还未输入运算符
                result=0;
                S="";
                S2="";
                choose=0;
                sum=0;
                point=0;
                num=0;
                dh=0;
                S+="00";
                ui->lineEdit->setText(S);
            }
            if(choose==1){
                S2+="00";
                ui->lineEdit->setText(data2+"+"+S2);
            }else if(choose==2){
                S2+="00";
                ui->lineEdit->setText(data2+"-"+S2);
            }else if(choose==3){
                S2+="00";
                ui->lineEdit->setText(data2+"×"+S2);
            }else if(choose==4){
                S2+="00";
                ui->lineEdit->setText(data2+"÷"+S2);
            }
    }
}

void calculator::on_pushButton_dian_clicked()//小数点
{
    if(dh==1){}
    else{
        if(point ==0){
            if(dh==0 && num==0){
                S+=".";
                ui->lineEdit->setText(S);
            }
            else if(dh==0 && num==1){
                if(choose==1){
                    S2+=".";
                    ui->lineEdit->setText(S+"+"+S2);
                }else if(choose==2){
                    S2+=".";
                    ui->lineEdit->setText(S+"-"+S2);
                }else if(choose==3){
                    S2+=".";
                    ui->lineEdit->setText(S+"×"+S2);
                }else if(choose==4){
                    S2+=".";
                    ui->lineEdit->setText(S+"÷"+S2);
                }
            }
        }
        if (point == 1){}
    }
}

void calculator::on_pushButton_del_clicked()//回退算式功能
{
    QString S3="";
    QString S4="";
    int lenS2=0;
    if(dh==0 || dh==1){
        if(choose ==0 && num==0){
            {
                S3 = S.mid(0,S.length()-1);
            }
            S=S3;
            ui->lineEdit->setText(S);
        }
        else if(choose !=0 && num==0){
            ui->lineEdit->setText(S);
            choose =0;
        }
        else if(num==1){
            S4=S;
            if(lenS2 != 0){
                S3 = S2.mid(0,S2.length()-1);
                S2=S3;
                lenS2=S2.length();
                if(lenS2==0){
                    num=0;
                    ui->lineEdit->setText(S4);
                }
                if(choose==1){
                    ui->lineEdit->setText(S+"+"+S2);
                }else if(choose==2){
                    ui->lineEdit->setText(S+"-"+S2);
                }else if(choose==3){
                    ui->lineEdit->setText(S+"×"+S2);
                }else if(choose==4){
                    ui->lineEdit->setText(S+"÷"+S2);
                }
            }
        }
    }
}
