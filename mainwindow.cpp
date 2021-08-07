#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{

    //createByNameFile();
    createActions();
    createMenus();
    createStatusBar();

    createSearchToolBar();
    createCentralWidgetTable();

    setFixedSize(550,450);
   // setMinimumSize(530,430);
   // setMaximumSize(550,450);

    setWindowTitle(tr("Registro de TAC"));
    setWindowIcon(QIcon(":/icons/windowico.png"));
    //ui->setupUi(this)
}

void MainWindow::createActions(){
    //Actions for import menu
    fromDicomAction = new QAction(tr("Desde DICOM Files"),this);
    fromDicomAction->setIcon(QIcon(":/icons/from_dicom_files.png"));
    fromDicomAction->setToolTip(tr("Importar datos al registro dicom \n desde el estudio"));
    connect(fromDicomAction,SIGNAL(triggered()),this,SLOT(importFiles()));

    fromTextAction = new QAction(tr("Desde Conf File"),this);
    fromTextAction->setIcon(QIcon(":/icons/from_reg_file.png"));
    fromTextAction->setToolTip(tr("Importar datos al registro dicom desde \n un archivo de registro compatible"));
    connect(fromTextAction,SIGNAL(triggered()),this,SLOT(importFromRegFile()));
    copyDicomFoldersAction = new QAction(tr("Copy DICOM Files"),this);
    copyDicomFoldersAction->setIcon(QIcon(":/icons/copy_dicom_folder.png"));
    copyDicomFoldersAction->setToolTip(tr("Copiar los directorios de las imagenes dicom \n y los renombra con el nombre del paciete"));
    connect(copyDicomFoldersAction,SIGNAL(triggered()),this,SLOT(copyDicomDirs()));
    exitAction = new QAction(tr("Salir"),this);
    exitAction->setIcon(QIcon(":/icons/exit.ico"));
    exitAction->setToolTip(tr("Salir de la aplicacion"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    //Actions for search menu
    byNameAction = new QAction(tr("Nombre"),this);
    byNameAction->setToolTip(tr("Buscar por nombre"));
    byNameAction->setCheckable(true);
    byDateAction = new QAction(tr("Fecha"),this);
    byDateAction->setToolTip(tr("Buscar por fecha"));
    byDateAction->setCheckable(true);
    byIDAction = new QAction(tr("ID"),this);
    byIDAction->setToolTip(tr("Buscar por ID del disco"));
    byIDAction->setCheckable(true);

    byNameAction->setChecked(true);

    searchActionGroup = new QActionGroup(this);
    searchActionGroup->addAction(byNameAction);
    searchActionGroup->addAction(byDateAction);
    searchActionGroup->addAction(byIDAction);

    connect(byNameAction,SIGNAL(triggered()),this,SLOT(connectionActionGroupGroupBox()));
    connect(byDateAction,SIGNAL(triggered()),this,SLOT(connectionActionGroupGroupBox()));
    connect(byIDAction,SIGNAL(triggered()),this,SLOT(connectionActionGroupGroupBox()));

    //Actions for info menu
    aboutAction = new QAction(tr("Acerca"),this);
    aboutAction->setToolTip(tr("Acerca de la aplicación"));

    connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));

    aboutQtAction = new QAction(tr("Acerca de Qt"),this);
    aboutQtAction->setToolTip(tr("Acerca de Qt"));
    connect(aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));


}
void MainWindow::createMenus(){
    importMenu = menuBar()->addMenu(tr("&Importar"));
    importMenu->addAction(fromDicomAction);
    importMenu->addAction(fromTextAction);
    importMenu->addSeparator();
    importMenu->addAction(copyDicomFoldersAction);
    importMenu->addSeparator();
    importMenu->addAction(exitAction);
    importMenu->setToolTipsVisible(true);



    searchMenu = menuBar()->addMenu(tr("&Buscar"));
    searchMenu->addAction(byNameAction);
    searchMenu->addSeparator();
    searchMenu->addAction(byDateAction);
    searchMenu->addSeparator();
    searchMenu->addAction(byIDAction);
    searchMenu->setToolTipsVisible(true);




    infoMenu = menuBar()->addMenu(tr("In&fo"));
    infoMenu->addAction(aboutAction);
    infoMenu->addSeparator();
    infoMenu->addAction(aboutQtAction);
    infoMenu->setToolTipsVisible(true);
}
void MainWindow::createStatusBar(){
    statusLabel = new QLabel("release v1.0");
    //statusLabel->setMaximumSize(statusLabel->sizeHint());
    statusLabel->setMinimumSize(this->sizeHint());
    // progressBar = new QProgressBar;
    statusBar()->addPermanentWidget(statusLabel);

    //statusLabel->setMinimumWidth(statusBar()->sizeHint().width());
    //statusBar()->addWidget(progressBar);
}
void MainWindow::createSearchToolBar(){
    importToolBar = addToolBar(tr("&Importar"));
    importToolBar->addAction(fromDicomAction);
    importToolBar->addAction(fromTextAction);


    copyToolBar = addToolBar(tr("&Copia"));
    copyToolBar->addAction(copyDicomFoldersAction);


    searchToolBar = addToolBar(tr("&Buscar"));
    searchLabel = new QLabel(tr("Buscar"));

    searchToolBar->addWidget(searchLabel);
    searchToolBar->addSeparator();
    searchEdit = new QLineEdit;
    searchToolBar->addWidget(searchEdit);
    connect(searchEdit,SIGNAL(textChanged(QString)),this,SLOT(getPatientfromRecord(QString)));

    searchToolBar->addSeparator();

    searchComboBox = new QComboBox(this);
    searchToolBar->addWidget(searchComboBox);
    searchComboBox->addItem("Nombre");
    searchComboBox->addItem("Fecha");
    searchComboBox->addItem("ID");

    connect(searchComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(connectionGroupBoxActionGroup(int)));

    searchToolBar->addSeparator();
}
void MainWindow::createCentralWidgetTable(){
    resultsTable = new QTableWidget(1,3,this);
    QTableWidgetItem* itemName = new QTableWidgetItem;
    itemName->setText("Nombre");
    QTableWidgetItem* itemID = new QTableWidgetItem;
    itemID->setText("ID");
    QTableWidgetItem* itemDate = new QTableWidgetItem;
    itemDate->setText("Fecha");
    resultsTable->setHorizontalHeaderItem(0,itemName);
    resultsTable->setHorizontalHeaderItem(1,itemID);
    resultsTable->setHorizontalHeaderItem(2,itemDate);

    resultsTable->setColumnWidth(0,200);

    addButton = new QPushButton(tr("Agregar"),this);
    addButton->setToolTip(tr("Agrega los estudios al registro."));
    addButton->setDisabled(true);
    connect(addButton,SIGNAL(released()),this,SLOT(addToRegister()));

    clearButton = new QPushButton(tr("Clear"),this);
    clearButton->setToolTip(tr("Limpia la tabla de resultados"));
    connect(clearButton,SIGNAL(released()),this,SLOT(clearResultTable()));

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addButton);

    buttonLayout->addWidget(clearButton,0,Qt::AlignTop);
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(resultsTable);

    mainLayout->addLayout(buttonLayout);

   QWidget* widget = new QWidget;
   widget->setLayout(mainLayout);


    setCentralWidget(widget);

}
void MainWindow::clearResultTable(){
    resultsTable->clearContents();
    for (int i = resultsTable->rowCount(); i>=0;--i){
        resultsTable->removeRow(i);
    }
    addButton->setDisabled(true);
}

