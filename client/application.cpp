#include "application.h"

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv),
    sDialog(new SettingsDialog), lDialog(new LightDialog)
{
  connect(sDialog, SIGNAL(finished(int)), this, SLOT(settingsFinished(int)));
  connect(lDialog, SIGNAL(reconnect()), sDialog, SLOT(show()));
  sDialog->show();
}

Application::~Application()
{
    delete sDialog;
    delete lDialog;
}

void Application::settingsFinished(int result)
{
    if (result == QDialog::Accepted) {
        lDialog->show();
        lDialog->connectToServer(sDialog->host(), sDialog->port());
    } else {
        exit(1);
    }
}
