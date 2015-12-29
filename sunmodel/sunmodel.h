#ifndef SUNMODEL_H
#define SUNMODEL_H

#include <QAbstractListModel>
#include "sun.h"

class SunModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(SunModel)

public:
    enum positionRoles{
        NameRole = Qt::UserRole +1,
        HourRole,
        MinuteRole,
        UtRole,
        RaRole,
        DecRole,
        TopRaRole,
        TopDecRole,
        LstRole,
        AzRole,
        ElRole,
        DistRole,
        HARole
    };

    SunModel(QAbstractListModel *parent = 0);
    ~SunModel();

    QVariant                data         (const QModelIndex &index, int role) const;
    bool                    setData      (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QHash<int, QByteArray>  roleNames    () const;
    int                     rowCount     (const QModelIndex &parent) const;

private:
    sun *m_pSun;
};

#endif // SUNMODEL_H

