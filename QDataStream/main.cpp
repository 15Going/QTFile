#include <QCoreApplication>
#include <QDataStream>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //通过数据流写二进制文件
    QFile wfile("file.dat");
    wfile.open(QIODevice::WriteOnly);
    QDataStream out(&wfile);
    out<<QString("the answer is: ");
    out<<(qint32)42;
    wfile.close();

    //通过数据流读二进制文件
    QFile rfile("file.dat");
    rfile.open(QIODevice::ReadOnly);
    QDataStream in(&rfile);
    QString str;
    qint32 answer;
    in>>str>>answer;
    rfile.close();
    qDebug()<<str<<answer;

    //通过数据流读写自定义文件格式的文件
    QFile myWirteFile("file.xxx");
    myWirteFile.open(QIODevice::WriteOnly);
    QDataStream myOut(&myWirteFile);
    //写入幻数和流版本号
    myOut<<(quint32)0xA0B0C0D0;
    myOut<<(qint32)12345;
    myOut.setVersion(QDataStream::Qt_4_0);
    //写入数据
    myOut<<QString("insert data");
    myWirteFile.close();

    QFile myReadFile("file.xxx");
    myReadFile.open(QIODevice::ReadOnly);
    QDataStream myIn(&myReadFile);
    quint32 magic;
    myIn>>magic;
    if(magic != 0xA0B0C0D0)
        return -1;
    qint32 version;
    myIn>>version;
    if(version <= 100)
        myIn.setVersion(QDataStream::Qt_3_3);
    else
        myIn.setVersion(QDataStream::Qt_4_0);
    //读取数据
    QString myData;
    myIn>>myData;
    myReadFile.close();
    qDebug()<<myData;

    return a.exec();
}
