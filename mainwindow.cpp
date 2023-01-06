#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include <QVector>
#include <QtAlgorithms>
#include <QPixmap>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    allList.push_back(defaultList);

    ui->setupUi(this);

    QPixmap pix("/Users/julioclopez/todoApp/user.png");
    ui->profile_image->setPixmap(pix.scaled(24,24,Qt::KeepAspectRatio));

    QPixmap plusPix("/Users/julioclopez/todoApp/plus.png");
    ui->plus_image->setPixmap(plusPix.scaled(24,24,Qt::KeepAspectRatio));

    ui->calendarWidget->setMinimumDate(QDate::currentDate());



    //To display default list
    QFrame* listFrame = ui->listFrame;
    QVBoxLayout* list = new QVBoxLayout(listFrame);
    listFrame->setLayout(list);

    QPushButton* listLabel = new QPushButton(defaultList.listName); // list name

    list->addWidget(listLabel);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    QString taskName = ui->newTaskLineEdit->text();
    QString taskDesc = ui->newTaskDesLineEdit->text();
    QString dueDate = ui->calendarWidget->selectedDate().toString();
    QString date = QDate::currentDate().toString();

    createNewTask(taskName, dueDate, taskDesc);


}



//add button for task
void MainWindow::on_addNewBtn_clicked()
{
    QString taskName = ui->newTaskLineEdit->text();
    QString taskDesc = ui->newTaskDesLineEdit->text();
    QDate dueDate = ui->calendarWidget->selectedDate();
    QString date = QDate::currentDate().toString();
    int prir = ui->comboBox->currentIndex();


    Task task1 = Task(taskName,taskDesc, dueDate, date, prir);

    defaultList.myList.push_back(task1);



     //createNewTask(taskName, dueDate, taskDesc);

}


//not used at the moment
void MainWindow::createNewTask(QString taskName, QString date, QString taskDesc) {

    Task currentTask = defaultList.myList.back();


    // Get the parent widget which the widget created to be child in
    QVBoxLayout* currentList = qobject_cast<QVBoxLayout*>(ui->allNewTasksContents->layout());

    // Create Frame for the main widget container
    QFrame* myFrame = new QFrame();
    myFrame->setFrameStyle(QFrame::StyledPanel);

    // Create Horizontal Box Layout as the Frame layout and also for easily add widget inside it
    // This is like a virtual layout. It doesn't added into ui as a ui things bcos it is just a layout.
    QHBoxLayout* newTask = new QHBoxLayout(myFrame);
    myFrame->setLayout(newTask);

    // Create Frame for the details container; task title, task name, task date created
    QFrame* taskFrame = new QFrame();
    QVBoxLayout* task = new QVBoxLayout(taskFrame);
    taskFrame->setLayout(task);

    QLabel* tasklabel = new QLabel(currentTask.taskName); // task name
    task->addWidget(tasklabel);
    QLabel* taskDescLabel = new QLabel(currentTask.taskDesc); // task name
    task->addWidget(taskDescLabel);
    QLabel* datelabel = new QLabel(currentTask.dueDate.toString()); // task date created
    task->addWidget(datelabel);

    // Insert delete button
    QRadioButton* checkMark = new QRadioButton();
    newTask->insertWidget(0, checkMark);

    // Insert the task details frame inside main task box layout
    newTask->insertWidget(1, taskFrame);



    // Store the current duplicated widget to the delete button property for easy reference
    // This is a useful function if you want to reference any widgets to the specific button
    checkMark->setProperty("CurrentTask", QVariant(QVariant::fromValue<QFrame*>(myFrame)));

    // Insert into parent ui frame
    currentList->insertWidget(currentList->count()-1, myFrame);

    // Connect the delete button
    connect(checkMark, SIGNAL(clicked()), this, SLOT(SlotDeleteTask()));

}

void MainWindow::SlotDeleteTask() {

    // Get the sender widget
    QRadioButton* fromButton = (QRadioButton*)sender();

    // Get the widget referenced in the property
    QVariant var;
    var = fromButton->property("CurrentTask");
    QFrame* taskHBox = qvariant_cast<QFrame*>(var);

    taskHBox->deleteLater();
    delete taskHBox;



}


void MainWindow::on_actionOpen_triggered()
{

}


