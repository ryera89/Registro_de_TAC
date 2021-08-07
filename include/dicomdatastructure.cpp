#include "dicomdatastructure.h"

//elementTag class helper function---------------------------------
bool operator ==(const elementTag& eT1, const elementTag& eT2){
    return eT1.getGroupNumber()==eT2.getGroupNumber() && eT1.getElementNumber()==eT2.getElementNumber();
}
bool operator !=(const elementTag& eT1, const elementTag& eT2){
    return !(eT1==eT2);
}


dicomDataStructure::dicomDataStructure(const elementTag &dataTag, const QByteArray &valueRepresentation, const quint16 &valueLength, const QString &valueField){
    this->t = dataTag;
    this->vr = valueRepresentation;
    this->vl = valueLength;
    this->vf = valueField;
}

dicomDataStructure::~dicomDataStructure()
{

}

