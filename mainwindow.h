#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QProgressBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>
#include <QDir>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QComboBox>
#include <QTableWidget>
#include <QProgressDialog>
#include "my_dicom_utils.h"
#include <QTextStream>
#include <QRegExp>
#include "searchfunctions.h"

//#include <QFileSystemModel>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void about();
    bool importFiles();
    bool importFromRegFile();
    void connectionGroupBoxActionGroup(int);
    void connectionActionGroupGroupBox();
    bool copyDicomDirs();
    void clearResultTable();

    void addToRegister();

    void getPatientfromRecord(const QString &name);

    void CentrarItems();

    //void editTableItems(QTableWidgetItem* item);

private:
    //memebers-----------------------
    QMenu* importMenu;
    QAction* fromDicomAction;
    QAction* fromTextAction;
    QAction* copyDicomFoldersAction;
    QAction* exitAction;

    QMenu* searchMenu;
    QAction* byNameAction;
    QAction* byDateAction;
    QAction* byIDAction;
    QComboBox* searchComboBox;

    QActionGroup* searchActionGroup;

    QMenu* infoMenu;
    QAction* aboutAction;
    QAction* aboutQtAction;


    QLabel* statusLabel;
    //QProgressBar* progressBar;

    //QLineEdit* debuggingLineEdit; //label para debug

    QToolBar* importToolBar;
    //QToolButton* fromDicomToolButton;
    //QToolButton* fromTextFileToolButton;
    QToolBar* copyToolBar;
    //QToolButton* copyDicomFoldersToolButton;

    QToolBar* searchToolBar;
    QLabel* searchLabel;
    QLineEdit* searchEdit;
    //QLabel* infoLabel;

    //QFileDialog* fileDialog;

    QTableWidget* resultsTable;
    QPushButton* addButton;
    QPushButton* clearButton;
    //QAbstractItemModel *model;

    //Private Functions--------------

    void createMenus();
    void createActions();
    void createStatusBar();
    void createSearchToolBar();
    void createCentralWidgetTable();

    void busquedaPorNombre(const QString &name);
    void busquedaPorID(const QString &id);
    void busquedaPorFecha(const QString &fecha);


    void updateResultTable(const QString &patientName,const QString &diskId,const QString &studyDate);

    bool copyDICOMFiles(const QString &main_dir,const QString &copy_dir);


   // QString getMainDicomDirPath();

    //QString getDirectoryPath();
    //QStringList getDirectoriesPaths(const QString dirName);
    //QStringList getDICOMFilesPath(const QStringList dirs_path);
    //QStringList getPatientNames(const QStringList files_path);

    //Ui::MainWindow *ui;

};
QFileInfoList getInfoSubDirs(const QString &main_path); //devuelve la info de los sub directorios coontenidos en una carpeta raiz

QStringList getSubDirsPath(const QFileInfoList &info_dirs); //devuelve las rutas hacia los archivos

QStringList getFilesPath(const QString &root_dir_path); //devuelve las rutas hacia los archivos dentro de un directorio especificado
                                                        //el directorio puede contener otros directorios esta funcion es la que une las otras funciones



QStringList getSubDirsPathforCopy(const QFileInfoList &info_dirs);
QStringList getFilesPathforCopy(const QString &root_dir_path);
QFileInfoList getFilesInfoforCopy(const QStringList &file_paths);

bool createDir(const QString &root_dir,QString &dir_name, QVariant cont=0);
bool copyDICOMFiles(const QString &main_dir,const QString &copy_dir);

#endif // MAINWINDOW_H
