#include "global_object_registry.hpp"
#include "object_registry.hpp"

#include <memory>

using namespace monomi;

int main(int argc, char *argv[])
{
    std::auto_ptr<ObjectRegistry> objectRegistry(new ObjectRegistry);
    globalObjectRegistry = objectRegistry.get();
    return 0;
}
