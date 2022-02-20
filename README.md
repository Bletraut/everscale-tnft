# NTF-TOURNAMENT

<h2>What is it?</h2>
  NTF-TOURNAMENT is a platform for implementing game mechanics based on TrueNFT at the level of smart contracts.
  
<h2>How it works?</h2>
  We have implemented the NftRoot smart contract on the Everscale platform, which is responsible for issuing NFTs necessary for creating a tournament, as well as for registering players.
  With the help of NftRoot, an NFT tournament is created, in which 2 players can take part.
Players contribute their genomes to the NFT tournament (registration). A special program - Oracle (neural network) calculates the genomes of each player and determines the best genome.
  At the end of the tournament, the Oracle records the results of the players in the NFT tournament and determines the winner.

<h2>How it looks?</h2>
  https://ton.bytie.moe/executor</br>
  All NFTs are deployed on the TrueNft blockchain (devdet), contract addresses, methods can be viewed at the following addresses.</br>
  Load all abi files from <a href="https://github.com/Bletraut/everscale-tnft/tree/master/src">everscale-tnft/src/</a></br>

👩‍🚀 NftRoot</br>
```0:de971a3e543d7bad75f908f431aaece483acaf96f2f62916ad4e4cfdd7850724```</br>
Master contract, provides methods for releasing NFT tournaments and players

🏠 TournamentNft</br>
```0:232cf076fa08bca5244353d866a4bff8b5640af07cddbe8f11ee0070c782c9ee```</br>
NFT of the tournament - accepts the genomes of the players of the players (registration for the tournament) and stores the results of the tournament

🖥 Player1Nft</br>
```0:df54101c058fb8766d5580a1110bf5ec420426d2d427537c4e344d3667cdaf86```</br>
NFT with the genome of the first player
  
🖥 Player2Nft</br>
```0:5520002dd0a8c970400fb589b44cc448035add09b049a3338ca6f23d12357969```</br>
NFT with the genome of the second player
