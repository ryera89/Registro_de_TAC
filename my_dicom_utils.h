#ifndef MY_DICOM_UTILS
#define MY_DICOM_UTILS

#include <QFile>
#include <QString>
#include <QStringList>
#include <QDate>
#include "include/dicomreadheader.h"
#include "include/patientrecord.h"

using namespace std;

typedef unsigned int uint;
bool isDICOM(const QString filePath); //Verifica si el archivo es tipo dicom
QString getPatientName(const QString& filePath);
QStringList getPatientNames(const QStringList &dicom_files_path); //retorna el nombre de los pacientes
QString getStudyDate(const QString& filePath);

void fixPatientName(QString &patient_name); //arregla el formato del nombre del paciente
void fixPatientNames(QStringList &patient_names); //arregla el formato del nombre del paciente en la lista de nombres

QDate StringToDate(const QString &studyDate);


//QString setNewID(QString &id);
#endif // MY_DICOM_UTILS

