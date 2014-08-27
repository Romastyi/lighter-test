#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>
#include "settingsdialog.h"
#include "lightdialog.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int & argc, char ** argv);
    virtual ~Application();

private slots:
    void settingsFinished(int result);

private:
    SettingsDialog *sDialog;
    LightDialog *lDialog;
};

#endif // APPLICATION_H
