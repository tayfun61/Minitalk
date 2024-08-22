# Minitalk

Minitalk is a small data exchange program using UNIX signals. This project from the 42 programming school involves creating a communication program in the form of a client and server. The server must be launched first and print its PID. The client takes two parameters: the server PID and the string to send. The client must communicate the string to the server using UNIX signals. The server must quickly display the string received.

## Key Learnings

- Server and client communication using UNIX signals
- Handling of SIGUSR1 and SIGUSR2 signals
- Efficient transmission of strings between processes

## Learning Objectives

- Understanding UNIX signals and their usage
- Process communication in UNIX systems
- Bitwise operations for encoding/decoding messages

## Usage

1. Compile the project with 'make' command.
2. Get the server PID: ./server
3. Open a new window and write your message: ./client <PID> <Message>
