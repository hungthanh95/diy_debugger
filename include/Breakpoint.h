#include <iostream>
#include <sys/ptrace.h>

class Breakpoint {
    public:
    Breakpoint(pid_t pid, std::intptr_t adr)
        :_pid{pid}, _addr{addr}, _enabled{false}, _saved_data{}
        {}

    void enable();
    void disable();

    auto is_enabled() const -> bool { return _enabled; }
    auto get_addr() const -> std::intptr_t { return _addr; }


    private:
    pid _pid;
    std::intptr_t _addr;
    bool _enabled;
    uint32_t _saved_data;
};