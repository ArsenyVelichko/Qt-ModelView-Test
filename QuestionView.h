//
// Created by arseny on 06.01.2021.
//

#ifndef QTTEST_QUESTIONVIEW_H
#define QTTEST_QUESTIONVIEW_H

#include <QScrollArea>
#include <QLabel>
#include "QuestionModel.h"

class QuestionView : public QScrollArea {
    Q_OBJECT
public:
    QuestionView(QuestionModel *model, QWidget *parent = nullptr);

public slots:
    void onCurrItemChange(const QModelIndex &current, const QModelIndex &previous);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    QLabel *mImageLabel;
    QuestionModel *mModel;
    QModelIndex mCurrentIndex;
};

#endif //QTTEST_QUESTIONVIEW_H
