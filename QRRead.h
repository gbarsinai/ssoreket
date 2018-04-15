/*
 * QRRead.h
 *
 *  Created on: Jan 27, 2018
 *      Author: W7
 */

#ifndef QRREAD_H_
#define QRREAD_H_

int readQR(char* jpgPath, char* outBuff);
int renameQR(const char *path, char** fileList, int listLen);

#endif /* QRREAD_H_ */
