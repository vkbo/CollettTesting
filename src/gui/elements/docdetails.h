#ifndef GUIDOCDETAILS_H
#define GUIDOCDETAILS_H

#include <QFont>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>

class GuiDocDetails : public QFrame
{
public:
    GuiDocDetails(QWidget *parent=nullptr);
    ~GuiDocDetails();

    void buildViewBox(QString tHandle);

private:

    QGridLayout *mainBox;
    QFont       *fntOne;
    QFont       *fntTwo;
    QLabel      *colTwo[4];

};
#endif // GUIDOCDETAILS_H
