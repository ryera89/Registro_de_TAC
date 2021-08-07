#ifndef DICOMDATASTRUCTURE_H
#define DICOMDATASTRUCTURE_H

#include <QCoreApplication>


class elementTag{
private:
    quint16 gN;
    quint16 eN;
public:
    elementTag():gN(0), eN(0){}
    elementTag(const quint16 &groupNumber, const quint16 &elementNumber): gN(groupNumber), eN(elementNumber){}

    quint16 getGroupNumber() const{return this->gN;}
    quint16 getElementNumber() const{return this->eN;}

    void setGroupNumber(const quint16 &newgroupNumber){this->gN = newgroupNumber;}
    void setElementNumber(const quint16 &newelementNumber){this->eN = newelementNumber;}
};
bool operator ==(const elementTag& eT1, const elementTag& eT2);
bool operator !=(const elementTag& eT1, const elementTag& eT2);

class dicomDataStructure
{
private:
    elementTag t;
    QByteArray vr;
    quint16 vl;
    QString vf;
public:
    dicomDataStructure(){}
    dicomDataStructure(const elementTag &dataTag, const QByteArray &valueRepresentation, const quint16 &valueLength, const QString &valueField);

    elementTag getElementTag() const{return this->t;}
    quint16 getValueLength() const{return this->vl;}
    QString getValueField() const{return this->vf;}
    QByteArray getValueRepresentation() const{return this->vr;}

    void setElementTag(const elementTag &eT){this->t = eT;}
    void setValueLength(const quint16 &valueLength){this->vl = valueLength;}
    void setValueField(const QString &valueField){this->vf = valueField;}
    void setValueRepresentation(const QByteArray &valueRepresentation){this->vr = valueRepresentation;}
    ~dicomDataStructure();
};

#endif // DICOMDATASTRUCTURE_H
