#include "searchfunctions.h"
bool createByNameFile(){
    QFile positionFile("byName.txt");
    if (positionFile.exists()) return true;
    if (!positionFile.open(QIODevice::WriteOnly)) return false;
    QTextStream stream(&positionFile);
    for (quint8 i = 'A';i <= 'Z';++i){
        QString str;
        str.push_back(char(i));
        str.push_back("#");
        stream << str << "\n" <<"\n" << "\n" << "\n";
    }
    return true;
}
quint64 getBytePosition(const QByteArray flag,QFile *file){


    QByteArray str;
    while (!file->atEnd()){
        str = file->readLine(3);
        if (str == flag) break;
    }


    return file->pos()+2;
}
void createBytePosTableFile(){
    QFile bytePosFile("bytePosTable.txt");

    if (bytePosFile.exists()) return;

     bytePosFile.open(QIODevice::WriteOnly);
}
void updateBytePosTable(const QString &filePath){
    QFile regFile(filePath);
    regFile.open(QIODevice::ReadOnly);
    //QTextStream in(regFile);

    QList<QByteArray> flagList;

    for (quint8 i = 'A';i<= 'Z';++i){
        QByteArray flag(2,0);
        flag[0] = char(i);
        flag[1] = '#';
        flagList.push_back(flag);
    }

    QFile bytePosTable("bytePosTable.txt");
    bytePosTable.open(QIODevice::WriteOnly);
    QTextStream out(&bytePosTable);
    for (int i = 0;i<flagList.size();++i){
        out << (quint64)getBytePosition(flagList[i],&regFile) << "\n";
    }
   regFile.close();
   bytePosTable.close();
}
