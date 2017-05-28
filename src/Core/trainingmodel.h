#ifndef TRAININGMODEL_H
#define TRAININGMODEL_H

#include "core_global.h"
#include <QAbstractListModel>

class CORESHARED_EXPORT TrainingModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TrainingModel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // TRAININGMODEL_H
