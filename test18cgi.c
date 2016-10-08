/** 
this program might leak memory; noticed by writer (https://nikhilm.github.io/uvbook)
test by telnet 127.0.0.1 13370
**/

#include <stdio.h>
#include <sys/socket.h>
#include <uv.h>

#define DEFAULT_PORT  13370
#define DEFAULT_BACKLOG 1024

uv_loop_t *loop;



void on_exit(uv_process_t *req, int64_t exit_status, int term_signal) {
    fprintf(stderr, "Process exited with status %d, signal %d\n", exit_status, term_signal);
    uv_close((uv_handle_t*) req, NULL);
}

void invoke_cgi_script(uv_stream_t* stream) {
  uv_process_t child_req;
  uv_process_options_t options;
  
    char* args[3];
    args[0] = "./uvcgitick";
    args[1] = NULL;
    args[2] = NULL;

    options.stdio_count = 3;
    uv_stdio_container_t child_stdio[3];
    child_stdio[0].flags = UV_IGNORE;
    child_stdio[1].flags = UV_INHERIT_STREAM;
    child_stdio[1].data.stream = (uv_stream_t*) client;
    child_stdio[2].flags = UV_IGNORE;
  
    options.stdio = child_stdio;
    options.exit_cb = on_exit;
    options.file = args[0];
    options.args = args;
  
    child_req.data = (void*) client;
    int r;
    if ((r = uv_spawn(loop, &child_req, &options))) {
        fprintf(stderr, "%s\n", uv_strerror(r));
        return;
    } else {
        fprintf(stderr, "Launched process with ID %d\n", child_req.pid);
    }
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        //uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
        invoke_cgi_script((uv_stream_t*)client);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}

int main() {
    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in addr;
    
    uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}
