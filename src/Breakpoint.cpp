#include "Breakpoint.h"

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
