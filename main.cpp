#include "html_message.h"
#include "xml.h"
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <signal.h>
#include <strstream>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define PORT 8888

void signalHandler(int signal) { exit(EXIT_SUCCESS); }

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    std::cerr << "Fork failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  if (setsid() < 0) {
    std::cerr << "setsid failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (chdir("/tmp/render") < 0) {
    std::cerr << "chdir failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  signal(SIGTERM, signalHandler);
  signal(SIGINT, signalHandler);
  signal(SIGQUIT, signalHandler);

  int serverSocket;
  if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Socket creation failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  // redirect cout to log file
  int logFile =
      open("/tmp/render/server_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);

  if (logFile < 0) {
    cout << "Log file creation failed" << endl;
    exit(EXIT_FAILURE);
  }

  if (dup2(logFile, STDOUT_FILENO) < 0) {
    cout << "dup2 failed" << endl;
    exit(EXIT_FAILURE);
  }

  if (dup2(logFile, STDERR_FILENO) < 0) {
    cout << "dup2 failed" << endl;
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(PORT);

  if (bind(serverSocket, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) < 0) {
    std::cerr << "Socket bind failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (listen(serverSocket, 5) < 0) {
    std::cerr << "Listen failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  int clientSocket;
  socklen_t clientAddressLength;
  struct sockaddr_in clientAddress;

  while (true) {
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress,
                          &clientAddressLength);
    if (clientSocket < 0) {
      std::cerr << "Accept failed" << std::endl;
      exit(EXIT_FAILURE);
    }
    HTML html;
    ssize_t bytesRead = read(clientSocket, &html, sizeof(html));
    if (bytesRead != sizeof(html)) {
      std::cerr << "Read failed" << std::endl;
      exit(EXIT_FAILURE);
    }

    // Write data from the Message struct to the log file
    int logFile =
        open("/tmp/render/log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (logFile < 0) {
      std::cerr << "Failed to open log file" << std::endl;
      exit(EXIT_FAILURE);
    }
    write(logFile, "Received HTML Request\n", 22);

    XML<ostream> xml(html.tag, html.id);
    xml.content = html.content;

    std::ostrstream oss;

    xml.render(oss);

    std::string str = oss.str();

    cout << str << endl;

    close(logFile);
    close(clientSocket);
  }

  return 0;
}
