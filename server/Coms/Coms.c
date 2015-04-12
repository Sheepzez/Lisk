#include "Coms.h"


int NumClients = 0;       //Current Number of clients connected
int Clients[MAX_CLIENTS]; //File Descriptor list for clients


/* Getter for NumClients */
int GetNumClients() { return NumClients; }

/* AcceptClients
 *  Sits and waits for connections to the Server
 *  Once we have MAX_CLIENTS connected, we return
 */
void AcceptClients(int Serverfd)
{
  struct sockaddr_in Cli_addr;
  int NewClient = 0;
  socklen_t Clilen;

  while(NumClients < MAX_CLIENTS)
  {
    printf("> Waiting for clients... (%d / %d)\n", GetNumClients(), MAX_CLIENTS);

    //Accept gets a connection from the client, saving a new file descriptor, checking for errors once more.
    Clilen = sizeof(Cli_addr);
    NewClient = accept(Serverfd, (struct sockaddr *) &Cli_addr, &Clilen);
    if (NewClient < 0) { printf("ERROR> Unable to accept client\n"); }
    else
    {
      Clients[NumClients] = NewClient;
      NumClients++;

      //Getting IP address to display to user
      struct sockaddr_in addr_in = (struct sockaddr_in)Cli_addr;
      char *IP = inet_ntoa(addr_in.sin_addr);
      printf("> New Client (%d): %s\n", NumClients, IP);

      //TODO Send Welcoming message, or some form of ID
      BroadcastMsg("stop");
      SendMsg(NewClient, "Welcome to Risk");
    }
  }
}

/* CloseAllClients
 *  Closes all Client connections the server current knows of
 */
void CloseAllClients()
{
  int i = 0;
  for(i = 0; i <= MAX_CLIENTS; i++)
  {
    close(Clients[i]);
  }
}

/* BroadcastMsg
 *  Sends given message to all clients
 *  NOTE: When boradcasting over localhost, server broadcasts to itself.
 */
void BroadcastMsg(char* Msg)
{
  int i = 0;
  for(i = 0; i <= MAX_CLIENTS; i++)
  {
    SendMsg(Clients[i], Msg);
  }
}


/* SendMsg
 *  Send message to given client
 *
 * TODO Fix FD to be the ID and convert the ID to FD for send
 */
int SendMsg(int Clientfd, char* Msg)
{
  char Buffer[256];
  strcpy(Buffer, Msg);
  int n = 0;

  n = write(Clientfd,Buffer,strlen(Buffer));
  if (n < 0)
  {
    printf("ERROR> Couldn't send messge to Client (%d)\n", Clientfd);
  }
  return n;
}
