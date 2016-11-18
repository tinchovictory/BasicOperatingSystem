#ifndef _RTL8139_H_
#define _RTL8139_H_

#define NULL ((void *)0)

void initRTL();

void sendMsg(char * message, int len);

#endif