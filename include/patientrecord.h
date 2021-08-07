#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H


#include <QString>
#include <QTextStream>

class PatientRecord{
private:
    QString patientName;
    QString diskID;
    QString studyDate;

public:
    PatientRecord(){}
    PatientRecord(const QString &name,const QString &id,const QString date):patientName(name), diskID(id), studyDate(date){}

    void setPatientName(const QString &name){this->patientName = name;}
    void setDiskID(const QString &id){this->diskID = id;}
    void setStudyDate(const QString &date){this->studyDate = date;}

    QString getPatientName() const {return this->patientName;}
    QString getDiskID() const {return this->diskID;}
    QString getStudyDate() const{return this->studyDate;}
};
bool operator ==(const PatientRecord &P1, const PatientRecord &P2);
bool operator !=(const PatientRecord &P1, const PatientRecord &P2);

QTextStream& operator << (QTextStream &out, const PatientRecord &write_patient);
QTextStream& operator >> (QTextStream &in,PatientRecord &read_patient);

#endif // PATIENTRECORD_H
