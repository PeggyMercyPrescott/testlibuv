#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

int main() {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    int uv_fs_open(loop, uv_fs_t* req, const char* path, int flags, int mode, uv_fs_cb cb)

    printf("Now quitting.\n");
    uv_run(loop, UV_RUN_DEFAULT);

    int uv_fs_close(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb)
      
    uv_loop_close(loop);
    free(loop);
    return 0;
}