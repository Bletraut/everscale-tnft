pragma ton-solidity >= 0.47.0;

pragma AbiHeader expire;
pragma AbiHeader pubkey;
pragma AbiHeader time;

import './IDescription.sol';

abstract contract Description is IDescription {

    string _description;

    function getDescription() public override responsible returns (string description) {
        return {value: 0, flag: 64}(_description);
    }

}