-module(guard).
-define(GuardNode, node()).
-export([warehouse/1]).

warehouse(Password) ->
    global:register_name(guard, self()),
    guard(Password, []).

guard (Password, L) ->
    receive
        {Node, knock_knock} ->
            global:send(Node, password_question),
            io:format("Knock-knock~n"),
            guard(Password, L);
        {Node, {password, Pass}} ->
            io:format("Password received~n"),
            if
                Pass == Password ->
                    io:format("Good password~n"),
                    global:send(Node, come_in),
                    guard(Password, L++[Node]);
                true -> 
                    io:format("Bad password~n"),
                    global:send(Node, go_away),
                    guard(Password, L)
            end;
        {Node, fbi} ->
            io:format("FBI is here~n"),
            global:send(Node, L),
            timer:sleep(rand:uniform(2000)),
            [try global:send(X, run) of _ -> ok catch exit:_ -> ok end || X <- L],
            io:format("Everyone (who can) is running~n")         

end.