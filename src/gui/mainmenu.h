#ifndef GUIMAINMENU_H
#define GUIMAINMENU_H

#include <QAction>
#include <QMenuBar>

class GuiMainMenu : public QMenuBar
{
    Q_OBJECT

public:
    GuiMainMenu(QWidget *parent=nullptr);
    ~GuiMainMenu();

private:
    void buildProjectMenu();
    void buildDocumentMenu();
    void buildEditMenu();
    void buildViewMenu();
    void buildFormatMenu();
    void buildToolsMenu();
    void buildHelpMenu();

    // Menus
    QMenu *projMenu;
    QMenu *fmtMenu;

    // Format Menu
    QAction *aFmtEmph;
    QAction *aFmtStrong;
    QAction *aFmtStike;

};
#endif // GUIMAINMENU_H
