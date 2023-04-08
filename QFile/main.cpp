#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //如果文件不存在，则创建文件，以只写方式打开
    QFile file("myfile.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug()<<file.errorString();
    file.write("hello qt! \nxiaoji");
    file.close();

    //获取文件信息
    QFileInfo info(file);
    qDebug() << QObject::tr("绝对路径：") << info.absoluteFilePath() << "\n"
             << QObject::tr("文件名：") << info.fileName() << "\n"
             << QObject::tr("基本名称：") << info.baseName() << "\n"
             << QObject::tr("后缀：") << info.suffix() << "\n"
             << QObject::tr("创建时间：") << info.birthTime() << "\n"
             << QObject::tr("大小：") << info.size();
    // 以只读方式打开
    if (!file.open(QIODevice::ReadOnly  | QIODevice::Text))
        qDebug() << file.errorString();
    qDebug() << QObject::tr("文件内容：") << "\n" << file.readAll();
    qDebug() << QObject::tr("当前位置：") << file.pos();

    file.seek(0);
    QByteArray array;
    array = file.read(5);
    qDebug()<<QObject::tr("前面五个字符：")<<array
           <<QObject::tr("当前位置：")<<file.pos();
    file.seek(10);
    array = file.read(5);
    qDebug()<<QObject::tr("第11-15个字符：")<<array;
    file.close();

    return a.exec();
}
