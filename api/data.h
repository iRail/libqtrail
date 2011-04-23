//
// Configuration
//

// Include guard
#ifndef DATA_H
#define DATA_H

// Includes
#include <QObject>
#include <QHash>

namespace iRail
{
    class Data : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Id id READ id CONSTANT)
    public:
        // Auxiliary types
        struct Id
        {
            // Operator implementation
            virtual bool equals(const Id& id) const = 0;
            virtual unsigned int hash() const = 0;

            // Operators
            friend unsigned int qHash(const Id& id);
            friend bool operator==(const Id& lhs, const Id& rhs);
        };

        // Basic I/O
        virtual Id& id() const = 0;

        // Operator implementation
        virtual bool equals(const Data& data) const = 0;
        virtual Data& assign(const Data& data) = 0;

        // Operators
        virtual Data& operator=(const Data& data)
        {
            return assign(data);
        }

        friend bool operator==(const Data& lhs, const Data& rhs);
    };

    unsigned int qHash(const Data::Id& id)
    {
        return id.hash();
    }

    bool operator==(const Data::Id& lhs, const Data::Id& rhs)
    {
        return lhs.equals(rhs);
    }

    bool operator==(const Data& lhs, const Data& rhs)
    {
        return lhs.equals(rhs);
    }
}

#endif // DATA_H
