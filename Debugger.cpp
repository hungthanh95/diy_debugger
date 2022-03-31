#include <iostream>
#include <string>

class Debugger {
    public:
    Debugger(std::string prog_name, pid_t pid)
        : _prog_name{std::move(prog_name)}, _pid{pid} {}

    void run();
    void handle_command(char *cmd);
    void linenoiseHistoryAdd(char *line);
    void linenoiseFree(char *line);

    private:
    std::string _prog_name;
    pid_t _pid;
}

void Debugger::handle_command(const std::string &cmd) {
    auto args = split(cmd, ' ');
    auto command = args[0];

    if (is_prefix(command, "continue")) {
        continue_execute();
    }
    else {
        std:cerr << "Unknown command\n";
    }
}

void Debugger::continue_execute() {
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