#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <QLineEdit>
#include <QComboBox>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<QLineEdit*> vLe;
    QTabWidget tabw;

    QString str_book();
    QString str_stat();
    QString str_site();
public slots:
    void add_avtor();
    void b_insert();
    void b_show();
    void b_reset();
    QString add_other_avtor(QComboBox* pqCB);
};
#endif // MAINWINDOW_H
