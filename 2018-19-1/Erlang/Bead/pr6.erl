-module(pr6).
-export([run/1, test/0, run2/1]).

run(N) ->
	[ spawn(pr6, test, []) || _ <- lists:seq(1, N)].

test() ->
	io:format("MyPid: ~p ~n", [self()]).

run2(N) ->
    Last = loop(N, self()),
	Last ! ok,
	receive
		ok -> "end"
	end.

worker(Pid)->
	test(),
    receive
		ok -> Pid ! ok
    end.
    
loop(N, PrevPid) ->
    PP = spawn(fun() -> worker(PrevPid) end),
    if 
        N > 1 -> loop(N-1, PP);
        N == 1 -> PP
end.


