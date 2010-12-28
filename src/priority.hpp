#ifndef MONOMI_PRIORITY_HPP
#define MONOMI_PRIORITY_HPP

namespace monomi {
    // Priority for actors. Actors with lower priority will be updated before
    // actors with higher priority.
    //
    // Set priority to <priorityCount> to skip all updates for the actor.
    enum Priority {
        scriptPriority,
        kinematicPriority,
        dynamicPriority,

        priorityCount
    };
}

#endif // MONOMI_PRIORITY_HPP
