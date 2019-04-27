-module(pr7_new).
-export([run/2, map/2, parmap/2, ordmap/2, fib/1]).


run(F, L) ->
	Dispatcher = spawn(fun() -> dispatcher(L) end),
    Collector = spawn(fun() -> collector([]) end),
    N = 2*erlang:system_info(logical_processors),
    %N = 3,
	Workers = [ spawn(fun() -> worker({Dispatcher, Collector, F}) end) || 
          _ <- lists:seq(1, N)],
    MyPid = self(),
    Dispatcher ! {finished, MyPid},
    receive
        dispatcher_finished -> exit
    end,
    io:format("Dispatcher finished"),
    [X ! {stop, MyPid} || X <- Workers],
    loop(N),
    io:format("All worker finished"),
    %Collector ! {subresult, MyPid},
    %receive
    %    Acc -> Result = Acc
    %end,
    %io:format(Acc),
    Collector ! {stop, MyPid},
    receive
        collector_finished -> exit
    end,
    io:format("Collector finished").
    %Result.
    


loop(N) ->
    if
        N == 0 -> exit;
        true -> receive
                    worker_finished -> exit
                end,
                io:format("A worker finished."),
                loop(N-1)
    end.
    

dispatcher([]) ->
	receive
		{newlist, List} ->
			dispatcher(List);
        {finished, Runner} -> 
            Runner ! dispatcher_finished
	end;
dispatcher([H | T]) ->
	receive
		{ready, Worker} ->
			Worker ! {data, H},
			dispatcher(T)
	end.
	
collector(Acc) ->
	receive
		{result, Res} ->
			collector([Res | Acc]);
		{subresult, Pid} ->
			Pid ! Acc,
			collector(Acc);
        {stop, Pid} ->
            Pid ! collector_finished,
            exit
	end.

worker({Dispatcher, Collector, F} = State) ->
	Dispatcher ! {ready, self()},
	receive
		{data, Data} ->
				Collector ! {result, F(Data)},
				worker(State);
        {stop, Pid} ->
                Pid ! worker_finished,
                exit
	end.
		


fib(0) ->
    1;
fib(1) ->
    1;
fib(N) ->
	fib(N-1) + fib(N-2).
	
	
map(F, L) -> 
	%lists:map(F, L).
	[ F(E) || E <- L].

ordmap(F, L) -> 
	MyPid = self(),
	Pids = [spawn(fun() -> MyPid ! {self(), F(E)} end) || E <- L],
	[receive
		{Pid, Res} -> Res
	 end || Pid <- Pids]. 
	 
parmap(F, L) -> 
	Pid = self(),
	[spawn(fun() -> Pid ! F(E) end) || E <- L],
	[receive
		Res -> Res
	 end || _ <- L]. 
	 
	 %erLast login: Wed Nov  7 14:24:19 on console
%Melindas-MacBook-Pro:~ melindatoth$ erl
%Erlang/OTP 20 [erts-9.0] [source] [64-bit] [smp:4:4] [ds:4:4:10] [async-threads:10] [hipe] [kernel-poll:false] [dtrace]

%Hello Melinda
%Eshell V9.0  (abort with ^G)
%1> self().
%<0.59.0>
%2> prcess_info().
%** exception error: undefined shell command prcess_info/0
%3> process_info(<0.59.0>).
%undefined
%4> self().                
%<0.62.0>
%5> process_info(<0.62.0>).
%[{current_function,{erl_eval,do_apply,6}},
 %{initial_call,{erlang,apply,2}},
 %{status,running},
 %{message_queue_len,0},
 %{messages,[]},
 %{links,[<0.58.0>]},
 %{dictionary,[]},
 %{trap_exit,false},
 %{error_handler,error_handler},
 %{priority,normal},
 %{group_leader,<0.53.0>},
 %{total_heap_size,650},
 %{heap_size,233},
 %{stack_size,24},
 %{reductions,2337},
 %{garbage_collection,[{max_heap_size,#{error_logger => true,kill => true,
                                       %size => 0}},
                      %{min_bin_vheap_size,46422},
                      %{min_heap_size,233},
                      %{fullsweep_after,65535},
                      %{minor_gcs,7}]},
 %{suspending,[]}]
