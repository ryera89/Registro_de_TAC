#ifndef SEARCHFUNCTIONS_H
#define SEARCHFUNCTIONS_H

#include <QTextStream>
#include <QFile>

void createBytePosTableFile();
bool createByNameFile();
quint64 getBytePosition(const QByteArray flag,QFile *file);
void updateBytePosTable(const QString &filePath);

#endif // SEARCHFUNCTIONS_H
