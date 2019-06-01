//Linux gcc での　TCP/IP サンプルプログラム（ここからサーバー）
//クライアントから送られてきた文字列を大文字に変換して送り返す
//サーバープログラムを実行してからクライアントプログラムを実行して下さい

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 6665 //クライアントプログラムとポート番号を合わせてください

int main(){
  int i;
  int srcSocket; //自分
  int dstSocket; //相手
  // sockaddr_in 構造体
  struct sockaddr_in srcAddr;
  struct sockaddr_in dstAddr;
  int dstAddrSize = sizeof(dstAddr);
  // 各種パラメータ
  int status;
  int numrcv;

  char buf[1024];
  char year[10];
  
  int compare_month;
  int old;

  while(1){//ループで回すことによって何度でもクライアントからつなぐことができる
    // sockaddr_in 構造体のセット
    bzero((char *)&srcAddr, sizeof(srcAddr));
    srcAddr.sin_port = htons(PORT);
    srcAddr.sin_family = AF_INET;
    srcAddr.sin_addr.s_addr = INADDR_ANY;
    
    // ソケットの生成（ストリーム型）
    srcSocket = socket(AF_INET, SOCK_STREAM, 0);
    // ソケットのバインド
    bind(srcSocket, (struct sockaddr *)&srcAddr, sizeof(srcAddr));printf("返ってきたoldだよ→ %c%c\n\n",buf[0],buf[1]);
    // 接続の許可
    listen(srcSocket, 1);
    
    // 接続の受付け
    printf("接続を待っています\nクライアントプログラムを動かして下さい\n");
    dstSocket = accept(srcSocket, (struct sockaddr *)&dstAddr, &dstAddrSize);
    printf("接続を受けました\n");
    close(srcSocket);
        
    while(1){
      //パケットの受信
      numrcv = read(dstSocket, buf, 1024);
      if(numrcv ==0 || numrcv ==-1 ){
	close(dstSocket); break;
      }


printf("year %s\n",year);

	  old = ((int)buf[0] - '0') * 1000 + ((int)buf[1] - '0') * 100 + ((int)buf[2] - '0') * 10 + ((int)buf[3] - '0');
	
	  old = 2019 - old;
	  compare_month = ((int)buf[5] - '0') * 1000 + ((int)buf[6] - '0') * 100 + ((int)buf[8] - '0') * 10 + ((int)buf[9] - '0');

      if((compare_month > 63 && compare_month < 1231) || (compare_month > 11 && compare_month < 33)){
		// nop
	  }else{
		old += 1;
	  }

      // パケットの送信

	  buf[0] = (char)((old / 10) + '0');
	  buf[1] = (char)((old % 10) + '0');
	  buf[2] = (char)((old % 100) + '0');
      write(dstSocket, buf, 1024);
      fprintf(stdout,"→ oldです %s \n",buf);
    }
  }
  return(0);
}