%6> self() ! alma.
%alma
%7> process_info(<0.62.0>).
%[{current_function,{erl_eval,do_apply,6}},
 %{initial_call,{erlang,apply,2}},
 %{status,running},
 %{message_queue_len,1},
 %{messages,[alma]},
 %{links,[<0.58.0>]},
 %{dictionary,[]},
 %{trap_exit,false},
 %{error_handler,error_handler},
 %{priority,normal},
 %{group_leader,<0.53.0>},
 %{total_heap_size,3196},
 %{heap_size,1598},
 %{stack_size,24},
 %{reductions,8165},
 %{garbage_collection,[{max_heap_size,#{error_logger => true,kill => true,
                                       %size => 0}},
                      %{min_bin_vheap_size,46422},
                      %{min_heap_size,233},
                      %{fullsweep_after,65535},
                      %{minor_gcs,4}]},
 %{suspending,[]}]
%8> process_info(<0.62.0>, messages).
%{messages,[alma]}
%9> 
%BREAK: (a)bort (c)ontinue (p)roc info (i)nfo (l)oaded
       %(v)ersion (k)ill (D)b-tables (d)istribution
%^CMelindas-MacBook-Pro:~ melindatoth$ cd Desktop/fp2/
%Melindas-MacBook-Pro:fp2 melindatoth$ ls
%pr2.beam	pr3.erl		pr5.beam	pr6.erl		proba.erl
%pr2.erl		pr4.beam	pr5.erl		pr7.erl
%pr3.beam	pr4.erl		pr6.beam	proba.beam
%Melindas-MacBook-Pro:fp2 melindatoth$ erl
%Erlang/OTP 20 [erts-9.0] [source] [64-bit] [smp:4:4] [ds:4:4:10] [async-threads:10] [hipe] [kernel-poll:false] [dtrace]

%Hello Melinda
%Eshell V9.0  (abort with ^G)
%1> c(pr7).
%pr7.erl:12: Warning: variable 'F' is unused
%pr7.erl:12: Warning: variable 'L' is unused
%pr7.erl:14: Warning: variable 'F' is unused
%pr7.erl:14: Warning: variable 'L' is unused
%{ok,pr7}
%2> pr7:fib(7).
%21
%3> pr7:fib(36).
%24157817
%4> timer:tc(pr7, fib, [36]).
%{669054,24157817}
%5> timer:tc(pr7, fib, [37]).
%{1071816,39088169}
%6> timer:tc(pr7, fib, [38]).
%{1734328,63245986}
%7> timer:tc(pr7, fib, [39]).
%{2874866,102334155}
%8> timer:tc(pr7, map, [fun pr7:fib/1, [36,37,39]]).
%{1,ok}
%9> c(pr7).                                         
%{ok,pr7}
%10> timer:tc(pr7, map, [fun pr7:fib/1, [36,37,39]]).
%{4572432,[24157817,39088169,102334155]}
%11> pr7:map(fun pr7:fib/1, [36,37,39]).             
%[24157817,39088169,102334155]
%12> pr7:parmap(fun pr7:fib/1, [36,37,39]).
%[<0.81.0>,<0.82.0>,<0.83.0>]
%13> c(pr7).                                         
%{ok,pr7}
%14> timer:tc(pr7, parmap, [fun pr7:fib/1, [36,37,39]]).
%{3031278,[24157817,39088169,102334155]}
%15> timer:tc(pr7, parmap, [fun pr7:fib/1, [36,37,39,39]]).
%{3945816,[24157817,39088169,102334155,102334155]}
%16> timer:tc(pr7, map, [fun pr7:fib/1, [36,37,39,39]]).    
%{7371214,[24157817,39088169,102334155,102334155]}
%17> observer:start().
%ok
%18> timer:tc(pr7, parmap, [fun pr7:fib/1, [36,37,39,39]]).
%{3961977,[24157817,39088169,102334155,102334155]}
%19> timer:tc(pr7, parmap, [fun pr7:fib/1, [39,36,37,39,39]]).
%{5242326,[24157817,39088169,102334155,102334155,102334155]}
%20> timer:tc(pr7, map, [fun pr7:fib/1, [39,36,37,39,39]]).   
%{10567708,[102334155,24157817,39088169,102334155,102334155]}
%21> c(pr7).                                                  
%pr7.erl:21: Warning: variable 'Pid' shadowed in generate
%{ok,pr7}
%22> c(pr7).
%{ok,pr7}
%23> timer:tc(pr7, parmap, [fun pr7:fib/1, [39,36,37,39,39]]).
%{9633131,[24157817,39088169,102334155,102334155,102334155]}
%24> timer:tc(pr7, ordmap, [fun pr7:fib/1, [39,36,37,39,39]]).
%{10177175,[102334155,24157817,39088169,102334155,102334155]}
%25> erlang:system_info(cores_avaialble).
%** exception error: bad argument
     %in function  erlang:system_info/1
        %called as erlang:system_info(cores_avaialble)
