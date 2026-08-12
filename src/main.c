#include "../include/http.h"
#include "../include/main.h"
#include "../include/tcp.h"

void debug_log(char msg[]) { printf("DEBUG LOG: %s\n", msg); }

int main() {
  tcp_server server = {0};

  server_status_e status = bind_tcp_port(&server, 8080);

  if (status != SERVER_OK) {
    debug_log("Server initialization failed");
    exit(EXIT_FAILURE);
  }

  int client_fd = accept_client(server.socket_fd);

  if (client_fd == -1) {
    debug_log("Failed to accept client connection");
    close(server.socket_fd);
    exit(EXIT_FAILURE);
  }

  debug_log("Client connected");

  http_request req = {0};

  if (read_http_request(client_fd, &req) != HTTP_PARSE_OK) {
    debug_log("Failed to read HTTP request");
    close(client_fd);
  }

  close(client_fd);
  close(server.socket_fd);
  return 0;
}
