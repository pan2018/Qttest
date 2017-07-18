#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString str = "Polluter pays principle";
    int i = str.indexOf("pan");
    QStringList words = str.split(" ");//以空格区分
    qDebug()<<str.left(7)<<" "<<str.right(8) <<" "<<i<<words.count();
    for(int j = 0;j<words.count();j++){
        qDebug()<<words[j];
    }

    return a.exec();
}