%26> erlang:system_info(cores_available).
%** exception error: bad argument
     %in function  erlang:system_info/1
        %called as erlang:system_info(cores_available)
%27> erlang:system_info(available_cores).
%** exception error: bad argument
     %in function  erlang:system_info/1
        %called as erlang:system_info(available_cores)
%28> erlang:system_info(logical_processors__available).
%** exception error: bad argument
     %in function  erlang:system_info/1
        %called as erlang:system_info(logical_processors__available)
%29> erlang:system_info(logical_processors_available). 
%unknown
%30> erlang:system_info(logical_processors).          
%4
%31> erlang:system_info(logical_processors_online).
%4
%32> c(pr7).                                                  
%pr7.erl:26: variable 'Collertor' is unbound
%pr7.erl:28: function worker/1 undefined
%pr7.erl:5: Warning: function run/2 is unused
%pr7.erl:10: Warning: function dispatcher/1 is unused
%pr7.erl:17: Warning: function collector/1 is unused
%pr7.erl:23: Warning: function worker/3 is unused
%pr7.erl:23: Warning: variable 'Collector' is unused
%error
%33> c(pr7).
%pr7.erl:28: function worker/1 undefined
%pr7.erl:5: Warning: function run/2 is unused
%pr7.erl:10: Warning: function dispatcher/1 is unused
%pr7.erl:17: Warning: function collector/1 is unused
%pr7.erl:23: Warning: function worker/3 is unused
%error
%34> c(pr7).
%pr7.erl:5: Warning: function run/2 is unused
%pr7.erl:10: Warning: function dispatcher/1 is unused
%pr7.erl:17: Warning: function collector/1 is unused
%pr7.erl:23: Warning: function worker/1 is unused
%{ok,pr7}
%35> c(pr7).
%pr7.erl:10: Warning: function dispatcher/1 is unused
%pr7.erl:17: Warning: function collector/1 is unused
%{ok,pr7}
%36> c(pr7).
%{ok,pr7}
%37> c(pr7).
%{ok,pr7}
%38> pr7:run(fun pr7:fib/1, [2,3,4,5,4,5,5,565,5,5]).
%[<0.6207.0>,<0.6208.0>,<0.6209.0>,<0.6210.0>,<0.6211.0>,
 %<0.6212.0>,<0.6213.0>,<0.6214.0>]
%39> 
%=ERROR REPORT==== 12-Nov-2018::09:39:25 ===
%Error in process <0.6205.0> with exit value:
%{function_clause,[{pr7,dispatcher,[[]],[{file,"pr7.erl"},{line,11}]}]}

%39> 
%39> 
%39> 
%39> [ exit(Pid, kill) || Pid <- [<0.6207.0>,<0.6208.0>,<0.6209.0>,<0.6210.0>,<0.6211.0>,]
%39>  <0.6212.0>,<0.6213.0>,<0.6214.0>]].
%* 5: syntax error before: ']'
%39> L = [<0.6207.0>,<0.6208.0>,<0.6209.0>,<0.6210.0>,<0.6211.0>,                39>  <0.6212.0>,<0.6213.0>,<0.6214.0>].
%[<0.6207.0>,<0.6208.0>,<0.6209.0>,<0.6210.0>,<0.6211.0>,
 %<0.6212.0>,<0.6213.0>,<0.6214.0>]
