#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include "graphwindow.h"
#include <QPixmap>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::WelcomeWindow)
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
    GraphWindow *gw = new GraphWindow();

    gw->show();
    this->hide();
}
void WelcomeWindow::on_backButton_clicked()
{
    emit backRequested();
    this->hide();
}