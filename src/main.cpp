#include <mud.hpp>

int main() {
    if(Mud::instance().run()) {
        return 0;
    }
    return 1;
}
