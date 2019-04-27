-module(fibp).
-export([fib/2]).

fib(N, K) ->
    MainPid = self(),
    spawn(fun() -> (fibP(MainPid, MainPid, N)) end),
    loop(K).

loop(K) ->
    receive
        {result, A} -> A;
        {question, Pid} ->
            if 
                K > 0 -> 
                    Pid ! par,
                    loop(K-1);
                true ->
                    Pid ! szekv,
                    loop(K)
            end;
        {finished} ->
            loop(K+1)
end.

fibS(0) ->
    1;
fibS(1) ->
    1;
fibS(N) ->
    fibS(N-2) + fibS(N-1).

fibP(MainPid, ParentPid, 0) ->
    ParentPid ! {result, 1};
fibP(MainPid,ParentPid, 1) ->
    ParentPid ! {result, 1};
fibP(MainPid, ParentPid, N) ->
    MyPid = self(),
    MainPid ! {question, MyPid},
    receive
        par -> 
            spawn(fun() -> (fibP(MainPid, MyPid, N-1)) end),
            spawn(fun() -> (fibP(MainPid, MyPid, N-2)) end),
            A = receiving([]),
            MainPid ! finished;
        szekv ->
            A = fibS(N-1) + fibS(N-2)
    end,
    ParentPid ! {result, A}.

receiving(L) ->
    G = (length(L) == 2),
    if 
        G -> lists:sum(L);
        true ->
            receive
                {result, A} -> receiving(L++[A])
            end
    end.