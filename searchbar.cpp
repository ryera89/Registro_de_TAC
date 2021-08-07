#include "searchbar.h"
#include "ui_searchbar.h"

searchBar::searchBar(QWidget *parent) :
    QWidget(parent)

{
    searchLabel = new QLabel(tr("Search"),this);
    searchEdit = new QLineEdit(this);

    infoLabel = new QLabel(this);

    searchLayout = new QHBoxLayout;

    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(infoLabel);
    this->setLayout(searchLayout);
}

searchBar::~searchBar()
{
    delete this;
}
