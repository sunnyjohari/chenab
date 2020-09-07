#include <stdio.h>
#include "../bmd_assets/bmd.h"

#ifndef ESB_H
#define ESB_H

int queue_the_request(bmd *b);
int process_esb_request(char* bmd_file_path);
int fetch_new_request_from_db(bmd *request);
void *poll_database_for_new_requets(void *vargp);

#endif