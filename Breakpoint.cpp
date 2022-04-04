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

void Breakpoint::enable() {
    auto data = ptrace(PTRACE_PEEKDATA, _pid, _addr, nullptr);
    _saved_data = static_cast<uint8_t>(data & 0xff); // save bottom byte
    uint64_t int3 = 0xcc;
    uint64_t data_with_int3 = ((data & ~0xff) | int3); //set bottom byte to 0xcc
    ptrace(PTRACE_POKEDATA, _pid, _addr, data_with_int3);

    _enabled = true;
}

void Breakpoint::disable() {
    auto data = ptrace(PTRACE_PEEKDATA, _pid, _addr, nullptr);
    auto restored_data = ((data & ~0xff) | _saved_data);
    ptrace(PTRACE_POKEDATA, _pid, _addr, restored_data);

    _enabled = false;
}
