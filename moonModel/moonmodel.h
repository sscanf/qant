#ifndef MoonModel_H
#define MoonModel_H

#include <QQuickItem>
#include <QAbstractListModel>
#include "moon2.h"

class positions
{
public:

    positions (int hour, int minute, double UT, double RA, double Dec, double topRA, double topDec, double LST, double HA, double Az, double El, double dist);

    int    m_hour;
    int    m_minute;
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

class MoonModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(MoonModel)

public:

    Q_INVOKABLE void setQTH (double lon, double lat);

    enum positionRoles{
        NameRole = Qt::UserRole +1,
        TextRole,
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

    MoonModel (QAbstractListModel *parent = 0);
    ~MoonModel();

    QVariant                data         (const QModelIndex &index, int role) const;
    bool                    setData      (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QHash<int, QByteArray>  roleNames    () const;
    int                     rowCount     (const QModelIndex &parent) const;

protected:
    void                    calcPositions();

protected:

    QList<positions *>m_positions;
    double    m_lon;
    double    m_lat;
    QTimer   *m_pTimer;

private slots:
    void on_timer();


};

#endif // MoonModel_H

