#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "logintimp.h"
#include "welcomewindow.h"
#include "servicemanager.h"

AboutWindow::AboutWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    setFixedSize(900, 600);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_nextButton_clicked()
{
    LoginTimp login(this);
    int result = login.exec();

    if (result == QDialog::Accepted) {
        WelcomeWindow *ww = new WelcomeWindow();
        connect(ww, &WelcomeWindow::backRequested, this, [this, ww]() {
            ww->deleteLater();
            this->show();
        });
        connect(ww, &WelcomeWindow::logoutRequested, this, [this, ww]() {
            ww->deleteLater();
            ServiceManager::instance().sendLogout(ServiceManager::instance().currentLogin());
            this->show();
        });
        ww->setAttribute(Qt::WA_DeleteOnClose);
        ww->show();
        this->hide();
    }
}