%40> [ exit(Pid, kill) || Pid <- L].                                             [true,true,true,true,true,true,true,true]
%41> exit(<0.6206.0>, kill)         
%41> .
%true
%42> observer:start().
%ok
%43> i().
%Pid                   Initial Call                          Heap     Reds Msgs
%Registered            Current Function                     Stack              
%<0.0.0>               otp_ring0:start/2                      376      894    0
%init                  init:loop/1                              2              
%<0.1.0>               erts_code_purger:start/0               610    77198    0
%erts_code_purger      erts_code_purger:wait_for_request        0              
%<0.2.0>               erts_literal_area_collector:start      233    75055    0
                      %erts_literal_area_collector:msg_l        5              
%<0.3.0>               erts_dirty_process_code_checker:s      233       52    0
                      %erts_dirty_process_code_checker:m        1              
%<0.6.0>               erlang:apply/2                        4185   920561    0
%erl_prim_loader       erl_prim_loader:loop/3                   5              
%<0.32.0>              gen_event:init_it/6                   1598     1887    0
%error_logger          gen_event:fetch_msg/6                   10              
%<0.33.0>              erlang:apply/2                        1598      600    0
%application_controlle gen_server:loop/7                        7              
%<0.35.0>              application_master:init/4              233      118    0
                      %application_master:main_loop/2           7              
%<0.36.0>              application_master:start_it/4          233      139    0
                      %application_master:loop_it/4             5              
%<0.37.0>              supervisor:kernel/1                    610     2221    0
%kernel_sup            gen_server:loop/7                       10              
%<0.38.0>              erlang:apply/2                       46422   203094    0
%code_server           code_server:loop/1                       3              
%<0.40.0>              rpc:init/1                             233       81    0
%rex                   gen_server:loop/7                       10              
%<0.41.0>              global:init/1                          233      112    0
%global_name_server    gen_server:loop/7                       10              
%<0.42.0>              erlang:apply/2                         233       74    0
                      %global:loop_the_locker/1                 5              
%<0.43.0>              erlang:apply/2                         233       52    0
                      %global:loop_the_registrar/0              2              
%<0.44.0>              inet_db:init/1                         233      428    0
%inet_db               gen_server:loop/7                       10              
%<0.45.0>              global_group:init/1                    233      123    0
%global_group          gen_server:loop/7                       10              
%<0.46.0>              file_server:init/1                     610     9675    0
%file_server_2         gen_server:loop/7                       10              
%<0.47.0>              gen_event:init_it/6                    233      100    0
%erl_signal_server     gen_event:fetch_msg/6                   10              
%<0.48.0>              supervisor_bridge:standard_error/      233       99    0
%standard_error_sup    gen_server:loop/7                       10              
%<0.49.0>              erlang:apply/2                         233       60    0
%standard_error        standard_error:server_loop/1             2              
%<0.50.0>              supervisor_bridge:user_sup/1           233      123    0
                      %gen_server:loop/7                       10              
%<0.51.0>              user_drv:server/2                      987   125130    0
%user_drv              user_drv:server_loop/6                   9              
%<0.52.0>              group:server/3                         233      251    0
%user                  group:server_loop/3                      4              
%<0.53.0>              group:server/3                       10958   153717    0
                      %group:server_loop/3                      4              
%<0.54.0>              kernel_config:init/1                   233       96    0
                      %gen_server:loop/7                       10              
%<0.55.0>              supervisor:kernel/1                    233      225    0
%kernel_safe_sup       gen_server:loop/7                       10              
%<0.59.0>              erlang:apply/2                        2586    35636    0
                      %shell:shell_rep/4                       17              
