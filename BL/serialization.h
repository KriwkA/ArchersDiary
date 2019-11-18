#pragma once
#include <QVariant>
#include <QDataStream>

namespace Serilization
{

    template< typename T >
    QByteArray serialize(const QList<T> &list)
    {
        QByteArray serializedData;

        QDataStream out( &serializedData, QIODevice::WriteOnly );
        out << list;

        return serializedData;
    }

    template< typename T >
    QList<T> unserialize( QByteArray& serializedData )
    {
        QList<T> list;

        QDataStream in( &serializedData, QIODevice::ReadOnly );
        in >> list;

        return list;
    }

}
