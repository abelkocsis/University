-module(agent).
-export([bad_guy/1, fbi/0]).

bad_guy (Password) ->
    spawn( fun() -> bad_guys(Password) end).
    
bad_guys(Password) ->
    %Name = list_to_atom([rand:uniform(2000),rand:uniform(2000),rand:uniform(2000)]),
    Name = self(),
    global:register_name(Name, self()),
    global:send(guard, {Name, knock_knock}),
    io:format("Knocked~n"),
    receive
        password_question -> 
            io:format("Received pass question~n"),
            global:send(guard, {Name, {password, Password}}),
            io:format("Password sent~n"),
            receive
                come_in ->
                    io:format("The bad guy is in the house~n"),
                    receive
                        run -> 
                            io:format("~p is running ~n", [self()]);
                        {Node, arrest} ->
                            global:send(Node, {Name, surrender}),
                            io:format("~p : I'm arrested~n", [self()])
                    end;
                go_away -> io:format("The bad guy left, bad password~n")
    end
    after 3000 ->  io:format("The bad guy left because of no responding~n")
end.

fbi() ->
    spawn(fun() -> fbis() end).

fbis()->
    %Name = list_to_atom([rand:uniform(2000),rand:uniform(2000),rand:uniform(2000)]),
    Name = self(),
    global:register_name(Name, self()),
    global:send(guard, {Name, knock_knock}),
    receive
        password_question -> global:send(guard, {Name, fbi})
end,
    receive
        L -> Bad_Guys = L
end,
    timer:sleep(rand:uniform(2000)),
    [global:send(X, {Name, arrest}) || X <- Bad_Guys],
    loop().

loop() ->
    receive
        {Node, surrender} -> io:format("FBI: ~p is arrested by FBI!~n", [Node]),
                                loop()
    after 5000 -> io:format("FBI: That's all.~n")
end.


