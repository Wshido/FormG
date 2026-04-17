#include "maintimp.h"
#include "ui_maintimp.h"

MainTimp::MainTimp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainTimp)
{
    ui->setupUi(this);
}

MainTimp::~MainTimp()
{
    delete ui;
}
