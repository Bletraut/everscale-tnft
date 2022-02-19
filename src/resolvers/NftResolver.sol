pragma ton-solidity >= 0.43.0;

pragma AbiHeader expire;
pragma AbiHeader time;

import '../TournamentNft.sol';
import '../PlayerNft.sol';

// TODO: Test the hypothesis that inline will be more profitable in a given situation

contract NftResolver {
    TvmCell _codePlayerNft;
    TvmCell _codeTournamentNft;

    function resolveCodeHashPlayerNft() public view returns (uint256 codeHashData) {
        return tvm.hash(_buildPlayerNftCode(address(this)));
    }

        function resolveCodeHashTournamentNft() public view returns (uint256 codeHashData) {
        return tvm.hash(_buildTournamentNftCode(address(this)));
    }

    function resolvePlayerNft(
        address addrRoot,
        uint256 id
    ) public view returns (address addrNft) {
        TvmCell code = _buildPlayerNftCode(addrRoot);
        TvmCell state = _buildPlayerNftState(code, id);
        uint256 hashState = tvm.hash(state);
        addrNft = address.makeAddrStd(0, hashState);
    }

    function resolveTournamentNft(
        address addrRoot,
        uint256 id
    ) public view returns (address addrNft) {
        TvmCell code = _buildTournamentNftCode(addrRoot);
        TvmCell state = _buildTournamentNftState(code, id);
        uint256 hashState = tvm.hash(state);
        addrNft = address.makeAddrStd(0, hashState);
    }

    function _buildPlayerNftCode(address addrRoot) internal virtual view returns (TvmCell) {
        TvmBuilder salt;
        salt.store(addrRoot);
        return tvm.setCodeSalt(_codePlayerNft, salt.toCell());
    }

    function _buildTournamentNftCode(address addrRoot) internal virtual view returns (TvmCell) {
        TvmBuilder salt;
        salt.store(addrRoot);
        return tvm.setCodeSalt(_codeTournamentNft, salt.toCell());
    }

    function _buildPlayerNftState(
        TvmCell code,
        uint256 id
    ) internal virtual pure returns (TvmCell) {
        return tvm.buildStateInit({
            contr: PlayerNft,
            varInit: {_id: id},
            code: code
        });
    }

    function _buildTournamentNftState(
        TvmCell code,
        uint256 id
    ) internal virtual pure returns (TvmCell) {
        return tvm.buildStateInit({
            contr: TournamentNft,
            varInit: {_id: id},
            code: code
        });
    }
}