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
#ifndef CHTTPD_H_
#define CHTTPD_H_


#include <sys/socket.h>

#include <mrb.h>
#include <caio.h>


enum chttpd_connection_status {
    CCS_HEADER,
    CCS_BODY,
    CCS_COMPLETED,
    CCS_CLOSING,
};


struct chttpd_request;


struct chttpd_connection {
    enum chttpd_connection_status status;
    int fd;
    struct sockaddr localaddr;
    struct sockaddr remoteaddr;
    mrb_t inbuff;
    mrb_t outbuff;
    struct chttpd_request *request;
};


struct chttpd_request {
    char *header;
    size_t headerlen;
    const char *verb;
    const char *path;
    const char *version;
    const char *connection;
    const char *contenttype;
    int contentlength;
    struct chttpd_connection *tcpconn;
};


/* Route Types */
struct chttpd_route {
    const char *pattern;
    const char *verb;
    caio_coro handler;
};


/* Core Types */
struct chttpd {
    const char *bindaddr;
    unsigned short bindport;
    int backlog;
    size_t buffsize;
    struct chttpd_route *routes;
};


/* Helper Macros */
#define CHTTPD_ROUTE(p, v, h) {(p), (v), (caio_coro)h}
#define CHTTPD_RESPONSE_FLUSH(req) while (chttpd_response_flush(req)) { \
        if (CMUSTWAIT()) { \
            CORO_WAIT((req)->tcpconn->fd, COUT); \
            continue; \
        } \
        chttpd_response_close(req); \
    }


#define CHTTPD_RESPONSE_FINALIZE(req) \
    chttpd_response_finalize(req); \
    CHTTPD_RESPONSE_FLUSH(req)


ASYNC
chttpdA(struct caio_task *self, struct chttpd *state);


int
chttpd_response_start(struct chttpd_request *req, const char *format, ...);


int
chttpd_response_header(struct chttpd_request *req, const char *format, ...);


int
chttpd_response_flush(struct chttpd_request *req);


int
chttpd_response_close(struct chttpd_request *req);


int
chttpd_response_finalize(struct chttpd_request *req);


int
chttpd_response_body(struct chttpd_request *req, const char *format, ...);


int
chttpd_forever(struct chttpd *state, int maxconn);


#endif  // CHTTPD_H_
