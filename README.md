# Linux localhost UDP client/server message exchange

## What is this?

> This project don't have a real practical utility bisides learning purposes of how UDP protocol works.

This project contains a simple server who can receive messages from a client and shutsdown when client sends a exit message.
In conjuntion, there is a simple client who sends to the server a psudorandom number of messages in [1,10] range with always the same content.

## Requirements:

You will need to have install gcc compailer in a linux machine. You can check it by executing this command in your terminal:

```bash
$gcc --version 
```

You should get an output similar to:

```txt
gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

In case you don't have it install execute this commands in your terminal:

```bash
$ sudo apt update
$ sudo apt install build-essential
```

## How to execute it:

Firstly you have to compile the .c files:

```bash
$ gcc server.c -o server.exe
$ gcc client.c -o client.exe
```

Check that server.exe and client.exe files can be executable. Otherwise, execute this:

```bash
$ chmod +x server.exe
$ chmod +x client.exe
```

Next open 2 different terminals. In the first one execute the server:

```bash
$ ./server.exe
```

In the other one execute the client this way:

```bash
$ ./client.exe <Message> <PortNumber>
```

Keep in mind that the port of the server is always 8080, if you want to change it you will have to change line 10 of server.c and recompile it.

## Documentation:

Here some documentation that can be useful for undertanding the functionality:

### Main() function:

It takes two arguments:

1. argc -> Number of arguments.
2. argv -> Array of arguments.

### Memset() function:

Fills the first bytes of the memory area pointed to with a value. It takes three arguments:

1. Pointer to the memory area to be filled.
2. Value to be set.
3. Number of bytes to be set.

### Htons() function:

Converts the unsigned short integer hostshort from host byte order to network byte order. It takes one argument:

1. The value to be converted.

Returns the converted value.

### explicit_bzero() function:

Erases a number of bytes of the memory starting at the location pointed. Guarantees that compailer optimizations will not remove
the erase operation if it is "unnecessary". It takes 2 arguments:

1. The pointer to the starting point of the memory area to remove.
2. The number of bytes to remove.
3. The pointer of starting memory area to erase.

### Socket() function:

Creates an enpoint for communication and returns a file descriptor that refers to that endpoint. Adds it to a name space (address family) 
but has no address assigned to it. It takes three arguments:

1. The address domain of the socket -> AF_INET for IPv4 && AF_INET6 for IPv6.
2. Especifies the communication semantics and can modify the behavior of socket(). -> SOCK_STREAM for TCP && SOCK_DGRAM for UDP.
3. The protocol to be used with the socket, usually 0.

Returns a file descriptor for the new socket, or -1 for errors.

### Bind() function:

"Assigns a name to a socket."

Assigns the address specified by an sockaddr_in structure to a socket file descriptor. It takes three arguments:

1. The file descriptor of the socket.
2. A pointer to a sockaddr_in structure.
3. The size of the sockaddr_in structure.

Returns 0 on success, -1 on error.

### Recvfrom() fucntion:

Used to receive messages from a socket. Places the message into a buffer without needing to connect the socket previosly. It takes 6 arguments:

1. Socket file descriptor.
2. Restrict pointer to a buffer.
3. Lenght of the buffer.
4. Flags (change behavior). 
5. Pointer to the address of the client sending the data (Optional in case of connected socket).
6. Pointer to the size of the client address (Optional in case of connected socket).

In case of success recvfrom returns the size of the read message. Otherwise, returns -1.

### Sendto() function:

Sends a message on a socket. It takes 6 arguments:

1. Socket file descriptor.
2. Message to send.
3. Lenght of the message.
4. Flags.
5. Pointer to the destination address (Optional in case of connected socket).
6. Pointer to the size of the destination address (Optional in case of connected socket).

In case of success sendto returns the size of the messages sent, otherwise returns -1.

### Close() function:

Close a file descriptor. It takes one argument:

1. File descriptor.
