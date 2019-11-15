# include <fcntl.h>
# include <stdio.h>
int main ()
{
char buffer;
int fd ;
fd = open ("/dev/gamepad" , O_RDONLY );
while(1){

read ( fd , &buffer,1  );

if (buffer > 0){
printf (" Value : %d \n " , buffer);
}

}
}

