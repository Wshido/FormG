#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include "logintimp.h"
#include <QPixmap>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::WelcomeWindow),
    loginWindow(nullptr)
{
    ui->setupUi(this);
    setFixedSize(900, 600);

    QPixmap img1("funcqt.png");
    QPixmap img2("uniqueqt.png");

    ui->imageLabel1->setPixmap(img1.scaled(350,200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->imageLabel2->setPixmap(img2.scaled(450,200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::on_nextButton_clicked()
{
    if (!loginWindow) {
        loginWindow = new LoginTimp();

        connect(loginWindow, &LoginTimp::backRequested, this, [this]() {
            this->show();
            loginWindow->hide();
        });
    }

    loginWindow->show();
    this->hide();
}
void WelcomeWindow::on_backButton_clicked()
{
    this->show();
}