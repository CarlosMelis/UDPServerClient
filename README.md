# Documentation:

## Main() function:

It takes two arguments:

1. argc -> Number of arguments.
2. argv -> Array of arguments.

## Memset() function:

Fills the first bytes of the memory area pointed to with a value. It takes three arguments:

1. Pointer to the memory area to be filled.
2. Value to be set.
3. Number of bytes to be set.

## Htons() function:

Converts the unsigned short integer hostshort from host byte order to network byte order. It takes one argument:

1. The value to be converted.

Returns the converted value.

## explicit_bzero() function:

Erases a number of bytes of the memory starting at the location pointed. Guarantees that compailer optimizations will not remove
the erase operation if it is "unnecessary". It takes 2 arguments:

1. The pointer to the starting point of the memory area to remove.
2. The number of bytes to remove.

1. The pointer of starting memory area to erase.
2. 

## Socket() function:

Creates an enpoint for communication and returns a file descriptor that refers to that endpoint. Adds it to a name space (address family) 
but has no address assigned to it. It takes three arguments:

1. The address domain of the socket -> AF_INET for IPv4 && AF_INET6 for IPv6.
2. Especifies the communication semantics and can modify the behavior of socket(). -> SOCK_STREAM for TCP && SOCK_DGRAM for UDP.
3. The protocol to be used with the socket, usually 0.

Returns a file descriptor for the new socket, or -1 for errors.

## Bind() function:

"Assigns a name to a socket."

Assigns the address specified by an sockaddr_in structure to a socket file descriptor. It takes three arguments:

1. The file descriptor of the socket.
2. A pointer to a sockaddr_in structure.
3. The size of the sockaddr_in structure.

Returns 0 on success, -1 on error.

## Recvfrom() fucntion:

Used to receive messages from a socket. Places the message into a buffer without needing to connect the socket previosly. It takes 6 arguments:

1. Socket file descriptor.
2. Restrict pointer to a buffer.
3. Lenght of the buffer.
4. Flags (change behavior). 
5. Pointer to the address of the client sending the data (Optional in case of connected socket).
6. Pointer to the size of the client address (Optional in case of connected socket).

In case of success recvfrom returns the size of the read message. Otherwise, returns -1.

## Sendto() function:

Sends a message on a socket. It takes 6 arguments:

1. Socket file descriptor.
2. Message to send.
3. Lenght of the message.
4. Flags.
5. Pointer to the destination address (Optional in case of connected socket).
6. Pointer to the size of the destination address (Optional in case of connected socket).

In case of success sendto returns the size of the messages sent, otherwise returns -1.

## Close() function:

Close a file descriptor. It takes one argument:

1. File descriptor.
