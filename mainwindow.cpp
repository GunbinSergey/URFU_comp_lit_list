#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QComboBox* Qcb2 = ui->CB_Index;
    //QComboBox* Qcb3 = ui->CB_Index_4;
    QVector<QString> City = {"M.", "Л."};
    for (int i = 0; i < City.size(); ++i)
    {
        Qcb2->addItem(City[i]);
        //Qcb3->addItem(City[i]);
    }


    this->setWindowTitle("Оформление 'Список использованой литературы'");

    QPushButton* but_add = ui->But_Add;
    connect(but_add, SIGNAL(clicked()), this, SLOT(add_avtor()));
    but_add = ui->But_Add_4;
    connect(but_add, SIGNAL(clicked()), this, SLOT(add_avtor()));

    QPushButton* but_show = ui->But_Show;
    connect(but_show, SIGNAL(clicked()), this, SLOT(b_show()));

    QPushButton* but_res = ui->But_Save;
    connect(but_res, SIGNAL(clicked()), this, SLOT(b_reset()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::str_book()
{
    QString book_temp = "%1 %2 %3 %4// - %5.: %6.-  %7. - %8 c.";

    QString Global = "";
    QComboBox* qCB = ui->CB_author;
    QString temp_Name = qCB->itemText(qCB->currentIndex());

    QList<QString> lis = temp_Name.split(" ");
    QString author = lis[0] + " " + QString(lis[1][0]) + ". " + QString(lis[2][0]) + ". " ; //%1
    //

    // Блок 2 Название
    QString Name_of_book = ui->LE_Name->text();



     //Доп строка
    QString dop_str = ""; //%2
    if (ui->LE_Dop->text() != nullptr && ui->tabWidget->currentIndex() == 0)
    {
        dop_str += ": ";
        dop_str += ui->LE_Dop->text();
    }


    //Все авторы
    QString other_authtor = add_other_avtor(qCB); //%3
   // Global += dop;
   // Global += " - ";

    //город Издательства
    qCB = ui->CB_Index;
    QString izdat = qCB->itemText(qCB->currentIndex());



     QString Izd = ui->LE_Izd->text();
     //Global += Izd;
     //Global += ", ";
     //Год
     QString Year = ui->LE_Year->text();
     Global += Year;
        //ЕСЛИ ЛИШЬ ФРАГМЕНТ

     QString Page = ui->LE_pages->text();;




    QString ac_book = book_temp.arg(author, Name_of_book, dop_str, other_authtor, izdat, Izd, Year, Page);
    return ac_book;
}

QString MainWindow::str_stat()
{
    QString stat_temp = "%1 %2/ %3// %4, %5. - №%6. - C. %7.";

    QString Global = "";
    QComboBox* qCB;
    if (ui->tabWidget->currentIndex() == 0)
    {
         qCB = ui->CB_author;

    }
    else
    {
        qCB = ui->CB_author_4;
    }
    QString temp_Name = qCB->itemText(qCB->currentIndex());
    QList<QString> lis = temp_Name.split(" ");
    QString author = lis[0] + " " + QString(lis[1][0]) + ". " + QString(lis[2][0]) + ". " ; //%1
    //

    // Блок 2 Название
    QString Name_of_book = ui->LE_Name_4->text(); //%2

    //Все авторы
    QString other_authtor = add_other_avtor(qCB); //%3

    //Журнал
     QString shur = ui->LE_Izd_4->text();
     //Global += Izd;
     //Global += ", ";
     //Год
     QString Year = ui->LE_Year_4->text();
     Global += Year;

     //Номер выпуска
     QString Num = ui->LE_num->text();

     QString Page = ui->LE_pages_4->text();;




    QString ac_stat = stat_temp.arg(author, Name_of_book, other_authtor, shur, Year, Num ,Page);
    return ac_stat;
}

QString MainWindow::str_site()
{
    QString site_temp = "%1 [Электронный ресурс]. - Режим доступа: %2 - Заглавие с экрана. - Дата обращения (%3)";

    QString st_name = ui->LE_siteName->text();
    QString st_url = ui->LE_siteURL->text();
    QString st_date = ui->LE_SiteDate->text();

    QString ac_site = site_temp.arg(st_name, st_url, st_date);
    return ac_site;
}

void MainWindow::add_avtor()
{
    QWidget* wid = new QWidget();
    QGridLayout* glay = new QGridLayout(wid);
    QList<QString> labels = {"Фамилия", "Имя", "Отчество"};
    vLe = QVector<QLineEdit*>(3);
    for (int i = 0; i < 3; ++i)
    {
        QLabel* l = new QLabel(labels[i]);
        vLe[i] = new QLineEdit();
        glay->addWidget(l, i, 0);
        glay->addWidget(vLe[i], i, 1);
    }
    QPushButton* but = new QPushButton("Добавить");
    glay->addWidget(but,3,1);
    connect(but, SIGNAL(clicked()), this, SLOT(b_insert()));
    wid->show();

}

void MainWindow::b_insert()
{
    QString text = "";
    for (int i = 0; i < 3; ++i)
    {
        text += vLe[i]->text();
        text += " ";
    }
    QComboBox* Qcb;
    if (ui->tabWidget->currentIndex() == 0)
    {
       Qcb = ui->CB_author;
    }
    else
    {
       Qcb = ui->CB_author_4;
    }

    Qcb->addItem(text);

}

void MainWindow::b_show()
{
    // Блок 1 Получение главного автора

    QString info;

    int cur_id = ui->tabWidget->currentIndex();

    switch (cur_id) {
    case 0:
     info = str_book();
    break;
    case 2:
     info = str_stat();
     break;
    case 1:
        info = str_site();
     break;
    }



    QTextEdit* ed = ui->textEdit;
    ed->setText(info);
}

void MainWindow::b_reset()
{
    QCoreApplication::exit(-1);
}

QString MainWindow::add_other_avtor(QComboBox *pqCB)
{
    QString dop = " / ";

    int size = pqCB->count();
    if (size> 3)
    {
        size = 3;
    }

    for (int i = 0; i < size; ++i)
    {
        QString i_aut = pqCB->itemText(i);
        QList<QString> lis = i_aut.split(" ");
        //QString temp = QString(lis[1][0]);
        dop +=  QString(lis[1][0]) + ". " + QString(lis[2][0]) + ". "  +  lis[0];
        if (i != size-1)
        {
            dop += ", ";
        }
    }


    if (pqCB->count() > 3)
    {
        dop += " и др.";
    }
    return dop;
}


//Книга // Статья
// Первый автор: Фамилия И.О (Если 3 автора)
// Название [Текст]: что это
// /Остальные авторы (3 автора и др.)
//-
//[под редакцией/ перевод с англ.]
//:
//Город издания
//: Название редакции
//год - (стр. (с.) или число томов (т.))


//Электронный ресурс
// Первый автор: Фамилия И.О (Если 3 автора)
// Название [Электронный ресурс]: что это
// Остальные авторы (3 автора и др.)
//-
//[под редакцией/ перевод с англ.]
//:
//Город издания
//: Название редакции
//год - (стр. (с.) или число томов (т.))
