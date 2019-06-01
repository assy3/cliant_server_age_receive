////////////////////////////////////////////////////////////////////////////////////////
//Linux gcc での　TCP/IP サンプルプログラム（ここからはクライアント）
//入力されたデータをクライアントに送り，もらったデータを表示する
//サーバープログラムを実行してからクライアントプログラムを実行して下さい

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 6665 //サーバープログラムとポート番号を合わせてください

int main(){
  // IP アドレス，ソケット，sockaddr_in 構造体
  char destination[32];
  int dstSocket;
  struct sockaddr_in dstAddr;

  //struct sockaddr_in addr;
  struct hostent *hp;
  char   buf[1024];
  int    numrcv;

  // 相手先アドレスの入力と送る文字の入力
  printf("サーバーマシンのIPは？:");
  scanf("%s", destination);
  
  //sockaddr_in 構造体のセット
  bzero((char *)&dstAddr, sizeof(dstAddr));
  dstAddr.sin_family = AF_INET;
  dstAddr.sin_port = htons(PORT);
  
  hp = gethostbyname(destination);
  bcopy(hp->h_addr, &dstAddr.sin_addr, hp->h_length);

  //ソケットの生成
  dstSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  //接続
  if (connect(dstSocket, (struct sockaddr *)&dstAddr, sizeof(dstAddr)) < 0){
    printf("%s に接続できませんでした\n",destination);
    return(-1);
  }
  printf("%s に接続しました\n",destination);
  printf("生年月日を入力してください 例：19XX/XX/XX \n");
  
  while (1){
    scanf("%s",buf);
	
	// 気休めのセーフ処理
	if(!(buf[4] == '/' && buf[7] == '/')){
		printf("正しいフォーマットで入力してください→ %s\n\n",buf);
		close(dstSocket);
		return(0);
	}
    //パケットの送信
    write(dstSocket, buf, 1024);
    //パケットの受信
    numrcv = read(dstSocket, buf, 1024);

    printf("あなたの年齢は→ %c%c歳です\n\n",buf[0],buf[1]);
  }
  close(dstSocket);
  return(0);
}
