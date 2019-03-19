# A brief curl tutorial

Lol someone goes on the LEARNPROGRAMMING subreddit and asks what curl is. Someone responds ( with sincerity ) that it might have to do
with vector calculus.
https://www.reddit.com/r/learnprogramming/comments/2sxlr2/what_is_curl/
https://github.com/reddit-archive/reddit/wiki/oauth2-quick-start-example
Maybe dont believe what you read online, or take it all with a grain of salt. Theres a lot of junk out there.


```
curl -X POST -d 'grant_type=password&username=JulianCienfuegos&password=Ernesto1'\
                 --user-agent "my_custom_user_agent" \
                 --user 'ygqLZG2O1-sQmA:BUm7Z4T9vKgQQPqjpKZb-rc7gJg' \
                 https://www.reddit.com/api/v1/access_token
```

I'm not sure about what is expected for user-agent. Some people say to use a standard one, others say to put any other string. 
For now, I'm just putting whatever works.
https://stackoverflow.com/questions/2763509/best-practices-for-custom-http-user-agent-strings
https://www.cyberciti.biz/faq/curl-set-user-agent-command-linux-unix/

We're going to use curl to access Reddit
Took alot of research to prepare this lecture!
https://www.reddit.com/r/redditdev/comments/3xvl50/reddit_api_responses_100x_slower_depending_on/
https://www.reddit.com/r/redditdev/comments/5w60r1/error_429_too_many_requests_i_havent_made_many/
