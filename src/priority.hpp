#ifndef MONOMI_PRIORITY_HPP
#define MONOMI_PRIORITY_HPP

namespace monomi {
    // Priority for actors. Actors with lower priority will be updated before
    // actors with higher priority.
    enum Priority {
        scriptPriority,
        kinematicPriority,
        dynamicPriority,

        priorityCount
    };
}

#endif // MONOMI_PRIORITY_HPP
