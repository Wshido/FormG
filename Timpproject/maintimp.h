#ifndef MAINTIMP_H
#define MAINTIMP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainTimp;
}
QT_END_NAMESPACE

class MainTimp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainTimp(QWidget *parent = nullptr);
    ~MainTimp() override;

private:
    Ui::MainTimp *ui;
};
#endif // MAINTIMP_H
