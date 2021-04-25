pragma solidity >=0.4.22 <0.7.0;
// import "./SafeMath.sol";
// import "./assign3Part2.sol";

contract FairSwap {
    
    uint timeStart;
    address party1;
    address contract1;
    address party2;
    address contract2;
    uint256 amount1;
    uint256 amount2;
    
    function swap(address ownAddr, address ownCont, uint256 ownAmount, address oppAddr, address oppCont, uint256 oppAmount) public{
        if (timeStart = 0){
            timeStart = block.timestamp;
            party1 = ownAddr;
            contract1 = ownCont;
            amount1 = ownAmount;
            party2 = oppAddr;
            contract2 = oppCont;
            amount2 = oppAmount;
        }
        else if (block.timestamp < timeStart + 60){
            timeStart = 0;
            revert("Timeout reached");
        }
        else{
            require(ownAddr == party2 && ownCont == contract2 && ownAmount == amount2 && 
                oppAddr == party1 && oppCont == contract1 && oppAmount == amount1, "Details are not match");
            bool status;
            bytes memory result;
            (status, result) =  contract1.call(abi.encodeWithSignature("getBalance()"));
            require(status);
        }
        
        
	
		
		
		return abi.decode(result, (uint256));
	}
}

