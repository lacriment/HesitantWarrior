#include "filehelper.h"

#include <QFile>
#include <QTextStream>
#include <QFileInfo>

FileHelper::FileHelper(QObject *parent) : QObject(parent)
{

}

QString FileHelper::fileToString(QString path)
{
    path.prepend("../../HesitantWarrior/");
    QFile inputFile(path);
    QString text;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       text = in.readAll();
       inputFile.close();
    }
    return text;
}

bool FileHelper::fileExists(QString path) {
    QFileInfo check_file(path);
    return check_file.exists() && check_file.isFile() ? true : false;
}
