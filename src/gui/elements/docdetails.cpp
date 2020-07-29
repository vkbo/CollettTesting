#include "docdetails.h"

GuiDocDetails::GuiDocDetails(QWidget *parent) : QFrame(parent)
{
    mainBox = new QGridLayout();
    mainBox->setVerticalSpacing(1);
    mainBox->setHorizontalSpacing(15);
    this->setLayout(mainBox);

    fntOne = new QFont();
    fntTwo = new QFont();
    fntOne->setPointSize(10);
    fntOne->setBold(true);
    fntTwo->setPointSize(10);

    QStringList colOne = (QStringList() << "Label" << "Status" << "Class" << "Layout");
    for (auto i=0; i<4; i++)
    {
        QLabel *lblOne = new QLabel(colOne[i]);
        colTwo[i] = new QLabel("");
        colTwo[i]->setWordWrap(true);
        colTwo[i]->setAlignment(Qt::AlignTop);
        lblOne->setFont(*fntOne);
        lblOne->setAlignment(Qt::AlignTop);
        mainBox->addWidget(lblOne, i, 0);
        mainBox->addWidget(colTwo[i], i, 1);
    }

    mainBox->setColumnStretch(0, 0);
    mainBox->setColumnStretch(1, 1);

    return;
}

GuiDocDetails::~GuiDocDetails()
{
}

void GuiDocDetails::buildViewBox(QString tHandle)
{


    return;
}