void MainWindow::updateResultTable(const QString &patientName, const QString &diskId, const QString &studyDate){
    QTableWidgetItem *itemName = new QTableWidgetItem;
    QTableWidgetItem *itemDate = new QTableWidgetItem;
    QTableWidgetItem *itemID = new QTableWidgetItem;
    itemName->setText(patientName.toUpper());
    itemID->setText(diskId);
    itemDate->setText(studyDate);
    resultsTable->insertRow(resultsTable->rowCount());
    resultsTable->setItem(resultsTable->rowCount()-1,0,itemName);
    resultsTable->setItem(resultsTable->rowCount()-1,1,itemID);
    resultsTable->setItem(resultsTable->rowCount()-1,2,itemDate);

}

//slots definitions-----------------------------------------------------------------
void MainWindow::about(){
    QMessageBox::about(this,tr("Acerca de Registro de TAC"),
                       tr("<h2>Registro de TAC v1.0</h2>"
                          "<p>Copyright &copy; 2016 Radioterapia-CIMEQ."
                          "<p>Registro de TAC es una pequeña aplicación"
                          " para llevar un registro de los pacientes que "
                          "se realizan TAC de planificación."));
}
bool MainWindow::importFiles(){

    QString main_dir_path = QFileDialog::getExistingDirectory(this);



    if (!main_dir_path.isEmpty()){
       clearResultTable();

       /*QFile idReg("idreg.txt");
       idReg.open(QIODevice::ReadOnly | QIODevice::Text);
       QTextStream in(&idReg);
       QString lastID = in.read(3);
       idReg.close();*/

        QStringList filesPath = getFilesPath(main_dir_path);

        for (int i = 0; i<filesPath.size(); ++i){
            QString patientName = getPatientName(filesPath[i]);
            fixPatientName(patientName);
            QString studyDate = getStudyDate(filesPath[i]);
            QDate date = StringToDate(studyDate);
            studyDate = date.toString("dd/MM/yyyy");
            QString d;
            for (int i=1;i<=4;++i){
               d.push_front(studyDate[studyDate.size()-i]);
            }
            updateResultTable(patientName,d+"-",studyDate);
        }
        CentrarItems();
        addButton->setDisabled(false);
        return true;
    }
    return false;
}
bool MainWindow::importFromRegFile(){
    QString filePath = QFileDialog::getOpenFileName(this,tr("Registro de TAC"));

    if (!filePath.isEmpty()){
        QFile regFile(filePath);
        regFile.open(QIODevice::ReadOnly| QIODevice::Text);

        QTextStream in(&regFile);

        PatientRecord patient;

        clearResultTable();
        while (!in.atEnd()){
            in >> patient;
            /*QString name;
            QString id;
            QString fecha;
            in >> id >> fecha;
            in.skipWhiteSpace();
            QChar ch;
            do{
                in >> ch;
                name.push_back(ch);
            }while(ch!='\n');
            QString d;
            patient.setPatientName(name.simplified());
            patient.setDiskID(id.simplified());
            patient.setStudyDate(fecha.simplified());

            for (int i=1;i<=4;++i){
               d.push_front(patient.getStudyDate()[patient.getStudyDate().size()-i]);
            }*/

            updateResultTable(patient.getPatientName(),patient.getDiskID(),patient.getStudyDate());
        }
        CentrarItems();
        addButton->setDisabled(false);
        regFile.close();
        return true;
    }
    return false;
}

