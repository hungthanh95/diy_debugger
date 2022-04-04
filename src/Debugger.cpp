#include "Debugger.h"

void Debugger::handle_command(const std::string &cmd) {
    auto args = split(cmd, ' ');
    auto command = args[0];

    if (is_prefix(command, "continue")) {
        continue_execution();
    }
    else if (is_prefix(command, "break")) {
        std::string addr {args[1], 2}; //naively assume that the user has writtern 0xADDRESS
        set_breakpoint_at_address(std::stol(addr, 0, 16));
    }
    else {
        std:cerr << "Unknown command\n";
    }
}

void Debugger::continue_execution() {
    ptrace(PTRACE_CONT, _pid, nullptr, nullptr);

    int wait_status;
    auto options = 0;
    waitpid(m_pid, &wait_status, options);
}

void Debugger::run() {
    int wait_status;
    auto options = 0;
    waitpid(_pid, &wait_status, options);

    char * line = nullptr;
    while( (line = linenoise("minidbg> ")) != nullptr) {
        handle_command(line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}

void Debugger::set_breakpoint_at_address(std::intptr_t addr) {
    std::cout << "Set breakpoint at address 0x" << std::hex << addr << std::endl;
    Breakpoint bp {_pid, addr};
    bp.enable();
    _breakpoints[addr] = bp;
}