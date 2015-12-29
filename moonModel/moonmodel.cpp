#include <QDate>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include "moonmodel.h"

positions::positions(int hour, int minute, double UT, double RA, double Dec, double topRA, double topDec, double LST, double HA, double Az, double El, double dist)
{
    m_hour  = hour;
    m_minute= minute;
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

MoonModel::MoonModel(QAbstractListModel *parent):
    QAbstractListModel (parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    //setFlag(ItemHasContents, true);
    m_lon = 1.96;
    m_lat = 41.27;
    qDebug() << "Initializing MoonModel";

    m_pTimer = new QTimer (this);
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT (on_timer()));
    m_pTimer->start (1000);
    calcPositions();
}

MoonModel::~MoonModel()
{
}

void MoonModel::on_timer()
{
    calcPositions();
}

void MoonModel::calcPositions()
{
    foreach (positions *pos, m_positions)
        delete pos;
    m_positions.clear();

    double  RA, Dec, topRA, topDec, LST, HA, Az, El, dist;

    QTime   time = QTime::currentTime();
    QDate   date = QDate::currentDate();

    time = time.addSecs(-240);

    for (int n=0;n<6;n++)
    {
        int hour = time.hour();
        int minute = time.minute();
        double  UT = hour+minute/60.;
        moon2(date.year(), date.month(), date.day(),
              UT,
              1.96, 41.27,
              &RA, &Dec, &topRA, &topDec, &LST, &HA, &Az, &El, &dist);

//        qDebug() << hour << minute << RA << Dec << topRA << topDec << LST << HA << Az << El << dist;
//        QModelIndex newRow = this->createIndex( n, 0);
        positions *pos = new positions (hour,minute,UT, RA, Dec, topRA, topDec, LST, HA, Az, El, dist);

        m_positions.append(pos);
        time = time.addSecs(120);
        QModelIndex modelIndex = this->index(n,0);
        setData(modelIndex, n, 0);
    }
}

QVariant MoonModel::data(const QModelIndex &index, int role) const
{
    switch (role){

        case NameRole:
        case TextRole:
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

    return EXIT_FAILURE;
}

bool MoonModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    emit dataChanged (index,index);

    return 0;
}

QHash<int, QByteArray> MoonModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole]     = "name";
    roles[TextRole]     = "text";
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

int MoonModel::rowCount(const QModelIndex &parent) const
{
//    qDebug() << "size = " << m_positions.size();
    Q_UNUSED (parent);
    return m_positions.size();
}

void MoonModel::setQTH(double lon, double lat)
{
    m_lon = lon;
    m_lat = lat;
    calcPositions();
}
