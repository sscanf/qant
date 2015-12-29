#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QList>
#include "moon2.h"


class positions
{
public:

    positions (double UT, double RA, double Dec, double topRA, double topDec, double LST, double HA, double Az, double El, double dist);

    double m_UT;
    double m_RA;
    double m_Dec;
    double m_topRA;
    double m_topDec;
    double m_LST;
    double m_HA;
    double m_Az;
    double m_El;
    double m_dist;
};

class listModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum positionRoles{
        YearRole = Qt::UserRole + 1,
        MonthRole,
        DayRole,
        UtRole,
        RaRole,
        DecRole,
        TopRaRole,
        TopDecRole,
        LstRole,
        AzRole,
        ElRole,
        DistRole
    };

    listModel(QAbstractListModel *parent = 0);
    QVariant data (const QModelIndex &index, int role) const;
    QHash<int, QByteArray> rolenames();
    int rowCount (const QModelIndex &parent) const;

protected:

    QList<positions *>m_positions;
    double m_lon;
    double m_lat;

};

#endif // LISTMODEL_H
