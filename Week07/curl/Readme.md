# curl
Follow this tutorial:
https://idratherbewriting.com/learnapidoc/docapis_understand_curl.html

CURL is used for exchanging data with various web protocols. We're going to use it for http, but if you type `man curl` you'll
see you can use it for otther things as well. We're just going to use it for http/https in this class, that's the major use
case anyway.

We're going to use it for making REST requests. REST is the big buzzword now in web development I guess. If you know why, you
know why, if you don't I won't try to explain it because it takes a little time to get familiar with it. I learned by accident,
I needed to do a thing on a website and it turned out that there was a technique called AJAX that worked nicely with what I 
wanted to do. That led into the Django REST framework, and then ultimately to learning about some front end frameworks. Your 
route might be different. Whatever the case, curl is good for things called REST requests.

We're using curl for http requests - those generally return html. HTTP is the hyper text transfer protocol, html is the hyper 
text markup language, so it makes sense. You send a request to a server and it sends you back some html. Your browser turns
that html ( + css + javascript ) into something nice looking. Sometimes you send stuff back to the server, like your credit
card number, so it can bill you for your latest amazon purchase or whatever.

But sometimes you can send things like JSON and xml back and forth too. 
Often times you'll send JSON and XMl to talk to a RESTful API. We'll implement our own REST API on a cloud machine in a few days
Generally speaking you send a message that has a 
header and a body. What you put in those are up to you and have to obey the http protocol. This is all very abstract, so we 
won't say too much more, we'll just start using these ideas by following along with the pretty good tutorial I found online.

This tutorial familiarizes you with some of the curl parameters. You all should work thorugh the tutorial now. Should only take about 20 minutes. Then we'll discuss it more and go over the homework.


here's the api the tuturial plays with

http://petstore.swagger.io/

Maybe useful

https://gist.github.com/joyrexus/85bf6b02979d8a7b0308

https://curl.haxx.se/docs/httpscripting.html


