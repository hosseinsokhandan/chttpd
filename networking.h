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
#ifndef NETWORKING_H_
#define NETWORKING_H_


#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>


/**
 * @brief Listens for incoming connections on the specified address and port.
 *
 * This function creates a socket, binds it to the specified address and port,
 * and listens for incoming connections. It supports both TCP and Unix domain
 * sockets. The created socket is set to non-blocking mode.
 *
 * @param chttpd The struct containing the address and port to listen on.
 * @return The file descriptor of the listening socket on success, or -1 if an
 * error occurs.
 */
int
chttpd_listen(struct chttpd *chttpd);


#endif  // NETWORKING_H_