void MainWindow::on_addNewListBtn_clicked()
{

    allList.push_back(List(ui->newListLineEdit->text()));


    QVBoxLayout* listFrame = qobject_cast<QVBoxLayout*>(ui->listFrame->layout());

    //Make frame and and assign it layout
    QFrame* indlistFrame = new QFrame();
    indlistFrame->setFrameStyle(QFrame::StyledPanel);
    QVBoxLayout* indlistLayout = new QVBoxLayout(indlistFrame);
    indlistFrame->setLayout(indlistLayout);

    //Adding frame to listframe
    listFrame->addWidget(indlistFrame);


    //Adding things into indivdual frame
    QString listName = ui->newListLineEdit->text();
    QPushButton* listLabel = new QPushButton(listName); // list name
    indlistLayout->addWidget(listLabel);

}

//refresh button for task
void MainWindow::on_pushButton_clicked()
{


    for (int i=0; i < defaultList.myList.size(); i++) {




        Task currentTask = defaultList.myList[i];

        // Get the parent widget which the widget created to be child in
        QVBoxLayout* currentList = qobject_cast<QVBoxLayout*>(ui->allNewTasksContents->layout());

        // Create Frame for the main widget container
        QFrame* myFrame = new QFrame();
        myFrame->setFrameStyle(QFrame::StyledPanel);

        // Create Horizontal Box Layout as the Frame layout and also for easily add widget inside it
        // This is like a virtual layout. It doesn't added into ui as a ui things bcos it is just a layout.
        QHBoxLayout* newTask = new QHBoxLayout(myFrame);
        myFrame->setLayout(newTask);

        // Create Frame for the details container; task title, task name, task date created
        QFrame* taskFrame = new QFrame();
        QVBoxLayout* task = new QVBoxLayout(taskFrame);
        taskFrame->setLayout(task);

        QLabel* tasklabel = new QLabel(currentTask.taskName); // task name
        task->addWidget(tasklabel);
        QLabel* taskDescLabel = new QLabel(currentTask.taskDesc); // task name
        task->addWidget(taskDescLabel);
        QLabel* datelabel = new QLabel(currentTask.dueDate.toString()); // task date created
        task->addWidget(datelabel);

        int importInt = currentTask.importance;
        if(importInt == 0) {
            QString s = "low";
            QLabel* prirLabel = new QLabel(s); // task date created
             task->addWidget(prirLabel);
        }

        else if (importInt == 1) {
            QString s = "medium";
            QLabel* prirLabel = new QLabel(s); // task date created
            task->addWidget(prirLabel);

        }

        else {
            QString s = "high";
            QLabel* prirLabel = new QLabel(s); // task date created
            task->addWidget(prirLabel);
        }


        //delete button
        QRadioButton* checkMark = new QRadioButton();
        newTask->insertWidget(0, checkMark);


        newTask->insertWidget(1, taskFrame);




        checkMark->setProperty("CurrentTask", QVariant(QVariant::fromValue<QFrame*>(myFrame)));


        currentList->insertWidget(currentList->count()-1, myFrame);


        connect(checkMark, SIGNAL(clicked()), this, SLOT(SlotDeleteTask()));


    }
}

//to sort by date
void MainWindow::on_pushButton_2_clicked()
{
   std::sort(defaultList.myList.begin(), defaultList.myList.end(), Task::sortDueDate);

}

//to sort by name
void MainWindow::on_pushButton_3_clicked()
{
    std::sort(defaultList.myList.begin(), defaultList.myList.end(), Task::sortName);
}

//delete
void MainWindow::on_deleteButton_clicked()
{
    //QVBoxLayout* currentList = qobject_cast<QVBoxLayout*>(ui->allNewTasksContents->layout());
    QVector<QFrame *> allFrames = ui->allNewTasks->findChildren<QFrame *>();

    for (int i = 0; i < allFrames.size(); i++) {
        QFrame* currentFrame = allFrames[i];
        currentFrame->deleteLater();
        delete currentFrame;
    }


}

//delete list
void MainWindow::on_pushButton_4_clicked()
{
    QVector<QFrame *> allFrames = ui->listFrame->findChildren<QFrame *>();


    for (int i = 0; i < allFrames.size(); i++) {
        QFrame* currentFrame = allFrames[i];
        currentFrame->deleteLater();
        delete currentFrame;
    }

}


void MainWindow::on_prirSortButton_clicked()
{
    std::sort(defaultList.myList.begin(), defaultList.myList.end(), Task::sortImportance);
}

