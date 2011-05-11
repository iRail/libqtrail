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
    Q_PROPERTY(AbstractId id READ id CONSTANT)
    public:
        // Auxiliary types
        struct AbstractId
        {
            // Operator implementation
            virtual bool equals(const AbstractId& id) const = 0;
            virtual unsigned int hash() const = 0;

            // Operators
            friend bool operator==(const AbstractId& lhs, const AbstractId& rhs);
        };        
        struct VirtualId
        {
            // Construction and destruction
            VirtualId(Data::AbstractId const* iId);
            VirtualId(const VirtualId& iVirtualId);

            // Data members
            Data::AbstractId const* id;
        };

        // Construction and destruction
        Data();
        virtual ~Data();

        // Basic I/O
        virtual AbstractId const* id() const = 0;
        virtual QVariant field(int iRole) const;

        // Operator implementation
        virtual bool equals(const Data& data) const = 0;
        virtual Data& assign(const Data& data) = 0;

        // Operators
        Data& operator=(const Data& data)
        {
            return assign(data);
        }
        friend bool operator==(const Data& lhs, const Data& rhs);
    };

    bool operator==(const Data& lhs, const Data& rhs);
    bool operator==(const Data::AbstractId& lhs, const Data::AbstractId& rhs);
    bool operator==(const Data::VirtualId& lhs, const Data::VirtualId& rhs);

    inline uint qHash(const Data::VirtualId& id) { return id.id->hash(); }
    inline uint qHash(const Data::AbstractId& id) { return id.hash(); }
}

#endif // DATA_H
