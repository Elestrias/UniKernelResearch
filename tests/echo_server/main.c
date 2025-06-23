#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define INITIAL_BUF_SIZE 128

int main(int argc, char *argv[]) {
   int listen_fd, conn_fd;
   struct sockaddr_in serv_addr, cli_addr;
   socklen_t cli_len = sizeof(cli_addr);

   listen_fd = socket(AF_INET, SOCK_STREAM, 0);
   if (listen_fd < 0) {
      perror("socket");
      exit(EXIT_FAILURE);
   }

   memset(&serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_addr.sin_port = htons(8080);

   if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("bind");
      close(listen_fd);
      exit(EXIT_FAILURE);
   }

   if (listen(listen_fd, 5) < 0) {
      perror("listen");
      close(listen_fd);
      exit(EXIT_FAILURE);
   }

   printf("Echo server listening on port 8080...\n");

   while (1) {
      conn_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, &cli_len);
      if (conn_fd < 0) {
         perror("accept");
         continue;
      }

      printf("Client connected: %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

      char *buf = malloc(INITIAL_BUF_SIZE);
      if (!buf) {
         perror("malloc");
         close(conn_fd);
         continue;
      }
      size_t buf_size = INITIAL_BUF_SIZE;
      size_t buf_len = 0;

      while (1) {
         buf_len = 0;
         ssize_t n = read(conn_fd, buf + buf_len, buf_size - buf_len - 1);
         if (n < 0) {
            perror("read");
            break;
         } else if (n == 0) {
            printf("Client disconnected\n");
            break;
         }

         buf_len += n;
         buf[buf_len] = '\0';

         if (buf_len + 1 >= buf_size) {
            buf_size *= 2;
            char *new_buf = realloc(buf, buf_size);
            if (!new_buf) {
               perror("realloc");
               free(buf);
               break;
            }
            buf = new_buf;
         }
         if (buf_len > 0) {
            if (write(conn_fd, buf, buf_len) != buf_len) {
               perror("write");
            }
         }
      }



      free(buf);
      close(conn_fd);
   }

   close(listen_fd);
   return 0;
}
