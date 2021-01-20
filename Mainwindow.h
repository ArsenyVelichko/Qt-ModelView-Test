//
// Created by arseny on 06.01.2021.
//

#ifndef QTTEST_MAINWINDOW_H
#define QTTEST_MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include "QuestionView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);


public slots:
    void saveToPdf();

private:
    void setupWidgets();
    void setupActions();

    QuestionModel* mModel;
    QuestionView* mQuestionView;
    QListView* mQuestionList;
};

#endif //QTTEST_MAINWINDOW_H
