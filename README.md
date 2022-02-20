# NTF-TOURNAMENT

<h2>What is it?</h2>
  NTF-TOURNAMENT is a platform for implementing game mechanics based on TrueNFT at the level of smart contracts.
  
<h2>How is works?</h2>
  We have implemented the NftRoot smart contract on the Everscale platform, which is responsible for issuing NFTs necessary for creating a tournament, as well as for registering players.
  With the help of NftRoot, an NFT tournament is created, in which 2 players can take part.
Players contribute their genomes to the NFT tournament (registration). A special program - Oracle (neural network) calculates the genomes of each player and determines the best genome.
  At the end of the tournament, the Oracle records the results of the players in the NFT tournament and determines the winner.

<h2>How it looks?</h2>
  All NFTs are deployed on the TrueNft blockchain, contract addresses, methods can be viewed at the following addresses.
    
👩‍🚀 NftRoot\n
```0:de971a3e543d7bad75f908f431aaece483acaf96f2f62916ad4e4cfdd7850724```\n
Master contract, provides methods for releasing NFT tournaments and players

🏠 TournamentNft\n
```0:e3e517fa8313d5d1ef5f6bb16452e2d7cc8449986782062ecf5729eb6fa00d65```\n
NFT of the tournament - accepts the genomes of the players of the players (registration for the tournament) and stores the results of the tournament

🖥 Player1Nft\n
```0:b7ae85b8acff24b124f62bff11b8469219783496046fe37f56f20a7d0b513269```\n
NFT with the genome of the first player
  
🖥 Player2Nft
0:072a27ee8e061f14a6bb306de03dd9fdb7a81d6632347d974f82e8e5c60dfadd
NFT with the genome of the second player
