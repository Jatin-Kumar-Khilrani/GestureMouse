#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>


int main(int argc, char *argv[])
{
  int sim_fd;
  float x=0, y=0, evt=0;
  char cordinatebuffer[10];

  int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;

  struct timespec spec;
  time_t currenttime,prevtime;


/*   Open the sysfs coordinate node */
  sim_fd = open("/sys/devices/platform/virmouse/vmevent", O_RDWR);
  if (sim_fd < 0) {
    perror("Couldn't open vms coordinate file\n");
    exit(-1);
  }

     /*Create UDP socket*/
   udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

   /*Configure settings in address struct*/
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(6000);
   serverAddr.sin_addr.s_addr = inet_addr("192.168.1.4");//0.94
   memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

   /*Bind socket with address struct*/
   bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

   /*Initialize size variable to be used later on*/
   addr_size = sizeof serverStorage;

  while (1) {

	  /* take system time and see if you are greater than 3 seconds */
	  clock_gettime(CLOCK_REALTIME,&spec);

	  currenttime=spec.tv_sec;

	  /* Try to receive any incoming UDP datagram. Address and port of
	       requesting client will be stored on serverStorage variable */
	     nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

	     sscanf(buffer,"%f|%f|%f",&x,&y,&evt);
	     printf("buffer = %s , x=%f and y=%f and evt=%f\n",buffer,x,y,evt);

	     sprintf(cordinatebuffer, "%d %d %d", (int)y*-1, (int)x, (int)evt);
		 write(sim_fd, cordinatebuffer, strlen(cordinatebuffer));
		 fsync(sim_fd);
		 //sleep(1);


	/*
     Generate random relative coordinates
    x = random()%20;
    y = random()%20;
    if (x%2) x = -x; if (y%2) y = -y;

     Convey simulated coordinates to the virtual mouse driver
    sprintf(cordinatebuffer, "%d %d %d", x, y, 0);
    write(sim_fd, cordinatebuffer, strlen(cordinatebuffer));
    fsync(sim_fd);
    sleep(1);*/
  }

  /*close(sim_fd);*/
}
