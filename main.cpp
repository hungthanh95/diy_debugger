#include <iostream>

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        std::cerr << "Program name not specified" << std::endl;
        return -1;
    }

    auto prog = argv[1];

    auto pid = fork();

    if (pid == 0) {
        // were're in the child process
        // execute debugee
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        execl(prog, prog, nullptr);

    }
    else if (pid >= 1) {
        // we're in the parent process
        //execute debugger
        std::cout << "Starting debugging process " << pid << std::endl;
        Debugger dbg(prog, id);
        dbg.run();
    }

    return 0;
}
