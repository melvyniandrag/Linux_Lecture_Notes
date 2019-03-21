# A brief curl tutorial

Lol someone goes on the LEARNPROGRAMMING subreddit and asks what curl is. Someone responds ( with sincerity ) that it might have to do
with vector calculus.
https://www.reddit.com/r/learnprogramming/comments/2sxlr2/what_is_curl/
Maybe dont believe what you read online, or take it all with a grain of salt. Theres a lot of junk out there.
Anyway I'm going to give you some good information now about curl that won't send you off reading about vector calculus.


## Simple curl example

```
curl https://www.google.com
```

See it returns some html

by default curl sends GET requests.

You can specify the http verb with the -X flag

```
curl -X GET https://www.google.com
```

## A little bit more in depth with curl.

We are going to use curl now to make authenticated https requests against a popular API. I like reddit and I think 
alot of people do, that's why I'm focusing on it. There are other APIs out there we could hit, but I think this is fun.
The purpose of what we're going to do is to exercise curl a bit. We're going to use the reddit api and get access to some data
on the server that only logged in people can get. If you're a web developer you may have done something like this if you've
integrated google maps into your website or something like that. If you haven't done anything lik that then what we are about to do will look strange
For you just look at it as an exercise in playing with HTTP headers and with different curl options. When the time comes
for you to need to use curl ( or a GUI like postman ) you'll have seen this stuff already and will go "aahhhhhhhhh thanks melvyn now I get it, 
thank you for explaining this complicated stuff to me!"

We talked about associative arrays and Ill just tell you an anecdote again, I already told you. when I first learned what  a dictionary was in python - thats
the python implementation of associative arrays - I thought it was stupid. At that time all I did was numerical solvers of differential equations, and everything
in that code is just regular arrays and I didn't see why you would want to index an array by a string. Some years later and now I use associative rays all the time
because I've had to do more than solve math problems on grids. You'll find this will happen in your career too. 

Youll want ot be a web develloper and you'll say - I'm just going to learn CSS and html. Then you find out about JS. Then you find out about Databases and have to learn sql. 
Then you find out you need to administer your server so you learn bash. Then you need a backend framework so you learn some ruby. etc. etc. and before you know it you learn all
kinds of stuff you once thought was stupid.

And as Ill do at least a few more times in this class, you'll probably remember thinking algebra was stupid and a waste of time. But in this class ( today or in a future class )
we're going to do some change of base calculations you probably hated in 7th grade nad thought were not very useful. And you robably said to your math teacher 
"what's the point fo this anyway, I'll never use this!! I want to take english class instead because that's actually interesting". And then you realize later you need to do set permissions in octal notation on linux and need to know about setting permissions with combinations of 0, 1, 2 and 4. </rant>

https://github.com/reddit-archive/reddit/wiki/oauth2-quick-start-example

Todo:
1. Make a throwaway account
2. Go here and make an app https://ssl.reddit.com/prefs/apps/
    a. Give a name
    b. select script
    c. blank
    d. blank
    e. put https://www.google.com as the redirect url

```
curl -X POST -d 'grant_type=password&username=reddit_bot&password=snoo'  \
            --user-agent "my custom agent" \
            --user 'p-jcoLKBynTLew:gko_LXELoV07ZBNUXrvWZfzE3aI' \
             https://www.reddit.com/api/v1/access_token
```

But in the above use your username and password. In --user you put the token under your app name, and after the : you put the secret key given by your app.

this will return you some json including an access token that lets you make rest api requests.

To make a rest api request ( just one, google reddit rest api to see the full list of end points you can hit ):

```
curl -H "Authorization: bearer J1qK1c18UUGJFAzz9xnH56584l4" \
        -A "ChangeMeClient/0.1 by YourUsername" \
         https://oauth.reddit.com/api/v1/me
```

You can specify the user-agent with the -A or --user-agent flags. Put whatever you want. See my notes below for more on the matter.

## Why do this?

It seems like a trend in web programming now to do single page apps where you make a bunch of AJAX requests against a server
and update components on the front end without pulling a whole new page from the server. This has led to a proliferation
of REST APIs for every little thing. These APIs typically return JSON - you'll go on Amazon, for example, and add something to your shopping
cart, but the web page doesn't reload. Just the items in your cart update. That's because the linux server that is serving the web aplication will give some JSON
to the browser and the browser will update just a piece of the webpage.

## Other stuff

I'm not sure about what is expected for user-agent. Some people say to use a standard one, others say to put any other string. 
For now, I'm just putting whatever works.
https://stackoverflow.com/questions/2763509/best-practices-for-custom-http-user-agent-strings
https://www.cyberciti.biz/faq/curl-set-user-agent-command-linux-unix/

We're going to use curl to access Reddit
Took alot of research to prepare this lecture!
https://www.reddit.com/r/redditdev/comments/3xvl50/reddit_api_responses_100x_slower_depending_on/
https://www.reddit.com/r/redditdev/comments/5w60r1/error_429_too_many_requests_i_havent_made_many/
