#pragma once
#include "../DLMS/objects.h"

int com_init();
int com_close();
int com_error();

int com_write();
int com_read(DLMS_object *object);