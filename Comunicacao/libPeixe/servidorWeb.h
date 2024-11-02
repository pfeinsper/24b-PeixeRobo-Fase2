#ifndef WEB_HANDLERS_H
#define WEB_HANDLERS_H

#include <WebServer.h>

// Declarações das funções
void handleForm();
void handlePost();

// Declaração de um ponteiro para o servidor, que será usado no arquivo .cpp
extern WebServer server;

#endif
