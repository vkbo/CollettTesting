#ifndef GUIDOCTREE_H
#define GUIDOCTREE_H

#include <QTreeWidget>

class GuiDocTree : public QTreeWidget
{
    Q_OBJECT

public:
    GuiDocTree(QWidget *parent=nullptr);
    ~GuiDocTree();

private:

};
#endif // GUIDOCTREE_H
