//
// Created by awesyr on 21.01.2021.
//

#ifndef QTTEST_CIRCULARPROGRESSBAR_H
#define QTTEST_CIRCULARPROGRESSBAR_H

#include <QProgressBar>

class CircularProgressBar : public QProgressBar {
public:
    explicit CircularProgressBar(int radius, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
};


#endif //QTTEST_CIRCULARPROGRESSBAR_H
