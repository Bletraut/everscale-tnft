pragma ton-solidity >= 0.47.0;

interface IDescription {
    function getDescription() external responsible returns (string description);
}