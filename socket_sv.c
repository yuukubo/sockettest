#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int
main()
{
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socklen_t len;
  int sock1, sock2;

  /* ソケットの作成 */
  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  /*** ソケットの設定 ***/

  /* IPv4を利用すること指定 */
  addr.sin_family = AF_INET;

  /* ポート番号は11111 */
  addr.sin_port = htons(11111);

  /* 任意のIFを指定 */
  addr.sin_addr.s_addr = INADDR_ANY;

  /* sockaddr_in構造体のサイズを設定 */
  /* addr.sin_len = sizeof(addr); */

  /* ソケットをIFとポートに関連付け */
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

  /* TCPクラからの接続を待つ状態に設定 */
  listen(sock0, 5);

  /* TCPクラからの接続要求を受付(1回目) */
  len = sizeof(client);
  sock1 = accept(sock0, (struct sockaddr *)&client, &len);

  /* 6文字送信 */
  /* ('H', 'E', 'L', 'L', 'O', '\0') */
  write(sock1, "HELLO", 6);

  /* TCPセッション1の終了 */
  close(sock1);

  /* TCPクラからの接続要求を受付(2回目) */
  len = sizeof(client);
  sock2 = accept(sock0, (struct sockaddr *)&client, &len);

  /* 5文字送信 */
  /* ('H', 'O', 'G', 'E', '\0') */
  write(sock2, "HOGE", 5);

  /* TCPセッション2の終了 */
  close(sock2);


  /* listenするsocketの終了 */
  close(sock0);

  return 0;
}
