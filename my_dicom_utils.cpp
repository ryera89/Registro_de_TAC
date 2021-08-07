#include "my_dicom_utils.h"

bool isDICOM(const QString filePath){
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
QString getPatientName(const QString &filePath){
    dicomDataStructure patientStructure;
    readHeader::getDataStructure(elementTag(0x0010,0x0010),filePath,patientStructure);
    return patientStructure.getValueField();
}
QStringList getPatientNames(const QStringList &dicom_files_path){
    QStringList patientNames;
    for (int i = 0;i<dicom_files_path.size();++i){
        //QFile dicomFile(dicom_files_path[i].toUtf8());
        if (isDICOM(dicom_files_path[i])){
            QString qnames = getPatientName(dicom_files_path[i]); //Convercion de stdString a QString
            patientNames.push_back(qnames);
        }
    }
    return patientNames;
}
void fixPatientName(QString &patient_name){ //arregla el formato de los nombres uno a uno
    QString name;
    QString last_name;
    bool ward = false;
    for (int i = 0;i<patient_name.size();++i){
        QChar ch = patient_name[i];
        if (ch == '^') ward = true;
        else {if (!ward) last_name.push_back(ch);
              else name.push_back(ch);
        }
    }
    patient_name = name+" "+last_name;

    patient_name = patient_name.simplified();
}

void fixPatientNames(QStringList &patient_names){ //arregla el formato de todos los nombre en la lista

    for (int i = 0; i<patient_names.size();++i){
        fixPatientName(patient_names[i]); //arregla el formato de los nombres uno a uno
    }
}
QString getStudyDate(const QString &filePath){
    dicomDataStructure studyDate;
    readHeader::getDataStructure(elementTag(0x0008,0x0020),filePath,studyDate);
    return studyDate.getValueField();
}
QDate StringToDate(const QString &studyDate){
    return QDate::fromString(studyDate,"yyyyMMdd");
}
