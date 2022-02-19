pragma ton-solidity >= 0.47.0;

pragma AbiHeader expire;
pragma AbiHeader time;
pragma AbiHeader pubkey;

import './resolvers/IndexResolver.sol';
import './resolvers/NftResolver.sol';

import './IndexBasis.sol';

import './interfaces/IIndexBasis.sol';

import './errors/NftRootErrors.sol';


contract NftRoot is NftResolver, IndexResolver {

    uint256 _ownerPubkey;
    uint256 _totalMinted;
    address _addrIndexBasis;

    /// _indexDeployValue will be spent on the Index deployment in the Nft contract
    uint128 _indexDeployValue = 0.4 ton;
    /// _remainOnNft - the number of crystals that will remain after the entire mint 
    /// process is completed on the Nft contract
    uint128 _remainOnNft = 0.3 ton;
    /// _deployIndexValue - the number of tokens that will be sent for the
    /// IndexBasic deployment and will remain on the IndexBasic contract after the deployment
    uint128 _deployIndexBasisValue = 0.4 ton;

    event TokenWasMinted(address nftAddr, address creatorAddr);

    constructor(
        TvmCell codeIndex, 
        TvmCell codePlayerNft, 
        TvmCell codeTournamentNft,
        uint256 ownerPubkey
    ) public {
        TvmCell empty;
        require(ownerPubkey != 0, NftRootErrors.pubkey_is_empty);
        require(codeIndex != empty, NftRootErrors.value_is_empty);
        require(codePlayerNft != empty, NftRootErrors.value_is_empty);
        require(codeTournamentNft != empty, NftRootErrors.value_is_empty);
        tvm.accept();

        _codeIndex = codeIndex;
        _codePlayerNft = codePlayerNft;
        _codeTournamentNft = codeTournamentNft;
        _ownerPubkey = ownerPubkey;
    }

    function mintPlayerNft(string description) public {
        require(msg.value >= (_indexDeployValue * 2) + _remainOnNft, NftRootErrors.value_less_than_required);
        tvm.rawReserve(msg.value, 1);

        TvmCell codeNft = _buildPlayerNftCode(address(this));
        TvmCell stateNft = _buildPlayerNftState(codeNft, _totalMinted);
        address nftAddr = new PlayerNft{
            stateInit: stateNft,
            value: (_indexDeployValue * 2) + _remainOnNft
            }(
                msg.sender, 
                _codeIndex,
                _indexDeployValue,
                description
            ); 

        emit TokenWasMinted(nftAddr, msg.sender);

        _totalMinted++;

        msg.sender.transfer({value: 0, flag: 128});
    }

    function mintTournamentNft(string description) public {
        require(msg.value >= (_indexDeployValue * 2) + _remainOnNft, NftRootErrors.value_less_than_required);
        tvm.rawReserve(msg.value, 1);

        TvmCell codeNft = _buildTournamentNftCode(address(this));
        TvmCell stateNft = _buildTournamentNftState(codeNft, _totalMinted);
        address nftAddr = new TournamentNft{
            stateInit: stateNft,
            value: (_indexDeployValue * 2) + _remainOnNft
            }(
                msg.sender, 
                _codeIndex,
                _indexDeployValue,
                description
            ); 

        emit TokenWasMinted(nftAddr, msg.sender);

        _totalMinted++;

        msg.sender.transfer({value: 0, flag: 128});
    }

    function destructIndexBasis() public view onlyOwner {
        require(_addrIndexBasis.value != 0, NftRootErrors.index_not_deployed);
        tvm.accept();
        
        IIndexBasis(_addrIndexBasis).destruct();
    }

    function withdraw(address to, uint128 value) public pure onlyOwner {
        require(address(this).balance > value, NftRootErrors.value_is_greater_than_the_balance);
        tvm.accept();
        to.transfer(value, true, 0);
    }

    function setIndexDeployValue(uint128 indexDeployValue) public onlyOwner {
        tvm.accept();
        _indexDeployValue = indexDeployValue;
    }

    function setRemainOnNft(uint128 remainOnNft) public onlyOwner {
        tvm.accept();
        _remainOnNft = remainOnNft;
    }   

    function setDeployIndexValue(uint128 deployIndexValue) public onlyOwner {
        tvm.accept();
        _deployIndexBasisValue = deployIndexValue;
    }

    function getIndexDeployValue() public view returns(uint128) {
        return _indexDeployValue;
    }

    function getRemainOnNft() public view returns(uint128) {
        return _remainOnNft;
    }

    function getDeployIndexValue() public view returns(uint128) {
        return _deployIndexBasisValue;
    }  

    function getIndexBasisAddress() public view returns(address) {
        return _addrIndexBasis;
    } 

    function getTotalMinted() public view returns(uint256) {
        return _totalMinted;
    }

    modifier onlyOwner {
        require(msg.pubkey() == _ownerPubkey, NftRootErrors.not_my_pubkey);
        _;
    }

}