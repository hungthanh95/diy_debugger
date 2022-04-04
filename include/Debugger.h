#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include <string>
#include "Breakpoint.h"

class Debugger {
    public:
    Debugger(std::string prog_name, pid_t pid)
        : _prog_name{std::move(prog_name)}, _pid{pid} {}

    void run();
    void handle_command(const std::string &cmd);
    void continue_execution();
    void linenoiseHistoryAdd(char *line);
    void linenoiseFree(char *line);
    void set_breakpoint_at_address(std::intptr_t addr);

    private:
    std::string _prog_name;
    pid_t _pid;
    std::unordered_map<std::intptr_t, Breakpoint> _breakpoints;
};