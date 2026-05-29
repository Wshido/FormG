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

    QPixmap img1(":/images/build/Desktop_Qt_6_10_3_MinGW_64_bit-u041eu0442u043bu0430u0434u043au0430/debug/funcqt.PNG");
    QPixmap img2(":/images/build/Desktop_Qt_6_10_3_MinGW_64_bit-u041eu0442u043bu0430u0434u043au0430/debug/uniqueqt.PNG");

    if (!img1.isNull())
        ui->imageLabel1->setPixmap(img1.scaled(350, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    else
        ui->imageLabel1->setText("Изображение функции");

    if (!img2.isNull())
        ui->imageLabel2->setPixmap(img2.scaled(450, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    else
        ui->imageLabel2->setText("Особенности функции");
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::on_nextButton_clicked()
{
    GraphWindow *gw = new GraphWindow();
    gw->setAttribute(Qt::WA_DeleteOnClose);
    connect(gw, &GraphWindow::destroyed, this, [this]() {
        this->show();
    });
    gw->show();
    this->hide();
}

void WelcomeWindow::on_backButton_clicked()
{
    emit backRequested();
    this->hide();
}