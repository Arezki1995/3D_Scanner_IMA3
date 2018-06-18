/*
 * Websocket server for serial interface
 */

////
// Include files
////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <linux/serial.h>
#include <libwebsockets.h>

////
// Constants
////
#define SERIAL_READ	0
#define SERIAL_WRITE	1
#define SERIAL_BOTH	2
#define WEBSOCKET_PORT	9000
#define MAX_FRAME_SIZE	1024
#define	WAIT_DELAY	50
#define SERIAL_DEVICE	"/dev/ttyACM0"
#define SERIAL_SPEED	B9600

////
// Global variables
////
int sd=-1;

////
// Functions
////

//
// Open serial port device
//
int serialOpen(char *device,int mode){
int flags=(mode==SERIAL_READ?O_RDONLY:(mode==SERIAL_WRITE?O_WRONLY:O_RDWR));
int fd=open(device,flags|O_NOCTTY|O_NONBLOCK); 
if(fd<0){ perror(device); exit(-1); }
return fd;
}

//
// Serial port configuration
//
void serialConfig(int fd,int speed){
struct termios new;
bzero(&new,sizeof(new));
new.c_cflag=CLOCAL|CREAD|speed|CS8;
new.c_iflag=0;
new.c_oflag=0;
new.c_lflag=0;     /* set input mode (non-canonical, no echo,...) */
new.c_cc[VTIME]=0; /* inter-character timer unused */
new.c_cc[VMIN]=1;  /* blocking read until 1 char received */
if(tcsetattr(fd,TCSANOW,&new)<0){ perror("serialInit.tcsetattr"); exit(-1); }
}

//
// Serial port termination
//
void serialClose(int fd){
close(fd);
}

//
// HTTP Callback
//
static int callback_http(
  struct lws *wsi,
  enum lws_callback_reasons reason,
  void *user,void *in,size_t len)
{
return 0;
}

//
// Serial Callback
//
static int callback_serial(
  struct lws *wsi,
  enum lws_callback_reasons reason,
  void *user,void *in,size_t len)
{
unsigned char byte;
char message[LWS_SEND_BUFFER_PRE_PADDING+LWS_SEND_BUFFER_POST_PADDING+3];
switch(reason){
  case LWS_CALLBACK_ESTABLISHED:
    printf("connection established\n");
    lws_callback_on_writable(wsi);
    break;
  case LWS_CALLBACK_RECEIVE:
                // Ici sont traites les messages envoyes par le navigateur
    printf("received data: %s\n",(char *)in);
    if(sscanf(in,"%hhd",&byte)==1) write(sd,&byte,1);
    //////////////////////////////////
    
    sleep(2000); //temps de pause ICI
    
    /////////////////////////////
    break;
  case LWS_CALLBACK_SERVER_WRITEABLE:
                // Ici sont envoyes les messages au navigateur
    if(read(sd,&byte,1)==1){ 
      char *out=message+LWS_SEND_BUFFER_PRE_PADDING;
      sprintf(out,"%d",byte);
      lws_write(wsi,(unsigned char *)out,strlen(out),LWS_WRITE_TEXT);
      }
    lws_callback_on_writable(wsi);
    break;
  default:
    break;
  }
return 0;
}

//
// Main function
//
static struct lws_protocols protocols[] = {
  {
    "http-only",   // name
    callback_http, // callback
    0,             // data size
    0              // maximum frame size
  },
  {"serial",callback_serial,0,MAX_FRAME_SIZE},
  {NULL,NULL,0,0}
};

int main(void) {
int port=WEBSOCKET_PORT;
struct lws_context_creation_info info;
memset(&info,0,sizeof info);
info.port=port;
info.protocols=protocols;
info.gid=-1;
info.uid=-1;
struct lws_context *context=lws_create_context(&info);
if(context==NULL){
  fprintf(stderr, "libwebsocket init failed\n");
  return -1;
  }
sd=serialOpen(SERIAL_DEVICE,SERIAL_BOTH);
if(sd<0){
  fprintf(stderr, "Cannot access serial port '%s'\n",SERIAL_DEVICE);
  return -1;
  }
serialConfig(sd,SERIAL_SPEED);
printf("starting server...\n");
while(1){
  lws_service(context,WAIT_DELAY);
  }
serialClose(sd);
lws_context_destroy(context);
return 0;
}
