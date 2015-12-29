#include <QTime>
#include <QDate>
#include <QDebug>
#include "sunmodel.h"

SunModel::SunModel(QAbstractListModel *parent):
    QAbstractListModel (parent)
{
    QTime   time = QTime::currentTime();
    QDate   date = QDate::currentDate();

    int hour = time.hour();
    int minute = time.minute();
    double  UT = hour+minute/60.;

    m_pSun = new sun(date.year(), date.month(), date.day(),UT,1.96, 41.27);

    double elev = m_pSun->getAltit();
    double azim = m_pSun->getAzim();
    double dec  = m_pSun->getDec();

    qDebug() << elev << azim << dec;
}

SunModel::~SunModel()
{
}

QVariant SunModel::data(const QModelIndex &index, int role) const
{/*
    switch (role){

        case NameRole:
        case UtRole:
            return QVariant (m_positions.at(index.row())->m_UT);

        case HourRole:
            return QVariant (m_positions.at(index.row())->m_hour);

        case MinuteRole:
            return QVariant (m_positions.at(index.row())->m_minute);

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

        case HARole:
            return QVariant (m_positions.at(index.row())->m_HA);
    }
*/
    return EXIT_FAILURE;

}

bool SunModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

QHash<int, QByteArray> SunModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole]     = "name";
    roles[UtRole]       = "ut";
    roles[RaRole]       = "ra";
    roles[DecRole]      = "dec";
    roles[TopRaRole]    = "topRa";
    roles[TopDecRole]   = "topDec";
    roles[LstRole]      = "lst";
    roles[AzRole]       = "az";
    roles[ElRole]       = "el";
    roles[HARole]       = "ha";
    roles[DistRole]     = "dist";
    roles[MinuteRole]   = "minute";
    roles[HourRole]     = "hour";
    return roles;
}

int SunModel::rowCount(const QModelIndex &parent) const
{

}

