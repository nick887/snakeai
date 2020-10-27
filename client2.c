#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include "cJSON.h"
#include "shortest.h"
#include <string.h>
#include "bfs.h"
#include "risk_rating.h"
int main(void) 
{
    char *server_ip_addr = "127.0.0.1";
    int server_ip_port = 8080;
    //////////////////////////////端口信息
    char send_message [2];
    strcpy(send_message,"g");
    int square[3];
    int view[25][25];
    int abs_position[3];//绝对坐标
    int rel_position[3];//视野内相对坐标
    char recvbuff[1024];
    char operate[2];
    int all_things[16]={1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0};
    int if_15=0;
    int if_speed=0;
    char operate_bfs[100];//生成的操作字符
    int steps=0;
////////////////////////////////////////////////////////////////////
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        fprintf(stderr, "socket error %s errno: %d\n", strerror(errno), errno);
    }

    struct sockaddr_in t_sockaddr;
    memset(&t_sockaddr, 0, sizeof(struct sockaddr_in));
    t_sockaddr.sin_family = AF_INET;
    t_sockaddr.sin_port = htons(server_ip_port);
    inet_pton(AF_INET, server_ip_addr, &t_sockaddr.sin_addr);

    if((connect(socket_fd, (struct sockaddr*)&t_sockaddr, sizeof(struct sockaddr))) < 0 ) {
        fprintf(stderr, "connect error %s errno: %d\n", strerror(errno), errno);
        return 0;
    }
    printf("connect success\n");
//----------------------------------------------------------------------------------------------
for(int i=0;i<100;i++){
	sleep(0.5);
	printf("speed:%d\n",if_speed);
    if((send(socket_fd, send_message, (char)strlen(send_message), 0)) < 0) {
        fprintf(stderr, "send message error: %s errno : %d", strerror(errno), errno);

    }
        printf("send g success\n");
    memset(recvbuff,0,sizeof(int)*256);
    if((recv(socket_fd, recvbuff, sizeof(recvbuff), 0)) < 0) {
        fprintf(stderr, "recive message error: %s errno : %d", strerror(errno), errno);

    }
        printf("receive success\n");
        cJSON *parseRoot = NULL;
        parseRoot = cJSON_Parse(recvbuff);
        ////////////////
	memset(view,0,sizeof(int)*25*25);
	show(parseRoot,square,view,abs_position,&if_15);//获取绝对坐标，视野范围，视野二维整数数组,打印地图
	printf("\n\n\n\n");
	relative_position(abs_position,rel_position,if_15);//获取相对坐标
	printf("abs_p:%d      %d \n",abs_position[0],abs_position[1]);
	printf("rel_p:%d      %d\n",rel_position[0],rel_position[1]);	
        if(parseRoot)
        {
            cJSON_Delete(parseRoot);
        parseRoot = NULL;
        }
        memset(operate,0,sizeof(char)*2);
//----------------------------------------------------------------------------------------------------以上是按照原始算法走
	risk_rating(view,square);
        memset(operate_bfs,0,sizeof(operate_bfs));
	if(!bfs(view,rel_position,all_things,square,operate_bfs))
		break;
	else
	{
        printf("***********************************************************\n");
      printf("operate_bfs:%s\n",operate_bfs);
      snprintf(operate,sizeof(operate),"%c",operate_bfs[0]);
      printf("operate:%s\n",operate);
      }

	        memset(operate_bfs,0,sizeof(operate_bfs));
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    if((send(socket_fd, operate, (char)strlen(operate), 0)) < 0) {
        fprintf(stderr, "send message error: %s errno : %d", strerror(errno), errno);

    }
        printf("operate success\n");
printf("--------------------------------------------------------------------\n");
}
    close(socket_fd);
    socket_fd = -1;

    return 0;
}
