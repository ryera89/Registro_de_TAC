#ifndef DICOMREADHEADER_H
#define DICOMREADHEADER_H

#include "dicomdatastructure.h"
#include <QFile>
#include <QDataStream>
#include <QtEndian>


class readHeader{
private:
    static bool isDICOM(const QString &filePath);
    static elementTag searchDataElement(const elementTag &tag, const QString &fileName);

public:
  static bool getDataStructure(const elementTag &tag, const QString &fileName,dicomDataStructure &dataStructure);

};

#endif // DICOMREADHEADER_H
