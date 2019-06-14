# Little bit about html and http

There are many protocols out there. They specify how to transmit data over some medium. I work in the embedded space
and I usually work with I2C and SPI protocols on circuit boards, and I work with bluetooth protocols when talking over the air
between circuit boards. There are of course many many protocols and the industry you get yourself into will dictate which ones you
work with. To be more concrete, I work for a company called Hytorc and we communicate between linux computers and tiny circuit boards embedded in
industrial tools. The linux pc needs to package information in a standard way such that when the tool receives it it knows 
how to parse the data. For example ( simplified a bit ) we send data in bursts of up to 20 bytes. The first 4 bytes contain some information about the data that is coming.
It might say the coming data is 10 bytes long and contains text. So the circuit board listens for 10 bytes more and interprets them as text. Otherwise, 
what would the computers do with streams of data? This is hte point of protocols. 

HTTP is the hypertext transfer protocol, and it specifies how data is transferred over the internet. Well there's alot that happens on the internet.
various tools will generate  some http packets, and then some other stuff happens to it and then it gets wrapped in an ethernet packet and 
is blasted out over some physical medium as electrical impulses and then it is received and unpackaged on the destination side, in a browser for example, or will be received by a tool like curl. Interesting stuff. Elaborate here some more interesting discussion about what http is and a little but about how the internet works.

The internet is a client/server relationsihp that allows computers to talk to each other. They have to talk in a standard way - 
they can't just say 'blah' blah to each other and have a meaningful conversation. So some protocols are in place.

There are a few verbs associated with HTTP requests GET, POST, PUT, DELETE, etc. In a later assignment I'll have you modify a webserver to handle all of these verbs. In general each verb makes the server do something different. And http requests come in two parts - a header and a payload. This is standard protocol stuff. A standard sized header will come, and tell the server something about whats coming next. Http has that. There are a few links here - show that some of the http actions have bodies and some don't etc. show a bit about the body. the body can come in different formats - in the header you often specify the datatype of the message - I'm not sure if there is any restriction about what the return type can be. Youll usually see html, json or xml being passed around, however.

html looks like 

<html>
<div></div>
</html>


json looks like this

{ x: "a",
 y: "b"}

and xml looks more or less like html. Its another markup language with these < > kinds of brackets.


https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol

https://en.wikipedia.org/wiki/List_of_HTTP_header_fields#Request_fields

https://en.wikipedia.org/wiki/HTTP_message_body
