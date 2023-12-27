# Minicoin
A lightweight Bitcoin implementation in C++

# TODO
- [ ] Press 'Enter' to pause mining doesn't work
- [ ] Remove bottom most dangling chain, and also remove placeholder block
- [ ] Change color of mining node to show incompleteness

- [ ] Clean up UI for v0.1 twitter demo
- [ ] Difficulty adjustment
- [ ] Implement wallets

# FUTURE
 - [ ] Right now the way setup_server() works I'm querying the current state of the block that's
   being mined. In theory, I could miss the winning hash for one block and skip to querying the
   mining of the next block. The UI needs a way of noticing a switch and querying the finalized
   block information. A websocket might also solve this problem.

# Dependencies
[Crypto++](https://www.cryptopp.com/)

# References
[Bitcoin Whitepaper](https://bitcoin.org/bitcoin.pdf)

# Competed Tasks
- [x] Change 0-check from end of hash to beginning
- [X] Implement proof of work function