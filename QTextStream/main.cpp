#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //通过文本流写数据
    QFile wfile("data.txt");
    if(wfile.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream out(&wfile);
        //写入数据并设置字符宽度
        out<<"Result: "<<qSetFieldWidth(10)<<3.14<<2.7;
    }
    wfile.close();

    //通过文本流读数据
    QFile rfile("data.txt");
    if(!rfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    QTextStream in(&rfile);
    while(!in.atEnd()){
        QString line = in.readLine();
        qDebug()<<line;
    }
    rfile.close();

    return a.exec();
}
