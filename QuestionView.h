//
// Created by arseny on 06.01.2021.
//

#ifndef QTTEST_QUESTIONVIEW_H
#define QTTEST_QUESTIONVIEW_H

#include <QScrollArea>
#include <QLabel>
#include <QItemSelectionModel>
#include "QuestionModel.h"

class QuestionView : public QScrollArea {
    Q_OBJECT
public:
    explicit QuestionView(QWidget *parent = nullptr);

    void setModel(QuestionModel *model);
    void setSelectionModel(QItemSelectionModel *selectionModel);

public slots:
    void deleteCurrent();
    void insertImage();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    bool setupImage(const QMimeData *mimeData);

    QLabel *mImageLabel;
    QuestionModel *mModel;
    QItemSelectionModel *mSelectionModel;

private slots:
    void onCurrItemChange(const QModelIndex &current, const QModelIndex &previous);
};

#endif //QTTEST_QUESTIONVIEW_H
