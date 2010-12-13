#ifndef MONOMI_PROCESS_HPP
#define MONOMI_PROCESS_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class Process;

    typedef boost::shared_ptr<Process> ProcessPtr;
    typedef boost::weak_ptr<Process> ProcessWeakPtr;

    class Process {
    public:
        virtual ~Process()
        { }

        virtual bool alive() const = 0;
        virtual void update(float dt) = 0;
    };
}

#endif // MONOMI_PROCESS_HPP
