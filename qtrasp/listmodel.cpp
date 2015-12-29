#include <QTime>
#include "listmodel.h"
#include <QDebug>
#include "moon2.h"

positions::positions(double UT, double RA, double Dec, double topRA, double topDec, double LST, double HA, double Az, double El, double dist)
{
    m_UT    = UT;
    m_RA    = RA;
    m_Dec   = Dec;
    m_topRA = topRA;
    m_topDec= topDec;
    m_LST   = LST;
    m_HA    = HA;
    m_Az    = Az;
    m_El    = El;
    m_dist  = dist;
}

listModel::listModel (QAbstractListModel *parent) :
    QAbstractListModel(parent)
{

    double  RA, Dec, topRA, topDec, LST, HA, Az, El, dist;

    m_lon = 0;
    m_lat = 0;

    QDate   date = QDate::currentDate();
    QTime   time (0,0,0,0);

    for (int n=0;n<1440;n++)
    {
        int hour = time.hour();
        int minute = time.minute();
//        int seconds = time.second();
        double  UT = hour+minute/60.;

        moon2(date.year(), date.month(), date.day(),
              UT,
              m_lon, m_lat,
              &RA, &Dec, &topRA, &topDec, &LST, &HA, &Az, &El, &dist);

        qDebug() << hour << minute << RA << Dec << topRA << topDec << LST << HA << Az << El << dist;
        positions *pos = new positions (UT, RA, Dec, topRA, topDec, LST, HA, Az, El, dist);
        m_positions.append(pos);

        time = time.addSecs(120);
    }


}

QVariant listModel::data(const QModelIndex &index, int role) const
{
    switch (role){

        case UtRole:
            return QVariant (m_positions.at(index.row())->m_UT);

        case RaRole:
            return QVariant (m_positions.at(index.row())->m_RA);

        case DecRole:
            return QVariant (m_positions.at(index.row())->m_Dec);

        case TopRaRole:
            return QVariant (m_positions.at(index.row())->m_topRA);

        case TopDecRole:
            return QVariant (m_positions.at(index.row())->m_topDec);

        case LstRole:
            return QVariant (m_positions.at(index.row())->m_LST);

        case AzRole:
            return QVariant (m_positions.at(index.row())->m_Az);

        case ElRole:
            return QVariant (m_positions.at(index.row())->m_El);

        case DistRole:
            return QVariant (m_positions.at(index.row())->m_dist);
    }
}

QHash<int, QByteArray> listModel::rolenames()
{
    QHash<int, QByteArray> roles;
    roles[UtRole]       = "ut";
    roles[RaRole]       = "ra";
    roles[DecRole]      = "dec";
    roles[TopRaRole]    = "topRa";
    roles[TopDecRole]   = "topDec";
    roles[LstRole]      = "lst";
    roles[AzRole]       = "az";
    roles[ElRole]       = "el";
    roles[DistRole]     = "dist";
    return roles;
}

int listModel::rowCount(const QModelIndex &parent) const
{
    return m_positions.size();
}
