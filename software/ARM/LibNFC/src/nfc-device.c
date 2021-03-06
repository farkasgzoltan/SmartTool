/*-
 * Free/Libre Near Field Communication (NFC) library
 *
 * Libnfc historical contributors:
 * Copyright (C) 2009      Roel Verdult
 * Copyright (C) 2009-2013 Romuald Conty
 * Copyright (C) 2010-2012 Romain Tartière
 * Copyright (C) 2010-2013 Philippe Teuwen
 * Copyright (C) 2012-2013 Ludovic Rousseau
 * Additional contributors of this file:
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

/**
 * @file nfc-device.c
 * @brief Provide internal function to manipulate nfc_device type
 */

#include <stdlib.h>
#include <string.h>
#include "freeRTOS.h"

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif // HAVE_CONFIG_H

#include "nfc-internal.h"

#ifdef NFC_STATIC_STRUCTS
static nfc_device dev;
#endif

nfc_device *
nfc_device_new(const nfc_context *context, const nfc_connstring connstring)
{
#ifndef NFC_STATIC_STRUCTS
  nfc_device *res = pvPortMalloc(sizeof(*res));
#else
  nfc_device *res = &dev;
#endif
  if (!res) {
    return NULL;
  }

  // Store associated context
  res->context = context;

  // Variables initiatialization
  // Note: Actually, these initialization will be overwritten while the device
  // will be setup. Putting them to _false_ while the default is _true_ ensure we
  // send the command to the chip
  res->bCrc = false;
  res->bPar = false;
  res->bEasyFraming    = false;
  res->bAutoIso14443_4 = false;
  res->last_error  = 0;
 // memcpy(res->connstring, connstring, sizeof(res->connstring));
  res->driver_data = NULL;
  res->chip_data   = NULL;

  return res;
}

void
nfc_device_free(nfc_device *dev)
{
#ifndef NFC_STATIC_STRUCTS
   if (dev) {
	  vPortFree(dev->driver_data);
	  vPortFree(dev);
  }
#endif
}
