#include <SL.h>

void audio();
void net();

int main(int argc, char** argv)
{
    // Initialisation
    if(!SL_init())
    {
        return -1;
    }
    slWindow* win = slWindow_init("Main", 0, 0);
    if( win == NULL )
    {
        SL_quit();
    }
    
    slFont* font = slFont_init("arial.ttf");
    slScene* scene = slScene_init(win, -1.f, -1.f, 2.f, 2.f);
    slInput* in = slInput_init();
    
    Player* player = Player_init();
    EnemyV* enemyV = EnemyV_init();
    
    int now = SDL_GetTicks();
    int prev = now;
    float dt;
    
    while(slWindow_getStatus(win) == TRUE)
    {
        now = SDL_GetTicks();
        dt = (now - prev) / 1000.f;
        prev = now;
        
        slWindow_clear(win);
        slWindow_update(win);
        slInput_update(in);
        
        slScene_update(scene, win);
        if(slInput_mouvementSouris(in) == 1)
        {
            float x = (float)slInput_getX(in) / win->w;
            Player_setX(player, x);
        }
        
        Player_update(player, dt);
        EnemyV_update(enemyV, dt);
        
        if(Player_doCollisionV(player, enemyV))
        {
            slWindow_setStatus(win, FALSE);
        }
        
        Player_draw(player, scene);
        EnemyV_draw(enemyV, scene, font, win);
        
        slFont_draw(font, win, "text printed", 0.f, 0.f);
        slWindow_draw(win);
    }
    
    EnemyV_free(&enemyV);
    Player_free(&player);
    slScene_free(&scene);
    slFont_free(&font);
    slWindow_free(&win);
    SL_quit();
    return 0;
}










void net()
{
    if (SDLNet_Init() == -1) {
    printf("SDLNet_Init: %s\n", SDLNet_GetError());
    exit(2);
  }

  bool done = false;
  char* app = "server";

  if (strcmp(app, "server") == 0)
  {
    SL_errorPrint(STRING, "Starting server...");
    TCPsocket server, client;
    IPaddress ip;
    SDLNet_ResolveHost(&ip, NULL, 9999);
    server = SDLNet_TCP_Open(&ip);
    
    while (!done) {
      /* try to accept a connection */
      client = SDLNet_TCP_Accept(server);

      /* get the clients IP and port number */
      IPaddress *remoteip;
      remoteip = SDLNet_TCP_GetPeerAddress(client);

      /* print out the clients IP and port number */
      Uint32 ipaddr;
      ipaddr = SDL_SwapBE32(remoteip->host);
      printf("Accepted a connection from %d.%d.%d.%d port %hu\n", ipaddr >> 24,
             (ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
             remoteip->port);

      while (1) {
        /* read the buffer from client */
        char message[1024];
        int len = SDLNet_TCP_Recv(client, message, 1024);
        
        /* print out the message */
        printf("Received: %.*s\n", len, message);
        if (message[0] == 'q') {
          printf("Disconecting on a q\n");
          break;
        }
        if (message[0] == 'Q') {
          printf("Closing server on a Q.\n");
          done = true;
          break;
        }
      }
      SDLNet_TCP_Close(client);
    }
  }
  else if(strcmp(app, "client") == 0)
  {
    printf("Starting client...\n");
    IPaddress ip;
    TCPsocket tcpsock;

    SDLNet_ResolveHost(&ip, "192.168.1.2", 9999);

    tcpsock = SDLNet_TCP_Open(&ip);

    while (1) {
      printf("message: ");
      char message[1024];
      fgets(message, 1024, stdin);
      int len = strlen(message);

      /* strip the newline */
      message[len - 1] = '\0';

      if (len) {
        int result;

        /* print out the message */
        printf("Sending: %.*s\n", len, message);

        result =
            SDLNet_TCP_Send(tcpsock, message, len); /* add 1 for the NULL */
        if (result < len)
          printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
      }

      if (len == 2 && tolower(message[0]) == 'q') {
        break;
      }
    }

    SDLNet_TCP_Close(tcpsock);
  } else {
    printf("Choose server or client\n");
  }

  SDLNet_Quit();
}
