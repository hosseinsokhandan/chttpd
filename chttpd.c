// Copyright 2023 Vahid Mardani
/*
 * This file is part of chttpd.
 *  chttpd is free software: you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation, either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  chttpd is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with chttpd. If not, see <https://www.gnu.org/licenses/>.
 *
 *  Author: Vahid Mardani <vahid.mardani@gmail.com>
 */
#include <sys/socket.h>

#include <clog.h>
#include <mrb.h>
#include <carrow.h>

#include "chttpd.h"
#include "request.h"
#include "addr.h"


#undef CARROW_ENTITY
#define CARROW_ENTITY chttpd
#include <carrow_generic.c>  // NOLINT


void
chttpdA(struct chttpd_coro *self, struct chttpd *state) {
    socklen_t addrlen = sizeof(struct sockaddr);
    struct sockaddr bindaddr;
    struct sockaddr connaddr;
    static int fd;
    int connfd;
    int res;
    int option = 1;
    CORO_START;

    /* Parse listen address */
    sockaddr_parse(&bindaddr, state->bindaddr, state->bindport);

    /* Create socket */
    fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    /* Allow reuse the address */
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    /* Bind to tcp port */
    res = bind(fd, &bindaddr, sizeof(bindaddr));
    if (res) {
        CORO_REJECT("Cannot bind on: %s", sockaddr_dump(&bindaddr));
    }

    /* Listen */
    res = listen(fd, state->backlog);
    INFO("Listening on: %s", sockaddr_dump(&bindaddr));
    if (res) {
        CORO_REJECT("Cannot listen on: %s", sockaddr_dump(&bindaddr));
    }

    while (true) {
        connfd = accept4(fd, &connaddr, &addrlen, SOCK_NONBLOCK);
        if ((connfd == -1) && CMUSTWAIT()) {
            CORO_WAIT(fd, CIN | CET);
            continue;
        }

        if (connfd == -1) {
            CORO_REJECT("accept4");
        }

        /* New Connection */
        struct chttpd_request *c = malloc(sizeof(struct chttpd_request));
        if (c == NULL) {
            CORO_REJECT("Out of memory");
        }

        c->fd = connfd;
        c->localaddr = bindaddr;
        c->remoteaddr = connaddr;
        c->reqbuff = mrb_create(state->buffsize);
        c->respbuff = mrb_create(state->buffsize);
        chttpd_request_coro_create_and_run(requestA, c);
    }

    CORO_FINALLY;
    chttpd_evloop_unregister(fd);
    close(fd);
    CORO_END;
}


int
chttpd_response_start(struct chttpd_request *req, const char *format, ...) {
    // TODO: implement
    return -1;
}


int
chttpd_response_header(struct chttpd_request *req, const char *format, ...) {
    // TODO: implement
    return -1;
}


int
chttpd_response_flush(struct chttpd_request *req) {
    // TODO: implement
    return -1;
}


int
chttpd_response_close(struct chttpd_request *req) {
    // TODO: implement
    return -1;
}


int
chttpd_response_finalize(struct chttpd_request *req) {
    // TODO: implement
    return -1;
}


int
chttpd_response_body(struct chttpd_request *req, const char *format, ...) {
    // TODO: implement
    return -1;
}
