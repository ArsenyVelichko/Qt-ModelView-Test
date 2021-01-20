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
    void save();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void setupWidgets();
    void setupMenus();

    QuestionModel* mModel;
    QuestionView* mQuestionView;
    QListView* mQuestionList;
};

#endif //QTTEST_MAINWINDOW_H
