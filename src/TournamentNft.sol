pragma ton-solidity >= 0.47.0;

pragma AbiHeader expire;
pragma AbiHeader time;
pragma AbiHeader pubkey;

import '../tnft-interfaces/NftInterfaces/INftBase/NftBase.sol';
import '../tnft-interfaces/NftInterfaces/IDescription/Description.sol';
import '../tnft-interfaces/NftInterfaces/ITIP6/TIP6.sol';

contract TournamentNft is NftBase, Description, TIP6 {

    string _player1Address;
    string _player2Address;
    string _result;

    bool _player1Setted;
    bool _player2Setted;

    constructor(
        address addrOwner, 
        TvmCell codeIndex,
        uint128 indexDeployValue, 
        string description
    ) public {
        optional(TvmCell) optSalt = tvm.codeSalt(tvm.code());
        require(optSalt.hasValue(), NftErrors.value_is_empty);
        (address addrRoot) = optSalt.get().toSlice().decode(address);
        require(msg.sender == addrRoot, NftErrors.sender_is_not_root);
        require(msg.value >= (_indexDeployValue * 2), NftErrors.value_less_than_required);
        tvm.accept();
        _addrRoot = addrRoot;
        _addrOwner = addrOwner;
        _codeIndex = codeIndex;
        _indexDeployValue = indexDeployValue;
        _description = description;

        _supportedInterfaces[ 
            bytes4(
            tvm.functionId(INftBase.setIndexDeployValue) ^ 
            tvm.functionId(INftBase.transferOwnership) ^
            tvm.functionId(INftBase.getIndexDeployValue) ^
            tvm.functionId(INftBase.getOwner)
            )
        ] = true;

        _supportedInterfaces[ bytes4(tvm.functionId(IName.getName)) ] = true;
        _supportedInterfaces[ bytes4(tvm.functionId(ITIP6.supportsInterface)) ] = true;

        emit TokenWasMinted(addrOwner);

        _deployIndex(addrOwner);
    }

    function setPlayer1Address(string player1Address) public {
        require(_player1Setted == false);

        tvm.accept();
        _player1Address = _player1Address;
        _player1Setted = true;
    }

    function setPlayer2Address(string player2Address) public {
        require(_player2Setted == false);

        tvm.accept();
        _player2Address = _player2Address;
        _player2Setted = true;
    }

    function setResult(string result) public onlyOwner {
        tvm.accept();
        _result = result;
    }

    function getPlayer1Address() public override responsible returns (string player1Address) {
        return {value: 0, flag: 64}(_player1Address);
    }

    function getPlayer2Address() public override responsible returns (string player2Address) {
        return {value: 0, flag: 64}(_player2Address);
    }

    function getResult() public override responsible returns (string result) {
        return {value: 0, flag: 64}(_result);
    }

    modifier onlyOwner {
        require(msg.pubkey() == _ownerPubkey, NftRootErrors.not_my_pubkey);
        _;
    }
}