bool MainWindow::copyDicomDirs(){
    QString main_dir_path = QFileDialog::getExistingDirectory(this,tr("Escoge el Directorio DICOM"));
    if (main_dir_path.isEmpty()) return false;
    QString root_copy_dir = QFileDialog::getExistingDirectory(this,tr("Escoge el Directorio de Copia"));
    if (root_copy_dir.isEmpty()) return false;

    return copyDICOMFiles(main_dir_path,root_copy_dir);

}

void MainWindow::connectionGroupBoxActionGroup(int i){
    switch (i) {
    case 0:
        this->byNameAction->setChecked(true);
        break;
    case 1:
        this->byDateAction->setChecked(true);
        break;
    case 2:
        this->byIDAction->setChecked(true);
    default:
        break;
    }
}
void MainWindow::connectionActionGroupGroupBox(){
    if (byNameAction->isChecked()) searchComboBox->setCurrentIndex(0);
    if (byDateAction->isChecked()) searchComboBox->setCurrentIndex(1);
    if (byIDAction->isChecked()) searchComboBox->setCurrentIndex(2);
}
bool MainWindow::copyDICOMFiles(const QString &main_dir, const QString &copy_dir){
    //QStringList dicom_files_path = getFilesPathforCopy(main_dir);
    QFileInfoList dicom_files_info = getFilesInfoforCopy(getFilesPathforCopy(main_dir));
    QString patient_name;
    bool isOtherPatient = true;

    int filesNumber=dicom_files_info.size();

    QProgressDialog progress(tr("Copying files..."),tr("Cancel"),0,filesNumber,this);
    progress.setWindowModality(Qt::WindowModal);
    for (int i = 0; i<filesNumber;++i){
        progress.setValue(i);
        if (!isDICOM(dicom_files_info[i].canonicalFilePath())){
            dicom_files_info.removeAt(i); //remueve el archivo que no es dicom
            --i;                          //reduce en indice
            --filesNumber;                //reduce el numero de archivos a copiar
            if (filesNumber==0) {
                QMessageBox::information(this,tr("Registro de TAC"),tr("No existen archivos DICOM en el \n directorio especificado."));
                return false;
            }
            progress.setMaximum(filesNumber);
            continue;
        }

        if (isOtherPatient){
            isOtherPatient = false;
            patient_name = getPatientName(dicom_files_info[i].canonicalFilePath()); //extrayendo el nombre del primer paciente para nombrar el directorio
            fixPatientName(patient_name);                                     //arreglando el nombre del paciente
            if (!createDir(copy_dir,patient_name)){                           //Creando el directorio
                QMessageBox::information(0,tr("Registro de TAC"),tr("Error creando directorios."));
                return false;
            }
        }
        if (i!=filesNumber-1){                                                                          //Para no irnos de rango
            if (dicom_files_info[i].canonicalPath() != dicom_files_info[i+1].canonicalPath()){          //Si tienen un mismo path pertenecen a un mismo paciente
                isOtherPatient = true;                                                                  //Existe un nuevo paciente en la proxima iteraccion
            }
        }
        if (!(QFile::copy(dicom_files_info[i].canonicalFilePath(),copy_dir+"\\"+patient_name+"\\"+dicom_files_info[i].fileName()))){
            QMessageBox::information(0,tr("Registro de TAC"),tr("Error Copiando Archivo ")+dicom_files_info[i].fileName()+".");
        }
    }
    progress.setValue(filesNumber);
    return true;

}
/*void MainWindow::editTableItems(QTableWidgetItem *item){

    item->setText(item->text());
}*/
void MainWindow::CentrarItems(){
    for (int i=0;i<=resultsTable->rowCount()-1;++i){
        for (int j=0;j<=resultsTable->columnCount()-1;++j){
            resultsTable->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void MainWindow::addToRegister(){
    QFile byNameFile("byName.txt");
    byNameFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream out(&byNameFile);
    for (int i=0;i<=resultsTable->rowCount()-1;++i){
        PatientRecord patient;
        patient.setPatientName(resultsTable->item(i,0)->text());
        patient.setDiskID(resultsTable->item(i,1)->text());
        patient.setStudyDate(resultsTable->item(i,2)->text());

        out << patient;
    }
    byNameFile.close();


   QMessageBox::information(this,tr("Registro de TAC"),tr("Registro completado"));
}

void MainWindow::getPatientfromRecord(const QString &str){
     if (byNameAction->isChecked()) busquedaPorNombre(str);
     if (byIDAction->isChecked()) busquedaPorID(str);
     if (byDateAction->isChecked()) busquedaPorFecha(str);



}
void MainWindow::busquedaPorNombre(const QString &name){

    QFile byNameFile("byName.txt");
    if (byNameFile.exists()){
       byNameFile.open(QIODevice::ReadOnly| QIODevice::Text);
       QTextStream in(&byNameFile);

      PatientRecord patient;
  // QList<PatientRecord> patientsRecord;
      clearResultTable();
      QRegExp rex("\\b"+name,Qt::CaseInsensitive);
      if (name.isEmpty()){
          clearResultTable();
      }else{
         while (!in.atEnd()){
         in >> patient;
           if (patient.getPatientName().contains(rex)){
             updateResultTable(patient.getPatientName(),patient.getDiskID(),patient.getStudyDate());
             CentrarItems();
           }

        }
    } byNameFile.close();
  }else {
        QMessageBox::information(this,tr("Registro de TAC"),tr("El Archivo byName.txt no existe."));
    }
}
void MainWindow::busquedaPorID(const QString &id){
    QFile byNameFile("byName.txt");
    if (byNameFile.exists()){
       byNameFile.open(QIODevice::ReadOnly | QIODevice::Text);
       QTextStream in(&byNameFile);

      PatientRecord patient;
  // QList<PatientRecord> patientsRecord;
      clearResultTable();
      QRegExp rex("\\b"+id,Qt::CaseInsensitive);
      if (id.isEmpty()){
          clearResultTable();
      }else{
         while (!in.atEnd()){
         in >> patient;
           if (patient.getDiskID().contains(rex)){
             updateResultTable(patient.getPatientName(),patient.getDiskID(),patient.getStudyDate());
             CentrarItems();
           }

        }
    } byNameFile.close();
  }else {
        QMessageBox::information(this,tr("Registro de TAC"),tr("El Archivo byName.txt no existe."));
    }
}

void MainWindow::busquedaPorFecha(const QString &fecha){
    QFile byNameFile("byName.txt");
    if (byNameFile.exists()){
       byNameFile.open(QIODevice::ReadOnly | QIODevice::Text);
       QTextStream in(&byNameFile);

      PatientRecord patient;
  // QList<PatientRecord> patientsRecord;
      clearResultTable();
      QRegExp rex("\\b"+fecha,Qt::CaseInsensitive);
      if (fecha.isEmpty()){
          clearResultTable();
      }else{
         while (!in.atEnd()){
         in >> patient;
           if (patient.getStudyDate().contains(rex)){
             updateResultTable(patient.getPatientName(),patient.getDiskID(),patient.getStudyDate());
             CentrarItems();
           }

        }
    } byNameFile.close();
  }else {
        QMessageBox::information(this,tr("Registro de TAC"),tr("El Archivo byName.txt no existe."));
    }
}

MainWindow::~MainWindow()
{
    delete this;
}
QFileInfoList getInfoSubDirs(const QString &main_path){
    QDir main_dir(main_path);
    main_dir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    return main_dir.entryInfoList();
}
QStringList getSubDirsPath(const QFileInfoList &info_dirs){ //esta fuuncion busca recursivamente hasta encontrar la ruta hacia los archivos y la retorna
    QStringList file_path;
    if (info_dirs.isEmpty()){
        return file_path;
    }
    for (int i=0;i<info_dirs.size();++i){
        if (info_dirs[i].isDir() && !(info_dirs[i].isHidden())){
            file_path.append(getSubDirsPath(getInfoSubDirs(info_dirs[i].canonicalFilePath())));
        }
        if (info_dirs[i].isFile() && !(info_dirs[i].isHidden()) && isDICOM(info_dirs[i].canonicalFilePath())){ //Agragar isDicom
            file_path.push_back(info_dirs[i].canonicalFilePath());
            break;
        }
    }
    return file_path;
}
QStringList getFilesPath(const QString &root_dir_path){
    QFileInfoList sub_dirspath = getInfoSubDirs(root_dir_path);
    return getSubDirsPath(sub_dirspath);
}

QStringList getSubDirsPathforCopy(const QFileInfoList &info_dirs){
    QStringList file_path;
    if (info_dirs.isEmpty()){
        return file_path;
    }
    for (int i=0;i<info_dirs.size();++i){
        if (info_dirs[i].isDir() && !(info_dirs[i].isHidden())){
            file_path.append(getSubDirsPathforCopy(getInfoSubDirs(info_dirs[i].canonicalFilePath())));
        }
        if (info_dirs[i].isFile() && !(info_dirs[i].isHidden())){ //Agragar isDicom
            file_path.push_back(info_dirs[i].canonicalFilePath());
            //break;
        }
    }
    return file_path;
 }
QStringList getFilesPathforCopy(const QString &root_dir_path){
    QFileInfoList sub_dirspath = getInfoSubDirs(root_dir_path);
    return getSubDirsPathforCopy(sub_dirspath);
}
QFileInfoList getFilesInfoforCopy(const QStringList &file_paths){
    QFileInfoList files_info;
    for (int i = 0; i<file_paths.size();++i){
        files_info.push_back(QFileInfo(file_paths[i]));
    }
    return files_info;
}
bool createDir(const QString &root_dir,QString &dir_name, QVariant cont){
    QDir dir(root_dir);
    QStringList dirs_names = dir.entryList();
    for (int i = 0;i < dirs_names.size(); ++i){
        if (dir_name == dirs_names[i]){
            cont = cont.toInt() + 1;
            dir_name = dir_name + "(" + cont.toString() + ")";
            return createDir(root_dir,dir_name,cont);
        }
    }
    return dir.mkdir(dir_name);
}

