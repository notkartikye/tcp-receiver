# TCP Receiver Implementation

This project implements a TCP receiver, decomposed into three primary components: a ByteStream class, a Reassembler class, and the TCP Receiver itself.

## Project Structure

- **ByteStream:** Handles reading and writing of bytes in a finite stream with a specified capacity.
- **Reassembler:** Reassembles out-of-order segments received from a sender into a contiguous byte stream.
- **TCP Receiver:** Integrates the ByteStream and Reassembler, handling TCP segments and generating appropriate acknowledgments.

## Getting Started

1. Clone the repository:
   ```sh
   git clone https://github.com/notkartikye/tcp-receiver.git
   cd tcp-receiver
   ```

2. Navigate to the build directory:
    ```sh
   cd build
   ```

3. Configure and build the project:
    ```sh
   cmake ..
   make
   ```
4. After building the project, you can run test cases with ctest:
    ```sh
   ctest
   ```

6. To run the TCP receiver, execute the following command in the build directory:
    
    ```sh
    ./tcp_receiver
    ```
