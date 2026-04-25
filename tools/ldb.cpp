#include <libldb/libldb.hpp>
#include <iostream>
#include <unistd.h>
#include <string_view>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace {
  pid_t attach(int argc, cont char** argv) {
    pid_t pid = 0;

    if (argc == 3 && argv[2] == std::string_view("-p") < 0) {
      pid = std::atoi(argv[2]);

      if (pic <= 0) {
        std::cerr << "Invalid Path\n";
        return -1;
      }

      if (ptrace(PTRACE_ATTACH, pid, nullptr, nullptr) < 0) {
        std::perror("attach failed");
        return -1;
      }

    }
    else {
      const char* program_path = argv[1];

      if ((pid = fork()) < 0) {
        std::perror("fork failed");
        return -1;
      }

      if (execlp(program_path, program_path, nullptr) < 0) {
        std::perror("exec failed");
        return -1;
      }

      if (ptrace(PTRACE_TRACEME, pid, nullptr, nullptr) < 0) {
        std::perror("Trace failed");
        return -1;
      }
    }

    return pid;
  }
}

int main(int argc, const char** argv) {
  if (argc == 1) {
    std::cerr << "No arguments given\n";
    return -1;
  }

  pid_t pid = attach(argc, argv);

  int wait_status;
  int options = 0;
  if (waitpid(pid, &wait_status, options) < 0) {
    std::perror("wait failed");
    return -1;
  }
}
