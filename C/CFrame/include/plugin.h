#ifndef __PLUGIN_H__
#define __PLUGIN_H__

int handleProcessInit();      //进程初始化
int handleProcessDeinit();    //进程退出的处理
int handleWorkerInit();       //工作线程的初始化
int handleWorkerDeinit();     //工作线程的关闭

int handleClientAccept();              //连接请求
int handleClientPacketProcess();       //连接处理
int handleClientClose();               //连接关闭


#endif
