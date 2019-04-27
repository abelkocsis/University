-module(szekv).
-export([toBitString/1, charToBitString/1, bitStringToChar/1, xOr/2, encrypt/2, 
decrypt/2, isCycledIn/2, getKey/2, decodeMessage/2, isAinB/2 ]).

toBitString(N) ->
    lists:reverse(lists:dropwhile(fun(D) -> D =:= 0 end, [X || <<X:1>> <= <<N:64>>])).

charToBitString(N) ->
    A = toBitString(N),
    charToBitStringS(A).

charToBitStringS(A) ->
    L = [X || X <- (A++[0,0,0,0,0,0,0,0]) ],
    lists:sublist(L, 8).

bitStringToChar(L) ->
    bitStringToCharS(L, 0, 0).

bitStringToCharS([F|L], K, N) ->
    if 
        length([F|L])>1 -> bitStringToCharS(L, K+1, (N + math:pow(2, K)*F));
        length([F|L])<2 -> round(N + math:pow(2, K)*F)
end.
 
xOr(A, B)->
    if
        length(A) == 0 -> B;
        length(B) == 0 -> A;
        true -> xOrS([], A, B)   
    end.
    

xOrS(L, [X|Xs], [Y|Ys])->
    if
        X == Y -> NL = L ++ [0];
        true -> NL = L ++ [1]  
    end,
    if
        length(Xs)==0 -> NL++Ys;
        length(Ys)==0 -> NL++Xs;
        true -> xOrS(NL, Xs, Ys)   
    end.

encrypt(Text, Key) ->
    S = [lists:nth(round(math:fmod(I, length(Key)))+1, Key) || I <- lists:seq(0, length(Text)-1)],
    BT = [charToBitString(lists:nth(I, Text)) || I <- lists:seq(1, length(Text)) ],
    BK = [charToBitString(lists:nth(I, S)) || I <- lists:seq(1, length(S)) ],
    Xor = [xOr(lists:nth(I, BT), lists:nth(I, BK)) || I <- lists:seq(1, length(BT))],
    [bitStringToChar(lists:nth(I, Xor)) || I <- lists:seq(1, length(Xor))] .

decrypt(Text, Key) ->
    encrypt(Text, Key).

isCycledIn(A, B) ->
    if
        length(B) > length (A) ->
            isCycledInS(A, B);
        length(B) == length(A) -> A == B;
        true -> false
    end.

dropFirst(N, L) ->
    [lists:nth(I, L) || I <- lists:seq(N+1, length(L))].

takeFirst(N, L) ->
    [lists:nth(I, L) || I <- lists:seq(1, N)].

takeFromTo(F, T, L) ->
    [lists:nth(I, L) || I <- lists:seq(F, T)].

isCycledInS(A, B) ->
        T = lists:prefix(A, B),
        if
            length(B) > length (A) ->
                if
                    T -> isCycledInS(A, dropFirst(length(A), B));
                    true -> false
                end;
            length(A) > length(B) -> lists:prefix(B, A);
            length(A) == length(B) -> A == B
        end.


getKey(Text, Cipher) ->
    CycledKey = decrypt(Text, Cipher),
    findShortest(1, CycledKey).

findShortest(N, CycledKey) ->
    Pre = takeFirst(N, CycledKey),
    G = isCycledIn(Pre, CycledKey),
    if
        G -> Pre;
        true ->  findShortest(N+1, CycledKey)     
    end.

decodeMessage(Cipher, PartOfText) ->
    Key = decodeMessageS(1, Cipher, PartOfText, 9999, []),
    decrypt(Cipher, Key).
    

decodeMessageS(N, Cipher, PartOfText, MinLength, BestKey) ->
    if
        N + length(PartOfText) > length(Cipher) -> BestKey;
        true ->     Key = getKey(PartOfText, takeFromTo(N, N+length(PartOfText)-1, Cipher)),
                    De = decrypt(Cipher, Key),
                    %G = ((lists:max(De)<123) and (lists:max(Key) < 123) and (lists:min(De)>30) and (lists:min(Key) > 30)),
                    G = isAinB(PartOfText, De),
                    %io:write(G),
                    %io:write(De),
                    %io:write(Key),
                    %io:write(BestKey),
                    if
                        (length(Key) < MinLength) and G ->
                            %io:write(Key),
                            decodeMessageS(N+1, Cipher, PartOfText, length(Key), Key);
                        true -> decodeMessageS(N+1, Cipher, PartOfText, MinLength, BestKey)
                    end    
    end.

isAinB(A, B) ->
    if
        length(B) == 0 -> false;
        true -> isAinBseged(1, A, B)    
    end.

isAinBseged(N, A, B) ->
    G = lists:sublist(B, N, length(A)) == A,
    if
        N+length(A) > length(B) -> false;
        G -> true;       
        true -> isAinBseged(N+1, A, B)  
    end.
    
