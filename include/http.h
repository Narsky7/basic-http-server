#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>
#include <stdio.h>

#define HTTP_MAX_REQUEST_LEN 8192 * 4
#define HTTP_METHOD_MAX_LEN 8
#define HTTP_PATH_MAX_LEN 2048
#define HTTP_PROTOCOL_MAX_LEN 16

typedef enum {
  HTTP_PARSE_OK,
  HTTP_PARSE_INVALID,
} http_parse_e;

typedef struct {
  char key[256];
  char value[512];
} http_header_t;

typedef struct {
  char method[HTTP_METHOD_MAX_LEN];
  char path[HTTP_PATH_MAX_LEN];
  char protocol[HTTP_PROTOCOL_MAX_LEN];
  http_header_t *headers;
  size_t header_count;
} http_request;

http_parse_e read_http_request(int socket_fd, http_request *request);

void parse_http_headers(const char *raw_request, http_request *request);

void free_http_headers(http_request *request);

#endif // HTTP_H
