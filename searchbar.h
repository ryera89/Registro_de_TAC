#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>


namespace Ui {
class searchBar;
}

class searchBar : public QWidget
{
    Q_OBJECT

public:
    explicit searchBar(QWidget *parent = 0);
    ~searchBar();

private:
    QLabel* searchLabel;
    QLabel* infoLabel;

    QLineEdit* searchEdit;

    QHBoxLayout* searchLayout;

};

#endif // SEARCHBAR_H
