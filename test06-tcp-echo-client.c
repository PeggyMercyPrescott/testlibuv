/** this program might leak memory; noticed by writer (https://nikhilm.github.io/uvbook) **/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/socket.h>
#include <uv.h>

#define DEFAULT_PORT  13370
#define DEFAULT_BACKLOG 1024

uv_loop_t *loop;

void on_close(uv_handle_t* handle) {
  
}

void cb(uv_write_t* req, int status) {
  uv_close(req->handle, on_close);
}

void on_connect(uv_connect_t* req, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
  
uv_buf_t a[] = {
  { .base = "O", .len = 1 },
  { .base = "k", .len = 1 }
};
uv_write_t req1;
  
uv_write(&req1, req.handle, a, 2, cb);

}

int main() {
    loop = uv_default_loop();
  
uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
uv_tcp_init(loop, socket);

uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));

struct sockaddr_in dest;
uv_ip4_addr("127.0.0.1", 13370, &dest);

uv_tcp_connect(connect, socket, (const struct sockaddr*)&dest, on_connect);
  
  
    return uv_run(loop, UV_RUN_DEFAULT);
}
