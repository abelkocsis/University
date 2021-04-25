pragma solidity  >=0.4.22 <0.7.0;

contract morra {
    struct Player {
        uint8 showNum;
        uint8 guessNum;
        uint8 status; // 0: nothing, 1: committed, 2: revealed
        address payable addr;
        uint bal; // balance
        uint time; // last updated time
        bytes32 showCommit; // hash of <showedNumber><password1>
        bytes32 guessCommit; // hash of <guessNumber><password2>
    }
    
    Player [2] players;
    
    function commit(bytes32 showCommit, bytes32 guessCommit) payable public {
        // Decide if therre is free place in the game
        uint playerNum;
        if (players[0].status == 0){
            playerNum = 0;
            players[0].addr = msg.sender;
            players[0].status = 1;
        }
        else if (players[1].status == 0 && players[0].addr != msg.sender){
            playerNum = 1;
            players[1].addr = msg.sender;
            players[1].status = 1;
        }
        else {
            revert("No free place in the game");
        }
        
        // Check payed value and save values
        require(msg.value == 6 ether, "Player has to pay 6 ETH to play.");
        players[playerNum].bal = msg.value;
        players[playerNum].showCommit = showCommit;
        players[playerNum].guessCommit = guessCommit;
        players[playerNum].time = block.timestamp;
    }
    
    function reveal(string memory showPass, string memory guessPass) public{
        // Check if user is in the game
        uint playerNum;
        if (players[0].addr == msg.sender){
            playerNum = 0;
        }
        else if (players[1].addr == msg.sender){
            playerNum = 1;
        }
        else{
            revert("Player is not on the game");
        }
        
        // Check if players have committed, the and validate inputs
        require(players[0].status >= 1 && players[1].status >= 1, "Some of the players has not committed yet");
        require(players[playerNum].status == 1, "Player has already revealed");
        require(keccak256(abi.encodePacked(showPass)) == players[playerNum].showCommit, "Showed number hash error");
        require(keccak256(abi.encodePacked(guessPass)) == players[playerNum].guessCommit, "Guessed number hash error");
        
        // Get numbers from passwords, validate numbers
        uint8 showNum  = uint8(bytes(showPass)[0])-48;
        uint8 guessNum  = uint8(bytes(guessPass)[0])-48;
        require(showNum > 0 && showNum < 6 && guessNum > 0 && guessNum < 6, "Showed or guessed number error");
        
        // Save values
        players[playerNum].showNum = showNum;
        players[playerNum].guessNum = guessNum;
        players[playerNum].status = 2;
        players[playerNum].time = block.timestamp;
        
        // If both player have revealed, evaluate the game
        if (players[0].status == 2 && players[1].status == 2){
            game();
        }
    }
    
    function game() private {
        // To check how much gas this function requires
        uint startGas = gasleft();
        
        // Permamently save values to evaluate the game
        bool win0 = players[0].guessNum == players[1].showNum;
        bool win1 = players[1].guessNum == players[0].showNum;
        uint num0 = players[0].showNum * 1 ether;
        uint num1 = players[1].showNum * 1 ether;
        uint eth0 = players[0].bal; // ETH to send to player0
        uint eth1 = players[1].bal; // ETH to send to player1
        address payable addr0 = players[0].addr;
        address payable addr1 = players[1].addr;
        
        // Delete values on Blockchain
        delete players[0];
        delete players[1];
        
        // Decide who won
        if (win0 && !win1){
            eth0 +=  num1;
            eth1 -= num1;
            require(eth0 >= 6 ether && eth1 < 6 ether); // check overflow
        }
        else if (win1 && !win0){
            eth1 +=  num0;
            eth0 -= num0;
            require(eth1 >= 6 ether && eth0 < 6 ether); // check overflow
        }
        
        // Check how much gas was used
        uint gasUsed = startGas - gasleft();
        
        // Split the gas used in this function in order to be as fair as possible
        if (msg.sender == players[0].addr){
            uint pre0 = eth0;
            uint pre1 = eth1;
            eth0 += gasUsed/2;
            eth1 -= gasUsed/2;
            require(eth0 > pre0 && eth1 < pre1);
            
        }
        else{
            uint pre0 = eth0;
            uint pre1 = eth1;
            eth1 += gasUsed/2;
            eth0 -= gasUsed/2;
            require(eth1 > pre1 && eth0 < pre0);
        }
        
        // Send the counted ETHs to the users.
        addr0.transfer(eth0);
        addr1.transfer(eth1);
    }
    
    
    function timeout() public {
        // Check if user is in the game and if timeout occur
        require(players[0].addr == msg.sender || players[1].addr == msg.sender, "Player is not in a game");
        require(block.timestamp > players[0].time + 30 && block.timestamp > players[1].time + 30, "Timeout not reached");
        
        // Save values permanently
        uint256 eth0 = players[0].bal;
        uint256 eth1 = players[1].bal;
        uint status0 = players[0].status;
        uint status1 = players[1].status;
        address payable addr0 = players[0].addr;
        address payable addr1 = players[1].addr;
        
        // Delete data on blockchain
        delete players[0];
        delete players[1];
        
        // Send all ETH to the user who has done more steps
        if (status0 > status1){
            addr0.transfer(eth0 + eth1);
        }
        else if (status1 > status0){
            addr1.transfer(eth0 + eth1);
        }
        else{
            revert("Players are in the same status");
        }
    }
    
    // generate the hash of a given string
    function generateHash(string memory word) pure public returns (bytes32){
        return keccak256(abi.encodePacked(word));
    }
}