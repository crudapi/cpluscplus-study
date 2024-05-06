// CMakeProjectMsgStat.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectMsgStat.h"

#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <ctime>
#include "stdio.h"
#include "errno.h"
void msg_stat(int, struct msqid_ds);
main()
{
	int gflags, sflags, rflags;
	key_t key;
	int msgid;
	int reval;
	struct msgsbuf {
		int mtype;
		char mtext[1];
	}msg_sbuf;
	struct msgmbuf
	{
		int mtype;
		char mtext[10];
	}msg_rbuf;
	struct msqid_ds msg_ginfo, msg_sinfo;
	char  msgpath[] = "./test";

	key = ftok(msgpath, 'b');
	gflags = IPC_CREAT | IPC_EXCL;
	msgid = msgget(key, gflags | 00666);
	if (msgid == -1)
	{
		printf("msg create error\n");
	}
	//´´½¨Ò»¸öÏûÏ¢¶ÓÁÐºó£¬Êä³öÏûÏ¢¶ÓÁÐÈ±Ê¡ÊôÐÔ
	msg_stat(msgid, msg_ginfo);
	sflags = IPC_NOWAIT;
	msg_sbuf.mtype = 10;
	msg_sbuf.mtext[0] = 'a';
	reval = msgsnd(msgid, &msg_sbuf, sizeof(msg_sbuf.mtext), sflags);
	if (reval == -1)
	{
		printf("message send error\n");
	}
	//·¢ËÍÒ»¸öÏûÏ¢ºó£¬Êä³öÏûÏ¢¶ÓÁÐÊôÐÔ
	msg_stat(msgid, msg_ginfo);


	reval = msgctl(msgid, IPC_RMID, NULL);//É¾³ýÏûÏ¢¶ÓÁÐ
	if (reval == -1)
	{
		printf("unlink msg queue error\n");
	}
}
void msg_stat(int msgid, struct msqid_ds msg_info)
{
	int reval;
	sleep(1);//Ö»ÊÇÎªÁËºóÃæÊä³öÊ±¼äµÄ·½±ã
	reval = msgctl(msgid, IPC_STAT, &msg_info);
	if (reval == -1)
	{
		printf("get msg info error\n");
	}
	printf("\n");
	printf("current number of bytes on queue is %d\n", msg_info.msg_cbytes);
	printf("number of messages in queue is %d\n", msg_info.msg_qnum);
	printf("max number of bytes on queue is %d\n", msg_info.msg_qbytes);
	//Ã¿¸öÏûÏ¢¶ÓÁÐµÄÈÝÁ¿£¨×Ö½ÚÊý£©¶¼ÓÐÏÞÖÆMSGMNB£¬ÖµµÄ´óÐ¡ÒòÏµÍ³¶øÒì¡£ÔÚ´´½¨ÐÂµÄÏûÏ¢¶ÓÁÐÊ±£¬//msg_qbytesµÄÈ±Ê¡Öµ¾ÍÊÇMSGMNB
	printf("pid of last msgsnd is %d\n", msg_info.msg_lspid);
	printf("pid of last msgrcv is %d\n", msg_info.msg_lrpid);
	printf("last msgsnd time is %s", ctime(&(msg_info.msg_stime)));
	printf("last msgrcv time is %s", ctime(&(msg_info.msg_rtime)));
	printf("last change time is %s", ctime(&(msg_info.msg_ctime)));
	printf("msg uid is %d\n", msg_info.msg_perm.uid);
	printf("msg gid is %d\n", msg_info.msg_perm.gid);
}
