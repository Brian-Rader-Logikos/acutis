#ifndef ACUTIS_WIN_SOCKET_API_H
#define ACUTIS_WIN_SOCKET_API_H

namespace acutis::net::windows::internal {

void wsa_initialize();
void wsa_cleanup();
int wsa_log_last_error();

}// namespace acutis::net::windows::internal

#endif// !ACUTIS_WIN_SOCKET_API_H
