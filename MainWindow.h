//
// Created by awesyr on 21.01.2021.
//

#ifndef QTTEST_MAINWINDOW_H
#define QTTEST_MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include "QuestionModel.h"
#include "QuestionView.h"
#include "CircularProgressBar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:
    void saveToPdf();

private:
    void setupWidgets();
    void setupActions();

    QuestionModel *mModel;
    QuestionView *mQuestionView;
    QListView *mQuestionList;
    CircularProgressBar *mProgressBar;
    Ui::MainWindow *ui;
};

#endif //QTTEST_MAINWINDOW_H
