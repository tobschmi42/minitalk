*This project has been created as part of the 42 curriculum by tobschmi.*

# Minitalk

## Description

In this project the two programes “client” and “server” were created. The role of the server is to receive messages from the client and printing it out on the terminal, while the client is sending a message to the server. This is done by using the two UNIX signals SIGUSR1 and SIGUSR2

## Instructions

Both the client and the server can be compiled with the make command.

First the server should be started. The server will print out its own PID. Then the client should be started with two arguments. The first argument should be the PID of the server, the second argument should be the string that the server should print out.

In case of an error, “Error\n” will be printed out.

Stopping the client before the full message was sent produces undefined behaviour.

## Ressources

Subject file - [https://cdn.intra.42.fr/pdf/pdf/196737/en.subject.pdf](https://cdn.intra.42.fr/pdf/pdf/196737/en.subject.pdf)  
Explanation of pause function - [https://www.nayab.dev/linux/man2/pause.html](https://www.nayab.dev/linux/man2/pause.html)

man page of pause() - [https://man7.org/linux/man-pages/man2/pause.2.html](https://man7.org/linux/man-pages/man2/pause.2.html)

Wikipedia page for Unicode - [https://en.wikipedia.org/wiki/Unicode](https://en.wikipedia.org/wiki/Unicode)

man page for signal() - [https://pubs.opengroup.org/onlinepubs/007904875/functions/sigaction.html](https://pubs.opengroup.org/onlinepubs/007904875/functions/sigaction.html)

man page for sigaction() - [https://man7.org/linux/man-pages/man2/sigaction.2.html](https://man7.org/linux/man-pages/man2/sigaction.2.html)

man page for getpid() - [https://man7.org/linux/man-pages/man2/getpid.2.html](https://man7.org/linux/man-pages/man2/getpid.2.html)

arch’s man page for the pid\_t datatype - [https://man.archlinux.org/man/pid\_t.3type.en](https://man.archlinux.org/man/pid_t.3type.en)

man page sigaddset() - [https://man7.org/linux/man-pages/man3/sigaddset.3p.html](https://man7.org/linux/man-pages/man3/sigaddset.3p.html)

man page kill() - [https://man7.org/linux/man-pages/man2/kill.2.html](https://man7.org/linux/man-pages/man2/kill.2.html)

Explanation of Signals in C - [https://www.geeksforgeeks.org/c/signals-c-language/](https://www.geeksforgeeks.org/c/signals-c-language/)

bitwise operations in C - [https://en.wikipedia.org/wiki/Bitwise\_operations\_in\_C](https://en.wikipedia.org/wiki/Bitwise_operations_in_C)  
AI has been used to get an explanation on the sigaction structure.

