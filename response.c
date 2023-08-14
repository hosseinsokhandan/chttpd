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
#include "chttpd.h"
#include "response.h"


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
