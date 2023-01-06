#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QDate>
#include <QDir>
#include <QListWidget>
#include <QList>
#include "task.h"
#include "list.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    List defaultList = List("School - UC Merced");
    QVector<List> allList;
    void createNewTask(QString taskName, QString date, QString taskDesc);

 public slots:
    void SlotDeleteTask();



private slots:
    void on_actionNew_triggered();
    void on_addNewBtn_clicked();

    void on_actionOpen_triggered();

    void on_addNewListBtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_deleteButton_clicked();

    void on_pushButton_4_clicked();

    void on_prirSortButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
