/*
 * buffApp.h
 *
 *  Created on: Sep 8, 2018
 *      Author: Sam2
 */

#pragma once

#define SEARCHING_FOR_SECTOR (0)
#define PROCESSING_SECTOR    (1)

void initRxDigestor();
void processIncomingData(uint8_t rxByte);