%<0.102.0>             wxe_master:init/1                      233      898    0
%wxe_master            gen_server:loop/7                       10              
%<0.103.0>             erlang:apply/2                        2586   137308    0
                      %timer:sleep/1                            5              
%<0.106.0>             timer:init/1                           610      612    0
%timer_server          gen_server:loop/7                       11              
%<0.4834.0>            erlang:apply/2                         987    53176    0
                      %c:pinfo/1                               50              
%<0.16206.0>           observer_wx:init/1                    1598    16373    0
%observer              wx_object:loop/6                        10              
%<0.16207.0>           wxe_server:init/1                      610    34707    0
                      %gen_server:loop/7                       10              
%<0.16209.0>           observer_sys_wx:init/1               10958    26319    0
                      %wx_object:loop/6                        10              
%<0.16210.0>           observer_perf_wx:init/1                376     3560    0
                      %wx_object:loop/6                        10              
%<0.16211.0>           observer_alloc_wx:init/1               610     4460    0
                      %wx_object:loop/6                        10              
%<0.16214.0>           observer_app_wx:init/1                 610     2001    0
                      %wx_object:loop/6                        10              
%<0.16215.0>           observer_pro_wx:init/1                 610     5301    0
                      %wx_object:loop/6                        10              
%<0.16216.0>           erlang:apply/2                        2586     9048    0
                      %observer_pro_wx:table_holder/1           8              
%<0.16225.0>           observer_port_wx:init/1                610     3375    0
                      %wx_object:loop/6                        10              
%<0.16226.0>           observer_tv_wx:init/1                  610     3289    0
                      %wx_object:loop/6                        10              
%<0.16227.0>           observer_trace_wx:init/1              2586    14109    0
                      %wx_object:loop/6                        10              
%Total                                                     100681  1922337    0
                                                             %382              
%ok
%44> c(pr7).                                                                     pr7.erl:34: function sworker/1 undefined
%error
%45> c(pr7).
%{ok,pr7}
%46> pr7:run(fun pr7:fib/1, [2,3,4,5,4,5,5,5,6,5,5,5]).                          [<0.19532.0>,<0.19533.0>,<0.19534.0>,<0.19535.0>,
 %<0.19536.0>,<0.19537.0>,<0.19538.0>,<0.19539.0>]
%47> erlang:process_info(<0.19531.0>, messages).
%{messages,[]}
%48> erlang:process_info(<0.19530.0>, messages).
%{messages,[{ready,<0.19536.0>},
           %{ready,<0.19537.0>},
           %{ready,<0.19538.0>},
           %{ready,<0.19539.0>},
           %{ready,<0.19532.0>},
           %{ready,<0.19533.0>},
           %{ready,<0.19534.0>},
           %{ready,<0.19535.0>}]}
%49> erlang:process_info(<0.19535.0>, messages).
%{messages,[]}
%50> c(pr7).                                           
%{ok,pr7}
%51> pr7:run(fun pr7:fib/1, [2,3,4,5,4,5,5,5,6,5,5,5]).
%[<0.25942.0>,<0.25943.0>,<0.25944.0>,<0.25945.0>,
 %<0.25946.0>,<0.25947.0>,<0.25948.0>,<0.25949.0>]
%52> <0.25941.0> ! {subresult, self()}.
%{subresult,<0.4834.0>}
%53> flush().                                          
%Shell got [8,8,8,13,8,8,8,5,8,5,3,2]
%ok
%54> <0.25941.0> ! {subresult, self()}.
%{subresult,<0.4834.0>}
%55> pr7:run(fun pr7:fib/1, [2,3,4,5,4,5,5,5,6,5,5,5]).
%[<0.27802.0>,<0.27803.0>,<0.27804.0>,<0.27805.0>,
 %<0.27806.0>,<0.27807.0>,<0.27808.0>,<0.27809.0>]
%56> <0.27801.0> ! {subresult, self()}.                
%{subresult,<0.4834.0>}
%57> flush().                                          
%Shell got [8,8,8,13,8,8,8,5,8,5,3,2]
%Shell got [8,8,8,13,8,8,8,5,8,5,3,2]
%ok
%58> 

