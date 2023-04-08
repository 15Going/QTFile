#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&myWatcher,&QFileSystemWatcher::directoryChanged,
            this,&MainWindow::showMessage);
    connect(&myWatcher,&QFileSystemWatcher::fileChanged,
            this,&MainWindow::showMessage);

    QDir myDir(QDir::currentPath());
    myDir.setNameFilters(QStringList("*.h"));
    ui->listWidget->addItem(myDir.absolutePath() + tr("目录下的.h文件有："));
    ui->listWidget->addItems(myDir.entryList());

    //创建一个新目录并加入到监视器中
    myDir.mkdir("mydir");
    myDir.cd("mydir");
    ui->listWidget->addItem(tr("监视的目录：") + myDir.absolutePath());
    myWatcher.addPath(myDir.absolutePath());

    //创建一个新文件并加入到监视器中
    QFile file(myDir.absolutePath() + "/myfile.txt");
    if(file.open(QIODevice::WriteOnly)){
        QFileInfo info(file);
        ui->listWidget->addItem(tr("监视文件：") + info.absoluteFilePath());
        myWatcher.addPath(info.absoluteFilePath());
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMessage(const QString &path)
{
    QDir dir(QDir::currentPath() + "/mydir");
    if(path == dir.absolutePath()){
        ui->listWidget->addItem(dir.absolutePath());
        ui->listWidget->addItem(path);
        ui->listWidget->addItem(dir.dirName() + tr("目录发生改变："));
        ui->listWidget->addItems(dir.entryList());
    }else{
        //如果文件发生改变，则发出两个信号（目录改变和文件改变）
        ui->listWidget->addItem(path + tr("文件发生改变！"));
    }
}

