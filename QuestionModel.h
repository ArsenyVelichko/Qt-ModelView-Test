//
// Created by arseny on 07.01.2021.
//

#ifndef QTTEST_QUESTIONMODEL_H
#define QTTEST_QUESTIONMODEL_H


#include <QAbstractListModel>
#include <QFile>
#include <QProgressBar>

class QuestionModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit QuestionModel(QObject *parent = nullptr);
    explicit QuestionModel(const QString &configPath, QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    int rowCount(const QModelIndex &parent) const override;
    bool removeRows(int position, int rows, const QModelIndex &parent) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addQuestion();
    void writeToPdf(const QString &pdfFilePath);

signals:
    void pixmapWritten(int index);

private:
    QList<QString> mQuestions;
    QList<QPixmap> mPixmaps;
    QString mConfigFilePath;
};


#endif //QTTEST_QUESTIONMODEL_H
