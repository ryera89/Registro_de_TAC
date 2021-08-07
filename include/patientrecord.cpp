#include "patientrecord.h"



bool operator ==(const PatientRecord &P1, const PatientRecord &P2){
    return P1.getPatientName() == P2.getPatientName() && P1.getDiskID() == P2.getDiskID() && P1.getStudyDate() == P2.getStudyDate();
}
bool operator !=(const PatientRecord &P1, const PatientRecord &P2){
    return !(P1==P2);
}

QTextStream& operator << (QTextStream &out,const PatientRecord &write_patient){
    quint32 name_size = write_patient.getPatientName().size();
    quint32 id_size = write_patient.getDiskID().size();
    quint32 date_size = write_patient.getStudyDate().size();
    return out << (quint32)name_size << " " <<write_patient.getPatientName() << "\t" << (quint32)id_size << " " << write_patient.getDiskID() << "\t" << (quint32)date_size << " " <<write_patient.getStudyDate() << "\n";
}

QTextStream& operator >> (QTextStream &in,PatientRecord &read_patient){
    quint32 name_size = 0;
    quint32 id_size = 0;
    quint32 date_size = 0;
    QChar endLine;
    in >> name_size;
    in.skipWhiteSpace();
    read_patient.setPatientName(in.read(name_size));
    in.skipWhiteSpace();
    in >> id_size;
    in.skipWhiteSpace();
    read_patient.setDiskID(in.read(id_size));
    in.skipWhiteSpace();
    in  >> date_size;
    in.skipWhiteSpace();
    read_patient.setStudyDate(in.read(date_size));
    return in >> endLine;
}
