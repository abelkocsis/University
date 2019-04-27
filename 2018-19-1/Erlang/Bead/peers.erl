-module(peers).

-export([begin/0, get/0]).

begin() ->

get() ->
    global:send(get, {[{info_hash, sum_info}, {peer_id, peer_id}, {event, started_or_empty}]} ).
    %receive
    %    {tracker_response, Peers} ->




