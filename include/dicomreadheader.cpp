#include "dicomreadheader.h"

bool readHeader::isDICOM(const QString &filePath){
    QFile dicomFile(filePath);
    if (!dicomFile.open(QIODevice::ReadOnly)) return false;


    QByteArray dicomID(4,0);

    if (!dicomFile.seek(128)){
        dicomFile.close();
        return false;
    }

    QDataStream in(&dicomFile);

    quint8 ch;
    for (int i = 0; i<4; ++i){
       in >> ch;
       dicomID[i]=ch;
    }
    dicomFile.close();

    if (dicomID == "DICM") return true;


    return false;
}

/*elementTag readHeader::searchDataElement(const elementTag &tag, const QString &fileName){
    if (!isDICOM(fileName)) return elementTag(0,0);

    quint16 groupNumber = 0x0000;
    quint16 elementNumber = 0x0000;

    quint16 auxGroupNumber = 0;
    quint16 auxElementNumber = 0;

    QFile dicomFile(fileName);
    dicomFile.open(QIODevice::ReadOnly);
    //dicomFile.open(QIODevice::ReadOnly);
    QDataStream in(&dicomFile);
    while (groupNumber!=tag.getGroupNumber() || elementNumber!=tag.getElementNumber()){
        in >> auxGroupNumber;
        groupNumber = qFromBigEndian(auxGroupNumber);
        if (groupNumber == tag.getGroupNumber()) in >> auxElementNumber;
        elementNumber = qFromBigEndian(auxElementNumber);
    }
    elementTag tagFinded(groupNumber,elementNumber);
    return tagFinded;
}*/

bool readHeader::getDataStructure(const elementTag &tag, const QString &fileName, dicomDataStructure &dataStructure){
    if (!isDICOM(fileName)) return false;

    quint16 groupNumber = 0x0000;
    quint16 elementNumber = 0x0000;

    quint16 auxGroupNumber = 0;
    quint16 auxElementNumber = 0;

    QFile dicomFile(fileName);
    dicomFile.open(QIODevice::ReadOnly);
    dicomFile.seek(128);
    //dicomFile.open(QIODevice::ReadOnly);
    QDataStream in(&dicomFile);
    while (groupNumber!=tag.getGroupNumber() || elementNumber!=tag.getElementNumber()){
        in >> auxGroupNumber;
        groupNumber = qFromBigEndian(auxGroupNumber);
        if (groupNumber == tag.getGroupNumber()) in >> auxElementNumber;
        elementNumber = qFromBigEndian(auxElementNumber);
    }

    elementTag tagFinded(groupNumber,elementNumber);

   //elementTag tagFinded = searchDataElement(tag,fileName);
   if (tagFinded == elementTag(0,0)) return false;

   dataStructure.setElementTag(tagFinded); //asignando el tag

   QByteArray valueRepresentation(2,0);

   //QFile dicomFile(fileName);
   //dicomFile.open(QIODevice::ReadOnly);
   //QDataStream in(&dicomFile);
   quint8 ch;

   in >> ch;  valueRepresentation[0]=ch;
   in >> ch;  valueRepresentation[1]=ch;

   dataStructure.setValueRepresentation(valueRepresentation); //asignando vr

   quint16 auxValueLength = 0;

   quint16 valueLength = 0;

   in >> auxValueLength;

   valueLength = qFromBigEndian(auxValueLength);

   dataStructure.setValueLength(valueLength);  //asignando vl

   QString valueField;

   //quint8 ch;
   for (int i = 0; i < valueLength; ++i){
       in >> ch;
       valueField.push_back(ch);
   }

   dataStructure.setValueField(valueField);  //asignando vf
   dicomFile.close();   //cerrando archivo

   return true;

}
