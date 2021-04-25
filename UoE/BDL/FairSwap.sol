pragma solidity >=0.4.22 <0.7.0;

contract FairSwap {
    
    address payable party1;
    address payable party2;
    address contract1;
    address contract2;
    uint256 amount1;
    uint256 amount2;
    uint256 p1Gas; // gas used by party1
    uint256 p2Gas; // gas used by party2
    uint startTime;
    uint8 status; // 0: no booking, 1: booked, 2: party1 has transferred
    
    function book() public{
        uint startGas = gasleft();
        require(status == 0 || block.timestamp > startTime + 180, "Contract has already booked");
        status = 1;
        party1 = msg.sender;
        startTime = block.timestamp;
        p2Gas = 0;
        p1Gas = startGas - gasleft();
    }
    
    function transactionDone(address ownContract, address oppContract, address payable oppAddr,  uint256 ownAmount,  uint256 oppAmount) payable public{
        uint startGas = gasleft();
        require(msg.value == 1 ether, "1 Ether must be sent to the contract");
        bool callStatus;
        bytes memory result;
        require(status < 3, "Status error");
        if (status == 1){
            require(party1 == msg.sender, "User error");
            (callStatus, result) =  ownContract.call(abi.encodeWithSignature("getBalance()"));
            require(callStatus && abi.decode(result, (uint256)) >= ownAmount, "getBalance error");
            contract1 = ownContract;
            party2 = oppAddr;
            contract2 = oppContract;
            amount1 = ownAmount;
            amount2 = oppAmount;
            status = 2;
            startTime = block.timestamp;
            p1Gas += startGas - gasleft();
        }
        else if (status == 2){
            require(party1 == oppAddr && party2 == msg.sender && contract1 == oppContract && contract2 == ownContract
                && amount1 == oppAmount && amount2 == ownAmount, "Parameter error");
            (callStatus, result) =  ownContract.call(abi.encodeWithSignature("getBalance()"));
            require(callStatus, "getBalance error");
            if (contract1 == contract2){
                require(amount1 + amount2 >= amount1 && abi.decode(result, (uint256)) >= amount1 + amount2, "GetBalance amount error");
            }
            else{
                require(abi.decode(result, (uint256)) >= amount2, "getBalance amount error");
            }
            
            (callStatus, ) =  contract1.call(abi.encodeWithSignature("transfer(address,uint256)", party2, amount1));
            require(callStatus, "Contract1 transfer error");
            (callStatus, ) =  contract2.call(abi.encodeWithSignature("transfer(address,uint256)", party1, amount2));
            require(callStatus, "Contract2 transfer error");
            status = 0;
            p2Gas += startGas - gasleft();
            party1.transfer(1 ether + p1Gas - p2Gas);
            party2.transfer(1 ether - (p1Gas - p2Gas));
        }
        
    }
    
    function check(address ownContract, address oppContract, address payable oppAddr,  uint256 ownAmount,  uint256 oppAmount) public returns (bool){
        uint startGas = gasleft();
        require(status == 2 && party1 == oppAddr && party2 == msg.sender && contract1 == oppContract && contract2 == ownContract
            && amount1 == oppAmount && amount2 == ownAmount, "Parameter error");
        p2Gas += startGas - gasleft();
        return true;
    }
    
    function withdraw(address contr) public{
        bool callStatus;
        bytes memory result;
        if (status == 0){
            (callStatus, result) =  contr.call(abi.encodeWithSignature("getBalance()"));
            require(callStatus, "getBalance error");
            if (abi.decode(result, (uint256)) > 0){
                (callStatus, ) =  contr.call(abi.encodeWithSignature("transfer(address,uint256)", msg.sender, abi.decode(result, (uint256))));
                require(callStatus, "Transfer error");
            }
        }
        else if (status == 1){
            require(msg.sender == party1, "Only party1 is allowed to withdraw");
            status = 0;
        }
        else {
            // status == 2
            require(msg.sender == party1 && contr == contract1 && block.timestamp > startTime + 60, "Only party1 is allowed to withdraw");
            (callStatus, ) =  contr.call(abi.encodeWithSignature("transfer(address,uint256)", msg.sender, amount1));
            require(callStatus, "Transfer error");
            party1.transfer(1 ether);
            status = 0;
        }
    }
}