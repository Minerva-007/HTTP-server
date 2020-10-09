HTTP server
This folder contains the source code and exe file of a working HTTP server.
Request format:-
Whenever a client request something from your server,it will send at most these 4 things:-
1)Request line,containing an HTTP command,its parameters and <CR><LF>
2)Request header fields,containing different flags and info for your server,each line ends with <CR><LF>
3)Empty line, its just <CR><LF>
4)An optional message body; it may be just nothing in here.

Response format:-
Your server will reply in the form of this:-
1)Status line,which has a status number,its short mnemonic and (surprise!)<CR><LF>
2)Response header fields,containing different info for your client your server sends. As expected,each one ends with <CR><LF>
3)Guess what? An empty Line <CR><LF>
4)An optional message Body; this time you may send your client the requested resource such as an image,or you might send him a HTML file.
