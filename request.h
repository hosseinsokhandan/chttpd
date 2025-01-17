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
#ifndef REQUEST_H_
#define REQUEST_H_


/**
 * @brief Parses an HTTP request.
 *
 * This function parses the start line and headers of an HTTP request
 * represented by the given chttpd_connection struct. It checks if the
 * start line and headers have already been parsed and, if not, invokes the
 * corresponding parsing functions. If any parsing operation fails, the
 * function returns -1 to indicate an error.
 *
 * @param req Pointer to the chttpd_connection struct representing the
 * connection and request.
 * @return 0 if the request parsing is successful, -1 otherwise.
 */
int
chttpd_request_parse(struct chttpd_connection *req);


void
chttpd_request_reset(struct chttpd_connection *conn);


#endif  // REQUEST_H_
